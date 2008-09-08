/*----------------------------------------------------------------------------+
A Law Based Test Automaton 'LaBatea'
Author: Joachim Faulhaber
Copyright (c) 2007-2008: Joachim Faulhaber
+-----------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+----------------------------------------------------------------------------*/
#pragma once

#include <itl/functors.hpp>
#include <itl/interval_morphism.hpp>
#include <validate/laws/set_laws.h>
#include <validate/laws/order.h>
#include <validate/laws/pushouts.h>
#include <validate/lawvalidater.h>

namespace itl
{
    typedef WeightedNumberGentor<int> ChoiceT;

    class AlgebraValidater
    {
    public:
        virtual ~AlgebraValidater(){}
        // the choice probability, and also the availability of laws is individual to each type
        // Somehow it has to be defined in conjunction to every type. So it is an aspect of
        // type traits.
        virtual void setProfile()=0;
        virtual void validate()=0;
        virtual void addFrequencies(ValidationCounterT&)=0;
        virtual void addViolations(ViolationCounterT&, ViolationMapT&)=0;

        virtual bool hasValidProfile()const{ return true; }
    };


    // ------------------------------------------------------------------------
    // Orderings
    // ------------------------------------------------------------------------

    template <typename Type, template<class>class Relation>
    class StrictWeakOrderValidater : public AlgebraValidater
    {
    public:
        enum Laws 
        { 
            transitivity,
            antisymmetry2,
            irreflexivity,
            Laws_size 
        };

        StrictWeakOrderValidater() {setProfile();}

        void setProfile()
        {
            _lawChoice.setSize(Laws_size);
            _lawChoice.setMaxWeights(100);
            _lawChoice[transitivity]  = 33;
            _lawChoice[antisymmetry2] = 33;
            _lawChoice[irreflexivity] = 34;
            _lawChoice.init();
        }


        LawValidaterI* chooseValidater()
        {
            switch(_lawChoice.some())
            {
            case transitivity:   return new LawValidater<Transitivity <Type, Relation >, RandomGentor >;
            case antisymmetry2:     return new LawValidater<Antisymmetry2<Type, Relation >, RandomGentor >;
            case irreflexivity:  return new LawValidater<Irreflexivity<Type, Relation >, RandomGentor >;
            default: return NULL;
            }
        }

        void validate()
        {
            _validater = chooseValidater();
            if(_validater)
            {
                _validater->run();
                _validater->addFrequencies(_frequencies);
                _validater->addViolations(_violationsCount, _violations);
                delete _validater;
            }
        }

        void addFrequencies(ValidationCounterT& summary) { summary += _frequencies; }
        void addViolations(ViolationCounterT& summary, ViolationMapT& collector)
        { 
            summary += _violationsCount; 
            collector += _violations;  
        }


    private:
        ChoiceT            _lawChoice;
        LawValidaterI*     _validater;
        ValidationCounterT _frequencies;
        ViolationCounterT  _violationsCount;
        ViolationMapT      _violations;
    }; //class AlgebraValidater


    // ------------------------------------------------------------------------

    template <typename Type, template<class>class Relation>
    class PartialOrderValidater : public AlgebraValidater
    {
    public:
        enum Laws 
        { 
            transitivity,
            antisymmetry,
            reflexivity,
            Laws_size 
        };

        PartialOrderValidater() {setProfile();}

        void setProfile()
        {
            _lawChoice.setSize(Laws_size);
            _lawChoice.setMaxWeights(100);
            _lawChoice[transitivity]  = 33;
            _lawChoice[antisymmetry]  = 33;
            _lawChoice[reflexivity]   = 34;
            _lawChoice.init();
        }


        LawValidaterI* chooseValidater()
        {
            switch(_lawChoice.some())
            {
            case transitivity: return new LawValidater<Transitivity<Type, Relation>, RandomGentor>;
            case antisymmetry: return new LawValidater<Antisymmetry<Type, Relation>, RandomGentor>;
            case reflexivity:  return new LawValidater<Reflexivity <Type, Relation>, RandomGentor>;
            default: return NULL;
            }
        }

        void validate()
        {
            _validater = chooseValidater();
            if(_validater)
            {
                _validater->run();
                _validater->addFrequencies(_frequencies);
                _validater->addViolations(_violationsCount, _violations);
                delete _validater;
            }
        }

        void addFrequencies(ValidationCounterT& summary) { summary += _frequencies; }
        void addViolations(ViolationCounterT& summary, ViolationMapT& collector)
        { 
            summary += _violationsCount; 
            collector += _violations;  
        }


    private:
        ChoiceT        _lawChoice;
        LawValidaterI* _validater;
        ValidationCounterT _frequencies;
        ViolationCounterT  _violationsCount;
        ViolationMapT      _violations;
    };


    // ------------------------------------------------------------------------
    // Monoids
    // ------------------------------------------------------------------------
    /*JODO currently not used, incomplete.
    template <typename Type>
    class InplaceCommutativeMonoidValidater : public AlgebraValidater
    {
    public:
        enum Laws 
        {
            inplacePlusAssociativity, // EA   semigroup
            inplacePlusNeutrality,    // EAN  monoid
            inplacePlusCommutativity, // EANC commutative monoid
            Laws_size 
        };

        InplaceCommutativeMonoidValidater(){setProfile();}

        void setProfile()
        {
            _lawChoice.setSize(Laws_size);
            _lawChoice.setMaxWeights(100);
            _lawChoice[inplacePlusAssociativity] = 33;
            _lawChoice[inplacePlusNeutrality]    = 33;
            _lawChoice[inplacePlusCommutativity] = 34;
            _lawChoice.init();
        }

        LawValidaterI* chooseValidater()
        {
            switch(_lawChoice.some())
            {
            case inplacePlusNeutrality:    return new LawValidater<InplaceNeutrality<Type>, RandomGentor>;
            case inplacePlusCommutativity: return new LawValidater<InplaceCommutativity<Type>, RandomGentor>;
            case inplacePlusAssociativity: return new LawValidater<InplaceAssociativity<Type>, RandomGentor>;
            default: return NULL;
            }
        }

        void validate()
        {
            _validater = chooseValidater();
            _validater->run();
            _validater->addFrequencies(_frequencies);
            _validater->addViolations(_violationsCount, _violations);
            delete _validater;
        }

        void addFrequencies(ValidationCounterT& summary) { summary += _frequencies; }
        void addViolations(ViolationCounterT& summary, ViolationMapT& collector)
        { 
            summary += _violationsCount; 
            collector += _violations;  
        }

    private:
        ChoiceT        _lawChoice;
        LawValidaterI* _validater;
        ValidationCounterT _frequencies;
    };
    */


    template <typename Type>
    class InplaceSetBaseValidater : public AlgebraValidater
    {
    public:
        typedef StrictWeakOrderValidater<Type, std::less> LessValidaterT;
        typedef PartialOrderValidater<Type, std::less_equal> LessEqualValidaterT;
        typedef PartialOrderValidater<Type, itl::contained_in> ContainedInValidaterT;

        enum Laws 
        { 
            strictWeakStdOrder,
            partialStdOrder,
            containedInOrder,
            inplacePlusAssociativity,
            inplacePlusNeutrality,
            inplacePlusCommutativity,
            inplaceStarAssociativity,
            inplaceStarCommutativity,
            Laws_size 
        };

        InplaceSetBaseValidater() {setProfile();}

        void setProfile()
        {
            _lawChoice.setSize(Laws_size);
            _lawChoice.setMaxWeights(100);
            _lawChoice[strictWeakStdOrder]         = 19;
            _lawChoice[partialStdOrder]            = 18;
            _lawChoice[containedInOrder]           = 18;
            _lawChoice[inplacePlusAssociativity]   = 9;
            _lawChoice[inplacePlusNeutrality]      = 9;
            _lawChoice[inplacePlusCommutativity]   = 9;
            _lawChoice[inplaceStarAssociativity]   = 9;
            _lawChoice[inplaceStarCommutativity]   = 9;
            //JODO _lawChoice[inplaceSymmetricDifference] = 10; // only (map|cop)<set> NOT (map|cop)<group>
            //JODO _lawChoice[inplacePlusDistributivity] = 100; // only (map|cop)<set> NOT (map|cop)<group>
            //JODO _lawChoice[inplaceStarDistributivity] = 100; // only (map|cop)<set> NOT (map|cop)<group>
            //JODO _lawChoice[inplacePlusDeMorgan]       = 100; // only (map|cop)<set> NOT (map|cop)<group>
            //JODO _lawChoice[inplaceStarDeMorgan]       = 100; // only (map|cop)<set> NOT (map|cop)<group>
            //JODO _lawChoice[inplaceUnionInvertability]  = 25;  // only cop NOT map
            _lawChoice.init();
        }


        LawValidaterI* chooseValidater()
        {
            switch(_lawChoice.some())
            {
            case strictWeakStdOrder:         return _lessValidater.chooseValidater();
            case partialStdOrder:            return _lessEqualValidater.chooseValidater();
            case containedInOrder:           return _containedInValidater.chooseValidater();
            case inplacePlusAssociativity:   
                if(   itl::type<Type>::is_interval_container() && type<Type>::is_interval_splitter()
                   && type<Type>::is_neutron_absorber() && type<Type>::is_neutron_emitter())
                    return new LawValidater<InplaceAssociativity<Type, inplace_plus, element_equal>, RandomGentor>;
                else
                    return new LawValidater<InplaceAssociativity<Type>, RandomGentor>;
            case inplacePlusNeutrality:      return new LawValidater<InplaceNeutrality<Type>, RandomGentor>;
            case inplacePlusCommutativity:   return new LawValidater<InplaceCommutativity<Type>, RandomGentor>;
            case inplaceStarAssociativity:
                if(   type<Type>::is_interval_container() && type<Type>::is_interval_splitter()
                   && type<Type>::is_neutron_absorber() && type<Type>::is_neutron_emitter())
                    return new LawValidater<InplaceAssociativity<Type, inplace_star, element_equal>, RandomGentor>;
                else
                    return new LawValidater<InplaceAssociativity<Type, inplace_star>, RandomGentor>;
            case inplaceStarCommutativity:   return new LawValidater<InplaceCommutativity<Type, inplace_star>, RandomGentor>;
            default: return NULL;
            }
        }

        void validate()
        {
            _validater = chooseValidater();
            if(_validater)
            {
                _validater->run();
                _validater->addFrequencies(_frequencies);
                _validater->addViolations(_violationsCount, _violations);
                delete _validater;
            }
        }

        void addFrequencies(ValidationCounterT& summary) { summary += _frequencies; }
        void addViolations(ViolationCounterT& summary, ViolationMapT& collector)
        { 
            summary += _violationsCount; 
            collector += _violations;  
        }


    private:
        ChoiceT        _lawChoice;
        LawValidaterI* _validater;
        ValidationCounterT _frequencies;
        ViolationCounterT  _violationsCount;
        ViolationMapT      _violations;

        LessValidaterT        _lessValidater;
        LessEqualValidaterT   _lessEqualValidater;
        ContainedInValidaterT _containedInValidater;
    };



    template <typename Type>
    class InplaceMapValidater : public InplaceSetBaseValidater<Type>
    {
    public:
        enum Laws 
        { 
            inplaceSetBaseLaws,
            inplaceSymmetricDifference,
            inplaceUnionInvertability,
            sectionAbsorbtion,
            Laws_size 
        };

        InplaceMapValidater() {setProfile();}

        void setProfile()
        {
            _lawChoice.setSize(Laws_size);
            _lawChoice.setMaxWeights(100);
            _lawChoice[inplaceSetBaseLaws]             = 85;
            if(Type::has_symmetric_difference())
            {
                _lawChoice[inplaceSymmetricDifference] = 5;
                _lawChoice[inplaceUnionInvertability]  = 5;
                _lawChoice[sectionAbsorbtion]          = 5;
            }
            else
            {
                _lawChoice[inplaceSymmetricDifference] = 0;
                _lawChoice[inplaceUnionInvertability]  = 7;
                _lawChoice[sectionAbsorbtion]          = 8;
            }
            _lawChoice.init();
        }


        LawValidaterI* chooseValidater()
        {
            switch(_lawChoice.some())
            {
            case inplaceSetBaseLaws:        
                return InplaceSetBaseValidater<Type>::chooseValidater();
            case inplaceSymmetricDifference: 
                return new LawValidater<InplaceSymmetricDifference<Type>, RandomGentor>;
            case inplaceUnionInvertability: 
                return new LawValidater<InplaceUnionInvertability<Type,itl::protonic_equal>, RandomGentor >;
            case sectionAbsorbtion:            
                return new LawValidater<SectionAbsorbtion<Type,itl::protonic_equal>, RandomGentor>;
            default: 
                return NULL;
            }
        }

        void validate()
        {
            _validater = chooseValidater();
            if(_validater)
            {
                _validater->run();
                _validater->addFrequencies(_frequencies);
                _validater->addViolations(_violationsCount, _violations);
                delete _validater;
            }
        }

        void addFrequencies(ValidationCounterT& summary) { summary += _frequencies; }
        void addViolations(ViolationCounterT& summary, ViolationMapT& collector)
        { 
            summary += _violationsCount; 
            collector += _violations;  
        }


    private:
        ChoiceT        _lawChoice;
        LawValidaterI* _validater;
        ValidationCounterT _frequencies;
        ViolationCounterT  _violationsCount;
        ViolationMapT      _violations;
    };


    template <typename Type>
    class InplaceSetValidater : public InplaceSetBaseValidater<Type>
    {
    public:
        enum Laws 
        { 
            inplaceSetBaseLaws,
            inplaceSymmetricDifference,
            inplaceUnionInvertability,
            inplacePlusDistributivity,
            inplaceStarDistributivity,
            inplacePlusDashRightDistrib,
            inplaceStarDashRightDistrib,
            inplacePlusDeMorgan,
            inplaceStarDeMorgan,
            Laws_size 
        };

        InplaceSetValidater() {setProfile();}

        void setProfile()
        {
            _lawChoice.setSize(Laws_size);
            _lawChoice.setMaxWeights(100);
            _lawChoice[inplaceSetBaseLaws]          = 44;
            _lawChoice[inplaceSymmetricDifference]  = 7;
            _lawChoice[inplaceUnionInvertability]   = 7;
            _lawChoice[inplacePlusDistributivity]   = 7;
            _lawChoice[inplaceStarDistributivity]   = 7;
            _lawChoice[inplacePlusDashRightDistrib] = 7;
            _lawChoice[inplaceStarDashRightDistrib] = 7;
            _lawChoice[inplacePlusDeMorgan]         = 7;
            _lawChoice[inplaceStarDeMorgan]         = 7;
            _lawChoice.init();
        }


        LawValidaterI* chooseValidater()
        {
            switch(_lawChoice.some())
            {
            case inplaceSetBaseLaws:         return InplaceSetBaseValidater<Type>::chooseValidater();
            case inplaceSymmetricDifference: return new LawValidater<InplaceSymmetricDifference<Type>, RandomGentor>;
            case inplaceUnionInvertability:  return new LawValidater<InplaceUnionInvertability<Type>, RandomGentor>;
            case inplacePlusDistributivity:  return new LawValidater<InplaceDistributivity<Type, inplace_plus, inplace_star, itl::element_equal>, RandomGentor>;
            case inplaceStarDistributivity:  return new LawValidater<InplaceDistributivity<Type, inplace_star, inplace_plus>, RandomGentor>;
            case inplacePlusDashRightDistrib:return new LawValidater<InplaceRightDistributivity<Type, inplace_plus, inplace_minus>, RandomGentor>;
            case inplaceStarDashRightDistrib:return new LawValidater<InplaceRightDistributivity<Type, inplace_star, inplace_minus>, RandomGentor>;
            case inplacePlusDeMorgan:        return new LawValidater<InplaceDeMorgan<Type, inplace_plus, inplace_star, itl::element_equal>, RandomGentor>;
            case inplaceStarDeMorgan:        return new LawValidater<InplaceDeMorgan<Type, inplace_star, inplace_plus, itl::element_equal>, RandomGentor>;
            default: return NULL;
            }
        }

        void validate()
        {
            _validater = chooseValidater();
            if(_validater)
            {
                _validater->run();
                _validater->addFrequencies(_frequencies);
                _validater->addViolations(_violationsCount, _violations);
                delete _validater;
            }
        }

        void addFrequencies(ValidationCounterT& summary) { summary += _frequencies; }
        void addViolations(ViolationCounterT& summary, ViolationMapT& collector)
        { 
            summary += _violationsCount; 
            collector += _violations;  
        }

    private:
        ChoiceT        _lawChoice;
        LawValidaterI* _validater;
        ValidationCounterT _frequencies;
        ViolationCounterT  _violationsCount;
        ViolationMapT      _violations;
    };


    template <typename Type>
    class IntervalMorphicValidater : public AlgebraValidater
    {
    public:
        enum Laws 
        { 
            atomize_plus,
            atomize_minus,
            atomize_star,
            cluster_plus,
            cluster_minus,
            cluster_star,
            atomize_insert,
            atomize_erase,
            cluster_insert,
            cluster_erase,
            join_plus,
            absorb_plus,
            Laws_size 
        };

        IntervalMorphicValidater() {setProfile();}

        void setProfile()
        {
            _lawChoice.setSize(Laws_size);
            _lawChoice.setMaxWeights(100);
            _lawChoice[atomize_plus]   = 10;
            _lawChoice[atomize_minus]  = 5;
            _lawChoice[atomize_star]   = 5;
            _lawChoice[cluster_plus]   = 10;
            _lawChoice[cluster_minus]  = 5;
            _lawChoice[cluster_star]   = 5;
            _lawChoice[atomize_insert] = 10;
            _lawChoice[atomize_erase]  = 10;
            _lawChoice[cluster_insert] = 10;
            _lawChoice[cluster_erase]  = 20;
            _lawChoice[join_plus]      = 10;
            _lawChoice[absorb_plus]    = 0;
            _lawChoice.init();
        }


        LawValidaterI* chooseValidater()
        {
            switch(_lawChoice.some())
            {
            case atomize_plus:    
                return new LawValidater
                           <
                               BinaryPushout
                               <
                                    Type, 
                                    typename Type::atomized_type, 
                                    Interval::Atomize, 
                                    inplace_plus
                               >,                                
                               RandomGentor
                           >();
            case atomize_minus:  return new LawValidater<BinaryPushout<Type, typename Type::atomized_type, Interval::Atomize, inplace_minus>, RandomGentor>();
            case atomize_star:   return new LawValidater<BinaryPushout<Type, typename Type::atomized_type, Interval::Atomize, inplace_star>,  RandomGentor>();
            case cluster_plus:   return new LawValidater<BinaryPushout<typename Type::atomized_type, Type, Interval::Cluster, inplace_plus>,  RandomGentor>();
            case cluster_minus:  return new LawValidater<BinaryPushout<typename Type::atomized_type, Type, Interval::Cluster, inplace_minus>, RandomGentor>();
            case cluster_star:   return new LawValidater<BinaryPushout<typename Type::atomized_type, Type, Interval::Cluster, inplace_star>,  RandomGentor>();
            case atomize_insert: return new LawValidater<BinaryPushout<Type, typename Type::atomized_type, Interval::Atomize, inserter>,      RandomGentor>();
            case atomize_erase:  return new LawValidater<BinaryPushout<Type, typename Type::atomized_type, Interval::Atomize, eraser>,        RandomGentor>();
            case cluster_insert: return new LawValidater<BinaryPushout<typename Type::atomized_type, Type, Interval::Cluster, inserter>,      RandomGentor>();
            case cluster_erase:  return new LawValidater<BinaryPushout<typename Type::atomized_type, Type, Interval::Cluster, eraser>,        RandomGentor>();
            case join_plus:      return new LawValidater<BinaryPushout<Type, typename Type::joint_type,    Interval::Join,    inplace_plus>,  RandomGentor>();
            //JODO absorb_plus holds for interval_map. For split_interval_map element_equal has to be used as equality-relation.
            //case absorb_plus:    return new LawValidater<BinaryPushout<Type, typename Type::neutron_absorber_type, Interval::AbsorbNeutrons, inplace_plus>,  RandomGentor>();
            //JODO doc: violated: inverse required: case absorb_minus:    return new LawValidater<BinaryPushout<Type, typename Type::neutron_absorber_type, Interval::AbsorbNeutrons, inplace_minus>,  RandomGentor>();
            default: return NULL;
            }
        }

        void validate()
        {
            _validater = chooseValidater();
            if(_validater)
            {
                _validater->run();
                _validater->addFrequencies(_frequencies);
                _validater->addViolations(_violationsCount, _violations);
                delete _validater;
            }
        }

        void addFrequencies(ValidationCounterT& summary) { summary += _frequencies; }
        void addViolations(ViolationCounterT& summary, ViolationMapT& collector)
        { 
            summary += _violationsCount; 
            collector += _violations;  
        }

    private:
        ChoiceT        _lawChoice;
        LawValidaterI* _validater;
        ValidationCounterT _frequencies;
        ViolationCounterT  _violationsCount;
        ViolationMapT      _violations;
    };


    template <typename Type>
    class IntervalSetValidater : public InplaceSetValidater<Type>
    {
    public:
        enum Laws 
        { 
            inplaceSetLaws,
            homomorphismLaws,
            Laws_size 
        };

        IntervalSetValidater() {setProfile();}

        void setProfile()
        {
            _lawChoice.setSize(Laws_size);
            _lawChoice.setMaxWeights(100);
            const bool morphism_exists   = !type<typename Type::domain_type>::is_continuous();
            const int  morphism_share    = 15;
            _lawChoice[inplaceSetLaws]   = morphism_exists ? 100 - morphism_share : 100;
            _lawChoice[homomorphismLaws] = 100 - _lawChoice[inplaceSetLaws];
            _lawChoice.init();
        }


        LawValidaterI* chooseValidater()
        {
            switch(_lawChoice.some())
            {
            case inplaceSetLaws:     return InplaceSetValidater<Type>::chooseValidater();
            case homomorphismLaws:   return _morphicValidater.chooseValidater();
            default: return NULL;
            }
        }

        void validate()
        {
            _validater = chooseValidater();
            if(_validater)
            {
                _validater->run();
                _validater->addFrequencies(_frequencies);
                _validater->addViolations(_violationsCount, _violations);
                delete _validater;
            }
        }

        void addFrequencies(ValidationCounterT& summary) { summary += _frequencies; }
        void addViolations(ViolationCounterT& summary, ViolationMapT& collector)
        { 
            summary += _violationsCount; 
            collector += _violations;  
        }

    private:
        IntervalMorphicValidater<Type> _morphicValidater;

        ChoiceT        _lawChoice;
        LawValidaterI* _validater;
        ValidationCounterT _frequencies;
        ViolationCounterT  _violationsCount;
        ViolationMapT      _violations;
    };


    template <typename Type>
    class IntervalMapValidater : public InplaceMapValidater<Type>
    {
    public:
        enum Laws 
        { 
            inplaceMapLaws,
            homomorphismLaws,
            Laws_size 
        };

        IntervalMapValidater() {setProfile();}

        void setProfile()
        {
            _lawChoice.setSize(Laws_size);
            _lawChoice.setMaxWeights(100);
            const bool morphism_exists    = !type<typename Type::domain_type>::is_continuous();
            const int  morphism_share     = 30;
            _lawChoice[inplaceMapLaws]= morphism_exists ? 100 - morphism_share : 100;
            _lawChoice[homomorphismLaws]  = 100 - _lawChoice[inplaceMapLaws];
            _lawChoice.init();
        }

        bool hasValidProfile()
        {
        }

        LawValidaterI* chooseValidater()
        {
            switch(_lawChoice.some())
            {
            case inplaceMapLaws: return InplaceMapValidater<Type>::chooseValidater();
            case homomorphismLaws:   return _morphicValidater.chooseValidater();
            default: return NULL;
            }
        }

        void validate()
        {
            _validater = chooseValidater();
            if(_validater)
            {
                _validater->run();
                _validater->addFrequencies(_frequencies);
                _validater->addViolations(_violationsCount, _violations);
                delete _validater;
            }
        }

        void addFrequencies(ValidationCounterT& summary) { summary += _frequencies; }
        void addViolations(ViolationCounterT& summary, ViolationMapT& collector)
        { 
            summary += _violationsCount; 
            collector += _violations;  
        }

    private:
        IntervalMorphicValidater<Type> _morphicValidater;

        ChoiceT        _lawChoice;
        LawValidaterI* _validater;
        ValidationCounterT _frequencies;
        ViolationCounterT  _violationsCount;
        ViolationMapT      _violations;
    };


} //namespace itl

