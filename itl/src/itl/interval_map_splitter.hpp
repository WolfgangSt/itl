/*----------------------------------------------------------------------------+
Copyright (c) 2007-2008: Joachim Faulhaber
+-----------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+----------------------------------------------------------------------------*/
#ifndef __itl_interval_map_splitter_h_JOFA_080608__
#define __itl_interval_map_splitter_h_JOFA_080608__

#include <itl/interval_base_map.hpp>
#include <itl/split_interval_set.hpp>

namespace itl
{

    /// JODO
    /** 
        Template-class <b>split_interval_map_splitter</b>

        @author  Joachim Faulhaber
    */
    template
    <
        typename DomainT,
        typename CodomainT,
        template<class>class Interval = itl::interval,
        template<class>class Compare  = std::less,
        template<class>class Alloc    = std::allocator
    >
    class interval_map_splitter
    {
    public:
        typedef interval_map_splitter<DomainT,CodomainT,Interval,Compare,Alloc> type;

        typedef Interval<DomainT> interval_type;

		/// Container type for the implementation 
		typedef typename itl::map<interval_type,CodomainT,exclusive_less,Alloc> ImplMapT;

		typedef typename ImplMapT::iterator iterator;        

		/// key type of the implementing container
		typedef typename ImplMapT::key_type   key_type;
		/// data type of the implementing container
		typedef typename ImplMapT::data_type  data_type;
		/// value type of the implementing container
		typedef typename ImplMapT::value_type value_type;

		//JODO ctors

        bool contains(const value_type& x)const;

        void insert(const value_type&);
        void subtract(const value_type&);

        void handle_neighbours(const iterator& it){}

		size_t jodo_interval_count()const { return _map.size(); }

        void toItvSetT(interval_set<DomainT,Interval,Compare,Alloc>& dst)const
        { dst.clear(); const_FORALL(typename ImplMapT, it, this->_map) dst.insert((*it).KEY_VALUE); }

        
        //TESTCODE
        void getResiduals(const interval_type& x_itv, interval_type& leftResid, interval_type& rightResid);

        //JODO make private after tests
        // If an associated value x is inserted into a SplitItvMap, the actual splitting takes place
        // only at the borders of the interval of x. All the other modifications of the SplitItvMap
        // can be done via inplace value modifications of associated intervals in the map or by simple
        // insertions of associated intervals.
        void splitFor(const interval_type& x_itv, iterator& lwb_it, iterator& upb_it);

    private:

        void iterative_insert(const value_type&);
        void iterative_subtract(const value_type&);

        void recursive_insert(const value_type&);
        void recursive_subtract(const value_type&);

        void insert_rest(const interval_type& x_itv, const CodomainT& x_val, iterator& it, iterator& end_it);
        void subtract_rest(const interval_type& x_itv, const CodomainT& x_val, iterator& it, iterator& end_it);

		void matchMap(interval_map_splitter& matchMap, const value_type& x)const;

	protected:
		ImplMapT _map;
    } ;


	template <typename DomainT, typename CodomainT, template<class>class Interval, template<class>class Compare, template<class>class Alloc>
	void interval_map_splitter<DomainT,CodomainT,Interval,Compare,Alloc>
		::matchMap(interval_map_splitter& matchMap, const value_type& x_y)const
	{
		interval_type x = x_y.KEY_VALUE;
		typename ImplMapT::const_iterator fst_it = _map.lower_bound(x);
		typename ImplMapT::const_iterator end_it = _map.upper_bound(x);

		for(typename ImplMapT::const_iterator it=fst_it; it!=end_it; it++) 
			matchMap.insert(*it);

		//JODO URG mixin base class
		//JODO URG matchMap.join();
	}



    template <typename DomainT, typename CodomainT, template<class>class Interval, template<class>class Compare, template<class>class Alloc>
    bool interval_map_splitter<DomainT,CodomainT,Interval,Compare,Alloc>::contains(const value_type& x_y)const
    {
        interval_type x = x_y.KEY_VALUE;
        if(x.empty()) return true;

        interval_map_splitter<DomainT,CodomainT,Interval,Compare,Alloc> match_map;
        matchMap(match_map, x_y);

		//JODO URG mixin base class
        if(match_map.jodo_interval_count() != 1) return false;

        iterator match_it = match_map._map.find(x);
        if(! x.contained_in((*match_it).KEY_VALUE) ) return false;

        return (*match_it).CONT_VALUE==x_y.CONT_VALUE;
    }

    //----------------------------------------------------------------------
    // Splits *this interval_map_splitter M at the borders of interval x as follows.
    //
    // M: ... [--------)  ...  [------) ...
    //        vi               vj
    // x:          [---------------)
    // -->
    // M':... [---)[---)  ...  [---)[-) ...
    //        vi   vi     ...  vj   vj
    //----------------------------------------------------------------------
    template <typename DomainT, typename CodomainT, template<class>class Interval, template<class>class Compare, template<class>class Alloc>
    void interval_map_splitter<DomainT,CodomainT,Interval,Compare,Alloc>::splitFor(const interval_type& x_itv, iterator& fst_it, iterator& end_it)
    {
        fst_it = this->_map.lower_bound(x_itv);
        end_it = this->_map.upper_bound(x_itv);
        iterator lst_it;

        interval_type fst_itv, lst_itv;
        interval_type outerLeft, outerRight;   // Partial intervals of M which are outside x
        interval_type innerLeft, innerRight;   // Partial intervals of M which are inside x
        CodomainT leftVal, rightVal;      // Associated values vi and vj

        if(fst_it!=end_it)
        {
            fst_itv = (*fst_it).KEY_VALUE;
            fst_itv.left_surplus(outerLeft, x_itv);

            lst_it = end_it; lst_it--;
            lst_itv = (*lst_it).KEY_VALUE;
            lst_itv.right_surplus(outerRight, x_itv);
        }

        if(!outerLeft.empty())
        {
            // Split the associated Interval Mi into M'i1 and M'i2
            fst_itv.intersect(innerLeft, x_itv);
            leftVal = (*fst_it).CONT_VALUE;
            this->_map.erase(fst_it);
            this->_map.insert(value_type(outerLeft, leftVal));
            this->_map.insert(value_type(innerLeft, leftVal));

            // refresh lower_bound
            fst_it = this->_map.lower_bound(x_itv);
        }
        if(!outerRight.empty())
        {
            // Split the associated Interval Mj into M'j1 and M'j2
            lst_itv.intersect(innerRight, x_itv);

            if(!(innerLeft == innerRight))
            {
                rightVal = (*lst_it).CONT_VALUE;
                this->_map.erase(lst_it);
                this->_map.insert(value_type(innerRight, rightVal));
                this->_map.insert(value_type(outerRight, rightVal));
            }
            else
            {
                this->_map.insert(value_type(outerRight, leftVal));
            }

            // refresh upper bound
            end_it = this->_map.upper_bound(x_itv);
        }

        // After associated values are saved, we may erase the splitted intervals from the map
        // CAUTION Will erase fst_it and insert outerLeft, innerLeft invalidate lst_it and vice versa?
        // No, it should not, according to docu    
    }


    //MEMO INFO -------------------------------------------------------------------
    // iterative_insert and iterative_subtract are iterative versions of recursive functions
    // recursive_insert and recursive_subtract. Since recursive_insert and recursive_subtract are one of the
    // most expensive functions (according to profile run) I expected the
    // iterative versions to speed up performance. As it turned out this is not
    // so, the iterative niftyVersions were even slightly slower.
    //   iterative_insert/Subtract should still be kept. (1) Their implementation is
    // more concise and better to understand. (2) May be it could be speeded up
    // by another attempt JODO 
    //-----------------------------------------------------------------------------
    // After splitFor(x, l, u) we have the following
    //
    // x:           [-----------------------------------)
    //               w
    // M:  ... [---)[---)     [--------)       ... [----)[--) ...
    //          vi   vi     ...v(i+1)               vj    vj
    // -->
    //     ... [---)[---)[===)[--------)[====) ... [----)[--) ...
    //          vi   vi+w w    v(i+1)+w  w      ... vj+w  vj
    //
    // The intersection intervals of x and M all get a value of v(i+k)+w
    // The complementary intervals within the range of x are getting value w
    // All the other intervals of M are of course unchanged
    //-----------------------------------------------------------------------------
    template <typename DomainT, typename CodomainT, template<class>class Interval, template<class>class Compare, template<class>class Alloc>
    void interval_map_splitter<DomainT,CodomainT,Interval,Compare,Alloc>::iterative_insert(const value_type& x)
    {
        typedef split_interval_set<DomainT,Interval,Compare,Alloc> AuxSetTD;
        const interval_type&   x_itv = x.KEY_VALUE;
        // JODO Must be a copy ??
        const CodomainT& x_val = x.CONT_VALUE; //CodomainT::OP =

        if(x_itv.empty()) return;
        if(x_val==CodomainT()) return; //CodomainT::OP CodomainT; CodomainT::OP ==

        std::pair<typename ImplMapT::iterator,bool> insertion = this->_map.insert(x);

        if(!insertion.WAS_SUCCESSFUL)
        {
            iterator lwb_, upb_, shared_, victim_;
            splitFor(x_itv, lwb_, upb_);

            AuxSetTD intersect, complement(x_itv);

            shared_=lwb_; 
            while(shared_ != upb_)
            {
                intersect.insert((*shared_).KEY_VALUE);
                if(CodomainT() == ((*shared_).CONT_VALUE += x_val))
                {
                    victim_ = shared_;
                    shared_++;
                    this->_map.erase(victim_);
                }
                else
                    shared_++;
            }

            complement -= intersect;

            FORALL(typename AuxSetTD, cmpl_, complement)
            {
                this->_map.insert(value_type(*cmpl_, x_val));
            }
        }
    }

    template <typename DomainT, typename CodomainT, template<class>class Interval, template<class>class Compare, template<class>class Alloc>
    void interval_map_splitter<DomainT,CodomainT,Interval,Compare,Alloc>::iterative_subtract(const value_type& x)
    {
        typedef split_interval_set<DomainT,Interval,Compare,Alloc> AuxSetTD;
        const interval_type&   x_itv = x.KEY_VALUE;
        const CodomainT& x_val = x.CONT_VALUE;

        if(x_itv.empty()) return;
        if(x_val==CodomainT()) return;

        std::pair<typename ImplMapT::iterator,bool> insertion = this->_map.insert(x);

        if(!insertion.WAS_SUCCESSFUL)
        {
            iterator lwb_, upb_, shared_, victim_;
            splitFor(x_itv, lwb_, upb_);

            AuxSetTD intersect, complement(x_itv);

            shared_=lwb_; 
            while(shared_ != upb_)
            {
                intersect.insert((*shared_).KEY_VALUE);
                if(CodomainT() == ((*shared_).CONT_VALUE -= x_val))
                {
                    victim_ = shared_;
                    shared_++;
                    this->_map.erase(victim_);
                }
                else
                    shared_++;
            }

            complement -= intersect;

            CodomainT insert_val = CodomainT();
            insert_val -= x_val;
            FORALL(typename AuxSetTD, cmpl_, complement)
            {
                this->_map.insert(value_type(*cmpl_, insert_val));
            }
        }
    }


    template <typename DomainT, typename CodomainT, template<class>class Interval, template<class>class Compare, template<class>class Alloc>
    void interval_map_splitter<DomainT,CodomainT,Interval,Compare,Alloc>::getResiduals(const interval_type& x_itv, interval_type& leftResid, interval_type& rightResid)
    {
        iterator fst_it = this->_map.lower_bound(x_itv);
        iterator end_it = this->_map.upper_bound(x_itv);
        
        if(fst_it==end_it)
        {
            leftResid.clear();
            rightResid.clear();
            return;
        }

        (*fst_it).KEY_VALUE.left_surplus(leftResid, x_itv);
        iterator lst_it = fst_it; lst_it++;

        if(lst_it==end_it)
        {
            rightResid.clear();
            return;
        }

        lst_it=end_it; lst_it--;

        (*lst_it).KEY_VALUE.right_surplus(rightResid, x_itv);
    }


    template <typename DomainT, typename CodomainT, template<class>class Interval, template<class>class Compare, template<class>class Alloc>
    void interval_map_splitter<DomainT,CodomainT,Interval,Compare,Alloc>::insert(const value_type& x)
    { recursive_insert(x); }
    //{ iterative_insert(x); }


    template <typename DomainT, typename CodomainT, template<class>class Interval, template<class>class Compare, template<class>class Alloc>
    void interval_map_splitter<DomainT,CodomainT,Interval,Compare,Alloc>::recursive_insert(const value_type& x)
    {
        const interval_type& x_itv = x.KEY_VALUE;
         // must be a copy
        CodomainT      x_val = x.CONT_VALUE;

        if(x_itv.empty()) return;
        if(x_val==CodomainT()) return;

        std::pair<typename ImplMapT::iterator,bool> insertion = this->_map.insert(x);

        if(!insertion.WAS_SUCCESSFUL)
        {

            iterator fst_it = this->_map.lower_bound(x_itv);
            iterator end_it = this->_map.upper_bound(x_itv);

            iterator cur_it = fst_it ;
            interval_type cur_itv   = (*cur_it).KEY_VALUE ;
            CodomainT cur_val = (*cur_it).CONT_VALUE;


            interval_type leadGap; x_itv.left_surplus(leadGap, cur_itv);
            // this is a new Interval that is a gap in the current map
            recursive_insert(value_type(leadGap, x_val));

            // only for the first there can be a leftResid: a part of *it left of x
            interval_type leftResid;  cur_itv.left_surplus(leftResid, x_itv);

            // handle special case for first

            interval_type interSec;
            cur_itv.intersect(interSec, x_itv);

            CodomainT cmb_val = cur_val;
            cmb_val += x_val;

            iterator snd_it = fst_it; snd_it++;
            if(snd_it == end_it) 
            {
                // first == last

                interval_type endGap; x_itv.right_surplus(endGap, cur_itv);
                // this is a new Interval that is a gap in the current map
                recursive_insert(value_type(endGap, x_val));

                // only for the last there can be a rightResid: a part of *it right of x
                interval_type rightResid;  (*cur_it).KEY_VALUE.right_surplus(rightResid, x_itv);

                this->_map.erase(cur_it);
                recursive_insert(value_type(leftResid,  cur_val));
                recursive_insert(value_type(interSec,   cmb_val));
                recursive_insert(value_type(rightResid, cur_val));
            }
            else
            {
                this->_map.erase(cur_it);
                recursive_insert(value_type(leftResid, cur_val));
                recursive_insert(value_type(interSec,  cmb_val));

                // shrink interval
                interval_type x_rest(x_itv);
                x_rest.left_subtract(cur_itv);

                insert_rest(x_rest, x_val, snd_it, end_it);
            }
        }
    }


    template <typename DomainT, typename CodomainT, template<class>class Interval, template<class>class Compare, template<class>class Alloc>
    void interval_map_splitter<DomainT,CodomainT,Interval,Compare,Alloc>::insert_rest(const interval_type& x_itv, const CodomainT& x_val, iterator& it, iterator& end_it)
    {
        iterator nxt_it = it; nxt_it++;

        interval_type   cur_itv = (*it).KEY_VALUE ;
        CodomainT cur_val = (*it).CONT_VALUE ;
        
        interval_type newGap; x_itv.left_surplus(newGap, cur_itv);
        // this is a new Interval that is a gap in the current map
        recursive_insert(value_type(newGap, x_val));

        interval_type interSec;
        cur_itv.intersect(interSec, x_itv);

        CodomainT cmb_val = cur_val;
        cmb_val += x_val;

        if(nxt_it==end_it)
        {
            interval_type endGap; x_itv.right_surplus(endGap, cur_itv);
            // this is a new Interval that is a gap in the current map
            recursive_insert(value_type(endGap, x_val));

            // only for the last there can be a rightResid: a part of *it right of x
            interval_type rightResid;  cur_itv.right_surplus(rightResid, x_itv);

            this->_map.erase(it);
            recursive_insert(value_type(interSec,   cmb_val));
            recursive_insert(value_type(rightResid, cur_val));
        }
        else
        {        
            this->_map.erase(it);
            recursive_insert(value_type(interSec,   cmb_val));

            // shrink interval
            interval_type x_rest(x_itv);
            x_rest.left_subtract(cur_itv);

            insert_rest(x_rest, x_val, nxt_it, end_it);
        }
    }



    template <typename DomainT, typename CodomainT, template<class>class Interval, template<class>class Compare, template<class>class Alloc>
    void interval_map_splitter<DomainT,CodomainT,Interval,Compare,Alloc>::subtract(const value_type& x)
    { recursive_subtract(x); }
    //{ iterative_subtract(x); }



    template <typename DomainT, typename CodomainT, template<class>class Interval, template<class>class Compare, template<class>class Alloc>
    void interval_map_splitter<DomainT,CodomainT,Interval,Compare,Alloc>::recursive_subtract(const value_type& x)
    {
        const interval_type&   x_itv = x.KEY_VALUE;
        const CodomainT& x_val = x.CONT_VALUE;

        if(x_itv.empty()) return;
        if(x_val==CodomainT()) return;

        iterator fst_it = this->_map.lower_bound(x_itv);
        if(fst_it==this->_map.end()) return;
        iterator end_it = this->_map.upper_bound(x_itv);
        if(fst_it==end_it) return;

        iterator cur_it = fst_it ;
        interval_type cur_itv   = (*cur_it).KEY_VALUE ;
        // must be copies because cur_it will be erased
        CodomainT cur_val = (*cur_it).CONT_VALUE ;

        // only for the first there can be a leftResid: a part of *it left of x
        interval_type leftResid;  cur_itv.left_surplus(leftResid, x_itv);

        // handle special case for first

        interval_type interSec;
        cur_itv.intersect(interSec, x_itv);

        CodomainT cmb_val = cur_val;
        cmb_val -= x_val;

        iterator snd_it = fst_it; snd_it++;
        if(snd_it == end_it) 
        {
            // first == last
            // only for the last there can be a rightResid: a part of *it right of x
            interval_type rightResid;  (*cur_it).KEY_VALUE.right_surplus(rightResid, x_itv);

            this->_map.erase(cur_it);
            insert(value_type(leftResid,  cur_val));
            if(!(cmb_val==CodomainT()))
                insert(value_type(interSec, cmb_val));
            insert(value_type(rightResid, cur_val));
        }
        else
        {
            // first AND NOT last
            this->_map.erase(cur_it);
            insert(value_type(leftResid, cur_val));
            if(!(cmb_val==CodomainT()))
                insert(value_type(interSec, cmb_val));

            subtract_rest(x_itv, x_val, snd_it, end_it);
        }
    }



    template <typename DomainT, typename CodomainT, template<class>class Interval, template<class>class Compare, template<class>class Alloc>
    void interval_map_splitter<DomainT,CodomainT,Interval,Compare,Alloc>::subtract_rest(const interval_type& x_itv, const CodomainT& x_val, iterator& snd_it, iterator& end_it)
    {
        iterator it=snd_it, nxt_it=snd_it; nxt_it++;

        while(nxt_it!=end_it)
        {
            CodomainT& cur_val = (*it).CONT_VALUE ;

            cur_val -= x_val;

            if(cur_val==CodomainT())
            { iterator victim; victim=it; it++; this->_map.erase(victim); }
            else it++;
            nxt_it=it; nxt_it++;
        }

        // it refers the last overlaying intervals of x_itv
        const interval_type&  cur_itv = (*it).KEY_VALUE ;

        interval_type rightResid; cur_itv.right_surplus(rightResid, x_itv);

        if(rightResid.empty())
        {
            CodomainT& cur_val = (*it).CONT_VALUE ;
            cur_val -= x_val;
            if(cur_val==CodomainT())
                this->_map.erase(it);
        }
        else
        {
            CodomainT cur_val = (*it).CONT_VALUE ;
            CodomainT cmb_val = cur_val ;
            cmb_val -= x_val;
            interval_type interSec; cur_itv.intersect(interSec, x_itv);

            this->_map.erase(it);
            if(!(cmb_val==CodomainT()))
                insert(value_type(interSec, cmb_val));
            insert(value_type(rightResid, cur_val));
        }
    }

} // namespace itl

#endif


