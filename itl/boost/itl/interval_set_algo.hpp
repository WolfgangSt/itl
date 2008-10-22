/*----------------------------------------------------------------------------+
Copyright (c) 2008-2008: Joachim Faulhaber
+-----------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+----------------------------------------------------------------------------*/
#ifndef __itl_interval_set_algo_JOFA_081005_H__
#define __itl_interval_set_algo_JOFA_081005_H__

#include <boost/itl/notate.hpp>

namespace boost{namespace itl
{

template <class IntervalContainerT>
typename IntervalContainerT::size_type continuous_cardinality(const IntervalContainerT& object)
{
	typedef typename IntervalContainerT::size_type size_type;

	size_type size = neutron<size_type>::value();
	size_type interval_size;
    const_FORALL(IntervalContainerT, it, object)
	{
		interval_size = IntervalContainerT::key_value(it).continuous_cardinality();
		if(interval_size == std::numeric_limits<size_type>::infinity())
			return interval_size;
		else
			size += interval_size;
	}
    return size;
}

template <class IntervalContainerT>
typename IntervalContainerT::size_type discrete_cardinality(const IntervalContainerT& object)
{
	typedef typename IntervalContainerT::size_type size_type;

	size_type size = neutron<size_type>::value();
    const_FORALL(IntervalContainerT, it, object)
		size += IntervalContainerT::key_value(it).discrete_cardinality();
    return size;
}

struct continuous_interval_container
{
	template<class IntervalContainerT> 
	static typename IntervalContainerT::size_type 
		cardinality(const IntervalContainerT& cont) 
	{ return continuous_cardinality(cont); }
};

struct discrete_interval_container
{
	template<class IntervalContainerT> 
	static typename IntervalContainerT::size_type 
		cardinality(const IntervalContainerT& cont) 
	{ return discrete_cardinality(cont); }
};


template<class IntervalSetT>
typename IntervalSetT::interval_type 
enclosure(const IntervalSetT& object)
{
	typedef typename IntervalSetT::interval_type interval_type;
    return 
		object.empty() ? itl::neutron<interval_type>::value()
        : IntervalSetT::key_value(object.begin())
		  .span(IntervalSetT::key_value(object.rbegin()));
}
    

	
}} // namespace itl boost

#endif 

