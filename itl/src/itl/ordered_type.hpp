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
#ifndef __ordered_type_h_JOFA_011005_H__
#define __ordered_type_h_JOFA_011005_H__

#include <string>

namespace itl
{

/**  
	Objekte, die nach einem (Aufz�hlungs-)Typ ordenbar sind

	Ok, ordenbar klingt sonderbar. Gemeint ist, da� es eine Ordnung von
	Objekten dieser Klasse gibt, dadurch, dass jedes Element der Klasse
	als <tt>type()</tt> den Wert eines Aufz�hlungstyps \ref TypeDomTV::DomainET
	liefern kann. Dieser Typ-Wert erlaubt es Objekte dieser Klasse (z.B. in
	Containern) zu sortieren.
  
	@author  Joachim Faulhaber
*/
template <class TypeDomTV>
class ordered_type
{
public:
	typedef ordered_type* OrderedTypePIT;

public:
	/// virtual dtor: cave leakem
	virtual ~ordered_type(){}
	/// gib deinen typ an
	virtual typename TypeDomTV::DomainET type()const=0;

	/// 
	virtual const typename TypeDomTV::ValueBaseTD* value()const=0;

	/// Kleiner Relation auf dem Typ
	virtual bool isLessOnType(const ordered_type* x2)const=0;
	/// Typ-�quivalenz <tt>this->type()==x2->type()</tt>
	virtual bool isTypeEquivalent(const ordered_type* x2)const=0;

	/// comparisons on value level
	virtual bool isEqual(const ordered_type* x2)const=0;  

	virtual bool isLess(const ordered_type* x2)const=0;  
	
	/// equality on value-level
	virtual bool operator == (const ordered_type& x2)const=0;
	
	//JODO Aufrufmechnismus f�r stl::container operator ==.verstehen
	//virtual bool operator == (const OrderedTypePIT& x2)const=0;

	//KEEP JODO einpflegen 
	// virtual bool isLess(const ordered_type* x2)const=0;  
	// virtual bool operator < (const ordered_type& x2)const=0;

	/// string representation
	virtual std::string asString()const=0 ;
};


template <class TypeDomTV>
class ordered_type_base : public ordered_type<TypeDomTV>
{
public:
	typedef ordered_type<TypeDomTV>* OrderedTypeOfDomPIT;

public:
	virtual bool isLessOnType (const ordered_type<TypeDomTV>* x2)const 
	{ return this->type() < x2->type(); }
	virtual bool isTypeEquivalent (const ordered_type<TypeDomTV>* x2)const 
	{ return this->type() == x2->type(); }

	// comparisons on value level
	bool isEqual(const ordered_type<TypeDomTV>* x2)const
	{ 
		return isTypeEquivalent(x2) && isValueEqual(x2); 
	}

	bool operator == (const ordered_type<TypeDomTV>& x2)const 
	{
		return isEqual(&x2); 
	} 

	bool isLess(const ordered_type<TypeDomTV>* x2)const
	{ 
		return this < x2; 
	}

	/*JODO Aufrufmechnismus f�r stl::container operator ==.verstehen
	bool operator == (const OrderedTypeOfDomPIT& x2)const 
	{
		return isEqual(x2); 
	} 
	*/

	/*KEEP JODO Einfplegen
	bool isLess(const ordered_type<TypeDomTV>* x2)const
	{ 
		return isLessOnType(x2) && isValueLess(x2); 
	}

	bool operator < (const ordered_type<TypeDomTV>& x2)const 
	{
		return isLess(&x2);
	}
	*/

protected:
	/// Gleichheit der Werte
	virtual bool isValueEqual(const ordered_type<TypeDomTV>* x2)const=0;

	//KEEP JODO Einfplegen
	//virtual bool isValueLess(const ordered_type<TypeDomTV>* x2)const=0;
};

} // namespace itl

#endif // __ordered_type_h_JOFA_011005_H__


