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

	private:
		void setTypeNames()
		{
			std::vector<std::string> type_names(Type::Types_size);
            type_names[Type::itl_set]            = "itl_set"; 
			type_names[Type::interval_set]       = "interval_set"; 
			type_names[Type::split_interval_set] = "split_interval_set"; 
            type_names[Type::itl_map]            = "itl_map"; 
			type_names[Type::split_interval_map] = "split_interval_map"; 
			_typeChoice.setTypeNames(type_names);
		}
		void setAtomicTypeNames()
		{
			std::vector<std::string> type_names(AtomicType::AtomicTypes_size);
            type_names[AtomicType::Int]          = "Int"; 
			type_names[AtomicType::Double]       = "Double"; 
			_atomicTypeChoice.setTypeNames(type_names);
		}

		void setInvalid() { _isValid = false; }

	public:
		bool hasValidProfile()const { return _isValid; }

        void setProfile()
        {
            _typeChoice.setSize(Type::Types_size);
            _typeChoice.setMaxWeights(100);
            _typeChoice[Type::itl_set]             = 0;
            _typeChoice[Type::interval_set]        = 0;
            _typeChoice[Type::split_interval_set]  = 0;
            _typeChoice[Type::itl_map]             = 50;
            _typeChoice[Type::split_interval_map]  = 50;
			setTypeNames();
            _typeChoice.init();

            _atomicTypeChoice.setSize(AtomicType::AtomicTypes_size);
            _atomicTypeChoice.setMaxWeights(100);
            _atomicTypeChoice[AtomicType::Int]     = 100;
            _atomicTypeChoice[AtomicType::Double]  = 0;
			setAtomicTypeNames();
            _atomicTypeChoice.init();

			if(!_typeChoice.is_consistent())
				std::cout << _typeChoice.inconsitencyMessage("RealmValidater::setProfile()") << std::endl;

			if(!_atomicTypeChoice.is_consistent())
				std::cout << _atomicTypeChoice.inconsitencyMessage("RealmValidater::setProfile()") << std::endl;

        }

        void validate()
        {
			srand(static_cast<unsigned>(time(NULL)));

			//for(int idx=0; idx<=10000; idx++)
			for(int idx=0; hasValidProfile(); idx++)
			{
				if(idx>0 && idx % 100 == 0)
					reportFrequencies();
				validateType();
			}
        }

        AlgebraValidater* chooseValidater()
        {
			int typeChoice       = _typeChoice.some();
			int atomicTypeChoice = _atomicTypeChoice.some();

            switch(atomicTypeChoice)
            {
            case AtomicType::Int:    
            case AtomicType::Double: break;
            default: { 
					reportTypeChoiceError(atomicTypeChoice, _atomicTypeChoice); 
					setInvalid();
					return NULL; 
				}
            }

            switch(typeChoice)
            {
            //case Type::itl_set: {
            //        switch(atomicTypeChoice) {
            //        case AtomicType::Int:    return new InplaceSetValidater<itl::set<int> >; 
            //        //case AtomicType::Double: return new InplaceSetValidater<itl::set<double> >; 
            //        }
            //    }
            //case Type::interval_set: {
            //        switch(atomicTypeChoice) {
            //        case AtomicType::Int:    return new IntervalSetValidater<interval_set<int> >;
            //        case AtomicType::Double: return new InplaceSetValidater<interval_set<double> >;
            //        }
            //    }
            //case Type::split_interval_set: {
            //        switch(atomicTypeChoice) {
            //        case AtomicType::Int:    return new IntervalSetValidater<split_interval_set<int> >;
            //        case AtomicType::Double: return new IntervalSetValidater<split_interval_set<double> >;
            //        }
            //    }
            case Type::itl_map: {
                    switch(atomicTypeChoice) {
                    case AtomicType::Int:    return new InplaceCopValidater<itl::map<int,int> >; 
                    case AtomicType::Double: return new InplaceSetBaseValidater<itl::map<int,double> >; 
                    }
                }
            case Type::split_interval_map: {
                    switch(atomicTypeChoice) {
                    case AtomicType::Int:    return new IntervalMapValidater<split_interval_map<int,double> >; 
                    case AtomicType::Double: return new IntervalMapValidater<split_interval_map<double,int> >; 
                    }
                    break;
                }
            default: { 
					reportTypeChoiceError(typeChoice, _typeChoice); 
					setInvalid();
					return NULL; 
				}
            } //switch()

			return NULL; //just to please the compiler ;)
        }


        void validateType()
        {
            _validater = chooseValidater();
			if(_validater)
			{
				_validater->validate();
				_validater->addFrequencies(_frequencies);
				_validater->addViolations(_violationsCount, _violations);
				delete _validater;
			}
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

		void reportTypeChoiceError(int typeChoice, const ChoiceT& chooser)const
		{
			std::cout << "Type choice: " << typeChoice << " is out of range\n"
				<< "Expected types and their weights are:\n"
				<< chooser.asString();
		}

    private:
        ChoiceT            _typeChoice;
        ChoiceT            _atomicTypeChoice;
        AlgebraValidater*  _validater;
        ValidationCounterT _frequencies;
        ViolationCounterT  _violationsCount;
        ViolationMapT      _violations;
		bool               _isValid;
    };


} //namespace itl

