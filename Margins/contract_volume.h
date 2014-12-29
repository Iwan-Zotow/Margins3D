// -*- C++ -*-

#pragma once

#include "rvolume.h"

namespace TOK
{
   void contract_volume( rvolume* dest, const rvolume* src,
                         float x_neg, float x_pos,
                         float y_neg, float y_pos,
                         float z_neg, float z_pos );
}
