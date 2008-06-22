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

/** Example man_power.cpp \file man_power.cpp

	Interval sets and maps can be filled and manipulated using
	set style operation like union +=, difference -= and intersection
	*=.

	In this example man_power a number of those operations are
	demonstrated in the process of calculation the available working 
	times (man-power) of it's employees accounting for weekends,
	holidays, sickness times and vacations.

    \include party/man_power.cpp
*/



// This function splits a gregorian::date interval 'scope' into a week grid:
// For every week contained in 'scope' that month is contained as interval
// in the resulting split_interval_set.

// Function weekends return the interval_set of weekends that are contained in
// the date interval 'scope'
interval_set<date> weekends(const interval<date>& scope)
{
	interval_set<date> weekends;

	date cur_weekend_sat 
		= scope.first() 
		  + days(days_until_weekday(scope.first(), greg_weekday(Saturday))) 
		  - weeks(1);
	week_iterator week_iter(cur_weekend_sat);

	for(; week_iter <= scope.last(); ++week_iter)
		weekends.insert(rightopen_interval(*week_iter, *week_iter + days(2)));

	weekends *= scope; // cut off the surplus

	return weekends;
}


// For a period of two months, starting from today, the function
// computes a partitioning for months and weeks using intersection
// operator *= on split_interval_sets.

// The avalable working time for the employees of a company is calculated
// for a period of 3 months accounting for weekends and holidays.
//    The available daily working time for the employees is calculated
// using interval_sets and split_interval_maps demonstrating a number of
// addition, subtraction and intersection operations.
void man_power()
{
	date someday = from_string("2008-08-01");
	date thenday = someday + months(3);

	interval<date> scope = rightopen_interval(someday, thenday);

	// ------------------------------------------------------------------------
	// (1) In a first step, the regular working times are computed for the
	// company within the given scope. From all available days, the weekends
	// and holidays have to be subtracted: 
	interval_set<date> worktime(scope);
	// Subtract the weekends
	worktime -= weekends(scope);
	// Subtract holidays
	worktime -= from_string("2008-10-03"); //german reunification ;)

	// company holidays (fictitious ;)
	worktime -= closed_interval(from_string("2008-08-18"), 
	                            from_string("2008-08-22"));

	//-------------------------------------------------------------------------
	// (2) Now we calculate the individual worktimes for some employees
	//-------------------------------------------------------------------------
	// In the company works Claudia. 
	// This is the map of her regular working times:
	split_interval_map<date,int> claudias_working_hours;

	// Claudia is working 8 hours a day. So the next statement says
	// that every day in the whole scope is mapped to 8 hours worktime.
	claudias_working_hours += make_pair(scope, 8);

	// But Claudia only works 8 hours on regular working days so we do
	// an intersection of the interval_map with the interval_set worktime:
	claudias_working_hours *= worktime;

	// Yet, in addition Claudia has her own absence times like
	interval<date> claudias_seminar (from_string("2008-09-16"), 
                                     from_string("2008-09-24"));
	interval<date> claudias_vacation(from_string("2008-08-01"), 
		                             from_string("2008-08-14"));

	interval_set<date> claudias_absence_times(claudias_seminar);
	claudias_absence_times += claudias_vacation;

	// All the absencetimes have to subtracted from the map of her working times
	claudias_working_hours -= claudias_absence_times;

	//-------------------------------------------------------------------------
	// Claudia's boss is Bodo. He only works part time. 
	// This is the map of his regular working times:
	split_interval_map<date,int> bodos_working_hours;

	// Bodo is working 4 hours a day.
	bodos_working_hours += make_pair(scope, 4);

	// Bodo works only on regular working days
	bodos_working_hours *= worktime;

	// Bodos additional absence times
	interval<date> bodos_flu(from_string("2008-09-19"), from_string("2008-09-29"));
	interval<date> bodos_vacation(from_string("2008-08-15"), from_string("2008-09-03"));

	interval_set<date> bodos_absence_times(bodos_flu);
	bodos_absence_times += bodos_vacation;

	// All the absencetimes have to subtracted from the map of his working times
	bodos_working_hours -= bodos_absence_times;

	//-------------------------------------------------------------------------
	// (3) Finally we want to calculate the available manpower of the company
	// for the selected time scope: This is done by adding up the employees
	// working time maps:
	split_interval_map<date,int> manpower;
	manpower += claudias_working_hours;
	manpower += bodos_working_hours;


	cout << scope.first() << " - " << scope.last() 
	     << "    available man-power:" << endl;
    cout << "---------------------------------------------------------------\n";

	for(split_interval_map<date,int>::iterator it = manpower.begin(); 
		it != manpower.end(); it++)
	{
		cout << it->first.first() << " - " << it->first.last() 
			 << " -> " << it->second << endl;
	}
}

int main()
{
    cout << ">> Interval Template Library: Sample man_power.cpp <<\n";
    cout << "---------------------------------------------------------------\n";
    man_power();
    return 0;
}

// Program output:
/*
>> Interval Template Library: Sample man_power.cpp <<
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