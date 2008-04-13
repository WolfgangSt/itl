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
Combinators
    a general classes for Combinators
--------------------------------------------------------------------*/
#ifndef __itl_CMBTOR_H_JOFA_990302__
#define __itl_CMBTOR_H_JOFA_990302__

//CL #include <itl/ctxlistt.hpp>

namespace itl
{

template <class ALPHA>
class UniCombinatorT
{
public:
    virtual ALPHA operator() (const ALPHA& a1, const ALPHA& a2)=0;
} ;

template <class ALPHA>
class UnifierT : public UniCombinatorT<ALPHA>
{
public:
    ALPHA operator() (const ALPHA& x1, const ALPHA& x2)
    { ALPHA y(x1); y += x2; return y; }
    // { ALPHA y; ::Union(y,x1,x2); return y; }
} ;

template <class ALPHA>
class SubtractorT : public UniCombinatorT<ALPHA>
{
public:
    ALPHA operator() (const ALPHA& x1, const ALPHA& x2)
    { ALPHA y(x1); y -= x2; return y; }
} ;

template <class ALPHA>
class IntersectorT : public UniCombinatorT<ALPHA>
{
public:
    ALPHA operator() (const ALPHA& x1, const ALPHA& x2)
    { ALPHA y(x1); y *= x2; return y; }
} ;

template <class ALPHA>
class AppenderT : public UniCombinatorT<ALPHA>
{
public:
    ALPHA operator() (const ALPHA& x1, const ALPHA& x2)
    { ALPHA y(x1); y.append(x2); return y; }
    // { ALPHA y; ::Union(y,x1,x2); return y; }
} ;



// ----------------------------------------------------------------------------------
// Trying a more efficient but nevertheless general implementation

template <class ALPHA>
class AccumulatorT  // InplaceCombinatorT
{
public:
    virtual ALPHA& operator()(ALPHA& y, const ALPHA& x)const=0; 
    // combine may be destructuve on x, like stl's list<T>::slice, so no const
} ;



template <class ALPHA>
class AppenderAT : public AccumulatorT<ALPHA>
{
public:
    ALPHA& operator()(ALPHA& y, const ALPHA& x)const
    { y.append(x); return y; }
} ;



// ------------------------------------------------------------------------------------
// This is the hard and potentially most efficient version, using accumulators that are
// destructive on the second argument like std::list<T>::splice

template <class ALPHA>
class DestrAccumulatorAT  // InplaceCombinatorT
{
public:
    virtual ALPHA& operator()(ALPHA& y, ALPHA& x)const=0; 
    // combine may be destructuve on x, like stl's list<T>::slice, so no const
} ;


template <class ALPHA>
class DestrAppenderIT : public AccumulatorT<ALPHA>
{
public:
    ALPHA& operator()(ALPHA& y, ALPHA& x)const
    { y.destrAppend(x); return y; }
} ;

} // namespace itl


#endif

