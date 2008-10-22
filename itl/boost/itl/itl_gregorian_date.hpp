/*----------------------------------------------------------------------------+
Copyright (c) 2007-2008: Joachim Faulhaber
+-----------------------------------------------------------------------------+
Boost Software License - Version 1.0 - August 17th, 2003

Permission is hereby granted, free of charge, to any person or organization
obtaining a copy of the software and accompanying documentation covered by
this license (the "Software") to use, reproduce, display, distribute,
execute, and transmit the Software, and to prepare derivative works of the
Software, and to permit third-parties to whom the Software is furnished to
do so, all subject to the following:

The copyright notices in the Software and this entire statement, including
the above license grant, this restriction and the following disclaimer,
must be included in all copies of the Software, in whole or in part, and
all derivative works of the Software, unless such copies or derivative
works are solely in the form of machine-executable object code generated by
a source language processor.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
+----------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
Function-templates for discrete Datatypes like int, unsigned or
    any class that provides a ++ operator c.f. iterators
-----------------------------------------------------------------------------*/

#ifndef __itl_gregorian_date_JOFA_080416_H__
#define __itl_gregorian_date_JOFA_080416_H__

#include <stdio.h>
#include <string>
#include <sstream>

#include <boost/date_time/gregorian/gregorian.hpp>

//JODO URG Produce a better compietime error here. 
//JODO (Write Macro to reduce codereplication. Generate line info.) not needed if compile-time error is nifty.
//JODO Make it complete for all date_time classes. check portability.
#ifdef ITL_NEUTRONS_PROVIDED
#pragma message("error: No neutral element provided for type boost::gregorian::date")
#pragma message(".. please #include <boost/itl/itl_gregorian.hpp> PRIOR TO other itl/* classes")
"JODO: Compiletime error has to be produced, but in a nicer way."
#endif

#ifdef ITL_DIFFERENCE_TYPES_PROVIDED
#pragma message("error: No difference type provided for type boost::gregorian::date")
#pragma message(".. please #include <boost/itl/itl_gregorian.hpp> PRIOR TO other itl/* classes")
#endif

#ifdef ITL_SIZE_TYPES_PROVIDED
#pragma message("error: No size type provided for type boost::gregorian::date")
#pragma message(".. please #include <boost/itl/itl_gregorian.hpp> PRIOR TO other itl/* classes")
#endif

#define ITL_NEEDS_GREGORIAN_DATE_NEUTRON_VALUE
#define ITL_NEEDS_GREGORIAN_DATE_DIFFERENCE_TYPE
#define ITL_NEEDS_GREGORIAN_DATE_SIZE_TYPE

namespace boost{namespace itl
{

    boost::gregorian::date operator ++(boost::gregorian::date& x)
    {
        return x += boost::gregorian::date::duration_type::unit();
    }

    boost::gregorian::date operator --(boost::gregorian::date& x)
    {
        return x -= boost::gregorian::date::duration_type::unit();
    }

    // ------------------------------------------------------------------------
    boost::gregorian::date_duration operator ++(boost::gregorian::date_duration& x)
    {
        return x += boost::gregorian::date::duration_type::unit();
    }

    boost::gregorian::date_duration operator --(boost::gregorian::date_duration& x)
    {
        return x -= boost::gregorian::date::duration_type::unit();
    }

    // ------------------------------------------------------------------------

    //JODO testing of boost gregorian fails 
    // boost::date_time::date_duration<duration_rep_traits> lacks op <<
    //
    //template<class CharType, class CharTraits, class duration_rep_traits>
    //std::basic_ostream<CharType, CharTraits>& operator <<
    //(std::basic_ostream<CharType, CharTraits> &stream, 
    // boost::date_time::date_duration<duration_rep_traits> const& x)
    //{
    //    return stream << "[date_duration<duration_rep_traits>]";
    //}

    //boost::date_time::date_duration<duration_rep_traits>

}} // namespace itl boost

#endif


