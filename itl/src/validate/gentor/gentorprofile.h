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

#include <itl/itl_interval.hpp>

namespace itl
{

    /*JODO
    template <typename Type>
    class IntervalGentor
    {
    public:
        interval<Type> some()const
        {
        }
    private:
        interval<Type>    _min_range;
        interval<Type>    _max_range;
        RandomGentor<Type> _domainGentor; 
    };
    */

    class GentorProfile
    {
    public:
        GentorProfile();

        void set_range_int(int lwb, int upb) { _range_int = rightopen_interval(lwb, upb); }
        void set_range_double(double lwb, double upb) { _range_double = rightopen_interval(lwb, upb); }
        void set_range_ContainerSize(int lwb, int upb) { _range_int = rightopen_interval(lwb, upb); }
        void set_range_interval_int(int lwb, int upb) { _range_interval_int = rightopen_interval(lwb, upb); }
        void set_range_interval_double(double lwb, double upb) { _range_interval_double = rightopen_interval(lwb, upb); }
        void set_maxIntervalLength(int val) { _maxIntervalLength = val; }

        interval<int>        range_int()                { return _range_int; }
        interval<double>    range_double()            { return _range_double; }
        interval<int>        range_ContainerSize()    { return _range_int; }
        interval<int>        range_interval_int()    { return _range_interval_int; }
        interval<double>    range_interval_double()    { return _range_interval_double; }
        int                    maxIntervalLength()        { return _maxIntervalLength; }

    private:
        interval<int>        _range_int;
        interval<double>    _range_double;
        interval<int>        _range_ContainerSize;

        interval<int>        _range_interval_int;
        interval<double>    _range_interval_double;
        int                    _maxIntervalLength;
    };

    class GentorProfileSgl // SINGLETON PATTERN
    {
    // Singleton pattern part -----------------------------------------------------
    public:
        static GentorProfileSgl* it(); // function to call the unique instance

    protected:
        GentorProfileSgl();            // default constructor is not callable from outside
                        // preventing illegal instances

    // specific interface ---------------------------------------------------------
    public:
        void set_range_int(int lwb, int upb)            { m_profile.set_range_int(lwb, upb); }
        void set_range_double(double lwb, double upb)    { m_profile.set_range_double(lwb, upb); }
        void set_range_ContainerSize(int lwb, int upb)    { m_profile.set_range_ContainerSize(lwb, upb); }
        void set_range_interval_int(int lwb, int upb)    { m_profile.set_range_interval_int(lwb, upb); }
        void set_range_interval_double(double lwb, double upb){ m_profile.set_range_interval_double(lwb, upb); }
        void set_maxIntervalLength(int val)                { m_profile.set_maxIntervalLength(val); }

        interval<int>        range_int()                { return m_profile.range_int();            }
        interval<double>    range_double()            { return m_profile.range_double();        }
        interval<int>        range_ContainerSize()    { return m_profile.range_ContainerSize();    }
        interval<int>        range_interval_int()    { return m_profile.range_interval_int(); }
        interval<double>    range_interval_double()    { return m_profile.range_interval_double(); }
        int                    maxIntervalLength()        { return m_profile.maxIntervalLength(); }


    private:
        // Singleton pattern part -------------------------------------------------
        static GentorProfileSgl*    s_instance; // pointer to the unique instance

        // specific members -------------------------------------------------------

        // TODO add specifc members as needed
        GentorProfile m_profile;
    };

} // namespace itl
