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


// Most of the tests will be done uniformly for interval_sets:
// interval_set, sepatate_interval_set and split_interval_set.
// So here again is desire for doing test case development especially
// on the level of types like
// for_all(container in test_containers) 
//    for_all(T in instance_types) { test(propery(container<T>)); }
// But I do refrain from going in to new developments here and
// try to keep it very simple:

// passing interval_container via MACRO ... :(
#define INTERVAL_SET interval_set;



// Most general, largest set of types
BOOST_AUTO_TEST_CASE_TEMPLATE(test_itl_interval_ctor_4_ordered_types, T, ordered_types)
{
	//interval_set<T> is;
	BOOST_CHECK_EQUAL(interval_set<T>().empty(), true);
	//BOOST_CHECK_EQUAL(INTERVAL_SET<T>().cardinality(), itl::type<itl::size<T>::type>::neutron());
	//BOOST_CHECK_EQUAL(INTERVAL_SET<T>().lower(), itl::unon<T>::value());
	//BOOST_CHECK_EQUAL(INTERVAL_SET<T>().upper(), itl::neutron<T>::value());

	//BOOST_CHECK_EQUAL(interval<T>(), interval<T>());
	//BOOST_CHECK_EQUAL(interval<T>(), interval<T>(itl::unon<T>::value(), itl::neutron<T>::value()));
	//BOOST_CHECK_EQUAL(interval<T>(), interval<T>(itl::unon<T>::value(), itl::neutron<T>::value(), interval<T>::CLOSED));

}

BOOST_AUTO_TEST_CASE_TEMPLATE(test_itl_ctor_4_bicremental_types, T, bicremental_types)
{
	BOOST_CHECK_EQUAL( T(), pred(succ(T())));
	BOOST_CHECK_EQUAL( itl::neutron<T>::value(), pred(succ(itl::neutron<T>::value()))       );
	BOOST_CHECK_EQUAL( itl::unon<T>::value(),    succ(itl::neutron<T>::value())             );
	BOOST_CHECK_EQUAL( interval<T>().length(),   itl::neutron<difference<T>::type>::value() );

	T v4 = make<T>(4);
	itl::interval<T> i_4_4(v4);
	BOOST_CHECK_EQUAL( i_4_4.is_closed(),         true  );
	BOOST_CHECK_EQUAL( i_4_4.is_leftopen(),       false );
	BOOST_CHECK_EQUAL( i_4_4.is_rightopen(),      false );
	BOOST_CHECK_EQUAL( i_4_4.is_open(),           false );
	BOOST_CHECK_EQUAL( i_4_4.leftbound_closed(),  true  );
	BOOST_CHECK_EQUAL( i_4_4.rightbound_closed(), true  );
	BOOST_CHECK_EQUAL( i_4_4.leftbound_open(),    false );
	BOOST_CHECK_EQUAL( i_4_4.rightbound_open(),   false );

	BOOST_CHECK_EQUAL( i_4_4.lower(),             v4    );
	BOOST_CHECK_EQUAL( i_4_4.upper(),             v4    );

	BOOST_CHECK_EQUAL( i_4_4.contains(v4),        true  );
	BOOST_CHECK_EQUAL( i_4_4.contains(i_4_4),     true  );
	BOOST_CHECK_EQUAL( i_4_4.contained_in(i_4_4), true  );
	BOOST_CHECK_EQUAL( i_4_4,                     i_4_4 );

	BOOST_CHECK_EQUAL( i_4_4.cardinality(),       unon<interval<T>::size_type>::value()          );
	BOOST_CHECK_EQUAL( i_4_4.size(),              unon<interval<T>::size_type>::value()          );
	BOOST_CHECK_EQUAL( i_4_4.length(),            neutron<interval<T>::difference_type>::value() );

	itl::interval<T> j_4_4(i_4_4);
	BOOST_CHECK_EQUAL( i_4_4, j_4_4 );

	T v2 = make<T>(2);
	BOOST_CHECK_EQUAL( closed_interval<T>(v2, v4),    interval<T>(v2, v4) );
	BOOST_CHECK_EQUAL( closed_interval<T>(v2, v4),    interval<T>(v2, v4, interval<T>::CLOSED) );
	BOOST_CHECK_EQUAL( rightopen_interval<T>(v2, v4), interval<T>(v2, v4, interval<T>::RIGHT_OPEN) );
	BOOST_CHECK_EQUAL( leftopen_interval<T>(v2, v4),  interval<T>(v2, v4, interval<T>::LEFT_OPEN) );
	BOOST_CHECK_EQUAL( open_interval<T>(v2, v4),      interval<T>(v2, v4, interval<T>::OPEN) );

	BOOST_CHECK_EQUAL( closed_interval<T>(v2, v4).lower(),               v2 );
	BOOST_CHECK_EQUAL( closed_interval<T>(v2, v4).upper(),               v4 );
	BOOST_CHECK_EQUAL( closed_interval<T>(v2, v4).boundtypes(),          interval<T>::CLOSED );
	BOOST_CHECK_EQUAL( closed_interval<T>(v2, v4).is_closed(),           true );
	BOOST_CHECK_EQUAL( closed_interval<T>(v2, v4).leftbound_closed(),    true );
	BOOST_CHECK_EQUAL( closed_interval<T>(v2, v4).rightbound_closed(),   true );

	BOOST_CHECK_EQUAL( rightopen_interval<T>(v2, v4).lower(),            v2 );
	BOOST_CHECK_EQUAL( rightopen_interval<T>(v2, v4).upper(),            v4 );
	BOOST_CHECK_EQUAL( rightopen_interval<T>(v2, v4).boundtypes(),       interval<T>::RIGHT_OPEN );
	BOOST_CHECK_EQUAL( rightopen_interval<T>(v2, v4).is_rightopen(),     true );
	BOOST_CHECK_EQUAL( rightopen_interval<T>(v2, v4).leftbound_closed(), true );
	BOOST_CHECK_EQUAL( rightopen_interval<T>(v2, v4).rightbound_open(),  true );

	BOOST_CHECK_EQUAL( leftopen_interval<T>(v2, v4).lower(),             v2 );
	BOOST_CHECK_EQUAL( leftopen_interval<T>(v2, v4).upper(),             v4 );
	BOOST_CHECK_EQUAL( leftopen_interval<T>(v2, v4).boundtypes(),        interval<T>::LEFT_OPEN );
	BOOST_CHECK_EQUAL( leftopen_interval<T>(v2, v4).is_leftopen(),       true );
	BOOST_CHECK_EQUAL( leftopen_interval<T>(v2, v4).leftbound_open(),    true );
	BOOST_CHECK_EQUAL( leftopen_interval<T>(v2, v4).rightbound_closed(), true );

	BOOST_CHECK_EQUAL( open_interval<T>(v2, v4).lower(),                 v2 );
	BOOST_CHECK_EQUAL( open_interval<T>(v2, v4).upper(),                 v4 );
	BOOST_CHECK_EQUAL( open_interval<T>(v2, v4).boundtypes(),            interval<T>::OPEN );
	BOOST_CHECK_EQUAL( open_interval<T>(v2, v4).is_open(),               true );
	BOOST_CHECK_EQUAL( open_interval<T>(v2, v4).leftbound_open(),        true );
	BOOST_CHECK_EQUAL( open_interval<T>(v2, v4).rightbound_open(),       true );	
}

BOOST_AUTO_TEST_CASE_TEMPLATE(test_itl_interval_ctor_4_integral_types, T, integral_types)
{
	BOOST_CHECK_EQUAL(interval<T>().first(), itl::unon<T>::value());
	BOOST_CHECK_EQUAL(interval<T>().last(), itl::neutron<T>::value());
	BOOST_CHECK_EQUAL(interval<T>().length(), 0);
}

BOOST_AUTO_TEST_CASE(test_itl_interval_ctor_specific)
{
	BOOST_CHECK_EQUAL(interval<double>().continuous_length(), 0.0);
	BOOST_CHECK_EQUAL(interval<double>(5.0,5.0).cardinality(), 1);
	BOOST_CHECK_EQUAL(interval<std::string>("test","test").cardinality(), 1);
	BOOST_CHECK_EQUAL(interval<std::string>("best","test").cardinality(), interval<double>(0.0,0.1).cardinality());
}


BOOST_AUTO_TEST_CASE_TEMPLATE(test_itl_interval_equal_4_integral_types, T, integral_types)
{
	T v2 = make<T>(2);
	T v3 = make<T>(3);
	T v7 = make<T>(7);
	T v8 = make<T>(8);
	BOOST_CHECK_EQUAL(interval<T>(), interval<T>(v7,v3));

	//I: (I)nside  = closed bound
	//O: (O)utside = open bound
	interval<T>  I3_7I  = closed_interval<T>(v3,v7);
	interval<T>  I3__8O = rightopen_interval<T>(v3,v8);
	interval<T> O2__7I  = leftopen_interval<T>(v2,v7);
	interval<T> O2___8O = open_interval<T>(v2,v8);

	BOOST_CHECK_EQUAL(  I3_7I ,  I3_7I  );	
	BOOST_CHECK_EQUAL(  I3_7I ,  I3__8O );	
	BOOST_CHECK_EQUAL(  I3_7I , O2__7I  );	
	BOOST_CHECK_EQUAL(  I3_7I , O2___8O );	

	BOOST_CHECK_EQUAL(  I3__8O,  I3__8O);	
	BOOST_CHECK_EQUAL(  I3__8O, O2__7I  );	
	BOOST_CHECK_EQUAL(  I3__8O, O2___8O );	

	BOOST_CHECK_EQUAL( O2__7I , O2__7I  );	
	BOOST_CHECK_EQUAL( O2__7I , O2___8O );	

	BOOST_CHECK_EQUAL( O2___8O, O2___8O );	
}

BOOST_AUTO_TEST_CASE_TEMPLATE(test_itl_interval_equal_4_bicremental_continuous_types, T, bicremental_continuous_types)
{
	T v3 = make<T>(3);
	T v7 = make<T>(7);
	BOOST_CHECK_EQUAL(interval<T>(), interval<T>(v7,v3));

	//I: (I)nside  = closed bound
	//O: (O)utside = open bound
	interval<T> I3_7I = closed_interval<T>(v3,v7);
	interval<T> I3_7O = rightopen_interval<T>(v3,v7);
	interval<T> O3_7I = leftopen_interval<T>(v3,v7);
	interval<T> O3_7O = open_interval<T>(v3,v7);

	BOOST_CHECK_EQUAL( I3_7I ,  I3_7I  );	
	BOOST_CHECK_EQUAL( I3_7I == I3_7O, false  );	
	BOOST_CHECK_EQUAL( I3_7I == O3_7O, false  );	
	BOOST_CHECK_EQUAL( I3_7I == O3_7O, false );	

	BOOST_CHECK_EQUAL( I3_7O ,  I3_7O  );	
	BOOST_CHECK_EQUAL( I3_7O == O3_7I, false  );	
	BOOST_CHECK_EQUAL( I3_7O == O3_7O, false );	

	BOOST_CHECK_EQUAL( O3_7I ,  O3_7I  );	
	BOOST_CHECK_EQUAL( O3_7I == O3_7O, false );	

	BOOST_CHECK_EQUAL( O3_7O,   O3_7O  );	
} 

BOOST_AUTO_TEST_CASE_TEMPLATE(test_itl_interval_touches_4_bicremental_types, T, bicremental_types)
{
	T v3 = make<T>(3);
	T v7 = make<T>(7);
	T v9 = make<T>(9);

	interval<T> I3_7O = rightopen_interval<T>(v3,v7);
	interval<T> I7_9I = closed_interval<T>(v7,v9);
	BOOST_CHECK_EQUAL( I3_7O.touches(I7_9I), true );	

	interval<T> I3_7I = closed_interval<T>(v3,v7);
	interval<T> O7_9I = leftopen_interval<T>(v7,v9);
	BOOST_CHECK_EQUAL( I3_7I.touches(O7_9I), true );

	BOOST_CHECK_EQUAL( I3_7O.touches(O7_9I), false );	
	BOOST_CHECK_EQUAL( I3_7I.touches(I7_9I), false );	
}

BOOST_AUTO_TEST_CASE_TEMPLATE(test_itl_interval_touches_4_integral_types, T, integral_types)
{
	T v3 = make<T>(3);
	T v6 = make<T>(6);
	T v7 = make<T>(7);
	T v9 = make<T>(9);

	interval<T> I3_6I = closed_interval<T>(v3,v6);
	interval<T> I7_9I = closed_interval<T>(v7,v9);
	BOOST_CHECK_EQUAL( I3_6I.touches(I7_9I), true );	

	interval<T> I3_7O = rightopen_interval<T>(v3,v7);
	interval<T> O6_9I = leftopen_interval<T>(v6,v9);
	BOOST_CHECK_EQUAL( I3_7O.touches(O6_9I), true );
}


BOOST_AUTO_TEST_CASE_TEMPLATE(test_itl_interval_intersect_4_bicremental_types, T, bicremental_types)
{
	T v0 = make<T>(0);
	T v3 = make<T>(3);
	T v4 = make<T>(4);
	T v5 = make<T>(5);
	T v6 = make<T>(6);
	T v7 = make<T>(7);
	T v9 = make<T>(9);

	interval<T> section;
	interval<T> I3_7O = rightopen_interval<T>(v3,v7);

	interval<T> I0_3O = rightopen_interval<T>(v0,v3);
	section = I3_7O; section *= I0_3O;
	BOOST_CHECK_EQUAL( I0_3O.exclusive_less(I3_7O), true );
	BOOST_CHECK_EQUAL( I0_3O.disjoint_to(I3_7O), true );
	BOOST_CHECK_EQUAL( section.empty(), true );
	BOOST_CHECK_EQUAL( section, interval<T>() );

	interval<T> I0_5O = rightopen_interval<T>(v0,v5);
	section = I3_7O; section *= I0_5O;
	BOOST_CHECK_EQUAL( section, rightopen_interval<T>(v3, v5) );

	interval<T> I0_9O = rightopen_interval<T>(v0,v9);
	section = I3_7O; section *= I0_9O;
	BOOST_CHECK_EQUAL( section, I3_7O );

	interval<T> I4_5I = closed_interval<T>(v4,v5);
	section = I3_7O; section *= I4_5I;
	BOOST_CHECK_EQUAL( section, I4_5I );

	interval<T> O4_6O = open_interval<T>(v4,v6);
	section = I3_7O; section *= O4_6O;
	BOOST_CHECK_EQUAL( section, O4_6O );

	interval<T> O4_9I = leftopen_interval<T>(v4,v9);
	section = I3_7O; section *= O4_9I;
	BOOST_CHECK_EQUAL( section, open_interval<T>(v4,v7) );

	interval<T> I7_9I = closed_interval<T>(v7,v9);
	section = I3_7O; section *= I7_9I;
	BOOST_CHECK_EQUAL( I3_7O.exclusive_less(I7_9I), true );
	BOOST_CHECK_EQUAL( I3_7O.disjoint_to(I7_9I), true );
	BOOST_CHECK_EQUAL( section.empty(), true );
}
