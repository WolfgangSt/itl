/*----------------------------------------------------------------------------+
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
class NumberGentorT
    A random generator for numbers
--------------------------------------------------------------------*/
#ifndef __NUMBERGENTORT_H_JOFA_000725__
#define __NUMBERGENTORT_H_JOFA_000725__


#include <stdlib.h>
#include <vector>
#include <itl/algbase.hpp>
#include <itl/gentorit.hpp>

#define RND_1_TO(y)      (1+(int)((double)(y)*rand()/(RAND_MAX+1.0)))
#define RND_0_TO(y)      ((int)((double)((y)+1)*rand()/(RAND_MAX+1.0)))
#define RND_WITHIN(x,y) ((x)+(int)((double)((y)-(x)+1)*rand()/(RAND_MAX+1.0)))

// -----------------------------------------------------------

#define RND_O_TO_EXCL(y) (((double)(y))*rand()/(RAND_MAX+1.0))

#define RND_WITHIN_EXUPB(x,y) ((x)+((double)((y)-(x))*rand()/(RAND_MAX+1.0)))

namespace itl
{

template <class NumTV>
inline NumTV rnd_0_to_excl(NumTV exclusive_upb) 
{ return (NumTV)RND_O_TO_EXCL(exclusive_upb); }


template <class NumTV>
inline NumTV rnd_within_exUpb(NumTV lwb, NumTV exclusive_upb) 
{ 
    NumTV some = (NumTV)RND_WITHIN_EXUPB(lwb,exclusive_upb); 
    return some;
}

template <class NumTV>
inline NumTV rnd_within(NumTV lwb, NumTV exclusive_upb) 
{ 
    NumTV some = (NumTV)RND_WITHIN(lwb,exclusive_upb); 
    return some;
}

template <class NumT>
class NumberGentorProfile : public RandomGentorProfile<NumT>
{
public:
private:
    interval<NumT> _range;
};

template <class NumTV>
class NumberGentorT : public RandomGentorAT<NumTV>
{
public:
    NumberGentorT(): 
      m_valueRange( NumTV(), AlgBaseT<NumTV>::unon(), interval<NumTV>::RIGHT_OPEN ) {}

    NumTV operator() (NumTV upb) { return rnd_0_to_excl<NumTV>(upb); }
    NumTV operator() (NumTV lwb, NumTV upb)  { return rnd_within_exUpb<NumTV>(lwb,upb); }
    NumTV operator() (interval<NumTV> rng) 
    { 
        J_ASSERT(rng.is_rightopen() || rng.is_closed());
        if(rng.is_rightopen())
            return rnd_within_exUpb<NumTV>(rng.lower_bound(), rng.upper_bound());
        else
            return rnd_within<NumTV>(rng.lower_bound(), rng.upper_bound());
    }

    void setRange(interval<NumTV> rng) { m_valueRange = rng; }
    void setRange(NumTV lwb, NumTV upb) { m_valueRange = rightopen_interval(lwb,upb); } 

    void calibrate(const RandomGentorProfile<NumTV>& profile)
    {
        m_valueRange = profile.getValueRange();
    }

    void some(NumTV& x) { x = (*this)(m_valueRange); }

    std::string as_string()const { return "NumberGentorT";}

private:
    interval<NumTV> m_valueRange;
};

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
template <typename WeightsT>
class WeightedNumberGentor : public RandomGentorAT<int>
{
public:
    WeightedNumberGentor(): _size(0), _maxWeights(0){}

    WeightedNumberGentor(int size, WeightsT maxWeights):
        _size(size), _maxWeights(maxWeights),
        _weights(size, WeightsT()), _kumWeights(size+1, WeightsT()) {}

    WeightedNumberGentor(int size):
        _size(size), _maxWeights(1000),
        _weights(size, WeightsT()), _kumWeights(size+1, WeightsT()) {}

    void setSize(int size);
    int size()const { return _size; }

    void setMaxWeights(int maxWeights) { _maxWeights = maxWeights; }
    WeightsT maxWeights()const { return _maxWeights; }
    WeightsT chosenValue()const { return _chosenValue; }

    WeightsT& operator[](int idx) 
    { J_ASSERT(0<=idx && idx<_size); return _weights[idx]; }

    void setWeight(int idx, WeightsT val) { J_ASSERT(0<=idx && idx<_size); _weights[idx] = val; }

    WeightsT getKumWeight(int idx)const { return _kumWeights[idx]; }

    void init();

    int some();
    void some(int& index){ index = some(); }

    int lower_bound_index(int low, int up, WeightsT val);

    bool isRangeValid()const 
    { return _kumWeights[_chosenIndex] <= _chosenValue && _chosenValue < _kumWeights[_chosenIndex+1]; }

private:
    int                        _size;
    WeightsT                _maxWeights;
    std::vector<WeightsT>   _weights;
    std::vector<WeightsT>   _kumWeights;
    NumberGentorT<int>        _numgentor;
    WeightsT                _chosenValue;
    int                        _chosenIndex;
};


template <typename WeightsT>
void WeightedNumberGentor<WeightsT>::setSize(int size)
{
    _size = size;
    _weights.resize(_size, WeightsT());
    _kumWeights.resize(_size+1, WeightsT());
}


template <typename WeightsT>
void WeightedNumberGentor<WeightsT>::init()
{
    _kumWeights[0] = WeightsT();
    for(int idx=1; idx < _size; idx++)
        _kumWeights[idx] = static_cast<WeightsT>(std::min(_kumWeights[idx-1]+_weights[idx-1], _maxWeights));

    _kumWeights[_size] = _maxWeights;
}

template <typename WeightsT>
int WeightedNumberGentor<WeightsT>::some()
{
    _chosenValue = _numgentor(_maxWeights);
    _chosenIndex = lower_bound_index(0, _size, _chosenValue);
    return _chosenIndex;
}

template <typename WeightsT>
int WeightedNumberGentor<WeightsT>::lower_bound_index(int low, int up, WeightsT val)
{
    int mid = (low+up)/2;
    if(_kumWeights[mid] <= val && val < _kumWeights[mid+1])
        return mid;
    else if(val < _kumWeights[mid])
        return lower_bound_index(low, mid, val);
    else
        return lower_bound_index(mid+1, up, val);
}

} // namespace itl

#endif // __NUMBERGENTORT_H_JOFA_000725__




