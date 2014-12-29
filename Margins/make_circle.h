// -*- C++ -*-

#pragma once

#include <memory>

#include "rvolume.h"

std::unique_ptr<TOK::rvolume> make_circle( float radius, float length );
