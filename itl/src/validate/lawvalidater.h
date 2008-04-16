#pragma once

#include <iostream>
#include <stdio.h>
#include <lokixt/Tuple.h>
#include <itl/itl_set.hpp>
#include <itl/itl_map.hpp>
#include <itl/cont_type_as_string.hpp>
#include <itl/itv_type_as_string.hpp>
#include <validate/gentor/randomgentor.h>

#include <validate/laws/monoid.h>
#include <validate/lawviolations.h>

namespace itl
{
    typedef itl::map<std::string, int> ValidationCounterT;
    typedef itl::map<std::string, int> ViolationCounterT;
    typedef itl::map<std::string, PolyLawViolations> ViolationMapT;

    class LawValidaterI
    {
    public:
        virtual ~LawValidaterI(){}
        virtual void init()=0;
        virtual void run()=0;
        virtual void addFrequencies(ValidationCounterT&)=0;
        virtual void addViolations(ViolationCounterT&, ViolationMapT&)=0;
    };


    template <class LawT, template<typename>class GentorT>
    class LawValidater : public LawValidaterI
    {
    public:
        typedef typename LawT::input_types    input_types;
        typedef typename LawT::output_types   output_types;
        typedef typename LawT::input_tuple    input_tuple;
        typedef typename LawT::output_tuple   output_tuple;
        
        //JODO don't forget for handcoded testcases
        //typedef typename GentorT<input_tuple> input_gentor;
        typedef typename Loki::TL::MapType<GentorT, input_types>::Result gentor_types;
        typedef typename Loki::tuple<gentor_types> input_gentor;

    public:
        LawValidater()    { setTrialsCount(5000); }

        void setTrialsCount(int trials) 
        {
            _trialsCount = trials;
            _silentTrialsCount = std::max(1, _trialsCount / 10);
        }

        void setSilentTrialsCount(int trials) { _trialsCount = trials; }

        void init();
        void run();
        void addFrequencies(ValidationCounterT& summary) { summary += _frequencies; }
        
        void addViolations(ViolationCounterT& summary, ViolationMapT& collector)   
        {
            summary.inject(ViolationCounterT::value_type(lawType(), static_cast<int>(_lawViolations.size()))); 
            //collector.inject(ViolationMapT::value_type(lawType(), PolyLawViolations(new LawViolationsT(_violations))));
            if(!_lawViolations.empty())
                collector.inject(ViolationMapT::value_type(lawType(), PolyLawViolations(new LawViolationsT(_lawViolations))));
        }

        std::string lawType()const{    return _law.typeString(); }

        void reportLawInfo()const;
        void reportProgress()const;
        void reportViolations()const;
        void reportSuccess()const;

        //CL this is tmp. Will be replaced by 'run'
        //CL void LawValidater::test_gen();

    private:
        typedef LawViolations<LawT> LawViolationsT;

    private:
        input_gentor _gentor;
        LawT         _law;

        int _trialsCount;
        int _silentTrialsCount;

        LawViolationsT     _lawViolations;
        ValidationCounterT _frequencies;
        ViolationCounterT  _violationsCount;
        ViolationMapT      _violations;
    }; //class LawValitater


    template <class LawT, template<typename>class GentorT>
    void LawValidater<LawT, GentorT>::init()
    {
        _frequencies.clear();
        _lawViolations.clear();
        _violations.clear();
    }

    template <class LawT, template<typename>class GentorT>
    void LawValidater<LawT, GentorT>::run()
    {
        //JODO reporting
        //reportLawInfo();
        //std::cout << "input_types.size()= " << TL::Length<input_types>::value << std::endl;
        //std::cout << "gentor_types.size()= " << TL::Length<gentor_types>::value << std::endl;

        // apply Calibrater.apply to each element of the generator-tuple _gentor
        // This is just an initialisation of the generators according to system
        // defaults for convenience purposes.
        _gentor.template apply<GentorT, Calibrater, input_tuple>();

        // Input values that are to be generated on every iteration
        input_tuple values;

        for(int idx=0; idx<_trialsCount; idx++)
        {
            // Apply the function SomeVale to each component of the input tuple
            _gentor.template map_template<GentorT, SomeValue>(values);
            _law.setInstance(values);

            //JODO reporting
            //if(idx % _silentTrialsCount == 0)
            //    reportProgress();

            if(!_law.holds())
                _lawViolations.insert(_law);
        }

        if(!_lawViolations.empty())
        {
            reportViolations();
            LawT violation = *(_lawViolations.begin());

            input_tuple  inVars;
            output_tuple outVars;
            violation.getInstance(inVars, outVars);
            std::cout << "Violation of: " << _law.typeString() << std::endl;
            std::cout <<  inVars.as_string() << std::endl;
            std::cout << outVars.as_string() << std::endl;

            violation.debug_holds();
        }
        else
        {
            //reportSuccess();
            _frequencies.insert(ValidationCounterT::value_type(lawType(), 1));
        }

    }

    template <class LawT, template<typename>class GentorT>
    void LawValidater<LawT, GentorT>::reportLawInfo()const
    {
        std::cout << "----------------------------------------------------------" << std::endl;
        std::cout << "Validation of law: " << std::endl;
        std::cout << _law.name() << std::endl;
        std::cout << _law.formula() << std::endl;
    }

    template <class LawT, template<typename>class GentorT>
    void LawValidater<LawT, GentorT>::reportProgress()const
    {
        typename LawT::input_tuple input_values;
        _law.getInputInstance(input_values);
        //JODO think about more general mechanics of pregress reporting here
        std::cout << "SomeValues " << input_values.as_string() << std::endl;
    }

    template <class LawT, template<typename>class GentorT>
    void LawValidater<LawT, GentorT>::reportViolations()const
    {
        std::cout << static_cast<int>(_lawViolations.getViolationsCount()) << " violations" << std::endl;
    }

    template <class LawT, template<typename>class GentorT>
    void LawValidater<LawT, GentorT>::reportSuccess()const
    {
        std::cout << "Law successfully validated for " << _trialsCount << " cases" << std::endl;
    }

} //namespace itl

// ----------------------------------------------------------------------------

