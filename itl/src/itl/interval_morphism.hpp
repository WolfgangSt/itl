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
#ifndef __itl_interval_morphism_H_JOFA_080315__
#define __itl_interval_morphism_H_JOFA_080315__

#include <itl/notate.hpp>

namespace itl
{
    namespace Interval
    {
        template <typename ElementContainerT, typename IntervalContainerT>
        void atomize(ElementContainerT& result, const IntervalContainerT& src)
        {
            const_FORALL(typename IntervalContainerT, itv_, src)
            {
                const typename IntervalContainerT::key_type& itv   = IntervalContainerT::key_value(itv_);
                typename IntervalContainerT::codomain_type   coval = IntervalContainerT::codomain_value(itv_);

                for(typename IntervalContainerT::domain_type element = itv.first(); element <= itv.last(); element++)
                {
                    result.insert(ElementContainerT::make_element(element, coval));
                }
            }
        }

        template <typename IntervalContainerT, typename ElementContainerT>
        void cluster(IntervalContainerT& result, const ElementContainerT& src)
        {
            const_FORALL(typename ElementContainerT, element_, src)
            {
                const typename ElementContainerT::key_type&  key  = ElementContainerT::key_value(element_);
                const typename ElementContainerT::data_type& data = ElementContainerT::data_value(element_);

                result.insert(IntervalContainerT::make_domain_element(key, data));
            }
        }

        template <typename AtomizedType, typename ClusteredType>
        struct Atomize
        {
            void operator()(AtomizedType& atomized, const ClusteredType& clustered)
            {
                Interval::atomize(atomized, clustered);
            }
        };

        template <typename ClusteredType, typename AtomizedType>
        struct Cluster
        {
            void operator()(ClusteredType& clustered, const AtomizedType& atomized)
            {
                Interval::cluster(clustered, atomized);
            }
        };

    } // namespace Interval


    template<> 
    inline std::string BinaryTemplateAsString<Interval::Atomize>::it() { return "@"; }
    template<> 
    inline std::string BinaryTemplateAsString<Interval::Cluster>::it() { return "&"; }

} // namespace itl

#endif



