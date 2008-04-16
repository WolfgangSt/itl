/*----------------------------------------------------------------------------+
Copyright (c) 2007-2008: Joachim Faulhaber
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
class itl::set
a general set class that extends stl-sets
for concepts InplaceAddable and InplaceSubtractable
--------------------------------------------------------------------*/
#ifndef __itl_itv_type_as_string_h_JOFA_070519__
#define __itl_itv_type_as_string_h_JOFA_070519__

#include <string>
#include <itl/interval_set.hpp>
#include <itl/split_interval_set.hpp>
//CL #include <itl/joint_interval_map.hpp>
#include <itl/split_interval_map.hpp>
#include <itl/itl_value.hpp>

namespace itl
{
    //JODO 1_0_1 documentation
    /// an stl based set implementing inplace addition and subtraction operators += and -=
    /** 

    @author Joachim Faulhaber
    */
    template <class Type>
    class TypeAsString<itl::interval_set<Type> >
    {
    public:
        static std::string it() 
        { return "interval_set<"+ TypeAsString<Type>::it() +">"; }
    };

    template <class Type>
    class TypeAsString<itl::split_interval_set<Type> >
    {
    public:
        static std::string it() 
        { return "splt_itv_set<"+ TypeAsString<Type>::it() +">"; }
    };

    //CL
    //template <class KeyT, class DataT>
    //class TypeAsString<itl::joint_interval_map<KeyT,DataT> >
    //{
    //public:
    //    static std::string it() 
    //    { return "joint_interval_map<"+ TypeAsString<KeyT>::it() + "," + TypeAsString<DataT>::it() +">"; }
    //};

    template <class KeyT, class DataT>
    class TypeAsString<itl::split_interval_map<KeyT,DataT> >
    {
    public:
        static std::string it() 
        { return "splt_itv_map<"+ TypeAsString<KeyT>::it() + "," + TypeAsString<DataT>::it() +">"; }
    };

} // namespace itl

#endif // __itl_itv_type_as_string_h_JOFA_070519__


