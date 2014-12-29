// -*- C++ -*-

#pragma once

#include "rvolume.h"

namespace TOK
{
	///
	/// knowing source volume and margins, returns expanded/contracted placeholder
	///
	rvolume* make_new_volume( const rvolume* src_vol,
                              float x_neg, float x_pos,
                              float y_neg, float y_pos,
                              float z_neg, float z_pos,
                              bool  expand );
}
