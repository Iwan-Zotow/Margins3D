#include <cassert>
#include <cmath>
#include <cstring>
#include <iostream>
#include <fstream>

#include "brush.h"
#include "utilities.h"

TOK::brush::brush( float x_pos, float y_pos, float x_neg, float y_neg ):
	_h_pos( 0 ),
	_v_pos( 0 ),
	_h_neg( 0 ),
	_v_neg( 0 ),
	_bm( nullptr )
{
	assert( x_pos >= 0.0f );
	assert( y_pos >= 0.0f );
	assert( x_neg >= 0.0f );
	assert( y_neg >= 0.0f );

	_h_pos = TOK::nearest_int( x_pos );
	_v_pos = TOK::nearest_int( y_pos );

	_h_neg = TOK::nearest_int( x_neg );
	_v_neg = TOK::nearest_int( y_neg );

   // allocate memory for bitmap and clean-it up
   int sz = this->size();

   _bm = new uint8_t [sz];
   memset( _bm, 0, sz );

   // fill up bitmap in quadrants

   float x_pos_inv = 1.0e+10f;
   if ( x_pos > 0.0f )
   {
      x_pos_inv = 1.0f / x_pos;
   }

   float y_pos_inv = 1.0e+10f;
   if ( y_pos > 0.0f )
   {
      y_pos_inv = 1.0f / y_pos;
   }

   float x_neg_inv = 1.0e+10f;
   if ( x_neg > 0.0f )
   {
      x_neg_inv = 1.0f / x_neg;
   }

   float y_neg_inv = 1.0e+10f;
   if ( y_neg > 0.0f )
   {
      y_neg_inv = 1.0f / y_neg;
   }

   float xc = float( _h_neg ) + 0.5f; // X center
   float yc = float( _v_neg ) + 0.5f; // Y center

   // Q ++
   for( int iv = _v_neg; iv != vsize(); ++iv )
   {
      float yy = float( iv ) + 0.5f;
      int ridx = iv * hsize();

      float y2 = TOK::squared( ( yy - yc ) * y_pos_inv ) - 1.0f;
      for( int ih = _h_neg; ih < hsize(); ++ih )
      {
         float xx = float( ih ) + 0.5f;

         assert( ridx + ih < sz );
         _bm[ ridx + ih ] = ( TOK::squared( ( xx - xc ) * x_pos_inv ) + y2 <= 0.0f );
      }
   }

   // Q +-
   for( int iv = 0; iv != _v_neg; ++iv )
   {
      float yy = float( iv ) + 0.5f;
      int ridx = iv * hsize();

      float y2 = TOK::squared( ( yy - yc ) * y_neg_inv ) - 1.0f;
      for( int ih = _h_neg; ih != hsize(); ++ih )
      {
         float xx = float( ih ) + 0.5f;

         assert( ridx + ih < sz );
         _bm[ ridx + ih ] = ( TOK::squared( ( xx - xc ) * x_pos_inv ) + y2 <= 0.0f );
      }
   }

   // Q --
   for( int iv = 0; iv != _v_neg; ++iv )
   {
      float yy = float( iv ) + 0.5f;
      int ridx = iv * hsize();

      float y2 = TOK::squared( ( yy - yc ) * y_neg_inv ) - 1.0f;
      for( int ih = 0; ih != _h_neg; ++ih )
      {
         float xx = float( ih ) + 0.5f;

         assert( ridx + ih < sz );
         _bm[ ridx + ih ] = ( TOK::squared( ( xx - xc ) * x_neg_inv ) + y2 <= 0.0f );
      }
   }

   // Q -+
   for( int iv = _v_neg; iv != vsize(); ++iv )
   {
      float yy = float( iv ) + 0.5f;
      int ridx = iv * hsize();

      float y2 = TOK::squared( ( yy - yc ) * y_pos_inv ) - 1.0f;
      for( int ih = 0; ih != _h_neg; ++ih )
      {
         float xx = float( ih ) + 0.5f;

         assert( ridx + ih < size() );
         _bm[ ridx + ih ] = ( TOK::squared( ( xx - xc ) * x_neg_inv ) + y2 <= 0.0f );
      }
   }
}

void  TOK::brush::write_PBM( const char* filename ) const
{
   static const char bit_char[2] =
   {
      '0', '1'
   };

   const char space = ' ';

   char fname[256];
   snprintf( fname, sizeof(fname), "%s.pbm", filename );
   // make file name and open stream
   std::ofstream os( fname, std::ios::binary | std::ios::out );

   // write PBM header
   os << "P1\n";
   os << space << hsize() << ' ' << vsize() << '\n';

   for( int iv = (_v_pos + _v_neg); iv >= 0; --iv )
   {
      int rowidx = iv * (_h_pos + _h_neg + 1);
      for( int ih = 0; ih != hsize(); ++ih )
      {
         os << ' ' << bit_char[ _bm[rowidx+ih] ];
      }
      os << '\n';
   }
   os << '\n';

   os.close();
}
