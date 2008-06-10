/*----------------------------------------------------------------------------+
Copyright (c) 2007-2008: Joachim Faulhaber
+-----------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+----------------------------------------------------------------------------*/
#ifndef __itl_interval_set_separator_JOFA_080608__
#define __itl_interval_set_separator_JOFA_080608__

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
    class interval_set_separator
    {
    public:
        typedef Interval<DomainT> interval_type;

		typedef typename itl::set<interval_type,exclusive_less,Alloc> ImplSetT;

		/// Container type for the implementation 
		typedef typename ImplSetT::iterator iterator;

		/// key type of the implementing container
		typedef typename ImplSetT::key_type   key_type;
		/// data type of the implementing container
		typedef typename ImplSetT::data_type  data_type;
		/// value type of the implementing container
		typedef typename ImplSetT::value_type value_type;


        typedef typename ImplSetT::iterator iterator;
        
        /// Virtual constructor
        interval_set_separator* cons()const 
		{ return new interval_set_separator<DomainT,Interval,Compare,Alloc>; }

        /// Does the set contain the interval  <tt>x</tt>?
        bool contains(const interval_type& x)const;

		/// Insertion of an interval <tt>x</tt>
		void insert(const value_type& x);

		/// Removal of an interval <tt>x</tt>
		void subtract(const value_type& x);

        /// Treatment of adjoint intervals on insertion
        void handle_neighbours(const iterator& it){}

	protected:
		ImplSetT _set;
    } ;



    template <typename DomainT, template<class>class Interval, template<class>class Compare, template<class>class Alloc>
    bool interval_set_separator<DomainT,Interval,Compare,Alloc>::contains(const interval_type& x)const
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



	template<class DomainT, template<class>class Interval, template<class>class Compare, template<class>class Alloc>
	void interval_set_separator<DomainT,Interval,Compare,Alloc>::insert(const value_type& x)
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
	void interval_set_separator<DomainT,Interval,Compare,Alloc>::subtract(const value_type& x)
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



