// -*- C++ -*-

#pragma once

#include <cassert>
#include <cstring>
#include <cstdint>

namespace TOK
{
	class brush
	{
#pragma region Data
		private: int      _h_pos;
		private: int      _v_pos;
		private: int      _h_neg;
		private: int      _v_neg;
		private: uint8_t* _bm;
#pragma endregion

#pragma region Ctor/Dtor/op=
		private: brush(void) :
			_h_pos(0),
			_v_pos(0),
			_h_neg(0),
			_v_neg(0),
			_bm(nullptr)
		{
		}

		public: brush( float x_pos, float y_pos, float x_neg, float y_neg );

		public: brush(const brush& b):
			_h_pos(b._h_pos),
			_v_pos(b._v_pos),
			_h_neg(b._h_neg),
			_v_neg(b._v_neg),
			_bm( nullptr )
		{
			int sz = b.size();
			_bm = new uint8_t[sz];
			memcpy(_bm, b._bm, sz);
		}

		public: ~brush()
		{
			delete[] _bm;
		}

		public: brush& operator=(const brush& b)
		{
			if (this != &b)
			{
				_h_pos = b._h_pos;
				_v_pos = b._v_pos;
				_h_neg = b._h_neg;
				_v_neg = b._v_neg;

				delete[] _bm;
				int sz = b.size();
				_bm = new uint8_t[sz];
				memcpy(_bm, b._bm, sz);
			}
			return *this;
		}
#pragma endregion

#pragma region Observers
		public: const uint8_t* bitmap(void) const
		{
			return _bm;
		}

		public: const uint8_t* row(int row_idx) const
		{
			return _bm + (row_idx + _v_neg) * hsize();
		}

		public: int hsize(void) const
		{
			return (_h_pos + _h_neg + 1);
		}

		public: int vsize(void) const
		{
			return (_v_pos + _v_neg + 1);
		}

		public: int size(void) const
		{
			return hsize()*vsize();
		}

		public: int	h_pos(void) const
		{
			return _h_pos;
		}

		public: int v_pos(void) const
		{
			return _v_pos;
		}

		public: int h_neg(void) const
		{
			return _h_neg;
		}

		public: int v_neg(void) const
		{
			return _v_neg;
		}
#pragma endregion

		public: void  write_PBM( const char* filename ) const;
   };
}
