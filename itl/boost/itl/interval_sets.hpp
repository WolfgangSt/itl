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
	typedef IntervalSet             <DomainT,Interval,Compare,Alloc> operand_type;
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

} // namespace itl

#endif


