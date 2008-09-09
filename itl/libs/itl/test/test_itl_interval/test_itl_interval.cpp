/*----------------------------------------------------------------------------+
Copyright (c) 2008-2008: Joachim Faulhaber
+-----------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+----------------------------------------------------------------------------*/
#define BOOST_TEST_MODULE itl::interval unit test
#include <string>
#include <boost/mpl/list.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/test/test_case_template.hpp>

#include <itl/itl_interval.hpp>

using namespace std;
using namespace boost;
using namespace unit_test;
using namespace itl;


typedef ::boost::mpl::list<
	unsigned char, unsigned short, unsigned int, unsigned long,  
	char, short, int, long,
	float, double
> decrementable_types;

typedef ::boost::mpl::list<
	unsigned char, unsigned short, unsigned int, unsigned long,  
	char, short, int, long,
	float, double
	//JODO std::string
> interval_instance_types;


BOOST_AUTO_TEST_CASE_TEMPLATE(test_itl_decrementability, T, decrementable_types)
{
	BOOST_CHECK_EQUAL(T(), pred(succ(T())));
	BOOST_CHECK_EQUAL(itl::type<T>::unon(), succ(T()));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(test_itl_interval_constructors, T, interval_instance_types)
{
	// An empty interval is defined as the closed interval [1,0]
	BOOST_CHECK_EQUAL(interval<T>().empty(), true);
	BOOST_CHECK_EQUAL(interval<T>().first(), itl::type<T>::unon());
	BOOST_CHECK_EQUAL(interval<T>().last(), itl::type<T>::neutron());
}

