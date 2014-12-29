// -*- C++ -*-

#pragma once

#include "rvolume.h"

namespace TOK
{
	///
	/// src_vol:     source volume
	/// x_neg, x_pos: positive and negative X margins, in pixels, ought to be non-negative,
	/// y_neg, y_pos: positive and negative X margins, in pixels, ought to be non-negative,
	/// z_neg, z_pos: positive and negative X margins, in pixels, ought to be non-negative,
	/// expand:       if "true" we expand, otherwise we contract
	/// skin_margin:  set skin margin cut off
	/// nthr:         number of threads to start
	///
	rvolume* margins( const rvolume* src_vol,
                      float x_neg, float x_pos,
                      float y_neg, float y_pos,
                      float z_neg, float z_pos,
                      bool  expand,
                      float skin_margin,
                      int   nthr );
}
