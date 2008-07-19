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
#include <itl/interval_base_set.hpp>

namespace itl
{

    /// implements a set as a set of intervals - on insertion overlapping intervals are split
    /**    
        Template-class <b>split_interval_set</b> 
        implements a set as a set of intervals - bordering interval bounds are not merged

        Template parameter <b>DomainT</b>: The set's domain-type. Type of the 
        set's elements.
        
        Suitable as domain types are all datatypes that posess a partial order.
        In particular all discrete atomic datatypes like <tt>int, short, long</tt> and
        atomic pseudo-continuous datatypes <tt>float, double</tt> may be instantiated.
        
          Template parameter <b>Interval=itl::interval</b>: Type of interval used
        to implement the set. The default <b>itl::interval</b> uses the
        interval class template that comes with this library. Own implementation of interval
        classes are possible (but not trivial).

        <b>split_interval_set</b> implements a set <tt>set<DomainT></tt> as a set of intervals
        <tt>set<interval<DomainT>></tt>. Intervals will not be <b>not</b> merged on 
        insertion, if they border each other or overlap. The inserted intervalls will be
        be preserved. 
      
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
	class split_interval_set: 
		public interval_base_set<split_interval_set<DomainT,Interval,Compare,Alloc>, 
		                         DomainT,Interval,Compare,Alloc>
    {
    public:
		typedef interval_base_set<itl::split_interval_set<DomainT,Interval,Compare,Alloc>,
			                      DomainT,Interval,Compare,Alloc> base_type;

		typedef interval_set<DomainT,Interval,Compare,Alloc> joint_type;

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
        split_interval_set(): base_type() {}
        /// Copy constructor
        split_interval_set(const split_interval_set& src): base_type(src) {}
        /// Constructor for a single interval
        explicit split_interval_set(const interval_type& itv): base_type() { insert(itv); }
        


		
        /// Does the set contain the interval  <tt>x</tt>?
        bool contains(const interval_type& x)const;

		/// Insertion of an interval <tt>x</tt>
		void insert(const value_type& x){ recursive_insert(x); }

		/// Removal of an interval <tt>x</tt>
		void subtract(const value_type& x){ recursive_subtract(x); }

        /// Treatment of adjoint intervals on insertion
        void handle_neighbours(const iterator& it){}

	private:
		void recursive_insert(const value_type& x);
		void recursive_subtract(const value_type& x);
		void insert_rest(const interval_type& x_itv, iterator& it, iterator& end_it);
		void subtract_rest(const interval_type& x_itv, iterator& it, iterator& end_it);


    } ;





    template <typename DomainT, template<class>class Interval, template<class>class Compare, template<class>class Alloc>
    bool split_interval_set<DomainT,Interval,Compare,Alloc>::contains(const interval_type& x)const
    {
        if(x.empty()) return true;

        typename ImplSetT::const_iterator fst_it = this->_set.lower_bound(x);
        typename ImplSetT::const_iterator end_it = this->_set.upper_bound(x);

        interval_set<DomainT,Interval,Compare,Alloc> matchSet;
        for(typename ImplSetT::const_iterator it=fst_it; it!=end_it; it++) 
			matchSet.insert(*it);

        interval_set<DomainT,Interval,Compare,Alloc> x_asSet; 
		x_asSet.insert(x);
        return x_asSet.contained_in(matchSet);
    }


    template <typename DomainT, template<class>class Interval, template<class>class Compare, template<class>class Alloc>
    void split_interval_set<DomainT,Interval,Compare,Alloc>::recursive_insert(const value_type& x)
    {
        if(x.empty()) return;

        std::pair<typename ImplSetT::iterator,bool> insertion = this->_set.insert(x);

        if(!insertion.WAS_SUCCESSFUL)
        {
            iterator fst_it = this->_set.lower_bound(x);
            iterator end_it = this->_set.upper_bound(x);

			if(fst_it == this->_set.end())
				fst_it = end_it;

            iterator cur_it       = fst_it ;
            interval_type cur_itv = *cur_it;

            interval_type leadGap; x.left_surplus(leadGap, cur_itv);
            // this is a new Interval that is a gap in the current map
            recursive_insert(leadGap);

            // only for the first there can be a leftResid: a part of *it left of x
            interval_type leftResid;  cur_itv.left_surplus(leftResid, x);

            // handle special case for first
            interval_type interSec;
            cur_itv.intersect(interSec, x);

            iterator snd_it = fst_it; snd_it++;
            if(snd_it == end_it) 
            {
                // first == last

                interval_type endGap; x.right_surplus(endGap, cur_itv);
                // this is a new Interval that is a gap in the current map
                recursive_insert(endGap);

                // only for the last there can be a rightResid: a part of *it right of x
                interval_type rightResid;  (*cur_it).right_surplus(rightResid, x);

                this->_set.erase(cur_it);
                recursive_insert(leftResid);
                recursive_insert(interSec);
                recursive_insert(rightResid);
            }
            else
            {
                this->_set.erase(cur_it);
                recursive_insert(leftResid);
                recursive_insert(interSec);

                // shrink interval
                interval_type x_rest(x);
                x_rest.left_subtract(cur_itv);

                insert_rest(x_rest, snd_it, end_it);
            }
        }
    }


    template <typename DomainT, template<class>class Interval, template<class>class Compare, template<class>class Alloc>
    void split_interval_set<DomainT,Interval,Compare,Alloc>::insert_rest(const interval_type& x_itv, iterator& it, iterator& end_it)
    {
        iterator nxt_it = it; nxt_it++;

        interval_type cur_itv = *it;
        
        interval_type newGap; x_itv.left_surplus(newGap, cur_itv);
        // this is a new Interval that is a gap in the current map
        recursive_insert(newGap);

        interval_type interSec;
        cur_itv.intersect(interSec, x_itv);

        if(nxt_it==end_it)
        {
            interval_type endGap; x_itv.right_surplus(endGap, cur_itv);
            // this is a new Interval that is a gap in the current map
            recursive_insert(endGap);

            // only for the last there can be a rightResid: a part of *it right of x
            interval_type rightResid;  cur_itv.right_surplus(rightResid, x_itv);

            this->_set.erase(it);
            recursive_insert(interSec);
            recursive_insert(rightResid);
        }
        else
        {        
            this->_set.erase(it);
            recursive_insert(interSec);

            // shrink interval
            interval_type x_rest(x_itv);
            x_rest.left_subtract(cur_itv);

            insert_rest(x_rest, nxt_it, end_it);
        }
    }


    template <typename DomainT, template<class>class Interval, template<class>class Compare, template<class>class Alloc>
    void split_interval_set<DomainT,Interval,Compare,Alloc>::recursive_subtract(const value_type& x)
    {
        if(x.empty()) return;
		if(this->_set.empty()) return;

        iterator fst_it;
		if(x.exclusive_less(*(this->_set.begin())))
			return;
		if(x.lower() < this->_set.begin()->upper())
			fst_it = this->_set.begin();
		else
			fst_it = this->_set.lower_bound(x);

        if(fst_it==this->_set.end()) return;
        iterator end_it = this->_set.upper_bound(x);
        if(fst_it==end_it) return;

        iterator cur_it = fst_it ;
        interval_type cur_itv   = *cur_it ;

        // only for the first there can be a leftResid: a part of *it left of x
        interval_type leftResid;  cur_itv.left_surplus(leftResid, x);

        // handle special case for first
        interval_type interSec;
        cur_itv.intersect(interSec, x);

        iterator snd_it = fst_it; snd_it++;
        if(snd_it == end_it) 
        {
            // first == last
            // only for the last there can be a rightResid: a part of *it right of x
            interval_type rightResid;  (*cur_it).right_surplus(rightResid, x);

            this->_set.erase(cur_it);
            recursive_insert(leftResid);
            recursive_insert(rightResid);
        }
        else
        {
            // first AND NOT last
            this->_set.erase(cur_it);
            recursive_insert(leftResid);
            subtract_rest(x, snd_it, end_it);
        }
    }



    template <typename DomainT, template<class>class Interval, template<class>class Compare, template<class>class Alloc>
    void split_interval_set<DomainT,Interval,Compare,Alloc>::subtract_rest(const interval_type& x_itv, iterator& snd_it, iterator& end_it)
    {
        iterator it=snd_it, nxt_it=snd_it; nxt_it++;

        while(nxt_it!=end_it)
        {
            { iterator victim; victim=it; it++; this->_set.erase(victim); }
            nxt_it=it; nxt_it++;
        }

        // it refers the last overlaying intervals of x_itv
        const interval_type&  cur_itv = *it ;

        interval_type rightResid; cur_itv.right_surplus(rightResid, x_itv);

        if(rightResid.empty())
            this->_set.erase(it);
        else
        {
            interval_type interSec; cur_itv.intersect(interSec, x_itv);
            this->_set.erase(it);
            this->_set.insert(rightResid);
        }
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


    template <class Type>
    struct type<itl::split_interval_set<Type> >
    {
    	static bool is_set() { return true; }
		static bool is_interval_container() { return true; }
		static bool is_interval_splitter() { return true; }
		static bool is_neutron_absorber() { return false; }
		static bool is_neutron_emitter() { return false; }


        static std::string to_string()
        { return "sp_itv_set<"+ type<Type>::to_string() +">"; }
    };

} // namespace itl

#endif



