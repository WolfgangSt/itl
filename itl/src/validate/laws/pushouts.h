/*----------------------------------------------------------------------------+
A Law Based Test Automaton 'LaBatea'
Author: Joachim Faulhaber
Copyright (c) 2007-2008: Joachim Faulhaber
+-----------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+----------------------------------------------------------------------------*/
#ifndef __itl_pushouts_h_JOFA_071124__
#define __itl_pushouts_h_JOFA_071124__

#include <itl/itl_value.hpp>
#include <itl/type_traits.hpp> //JODO ReprBase and/or type_traits
#include <validate/law.h>

namespace itl
{

    // ---------------------------------------------------------------------------
    //  (a,b) ---o---> c
    //    |            |
    //    |f           |f
    //    V            V
    // (a',b')---o---> c'
    // ---------------------------------------------------------------------------
    template <typename SourceT, typename TargetT, 
              template<class,class>class FunctionT, template<typename>class OperatorT>
    class BinaryPushout : 
        public Law<BinaryPushout<SourceT,TargetT,FunctionT,OperatorT>, 
                   LOKI_TYPELIST_2(SourceT, SourceT), LOKI_TYPELIST_2(TargetT,TargetT)>
    {
        /** f(a o b) == f(a) o f(b)
        computed using inplace operators  o=
        Input  = (a := inVal1, b := inVal2)
        Output = (lhs_result, rhs_result)
        */
    public:
        std::string name()const { return "Pushout"; }
        std::string formula()const { return "cont a, cont b: f(a o b) == f(a) o f(b) 'inplace'"; }

        std::string typeString()const
        {
            return
                "Pushout<"+type<SourceT>::to_string()+","
                          +type<TargetT>::to_string()+","
                          +binary_template<FunctionT>::to_string()+","
                          +unary_template<OperatorT>::to_string()+">";
        }

    public:

        bool holds()
        {
            // f(a o b) == f(a) o f(b)
            // --- left hand side ------------------------
            // lhs := f(a o b)
            SourceT a_o_b = this->template getInputValue<operand_a>();
            // a_o_b *=  this->template getInputValue<operand_b>();
            OperatorT<SourceT>()(a_o_b, this->template getInputValue<operand_b>());

            TargetT lhs;
            FunctionT<TargetT,SourceT>()(lhs, a_o_b);

            // --- right hand side -----------------------
            // rhs := atomize(a) * atomize(b)
            TargetT atomic_a;
            FunctionT<TargetT,SourceT>()(atomic_a, this->template getInputValue<operand_a>());
            TargetT atomic_b;
            FunctionT<TargetT,SourceT>()(atomic_b, this->template getInputValue<operand_b>());
            TargetT rhs = atomic_a;
            OperatorT<TargetT>()(rhs, atomic_b);

            this->template setOutputValue<lhs_result>(lhs);
            this->template setOutputValue<rhs_result>(rhs);

            return lhs == rhs;
        }

        size_t size()const 
        { 
            return 
                value_size<SourceT>::get(this->template getInputValue<operand_a>())+
                value_size<SourceT>::get(this->template getInputValue<operand_b>());
        }

		bool debug_holds()
        {
            // f(a o b) == f(a) o f(b)
            // --- left hand side ------------------------
            // lhs := f(a o b)
            SourceT a_o_b = this->template getInputValue<operand_a>();
			std::cout << "a:" << this->template getInputValue<operand_a>().as_string() << std::endl;
			std::cout << "b:" << this->template getInputValue<operand_b>().as_string() << std::endl;
            // a_o_b o=  this->template getInputValue<operand_b>();
            OperatorT<SourceT>()(a_o_b, this->template getInputValue<operand_b>());

            TargetT lhs;
            FunctionT<TargetT,SourceT>()(lhs, a_o_b);

            // --- right hand side -----------------------
            // rhs := atomize(a) * atomize(b)
            TargetT atomic_a;
            FunctionT<TargetT,SourceT>()(atomic_a, this->template getInputValue<operand_a>());
            TargetT atomic_b;
            FunctionT<TargetT,SourceT>()(atomic_b, this->template getInputValue<operand_b>());
            TargetT rhs = atomic_a;
            OperatorT<TargetT>()(rhs, atomic_b);

            this->template setOutputValue<lhs_result>(lhs);
            this->template setOutputValue<rhs_result>(rhs);

            return lhs == rhs;
        }

    };


} // namespace itl

#endif // __itl_pushouts_h_JOFA_071124__

