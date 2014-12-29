#include <cassert>
#include <cmath>
#include <list>

#include "expand_volume.h"
#include "utilities.h"
#include "brush.h"
#include "brush_holder.h"
#include "extract_contours.h"

static void dump_brushes( const TOK::brush_holder& bh )
{
	{
		int zp = 0;
		for( auto bp = bh.begin_pos(); bp != bh.end_pos(); ++bp, ++zp )
		{
			char path[256];
			snprintf( path, sizeof(path), "pos_brush%d", zp );
			bp->get()->write_PBM( path );
		}
	}

	{
		int zn = 0;
		for( auto bn = bh.begin_neg(); bn != bh.end_neg(); ++bn, ++zn )
		{
			char path[256];
			snprintf( path, sizeof(path), "neg_brush%d", zn );
			bn->get()->write_PBM( path );
		}
   }
}

static void merge_planes( const uint8_t* src, uint8_t* dst,
                          int snx, int sny,
                          int dnx, int dny,
                          int shift_x, int shift_y )
{
   assert( src != 0 );
   assert( dst != 0 );
   assert( snx > 0 );
   assert( sny > 0 );
   assert( dnx >= snx );
   assert( dny >= sny );
   assert( shift_x >= 0 );
   assert( shift_y >= 0 );

   for( int iy = 0; iy < sny; ++iy )
   {
      int src_rowidx = iy * snx;
      int dst_rowidx = ( iy + shift_y ) * dnx;

      const uint8_t* s = src + src_rowidx;
      uint8_t*       d = dst + dst_rowidx + shift_x;
      const uint8_t* e = d + snx;
      while ( d != e )
      {
         *d++ |= *s++;
      }
   }
}

void TOK::expand_volume( TOK::rvolume* dest, const TOK::rvolume* src,
                         float x_neg, float x_pos,
                         float y_neg, float y_pos,
                         float z_neg, float z_pos )
{
	assert( dest != 0 );
	assert( src != 0 );
	assert( x_neg >= 0.0f );
	assert( x_pos >= 0.0f );
	assert( y_neg >= 0.0f );
	assert( y_pos >= 0.0f );
	assert( z_neg >= 0.0f );
	assert( z_pos >= 0.0f );

	int x_pos_inc = 0;
	int y_pos_inc = 0;
	int z_pos_inc = 0;

	int x_neg_inc = 0;
	int y_neg_inc = 0;
	int z_neg_inc = 0;
	TOK::compute_pos_inc( x_pos, y_pos, z_pos, x_pos_inc, y_pos_inc, z_pos_inc );
	TOK::compute_neg_inc( x_neg, y_neg, z_neg, x_neg_inc, y_neg_inc, z_neg_inc );

	// now compute set of positive and negative brushes
	// and store them into brush holder
	brush_holder bh;

	bh.make_pos_brushes( x_pos, y_pos, x_neg, y_neg, z_pos );
	bh.make_neg_brushes( x_pos, y_pos, x_neg, y_neg, z_neg );

	// dump_brushes( bh );

	// now copy data from old volume into new volume
	for( int iz = 0; iz != src->nz(); ++iz )
	{
		const uint8_t* src_pln = src->plane( iz );

		for( int k = 0; k != bh.size_pos(); ++k )
		{
			uint8_t* dst_pln = dest->plane( iz + z_neg_inc + k );
			merge_planes( src_pln, dst_pln,
						  src->nx(), src->ny(),
						  dest->nx(), dest->ny(),
						  x_neg_inc, y_neg_inc );
		}

		for( int k = 1; k != bh.size_neg(); ++k )
		{
			uint8_t* dst_pln = dest->plane( iz + z_neg_inc - k );
			merge_planes( src_pln, dst_pln,
						  src->nx(), src->ny(),
                          dest->nx(), dest->ny(),
						  x_neg_inc, y_neg_inc );
		}
	}

	// now extract contours and paint using negative and positive brushes
	for( int iz = 0; iz != src->nz(); ++iz )
	{
		auto r( TOK::extract_contours( src, iz ) );
		if ( r != 0 )
		{
			for( auto i = r->begin(); i != r->end(); ++i )
			{
				for( auto k = i->cbegin(); k != i->cend(); ++k )
				{
					if ( ! bh.empty_pos() ) // have some positive brushes defined
					{
						/// paint with positive brushes
						int zp = 0;
						for( brush_holder::const_iterator bp = bh.begin_pos(); bp != bh.end_pos(); ++bp, ++zp )
						{
							uint8_t* pln = dest->plane( iz + z_neg_inc + zp );
							paint_plane( pln, dest->nx(), dest->ny(),
										 k->x + x_neg_inc, k->y + y_neg_inc, bp->get(), 1U );
						}
					}
					if ( ! bh.empty_neg() ) // have some negative brushes defined
					{
						/// paint with negative brushes
						int zn = 0;
						for( brush_holder::const_iterator bn = bh.begin_neg(); bn != bh.end_neg(); ++bn, ++zn )
						{
							uint8_t* pln = dest->plane( iz + z_neg_inc - zn );
							paint_plane( pln, dest->nx(), dest->ny(),
										 k->x + x_neg_inc, k->y + y_neg_inc, bn->get(), 1U );
						}
					}
				}
			}
		}
   }
}
