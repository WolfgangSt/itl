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

#include <itl/interval_set.hpp>
#include <itl/split_interval_set.hpp>
#include <itl/split_interval_map.hpp>
#include "../toytime.h"

using namespace std;
using namespace itl;

/** Example interval_container.cpp \file interval_container.cpp

    Sample file interval_container.cpp demontrates basic charactersistics of 
    interval container objects.

    Simple interactive shells for the manipulation of interval containers can be found
    in the 'tests.sln' project.

    \include interval_container/interval_container.cpp
*/
void interval_container_basics()
{
    interval<Time> night_and_day = rightopen_interval(Time(monday,   20,00), Time(tuesday,  20,00));
    interval<Time> day_and_night = rightopen_interval(Time(tuesday,   7,00), Time(wednesday, 7,00));
    interval<Time> next_morning  = rightopen_interval(Time(wednesday, 7,00), Time(wednesday,10,00));
    interval<Time> next_evening  = rightopen_interval(Time(wednesday,18,00), Time(wednesday,21,00));

    // An interval set of type interval_set joins intervals that that overlap or touch each other.
    interval_set<Time> joinedTimes;
    joinedTimes.insert(night_and_day);
    joinedTimes.insert(day_and_night);
    joinedTimes.insert(next_morning);
    joinedTimes.insert(next_evening);

    cout << "Joined times:    " << joinedTimes.as_string() << endl;

    // A discrete interval set of type split_interval_set joins intervals that that overlap but it
    // preserves interval borders that just touch each other. You may represent time grids 
    // like the months of a year as a split_interval_set.
    split_interval_set<Time> discreteTimes;
    discreteTimes.insert(night_and_day);
    discreteTimes.insert(day_and_night);
    discreteTimes.insert(next_morning);
    discreteTimes.insert(next_evening);

    cout << "Discrete times: " << discreteTimes.as_string() << endl;

    // A split interval map splits up inserted intervals on overlap and aggregates the
    // associated quantities via the operator +=
    split_interval_map<Time, int> overlapCounter;
    overlapCounter.insert(make_pair(night_and_day, 1));
    overlapCounter.insert(make_pair(day_and_night, 1));
    overlapCounter.insert(make_pair(next_morning, 1));
    overlapCounter.insert(make_pair(next_evening, 1));

    cout << "Split times:    " << overlapCounter.as_string() << endl;
}

int main()
{
    cout << ">> Interval Template Library: Sample interval_container.cpp <<\n";
    cout << "--------------------------------------------------------------\n";
    interval_container_basics();
    return 0;
}


// Program output:

// >> Interval Template Library: Sample interval_container.cpp <<
// --------------------------------------------------------------
// Joined times:   [mon:20:00,wed:10:00)[wed:18:00,wed:21:00)
// Discrete times: [mon:20:00,wed:07:00)[wed:07:00,wed:10:00)[wed:18:00,wed:21:00)
// Split times:    ([mon:20:00,tue:07:00),1)([tue:07:00,tue:20:00),2)([tue:20:00,wed:07:00),1)
//                 ([wed:07:00,wed:10:00),1)([wed:18:00,wed:21:00),1)
