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


BOOST_AUTO_TEST_CASE_TEMPLATE(test_itl_interval_set_ctor_4_ordered_types, T, ordered_types)
{         
	T v0 = neutron<T>::value();
	T v1 = unon<T>::value();

	split_interval_set<T>    mt_split(v0);
	separate_interval_set<T> mt_sep(mt_split);
	interval_set<T>          mt_join(mt_sep);

	BOOST_CHECK_EQUAL( mt_split.lower(), mt_sep.lower() );
	BOOST_CHECK_EQUAL( mt_split.lower(), mt_join.lower() );
}

BOOST_AUTO_TEST_CASE_TEMPLATE(test_itl_interval_set_ctor_4_bicremental_types, T, bicremental_types)
{         
	T v0 = make<T>(0);

	split_interval_set<T> mt_split;
	separate_interval_set<T> mt_sep(mt_split);

	BOOST_CHECK_EQUAL( v0, v0 );
}

