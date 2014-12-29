// -*- C++ -*-

#pragma once

#include <cassert>
#include <cstring>
#include <cstdint>

#include <iosfwd>

namespace TOK
{
   class rvolume
   {
         /// ctors and dtor
      private:
         rvolume( void );
      public:
         rvolume( int nx, int ny, int nz, const uint8_t* vol = 0 );
         rvolume( const char* filename );
         rvolume( const rvolume& rv );

         ~rvolume();

         /// assignment op
         rvolume& operator=( const rvolume& rv );

         /// accessors
         uint8_t  pixel( int ix, int iy, int iz ) const;

		 int      nx(void) const
		 {
			 return _nx;
		 }

		 int      ny(void) const
		 {
			 return _ny;
		 }

		 int      nz(void) const
		 {
			 return _nz;
		 }

		 const uint8_t* volume(void) const
		 {
			 return _vol;
		 }

		 const uint8_t* plane(int iz) const
		 {
			 assert(iz >= 0);
			 assert(iz < _nz);
			 return _vol + iz * _nplane;
		 }

         int      calculate_volume( void ) const;

         /// mutators
		 uint8_t* volume(void)
		 {
			 return _vol;
		 }

		 uint8_t* plane(int iz)
		 {
			 assert(iz >= 0);
			 assert(iz < _nz);
			 return _vol + iz * _nplane;
		 }

         void     read( const char* filename );

         // some interesting functions

         /// dump volume as series of PBM images
         void     write_PBM( const char* filename ) const;

         /// write binary representation
         void     write( const char* filename ) const;

      private:
         void              allocate_vol( const uint8_t* src );
         void              write_plane( const uint8_t* plane, std::ostream& os ) const;

         int      _nx;
         int      _ny;
         int      _nz;

         int      _nplane; // number of bits in an image plane

         uint8_t* _vol;
   };
}

inline TOK::rvolume::rvolume( void ):
   _nx(0),
   _ny(0),
   _nz(0),
   _nplane(0),
   _vol(0)
{
}

inline void TOK::rvolume::allocate_vol( const uint8_t* src )
{
   _vol = new uint8_t [_nplane * _nz];
   if ( src != 0 )
   {
      memcpy( _vol, src, _nplane*_nz );
   }
   else
   {
      memset( _vol, 0, _nplane*_nz );
   }
}

inline TOK::rvolume::rvolume( int nx, int ny, int nz, const uint8_t* vol ):
   _nx( nx ),
   _ny( ny ),
   _nz( nz ),
   _nplane( _nx*_ny ),
   _vol( 0 )
{
   assert( _nx > 0 );
   assert( _ny > 0 );
   assert( _nz > 0 );
   assert( _nplane > 0 );

   allocate_vol( vol );
}

inline TOK::rvolume::~rvolume()
{
   delete [] _vol;
}

inline uint8_t TOK::rvolume::pixel( int ix, int iy, int iz ) const
{
   assert( ix >= 0 );
   assert( ix < _nx );
   assert( iy >= 0 );
   assert( iy < _ny );
   assert( iz >= 0 );
   assert( iz < _nz );

   return _vol[iz*_nplane + iy*_nx + ix];
}
