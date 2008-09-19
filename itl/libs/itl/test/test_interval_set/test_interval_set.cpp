/*----------------------------------------------------------------------------+
Copyright (c) 2008-2008: Joachim Faulhaber
+-----------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+----------------------------------------------------------------------------*/
#define BOOST_TEST_MODULE itl::interval_set unit test
#include <string>
#include <boost/mpl/list.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/test/test_case_template.hpp>

// interval instance types
#include "../test_type_lists.hpp"
#include "../test_value_maker.hpp"

#include <itl/interval_set.hpp>

using namespace std;
using namespace boost;
using namespace unit_test;
using namespace itl;

// -----------------------------------------------------------------------------
// test_interval_set_shared are tests that should give identical results for all
// interval_sets: interval_set, separate_interval_set and split_interval_set.
#include "test_interval_set_shared.hpp"
// Due to limited expressiveness of the testing framework, the testcode in files
// test_interval_set{,_separate,split}_shared.hpp are generated though code
// replication.

/*
// Most general, largest set of types
BOOST_AUTO_TEST_CASE_TEMPLATE(test_itl_interval_set_ctor_4_ordered_types, T, ordered_types)
{
	// ordered types is the largest set of instance types.
	// Because we can not generate values via incrementation for e.g. string,
	// we are able to test operations only for the most basic values
	// neutron (0, empty, T() ...) and unon.

	//T v0 = itl::neutron<T>(); //JODO check operator() variant
	//T v1 = itl::unon<T>();
	T v0 = itl::neutron<T>::value();
	T v1 = itl::unon<T>::value();
	interval<T> I0_0I(v0);
	interval<T> I1_1I(v1);
	interval<T> I0_1I(v0,v1);

	//-------------------------------------------------------------------------
	//empty set
	BOOST_CHECK_EQUAL(interval_set<T>().empty(), true);
	BOOST_CHECK_EQUAL(interval_set<T>().cardinality(), itl::neutron<itl::size<T>::type>::value());
	BOOST_CHECK_EQUAL(interval_set<T>().size(), itl::neutron<itl::size<T>::type>::value());
	BOOST_CHECK_EQUAL(interval_set<T>(), interval_set<T>());

	interval<T> mt_interval = neutron<interval<T> >::value();
	BOOST_CHECK_EQUAL(mt_interval, interval<T>());
	interval_set<T> mt_set = neutron<interval_set<T> >::value();
	BOOST_CHECK_EQUAL(mt_set, interval_set<T>());

	//adding emptieness to emptieness yields emptieness ;)
	mt_set.add(mt_interval).add(mt_interval);
	BOOST_CHECK_EQUAL(mt_set, interval_set<T>());
	(mt_set += mt_interval) += mt_interval;
	BOOST_CHECK_EQUAL(mt_set, interval_set<T>());

	//subtracting emptieness
	mt_set.subtract(mt_interval).subtract(mt_interval);
	BOOST_CHECK_EQUAL(mt_set, interval_set<T>());
	(mt_set -= mt_interval) -= mt_interval;
	BOOST_CHECK_EQUAL(mt_set, interval_set<T>());

	//subtracting elements form emptieness
	mt_set.subtract(v0).subtract(v1);
	BOOST_CHECK_EQUAL(mt_set, interval_set<T>());
	(mt_set -= v1) -= v0;
	BOOST_CHECK_EQUAL(mt_set, interval_set<T>());

	//subtracting intervals form emptieness
	mt_set.subtract(I0_1I).subtract(I1_1I);
	BOOST_CHECK_EQUAL(mt_set, interval_set<T>());
	(mt_set -= I1_1I) -= I0_1I;
	BOOST_CHECK_EQUAL(mt_set, interval_set<T>());

	//insecting emptieness
	//mt_set.insect(mt_interval).insect(mt_interval);
	//BOOST_CHECK_EQUAL(mt_set, interval_set<T>());
	(mt_set *= mt_interval) *= mt_interval;
	BOOST_CHECK_EQUAL(mt_set, interval_set<T>());
	//insecting emptieness with elements
	(mt_set *= v1) *= v0;
	BOOST_CHECK_EQUAL(mt_set, interval_set<T>());
	//insecting emptieness with intervals
	(mt_set *= I1_1I) *= I0_1I;
	BOOST_CHECK_EQUAL(mt_set, interval_set<T>());

	//-------------------------------------------------------------------------
	//unary set

	interval_set<T> single_I0_0I_from_element(v0);
	interval_set<T> single_I0_0I_from_interval(I0_0I);
	interval_set<T> single_I0_0I(single_I0_0I_from_interval);

	BOOST_CHECK_EQUAL(single_I0_0I_from_element, single_I0_0I_from_interval);
	BOOST_CHECK_EQUAL(single_I0_0I_from_element, single_I0_0I);

	interval_set<T> single_I1_1I_from_element(v1);
	interval_set<T> single_I1_1I_from_interval(I1_1I);
	interval_set<T> single_I1_1I(single_I1_1I_from_interval);

	BOOST_CHECK_EQUAL(single_I1_1I_from_element, single_I1_1I_from_interval);
	BOOST_CHECK_EQUAL(single_I1_1I_from_element, single_I1_1I);

	interval_set<T> single_I0_1I_from_interval(I0_1I);
	interval_set<T> single_I0_1I(single_I0_1I_from_interval);

	BOOST_CHECK_EQUAL(single_I0_1I_from_interval, single_I0_1I);

	//contains predicate
	BOOST_CHECK_EQUAL(single_I0_0I.contains(v0), true);
	BOOST_CHECK_EQUAL(single_I0_0I.contains(I0_0I), true);
	BOOST_CHECK_EQUAL(single_I1_1I.contains(v1), true);
	BOOST_CHECK_EQUAL(single_I1_1I.contains(I1_1I), true);

	BOOST_CHECK_EQUAL(single_I0_1I.contains(v0), true);
	BOOST_CHECK_EQUAL(single_I0_1I.contains(I0_1I), true);
	BOOST_CHECK_EQUAL(single_I0_1I.contains(v1), true);
	BOOST_CHECK_EQUAL(single_I0_1I.contains(I1_1I), true);
	BOOST_CHECK_EQUAL(single_I0_1I.contains(single_I0_0I), true);
	BOOST_CHECK_EQUAL(single_I0_1I.contains(single_I1_1I), true);
	BOOST_CHECK_EQUAL(single_I0_1I.contains(single_I0_1I), true);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(test_itl_interval_set_ctor_4_bicremental_types, T, bicremental_types)
{
	T v4 = make<T>(4);
	itl::interval<T> I4_4I(v4);

	interval_set<T> _I4_4I;
	BOOST_CHECK_EQUAL( _I4_4I.empty(), true );
	interval_set<T> _I4_4I_1;
	interval_set<T> _I4_4I_2;
	interval_set<T> _I4_4I_3;
	_I4_4I   += v4;
	_I4_4I_1 += I4_4I;
	BOOST_CHECK_EQUAL( _I4_4I,                    _I4_4I_1 );
	_I4_4I_2.add(v4);
	BOOST_CHECK_EQUAL( _I4_4I,                    _I4_4I_2 );
	_I4_4I_3.add(I4_4I);
	BOOST_CHECK_EQUAL( _I4_4I,                    _I4_4I_3 );
	_I4_4I_1.add(v4).add(I4_4I);
	BOOST_CHECK_EQUAL( _I4_4I,                    _I4_4I_1 );
	(_I4_4I_1 += v4) += I4_4I;
	BOOST_CHECK_EQUAL( _I4_4I,                    _I4_4I_1 );
	
	BOOST_CHECK_EQUAL( _I4_4I.cardinality(),      unon<interval_set<T>::size_type>::value()  );
	BOOST_CHECK_EQUAL( _I4_4I.size(),             unon<interval_set<T>::size_type>::value()  );
	BOOST_CHECK_EQUAL( _I4_4I.interval_count(),   1  );
	BOOST_CHECK_EQUAL( _I4_4I.iterative_size(),   1  );
	BOOST_CHECK_EQUAL( _I4_4I.lower(),            v4 );
	BOOST_CHECK_EQUAL( _I4_4I.upper(),            v4 );

	interval_set<T> _I4_4I_copy(_I4_4I);
	interval_set<T> _I4_4I_assigned;
	_I4_4I_assigned = _I4_4I;
	BOOST_CHECK_EQUAL( _I4_4I, _I4_4I_copy );
	BOOST_CHECK_EQUAL( _I4_4I, _I4_4I_assigned );
	_I4_4I_assigned.clear();
	BOOST_CHECK_EQUAL( true,   _I4_4I_assigned.empty() );

	_I4_4I_assigned.swap(_I4_4I_copy);
	BOOST_CHECK_EQUAL( true,   _I4_4I_copy.empty() );
	BOOST_CHECK_EQUAL( _I4_4I, _I4_4I_assigned );

}


BOOST_AUTO_TEST_CASE_TEMPLATE(test_itl_interval_set_distinct_4_bicremental_types, T, bicremental_types)
{
	typedef typename interval_set<T>::size_type       size_T;
	typedef typename interval_set<T>::difference_type diff_T;
	T v1 = make<T>(1);
	T v3 = make<T>(3);
	T v5 = make<T>(5);

	size_T s3 = make<size_T>(3);
	diff_T d0 = make<diff_T>(0);

	interval_set<T> is_1_3_5;
	is_1_3_5.add(v1).add(v3).add(v5);

	BOOST_CHECK_EQUAL( is_1_3_5.cardinality(),      s3 );
	BOOST_CHECK_EQUAL( is_1_3_5.size(),             s3 );
	BOOST_CHECK_EQUAL( is_1_3_5.interval_count(),   3 );
	BOOST_CHECK_EQUAL( is_1_3_5.iterative_size(),   3 );
}


BOOST_AUTO_TEST_CASE_TEMPLATE(test_itl_interval_set_distinct_4_bicremental_continuous_types, T, bicremental_continuous_types)
{
	typedef typename interval_set<T>::size_type       size_T;
	typedef typename interval_set<T>::difference_type diff_T;
	T v1 = make<T>(1);
	T v2 = make<T>(2);
	T v3 = make<T>(3);
	T v5 = make<T>(5);

	size_T s3 = make<size_T>(3);
	diff_T d0 = make<diff_T>(0);
	diff_T d2 = make<diff_T>(2);
	diff_T d3 = make<diff_T>(3);

	interval_set<T> is_1_3_5;
	is_1_3_5.add(v1).add(v3).add(v5);

	BOOST_CHECK_EQUAL( is_1_3_5.cardinality(),      s3 );
	BOOST_CHECK_EQUAL( is_1_3_5.size(),             s3 );
	BOOST_CHECK_EQUAL( is_1_3_5.length(),           d0 );
	BOOST_CHECK_EQUAL( is_1_3_5.interval_count(),   3 );
	BOOST_CHECK_EQUAL( is_1_3_5.iterative_size(),   3 );

	size_T s4 = make<size_T>(4);
	diff_T d4 = make<diff_T>(4);

	interval_set<T> is_123_5;
	is_123_5 = is_1_3_5;
	is_123_5 += open_interval<T>(v1,v3);

	BOOST_CHECK_EQUAL( is_123_5.cardinality(),      std::numeric_limits<size_T>::infinity() );
	BOOST_CHECK_EQUAL( is_123_5.size(),             std::numeric_limits<size_T>::infinity() );
	BOOST_CHECK_EQUAL( is_123_5.length(),           d2 );
	BOOST_CHECK_EQUAL( is_123_5.interval_count(),   2 );
	BOOST_CHECK_EQUAL( is_123_5.iterative_size(),   2 );
}

BOOST_AUTO_TEST_CASE_TEMPLATE(test_itl_interval_set_isolate_4_bicremental_continuous_types, T, bicremental_continuous_types)
{
	typedef typename interval_set<T>::size_type       size_T;
	typedef typename interval_set<T>::difference_type diff_T;

	T v0 = make<T>(0);
	T v2 = make<T>(2);
	T v4 = make<T>(4);
	interval<T> I0_4I = closed_interval(v0,v4);
	interval<T> C0_2D = open_interval(v0,v2);
	interval<T> C2_4D = open_interval(v2,v4);
	//   {[0               4]}
	// - {   (0,2)   (2,4)   }
	// = {[0]     [2]     [4]}
	interval_set<T> iso_set = interval_set<T>(I0_4I);
	interval_set<T> gap_set;
	gap_set.add(C0_2D).add(C2_4D);
	iso_set -= gap_set;
	
	BOOST_CHECK_EQUAL( iso_set.cardinality(), static_cast<size_T>(3) );
	BOOST_CHECK_EQUAL( iso_set.iterative_size(), static_cast<std::size_t>(3) );

	interval_set<T> iso_set2;
	iso_set2.add(I0_4I);
	iso_set2.subtract(C0_2D).subtract(C2_4D);
	
	interval_set<T> iso_set3(I0_4I);
	(iso_set3 -= C0_2D) -= C2_4D;

	BOOST_CHECK_EQUAL( iso_set, iso_set2 );
	BOOST_CHECK_EQUAL( iso_set, iso_set3 );
}

BOOST_AUTO_TEST_CASE_TEMPLATE(test_itl_interval_set_contains_4_bicremental_types, T, bicremental_types)
{
	//LAW: x.add(e).contains(e);
	//LAW: z = x + y => z.contains(x) && z.contains(y);
	T v1 = make<T>(1);
	T v3 = make<T>(3);
	T v5 = make<T>(5);
	T v7 = make<T>(7);
	T v8 = make<T>(8);
	T v9 = make<T>(9);
	T v11 = make<T>(11);
	interval_set<T> is(v1);	
	BOOST_CHECK_EQUAL( is.contains(v1), true );

	BOOST_CHECK_EQUAL( interval_set<T>().add(make<T>(2)).contains(make<T>(2)), true );
	BOOST_CHECK_EQUAL( (is += interval<T>(v3,v7)).contains(interval<T>(v3,v7)), true );

	interval_set<T> is2(closed_interval(v5,v8));
	is2.add(v9).add(v11);
	is += is2;
	BOOST_CHECK_EQUAL( is.contains(is2), true );	
}

BOOST_AUTO_TEST_CASE_TEMPLATE(test_itl_interval_set_operators_4_bicremental_types, T, bicremental_types)
{
	T v0 = make<T>(0);
	T v1 = make<T>(1);
	T v3 = make<T>(3);
	T v5 = make<T>(5);
	T v7 = make<T>(7);
	T v8 = make<T>(8);
	itl::interval_set<T> left, left2, right, all, all2, section, complement, naught;
	left.add(closed_interval(v0,v1)).add(closed_interval(v3,v5));
	(right += closed_interval(v3,v5)) += closed_interval(v7,v8);

	BOOST_CHECK_EQUAL( left.disjoint_to(right), false );

	(all += left) += right;
	(section += left) *= right;
	(complement += all) -= section;
	(all2 += section) += complement; 

	BOOST_CHECK_EQUAL( section.disjoint_to(complement), true );
	BOOST_CHECK_EQUAL( all, all2 );

	BOOST_CHECK_EQUAL( all.contains(left), true );
	BOOST_CHECK_EQUAL( all.contains(right), true );
	BOOST_CHECK_EQUAL( all.contains(complement), true );
	BOOST_CHECK_EQUAL( left.contains(section), true );
	BOOST_CHECK_EQUAL( right.contains(section), true );

	BOOST_CHECK_EQUAL( left.contained_in(all), true );
	BOOST_CHECK_EQUAL( right.contained_in(all), true );
	BOOST_CHECK_EQUAL( complement.contained_in(all), true );
	BOOST_CHECK_EQUAL( section.contained_in(left), true );
	BOOST_CHECK_EQUAL( section.contained_in(right), true );
}
*/
