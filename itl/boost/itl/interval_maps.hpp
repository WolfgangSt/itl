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
/*JODO OPROM
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
	                  Traits,Interval,Compare,Alloc>::base_value_type& operand
)
{
    return object.add(operand); 
}
*/


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
// intersect: non destructive on arguments  
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
void intersect
(
		  interval_base_map<SubType,DomainT,CodomainT,
		                    Traits,Interval,Compare,Alloc>& intersection,
	const interval_base_map<SubType,DomainT,CodomainT,
		                    Traits,Interval,Compare,Alloc>& object,
	const IntervalMap<DomainT,CodomainT,
	                  Traits,Interval,Compare,Alloc>& operand
)
{
	intersection.clear();

    if(Traits::emits_neutrons || (Traits::absorbs_neutrons && !is_set<CodomainT>::value))
	{
		intersection = object;
        intersection += operand;
	}
    else
		object.add_intersection(intersection,operand);
}

//--- interval_set ------------------------------------------------------------
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
void intersect
(
		  interval_base_map<SubType,DomainT,CodomainT,
		                    Traits,Interval,Compare,Alloc>& intersection,
	const interval_base_map<SubType,DomainT,CodomainT,
		                    Traits,Interval,Compare,Alloc>& object,
	const IntervalSet<DomainT,Interval,Compare,Alloc>& operand
)
{
	intersection.clear();
    object.add_intersection(intersection,operand);
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
void intersect
(
		  IntervalMap<DomainT,CodomainT,
		              Traits,Interval,Compare,Alloc>& intersection,
	const IntervalMap<DomainT,CodomainT,
		              Traits,Interval,Compare,Alloc>& object,
	const typename 
	      IntervalMap<DomainT,CodomainT,
	                  Traits,Interval,Compare,Alloc>::value_type& operand
)
{
	intersection.clear();
    object.add_intersection(intersection,operand);
}

//--- interval_type -----------------------------------------------------------
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
void intersect
(
		  IntervalMap<DomainT,CodomainT,
		              Traits,Interval,Compare,Alloc>& intersection,
	const IntervalMap<DomainT,CodomainT,
		              Traits,Interval,Compare,Alloc>& object,
	const typename 
	      IntervalMap<DomainT,CodomainT,
	                  Traits,Interval,Compare,Alloc>::interval_type& operand
)
{
	intersection.clear();
    object.add_intersection(intersection,operand);
}

//-----------------------------------------------------------------------------
// intersection *=  
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
operator *=
(
		  interval_base_map<SubType,DomainT,CodomainT,
		                    Traits,Interval,Compare,Alloc>& object,
	const IntervalMap<DomainT,CodomainT,
	                  Traits,Interval,Compare,Alloc>& operand
)
{
	typedef interval_base_map<SubType,DomainT,CodomainT,
		                      Traits,Interval,Compare,Alloc> object_type;
	object_type intersection;
	intersect(intersection,object,operand);
	object.swap(intersection);
	return object;
}

//--- interval_set ------------------------------------------------------------
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
operator *=
(
		  interval_base_map<SubType,DomainT,CodomainT,
		                    Traits,Interval,Compare,Alloc>& object,
	const IntervalSet<DomainT,Interval,Compare,Alloc>& operand
)
{
	typedef interval_base_map<SubType,DomainT,CodomainT,
		                      Traits,Interval,Compare,Alloc> object_type;
    object_type intersection;
    object.add_intersection(intersection,operand);
    object.swap(intersection);
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
operator *=
(
		  IntervalMap<DomainT,CodomainT,
		              Traits,Interval,Compare,Alloc>& object,
	const typename 
	      IntervalMap<DomainT,CodomainT,
	                  Traits,Interval,Compare,Alloc>::value_type& operand
)
{
	typedef IntervalMap<DomainT,CodomainT,
		                Traits,Interval,Compare,Alloc> object_type;
	object_type intersection;
    object.add_intersection(intersection,operand);
	object.swap(intersection);
	return object;
}

//--- interval_type -----------------------------------------------------------
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
operator *=
(
		  IntervalMap<DomainT,CodomainT,
		              Traits,Interval,Compare,Alloc>& object,
	const typename 
	      IntervalMap<DomainT,CodomainT,
	                  Traits,Interval,Compare,Alloc>::interval_type& operand
)
{
	typedef IntervalMap<DomainT,CodomainT,
		                Traits,Interval,Compare,Alloc> object_type;
	object_type intersection;
    object.add_intersection(intersection,operand);
	object.swap(intersection);
	return object;
}

//-----------------------------------------------------------------------------
// is_disjoint
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
		object.add_intersection(intersection, *it++);
		if(!intersection.empty())
			return false;
	}

	return true; 
}


} // namespace itl

#endif


