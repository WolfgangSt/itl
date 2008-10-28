/*----------------------------------------------------------------------------+
Copyright (c) 2008-2008: Joachim Faulhaber
+-----------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+----------------------------------------------------------------------------*/
#ifndef __itl_interval_maps_h_JOFA_081008__
#define __itl_interval_maps_h_JOFA_081008__

#include <boost/itl/interval_base_map.hpp>
#include <boost/itl/interval_map_algo.hpp>

namespace boost{namespace itl
{

template
<    
    class, class, class, template<class>class, 
    template<class>class, template<class>class
>
class interval_map;


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
// Addition (+=) of a base value pair.
/* Addition of an value pair <tt>x=(I,y)</tt>

    This adds (inserts) a value <tt>y</tt> for an interval <tt>I</tt> into the 
	map, identical member function add. 

    If no values are associated already within the range of <tt>I</tt>,
    <tt>y</tt> will be associated to that interval.

    If there are associated values, in the range of <tt>I</tt>, then all
    those values within the ranges of their intervals,
    are incremented by <tt>y</tt>. This is done via operator <tt>+=</tt>
    which has to be implemented for CodomainT. 
*/
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
// Subtraction of an interval value pair
/* Subtraction of an interval value pair  <tt>x=(I,y)</tt>.
    This subtracts a value <tt>y</tt> for an interval <tt>I</tt> from the map.

    If there are associated values, in the range of <tt>I</tt>, all
    those values within the ranges of their intervals,
    are decremented by <tt>y</tt>. This is done usign operator -=.

    If <tt>y</tt> becomes the neutral element CodomainT() <tt>k</tt> will
    also be removed from the map, if the Traits include the property 
    neutron_absorber. 
*/
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
// insert  
//-----------------------------------------------------------------------------
template 
<
    class SubType, class DomainT, class CodomainT,
    class Traits, template<class>class Interval, 
    template<class>class Compare, template<class>class Alloc,
    class OperandT
>
interval_base_map<SubType,DomainT,CodomainT,Traits,Interval,Compare,Alloc>& 
insert
(
          interval_base_map<SubType,DomainT,CodomainT,
                            Traits,Interval,Compare,Alloc>& object,
    const OperandT& operand
)
{
    const_FORALL(typename OperandT, elem_, operand) 
        object.insert(*elem_); 
    return object;
}

//-----------------------------------------------------------------------------
// erase  
//-----------------------------------------------------------------------------
template 
<
    class SubType, class DomainT, class CodomainT,
    class Traits, template<class>class Interval, 
    template<class>class Compare, template<class>class Alloc,
    class OperandT
>
interval_base_map<SubType,DomainT,CodomainT,Traits,Interval,Compare,Alloc>& 
erase
(
          interval_base_map<SubType,DomainT,CodomainT,
                            Traits,Interval,Compare,Alloc>& object,
    const OperandT& operand
)
{
    const_FORALL(typename OperandT, elem_, operand) 
        object.erase(*elem_); 
    return object;
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
	return Map::is_element_equal(object, operand);
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

    typename operand_type::const_iterator common_lwb;
    typename operand_type::const_iterator common_upb;

    if(!Set::common_range(common_lwb, common_upb, operand, object))
        return true;

    typename operand_type::const_iterator it = common_lwb;
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

    typename operand_type::const_iterator common_lwb;
    typename operand_type::const_iterator common_upb;

    if(!Set::common_range(common_lwb, common_upb, operand, object))
        return true;

    typename operand_type::const_iterator it = common_lwb;
    while(it != common_upb)
    {
        object.add_intersection(intersection, operand_type::key_value(it++));
        if(!intersection.empty())
            return false;
    }

    return true; 
}

}} // namespace itl boost

#endif


