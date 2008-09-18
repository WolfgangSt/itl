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



// Most general, largest set of types
BOOST_AUTO_TEST_CASE_TEMPLATE(test_itl_interval_set_ctor_4_ordered_types, T, ordered_types)
{
	BOOST_CHECK_EQUAL(interval_set<T>().empty(), true);
	BOOST_CHECK_EQUAL(interval_set<T>().cardinality(), itl::neutron<itl::size<T>::type>::value());
	BOOST_CHECK_EQUAL(interval_set<T>().size(), itl::neutron<itl::size<T>::type>::value());

	BOOST_CHECK_EQUAL(interval_set<T>(), interval_set<T>());
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


BOOST_AUTO_TEST_CASE_TEMPLATE(test_itl_interval_set_ops_4_bicremental_types, T, bicremental_types)
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

	//JODO overloading contains
	//BOOST_CHECK_EQUAL( all.contains(left), true );
	//BOOST_CHECK_EQUAL( all.contains(right), true );
	//BOOST_CHECK_EQUAL( all.contains(complement), true );
	//BOOST_CHECK_EQUAL( complement.contains(left), true );
	//BOOST_CHECK_EQUAL( complement.contains(right), true );
	//BOOST_CHECK_EQUAL( complement.contains(section), false );

	BOOST_CHECK_EQUAL( left.contained_in(all), true );
	BOOST_CHECK_EQUAL( right.contained_in(all), true );
	BOOST_CHECK_EQUAL( complement.contained_in(all), true );

}

