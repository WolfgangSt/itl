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
#include <itl/separate_interval_set.hpp>
#include <itl/split_interval_set.hpp>

using namespace std;
using namespace boost;
using namespace unit_test;
using namespace itl;


BOOST_AUTO_TEST_CASE_TEMPLATE(test_itl_interval_set_mixed_ctor_4_ordered_types, T, ordered_types)
{         
	T v0 = neutron<T>::value();
	T v1 = unon<T>::value();

	split_interval_set<T>    split_set(v0);
	separate_interval_set<T> sep_set(split_set);
	interval_set<T>          join_set(sep_set);

	BOOST_CHECK_EQUAL( split_set.lower(), sep_set.lower() );
	BOOST_CHECK_EQUAL( split_set.lower(), join_set.lower() );
}

BOOST_AUTO_TEST_CASE_TEMPLATE(test_itl_interval_set_mixed_assign_4_ordered_types, T, ordered_types)
{         
	T v0 = neutron<T>::value();
	T v1 = unon<T>::value();

	split_interval_set<T>    split_set;
	separate_interval_set<T> sep_set;
	interval_set<T>          join_set;
	split_set.add(v0);
	sep_set = split_set;
	join_set = sep_set;

	BOOST_CHECK_EQUAL( split_set.lower(), sep_set.lower() );
	BOOST_CHECK_EQUAL( split_set.lower(), join_set.lower() );
}

BOOST_AUTO_TEST_CASE_TEMPLATE(test_itl_interval_set_mixed_ctor_4_bicremental_types, T, bicremental_types)
{         
	T v0 = make<T>(0);
	T v1 = make<T>(1);
	T v2 = make<T>(2);
	T v3 = make<T>(3);
	T v4 = make<T>(4);
	T v5 = make<T>(5);

	interval<T> I1_3D = rightopen_interval(v1,v3);
	interval<T> I2_4D = rightopen_interval(v2,v4);
	interval<T> I4_5D = rightopen_interval(v4,v5);

	split_interval_set<T> split_set;
	split_set.add(I1_3D).add(I2_4D).add(I4_5D);
	BOOST_CHECK_EQUAL( split_set.iterative_size(), 4 );
	separate_interval_set<T> sep_set(split_set);
	BOOST_CHECK_EQUAL( sep_set.iterative_size(), 4 );
	interval_set<T> join_set(split_set);
	BOOST_CHECK_EQUAL( join_set.iterative_size(), 1 );

	separate_interval_set<T> sep_set2;
	sep_set2.add(I1_3D).add(I2_4D).add(I4_5D);
	BOOST_CHECK_EQUAL( sep_set2.iterative_size(), 2 );
	split_interval_set<T> split_set2(sep_set2);
	BOOST_CHECK_EQUAL( split_set2.iterative_size(), 2 );
	interval_set<T> join_set2(sep_set2);
	BOOST_CHECK_EQUAL( join_set2.iterative_size(), 1 );
}


BOOST_AUTO_TEST_CASE_TEMPLATE(test_itl_interval_set_mixed_assign_4_bicremental_types, T, bicremental_types)
{         
	T v0 = make<T>(0);
	T v1 = make<T>(1);
	T v2 = make<T>(2);
	T v3 = make<T>(3);
	T v4 = make<T>(4);
	T v5 = make<T>(5);

	interval<T> I1_3D = rightopen_interval(v1,v3);
	interval<T> I2_4D = rightopen_interval(v2,v4);
	interval<T> I4_5D = rightopen_interval(v4,v5);

	split_interval_set<T> split_set;
	split_set.add(I1_3D).add(I2_4D).add(I4_5D);
	BOOST_CHECK_EQUAL( split_set.iterative_size(), 4 );
	separate_interval_set<T> sep_set;
	sep_set = split_set;
	BOOST_CHECK_EQUAL( sep_set.iterative_size(), 4 );
	interval_set<T> join_set;
	join_set = split_set;
	BOOST_CHECK_EQUAL( join_set.iterative_size(), 1 );

	separate_interval_set<T> sep_set2;
	sep_set2.add(I1_3D).add(I2_4D).add(I4_5D);
	BOOST_CHECK_EQUAL( sep_set2.iterative_size(), 2 );
	split_interval_set<T> split_set2;
	split_set2 = sep_set2;
	BOOST_CHECK_EQUAL( split_set2.iterative_size(), 2 );
	interval_set<T> join_set2;
	join_set2 = sep_set2;
	BOOST_CHECK_EQUAL( join_set2.iterative_size(), 1 );
}


BOOST_AUTO_TEST_CASE_TEMPLATE(test_itl_interval_set_mixed_add_4_bicremental_types, T, bicremental_types)
{         
	T v0 = make<T>(0);
	T v1 = make<T>(1);
	T v2 = make<T>(2);
	T v3 = make<T>(3);
	T v4 = make<T>(4);
	T v5 = make<T>(5);

	interval<T> I1_3D = rightopen_interval(v1,v3);
	interval<T> I2_4D = rightopen_interval(v2,v4);
	interval<T> I4_5D = rightopen_interval(v4,v5);

	split_interval_set<T> split_set;
	split_set.add(I1_3D).add(I2_4D).add(I4_5D);
	BOOST_CHECK_EQUAL( split_set.iterative_size(), 4 );
	separate_interval_set<T> sep_set;
	sep_set += split_set;
	BOOST_CHECK_EQUAL( sep_set.iterative_size(), 4 );
	interval_set<T> join_set;
	join_set += split_set;
	BOOST_CHECK_EQUAL( join_set.iterative_size(), 1 );

	separate_interval_set<T> sep_set2;
	sep_set2.add(I1_3D).add(I2_4D).add(I4_5D);
	BOOST_CHECK_EQUAL( sep_set2.iterative_size(), 2 );
	split_interval_set<T> split_set2;
	split_set2 += sep_set2;
	BOOST_CHECK_EQUAL( split_set2.iterative_size(), 2 );
	interval_set<T> join_set2;
	join_set2 += sep_set2;
	BOOST_CHECK_EQUAL( join_set2.iterative_size(), 1 );

	interval_set<T> join_set3;
	join_set3.add(v1).add(v3).add(v5);
	BOOST_CHECK_EQUAL( join_set3.iterative_size(), 3 );
	split_interval_set<T> split_set3;
	split_set3 += join_set3;
	BOOST_CHECK_EQUAL( split_set3.iterative_size(), 3 );
	separate_interval_set<T> sep_set3;
	sep_set3 += join_set3;
	BOOST_CHECK_EQUAL( join_set3.iterative_size(), 3 );
}

