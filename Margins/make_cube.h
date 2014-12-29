// -*- C++ -*-

#pragma once

#include <memory>

#include "rvolume.h"

std::unique_ptr<TOK::rvolume> make_cube( float x, float y, float length );
