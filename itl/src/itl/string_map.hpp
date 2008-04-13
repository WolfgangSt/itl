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
#ifndef __itl_string_map_JOFA_021215_H__
#define __itl_string_map_JOFA_021215_H__

#include <itl/notate.hpp>
#include <itl/itl_map.hpp>
#include <string>

namespace itl
{    
    template <class CodomTV, class CompTV=less<std::string> >
        class string_map : public MapT<std::string, CodomTV, CompTV>
    {
    };
    
    /// Compair class for Strings ingnoring case
    struct  string_ICLess {
        bool operator() (const std::string& c1, const std::string& c2) const 
        { 
            //return c1.stricmp(c2)<0; //JODO URG
            return c1 < c2; //JODO URG
        }
    };
    
    /// A template map class that's keys are handled case insensitive
    template <class CodomTV>
        class ICstring_map : public itl::string_map<CodomTV, string_ICLess>
    {
    };

} // namespace itl

#endif // __itl_string_map_JOFA_021215_H__



