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
#ifndef __RANDOM_H_JOFA_990223__
#define __RANDOM_H_JOFA_990223__


#include <functional>
#include <stdlib.h>
#include <boost/itl/j_assert.hpp>
#include <boost/itl/interval.hpp>

namespace boost{namespace itl
{

class random
{
public:
    //JODO subtractive_rng random generator is only an sgi extension of std-lib
    //unsigned rnd(unsigned upb) { return m_random(upb); };
    
    unsigned rnd(unsigned upb) 
    {
        return static_cast<int>(upb * (::rand() / static_cast<double>(RAND_MAX)));
        //JODO return m_random(upb); 
    };


    unsigned rnd(unsigned lwb, unsigned upb)
    { // JODO cpp
        J_ASSERT(0<=lwb && lwb <= upb);
        unsigned len = upb - lwb ;
        unsigned some = rnd(len);
        return some + lwb;
    }

    unsigned rnd(const itl::interval<unsigned>& rng)
    { J_ASSERT( rng.is_rightopen() ); return rnd(rng.lower(),rng.upper()); }

private:
    //JODO subtractive_rng m_random;
};

}} // namespace itl boost

#endif

