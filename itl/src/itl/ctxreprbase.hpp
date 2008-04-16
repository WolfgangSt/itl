/*----------------------------------------------------------------------------+
Copyright (c) 2007-2008: Joachim Faulhaber
+-----------------------------------------------------------------------------+
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


/*-----------------------------------------------------------------------------
Function-templates for discrete Datatypes like int, unsigned or
    any class that provides a ++ operator c.f. iterators
-----------------------------------------------------------------------------*/

#ifndef __itl_REPRBASE_JOFA_000712_H__
#define __itl_REPRBASE_JOFA_000712_H__

#include <stdio.h>
#include <string>
#include <sstream>

namespace itl
{    

/**
    <b>value</b> serves as a base to for the representation
    of atomic types and classes as strings.

    The function <tt>toString</tt> is defined for all atomic (built in) types
    like <tt>int, double etc.</tt>. For types other than atomic ones namely
    classes the function template <tt>toString</tt> calls a member function
    <tt>asString</tt> on the class-type passed to the template.

    Thereby we can implement a general string representation for template classes
    which is independent of the template parameter being an atomic or a class type.
    For every object, including atomic the string converter function toString can
    be called, provides new classes implement a memberfunction <tt>asString</tt>
  
    @author  Jofa
*/
template <class TypeTV>
class value
{
public:
    /** String converter for all types <tt>TypeTV</tt>

        E.g.: <tt>int i=5; string s = value<int>::toString(i);</tt>
    */
    static const std::string toString(const TypeTV &);    
};


typedef char * CharPT;

#define RETURN_AS_STRING(format, atomicValue) \
    std::stringstream repr; \
    repr << atomicValue; \
    return repr.str();

/* Alternative macro using formated sprintf output
#define RETURN_AS_STRING(format, atomicValue) \
    char stringRepr[512]; \
    sprintf(stringRepr, format, atomicValue); \
    return stringRepr;
*/

template<> inline const std::string value<bool>::toString(const bool& x){ return x ? "true" : "false"; }
template<> inline const std::string value<char>::toString(const char& x){ RETURN_AS_STRING("%c", x); }
template<> inline const std::string value<short>::toString (const short& x) { RETURN_AS_STRING("%d", x); }
template<> inline const std::string value<int>::toString (const int& x) { RETURN_AS_STRING("%d", x);   }
template<> inline const std::string value<long>::toString(const long& x) { RETURN_AS_STRING("%ld", x);   }
template<> inline const std::string value<unsigned char>::toString (const unsigned char& x) { RETURN_AS_STRING("%uc", x);   }
template<> inline const std::string value<unsigned short>::toString (const unsigned short& x) { RETURN_AS_STRING("%hu", x);   }
template<> inline const std::string value<unsigned int>::toString (const unsigned int& x) { RETURN_AS_STRING("%u", x);   }
template<> inline const std::string value<unsigned long>::toString(const unsigned long& x) { RETURN_AS_STRING("%lu", x);   }
template<> inline const std::string value<float>::toString (const float& x) { RETURN_AS_STRING("%f", x);   }
template<> inline const std::string value<double>::toString(const double& x) { RETURN_AS_STRING("%lf", x);   }
template<> inline const std::string value<CharPT>::toString(const CharPT & x) { RETURN_AS_STRING("%s", x);   }
template<> inline const std::string value<std::string>::toString(const std::string& x) { return x; }

template <class TypeTV>
inline const std::string value<TypeTV>::toString(const TypeTV& x) { return x.asString(); }

    
    // ------------------------------------------------------------------------
    template<class Type>
    struct TypeAsString
    {
        static std::string it();
    };

    template<>
    inline std::string TypeAsString<int>::it() { return "int"; }
    template<>
    inline std::string TypeAsString<double>::it() { return "double"; }
    template<>
    inline std::string TypeAsString<std::string>::it() { return "string"; }

    // ------------------------------------------------------------------------
    template<template<class> class Templ>
    struct UnaryTemplateAsString
    {
        static std::string it();
    };

    template <template<class>class Unary, class Type>
    struct TypeAsString<Unary<Type> >
    {
        static std::string it() 
        { 
            return UnaryTemplateAsString<Unary>::it()+"<"+TypeAsString<Type>::it()+">"; 
        }
    };

    // ---------------------------------------------------------------------------
    template<template<class,class>class Templ>
    struct BinaryTemplateAsString
    {
        static std::string it();
    };

    template <template<class Type1, class Type2>class Binary, class Type1, class Type2>
    struct TypeAsString<Binary<Type1, Type2> >
    {
        static std::string it() 
        { 
            return BinaryTemplateAsString<Binary>::it()+
                "<"+TypeAsString<Type1>::it()+","+TypeAsString<Type2>::it()+">"; 
        }
    };

} // namespace itl

#endif


