/*----------------------------------------------------------------------------+
Copyright (c) 2007-2008: Joachim Faulhaber
+-----------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+----------------------------------------------------------------------------*/
#ifndef __itl_interval_set_splitter_JOFA_080606__
#define __itl_interval_set_splitter_JOFA_080606__

//CL #include <itl/interval_set.hpp>


namespace itl
{

    /// JODO
    /**    

        @author  Joachim Faulhaber

    */
    template 
    <
        typename             DomainT, 
        template<class>class Interval = itl::interval,
        template<class>class Compare  = std::less,
        template<class>class Alloc    = std::allocator
    > 
    class interval_set_splitter
    {
    public:
        typedef Interval<DomainT> interval_type;

		/// Container type for the implementation 
		typedef typename itl::set<interval_type,exclusive_less,Alloc> ImplSetT;

		typedef typename ImplSetT::iterator iterator;        

		/// key type of the implementing container
		typedef typename ImplSetT::key_type   key_type;
		/// data type of the implementing container
		typedef typename ImplSetT::data_type  data_type;
		/// value type of the implementing container
		typedef typename ImplSetT::value_type value_type;

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

	protected:
		ImplSetT _set;
    } ;



    template <typename DomainT, template<class>class Interval, template<class>class Compare, template<class>class Alloc>
    bool interval_set_splitter<DomainT,Interval,Compare,Alloc>::contains(const interval_type& x)const
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
    void interval_set_splitter<DomainT,Interval,Compare,Alloc>::recursive_insert(const value_type& x)
    {
        if(x.empty()) return;

        std::pair<typename ImplSetT::iterator,bool> insertion = this->_set.insert(x);

        if(!insertion.WAS_SUCCESSFUL)
        {
            iterator fst_it = this->_set.lower_bound(x);
            iterator end_it = this->_set.upper_bound(x);

			if(fst_it == _set.end())
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
    void interval_set_splitter<DomainT,Interval,Compare,Alloc>::insert_rest(const interval_type& x_itv, iterator& it, iterator& end_it)
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
    void interval_set_splitter<DomainT,Interval,Compare,Alloc>::recursive_subtract(const value_type& x)
    {
        if(x.empty()) return;
		if(this->_set.empty()) return;

        iterator fst_it;
		if(x.exclusive_less(*(this->_set.begin())))
			return;
		if(x.lower_bound() < this->_set.begin()->upper_bound())
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
    void interval_set_splitter<DomainT,Interval,Compare,Alloc>::subtract_rest(const interval_type& x_itv, iterator& snd_it, iterator& end_it)
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

} // namespace itl

#endif



