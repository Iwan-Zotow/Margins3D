#include <cassert>
#include <cmath>

#include "brush.h"
#include "utilities.h"

static void compute_increments( float x, float y, float z,
									 int& x_inc, int& y_inc, int& z_inc )
{
	assert( x >= 0.0f );
	assert( y >= 0.0f );
	assert( z >= 0.0f );

	x_inc = TOK::nearest_int( x + 0.5f );
	y_inc = TOK::nearest_int( y + 0.5f );
	z_inc = TOK::nearest_int( z );
}

void TOK::compute_pos_inc( float x_pos, float y_pos, float z_pos,
                           int& x_pos_inc, int& y_pos_inc, int& z_pos_inc )
{
	compute_increments( x_pos, y_pos, z_pos,
						x_pos_inc, y_pos_inc, z_pos_inc );
}

void TOK::compute_neg_inc( float x_neg, float y_neg, float z_neg,
                           int& x_neg_inc, int& y_neg_inc, int& z_neg_inc )
{
	compute_increments( x_neg, y_neg, z_neg,
                        x_neg_inc, y_neg_inc, z_neg_inc );
}

void TOK::paint_plane( uint8_t*      plane,
                       int nx,       int ny,
                       int center_x, int center_y,
                       const brush* b, uint8_t color )
{
	assert( plane != 0 );
	assert( nx > 0 );
	assert( ny > 0 );
	assert( center_x >= 0 );
	assert( center_x < nx );
	assert( center_y >= 0 );
	assert( center_y < ny );
	assert( b != 0 );

	int nbytes = b->h_neg() + b->h_pos() + 1;

	for ( int ir = - b->v_neg(); ir <= b->v_pos(); ++ir ) // loop over rows
	{
		const uint8_t* src = b->row( ir );

		uint8_t* dest = plane + ( center_y + ir ) * nx + ( center_x - b->h_neg() );

		for( int k = 0; k < nbytes; ++k )
		{
			 dest[k] = dest[k] || src[k];
		}
	}
}
