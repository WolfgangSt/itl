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

/*----------------------------------------------------------------------------+
class interval_base_set
+----------------------------------------------------------------------------*/
#ifndef __interval_base_set_h_JOFA_990223__
#define __interval_base_set_h_JOFA_990223__

#include <limits>
#include <itl/itl_set.hpp>
#include <itl/itl_interval.hpp>
#include <itl/notate.hpp>


#define const_FOR_IMPL(iter) for(typename ImplSetT::const_iterator iter=_set.begin(); (iter)!=_set.end(); (iter)++)
#define FOR_IMPL(iter) for(typename ImplSetT::iterator iter=_set.begin(); (iter)!=_set.end(); (iter)++)


namespace itl
{

//JODO update documentation (all invterval containers; template parameters have changed)
/// Implements a set as a set of intervals (base class)
/**    
    Abstract template-class <b>interval_base_set</b> 
    implements a set as a set of intervals

    Template parameter <b>DomainT</b>: The set's domain-type. Type of the 
    set's elements.

    Suitable as domain types are all datatypes that posess a partial order.
    In particular all discrete atomic datatypes like <tt>int, short, long</tt> and
    atomic pseudo-continuous datatypes <tt>float, double</tt> may be instantiated.
    
      Template parameter <b>Interval=itl::interval</b>: Type of interval used
    to implement the set. The default <b>itl::interval</b> uses the
    interval class template that comes with this library. Own implementation of interval
    classes are possible (but not trivial).

    <b>interval_base_set</b> implements a set <tt>set<DomainT></tt> as a set of intervals
    <tt>set<interval<DomainT>></tt>.
  
    interval_base_set<DomainT> can thus be used like a set. As it is known from mathematics
    the union over a set of intervls is a set itself.

    <b>Class <tt>interval_base_set</tt> yields the following benefits: </b>
  
    <ul>
        <li> 
            A set of intervals is conceived as a set. The complexity involved with
            operations on intervals and sets of intervals is encapsulated.
            The user of the class who
            wants to perform set operations on sets of intervals is no more concerned
            with questions of overlapping, joining and bordering intervals.
        <li>
            <b>interval_base_set</b> gives an efficient implementation of sets consisting
            of larger contiguous chunks. Very large, even uncountably infinite sets of
            elements can be represented in a compact way and handled efficiently.
    </ul>

    <b>Restrictions: </b>
    
    A small number of functions can only be used for <b>discrete</b> domain datatypes 
    (<tt>short, int, Date</tt> etc.) that implement operators <tt>++</tt> and <tt>--</tt>.

    These functions are tagged in the documentation. Using such functions
    for continuous domain datatypes yields compiletime errors. C.f. getting
    the <tt>first()</tt> element of a left open interval makes sense for intervals of
    int but not for intervals of double.

    @author  Joachim Faulhaber
*/
template 
<
    typename             SubType,
    typename             DomainT, 
    template<class>class Interval = itl::interval,
    template<class>class Compare  = std::less,
    template<class>class Alloc    = std::allocator
> 
#ifdef USE_CONCEPTS
    requires {std::LessThanComparable<DomainT>}
#endif
class interval_base_set
{
public:

    //A: Type definitions for the template class 

    /// The designated \e derived or \e sub_type of this base class
    typedef SubType sub_type;

    /// The domain type of the set
    typedef DomainT   domain_type;
    /// The codomaintype is the same as domain_type
    typedef DomainT   codomain_type;

    /// The interval type of the set
    typedef Interval<DomainT> interval_type;

    /// Comparison functor for domain values
    typedef Compare<DomainT> domain_compare;
    /// Comparison functor for intervals
    typedef exclusive_less<interval_type> interval_compare;

    /// Comparison functor for keys
    typedef exclusive_less<interval_type> key_compare;

    /// The allocator type of the set
    typedef Alloc<interval_type> allocator_type;

    /// allocator type of the corresponding element set
    typedef Alloc<DomainT> domain_allocator_type;

    /// The type of the set of elements that is equivalent to the set of intervals
    typedef typename itl::set<DomainT,Compare,Alloc> element_set;

    /// The corresponding atomized type representing this ineterval container of elements
    typedef typename itl::set<DomainT,Compare,Alloc> atomized_type;

    /// Container type for the implementation 
    typedef typename itl::set<interval_type,exclusive_less,Alloc> ImplSetT;

    /// key type of the implementing container
    typedef typename ImplSetT::key_type   key_type;
    /// data type of the implementing container
    typedef typename ImplSetT::data_type  data_type;
    /// value type of the implementing container
    typedef typename ImplSetT::value_type value_type;

    /// iterator for iteration over intervals
    typedef typename ImplSetT::iterator iterator;
    /// const_iterator for iteration over intervals
    typedef typename ImplSetT::const_iterator const_iterator;


    // B: Constructors, destructors, assignment
    /// Default constructor for the empty set 
    interval_base_set(){}
    /// Copy constructor
    interval_base_set(const interval_base_set& src): _set(src._set) {}

    /// Assignment operator
    interval_base_set& operator = (const interval_base_set& src) 
    { 
        _set.ImplSetT::operator=(src._set);
        return *this;  
    }

    // ------------------------------------------------------------------------
    // Basic set concept
    // C:

    /// sets the container empty
    void clear() { _set.clear(); }
    /// is the container empty
    bool empty()const { return _set.empty(); }

    void swap(interval_base_set& x) { _set.swap(x._set); }

    /// does the container contain the element \c x
    bool contains(const DomainT& x)const
    {
        typename ImplSetT::const_iterator it = _set.find(interval_type(x)); 
        return it != _set.end(); 
    }

    /** Is <tt>*this</tt> contained in <tt>super</tt>? */
    bool contained_in(const interval_base_set& super)const;

    /** Does <tt>*this</tt> container contain <tt>sub</tt>? */
    bool contains(const interval_base_set& sub)const { return sub.contained_in(*this); }



/** @name E: Bounds and other selectors
    */
//@{ 
    /// lower bound of all intervals in the set
    DomainT lower()const { return (*(_set.begin())).lower(); }
    /// upper bound of all intervals in the set
    DomainT upper()const { return (*(_set.rbegin())).upper(); }

    /// first (smallest) interval in the set
    interval_type first_interval()const { return (*(_set.begin())); }
    /// last (largest) interval in the set
    interval_type last_interval()const { return (*(_set.rbegin())); }

    /// enclosing Interval
    interval_type enclosure()const { return first_interval().span(last_interval()); }

    /// number of intervals
    size_t interval_count()const { return _set.size(); }
    size_t iterative_size()const { return _set.size(); }
//@}


/** @name F: Tester
    */
//@{
    /// Equality
    bool equal(const interval_base_set& x2)const
    { return contained_in(x2) && x2.contained_in(*this); }

    ///  <tt>*this</tt> and <tt>x2</tt> are disjoint; their intersection is empty.
    bool disjoint_to(const interval_base_set& x2)const;

    ///  <tt>*this</tt> and <tt>x2</tt> are disjoint; their intersection is empty.
    bool disjoint_to(const interval_type& x2)const;
//@}


//-----------------------------------------------------------------------------
/** @name G.add: Addition */
//@{

    /// Add a single element \c x to the set
    void add(const DomainT& x) { insert(x); }

    /// Add an interval of elements \c x to the set
    void add(const value_type& x) { that()->insert(x); }

    /// Add an interval of elements \c x to the set
    interval_base_set& operator += (const DomainT& x) 
    { insert(x); return *this; }

    /// Add an interval of elements \c x to the set
    interval_base_set& operator += (const value_type& x) 
    { that()->insert(x); return *this; }

//@}

//-----------------------------------------------------------------------------
/** @name G.sub: Subtraction */
//@{

    /// Subtract a single element \c x from the set
    void subtract(const DomainT& x) 
    { subtract(interval_type(x)); }

    /// Subtract an interval of elements \c x from the set
    void subtract(const value_type& x) 
    { that()->subtract(x); }

    /// Subtract a single element \c x from the set
    interval_base_set& operator -= (const DomainT& x) 
    { subtract(x); return *this; }

    /// Subtract an interval of elements \c x from the set
    interval_base_set& operator -= (const value_type& x)
    { that()->subtract(x); return *this; }

//@}

//-----------------------------------------------------------------------------
/** @name G.ins&ers: Insertion and erasure  */
//@{
    /// Insert an element \c x into the set
    void insert(const DomainT& x) { insert(interval_type(x)); }

    /// Insert an interval of elements \c x to the set
    void insert(const value_type& x) { that()->insert(x); }

    /// Erase an element \c x from the set
    void erase(const DomainT& x) 
    { subtract(interval_type(x)); }

    /// Erase an interval of element \c x from the set
    void erase(const value_type& x) 
    { that()->subtract(x); }
//@}

//-----------------------------------------------------------------------------
/** @name G.sect: Intersection */
//@{

    /** Intersection with interval x; The intersection is assigned to <tt>section</tt>. 
    
        Intersection also serves a generalized <tt>find</tt>-function to search
        for intervals in the set:

        <tt>ItvSetT<int> x, sec; interval<int> i; fill x; fill i;</tt>

        <tt>x.intersect(sec,i);</tt> 
        
        If <tt>i</tt> is an interval of <tt>x</tt>, then 
        
        <tt>sec.nOfIntervals()==1</tt> and <tt>*(sec.begin())==x</tt> 
    */
    void intersect(interval_base_set& section, const value_type& x)const;

    /** Perform intersection of <tt>*this</tt> and <tt>x</tt>; assign result
        to <tt>section</tt>
    */
    void intersect(interval_base_set& section, const interval_base_set& x)const;

    interval_base_set& operator *= (const value_type& x)
    {
        interval_base_set section;
        intersect(section, x); 
        section._set.swap(_set);
        return *this;
    }


    /** Perform intersection of <tt>*this</tt> and <tt>x</tt>; assign result
        to <tt>*this</tt>

        Aufruf <tt>x *= y</tt> bedeutet <tt>x = x geschnitten mit y </tt>
    */
    interval_base_set& operator *= (const interval_base_set& x);
//@}

//-----------------------------------------------------------------------------
/** @name G.jodo: JODO */

    /// Union with set <tt>x</tt>
    interval_base_set& operator +=(const interval_base_set& x)
    { 
        const_FORALL(typename ImplSetT, it, x._set) insert(*it); 
        return *this; 
    }

    /// Perform set difference with the set <tt>x</tt>
    interval_base_set& operator -= (const interval_base_set& x)
    { 
        const_FORALL(typename ImplSetT, it, x._set) subtract(*it); 
        return *this; 
    }

    /// Join bordering intervals    
    interval_base_set& join();

    interval_base_set& scale_up(DomainT factor, DomainT max)
    { 
        FORALL(typename ImplSetT, it, _set) 
            (const_cast<interval_type&>(*it)).scale_up(factor, max); 
        return *this; 
    }
    
    interval_base_set& scale_up(const interval_base_set& src, DomainT factor, DomainT max);

    interval_base_set& scale_down(DomainT factor)
    { 
        FORALL(typename ImplSetT, it, _set) 
            (const_cast<interval_type&>(*it)).scale_down(factor); 
        return *this; 
    }
    
    interval_base_set& scale_down(const interval_base_set& src, DomainT factor);
//@}



/** @name I: Interval iterators
    */
//@{
    ///
    iterator begin() { return _set.begin(); }
    ///
    iterator end()   { return _set.end(); }
    ///
    const_iterator begin()const { return _set.begin(); }
    ///
    const_iterator end()const   { return _set.end(); }
//@}



/** @name S: String representation
    */
//@{
    /// Interval-set as string
    const std::string as_string()const
    { std::string res(""); const_FOR_IMPL(it) res += (*it).as_string(); return res; }
//@}

    
/** @name T: For discrete domain datatypes only that implement operators <tt>++</tt> 
        and <tt>--</tt>
    */
//@{
    /** Smallest element of the set (wrt. the partial ordering on DomainT).
        first() does not exist for continuous datatypes and open interval bounds.
    */
    DomainT first()const { return (*(_set.begin())).first(); }  // JODO NONCONT

    /** Largest element of the set (wrt. the partial ordering on DomainT).
        first() does not exist for continuous datatypes and open interval bounds.
    */
    DomainT last()const { return (*(_set.rbegin())).last(); } // JODO NONCONT

    // JODO TEST
    /** Number of elements in the set (cardinality). 
        Infinite for continuous domain datatyps
        <b>Nicht getestet</b>
    */
    DomainT size()const;

    /**    Set interval bounds to the type <tt>bt</tt> for intervals in the set.

        Interval bounds of different types are created by opeations on
        interval sets. This function allows to reset them uniformly without,
        of course, changing their value. This is only possible for discrete
        domain datatypes.
    */
    void uniform_bounds(typename interval<DomainT>::bound_types bt);

//@}


    template<typename IteratorT>
    static const key_type& key_value(IteratorT& value_){ return (*value_); }

    template<typename IteratorT>
    static codomain_type codomain_value(IteratorT& value_)
    { return (*value_).empty()? codomain_type() : (*value_).first(); }

    template<typename LeftIterT, typename RightIterT>
    static bool key_less(LeftIterT& lhs_, RightIterT& rhs_) 
    { return key_compare()(*lhs_, *rhs_); }

    static value_type make_domain_element(const domain_type& dom_val, const codomain_type& codom_val)
    { return value_type(interval_type(dom_val)); }


    // TESTCODE KEEP
    void to_set(element_set& s)const
    { const_FOR_IMPL(it) for(DomainT i=(*it).first(); i<=last(); i++) s.insert(i); } // JODO NONCONT 

    bool equal(element_set& x2)const
    { element_set x1; to_set(x1); return x1.contained_in(x2) && x2.contained_in(x1); }

protected:
    sub_type* that() { return static_cast<sub_type*>(this); }
    const sub_type* that()const { return static_cast<const sub_type*>(this); }

protected:
    ImplSetT _set;
} ;


template<class SubType,
         class DomainT, template<class>class Interval, template<class>class Compare, template<class>class Alloc>
DomainT interval_base_set<SubType,DomainT,Interval,Compare,Alloc>::size()const
{
    DomainT size = DomainT();
    const_FOR_IMPL(it) size += (*it).size();
    return size;
}


template<class SubType,
         class DomainT, template<class>class Interval, template<class>class Compare, template<class>class Alloc>
bool interval_base_set<SubType,DomainT,Interval,Compare,Alloc>::contained_in(const interval_base_set& x2)const
{
    // The empty set is subset of every set
    if(empty())
        return true;
    else if (x2.empty())
        return false;
    else if(last() < x2.first())
        return false;
    else if(x2.last() < first())
        return false;
    else
    {
        // x2 should be larger than *this; so every element in this should be in x2
        const_FOR_IMPL(it) 
            if(!x2.that()->contains(*it)) 
                return false;
        return true;
    }
}



template<class SubType,
         class DomainT, template<class>class Interval, template<class>class Compare, template<class>class Alloc>
bool interval_base_set<SubType,DomainT,Interval,Compare,Alloc>::disjoint_to(const interval_type& x)const
{
    interval_base_set<SubType,DomainT,Interval,Compare,Alloc> section;
    intersect(section, x);
    return section->empty();
}

template<class SubType,
         class DomainT, template<class>class Interval, template<class>class Compare, template<class>class Alloc>
bool interval_base_set<SubType,DomainT,Interval,Compare,Alloc>::disjoint_to(const interval_base_set& x)const
{
    interval_base_set<SubType,DomainT,Interval,Compare,Alloc> section;
    intersect(section, x);
    return section->empty();
}


template<class SubType,
         class DomainT, template<class>class Interval, template<class>class Compare, template<class>class Alloc>
void interval_base_set<SubType,DomainT,Interval,Compare,Alloc>::intersect(interval_base_set& section, const value_type& x)const
{
    section.clear();
    // any intersection with the empty intervall is empty
    if(x.empty()) return;

    typename ImplSetT::const_iterator fst_it = _set.lower_bound(x);
    typename ImplSetT::const_iterator end_it = _set.upper_bound(x);

    for(typename ImplSetT::const_iterator it=fst_it; it != end_it; it++) {
        interval_type isec; (*it).intersect(isec, x);
        section.insert(isec);
    }
}


template<class SubType,
         class DomainT, template<class>class Interval, template<class>class Compare, template<class>class Alloc>
void interval_base_set<SubType,DomainT,Interval,Compare,Alloc>::intersect(interval_base_set& interSection, 
                                            const interval_base_set& x)const
{
    interSection.clear();
    if(x.empty()) return;

    interval_base_set<SubType,DomainT,Interval,Compare,Alloc> aux;
    const_FORALL(typename ImplSetT, it, x._set)
    {
        intersect(aux, *it);
        interSection += aux;
    }
}


template<class SubType,
         class DomainT, template<class>class Interval, template<class>class Compare, template<class>class Alloc>
interval_base_set<SubType,DomainT,Interval,Compare,Alloc>& 
    interval_base_set<SubType,DomainT,Interval,Compare,Alloc>::operator *= (const interval_base_set& x)
{
    interval_base_set<SubType,DomainT,Interval,Compare,Alloc> section;
    intersect(section, x);
    section._set.swap(_set);
    return *this;
}





template<class SubType,
         class DomainT, template<class>class Interval, template<class>class Compare, template<class>class Alloc>
interval_base_set<SubType,DomainT,Interval,Compare,Alloc>& interval_base_set<SubType,DomainT,Interval,Compare,Alloc>::join()
{
    iterator it=_set.begin();
    if(it==_set.end()) 
        return *this;

    iterator nxt=it; nxt++;
    if(nxt==_set.end()) 
        return *this;

    while(nxt != _set.end())
    {
        if( (*it).touches(*nxt) )
        {
            iterator fst_mem = it;  // hold the fist member
            
            // go noodling on while touchin members found
            it++; nxt++;
            while(     nxt != _set.end()
                    && (*it).touches(*nxt) )
            { it++; nxt++; }

            // finally we arrive at the end of a sequence of joinable intervals
            // and it points to the last member of that sequence
            iterator lst_mem = it, end_mem = nxt;
            interval_type joinedInterval(*fst_mem);
            joinedInterval.extend(*lst_mem);
            
            _set.erase(fst_mem, end_mem);
            it = _set.insert(joinedInterval).ITERATOR;

            it++; // go on for the next after the currently inserted
            nxt=it; if(nxt!=_set.end())nxt++;
        }
        else { it++; nxt++; }
    }
    return *this;
}



template<class SubType,
         class DomainT, template<class>class Interval, template<class>class Compare, template<class>class Alloc>
void interval_base_set<SubType,DomainT,Interval,Compare,Alloc>::uniform_bounds(typename interval<DomainT>::bound_types bt)
{
    // I can do this only, because I am shure that the contents and the
    // ordering < on interval is invariant wrt. this transformation on bounds
    FOR_IMPL(it) const_cast<interval_type&>(*it).transform_bounds(bt);
}


template<class SubType,
         class DomainT, template<class>class Interval, template<class>class Compare, template<class>class Alloc>
interval_base_set<SubType,DomainT,Interval,Compare,Alloc>& interval_base_set<SubType,DomainT,Interval,Compare,Alloc>::scale_up(const interval_base_set& src, DomainT factor, DomainT max)
{ 
    clear();
    const_FORALL(typename interval_base_set, it, src)
    {
        interval_type itv = *it;
        itv.scale_up(factor, max);
        _set.insert(itv);
    }
    return *this;
}

template<class SubType,
         class DomainT, template<class>class Interval, template<class>class Compare, template<class>class Alloc>
interval_base_set<SubType,DomainT,Interval,Compare,Alloc>& interval_base_set<SubType,DomainT,Interval,Compare,Alloc>::scale_down(const interval_base_set& src, DomainT factor)
{ 
    clear();
    const_FORALL(typename interval_base_set, it, src)
    {
        interval_type itv = *it;
        itv.scale_down(factor);
        _set.insert(itv); //JODO THINK Preconditions
    }
    return *this;
}



template<class SubType,
         class DomainT, template<class>class Interval, template<class>class Compare, template<class>class Alloc>
inline bool operator == (const interval_base_set<SubType,DomainT,Interval,Compare,Alloc>& lhs,
                         const interval_base_set<SubType,DomainT,Interval,Compare,Alloc>& rhs)
{
    //MEMO PORT: This implemetation worked with stlport, sgi and gnu 
    // implementations of the stl. But using MSVC-implementation
    // results in runtime error! So I had to provide an independent
    // safe implemetation.
    //return std::equal(lhs.begin(), lhs.end(), rhs.begin());
    return Set::lexicographical_equal(lhs, rhs);
}

template<class SubType,
         class DomainT, template<class>class Interval, template<class>class Compare, template<class>class Alloc>
inline bool operator < (const interval_base_set<SubType,DomainT,Interval,Compare,Alloc>& lhs,
                        const interval_base_set<SubType,DomainT,Interval,Compare,Alloc>& rhs)
{
    return std::lexicographical_compare(
        lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), Compare<Interval<DomainT> >());
}

template<class SubType,
         class DomainT, template<class>class Interval, template<class>class Compare, template<class>class Alloc>
inline bool operator <= (const interval_base_set<SubType,DomainT,Interval,Compare,Alloc>& lhs,
                         const interval_base_set<SubType,DomainT,Interval,Compare,Alloc>& rhs)
{
    return lhs < rhs || lhs == rhs;
}


template 
<
    class SubType, class DomainT, template<class>class Interval, 
    template<class>class Compare, template<class>class Alloc
>
interval_base_set<SubType,DomainT,Interval,Compare,Alloc>& 
insert(interval_base_set<SubType,DomainT,Interval,Compare,Alloc>& object,
       const interval_base_set<SubType,DomainT,Interval,Compare,Alloc>& 
       insertee)
{
    return object += insertee; 
}
    

template 
<
    class SubType, class DomainT, template<class>class Interval, 
    template<class>class Compare, template<class>class Alloc
>
interval_base_set<SubType,DomainT,Interval,Compare,Alloc>& 
erase(interval_base_set<SubType,DomainT,Interval,Compare,Alloc>& object,
      const interval_base_set<SubType,DomainT,Interval,Compare,Alloc>& 
      erasee)
{
    return object -= erasee;
}




//-----------------------------------------------------------------------------
// addition (set union) += and subtraction (set difference) -=
//-----------------------------------------------------------------------------

template 
<
    class SubType, class DomainT, template<class>class Interval, 
    template<class>class Compare, template<class>class Alloc
>
interval_base_set<SubType,DomainT,Interval,Compare,Alloc>& 
operator +=
(
          interval_base_set<SubType,DomainT,Interval,Compare,Alloc>& object,
    const interval_base_set<SubType,DomainT,Interval,Compare,Alloc>& operand
)
{
    typedef interval_base_set<SubType,DomainT,Interval,Compare,Alloc> set_type;
    const_FORALL(typename set_type, elem_, operand) 
        object.add(*elem_); 

    return object; 
}



} // namespace itl

#endif


