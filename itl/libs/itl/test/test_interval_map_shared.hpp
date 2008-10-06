/*----------------------------------------------------------------------------+
Copyright (c) 2008-2008: Joachim Faulhaber
+-----------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+----------------------------------------------------------------------------*/
#ifndef __test_itl_interval_map_shared_h_JOFA_081005__
#define __test_itl_interval_map_shared_h_JOFA_081005__


template <template<class T, class U,
                   class Traits = itl::neutron_absorber,
                   template<class>class = itl::interval,
                   template<class>class = std::less,
				   template<class>class = std::allocator
                  >class IntervalMap, 
          class T, class U>
void interval_map_fundamentals_4_ordered_types()
{
	typedef IntervalMap<T,U> IntervalMapT;
	typedef typename IntervalMapT::size_type       size_T;
	typedef typename IntervalMapT::difference_type diff_T;

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
	U u0 = itl::neutron<U>::value();
	U u1 = itl::unon<U>::value();

	//-------------------------------------------------------------------------
	//empty set
	//-------------------------------------------------------------------------
	BOOST_CHECK_EQUAL(IntervalMapT().empty(), true);
	BOOST_CHECK_EQUAL(IntervalMapT().cardinality(), itl::neutron<size_T>::value());
	BOOST_CHECK_EQUAL(IntervalMapT().size(), itl::neutron<size_T>::value());
	BOOST_CHECK_EQUAL(IntervalMapT().interval_count(), 0);
	BOOST_CHECK_EQUAL(IntervalMapT().iterative_size(), 0);
	BOOST_CHECK_EQUAL(IntervalMapT(), IntervalMapT());

	interval<T> mt_interval = neutron<interval<T> >::value();
	BOOST_CHECK_EQUAL(mt_interval, interval<T>());
	IntervalMapT::value_type mt_u1 = make_pair(mt_interval, u1);
	IntervalMapT mt_map = neutron<IntervalMapT >::value();
	BOOST_CHECK_EQUAL(mt_map, IntervalMapT());

	//adding emptieness to emptieness yields emptieness ;)
	mt_map.add(mt_u1).add(mt_u1);
	BOOST_CHECK_EQUAL(mt_map, IntervalMapT());
	mt_map.insert(mt_u1).insert(mt_u1);
	BOOST_CHECK_EQUAL(mt_map, IntervalMapT());
	(mt_map += mt_u1) += mt_u1;
	BOOST_CHECK_EQUAL(mt_map, IntervalMapT());
	BOOST_CHECK_EQUAL(enclosure(mt_map), neutron<interval<T> >::value());

	//subtracting emptieness
	mt_map.subtract(mt_u1).subtract(mt_u1);
	BOOST_CHECK_EQUAL(mt_map, IntervalMapT());

	mt_map.erase(mt_interval).erase(mt_interval);
	BOOST_CHECK_EQUAL(mt_map, IntervalMapT());
	(mt_map -= mt_u1) -= mt_u1;
	BOOST_CHECK_EQUAL(mt_map, IntervalMapT());

	//subtracting elements form emptieness
	IntervalMapT::base_value_type v0_u1 = make_pair(v0,u1);
	IntervalMapT::base_value_type v1_u1 = make_pair(v1,u1);
	mt_map.subtract(v0_u1).subtract(v1_u1);
	BOOST_CHECK_EQUAL(mt_map, IntervalMapT());
	mt_map.erase(v0_u1).erase(v1_u1);
	BOOST_CHECK_EQUAL(mt_map, IntervalMapT());
	(mt_map -= v0_u1) -= v1_u1;
	BOOST_CHECK_EQUAL(mt_map, IntervalMapT());

	//subtracting intervals form emptieness
	IntervalMapT::value_type I0_0I_u1 = make_pair(I0_0I,u1);
	IntervalMapT::value_type I0_1I_u1 = make_pair(I0_1I,u1);
	IntervalMapT::value_type I1_1I_u1 = make_pair(I1_1I,u1);
	mt_map.subtract(I0_1I_u1).subtract(I1_1I_u1);
	BOOST_CHECK_EQUAL(mt_map, IntervalMapT());
	mt_map.erase(I0_1I_u1).erase(I1_1I_u1);
	BOOST_CHECK_EQUAL(mt_map, IntervalMapT());
	(mt_map -= I0_1I_u1) -= I1_1I_u1;
	BOOST_CHECK_EQUAL(mt_map, IntervalMapT());

	mt_map.erase(I0_1I).erase(I1_1I);
	BOOST_CHECK_EQUAL(mt_map, IntervalMapT());

	//insecting emptieness
	(mt_map *= mt_u1) *= mt_u1;
	BOOST_CHECK_EQUAL(mt_map, IntervalMapT());
	(mt_map *= mt_interval) *= mt_interval;
	BOOST_CHECK_EQUAL(mt_map, IntervalMapT());

	/*JODO URG
	//insecting emptieness with elements
	(mt_map *= v1_u1) *= v0_u1;
	BOOST_CHECK_EQUAL(mt_map, IntervalMapT());
	//insecting emptieness with intervals
	(mt_map *= I1_1I) *= I0_1I;
	BOOST_CHECK_EQUAL(mt_map, IntervalMapT());
	*/

	//-------------------------------------------------------------------------
	//unary set
	//-------------------------------------------------------------------------
	IntervalMapT single_I0_0I_u1_from_element(v0_u1);
	IntervalMapT single_I0_0I_u1_from_interval(I0_0I_u1);
	IntervalMapT single_I0_0I_u1(single_I0_0I_u1_from_interval);

	BOOST_CHECK_EQUAL(single_I0_0I_u1_from_element, single_I0_0I_u1_from_interval);
	BOOST_CHECK_EQUAL(single_I0_0I_u1_from_element, single_I0_0I_u1);
	BOOST_CHECK_EQUAL(enclosure(single_I0_0I_u1), I0_0I);
	BOOST_CHECK_EQUAL(single_I0_0I_u1.lower(), I0_0I.lower());
	BOOST_CHECK_EQUAL(single_I0_0I_u1.upper(), I0_0I.upper());

	IntervalMapT single_I1_1I_u1_from_element(v1_u1);
	IntervalMapT single_I1_1I_u1_from_interval(I1_1I_u1);
	IntervalMapT single_I1_1I_u1(single_I1_1I_u1_from_interval);

	BOOST_CHECK_EQUAL(single_I1_1I_u1_from_element, single_I1_1I_u1_from_interval);
	BOOST_CHECK_EQUAL(single_I1_1I_u1_from_element, single_I1_1I_u1);

	IntervalMapT single_I0_1I_u1_from_interval(I0_1I_u1);
	IntervalMapT single_I0_1I_u1(single_I0_1I_u1_from_interval);

	BOOST_CHECK_EQUAL(single_I0_1I_u1_from_interval, single_I0_1I_u1);
	BOOST_CHECK_EQUAL(enclosure(single_I0_1I_u1), I0_1I);
	BOOST_CHECK_EQUAL(single_I0_1I_u1.lower(), I0_1I.lower());
	BOOST_CHECK_EQUAL(single_I0_1I_u1.upper(), I0_1I.upper());

	//contains predicate
	BOOST_CHECK_EQUAL(single_I0_0I_u1.contains(v0), true);
	BOOST_CHECK_EQUAL(single_I0_0I_u1.contains(v0_u1), true);
	BOOST_CHECK_EQUAL(single_I0_0I_u1.contains(I0_0I_u1), true);

	BOOST_CHECK_EQUAL(single_I1_1I_u1.contains(v1), true);
	BOOST_CHECK_EQUAL(single_I1_1I_u1.contains(v1_u1), true);
	BOOST_CHECK_EQUAL(single_I1_1I_u1.contains(I1_1I_u1), true);

	BOOST_CHECK_EQUAL(single_I0_1I_u1.contains(v0), true);
	BOOST_CHECK_EQUAL(single_I0_1I_u1.contains(I0_1I_u1), true);
	BOOST_CHECK_EQUAL(single_I0_1I_u1.contains(v1), true);
	BOOST_CHECK_EQUAL(single_I0_1I_u1.contains(I1_1I_u1), true);

	BOOST_CHECK_EQUAL(single_I0_1I_u1.contains(single_I0_0I_u1), true);
	BOOST_CHECK_EQUAL(single_I0_1I_u1.contains(single_I1_1I_u1), true);
	BOOST_CHECK_EQUAL(single_I0_1I_u1.contains(single_I0_1I_u1), true);

	BOOST_CHECK_EQUAL(single_I0_0I_u1.cardinality(), itl::unon<size_T>::value());
	BOOST_CHECK_EQUAL(single_I0_0I_u1.size(), itl::unon<size_T>::value());
	BOOST_CHECK_EQUAL(single_I0_0I_u1.interval_count(), 1);
	BOOST_CHECK_EQUAL(single_I0_0I_u1.iterative_size(), 1);
}

template <template<class T, class U,
                   class Traits = itl::neutron_absorber,
                   template<class>class = itl::interval,
                   template<class>class = std::less,
				   template<class>class = std::allocator
                  >class IntervalMap, 
          class T, class U>
void interval_map_ctor_4_bicremental_types()
{
	typedef IntervalMap<T,U> IntervalMapT;

	T v4 = make<T>(4);
	U u2 = make<U>(2);
	U u4 = make<U>(4);
	itl::interval<T> I4_4I(v4);
	IntervalMapT::base_value_type v4_u2(v4,u2);
	IntervalMapT::value_type I4_4I_u2(I4_4I,u2);

	IntervalMapT _I4_4I_u2;
	BOOST_CHECK_EQUAL( _I4_4I_u2.empty(), true );
	IntervalMapT _I4_4I_u2_1;
	IntervalMapT _I4_4I_u2_2;
	IntervalMapT _I4_4I_u2_3;
	_I4_4I_u2   += v4_u2;
	_I4_4I_u2_1 += I4_4I_u2;
	BOOST_CHECK_EQUAL( _I4_4I_u2, _I4_4I_u2_1 );
	_I4_4I_u2_2.add(v4_u2);
	BOOST_CHECK_EQUAL( _I4_4I_u2, _I4_4I_u2_2 );
	_I4_4I_u2_3.add(I4_4I_u2);
	BOOST_CHECK_EQUAL( _I4_4I_u2, _I4_4I_u2_3 );

	_I4_4I_u2.clear();
	_I4_4I_u2.add(I4_4I_u2).add(I4_4I_u2);
	IntervalMapT _I4_4I_u4(make_pair(I4_4I, make<U>(4)));
	BOOST_CHECK_EQUAL( _I4_4I_u2, _I4_4I_u4 );

	_I4_4I_u2.clear();
	_I4_4I_u2.insert(I4_4I_u2).insert(I4_4I_u2);
	BOOST_CHECK_EQUAL( _I4_4I_u2, _I4_4I_u2_1 );

	BOOST_CHECK_EQUAL( _I4_4I_u2.cardinality(),      unon<IntervalMapT::size_type>::value()  );
	BOOST_CHECK_EQUAL( _I4_4I_u2.size(),             unon<IntervalMapT::size_type>::value()  );
	BOOST_CHECK_EQUAL( _I4_4I_u2.interval_count(),   1  );
	BOOST_CHECK_EQUAL( _I4_4I_u2.iterative_size(),   1  );
	BOOST_CHECK_EQUAL( _I4_4I_u2.lower(),            v4 );
	BOOST_CHECK_EQUAL( _I4_4I_u2.upper(),            v4 );

	IntervalMapT _I4_4I_u2_copy(_I4_4I_u2);
	IntervalMapT _I4_4I_u2_assigned;
	_I4_4I_u2_assigned = _I4_4I_u2;
	BOOST_CHECK_EQUAL( _I4_4I_u2, _I4_4I_u2_copy );
	BOOST_CHECK_EQUAL( _I4_4I_u2, _I4_4I_u2_assigned );

	_I4_4I_u2_assigned.clear();
	BOOST_CHECK_EQUAL( true,   _I4_4I_u2_assigned.empty() );

	_I4_4I_u2_assigned.swap(_I4_4I_u2_copy);
	BOOST_CHECK_EQUAL( true,   _I4_4I_u2_copy.empty() );
	BOOST_CHECK_EQUAL( _I4_4I_u2, _I4_4I_u2_assigned );
}


template <template<class T, class U,
                   class Traits = itl::neutron_absorber,
                   template<class>class = itl::interval,
                   template<class>class = std::less,
				   template<class>class = std::allocator
                  >class IntervalMap, 
          class T, class U>
void interval_map_add_sub_4_bicremental_types()
{
	typedef IntervalMap<T,U> IntervalMapT;

	T v0 = make<T>(0);
	T v5 = make<T>(5);
	T v6 = make<T>(6);
	T v9 = make<T>(9);
	U u1 = make<U>(1);
	interval<T> I5_6I(v5,v6);
	interval<T> I5_9I(v5,v9);
	interval<T> I0_9I = closed_interval(v0, v9);
	IntervalMapT::base_value_type v0_u1 = make_pair(v0, u1);
	IntervalMapT::base_value_type v9_u1 = make_pair(v9, u1);
	IntervalMapT::value_type I5_6I_u1 = make_pair(I5_6I, u1);
	IntervalMapT::value_type I5_9I_u1 = make_pair(I5_9I, u1);
	IntervalMapT::value_type I0_9I_u1 = make_pair(closed_interval(v0, v9), u1);

	BOOST_CHECK_EQUAL( IntervalMapT(I5_6I_u1).add(v0_u1).add(v9_u1), 
		               IntervalMapT().add(v9_u1).add(I5_6I_u1).add(v0_u1) );

	IntervalMapT map_A = IntervalMapT(I5_6I_u1).add(v0_u1).add(v9_u1);
	IntervalMapT map_B = IntervalMapT().insert(v9_u1).insert(I5_6I_u1).insert(v0_u1);
	BOOST_CHECK_EQUAL( map_A, map_B );
	BOOST_CHECK_EQUAL( enclosure(map_A), I0_9I );
	BOOST_CHECK_EQUAL( map_A.lower(), I0_9I.lower() );
	BOOST_CHECK_EQUAL( map_A.upper(), I0_9I.upper() );
	//JODO: LAW !a.empty() => enclosure(a).lower() == a.lower()
	//JODO: LAW !a.empty() => enclosure(a).upper() == a.upper()

	IntervalMapT map_A1 = map_A, map_B1 = map_B,
	             map_A2 = map_A, map_B2 = map_B;

	map_A1.subtract(I5_6I_u1).subtract(v9_u1);
	map_B1.erase(v9_u1).erase(I5_6I_u1);
	BOOST_CHECK_EQUAL( map_A1, map_B1 );

	map_B1 = map_B;
	map_B2.erase(v9).erase(I5_6I);
	BOOST_CHECK_EQUAL( map_A1, map_B2 );

	map_A2.subtract(I5_9I_u1);
	map_B2.erase(I5_9I);
	BOOST_CHECK_EQUAL( map_A2, map_B2 );
}


/*
template <template<class T, template<class>class = itl::interval,
                            template<class>class = std::less,
							template<class>class = std::allocator
                  >class IntervalSet, 
          class T>
void interval_set_distinct_4_bicremental_types()
{
	typedef typename IntervalSet<T>::size_type       size_T;
	typedef typename IntervalSet<T>::difference_type diff_T;
	T v1 = make<T>(1);
	T v3 = make<T>(3);
	T v5 = make<T>(5);

	size_T s3 = make<size_T>(3);
	diff_T d0 = make<diff_T>(0);

	IntervalSet<T> is_1_3_5;
	is_1_3_5.add(v1).add(v3).add(v5);

	BOOST_CHECK_EQUAL( is_1_3_5.cardinality(),      s3 );
	BOOST_CHECK_EQUAL( is_1_3_5.size(),             s3 );
	BOOST_CHECK_EQUAL( is_1_3_5.interval_count(),   3 );
	BOOST_CHECK_EQUAL( is_1_3_5.iterative_size(),   3 );
}


template <template<class T, template<class>class = itl::interval,
                            template<class>class = std::less,
							template<class>class = std::allocator
                  >class IntervalSet, 
          class T>
void interval_set_distinct_4_bicremental_continuous_types()
{
	typedef typename IntervalSet<T>::size_type       size_T;
	typedef typename IntervalSet<T>::difference_type diff_T;
	T v1 = make<T>(1);
	T v2 = make<T>(2);
	T v3 = make<T>(3);
	T v5 = make<T>(5);

	size_T s3 = make<size_T>(3);
	diff_T d0 = make<diff_T>(0);
	diff_T d2 = make<diff_T>(2);
	diff_T d3 = make<diff_T>(3);

	IntervalSet<T> is_1_3_5;
	is_1_3_5.add(v1).add(v3).add(v5);

	BOOST_CHECK_EQUAL( is_1_3_5.cardinality(),      s3 );
	BOOST_CHECK_EQUAL( is_1_3_5.size(),             s3 );
	BOOST_CHECK_EQUAL( is_1_3_5.length(),           d0 );
	BOOST_CHECK_EQUAL( is_1_3_5.interval_count(),   3 );
	BOOST_CHECK_EQUAL( is_1_3_5.iterative_size(),   3 );

	size_T s4 = make<size_T>(4);
	diff_T d4 = make<diff_T>(4);

	IntervalSet<T> is_123_5;
	is_123_5 = is_1_3_5;
	is_123_5 += open_interval<T>(v1,v3);

	BOOST_CHECK_EQUAL( is_123_5.cardinality(),      std::numeric_limits<size_T>::infinity() );
	BOOST_CHECK_EQUAL( is_123_5.size(),             std::numeric_limits<size_T>::infinity() );
	BOOST_CHECK_EQUAL( is_123_5.length(),           d2 );
}


template <template<class T, template<class>class = itl::interval,
                            template<class>class = std::less,
							template<class>class = std::allocator
                  >class IntervalSet, 
          class T>
void interval_set_isolate_4_bicremental_continuous_types()
{
	typedef typename IntervalSet<T>::size_type       size_T;
	typedef typename IntervalSet<T>::difference_type diff_T;

	T v0 = make<T>(0);
	T v2 = make<T>(2);
	T v4 = make<T>(4);
	interval<T> I0_4I = closed_interval(v0,v4);
	interval<T> C0_2D = open_interval(v0,v2);
	interval<T> C2_4D = open_interval(v2,v4);
	//   {[0               4]}
	// - {   (0,2)   (2,4)   }
	// = {[0]     [2]     [4]}
	IntervalSet<T> iso_set = IntervalSet<T>(I0_4I);
	IntervalSet<T> gap_set;
	gap_set.add(C0_2D).add(C2_4D);
	iso_set -= gap_set;
	
	BOOST_CHECK_EQUAL( iso_set.cardinality(), static_cast<size_T>(3) );
	BOOST_CHECK_EQUAL( iso_set.iterative_size(), static_cast<std::size_t>(3) );

	IntervalSet<T> iso_set2;
	iso_set2.add(I0_4I);
	iso_set2.subtract(C0_2D).subtract(C2_4D);
	
	IntervalSet<T> iso_set3(I0_4I);
	(iso_set3 -= C0_2D) -= C2_4D;

	IntervalSet<T> iso_set4;
	iso_set4.insert(I0_4I);
	iso_set4.erase(C0_2D).erase(C2_4D);
	
	BOOST_CHECK_EQUAL( iso_set, iso_set2 );
	BOOST_CHECK_EQUAL( iso_set, iso_set3 );
	BOOST_CHECK_EQUAL( iso_set, iso_set4 );
}


template <template<class T, template<class>class = itl::interval,
                            template<class>class = std::less,
							template<class>class = std::allocator
                  >class IntervalSet, 
          class T>
void interval_set_contains_4_bicremental_types()
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
	IntervalSet<T> is(v1);	
	BOOST_CHECK_EQUAL( is.contains(v1), true );

	BOOST_CHECK_EQUAL( IntervalSet<T>().add(make<T>(2)).contains(make<T>(2)), true );
	BOOST_CHECK_EQUAL( IntervalSet<T>().insert(make<T>(2)).contains(make<T>(2)), true );
	BOOST_CHECK_EQUAL( (is += interval<T>(v3,v7)).contains(interval<T>(v3,v7)), true );

	IntervalSet<T> is0 = is;	

	IntervalSet<T> is2(closed_interval(v5,v8));
	is2.add(v9).add(v11);
	is += is2;
	BOOST_CHECK_EQUAL( is.contains(is2), true );	

	is = is0;
	IntervalSet<T> is3(closed_interval(v5,v8));
	is3.insert(v9).insert(v11);
	is += is3;
	BOOST_CHECK_EQUAL( is.contains(is3), true );	
}


template <template<class T, template<class>class = itl::interval,
                            template<class>class = std::less,
							template<class>class = std::allocator
                  >class IntervalSet, 
          class T>
void interval_set_operators_4_bicremental_types()
{
	T v0 = make<T>(0);
	T v1 = make<T>(1);
	T v3 = make<T>(3);
	T v5 = make<T>(5);
	T v7 = make<T>(7);
	T v8 = make<T>(8);
	IntervalSet<T> left, left2, right, all, all2, section, complement, naught;
	left.add(closed_interval(v0,v1)).add(closed_interval(v3,v5));
	(right += closed_interval(v3,v5)) += closed_interval(v7,v8);

	BOOST_CHECK_EQUAL( is_disjoint(left, right), false );

	(all += left) += right;
	(section += left) *= right;
	(complement += all) -= section;
	(all2 += section) += complement; 

	BOOST_CHECK_EQUAL( is_disjoint(section, complement), true );
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

// Test for nontrivial intersection of interval sets with intervals and values
template <template<class T, template<class>class = itl::interval,
                            template<class>class = std::less,
							template<class>class = std::allocator
                  >class IntervalSet, 
          class T>
void interval_set_base_intersect_4_bicremental_types()
{
	T v0 = make<T>(0);
	T v1 = make<T>(1);
	T v2 = make<T>(2);
	T v3 = make<T>(3);
	T v4 = make<T>(4);
	T v5 = make<T>(5);
	T v6 = make<T>(6);
	T v7 = make<T>(7);
	T v8 = make<T>(8);
	T v9 = make<T>(9);

	interval<T> I0_3D = rightopen_interval(v0,v3);
	interval<T> I1_3D = rightopen_interval(v1,v3);
	interval<T> I1_8D = rightopen_interval(v1,v8);
	interval<T> I2_7D = rightopen_interval(v2,v7);
	interval<T> I2_3D = rightopen_interval(v2,v3);
	interval<T> I6_7D = rightopen_interval(v6,v7);
	interval<T> I6_8D = rightopen_interval(v6,v8);
	interval<T> I6_9D = rightopen_interval(v6,v9);

	//--------------------------------------------------------------------------
	// IntervalSet
	//--------------------------------------------------------------------------
	//split_A      [0       3)       [6    9)
	//         *=      [1                8)
	//split_AB ->      [1   3)       [6  8)
	//         *=        [2             7)     
	//         ->        [2 3)       [6 7)
	IntervalSet<T>    split_A, split_B, split_AB, split_ab, split_ab2;

	split_A.add(I0_3D).add(I6_9D);
	split_AB = split_A;
	split_AB *= I1_8D;
	split_ab.add(I1_3D).add(I6_8D);

	BOOST_CHECK_EQUAL( split_AB, split_ab );

	split_AB = split_A;
	(split_AB *= I1_8D) *= I2_7D;
	split_ab2.add(I2_3D).add(I6_7D);

	BOOST_CHECK_EQUAL( split_AB, split_ab2 );


	//--------------------------------------------------------------------------
	//split_A      [0       3)       [6    9)
	//         *=       1
	//split_AB ->      [1]
	//         +=         (1             7)     
	//         ->      [1](1             7)
	split_A.add(I0_3D).add(I6_9D);
	split_AB = split_A;
	split_AB *= v1;
	split_ab.clear();
	split_ab.add(v1);

	BOOST_CHECK_EQUAL( split_AB, split_ab );

	split_AB = split_A;
	(split_AB *= v1) += open_interval<T>(v1,v7);
	split_ab2.clear();
	split_ab2 += rightopen_interval<T>(v1,v7);

	BOOST_CHECK_EQUAL( is_element_equal(split_AB, split_ab2), true );
}
*/

#endif // __test_itl_interval_map_shared_h_JOFA_080920__

