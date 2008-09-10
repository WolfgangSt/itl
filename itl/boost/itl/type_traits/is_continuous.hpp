/*----------------------------------------------------------------------------+
Copyright (c) 2008-2008: Joachim Faulhaber
+-----------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
itl_ptime provides adapter code for boost::posix_time::ptime.
It implements incrementation (++) decrementation (--) and a neutral element
w.r.t. addition (neutron()).
-----------------------------------------------------------------------------*/

#ifndef __itl_type_traits_is_continuous_JOFA_080910_H__
#define __itl_type_traits_is_continuous_JOFA_080910_H__

#include <string>

namespace itl
{

	template <class Type>
	struct is_continuous{ enum {value = false}; };

	template<> struct is_continuous<float>       { enum {value = true}; };
	template<> struct is_continuous<double>      { enum {value = true}; };
	template<> struct is_continuous<std::string> { enum {value = true}; };

} // namespace itl

#endif


