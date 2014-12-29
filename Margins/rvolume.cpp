#include <cstdint>
#include <iostream>
#include <fstream>

#include "rvolume.h"

TOK::rvolume::rvolume( const char* filename ):
   _nx(0),
   _ny(0),
   _nz(0),
   _nplane(0),
   _vol(0)
{
   std::ifstream is( filename );

   if ( ! is )
   {
      throw 12;
   }

   char buff[1024];

   // eat header
   for( ;; )
   {
      memset( buff, 0, sizeof(buff) );
      is.getline( buff, sizeof buff );
      // std::cerr << buff << '\n';
      if ( buff[0] == '#')
      {
         continue;
      }
      if ( buff[0] == 'P' && buff[1] == '1')
      {
         break;
      }
   }

   is >> _nx >> _ny;

   assert( _nx > 0 );
   assert( _ny > 0 );

   _nz = 1; // one image only for now

   _nplane = _nx*_ny;

   allocate_vol(0);

   for( int iy = _ny - 1; iy >= 0; --iy )
   {
      int rowidx = iy * _nx;
      for( int ix = 0; ix < _nx; ++ix )
      {
         int iii = 0;
         is >> iii;
         _vol[ rowidx + ix] = (iii != 0);
      }
   }
}

TOK::rvolume::rvolume( const rvolume& rv ):
   _nx( rv._nx ),
   _ny( rv._ny ),
   _nz( rv._nz ),
   _nplane( _nx*_ny )
{
   delete [] _vol;

   allocate_vol( rv._vol );
}

TOK::rvolume& TOK::rvolume::operator=( const rvolume& rv )
{
   if ( this != &rv )
   {
      _nx = rv._nx;
      _ny = rv._ny;
      _nz = rv._nz;
      _nplane = rv._nx * rv._ny;

      delete [] _vol;
      allocate_vol( rv._vol );
   }
   return *this;
}

void TOK::rvolume::write_PBM( const char* filename ) const
{
   char fname[128];
   for( int iz = 0; iz < _nz; ++iz )
   {
      // make file name and open stream
      snprintf( fname, sizeof(fname), "%s_%d.pbm", filename, iz );
      std::ofstream os( fname, std::ios::binary | std::ios::out );

      // write PBM header
      os << "P1\n";
      os << ' ' << _nx << ' ' << _ny << '\n';

      // write bitmap itself
      write_plane( plane( iz ), os );

      os.close();
   }
}

void TOK::rvolume::write_plane( const uint8_t* plane, std::ostream& os ) const
{
   static const char bit_char[2] =
   {
      '0', '1'
   };

   for( int iy = _ny - 1; iy >= 0; --iy )
   {
      int rowidx = iy * _nx;
      for( int ix = 0; ix < _nx; ++ix )
      {
         os << ' ' << bit_char[ plane[rowidx+ix] ];
      }
      os << '\n';
   }
   os << '\n';
   os.flush();
}

int TOK::rvolume::calculate_volume( void ) const
{
   const uint8_t* v = _vol;

   int r = 0;
   for( int iz = 0; iz < _nz; ++iz )
   {
      for( int iy = 0; iy < _ny; ++iy )
      {
         for( int ix = 0; ix < _nx; ++ix )
         {
            r += *v++;
         }
      }
   }
   return r;
}

void TOK::rvolume::write( const char* filename ) const
{
   _unlink( filename );
   std::ofstream os( filename, std::ios::binary | std::ios::out );

   os.write( (char*)&_nx, sizeof _nx );
   os.write( (char*)&_ny, sizeof _ny );
   os.write( (char*)&_nz, sizeof _nz );

   os.write( (char*)_vol, _nplane * _nz );
}

void TOK::rvolume::read( const char* filename )
{
   std::ifstream is( filename, std::ios::binary | std::ios::in );

   is.read( (char*)&_nx, sizeof _nx );
   is.read( (char*)&_ny, sizeof _ny );
   is.read( (char*)&_nz, sizeof _nz );

   delete [] _vol;

   is.read( (char*)_vol, _nplane * _nz );
}
