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

// The next line includes <boost/date_time/posix_time/posix_time.hpp>
// and a few lines of adapter code.
#include <itl/itl_ptime.hpp> 

using namespace std;
using namespace boost::posix_time;
using namespace itl;

/** Example boost_party.cpp \file boost_party.cpp

    Party.cpp demonstrates the possibilities of a split interval map (split_interval_map).
	As time parameter boost::posix_time::ptime is used. 
    A split_interval_map maps intervals to a given content. In this case the content 
    is a set of party guests represented by their name strings.

    As time goes by, groups of people join the party and leave later in the evening.
    So we insert a time interval and a name set to the split_interval_map for the attendance
    of each group of people, that come together and leave together.

    On every overlap of intervals, the corresponding name sets are accumulated. At
    the points of overlap the intervals are split. The accumulation of content on
    overlap of intervals is always done via an operator += that has to be implemented
    for the content parameter of the split_interval_map.

    Finally the split_interval_map contains the history of attendance and all points in
    time, where the group of party guests changed.

    Party.cpp demonstrates a principle that we call 
    <b><em>aggregate on overlap (aggovering;)</em></b>:
    On insertion a value associated to the interval is aggrgated (added) to those
    values in the split_interval_map that overlap with the inserted value.

    There are two behavioral aspects to <b>aggovering</b>: a <em>decompositional
    behavior</em> and a <em>accumulative behavior</em>.

    The <em>decompositional behavior</em> splits up intervals on the time dimension of the 
    split_interval_map so that the intervals change whenever associated values
    change.

    The <em>accumulative behavior</em> accumulates associated values on every overlap of
    an insertion for the associated values.

    \include party/boost_party.cpp
*/

// Type itl::set<string> collects the names of party guests. Therefore it needs to
// implement operator += that performs a set union on overlap of intervals.
typedef itl::set<string> GuestSetT;

// boost::posix_time::ptime is the domain type the the split_interval_map. 
// It's key values are therefore time intervals: interval<ptime>. The content
// is the set of names: GuestSetT.
typedef split_interval_map<ptime, GuestSetT> BoostPartyAttendenceHistoryT;


void boost_party()
{
    GuestSetT mary_harry; 
    mary_harry.insert("Mary");
    mary_harry.insert("Harry");

    GuestSetT diana_susan; 
    diana_susan.insert("Diana");
    diana_susan.insert("Susan");

    GuestSetT peter; 
    peter.insert("Peter");

    BoostPartyAttendenceHistoryT party;

	party.insert(
	  make_pair( 
		rightopen_interval<ptime>(
		  time_from_string("2008-05-20 19:30"), 
		  time_from_string("2008-05-20 23:00")), 
		  mary_harry) );
	party.insert(
	  make_pair( 
		rightopen_interval<ptime>(
		  time_from_string("2008-05-20 20:10"), 
		  time_from_string("2008-05-21 00:00")), 
		  diana_susan) );
	party.insert(
	  make_pair( 
		rightopen_interval<ptime>(
		  time_from_string("2008-05-20 22:15"), 
		  time_from_string("2008-05-21 00:30")), 
		  peter) );

    BoostPartyAttendenceHistoryT::iterator it = party.begin();
    while(it != party.end())
    {
        interval<ptime> when = (*it).first;
        // Who is at the party within the time interval 'when' ?
        GuestSetT who = (*it++).second;
        cout << "[" << when.first() << " - " << when.upper_bound() << ")"
			 << ": " << who.as_string() << endl;
    }
}


int main()
{
    cout << ">> Interval Template Library: Sample boost_party.cpp <<\n";
    cout << "-------------------------------------------------------\n";
    boost_party();
    return 0;
}

// Program output:
/*-----------------------------------------------------------------------------
>> Interval Template Library: Sample boost_party.cpp <<
-------------------------------------------------------
[2008-May-20 19:30:00 - 2008-May-20 20:10:00): Harry Mary
[2008-May-20 20:10:00 - 2008-May-20 22:15:00): Diana Harry Mary Susan
[2008-May-20 22:15:00 - 2008-May-20 23:00:00): Diana Harry Mary Peter Susan
[2008-May-20 23:00:00 - 2008-May-21 00:00:00): Diana Peter Susan
[2008-May-21 00:00:00 - 2008-May-21 00:30:00): Peter
Drücken Sie eine beliebige Taste . . .
-----------------------------------------------------------------------------*/
