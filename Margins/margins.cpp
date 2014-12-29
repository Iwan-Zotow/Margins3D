#include <cassert>
#include <algorithm>

#include "rvolume.h"
#include "make_new_volume.h"
#include "expand_volume.h"
#include "contract_volume.h"
#include "margins.h"

const float MARGINS_TOLERANCE = 0.5f;

/// check parameters for consistency, asserts for now, exceptions later
static void check_parameters( const TOK::rvolume* src_vol,
                              float x_neg, float x_pos,
                              float y_neg, float y_pos,
                              float z_neg, float z_pos,
                              float skin_margin,
                              int   nthr  )
{
	assert( src_vol != 0 );

	assert( x_neg >= 0.0f );
	assert( x_pos >= 0.0f );

	assert( y_neg >= 0.0f );
	assert( y_pos >= 0.0f );

	assert( z_neg >= 0.0f );
	assert( z_pos >= 0.0f );

	assert( skin_margin >= 0.0f );

	assert( nthr >= 1 );
}

static void fixup_margins( float& x_neg, float& x_pos,
                           float& y_neg, float& y_pos,
                           float& z_neg, float& z_pos )
{
	if ( x_pos < MARGINS_TOLERANCE )
	{
		x_pos = 0.0f;
	}
	if ( x_neg < MARGINS_TOLERANCE )
	{
		x_neg = 0.0f;
	}
	if ( y_pos < MARGINS_TOLERANCE )
	{
		y_pos = 0.0f;
	}
	if ( y_neg < MARGINS_TOLERANCE )
	{
		y_neg = 0.0f;
	}
	if ( z_pos < MARGINS_TOLERANCE )
	{
		z_pos = 0.0f;
	}
	if ( z_neg < MARGINS_TOLERANCE )
	{
		z_neg = 0.0f;
	}
}

TOK::rvolume* TOK::margins( const TOK::rvolume* src_vol,
                            float x_neg, float x_pos,
                            float y_neg, float y_pos,
                            float z_neg, float z_pos,
                            bool  expand,
                            float skin_margin,
                            int   nthr )
{
	check_parameters( src_vol,
	                  x_neg, x_pos,
                      y_neg, y_pos,
                      z_neg, z_pos,
                      skin_margin,
                      nthr );

	fixup_margins( x_neg, x_pos,
                   y_neg, y_pos,
                   z_neg, z_pos );
 
	rvolume* dest = make_new_volume( src_vol,
                                     x_neg, x_pos,
                                     y_neg, y_pos,
                                     z_neg, z_pos,
                                     expand );

	if ( expand )
	{
		expand_volume( dest, src_vol,
                       x_neg, x_pos,
                       y_neg, y_pos,
                       z_neg, z_pos );
	}
	else
	{
		contract_volume( dest, src_vol,
                         x_neg, x_pos,
                         y_neg, y_pos,
                         z_neg, z_pos );
	}

	return dest;
}
