// -*- C++ -*-

#pragma once

#include <memory>
#include <vector>

#include "brush.h"

namespace TOK
{
	class brush_holder
	{
#pragma region Types
		public: typedef std::vector< std::shared_ptr<brush> >   brush_container_t;
        public: typedef brush_container_t::iterator                  iterator;
        public: typedef brush_container_t::const_iterator            const_iterator;
#pragma endregion

#pragma region Data
		private: brush_container_t _brushes_pos;
		private: brush_container_t _brushes_neg;
#pragma endregion

#pragma region Ctor/Dtor/op=
		public: brush_holder( void ):
		    _brushes_pos(),
			_brushes_neg()
		{
		}

		public: ~brush_holder()
		{
		}
#pragma endregion

		public: void make_pos_brushes( float x_pos, float y_pos,
                                       float x_neg, float y_neg,
                                       float z_pos );

		public: void make_neg_brushes( float x_pos, float y_pos,
                                       float x_neg, float y_neg,
                                       float z_pos );

#pragma region Observers
		public: const_iterator begin_pos( void ) const
		{
			return _brushes_pos.begin();
		}

		public: const_iterator end_pos(void) const
		{
			return _brushes_pos.end();
		}

		public: const_iterator begin_neg(void) const
		{
			return _brushes_neg.begin();
		}

		public: const_iterator end_neg(void) const
		{
			return _brushes_neg.end();
		}

		public: size_t size_pos( void ) const
		{
			return _brushes_pos.size();
		}

		public: size_t size_neg(void) const
		{
			return _brushes_neg.size();
		}

		public: bool empty_pos(void) const
		{
			return _brushes_pos.empty();
		}

		public: bool empty_neg(void) const
		{
			return _brushes_neg.empty();
		}
#pragma endregion
	};
}
