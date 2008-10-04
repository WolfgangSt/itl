/*----------------------------------------------------------------------------+
Copyright (c) 2008-2008: Joachim Faulhaber
+-----------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+----------------------------------------------------------------------------*/
#ifndef __itl_interval_sets_h_JOFA_080930__
#define __itl_interval_sets_h_JOFA_080930__

#include <itl/interval_base_set.hpp>

namespace itl
{

//-----------------------------------------------------------------------------
// addition +=
//-----------------------------------------------------------------------------
template 
<
	class SubType, class DomainT, template<class>class Interval, 
	template<class>class Compare, template<class>class Alloc,
	template
	<	
		class, template<class>class, 
		template<class>class, template<class>class
	>
	class IntervalSet
>
interval_base_set<SubType,DomainT,Interval,Compare,Alloc>& 
operator +=
(
		  interval_base_set<SubType,DomainT,Interval,Compare,Alloc>& object,
	const IntervalSet              <DomainT,Interval,Compare,Alloc>& operand
)
{
	typedef split_interval_set<DomainT,Interval,Compare,Alloc> set_type;
	const_FORALL(typename set_type, elem_, operand) 
		object.subtract(*elem_); 

	return object; 
}

//--- interval_type -----------------------------------------------------------
template 
<
	class DomainT, template<class>class Interval, 
	template<class>class Compare, template<class>class Alloc,
	template
	<	
		class, template<class>class, 
		template<class>class, template<class>class
	>
	class IntervalSet
>
IntervalSet<DomainT,Interval,Compare,Alloc>& 
operator +=
(
	IntervalSet<DomainT,Interval,Compare,Alloc>& object,
	const typename IntervalSet<DomainT,Interval,Compare,Alloc>::interval_type& interval
)
{
	return object.add(interval);
}

//--- domain_type -------------------------------------------------------------
template 
<
	class DomainT, template<class>class Interval, 
	template<class>class Compare, template<class>class Alloc,
	template
	<	
		class, template<class>class, 
		template<class>class, template<class>class
	>
	class IntervalSet
>
IntervalSet<DomainT,Interval,Compare,Alloc>& 
operator +=
(
	IntervalSet<DomainT,Interval,Compare,Alloc>& object,
	const typename IntervalSet<DomainT,Interval,Compare,Alloc>::domain_type& value
)
{
	return object.add(value);
}


//-----------------------------------------------------------------------------
// difference -=
//-----------------------------------------------------------------------------
template 
<
	class SubType, class DomainT, template<class>class Interval, 
	template<class>class Compare, template<class>class Alloc,
	template
	<	
		class, template<class>class, 
		template<class>class, template<class>class
	>
	class IntervalSet
>
interval_base_set<SubType,DomainT,Interval,Compare,Alloc>& 
operator -=
(
		  interval_base_set<SubType,DomainT,Interval,Compare,Alloc>& object,
	const IntervalSet              <DomainT,Interval,Compare,Alloc>& operand
)
{
		typedef IntervalSet<DomainT,Interval,Compare,Alloc> operand_type;
		const_FORALL(typename operand_type, elem_, operand) 
			object.subtract(*elem_); 

		return object; 
}

//--- interval_type -----------------------------------------------------------
template 
<
	class DomainT, template<class>class Interval, 
	template<class>class Compare, template<class>class Alloc,
	template
	<	
		class, template<class>class, 
		template<class>class, template<class>class
	>
	class IntervalSet
>
IntervalSet<DomainT,Interval,Compare,Alloc>& 
operator -=
(
	IntervalSet<DomainT,Interval,Compare,Alloc>& object,
	const typename IntervalSet<DomainT,Interval,Compare,Alloc>::interval_type& interval
)
{
	return object.subtract(interval);
}

//--- domain_type -------------------------------------------------------------
template 
<
	class DomainT, template<class>class Interval, 
	template<class>class Compare, template<class>class Alloc,
	template
	<	
		class, template<class>class, 
		template<class>class, template<class>class
	>
	class IntervalSet
>
IntervalSet<DomainT,Interval,Compare,Alloc>& 
operator -=
(
	IntervalSet<DomainT,Interval,Compare,Alloc>& object,
	const typename IntervalSet<DomainT,Interval,Compare,Alloc>::domain_type& value
)
{
	return object.subtract(value);
}


//-----------------------------------------------------------------------------
// intersection *=
//-----------------------------------------------------------------------------
template 
<
	class SubType, class DomainT, template<class>class Interval, 
	template<class>class Compare, template<class>class Alloc,
	template
	<	
		class, template<class>class, 
		template<class>class, template<class>class
	>
	class IntervalSet
>
interval_base_set<SubType,DomainT,Interval,Compare,Alloc>& 
operator *=
(
		  interval_base_set<SubType,DomainT,Interval,Compare,Alloc>& object,
	const IntervalSet              <DomainT,Interval,Compare,Alloc>& operand
)
{
	typedef interval_base_set<SubType,DomainT,Interval,Compare,Alloc> object_type;
	typedef IntervalSet              <DomainT,Interval,Compare,Alloc> operand_type;
	object_type intersection;

	if(operand.empty())
	{
		object.clear();
		return object;
	}

	operand_type::const_iterator common_lwb;
	operand_type::const_iterator common_upb;

	if(!Set::common_range(common_lwb, common_upb, operand, object))
	{
		object.clear();
		return object;
	}

	operand_type::const_iterator it = common_lwb;
	while(it != common_upb)
		object.add_intersection(intersection, *it++);

	object.swap(intersection);

	return object; 
}

//--- interval_type -----------------------------------------------------------
template 
<
	class DomainT, template<class>class Interval, 
	template<class>class Compare, template<class>class Alloc,
	template
	<	
		class, template<class>class, 
		template<class>class, template<class>class
	>
	class IntervalSet
>
IntervalSet<DomainT,Interval,Compare,Alloc>& 
operator *=
(
	IntervalSet<DomainT,Interval,Compare,Alloc>& object,
	const typename IntervalSet<DomainT,Interval,Compare,Alloc>::interval_type& interval
)
{
	typedef IntervalSet<DomainT,Interval,Compare,Alloc> object_type;
	object_type intersection;

	if(interval.empty())
	{
		object.clear();
		return object;
	}

	object.add_intersection(intersection, interval);
	object.swap(intersection);
	return object; 
}

//--- domain_type -------------------------------------------------------------
template 
<
	class DomainT, template<class>class Interval, 
	template<class>class Compare, template<class>class Alloc,
	template
	<	
		class, template<class>class, 
		template<class>class, template<class>class
	>
	class IntervalSet
>
IntervalSet<DomainT,Interval,Compare,Alloc>& 
operator *=
(
	IntervalSet<DomainT,Interval,Compare,Alloc>& object,
	const typename IntervalSet<DomainT,Interval,Compare,Alloc>::domain_type& value
)
{
	typedef typename IntervalSet<DomainT,Interval,Compare,Alloc>
		::interval_type interval_type;
	return object *= interval_type(value);
}


//-----------------------------------------------------------------------------
// is_disjoint
//-----------------------------------------------------------------------------
template 
<
	class SubType, class DomainT, template<class>class Interval, 
	template<class>class Compare, template<class>class Alloc,
	template
	<	
		class, template<class>class, 
		template<class>class, template<class>class
	>
	class IntervalSet
>
bool is_disjoint
(
		  interval_base_set<SubType,DomainT,Interval,Compare,Alloc>& object,
	const IntervalSet              <DomainT,Interval,Compare,Alloc>& operand
)
{
	typedef interval_base_set<SubType,DomainT,Interval,Compare,Alloc> object_type;
	typedef IntervalSet              <DomainT,Interval,Compare,Alloc> operand_type;
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
		object.add_intersection(intersection, *it++);
		if(!intersection.empty())
			return false;
	}

	return true; 
}

//-----------------------------------------------------------------------------
// insert
//-----------------------------------------------------------------------------
template 
<
	class SubType, class DomainT, template<class>class Interval, 
	template<class>class Compare, template<class>class Alloc,
	template
	<	
		class, template<class>class, 
		template<class>class, template<class>class
	>
	class IntervalSet
>
interval_base_set<SubType,DomainT,Interval,Compare,Alloc>& 
insert
(
	      interval_base_set<SubType,DomainT,Interval,Compare,Alloc>& object,
    const IntervalSet              <DomainT,Interval,Compare,Alloc>& operand
)
{
    return object += operand; 
}
    
//-----------------------------------------------------------------------------
// erase
//-----------------------------------------------------------------------------
template 
<
	class SubType, class DomainT, template<class>class Interval, 
	template<class>class Compare, template<class>class Alloc,
	template
	<	
		class, template<class>class, 
		template<class>class, template<class>class
	>
	class IntervalSet
>
interval_base_set<SubType,DomainT,Interval,Compare,Alloc>& 
erase
(
	      interval_base_set<SubType,DomainT,Interval,Compare,Alloc>& object,
    const IntervalSet              <DomainT,Interval,Compare,Alloc>& operand
)
{
    return object -= operand; 
}

//-----------------------------------------------------------------------------
// enclosure
//-----------------------------------------------------------------------------
template 
<
	class DomainT, template<class>class Interval, 
	template<class>class Compare, template<class>class Alloc,
	template
	<	
		class, template<class>class, 
		template<class>class, template<class>class
	>
	class IntervalSet
>
typename IntervalSet<DomainT,Interval,Compare,Alloc>::interval_type 
enclosure(const IntervalSet<DomainT,Interval,Compare,Alloc>& object)
{
	typedef typename 
	IntervalSet<DomainT,Interval,Compare,Alloc>::interval_type interval_type;
    return 
		object.empty() ? itl::neutron<interval_type>::value()
                       : (*object.begin()).span(*object.rbegin());
}
    


} // namespace itl

#endif


