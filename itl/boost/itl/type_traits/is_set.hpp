/*----------------------------------------------------------------------------+
Copyright (c) 2008-2008: Joachim Faulhaber
+-----------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+----------------------------------------------------------------------------*/
#ifndef __itl_type_traits_is_set_JOFA_081004_H__
#define __itl_type_traits_is_set_JOFA_081004_H__

namespace itl
{
	template <class Type> struct is_set;

	template <class Type> struct is_set{ enum {value = false}; };

} // namespace itl

#endif


