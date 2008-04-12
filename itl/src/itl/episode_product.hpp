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
#ifndef __episode_product_h_JOFA_011005_H__
#define __episode_product_h_JOFA_011005_H__

#include <itl/itl_map.hpp>
#include <itl/episode_set.hpp>

namespace itl
{

/**    
	<b>Eine Klasse zur Sammlung von Episoden unterschiedlichen Typs</b>

    episode_product ist so benannt nach dem mathematischen Ding
	(T1 e1, ... Tn en), was gelegentlich Produkt oder Tupel (in der Informatik
	auch struct (c), record (pascal)) genannt wird. Beim EpisodenProdukt
	sind Ti Typen und ei Episoden-Mengen. Die Elemente der Episodenmengen sind 
	vom Typ Ti. Implementiert wird das Ganze als Map

	{ T1->e1, ... , Tn->en }. Es m�ssen also nicht alle Komponenten vorhanden sein.

	Template-Parameter <b>ItvDomTV</b>: Domain-Typ der Episoden-Intervalle
	(z.B. Tage, Sekunden, Monate, int u.�.). Episoden haben ja ein Intervall, das
	Anfang und Ende der Episode angibt.
  
    Template-Parameter <b>TypeDomTV</b>: TypeDomTV ist der Definitionsbereich (Domain)
	der Typen von Episoden, die in der Produkt-Historie verwendet werden k�nnen.
	
	Ein Episoden-Produkt ist ein Map (partielle Abbildung). Der Definitionbereich
	des Map ist ein Aufz�hlungstyp TypeDomTV::DomainET. Das Map ist hierdurch auf ganz
	spezifische Werte und eine maximale Anzahl beschr�nkt.

	Der Wertebereich (CoDomain) sind Mengen von Episoden. Diese Episoden sind
	'getypte' \ref TypedEpisodeT, die ihren Typ kennen. Eine Episode aus einer 
	Episodenmenge ei
	hat immer den gleichen Typ aus TypeDomTV::DomainET wie ihr Schl�ssels Ti 
	eines Wertepaares (Ti, ei).

	Im Kontext von Produkthistorien repr�sentieren die Episoden-Mengen die
	Episoden eines Typs, die sich �berlappen. Eine einelementige Menge ist
	eine nicht�berlappende Episode eines Typs.


	Im Kontext von Produkthistorien kann man das EpisodenProdukt auch als
	<b>Episoden-Aufsammelobjekt f�r zeitliche �berlappung</b> betrachten:

	Eine Episodenmenge mit mehreren Elementen repr�sentiert zeiliche �berlappung
	von Episoden gleichen Typs: Beispiel:

	{ KUE -> { kueEpi_Bfa, kueEpi_Aok } }

	Episoden unterschiedlichen Typs repr�sentieren �berlappung von Episoden
	unterschidlichen Typs: Beispiel:

	{ AUFENTH -> {aufentEpi}, KUE -> {kueEpi} }
	

	@author  Joachim Faulhaber
*/

template <class ItvDomTV, class TypeDomTV>
class episode_product : public itl::map<typename TypeDomTV::DomainET, episode_set<ItvDomTV,TypeDomTV> >
{
public:
	typedef itl::map<typename TypeDomTV::DomainET, episode_set<ItvDomTV,TypeDomTV> > base_type;
	typedef	typename base_type::value_type value_type;
	typedef	typename base_type::data_type data_type;
	typedef	typename base_type::data_type EpisodeSetTD;
	typedef	typename episode_set<ItvDomTV,TypeDomTV>::value_type EpisodePTD;
	typedef typename base_type::iterator iterator;
	typedef typename base_type::const_iterator const_iterator;
	
public:

	/// Zu einem Episoden-Typ wird ein Pointer auf die erste Episode einer Episoden-Menge 
	///	zur�ckgegeben. Wenn die Menge leer ist liefert die Funktion NULL.
	EpisodePTD getFirst(typename TypeDomTV::DomainET type)const
	{
		const_iterator epiSet_ = find(type);
		if(epiSet_ == this->end()) 
			return NULL;
		else return *((*epiSet_).CONT_VALUE.begin());
	}

	EpisodePTD getLast(typename TypeDomTV::DomainET type)const
	{
		const_iterator epiSet_ = find(type);
		if(epiSet_ == this->end())
			return NULL;
		else return *((*epiSet_).CONT_VALUE.rbegin());
	}

	EpisodeSetTD* getEpisodeSetPtr(typename TypeDomTV::DomainET type)
	{
		iterator epiSet_ = find(type);
		if(epiSet_ == this->end()) 
			return NULL;
		else return &((*epiSet_).CONT_VALUE);
	}
	
	int size(typename TypeDomTV::DomainET type)const
	{
		const_iterator epiSet_ = find(type);
		if(epiSet_ == this->end()) 
			return 0;
		else return (*epiSet_).CONT_VALUE.size();
	}
		
	bool insert(EpisodePTD pEpisode)
	{
		EpisodeSetTD sglSet;
		sglSet.insert(pEpisode);
		typename TypeDomTV::DomainET type = pEpisode->type();
		return base_type::insert(value_type(type,sglSet)).WAS_SUCCESSFUL;
	}

	void leftAlignedEpisodes(episode_product& syncProd, const ItvDomTV& start)
	{
		const_FORALL_THIS(elem_)
		{
			TypeDomTV type = (*elem_).KEY_VALUE;
			EpisodeSetTD& epiSet = (*elem_).KEY_VALUE;
			
			EpisodeSetTD syncSet;
			const_FORALL(typename EpisodeSetTD, epi_, epiSet)
			{
				if((*epi_)->interval().first()==start)
					syncSet.insert(*epi_);
			}
			syncProd.insert(episode_product::value_type(type, syncSet));
		}
	}
	

	std::string asString()const
	{
		std::string str;
		const_iterator it = this->begin();

		if(it == this->end()) 
			return std::string("");
		else
		{
			std::string str( TypeDomTV::asString((*it).KEY_VALUE) );
			str += ("{"+((*it).CONT_VALUE).asString()+"}");
			it++;
			
			while(it != this->end()) {
				str += ", "; str += TypeDomTV::asString((*it).KEY_VALUE);
				str += ("{"+((*it).CONT_VALUE).asString()+"}");
				it++;
			}
			return str;
		}
	}

};


/* KEEP Eigentlich bessere Implementierung exemplarisch f�r 'using' in Verbindung
	private inheritence. M�sste aber wg. R�ckw�rtskompatibilit�t sorgf�ltig
	eingepflegt werden (eigentlich nur StatPflege)
NOTE MEMO DESIGN USING PRIVATE INHERITENCE

template <class ItvDomTV, class TypeDomTV>
class episode_product : private itl::MapT<TypeDomTV::DomainET, episode_set<ItvDomTV,TypeDomTV> >
{
public:
	typedef itl::MapT<TypeDomTV::DomainET, episode_set<ItvDomTV,TypeDomTV> > BaseTD;
	typedef BaseTD::value_type value_type;
	typedef BaseTD::data_type data_type;
	typedef BaseTD::data_type EpisodeSetTD;
	typedef episode_set<ItvDomTV,TypeDomTV>::value_type EpisodePTD;

	typedef BaseTD::iterator iterator;
	typedef BaseTD::const_iterator const_iterator;

public:

	using BaseTD::find;
	using BaseTD::begin;
	using BaseTD::end;

	using BaseTD::contains;

	episode_product& operator += (const episode_product& rhs) {	BaseTD::operator += (rhs); return *this; }
	episode_product& operator -= (const episode_product& rhs) {	BaseTD::operator -= (rhs); return *this; }

	/// Zu einem Episoden-Typ wird ein Pointer auf die erste Episode einer Episoden-Menge 
	///	zur�ckgegeben. Wenn die Menge leer ist liefert die Funktion NULL.
	EpisodePTD getFirst(TypeDomTV::DomainET type)const
	{
		const_iterator epiSet_ = find(type);
		if(epiSet_==end()) return NULL;
		else return *((*epiSet_).CONT_VALUE.begin());
	}

	int size()const { return BaseTD::size(); }
	
	int size(TypeDomTV::DomainET type)const
	{
		const_iterator epiSet_ = find(type);
		if(epiSet_==end()) return 0;
		else return (*epiSet_).CONT_VALUE.size();
	}
	
	
	
	bool insert(EpisodePTD pEpisode)
	{
		EpisodeSetTD sglSet;
		sglSet.insert(pEpisode);
		TypeDomTV::DomainET type = pEpisode->type();
		return BaseTD::insert(value_type(type,sglSet)).WAS_SUCCESSFUL;
	}

	std::string asString()const
	{
		std::string str;
		const_iterator it = begin();

		if(it==end()) return std::string("");
		else
		{
			std::string str( TypeDomTV::asString((*it).KEY_VALUE) );
			str += ("{"+((*it).CONT_VALUE).asString()+"}");
			it++;
			
			while(it != end()) {
				str += ", "; str += TypeDomTV::asString((*it).KEY_VALUE);
				str += ("{"+((*it).CONT_VALUE).asString()+"}");
				it++;
			}
			return str;
		}
	}

};


template <class ItvDomTV, class TypeDomTV>
inline bool operator == (const episode_product<ItvDomTV,TypeDomTV>& lhs,
						 const episode_product<ItvDomTV,TypeDomTV>& rhs)
{
	if(lhs.size() != rhs.size())
		return false;

	episode_product<ItvDomTV,TypeDomTV>::const_iterator lhs_ = lhs.begin(), rhs_ = rhs.begin();

	while(lhs_ != lhs.end())
	{
		if(!((*lhs_).KEY_VALUE == (*rhs_).KEY_VALUE))
			return false;
		else if (!((*lhs_).CONT_VALUE == (*rhs_).CONT_VALUE))
			return false;

		lhs_++; rhs_++;
	}

	return true;
}
*/

} // namespace itl

#endif // __episode_product_h_JOFA_011005_H__


