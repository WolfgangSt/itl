/*----------------------------------------------------------------------------+
A Law Based Test Automaton 'LaBatea'
Author: Joachim Faulhaber
Copyright (c) 2007-2008: Joachim Faulhaber
+-----------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+----------------------------------------------------------------------------*/
#include <iostream>
#include <stdio.h>
#include <lokixt/Tuple.h>
#include <itl/itl_set.hpp>
#include <itl/itl_map.hpp>
#include <validate/lawvalidater.h>
#include <validate/laws/monoid.h>
//#include <validate/laws/pushouts.h>
#include <validate/gentor/gentorprofile.h>
#include <validate/gentor/rangegentor.h>
#include <validate/realmvalidater.h>
#include <itl/interval_set.hpp>
#include <itl/numbergentor.hpp>
#include <itl/setgentor.hpp>
//#include <itl/mapgentor.hpp>
//#include <itl/interval_morphism.hpp>
#include <itl/functors.hpp>

using namespace std;
using namespace Loki;
using namespace itl;


void test_Validater()
{
    GentorProfileSgl::it()->set_range_int(-10, 10);
    GentorProfileSgl::it()->set_range_double(-10.0, 10.0);
    GentorProfileSgl::it()->set_range_ContainerSize(0, 20);
    GentorProfileSgl::it()->set_range_interval_int(-20, 20);
    GentorProfileSgl::it()->set_maxIntervalLength(5);


    typedef BinaryPushout<itl::split_interval_map<int,double>, itl::map<int,double>, Interval::Atomize, inplace_plus>
        Map_Atomize_Union_DiagramT;
    LawValidater<Map_Atomize_Union_DiagramT, RandomGentor> map_atomize_plus_pushout;
    map_atomize_plus_pushout.setTrialsCount(1000);
    map_atomize_plus_pushout.run();

    typedef BinaryPushout<itl::map<int,double>, itl::split_interval_map<int,double>, Interval::Cluster, inplace_star>
        Map_Cluster_Intersect_DiagramT;
    LawValidater<Map_Cluster_Intersect_DiagramT, RandomGentor> map_cluster_star_pushout;
    map_cluster_star_pushout.setTrialsCount(1000);
    map_cluster_star_pushout.run();
}


void test_realmvalidater()
{
    RealmValidater validater;

    cout << 
    ">> ------------------------------------------------------ <<\n"
    ">> -------- Law based test automaton 'LaBatea' ---------- <<\n"
    ">> Output will be generated in a few seconds\n"
    ">> teminate by typing <CTRL>C\n"
    ">> ------------------------------------------------------ <<\n";
	validater.validate();
};


int main()
{
    //test_Validater();
    test_realmvalidater();
    return 0;
}
