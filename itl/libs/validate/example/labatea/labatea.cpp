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
#include <validate/loki_xt/Tuple.h>
#include <itl/itl_set.hpp>
#include <itl/itl_map.hpp>
#include <validate/lawvalidater.h>
#include <validate/laws/monoid.h>
#include <validate/gentor/gentorprofile.h>
#include <validate/gentor/rangegentor.h>
#include <validate/realmvalidater.h>
#include <itl/interval_set.hpp>
#include <itl_xt/numbergentor.hpp>
#include <itl_xt/setgentor.hpp>
#include <itl/functors.hpp>

using namespace std;
using namespace Loki;
using namespace boost::itl;


void test_Validater()
{
    //GentorProfileSgl::it()->set_range_int(-10, 10);
    //GentorProfileSgl::it()->set_range_double(-10.0, 10.0);
    //GentorProfileSgl::it()->set_range_ContainerSize(0, 20);
    //GentorProfileSgl::it()->set_range_interval_int(-20, 20);
    //GentorProfileSgl::it()->set_maxIntervalLength(5);


    //typedef BinaryPushout<itl::split_interval_map<int,double>, itl::map<int,double>, Interval::Atomize, inplace_plus>
    //    Map_Atomize_Union_DiagramT;
    //LawValidater<Map_Atomize_Union_DiagramT, RandomGentor> map_atomize_plus_pushout;
    //map_atomize_plus_pushout.setTrialsCount(1000);
    //map_atomize_plus_pushout.run();

    //typedef BinaryPushout<itl::map<int,double>, itl::split_interval_map<int,double>, Interval::Cluster, inplace_star>
    //    Map_Cluster_Intersect_DiagramT;
    //LawValidater<Map_Cluster_Intersect_DiagramT, RandomGentor> map_cluster_star_pushout;
    //map_cluster_star_pushout.setTrialsCount(1000);
    //map_cluster_star_pushout.run();
}

/*CL
interval_map<int, interval_set<int> > itv_map_of_intsets()
{
    itl::interval_set<int> soi_AB; 
    soi_AB.insert(1);
    soi_AB.insert(2);
    soi_AB.insert(3);
    soi_AB.insert(4);
    itl::interval_set<int> soi_BC(soi_AB);
    soi_BC.erase(1);
    soi_BC.insert(5);

    interval_map<int, itl::interval_set<int> > mois;
    mois += make_pair(rightopen_interval(0, 20), soi_AB);
    mois *= make_pair(rightopen_interval(1, 11), soi_BC);
    mois *= closed_interval(2, 9);

    return mois;
}

split_interval_map<int, itl::interval_set<int> > spitv_map_of_intsets()
{
    itl::interval_set<int> soi_AB; 
    soi_AB += 2;
    soi_AB.insert(3);
    soi_AB.insert(4);
    soi_AB.insert(5);
    itl::interval_set<int> soi_BC(soi_AB);
    soi_BC.subtract(2);
    soi_BC.insert(6);

    split_interval_map<int, itl::interval_set<int> > mois;
    mois += make_pair(rightopen_interval(0, 20), soi_AB);
    mois *= make_pair(rightopen_interval(1, 15), soi_BC);
    mois *= closed_interval(3, 11);

    return mois;
}

void test_intersect()
{
    split_interval_map<int, itl::interval_set<int> > spim;
    spim = spitv_map_of_intsets();
    spim *= itv_map_of_intsets();
    cout << spim.as_string() << endl;

    interval_map<int, itl::interval_set<int> > im;
    im = itv_map_of_intsets();
    im *= spitv_map_of_intsets();
    cout << im.as_string() << endl;
}
*/

void test_realmvalidater()
{
    RealmValidater validater;
    cout << 
    ">> ------------------------------------------------------ <<\n"
    ">> -------- Law based test automaton 'LaBatea' ---------- <<\n"
    ">> Output will be generated in a few seconds\n"
    ">> terminate by typing <CTRL>C\n"
    ">> ------------------------------------------------------ <<\n";
    validater.validate();
};


int main()
{
    //test_Validater();
    test_realmvalidater();
    return 0;
}
