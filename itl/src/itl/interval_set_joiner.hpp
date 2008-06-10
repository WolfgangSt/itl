/*----------------------------------------------------------------------------+
Copyright (c) 2007-2008: Joachim Faulhaber
+-----------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+----------------------------------------------------------------------------*/
#ifndef __itl_interval_set_joiner_h_JOFA_080602__
#define __itl_interval_set_joiner_h_JOFA_080602__

#include <itl/interval_base_set.hpp>
#include <itl/j_assert.hpp>


#define const_FOR_IMPL(iter) for(typename ImplSetT::const_iterator iter=_set.begin(); (iter)!=_set.end(); (iter)++)
#define FOR_IMPL(iter) for(typename ImplSetT::iterator iter=_set.begin(); (iter)!=_set.end(); (iter)++)


namespace itl
{

/// JODO
/**    
	JODO
    @author Joachim Faulhaber
*/
template
<
    typename             DomainT, 
    template<class>class Interval = itl::interval,
    template<class>class Compare  = std::less,
    template<class>class Alloc    = std::allocator
> 
class interval_set_joiner
{
public:
    //PORT: The following types should be intereted from the base class
    // which does work with mscv++ but gcc complaines
	typedef Interval<DomainT> interval_type;

    /// Container type for the implementation 
    typedef typename itl::set<interval_type,exclusive_less,Alloc> ImplSetT;

    /// Container type for the implementation 
    typedef typename ImplSetT::iterator iterator;

    /// key type of the implementing container
    typedef typename ImplSetT::key_type   key_type;
    /// data type of the implementing container
    typedef typename ImplSetT::data_type  data_type;
    /// value type of the implementing container
    typedef typename ImplSetT::value_type value_type;


    /// Virtual constructor JODO
    interval_set_joiner* cons()const; 
    //{ return new interval_set<DomainT,Interval,Compare,Alloc>(); }

    /// Does the set contain the interval  <tt>x</tt>?
    bool contains(const interval_type& x)const;

	/// Insertion of an interval <tt>x</tt>
	void insert(const value_type& x);

	/// Removal of an interval <tt>x</tt>
	void subtract(const value_type& x);

    /// Treatment of adjoint intervals on insertion
    void handle_neighbours(const iterator& it);

protected:
    iterator joint_insert(const iterator& left_it, const iterator& right_it);

protected:
    ImplSetT _set;
};


template <typename DomainT, template<class>class Interval, template<class>class Compare, template<class>class Alloc>
bool interval_set_joiner<DomainT,Interval,Compare,Alloc>::contains(const interval_type& x)const
{ 
    // Emptiness is contained in everything
    if(x.empty()) 
        return true;
    else if (_set.empty())
        return false;
    //else if(x.last() < _set.begin()->first()) //JODO adjust for continuous DomainT-parameters
    //    return false;
    //else if(this->last() < x.first())
    //    return false;
    {
        typename ImplSetT::const_iterator it = this->_set.find(x);
        if(it == this->_set.end())
            return false;
        else
            return x.contained_in(*it);
    }
}


template <typename DomainT, template<class>class Interval, template<class>class Compare, template<class>class Alloc>
void interval_set_joiner<DomainT,Interval,Compare,Alloc>::handle_neighbours(const iterator& it)
{
    interval_type x = *it;

    if(it == this->_set.begin())
    {
        typename ImplSetT::iterator it_nxt=it; it_nxt++;
        if(it_nxt!=this->_set.end() && (*it).touches(*it_nxt)) 
            joint_insert(it, it_nxt);
    }
    else
    {
        // there is a predecessor
        iterator it_pred = it; it_pred-- ;

        if((*it_pred).touches(*it)) 
        {
            iterator it_extended = joint_insert(it_pred, it);

            iterator it_succ=it_extended; it_succ++;
            if(it_succ!=this->_set.end())
            {
                // it's a non border element that might have two touching neighbours
                if((*it_extended).touches(*it_succ)) 
                    joint_insert(it_extended, it_succ);
            }
        }
        else
        {
            iterator it_succ=it; it_succ++;
            if(it_succ!=this->_set.end())
            {
                // it's a non border element that might have a right touching neighbours
                if((*it).touches(*it_succ)) 
                    joint_insert(it, it_succ);
            }
        }
    }
}



template <typename DomainT, template<class>class Interval, template<class>class Compare, template<class>class Alloc>
typename interval_set_joiner<DomainT,Interval,Compare,Alloc>::iterator 
    interval_set_joiner<DomainT,Interval,Compare,Alloc>
    ::joint_insert(const iterator& left_it, const iterator& right_it)
{
    // both left and right are in the set and they are neighbours
    DEV_ASSERT((*left_it).excl_less(*right_it));
    DEV_ASSERT((*left_it).touches(*right_it));

    interval_type curItv = (*left_it);
    curItv.extend(*right_it);

    this->_set.erase(left_it);
    this->_set.erase(right_it);
    
    typename ImplSetT::iterator new_it = this->_set.insert(curItv).ITERATOR;
    J_ASSERT(new_it!=this->_set.end());
    return new_it;
}


template<class DomainT, template<class>class Interval, template<class>class Compare, template<class>class Alloc>
void interval_set_joiner<DomainT,Interval,Compare,Alloc>::insert(const value_type& x)
{
    if(x.empty()) return;

    std::pair<typename ImplSetT::iterator,bool> insertion = _set.insert(x);

    if(insertion.WAS_SUCCESSFUL)
        handle_neighbours(insertion.ITERATOR);
    else
    {
        typename ImplSetT::iterator fst_it = _set.lower_bound(x);
        typename ImplSetT::iterator end_it = _set.upper_bound(x);

        typename ImplSetT::iterator it=fst_it, nxt_it=fst_it, victim;
        Interval<DomainT> leftResid;  (*it).left_surplus(leftResid,x);
        Interval<DomainT> rightResid;

        while(it!=end_it)
        { 
            if((++nxt_it)==end_it) 
				(*it).right_surplus(rightResid,x);
            victim = it; it++; _set.erase(victim);
        }

        Interval<DomainT> extended = x;
        extended.extend(leftResid).extend(rightResid);
        extended.extend(rightResid);
        insert(extended);
    }

}


template<class DomainT, template<class>class Interval, template<class>class Compare, template<class>class Alloc>
void interval_set_joiner<DomainT,Interval,Compare,Alloc>::subtract(const value_type& x)
{
    if(x.empty()) return;
    typename ImplSetT::iterator fst_it = _set.lower_bound(x);
    if(fst_it==_set.end()) return;
    typename ImplSetT::iterator end_it = _set.upper_bound(x);

    typename ImplSetT::iterator it=fst_it, nxt_it=fst_it, victim;
    interval_type leftResid; (*it).left_surplus(leftResid,x);
    interval_type rightResid;

    while(it!=end_it)
    { 
        if((++nxt_it)==end_it) (*it).right_surplus(rightResid,x);
        victim = it; it++; _set.erase(victim);
    }

    insert(leftResid);
    insert(rightResid);
}





} // namespace itl

#endif


