#include <algorithm>
#include <cassert>
#include <cmath>

#include "utilities.h"
#include "brush_holder.h"

void TOK::brush_holder::make_pos_brushes( float x_pos, float y_pos,
                                          float x_neg, float y_neg,
                                          float z_pos )
{
	assert( x_pos >= 0.0f );
	assert( y_pos >= 0.0f );
	assert( x_neg >= 0.0f );
	assert( y_neg >= 0.0f );
	assert( z_pos >= 0.0f );

	int x_pos_inc = 0;
	int y_pos_inc = 0;
	int z_pos_inc = 0;
	TOK::compute_pos_inc( x_pos, y_pos, z_pos, x_pos_inc, y_pos_inc, z_pos_inc );

	int x_neg_inc = 0;
	int y_neg_inc = 0;
	int z_neg_inc = 0;
	TOK::compute_neg_inc( x_neg, y_neg, 10.f, x_neg_inc, y_neg_inc, z_neg_inc );

	_brushes_pos.clear();
	_brushes_pos.reserve(z_pos_inc + 1);

	// making bitmaps
	for( int iz = 0; iz <= z_pos_inc; ++iz )
	{
		float coeff = 1.0f - TOK::squared( float( iz )/ z_pos );
		coeff = std::max( 0.0f, coeff ); // prevent from going into negative
		coeff = sqrtf( coeff );

		auto p = std::make_shared<brush>(x_pos*coeff, y_pos*coeff, x_neg*coeff, y_neg*coeff);

		_brushes_pos.push_back( p );
	}
}

void TOK::brush_holder::make_neg_brushes( float x_pos, float y_pos,
                                          float x_neg, float y_neg,
                                          float z_neg )
{
	assert( x_pos >= 0.0f );
	assert( y_pos >= 0.0f );
	assert( x_neg >= 0.0f );
	assert( y_neg >= 0.0f );
	assert( z_neg >= 0.0f );

	int x_pos_inc = 0;
	int y_pos_inc = 0;
	int z_pos_inc = 0;
	TOK::compute_pos_inc( x_pos, y_pos, 10.0f, x_pos_inc, y_pos_inc, z_pos_inc );

	int x_neg_inc = 0;
	int y_neg_inc = 0;
	int z_neg_inc = 0;
	TOK::compute_neg_inc( x_neg, y_neg, z_neg, x_neg_inc, y_neg_inc, z_neg_inc );

	_brushes_neg.clear();
	_brushes_neg.reserve(z_neg_inc + 1);

	// making bitmaps
	for( int iz = 1; iz <= z_neg_inc; ++iz )
	{
		float coeff = 1.0f - TOK::squared( float( iz )/ z_neg );
		coeff = std::max( 0.0f, coeff ); // prevent from going into negative
		coeff = sqrtf( coeff );

		auto p = std::make_shared<brush>(x_pos*coeff, y_pos*coeff, x_neg*coeff, y_neg*coeff);
		_brushes_neg.push_back( p );
	}
}
