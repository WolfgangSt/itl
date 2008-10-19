/*----------------------------------------------------------------------------+
Copyright (c) 2008-2008: Joachim Faulhaber
+-----------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+----------------------------------------------------------------------------*/
#ifndef __itl_interval_maps_h_JOFA_081008__
#define __itl_interval_maps_h_JOFA_081008__

#include <itl/interval_base_map.hpp>

namespace itl
{

//-----------------------------------------------------------------------------
// addition +=
//-----------------------------------------------------------------------------
template 
<
	class SubType, class DomainT, class CodomainT,
	class Traits, template<class>class Interval, 
	template<class>class Compare, template<class>class Alloc,
	template
	<	
		class, class, class, template<class>class, 
		template<class>class, template<class>class
	>
	class IntervalMap
>
interval_base_map<SubType,DomainT,CodomainT,Traits,Interval,Compare,Alloc>& 
operator +=
(
		  interval_base_map<SubType,DomainT,CodomainT,
		                    Traits,Interval,Compare,Alloc>& object,
	const IntervalMap<DomainT,CodomainT,
	                  Traits,Interval,Compare,Alloc>& operand
)
{
	typedef IntervalMap<DomainT,CodomainT,
		                Traits,Interval,Compare,Alloc> operand_type;
    const_FORALL(typename operand_type, elem_, operand) 
        object.add(*elem_); 

    return object; 
}

//--- value_type --------------------------------------------------------------
template 
<
	class DomainT, class CodomainT,
	class Traits, template<class>class Interval, 
	template<class>class Compare, template<class>class Alloc,
	template
	<	
		class, class, class, template<class>class, 
		template<class>class, template<class>class
	>
	class IntervalMap
>
IntervalMap<DomainT,CodomainT,Traits,Interval,Compare,Alloc>& 
operator +=
(
		  IntervalMap<DomainT,CodomainT,
		              Traits,Interval,Compare,Alloc>& object,
	const typename 
	      IntervalMap<DomainT,CodomainT,
	                  Traits,Interval,Compare,Alloc>::value_type& operand
)
{
    return object.add(operand); 
}

//--- base_value_type ---------------------------------------------------------
template 
<
	class DomainT, class CodomainT,
	class Traits, template<class>class Interval, 
	template<class>class Compare, template<class>class Alloc,
	template
	<	
		class, class, class, template<class>class, 
		template<class>class, template<class>class
	>
	class IntervalMap
>
IntervalMap<DomainT,CodomainT,Traits,Interval,Compare,Alloc>& 
operator +=
(
		  IntervalMap<DomainT,CodomainT,
		              Traits,Interval,Compare,Alloc>& object,
	const typename 
	      IntervalMap<DomainT,CodomainT,
	                  Traits,Interval,Compare,Alloc>::base_pair_type& operand
)
{
    return object.add(operand); 
}


//-----------------------------------------------------------------------------
// subtraction -=
//-----------------------------------------------------------------------------
template 
<
	class SubType, class DomainT, class CodomainT,
	class Traits, template<class>class Interval, 
	template<class>class Compare, template<class>class Alloc,
	template
	<	
		class, class, class, template<class>class, 
		template<class>class, template<class>class
	>
	class IntervalMap
>
interval_base_map<SubType,DomainT,CodomainT,Traits,Interval,Compare,Alloc>& 
operator -=
(
		  interval_base_map<SubType,DomainT,CodomainT,
		                    Traits,Interval,Compare,Alloc>& object,
	const IntervalMap<DomainT,CodomainT,
	                  Traits,Interval,Compare,Alloc>& operand
)
{
	typedef IntervalMap<DomainT,CodomainT,
		                Traits,Interval,Compare,Alloc> operand_type;
    const_FORALL(typename operand_type, elem_, operand) 
        object.subtract(*elem_); 

    return object; 
}

//--- value_type --------------------------------------------------------------
template 
<
	class DomainT, class CodomainT,
	class Traits, template<class>class Interval, 
	template<class>class Compare, template<class>class Alloc,
	template
	<	
		class, class, class, template<class>class, 
		template<class>class, template<class>class
	>
	class IntervalMap
>
IntervalMap<DomainT,CodomainT,Traits,Interval,Compare,Alloc>& 
operator -=
(
		  IntervalMap<DomainT,CodomainT,
		              Traits,Interval,Compare,Alloc>& object,
	const typename 
	      IntervalMap<DomainT,CodomainT,
	                  Traits,Interval,Compare,Alloc>::value_type& operand
)
{
    return object.subtract(operand); 
}

//--- base_value_type ---------------------------------------------------------
template 
<
	class DomainT, class CodomainT,
	class Traits, template<class>class Interval, 
	template<class>class Compare, template<class>class Alloc,
	template
	<	
		class, class, class, template<class>class, 
		template<class>class, template<class>class
	>
	class IntervalMap
>
IntervalMap<DomainT,CodomainT,Traits,Interval,Compare,Alloc>& 
operator -=
(
		  IntervalMap<DomainT,CodomainT,
		              Traits,Interval,Compare,Alloc>& object,
	const typename 
	      IntervalMap<DomainT,CodomainT,
	                  Traits,Interval,Compare,Alloc>::base_pair_type& operand
)
{
    return object.subtract(operand); 
}


//-----------------------------------------------------------------------------
// erasure -= of elements given by an interval_set
//-----------------------------------------------------------------------------
template 
<
	class SubType, class DomainT, class CodomainT,
	class Traits, template<class>class Interval, 
	template<class>class Compare, template<class>class Alloc,
	template
	<	
		class, template<class>class, 
		template<class>class, template<class>class
	>
	class IntervalSet
>
interval_base_map<SubType,DomainT,CodomainT,Traits,Interval,Compare,Alloc>& 
operator -=
(
          interval_base_map<SubType,DomainT,CodomainT,
                            Traits,Interval,Compare,Alloc>& object,
    const IntervalSet<DomainT,Interval,Compare,Alloc>& erasure
)
{
    typedef IntervalSet<DomainT,Interval,Compare,Alloc> set_type;
    const_FORALL(typename set_type, interval_, erasure) 
        object.erase(*interval_); 

    return object; 
}

//--- value_type --------------------------------------------------------------
template 
<
	class DomainT, class CodomainT,
	class Traits, template<class>class Interval, 
	template<class>class Compare, template<class>class Alloc,
	template
	<	
		class, class, class, template<class>class, 
		template<class>class, template<class>class
	>
	class IntervalMap
>
IntervalMap<DomainT,CodomainT,Traits,Interval,Compare,Alloc>& 
operator -=
(
		  IntervalMap<DomainT,CodomainT,
		              Traits,Interval,Compare,Alloc>& object,
	const typename 
	      IntervalMap<DomainT,CodomainT,
	                  Traits,Interval,Compare,Alloc>::interval_type& operand
)
{
    return object.erase(operand); 
}


//-----------------------------------------------------------------------------
// intersection *=  
//-----------------------------------------------------------------------------
template 
<
	class SubType, class DomainT, class CodomainT,
	class Traits, template<class>class Interval, 
	template<class>class Compare, template<class>class Alloc,
	class SectanT
>
interval_base_map<SubType,DomainT,CodomainT,Traits,Interval,Compare,Alloc>& 
operator *=
(
		  interval_base_map<SubType,DomainT,CodomainT,
		                    Traits,Interval,Compare,Alloc>& object,
	const SectanT& operand
)
{
	typedef interval_base_map<SubType,DomainT,CodomainT,
		                      Traits,Interval,Compare,Alloc> object_type;
	object_type intersection;
	object.add_intersection(intersection,operand);
	object.swap(intersection);
	return object;
}

//-----------------------------------------------------------------------------
// is_element_equal
//-----------------------------------------------------------------------------
template 
<
	class SubType, class DomainT, class CodomainT,
	class Traits, template<class>class Interval, 
	template<class>class Compare, template<class>class Alloc,
	template
	<	
		class, class, class, template<class>class, 
		template<class>class, template<class>class
	>
	class IntervalMap
>
bool is_element_equal
(
		  interval_base_map<SubType,DomainT,CodomainT,
		                    Traits,Interval,Compare,Alloc>& object,
	const IntervalMap<DomainT,CodomainT,
	                  Traits,Interval,Compare,Alloc>& operand
)
{
	typedef interval_map<DomainT,CodomainT,
		                 Traits,Interval,Compare,Alloc> joined_type;
	//JODO OPTI: faster compare
	joined_type object_joined(object);
	joined_type operand_joined(operand);

    return Set::lexicographical_equal(object_joined, operand_joined);
}

//-----------------------------------------------------------------------------
// is_disjoint
//-----------------------------------------------------------------------------

//--- IntervalMap -------------------------------------------------------------
template 
<
	class SubType, class DomainT, class CodomainT,
	class Traits, template<class>class Interval, 
	template<class>class Compare, template<class>class Alloc,
	template
	<	
		class, class, class, template<class>class, 
		template<class>class, template<class>class
	>
	class IntervalMap
>
//JODO boost::enable_if
bool is_disjoint
(
		  interval_base_map<SubType,DomainT,CodomainT,
		                    Traits,Interval,Compare,Alloc>& object,
	const IntervalMap<DomainT,CodomainT,
	                  Traits,Interval,Compare,Alloc>& operand
)
{
	typedef interval_base_map<SubType,DomainT,CodomainT,
		                      Traits,Interval,Compare,Alloc> object_type;
	typedef IntervalMap<DomainT,CodomainT,
		                Traits,Interval,Compare,Alloc> operand_type;
	object_type intersection;

	if(operand.empty())
		return true;

	operand_type::const_iterator common_lwb;
	operand_type::const_iterator common_upb;

	if(!Set::common_range(common_lwb, common_upb, operand, object))
		return true;

	operand_type::const_iterator it = common_lwb;
	while(it != common_upb)
	{
		object.add_intersection(intersection, operand_type::key_value(it++));
		if(!intersection.empty())
			return false;
	}

	return true; 
}

//--- IntervalSet -------------------------------------------------------------
template 
<
	class SubType, class DomainT, class CodomainT,
	class Traits, template<class>class Interval, 
	template<class>class Compare, template<class>class Alloc,
	template
	<	
		class, template<class>class, 
		template<class>class, template<class>class
	>
	class IntervalSet
>
//JODO boost::enable_if
bool is_disjoint
(
		  interval_base_map<SubType,DomainT,CodomainT,
		                    Traits,Interval,Compare,Alloc>& object,
	const IntervalSet<DomainT,Interval,Compare,Alloc>& operand
)
{
	typedef interval_base_map<SubType,DomainT,CodomainT,
		                      Traits,Interval,Compare,Alloc> object_type;
	typedef IntervalSet<DomainT,Interval,Compare,Alloc> operand_type;
	object_type intersection;

	if(operand.empty())
		return true;

	operand_type::const_iterator common_lwb;
	operand_type::const_iterator common_upb;

	if(!Set::common_range(common_lwb, common_upb, operand, object))
		return true;

	operand_type::const_iterator it = common_lwb;
	while(it != common_upb)
	{
		object.add_intersection(intersection, operand_type::key_value(it++));
		if(!intersection.empty())
			return false;
	}

	return true; 
}


} // namespace itl

#endif


