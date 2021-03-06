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
#ifndef __itl_episode_set_hpp_JOFA_011015_H__
#define __itl_episode_set_hpp_JOFA_011015_H__

#include <string>
#include <boost/itl/set.hpp>
#include <boost/itl_xt/typed_episode.hpp>

namespace boost{namespace itl
{
    template <typename EpisodePointer>
    class Less_TypedEpisodeATP
    {
    public:
        bool operator ()(const EpisodePointer& rhs, const EpisodePointer& lhs)const
        {
            return rhs->isLess(lhs);
        }
    };

/// A set of episodes
/**    
    <b>Eine Menge von Episoden</b>

    Template-Parameter <b>TimeT</b>: Domain-Typ der Episoden-Intervalle
    (z.B. Tage, Sekunden, Monate, int u.�.). Episoden haben ja ein Intervall, das
    Anfang und Ende der Episode angibt.

    Template-Parameter <b>TypeDomain</b>: TypeDomain ist der Definitionsbereich (Domain)
    der Typen von Episoden, die in der Menge verwendet werden k�nnen.

    Die Episonden-Menge darf nur Episoden enthalten, die vom gleichen
    Episoden-Typ sind. Dieser Episodentyp wird durch einen Wert aus dem
    Template-Parameter TypeDomain repr�sentiert.

    JODO: Diese Eigenschaft sollte man durch eine geeignete Implementierung
    der Klasse sicherstellen. Enf�llt bislang wg. Zeitmangels

    @author  Joachim Faulhaber
*/
template <class TimeT, class TypeDomain>
class episode_set : public itl::set<typed_episode<TimeT, TypeDomain>*, Less_TypedEpisodeATP > 
{
    // all elements must have the same type from TypeDomain
public:
    typedef itl::set<typed_episode<TimeT, TypeDomain>*, Less_TypedEpisodeATP > base_type;
    typedef typename base_type::iterator iterator;
    typedef typename base_type::const_iterator const_iterator;
    
public:
    bool isMonoTyped()const;

    std::string as_string(const char* sep = " ")const
    {
        const_iterator it = this->begin();
        
        if(it == this->end()) return std::string("");
        else
        {
            std::string y = (**it).as_string(); it++;
            while(it != this->end()) 
            { 
                y += sep; 
                y += (**it).as_string(); 
                it++; 
            }
            return y;
        }
    }
};


//JODO Aufrufmechnismus f�r stl::container operator ==.verstehen. Eigener
// == operator sollte �berfl�ssig sein. Korrektes Type-Konzept f�r Pointertypen etc.
template <class TimeT, class TypeDomain>
inline bool operator == (const episode_set<TimeT,TypeDomain>& lhs,
                         const episode_set<TimeT,TypeDomain>& rhs)
{
    if(lhs.size() != rhs.size())
        return false;

    typename episode_set<TimeT,TypeDomain>::const_iterator 
        lhs_ = lhs.begin(), 
        rhs_ = rhs.begin();

    while(lhs_ != lhs.end())
    {
        if(!(**lhs_ == **rhs_))
            return false;
        lhs_++; rhs_++;
    }

    return true;
}

}} // namespace itl boost

#endif // __itl_episode_set_hpp_JOFA_011015_H__


