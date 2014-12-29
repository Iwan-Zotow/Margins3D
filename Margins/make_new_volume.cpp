#include <cassert>
#include <cstring>

#include "utilities.h"
#include "make_new_volume.h"

TOK::rvolume* TOK::make_new_volume( const TOK::rvolume* src,
                                    float x_neg, float x_pos,
                                    float y_neg, float y_pos,
                                    float z_neg, float z_pos,
                                    bool  expand )
{
   rvolume* dest = nullptr;
   if ( expand )
   {
      int x_neg_inc = 0;
      int x_pos_inc = 0;

      int y_neg_inc = 0;
      int y_pos_inc = 0;

      int z_neg_inc = 0;
      int z_pos_inc = 0;
      TOK::compute_pos_inc( x_pos, y_pos, z_pos, x_pos_inc, y_pos_inc, z_pos_inc );
      TOK::compute_neg_inc( x_neg, y_neg, z_neg, x_neg_inc, y_neg_inc, z_neg_inc );

      int nx = src->nx() + x_neg_inc + x_pos_inc;
      int ny = src->ny() + y_neg_inc + y_pos_inc;
      int nz = src->nz() + z_neg_inc + z_pos_inc;

      dest = new rvolume( nx, ny, nz, 0 );
   }
   else
   {
      // when we contract, we just need copy of the volume, and that's it
      dest = new rvolume( *src );
   }

   return dest;
}
