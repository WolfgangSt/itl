/*----------------------------------------------------------------------------+
Copyright (c) 2007-2008: Joachim Faulhaber
+-----------------------------------------------------------------------------+
Copyright (c) 1999-2006: Cortex Software GmbH, Kantstrasse 57, Berlin
+-----------------------------------------------------------------------------+
Boost Software License - Version 1.0 - August 17th, 2003

Permission is hereby granted, free of charge, to any person or organization
obtaining a copy of the software and accompanying documentation covered by
this license (the "Software") to use, reproduce, display, distribute,
execute, and transmit the Software, and to prepare derivative works of the
Software, and to permit third-parties to whom the Software is furnished to
do so, all subject to the following:

The copyright notices in the Software and this entire statement, including
the above license grant, this restriction and the following disclaimer,
must be included in all copies of the Software, in whole or in part, and
all derivative works of the Software, unless such copies or derivative
works are solely in the form of machine-executable object code generated by
a source language processor.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
+----------------------------------------------------------------------------*/
#ifndef __split_interval_set_JOFA_990223__
#define __split_interval_set_JOFA_990223__

#include <itl/interval_set.hpp>


namespace itl
{

/// implements a set as a set of intervals - bordering interval bounds are not merged
/**    
    Template-class <b>split_interval_set</b> 
    implements a set as a set of intervals - bordering interval bounds are not merged

    Template parameter <b>DomainT</b>: The set's domain-type. Type of the 
    set's elements.
    
    Suitable as domain types are all datatypes that posess a partial order.
    In particular all discrete atomic datatypes like <tt>int, short, long</tt> and
    atomic pseudo-continuous datatypes <tt>float, double</tt> may be instantiated.
    
      Template parameter <b>IntervT=interval<DomainT></b>: Type of interval used
    to implement the set. The default <b>interval<DomainT></b> uses the
    interval class that comes with this library. Own implementation of interval
    classes are possible (but not trivial).

    <b>split_interval_set</b> implements a set <tt>SetT<DomainT></tt> as a set of intervals
    <tt>SetT<interval<DomainT>></tt>. Intervals will not be <b>not</b> merged on 
    insertion, if they border each other or overlap. The inserted intervalls will be
    be preserved and hence kept <b>disc</b>rete. So the calss is called <b>Disc</b>interval_set.
  
    interval_base_set<DomainT> can thus be used like a set. As it is known from mathematics
    the union over a set of intervls is a set itself.

    <b>Class <tt>interval_set</tt> yields the following benefits: </b>
  
    <ul>
        <li> 
            A set of intervals is conceived as a set. The complexity involved with
            operations on intervals and sets of intervals is encapsulated.
            The user of the class who
            wants to perform set operations on sets of intervals is no more concerned
            with questions of overlapping, joining and bordering intervals.
        <li>
            <b>interval_set</b> gives an efficient implementation of sets consisting
            of larger contiguous chunks. Very large, even uncountably infinite sets of
            elements can be represented in a compact way and handled efficiently.
    </ul>

    <b>Restrictions: </b>
    
    A small number of functions can only be used for <b>discrete</b> domain datatypes 
    (<tt>short, int, Date</tt> etc.) that implement operators <tt>++</tt> and <tt>--</tt>.
    These functions are tagged in the documentation.

    @author  Joachim Faulhaber

*/
template 
<
    typename             DomainT, 
    template<class>class Interval = itl::interval,
    template<class>class Compare  = std::less,
    template<class>class Alloc    = std::allocator
> 
class split_interval_set: public interval_base_set<DomainT,Interval,Compare,Alloc>
{
public:
    // inherit all typedefs
    typedef interval_base_set<DomainT,Interval,Compare,Alloc> base_type;

    //PORT: The following types should be intereted from the base class
    // which does work with mscv++ but gcc complaines
    typedef Interval<DomainT> interval_type;
    typedef typename base_type::iterator iterator;
    typedef typename itl::set<interval_type,exclusive_less,Alloc> ImplSetT;

    // B: Constructors, destructors, assignment
    /// Default constructor for the empty set 
    split_interval_set(): base_type() {}
    /// Copy constructor
    split_interval_set(const split_interval_set& src): base_type(src) {}
    /// Constructor for a single interval
    explicit split_interval_set(const interval_type& itv): base_type() { insert(itv); }
    
    /// Virtual constructor
    virtual base_type* cons()const { return new split_interval_set<DomainT,Interval,Compare,Alloc>; }

    /// Does the set contain the interval  <tt>x</tt>?
    virtual bool contains(const interval_type& x)const;


    /// Insertion of an interval <tt>x</tt>
    virtual void insert(const interval_type&);

    /// Subtraction of an interval <tt>x</tt>
    virtual void subtract(const interval_type& x);

    /// Treatment of adjoint intervals on insertion
    virtual void handle_neighbours(const iterator& it){}

    void toItvSetT(interval_set<DomainT,Interval,Compare,Alloc>& dst)const
    { dst.clear(); const_FORALL(typename ImplSetT, it, this->_set) dst.insert(*it); }

    /// Maximum DiscItvSet representing 'always' as good as possible
    static split_interval_set always()    { return split_interval_set(interval_type::always()); }
} ;



template <typename DomainT, template<class>class Interval, template<class>class Compare, template<class>class Alloc>
bool split_interval_set<DomainT,Interval,Compare,Alloc>::contains(const interval_type& x)const
{
    if(x.empty()) return true;

    typename ImplSetT::const_iterator fst_it = this->_set.lower_bound(x);
    typename ImplSetT::const_iterator end_it = this->_set.upper_bound(x);

    interval_set<DomainT,Interval,Compare,Alloc> matchSet;
    for(typename ImplSetT::const_iterator it=fst_it; it!=end_it; it++) matchSet.insert(*it);

    interval_set<DomainT,Interval,Compare,Alloc> x_asSet; x_asSet.insert(x);
    return x_asSet.contained_in(matchSet);
}



template <typename DomainT, template<class>class Interval, template<class>class Compare, template<class>class Alloc>
void split_interval_set<DomainT,Interval,Compare,Alloc>::insert(const interval_type& x)
{
#ifdef _DEV_TEST
    interval_set<DomainT,Interval,Compare,Alloc> clone; toItvSetT(clone);
#endif

    base_type::insert(x);

#ifdef _DEV_TEST
    ON_DEV_TEST(clone.insert(x);)
    DEV_ASSERT(isEqual(clone))
#endif
}


template <typename DomainT, template<class>class Interval, template<class>class Compare, template<class>class Alloc>
void split_interval_set<DomainT,Interval,Compare,Alloc>::subtract(const interval_type& x)
{
#ifdef _DEV_TEST
    interval_set<DomainT,Interval,Compare,Alloc> clone; toItvSetT(clone);
#endif

    base_type::subtract(x);
#ifdef _DEV_TEST
    ON_DEV_TEST(clone.subtract(x);)
    DEV_ASSERT(isEqual(clone))
#endif
}


/** Equality on discrete interval sets. Discrete interval sets are equal, if
    their elements are equal and their fragmentation is equal.
    NOTE: This is not inline with the mathematical view.
    We have a distiction between 'element equality' and 'lexicographical 
    equality'.    */
template <typename DomainT, template<class>class Interval, template<class>class Compare, template<class>class Alloc>
inline bool operator == (const split_interval_set<DomainT,Interval,Compare,Alloc>& lhs,
                         const split_interval_set<DomainT,Interval,Compare,Alloc>& rhs)
{
    return std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <typename DomainT, template<class>class Interval, template<class>class Compare, template<class>class Alloc>
inline bool is_element_equal(const split_interval_set<DomainT,Interval,Compare,Alloc>& lhs,
                             const split_interval_set<DomainT,Interval,Compare,Alloc>& rhs)
{
    split_interval_set<DomainT,Interval,Compare,Alloc> lhs_joined = lhs, rhs_joined = rhs;
    lhs_joined.join(); rhs_joined.join();
    return std::equal(lhs_joined.begin(), lhs_joined.end(), rhs_joined.begin());
}

template <typename DomainT, template<class>class Interval, template<class>class Compare, template<class>class Alloc>
inline bool operator < (const split_interval_set<DomainT,Interval,Compare,Alloc>& lhs,
                        const split_interval_set<DomainT,Interval,Compare,Alloc>& rhs)
{
    split_interval_set<DomainT,Interval,Compare,Alloc> lhs_joined = lhs, rhs_joined = rhs;
    lhs_joined.join(); rhs_joined.join();
    return std::lexicographical_compare(
        lhs_joined.begin(), lhs_joined.end(), 
        rhs_joined.begin(), rhs_joined.end(), 
        Compare<Interval<DomainT> >());
}


} // namespace itl

#endif



