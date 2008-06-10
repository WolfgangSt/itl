/*----------------------------------------------------------------------------+
Copyright (c) 2007-2008: Joachim Faulhaber
+-----------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+----------------------------------------------------------------------------*/
#ifndef __joint_interval_map_h_JOFA_000706__
#define __joint_interval_map_h_JOFA_000706__

#include <itl/interval_base_map.hpp>
#include <itl/interval_set.hpp>

namespace itl
{

/**    
    @author  Joachim Faulhaber
*/
template <typename DomainT, typename CodomainT, typename IntervT=interval<DomainT>, 
          typename CompareT = std::less<DomainT>,
          typename AllocT   = std::allocator<std::pair<const IntervT, CodomainT> > >
class joint_interval_map: public interval_base_map<DomainT,CodomainT,IntervT,CompareT,AllocT>
{
public:
    typedef typename interval_base_map<DomainT,CodomainT,IntervT,CompareT,AllocT> base_type;

    // inherit all typedefs
    joint_interval_map(): base_type() {}
    joint_interval_map(const joint_interval_map& src): base_type(src) {}

    virtual base_type* cons()const
    { return new joint_interval_map(); }

    virtual bool contains(const value_type& x)const;

    virtual void insert(const value_type&);
    virtual void subtract(const value_type& x);

    //JODO joint_interval_map is not completely implemented and not tested
    virtual void handle_neighbours(const iterator& it);

    void toItvSetT(interval_set<DomainT,IntervT,CompareT,AllocT>& dst)const
    { dst.clear(); const_FORALL(ImplMapT, it, _map) dst.insert(*it); }

private:
    iterator joint_insert(const iterator& left_it, const iterator& right_it);
};



template <typename DomainT, typename CodomainT, typename IntervT, typename CompareT, typename AllocT>
bool joint_interval_map<DomainT,CodomainT,IntervT,CompareT,AllocT>::contains(const value_type& x_y)const
{
    IntervT x = x_y.KEY_VALUE;
    if(x.empty()) return true;

    joint_interval_map match_map;
    matchMap(match_map, x_y);

    if(match_map.interval_count() != 1) return false;
    iterator match_it = match_map._map.find(x);
    if(! x.contained_in((*match_it).KEY_VALUE) ) return false;

    return (*match_it).CONT_VALUE==x_y.CONT_VALUE;
}



template <typename DomainT, typename CodomainT, typename IntervT, typename CompareT, typename AllocT>
void joint_interval_map<DomainT,CodomainT,IntervT,CompareT,AllocT>::insert(const value_type& x)
{
    /*
#ifdef _DEBUG
    interval_set<DomainT,IntervT,CompareT,AllocT> clone; toItvSetT(clone);
#endif
    */

    base_type::insert(x);

    // ON_DEBUG(clone.insert(x);)
    // J_ASSERT(isEqual(clone))
}


template <typename DomainT, typename CodomainT, typename IntervT, typename CompareT, typename AllocT>
void joint_interval_map<DomainT,CodomainT,IntervT,CompareT,AllocT>::subtract(const value_type& x)
{
    /*
#ifdef _DEBUG
    interval_set<DomainT,IntervT,CompareT,AllocT> clone; toItvSetT(clone);
#endif
    */

    base_type::subtract(x);

    // ON_DEBUG(clone.subtract(x);)
    // J_ASSERT(isEqual(clone))
}


template <typename DomainT, typename CodomainT, typename IntervT, typename CompareT, typename AllocT>
void joint_interval_map<DomainT,CodomainT,IntervT,CompareT,AllocT>::handle_neighbours(const iterator& it)
{
    DEV_ASSERT(_set.contains(*it));
    IntervT itv = (*it).KEY_VALUE;

    if(it == _map.begin())
    {
        ImplMapT::iterator it_nxt=it; it_nxt++;
        if(it_nxt!=_map.end() && itv.touches((*it_nxt).KEY_VALUE)) 
            joint_insert(it, it_nxt);
    }
    else
    {
        // there is a predecessor
        iterator it_pred = it; it_pred-- ;

        if((*it_pred).KEY_VALUE.touches(itv)) 
        {
            iterator it_extended = joint_insert(it_pred, it);

            iterator it_succ=it_extended; it_succ++;
            if(it_succ!=_map.end())
            {
                // it's a non border element that might have two touching neighbours
                if((*it_extended).KEY_VALUE.touches((*it_succ).KEY_VALUE)) 
                    joint_insert(it_extended, it_succ);
            }
        }
        else
        {
            iterator it_succ=it; it_succ++;
            if(it_succ!=_map.end())
            {
                // it's a non border element that might have a right touching neighbours
                if(itv.touches((*it_succ).KEY_VALUE)) 
                    joint_insert(it, it_succ);
            }
        }
    }
}


template <typename DomainT, typename CodomainT, typename IntervT, typename CompareT, typename AllocT>
    typename joint_interval_map<DomainT,CodomainT,IntervT,CompareT,AllocT>::iterator 
joint_interval_map<DomainT,CodomainT,IntervT,CompareT,AllocT>
    ::joint_insert(const iterator& left_it, const iterator& right_it)
{
    // both left and right are in the set and they are neighbours
    DEV_ASSERT((*left_it).KEY_VALUE.excl_less((*right_it).KEY_VALUE));
    DEV_ASSERT((*left_it).KEY_VALUE.touches((*right_it).KEY_VALUE));

    IntervT curItv = (*left_it).KEY_VALUE;
    curItv.extend((*right_it).KEY_VALUE);

    CodomainT covalue = (*left_it).CONT_VALUE;
    covalue += (*right_it).CONT_VALUE;

    _map.erase(left_it);
    _map.erase(right_it);

    ImplMapT::iterator new_it = _map.insert(value_type(curItv, covalue)).ITERATOR;
    J_ASSERT(new_it!=_map.end());
    return new_it;
}


} // namespace itl

#endif


