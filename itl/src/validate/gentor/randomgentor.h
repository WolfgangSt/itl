/*----------------------------------------------------------------------------+
Interval Template Library
Author: Joachim Faulhaber
Copyright (c) 2007-2008: Joachim Faulhaber
+-----------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+----------------------------------------------------------------------------*/
#pragma once


#include <itl/numbergentor.hpp>
#include <itl/setgentor.hpp>
#include <itl/mapgentor.hpp>
#include <itl/itvgentor.hpp>
#include <itl/interval_set.hpp>
#include <itl/split_interval_set.hpp>
#include <itl/split_interval_map.hpp>
#include <validate/gentor/gentorprofile.h>


namespace itl
{

    // ----------------------------------------------------------
    template <class ValueT> class RandomGentor;
    template <> class RandomGentor<int> : public NumberGentorT<int> {};
    template <> class RandomGentor<double> : public NumberGentorT<double> {};
    // ----- sets ----------------------------------------------------------------
    template <> class RandomGentor<itl::set<int> > : public SetGentorT<itl::set<int> > {};
    template <> class RandomGentor<interval_set<int> > : public SetGentorT<interval_set<int> > {};
    template <> class RandomGentor<split_interval_set<int> > : public SetGentorT<split_interval_set<int> > {};
    template <> class RandomGentor<itl::set<double> > : public SetGentorT<itl::set<double> > {};
    template <> class RandomGentor<interval_set<double> > : public SetGentorT<interval_set<double> > {};
    template <> class RandomGentor<split_interval_set<double> > : public SetGentorT<split_interval_set<double> > {};
    // ----- maps ----------------------------------------------------------------
    template <> class RandomGentor<itl::map<int,int> > : public MapGentorT<itl::map<int,int> > {};
    template <> class RandomGentor<itl::map<int,double> > : public MapGentorT<itl::map<int,double> > {};
    template <> class RandomGentor<itl::map<double,int> > : public MapGentorT<itl::map<double,int> > {};
    //CL template <> class RandomGentor<joint_interval_map<int,double> > : public MapGentorT<joint_interval_map<int,double> > {};
    //CL template <> class RandomGentor<joint_interval_map<double,int> > : public MapGentorT<joint_interval_map<double,int> > {};
    template <> class RandomGentor<split_interval_map<int,double> > : public MapGentorT<split_interval_map<int,double> > {};
    template <> class RandomGentor<split_interval_map<double,int> > : public MapGentorT<split_interval_map<double,int> > {};

    //CL template <> class RandomGentor<joint_interval_map<int,int> > : public MapGentorT<joint_interval_map<int,int> > {};

    //JODO THINK: Recursive template for the general case!!
    //template <class ElemT> class RandomGentor<itl::set<ElemT> > : public SetGentorT<itl::set<ElemT> > 
    //{
    //private:
    //    RandomGentor<ElemT>    m_domainGentor;
    //};

    // ----------------------------------------------------------
    // class template SomeValue:
    // TargetT is a value tuple that fits to the value generator gentor
    // of type GentorT<TargetT>. The special kind of generator can be
    // passed by the user. The only requirement is that the generator
    // implements a function 'some' which is called to generate a tuple
    // of type TargetT
    template <class TargetT, template<class>class GentorT> struct SomeValue
    {
        static void apply(TargetT& value, GentorT<TargetT>& gentor); 
    };

    template <class TargetT> 
    struct SomeValue<TargetT, RandomGentor>
    {
        static void apply(TargetT& value, RandomGentor<TargetT>& gentor) 
        {
            gentor.some(value);
        }
    };
    // ----------------------------------------------------------

    /*JODO THINK
    // ----------------------------------------------------------
    // class template Calibrate:
    // TargetT is a value tuple that fits to the value generator gentor
    // of type GentorT<TargetT>. The special kind of generator can be
    // passed by the user. The only requirement is that the generator
    // implements a function 'calibrate' which is calls to calibrate 
    // each generator of generator tuple GentorT<TargetT>
    template <template<class>class GentorT, 
    template<class>class GentorProfileT, class TargetT> struct Calibrate
    {
    static void apply(GentorT<TargetT>& gentor, GentorProfileT<TargetT>& profile); 
    };

    template <class TargetT> 
    struct Calibrate<RandomGentor, RandomGentorProfile, TargetT>
    {
    static void apply(RandomGentor<TargetT>& gentor, RandomGentorProfile<TargetT>& profile) 
    {
    gentor.calibrate(profile);
    }
    };
    // ----------------------------------------------------------
    */

    // ---------------------------------------------------------------------------
    // ---------------------------------------------------------------------------
    template <class TargetT, template<class>class GentorT> struct Calibrater
    {
        static void apply(GentorT<TargetT>& gentor); 
    };

    template <> 
    struct Calibrater<int, RandomGentor>
    {
        static void apply(RandomGentor<int>& gentor)
        {
            // Set the range within which the sizes of the generated object varies.
            gentor.setRange(GentorProfileSgl::it()->range_int());
        }
    };

    template <> 
    struct Calibrater<double, RandomGentor>
    {
        static void apply(RandomGentor<double>& gentor) 
        {
            // Set the range within which the sizes of the generated object varies.
            gentor.setRange(GentorProfileSgl::it()->range_double());
        }
    };

    template <> 
    struct Calibrater<itl::set<int>, RandomGentor>
    {
        static void apply(RandomGentor<itl::set<int> >& gentor) 
        {
            // Set the range within which the sizes of the generated object varies.
            // interval<int> range = rightOpenInterval<int>(0,10); //JODO: From SysCalibrater
            //JODO gentor.calibrate(profile);

            gentor.setRangeOfSampleSize(GentorProfileSgl::it()->range_ContainerSize());

            // If it is a container: (Create and) Pass the generator(s) for their contents
            // NumberGentorT<int> intGentor;
            NumberGentorT<int>* intGentor = new NumberGentorT<int>;
            intGentor->setRange(GentorProfileSgl::it()->range_int());
            gentor.setDomainGentor(intGentor);
        }
    };

    template <> 
    struct Calibrater<itl::set<double>, RandomGentor>
    {
        static void apply(RandomGentor<itl::set<double> >& gentor) 
        {
            gentor.setRangeOfSampleSize(GentorProfileSgl::it()->range_ContainerSize());

            // If it is a container: (Create and) Pass the generator(s) for their contents
            // NumberGentorT<int> intGentor;
            NumberGentorT<double>* elemGentor = new NumberGentorT<double>;
            elemGentor->setRange(GentorProfileSgl::it()->range_double());
            gentor.setDomainGentor(elemGentor);
        }
    };


    template <> 
    struct Calibrater<interval_set<int>, RandomGentor>
    {
        static void apply(RandomGentor<interval_set<int> >& gentor) 
        {
            // Set the range within which the sizes of the generated object varies.
            // interval<int> range = rightOpenInterval<int>(0,10); //JODO: From SysCalibrater
            //JODO gentor.calibrate(profile);

            gentor.setRangeOfSampleSize(GentorProfileSgl::it()->range_ContainerSize());

            // If it is a container: (Create and) Pass the generator(s) for their contents
            // NumberGentorT<int> intGentor;
            ItvGentorT<int>* itvGentor = new ItvGentorT<int>;
            interval<int> valRange = GentorProfileSgl::it()->range_interval_int();
            itvGentor->setValueRange(valRange.lower_bound(), valRange.upper_bound());
            itvGentor->setMaxIntervalLength(GentorProfileSgl::it()->maxIntervalLength()); //JODO
            gentor.setDomainGentor(itvGentor);
        }
    };

    template <> 
    struct Calibrater<interval_set<double>, RandomGentor>
    {
        static void apply(RandomGentor<interval_set<double> >& gentor) 
        {
            gentor.setRangeOfSampleSize(GentorProfileSgl::it()->range_ContainerSize());

            // If it is a container: (Create and) Pass the generator(s) for their contents
            // NumberGentorT<int> intGentor;
            ItvGentorT<double>* itvGentor = new ItvGentorT<double>;
            interval<double> valRange = GentorProfileSgl::it()->range_interval_double();
            itvGentor->setValueRange(valRange.lower_bound(), valRange.upper_bound());
            itvGentor->setMaxIntervalLength(GentorProfileSgl::it()->maxIntervalLength()); //JODO
            gentor.setDomainGentor(itvGentor);
        }
    };

    template <> 
    struct Calibrater<split_interval_set<int>, RandomGentor>
    {
        static void apply(RandomGentor<split_interval_set<int> >& gentor) 
        {
            // Set the range within which the sizes of the generated object varies.
            // interval<int> range = rightOpenInterval<int>(0,10); //JODO: From SysCalibrater
            //JODO gentor.calibrate(profile);

            gentor.setRangeOfSampleSize(GentorProfileSgl::it()->range_ContainerSize());

            // If it is a container: (Create and) Pass the generator(s) for their contents
            // NumberGentorT<int> intGentor;
            ItvGentorT<int>* itvGentor = new ItvGentorT<int>;
            interval<int> valRange = GentorProfileSgl::it()->range_interval_int();
            itvGentor->setValueRange(valRange.lower_bound(), valRange.upper_bound());
            itvGentor->setMaxIntervalLength(GentorProfileSgl::it()->maxIntervalLength()); //JODO
            gentor.setDomainGentor(itvGentor);
        }
    };

    template <> 
    struct Calibrater<split_interval_set<double>, RandomGentor>
    {
        static void apply(RandomGentor<split_interval_set<double> >& gentor) 
        {
            gentor.setRangeOfSampleSize(GentorProfileSgl::it()->range_ContainerSize());

            // If it is a container: (Create and) Pass the generator(s) for their contents
            // NumberGentorT<int> intGentor;
            ItvGentorT<double>* itvGentor = new ItvGentorT<double>;
            interval<double> valRange = GentorProfileSgl::it()->range_interval_double();
            itvGentor->setValueRange(valRange.lower_bound(), valRange.upper_bound());
            itvGentor->setMaxIntervalLength(GentorProfileSgl::it()->maxIntervalLength()); //JODO
            gentor.setDomainGentor(itvGentor);
        }
    };

    template <> 
    struct Calibrater<itl::map<int,int>, RandomGentor>
    {
        static void apply(RandomGentor<itl::map<int,int> >& gentor) 
        {
            // Set the range within which the sizes of the generated object varies.
            // interval<int> range = rightOpenInterval<int>(0,10); //JODO: From SysCalibrater
            //JODO gentor.calibrate(profile);

            gentor.setRangeOfSampleSize(GentorProfileSgl::it()->range_ContainerSize());

            // If it is a container: (Create and) Pass the generator(s) for their contents
            // NumberGentorT<int> intGentor;
            NumberGentorT<int>* domainGentor = new NumberGentorT<int>;
            NumberGentorT<int>* codomainGentor = new NumberGentorT<int>;
            domainGentor->setRange(GentorProfileSgl::it()->range_int());
            codomainGentor->setRange(GentorProfileSgl::it()->range_int());
            gentor.setDomainGentor(domainGentor);
            gentor.setCodomainGentor(codomainGentor);
        }
    };

    template <> 
    struct Calibrater<itl::map<int,double>, RandomGentor>
    {
        static void apply(RandomGentor<itl::map<int,double> >& gentor) 
        {
            // Set the range within which the sizes of the generated object varies.
            // interval<int> range = rightOpenInterval<int>(0,10); //JODO: From SysCalibrater
            //JODO gentor.calibrate(profile);

            gentor.setRangeOfSampleSize(GentorProfileSgl::it()->range_ContainerSize());

            // If it is a container: (Create and) Pass the generator(s) for their contents
            // NumberGentorT<int> intGentor;
            NumberGentorT<int>* domainGentor = new NumberGentorT<int>;
            NumberGentorT<double>* codomainGentor = new NumberGentorT<double>;
            domainGentor->setRange(GentorProfileSgl::it()->range_int());
            codomainGentor->setRange(GentorProfileSgl::it()->range_double());
            gentor.setDomainGentor(domainGentor);
            gentor.setCodomainGentor(codomainGentor);
        }
    };

    template <> 
    struct Calibrater<itl::map<double,int>, RandomGentor>
    {
        static void apply(RandomGentor<itl::map<double,int> >& gentor) 
        {
            // Set the range within which the sizes of the generated object varies.
            // interval<int> range = rightOpenInterval<int>(0,10); //JODO: From SysCalibrater
            //JODO gentor.calibrate(profile);

            gentor.setRangeOfSampleSize(GentorProfileSgl::it()->range_ContainerSize());

            // If it is a container: (Create and) Pass the generator(s) for their contents
            // NumberGentorT<int> intGentor;
            NumberGentorT<double>* domainGentor = new NumberGentorT<double>;
            NumberGentorT<int>* codomainGentor = new NumberGentorT<int>;
            domainGentor->setRange(GentorProfileSgl::it()->range_double());
            codomainGentor->setRange(GentorProfileSgl::it()->range_int());
            gentor.setDomainGentor(domainGentor);
            gentor.setCodomainGentor(codomainGentor);
        }
    };


    //CL
    //template <> 
    //struct Calibrater<itl::cop<int,int>, RandomGentor>
    //{
    //    static void apply(RandomGentor<itl::cop<int,int> >& gentor) 
    //    {
    //        // Set the range within which the sizes of the generated object varies.
    //        // interval<int> range = rightOpenInterval<int>(0,10); //JODO: From SysCalibrater
    //        //JODO gentor.calibrate(profile);

    //        gentor.setRangeOfSampleSize(GentorProfileSgl::it()->range_ContainerSize());

    //        // If it is a container: (Create and) Pass the generator(s) for their contents
    //        // NumberGentorT<int> intGentor;
    //        NumberGentorT<int>* domainGentor = new NumberGentorT<int>;
    //        NumberGentorT<int>* codomainGentor = new NumberGentorT<int>;
    //        domainGentor->setRange(GentorProfileSgl::it()->range_int());
    //        codomainGentor->setRange(GentorProfileSgl::it()->range_int());
    //        gentor.setDomainGentor(domainGentor);
    //        gentor.setCodomainGentor(codomainGentor);
    //    }
    //};

    //template <> 
    //struct Calibrater<itl::cop<int,double>, RandomGentor>
    //{
    //    static void apply(RandomGentor<itl::cop<int,double> >& gentor) 
    //    {
    //        // Set the range within which the sizes of the generated object varies.
    //        // interval<int> range = rightOpenInterval<int>(0,10); //JODO: From SysCalibrater
    //        //JODO gentor.calibrate(profile);

    //        gentor.setRangeOfSampleSize(GentorProfileSgl::it()->range_ContainerSize());

    //        // If it is a container: (Create and) Pass the generator(s) for their contents
    //        // NumberGentorT<int> intGentor;
    //        NumberGentorT<int>* domainGentor = new NumberGentorT<int>;
    //        NumberGentorT<double>* codomainGentor = new NumberGentorT<double>;
    //        domainGentor->setRange(GentorProfileSgl::it()->range_int());
    //        codomainGentor->setRange(GentorProfileSgl::it()->range_double());
    //        gentor.setDomainGentor(domainGentor);
    //        gentor.setCodomainGentor(codomainGentor);
    //    }
    //};

    // ---------------------------------------------------------------------------
    // ---------------------------------------------------------------------------
    //CL
    //template <> 
    //struct Calibrater<joint_interval_map<int,int>, RandomGentor>
    //{
    //    static void apply(RandomGentor<joint_interval_map<int,int> >& gentor) 
    //    {
    //        // Set the range within which the sizes of the generated object varies.
    //        // interval<int> range = rightOpenInterval<int>(0,10); //JODO: From SysCalibrater
    //        //JODO gentor.calibrate(profile);

    //        gentor.setRangeOfSampleSize(GentorProfileSgl::it()->range_ContainerSize());

    //        // If it is a container: (Create and) Pass the generator(s) for their contents
    //        // NumberGentorT<int> intGentor;
    //        ItvGentorT<int>* itvGentor = new ItvGentorT<int>;
    //        interval<int> valRange = GentorProfileSgl::it()->range_interval_int();
    //        itvGentor->setValueRange(valRange.lower_bound(), valRange.upper_bound());
    //        itvGentor->setMaxIntervalLength(GentorProfileSgl::it()->maxIntervalLength()); //JODO

    //        NumberGentorT<int>* codomainGentor = new NumberGentorT<int>;
    //        codomainGentor->setRange(GentorProfileSgl::it()->range_int());

    //        gentor.setDomainGentor(itvGentor);
    //        gentor.setCodomainGentor(codomainGentor);
    //    }
    //};

    // ---------------------------------------------------------------------------
    // ---------------------------------------------------------------------------
    template <> 
    struct Calibrater<split_interval_map<int,double>, RandomGentor>
    {
        static void apply(RandomGentor<split_interval_map<int,double> >& gentor) 
        {
            // Set the range within which the sizes of the generated object varies.
            // interval<int> range = rightOpenInterval<int>(0,10); //JODO: From SysCalibrater
            //JODO gentor.calibrate(profile);

            gentor.setRangeOfSampleSize(GentorProfileSgl::it()->range_ContainerSize());

            // If it is a container: (Create and) Pass the generator(s) for their contents
            // NumberGentorT<int> intGentor;
            ItvGentorT<int>* itvGentor = new ItvGentorT<int>;
            interval<int> valRange = GentorProfileSgl::it()->range_interval_int();
            itvGentor->setValueRange(valRange.lower_bound(), valRange.upper_bound());
            itvGentor->setMaxIntervalLength(GentorProfileSgl::it()->maxIntervalLength()); //JODO

            NumberGentorT<double>* codomainGentor = new NumberGentorT<double>;
            codomainGentor->setRange(GentorProfileSgl::it()->range_double());

            gentor.setDomainGentor(itvGentor);
            gentor.setCodomainGentor(codomainGentor);
        }
    };

    template <> 
    struct Calibrater<split_interval_map<double,int>, RandomGentor>
    {
        static void apply(RandomGentor<split_interval_map<double,int> >& gentor) 
        {
            // Set the range within which the sizes of the generated object varies.
            // interval<int> range = rightOpenInterval<int>(0,10); //JODO: From SysCalibrater
            //JODO gentor.calibrate(profile);

            gentor.setRangeOfSampleSize(GentorProfileSgl::it()->range_ContainerSize());

            // If it is a container: (Create and) Pass the generator(s) for their contents
            // NumberGentorT<int> intGentor;
            ItvGentorT<double>* itvGentor = new ItvGentorT<double>;
            interval<double> valRange = GentorProfileSgl::it()->range_interval_double();
            itvGentor->setValueRange(valRange.lower_bound(), valRange.upper_bound());
            itvGentor->setMaxIntervalLength(GentorProfileSgl::it()->maxIntervalLength()); //JODO

            NumberGentorT<int>* codomainGentor = new NumberGentorT<int>;
            codomainGentor->setRange(GentorProfileSgl::it()->range_int());

            gentor.setDomainGentor(itvGentor);
            gentor.setCodomainGentor(codomainGentor);
        }
    };
    // ---------------------------------------------------------------------------

} //namespace itl
