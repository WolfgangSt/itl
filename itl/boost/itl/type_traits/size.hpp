/*----------------------------------------------------------------------------+
Copyright (c) 2008-2008: Joachim Faulhaber
+-----------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+----------------------------------------------------------------------------*/
#ifndef __itl_type_traits_size_JOFA_080911_H__
#define __itl_type_traits_size_JOFA_080911_H__

namespace itl
{
	template <class Type>
	struct size
	{ 
		/// size type of Type
		typedef std::size_t type; 
	};
} // namespace itl

#endif


