/*----------------------------------------------------------------------------+
Interval Template Library
Author: Joachim Faulhaber
Copyright (c) 2007-2008: Joachim Faulhaber
Copyright (c) 1999-2006: Cortex Software GmbH, Kantstrasse 57, Berlin
+-----------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+----------------------------------------------------------------------------*/
#include <stdio.h>
#include <iostream>
#include <itl/itl_value.hpp>
#include <itl/string_set.hpp>
#include <itl/split_interval_map.hpp>
#include "../toytime.h"

// The next line includes <boost/gregorian/date.hpp>
// and a few lines of adapter code.
#include <itl/itl_gregorian_date.hpp> 

using namespace std;
using namespace boost::gregorian;
using namespace itl;

/** Example month_and_time_grid.cpp \file month_and_time_grid.cpp


    \include party/month_and_time_grid.cpp
*/

typedef split_interval_set<boost::gregorian::date> date_grid;

date_grid month_grid(const interval<date>& scope)
{
	split_interval_set<date> month_grid;

	date frame_months_1st = scope.first().end_of_month() + days(1) - months(1);
	month_iterator month_iter(frame_months_1st);

	for(; month_iter <= scope.last(); ++month_iter)
		month_grid.insert(rightopen_interval(*month_iter, *month_iter + months(1)));

	month_grid *= scope; // cut off the surplus

	return month_grid;
}

//date_grid week_grid(const interval<date>& scope)
//{
//	split_interval_set<date> week_grid;
//
//	date frame_weeks_1st = scope.first().end_of_week() + days(1) - weeks(1);
//	week_iterator week_iter(frame_weeks_1st);
//
//	for(; week_iter <= scope.last(); ++week_iter)
//		week_grid.insert(rightopen_interval(*week_iter, *week_iter + months(1)));
//
//	month_grid *= scope; // cut off the surplus
//
//	return month_grid;
//}

void month_and_time_grid()
{
	date someday = day_clock::local_day();
	date thenday = someday + months(3);

	interval<date> itv = rightopen_interval(someday, thenday);
	date_grid months = month_grid(itv);

	for(date_grid::iterator it = months.begin(); it != months.end(); it++)
		cout << it->first() << " - " << it->last() << endl;
}

#include <limits>

int main()
{
    cout << ">> Interval Template Library: Sample month_and_time_grid.cpp <<\n";
    cout << "---------------------------------------------------------------\n";
    month_and_time_grid();

	printf("unsigned int min=%u max=%u\n", 
		std::numeric_limits<unsigned int>::min(),
		std::numeric_limits<unsigned int>::max());
	cout << "unsigned int min="<< std::numeric_limits<unsigned int>::min()
		 << "unsigned int max="<< std::numeric_limits<unsigned int>::max() <<endl;

    return 0;
}

// Program output:
/*
>> Interval Template Library: Sample month_and_time_grid.cpp <<
-------------------------------------------------------
[2008-May-20 19:30:00 - 2008-May-20 20:09:59.999999]: Harry Mary
[2008-May-20 20:10:00 - 2008-May-20 22:14:59.999999]: Diana Harry Mary Susan
[2008-May-20 22:15:00 - 2008-May-20 22:59:59.999999]: Diana Harry Mary Peter Sus
an
[2008-May-20 23:00:00 - 2008-May-20 23:59:59.999999]: Diana Peter Susan
[2008-May-21 00:00:00 - 2008-May-21 00:29:59.999999]: Peter
*/
