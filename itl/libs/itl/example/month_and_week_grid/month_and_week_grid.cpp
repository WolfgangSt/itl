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

// The next line includes <boost/gregorian/date.hpp>
// and a few lines of adapter code.
#include <boost/itl/gregorian.hpp> 

#include <boost/itl/type_traits/to_string.hpp>
#include <boost/itl/split_interval_map.hpp>

using namespace std;
using namespace boost::gregorian;
using namespace boost::itl;

/** Example month_and_week_grid.cpp \file month_and_week_grid.cpp

    As split_interval_set preserves all interval borders on insertion
    and intersection operations. So given a split_interval_set
    \code
    x =  {[1,     3)}
    x.add(     [2,     4)) then
    x == {[1,2)[2,3)[3,4)}
    \endcode
    Using this property we can intersect split_interval_maps in
    order to iterate over intervals accounting for all occurring
    changes of interval borders.

    In this example we provide an intersection of two split_interval_sets
    representing a month and week time grid. 

    \include month_and_week_grid/month_and_week_grid.cpp
*/

typedef split_interval_set<boost::gregorian::date> date_grid;

// This function splits a gregorian::date interval 'scope' into a month grid:
// For every month contained in 'scope' that month is contained as interval
// in the resulting split_interval_set.
date_grid month_grid(const interval<date>& scope)
{
    split_interval_set<date> month_grid;

    date frame_months_1st = scope.first().end_of_month() + days(1) - months(1);
    month_iterator month_iter(frame_months_1st);

    for(; month_iter <= scope.last(); ++month_iter)
        month_grid += rightopen_interval(*month_iter, *month_iter + months(1));

    month_grid *= scope; // cut off the surplus

    return month_grid;
}

// This function splits a gregorian::date interval 'scope' into a week grid:
// For every week contained in 'scope' that month is contained as interval
// in the resulting split_interval_set.
date_grid week_grid(const interval<date>& scope)
{
    split_interval_set<date> week_grid;

    date frame_weeks_1st = scope.first() + days(days_until_weekday(scope.first(), greg_weekday(Monday))) - weeks(1);
    week_iterator week_iter(frame_weeks_1st);

    for(; week_iter <= scope.last(); ++week_iter)
        week_grid.insert(rightopen_interval(*week_iter, *week_iter + weeks(1)));

    week_grid *= scope; // cut off the surplus

    return week_grid;
}

// For a period of two months, starting from today, the function
// computes a partitioning for months and weeks using intersection
// operator *= on split_interval_sets.
void month_and_time_grid()
{
    date someday = day_clock::local_day();
    date thenday = someday + months(2);

    interval<date> itv = rightopen_interval(someday, thenday);

    // Compute a month grid
    date_grid month_and_week_grid = month_grid(itv);
    // Intersection of the month and week grids:
    month_and_week_grid *= week_grid(itv);

    cout << "interval : " << itv.first() << " - " << itv.last() 
         << " month and week partitions:" << endl;
    cout << "---------------------------------------------------------------\n";

    for(date_grid::iterator it = month_and_week_grid.begin(); 
        it != month_and_week_grid.end(); it++)
    {
        if(it->first().day() == 1)
            cout << "new month: ";
        else if(it->first().day_of_week()==greg_weekday(Monday))
            cout << "new week : " ;
        else if(it == month_and_week_grid.begin())
            cout << "first day: " ;
        cout << it->first() << " - " << it->last() << endl;
    }
}


int main()
{
    cout << ">> Interval Template Library: Sample month_and_time_grid.cpp <<\n";
    cout << "---------------------------------------------------------------\n";
    month_and_time_grid();
    return 0;
}

// Program output:
/*
>> Interval Template Library: Sample month_and_time_grid.cpp <<
---------------------------------------------------------------
interval : 2008-Jun-22 - 2008-Aug-21 month and week partitions:
---------------------------------------------------------------
first day: 2008-Jun-22 - 2008-Jun-22
new week : 2008-Jun-23 - 2008-Jun-29
new week : 2008-Jun-30 - 2008-Jun-30
new month: 2008-Jul-01 - 2008-Jul-06
new week : 2008-Jul-07 - 2008-Jul-13
new week : 2008-Jul-14 - 2008-Jul-20
new week : 2008-Jul-21 - 2008-Jul-27
new week : 2008-Jul-28 - 2008-Jul-31
new month: 2008-Aug-01 - 2008-Aug-03
new week : 2008-Aug-04 - 2008-Aug-10
new week : 2008-Aug-11 - 2008-Aug-17
new week : 2008-Aug-18 - 2008-Aug-21
*/
