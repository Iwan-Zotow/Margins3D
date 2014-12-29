#include <cassert>
#include <cmath>
#include <cstdint>

#include "rvolume.h"
#include "utilities.h"
#include "make_cube.h"

static void fill_plane( uint8_t* plane, int nx, int ny )
{
   for(int iy = 0; iy != ny; ++iy )
   {
      for(int ix = 0; ix != nx; ++ix )
      {
         int idx    = iy * nx + ix;
         plane[idx] = 1U;
      }
   }
}

std::unique_ptr<TOK::rvolume> make_cube( float x, float y, float length )
{
   assert( x > 0.0f );
   assert( y > 0.0f );
   assert( length > 0.0f );

   if ( x <= 0.0f )
   {
      return 0;
   }

   if ( y <= 0.0f )
   {
      return 0;
   }

   if ( length <= 0.0f )
   {
      return 0;
   }

   int nx = TOK::nearest_int( x );
   int ny = TOK::nearest_int( y );
   int nz = TOK::nearest_int( length );

   auto v = std::make_unique<TOK::rvolume>( nx, ny, nz );

   for( int iz = 0; iz != nz; ++iz )
   {
      uint8_t* plane = v->plane( iz );
      fill_plane( plane, nx, ny );
   }

   return v;
}
