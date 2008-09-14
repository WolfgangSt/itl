/*----------------------------------------------------------------------------+
Copyright (c) 2008-2008: Joachim Faulhaber
+-----------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+----------------------------------------------------------------------------*/
#ifndef __itl_type_traits_difference_JOFA_080911_H__
#define __itl_type_traits_difference_JOFA_080911_H__

// I DO NOT #include boost/itl/itl_<date_time_adapter>.hpp here, because it
// HAS TO be included by client code prior to this location.

namespace itl
{
	template <class Type> struct difference;

#ifdef ITL_NEEDS_GREGORIAN_DATE_DIFFERENCE_TYPE
	template<> 
	struct difference<boost::gregorian::date> 
	{ typedef boost::gregorian::date_duration type; };  
#endif 

#ifdef ITL_NEEDS_POSIX_TIME_PTIME_DIFFERENCE_TYPE
	template<> 
	struct difference<boost::posix_time::ptime> 
	{ typedef boost::posix_time::time_duration type; };  
#endif

	template <class Type> struct difference{ typedef Type type; };

	/*CL JODO Wir müssen also die instantiierungsreihenfolge beachten!!!
	template <template<class>class Type, class P1>
	struct difference<Type<P1> >{ typedef Type<P1> type; };

	template <template<class,class>class Type, class P1, class P2>
	struct difference<Type<P1,P2> >{ typedef Type<P1,P2> type; };

	template <template<class,class,class>
	class Type, class P1, class P2, class P3>
	struct difference<Type<P1,P2,P3> >{ typedef Type<P1,P2,P3> type; };

	template <template<class,class,class,class>
	class Type, class P1, class P2, class P3, class P4>
	struct difference<Type<P1,P2,P3,P4> >{ typedef Type<P1,P2,P3,P4> type; };

	template <template<class,class,class,class,class>
	class Type, class P1, class P2, class P3, class P4, class P5>
	struct difference<Type<P1,P2,P3,P4,P5> >
	{ typedef Type<P1,P2,P3,P4,P5> type; };
	*/

} // namespace itl

#endif


