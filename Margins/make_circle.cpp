#include <cassert>
#include <cmath>
#include <cstdint>

#include "rvolume.h"
#include "utilities.h"
#include "make_circle.h"

static void fill_plane( uint8_t* plane, int nx, int ny, float radius )
{
   float r2 = radius*radius;

   // center of the plane
   float xc = float( nx ) / 2.0f;
   float yc = float( ny ) / 2.0f;

   for( int iy = 0; iy != ny; ++iy )
   {
      float y = float( iy ) + 0.5f;
      for( int ix = 0; ix != nx; ++ix )
      {
         float x = float( ix ) + 0.5f;

         float d2 = TOK::squared( x - xc ) + TOK::squared( y - yc );
         int idx  = iy * nx + ix;
         plane[idx] = ( d2 <= r2 );
      }
   }
}

std::unique_ptr<TOK::rvolume> make_circle( float radius, float length )
{
   assert( radius > 0.0f );
   assert( length > 0.0f );

   if ( radius <= 0.0f )
   {
      return 0;
   }

   if ( length <= 0.0f )
   {
      return 0;
   }

   int nx = int( 2.0f * radius ) + 1;
   int ny = nx;
   int nz = TOK::nearest_int( length );

   auto v = std::make_unique<TOK::rvolume>( nx, ny, nz );

   for( int iz = 0; iz != nz; ++iz )
   {
      uint8_t* plane = v->plane( iz );
      fill_plane( plane, nx, ny, radius );
   }

   return v;
}
