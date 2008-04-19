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
/* ------------------------------------------------------------------
Predicates
    general classes for Predicates
--------------------------------------------------------------------*/
#ifndef __itl_predicates_H_JOFA_990224__
#define __itl_predicates_H_JOFA_990224__

#include <functional>

namespace itl
{
    // naming convention
    // predicate: n-ary predicate
    // property:  unary predicate
    // relation:  binary predicate

    // Unary predicates

    template <class Type>
    class property : public std::unary_function<Type,bool>
    {
    public:
        virtual bool operator() (const Type& x)const=0;
    };

    template <class Type>
    class member_property : public property<Type>
    {
    public:
        member_property( bool(Type::* pred)()const ): property<Type>(), m_pred(pred){}
        bool operator () (const Type& x)const { return (x.*m_pred)(); }
    private:
        bool(Type::* m_pred)()const;
    } ;

    template <class Type>
    class empty: public property<Type>
    {
    public:
        bool operator() (const Type& x)const { return x.empty(); }
    } ;


    // Binary predicates: relations

    template <class LeftT, class RightT>
    class relation : public std::binary_function<LeftT,RightT,bool>
    {
    public:
        virtual bool operator() (const LeftT& a, const RightT& b)const=0;
    } ;

    template <class Type> struct std_equal : public relation<Type, Type>
    {
        bool operator()(const Type& lhs, const Type& rhs)const
        {
            return lhs == rhs;
        }
    };

    template<>
    inline std::string unary_template<itl::std_equal>::to_string()  { return "=="; }

    template <class Type> 
    struct element_equal : public relation<Type, Type>
    {
        bool operator()(const Type& lhs, const Type& rhs)const
        {
            return is_element_equal(lhs, rhs);
        }
    };

    template<>
    inline std::string unary_template<itl::element_equal>::to_string()  { return "="; }

    /** Functor class contained_in implements the subset relation. 
    <tt>contained_in(sub, super)</tt> is true if <tt>sub</tt> is contained in <tt>super</tt> */
    template<class Type> 
    struct contained_in : public relation<Type, Type>
    {
        bool operator()(const Type& sub, const Type& super)const
        {
            return sub.contained_in(super);
        }
    };

    /** Functor class containes implements the superset relation. 
    <tt>containes(super, sub)</tt> is true if <tt>super</tt> containes <tt>sub</tt> */
    template<class Type> 
    struct containes : public relation<Type, Type>
    {
        bool operator()(const Type& super, const Type& sub)const
        {
            return super.containes(sub);
        }
    };

} // namespace itl


#endif
