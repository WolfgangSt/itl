#pragma once

#include <iostream>
#include <stdio.h>
#include <time.h>
#include <validate/typevalidater.h>

namespace itl
{
    namespace Type 
    {
        enum Types 
        { 
            itl_set, interval_set, split_interval_set, 
            itl_map, split_interval_map, 
            Types_size 
        };
    }

    namespace AtomicType 
    {
        enum AtomicTypes { Int, Double, AtomicTypes_size };
    }

    
    class RealmValidater
    {
    public:
        RealmValidater() { setProfile(); }

        void setProfile()
        {
            _typeChoice.setSize(Type::Types_size);
            _typeChoice.setMaxWeights(100);
            _typeChoice[Type::itl_set]             = 0;
            _typeChoice[Type::interval_set]        = 50;
            _typeChoice[Type::split_interval_set]  = 0;
            _typeChoice[Type::itl_map]             = 0;
            _typeChoice[Type::split_interval_map]  = 50;
            _typeChoice.init();

            _atomicTypeChoice.setSize(AtomicType::AtomicTypes_size);
            _atomicTypeChoice.setMaxWeights(100);
            _atomicTypeChoice[AtomicType::Int]     = 50;
            _atomicTypeChoice[AtomicType::Double]  = 50;
            _atomicTypeChoice.init();
        }

        void validate()
        {
            srand(static_cast<unsigned>(time(NULL)));

            //for(int idx=0; idx<=10000; idx++)
            for(int idx=0; true; idx++)
            {
                if(idx>0 && idx % 100 == 0)
                    reportFrequencies();
                validateType();
            }
        }

        AlgebraValidater* chooseValidater()
        {
            switch(_typeChoice.some())
            {
            //case Type::itl_set:
            //    {
            //        switch(_atomicTypeChoice.some())
            //        {
            //        case AtomicType::Int:      return new InplaceSetValidater<itl::set<int> >; 
            //        case AtomicType::Double: return new InplaceSetValidater<itl::set<double> >; 
            //        default: return NULL;
            //        }
            //        break;
            //    }
            case Type::interval_set:
                {
                    switch(_atomicTypeChoice.some())
                    {
                    case AtomicType::Int:    return new IntervalSetValidater<interval_set<int> >;
                    case AtomicType::Double: return new InplaceSetValidater<interval_set<double> >;
                    default: return NULL;
                    }
                    break;
                }
            //case Type::split_interval_set:
            //    {
            //        switch(_atomicTypeChoice.some())
            //        {
            //        case AtomicType::Int:    return new IntervalSetValidater<split_interval_set<int> >;
            //        case AtomicType::Double: return new IntervalSetValidater<split_interval_set<double> >;
            //        default: return NULL;
            //        }
            //        break;
            //    }
            //case Type::itl_map:
            //    {
            //        switch(_atomicTypeChoice.some())
            //        {
            //        case AtomicType::Int:    return new InplaceCopValidater<itl::map<int,int> >; 
            //        case AtomicType::Double: return new InplaceSetBaseValidater<itl::map<int,double> >; 
            //        default: return NULL;
            //        }
            //        break;
            //    }
            case Type::split_interval_map:
                {
                    switch(_atomicTypeChoice.some())
                    {
                    case AtomicType::Int:    return new IntervalMapValidater<split_interval_map<int,double> >; 
                    case AtomicType::Double: return new IntervalMapValidater<split_interval_map<double,int> >; 
                    default: return NULL;
                    }
                    break;
                }
            default: return NULL;
            } //switch()
        }


        void validateType()
        {
            _validater = chooseValidater();
            _validater->validate();
            _validater->addFrequencies(_frequencies);
            _validater->addViolations(_violationsCount, _violations);
            delete _validater;
        }

        void reportFrequencies()
        {
            std::cout << "------------------------------------------------------------------------------" << std::endl;
            int valid_count = 1;
            FORALL(ValidationCounterT, it, _frequencies)
            {
                printf("%3d %-66s%8d\n", valid_count, it->KEY_VALUE.c_str(), it->CONT_VALUE);
                valid_count++;
            }
            std::cout << "------------------------------------------------------------------------------" << std::endl;
            int violation_count = 1;
            FORALL(ViolationMapT, it, _violations)
            {
                printf("%3d %-66s%8d\n", violation_count, it->KEY_VALUE.c_str(), it->CONT_VALUE.getViolationsCount());
                violation_count++;
            }
            if(!_violations.empty())
                std::cout << "------------------------------------------------------------------------------" << std::endl;
            FORALL(ViolationMapT, it, _violations)
            {
                PolyLawViolations violas = it->CONT_VALUE;
                violas.reportFirst();
            }
            if(!_violations.empty())
                std::cout << "------------------------------------------------------------------------------" << std::endl;
        }

    private:
        ChoiceT            _typeChoice;
        ChoiceT            _atomicTypeChoice;
        AlgebraValidater*  _validater;
        ValidationCounterT _frequencies;
        ViolationCounterT  _violationsCount;
        ViolationMapT      _violations;
    };


} //namespace itl

