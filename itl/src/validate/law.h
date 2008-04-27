/*----------------------------------------------------------------------------+
A Law Based Test Automaton 'LaBatea'
Author: Joachim Faulhaber
Copyright (c) 2007-2008: Joachim Faulhaber
+-----------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+----------------------------------------------------------------------------*/
#ifndef __itl_Law_h_JOFA_070411__
#define __itl_Law_h_JOFA_070411__

#include <string>
#include <set>
#include <lokixt/Tuple.h>

namespace itl
{

    /** abstract template class Law:
        A Law can hold for a given set of variables.
        A Law together with the set of input variables is an instance of the law.
        The evaluation of the law results in a set of output variables.
        Output variables hold interim and final results of the evaluation of the law.
    */
    template <typename InputTypes, typename OutputTypes>
    class Law
    {
    public:
        typedef InputTypes               input_types;
        typedef OutputTypes              output_types;
        typedef typename Loki::tuple<InputTypes>  input_tuple;
        typedef typename Loki::tuple<OutputTypes> output_tuple;
    public:
        virtual ~Law(){}
        virtual bool holds()=0;
        virtual bool debug_holds()=0;

        virtual void setInstance(const input_tuple&)=0;
        virtual void getInstance(input_tuple&, output_tuple&)const=0;
        virtual void getInputInstance(input_tuple&)const=0;
        virtual void getOutputInstance(output_tuple&)const=0;

        virtual bool operator == (const Law& rhs)const=0;
        virtual bool operator < (const Law& rhs)const=0;
        virtual size_t size()const=0;

        virtual std::string name()const=0;
        virtual std::string formula()const=0;
        virtual std::string typeString()const=0;
    };


    template <typename InputTypes, typename OutputTypes>
    class LawBase : public Law<InputTypes, OutputTypes>
    {
    public:
        typedef Law<InputTypes, OutputTypes>     base_type;
        typedef typename base_type::input_tuple  input_tuple;
        typedef typename base_type::output_tuple output_tuple;

    public:
        virtual size_t size()const=0;
        virtual bool holds()=0;

        bool debug_holds(){ return holds(); }

        void setInstance(const input_tuple& inVars)
        { _inputTuple = inVars; }

        void getInstance(input_tuple& inVars, output_tuple& outVars)const
        { inVars = _inputTuple; outVars = _outputTuple; }

        void getInputInstance(input_tuple& inVars)const
        { inVars = _inputTuple; }

        void getOutputInstance(output_tuple& outVars)const
        { outVars = _outputTuple; }

        bool operator == (const base_type& rhs)const
        {
            return size() == rhs.size(); //JODO
        }

        bool operator < (const base_type& rhs)const
        {
            return size() < rhs.size();
        }


        std::string name()const { return "unspecified law"; }
        std::string formula()const { return "unspecified formula"; }
        std::string typeString()const { return ""; }


        template<unsigned int index>
        typename Loki::TL::TypeAt<InputTypes, index>::Result 
            setInputValue(const typename Loki::TL::TypeAt<InputTypes, index>::Result& value) 
        { return Loki::tup::refer<index>(_inputTuple)=value; }

        template<unsigned int index>
        typename Loki::TL::TypeAt<InputTypes, index>::Result getInputValue()const 
        { return Loki::tup::get<index>(_inputTuple); }

        template<unsigned int index>
        typename Loki::TL::TypeAt<OutputTypes, index>::Result 
            setOutputValue(const typename Loki::TL::TypeAt<OutputTypes, index>::Result& value) 
        { return Loki::tup::refer<index>(_outputTuple)=value; }

        template<unsigned int index>
        typename Loki::TL::TypeAt<OutputTypes, index>::Result getOutputValue()const 
        { return Loki::tup::get<index>(_outputTuple); }

    private:
        input_tuple  _inputTuple;
        output_tuple _outputTuple;
    }; //class LawBase

    enum InputVarIndex  { operand_a, operand_b, operand_c, operand_d, operand_e };
    enum OutputVarIndex { lhs_result, rhs_result };

} // namespace itl

#endif //__itl_Law_h_JOFA_070411__

