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

#ifndef __itl_date_time_adapter_JOFA_080416_H__
#define __itl_date_time_adapter_JOFA_080416_H__

#include <stdio.h>
#include <string>
#include <sstream>

#include <boost/date_time/gregorian/greg_date.hpp>

namespace itl
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
	template<> 
	inline boost::gregorian::date type<boost::gregorian::date>::neutron()
	{ 
		return boost::gregorian::date(boost::gregorian::min_date_time); 
	}

} // namespace itl

#endif


