// -*- C++ -*-

#pragma once

#include <cstdint>

namespace TOK
{
	void compute_pos_inc( float x_pos, float y_pos, float z_pos,
						  int& x_pos_inc, int& y_pos_inc, int& z_pos_inc );

	void compute_neg_inc( float x_neg, float y_neg, float z_neg,
                          int& x_neg_inc, int& y_neg_inc, int& z_neg_inc );

	// class rvolume;
	// contours_container_t* extract_contours( const rvolume* v, int iz );

	class brush;
	void  paint_plane( uint8_t* plane, int nx, int ny, int center_x, int center_y, const brush* b, uint8_t color );

	inline float squared( float x )
	{
		return x*x;
	}

	inline double squared(double x)
	{
		return x*x;
	}

	inline int nearest_int( float x )
	{
		return (x < 0.0f) ? int( x - 0.5f ) : int( x + 0.5f ); // lrint()
	}

	inline int nearest_int( double x )
	{
		return (x < 0.0) ? int( x - 0.5 ) : int( x + 0.5 ); // lrint()
	}
}
