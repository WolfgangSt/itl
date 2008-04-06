////////////////////////////////////////////////////////////////////////////////
// The Loki Library
// Copyright (c) 2001 by Andrei Alexandrescu
////////////////////////////////////////////////////////////////////////////////
#ifndef LOKI_TypelistGentor_INC_
#define LOKI_TypelistGentor_INC_

// $Id: HierarchyGenerators.h 751 2006-10-17 19:50:37Z syntheticpp $


#include <loki/Typelist.h>
#include <loki/TypeTraits.h>
#include <loki/EmptyType.h>


namespace Loki
{
#if defined(_MSC_VER) && _MSC_VER >= 1300
#pragma warning( push ) 
 // 'class1' : base-class 'class2' is already a base-class of 'class3'
#pragma warning( disable : 4584 )
#endif // _MSC_VER

	//JODO This should be integrated into Typelist.h
	namespace TL
	{
		template <class TList1, class TList2> struct StrictEquality;

		template<>
		struct StrictEquality<NullType, NullType>
		{
			enum { Result = true };
		};

		template<typename Head1>
		struct StrictEquality<Typelist<Head1, NullType>, NullType>
		{
			enum { Result = false };
		};

		template<typename Head2>
		struct StrictEquality<NullType, Typelist<Head2, NullType> >
		{
			enum { Result = false };
		};

		template<typename Head, class Tail1, class Tail2>
		struct StrictEquality<Typelist<Head, Tail1>, Typelist<Head, Tail2> >
		{
			enum { Result = StrictEquality<Tail1, Tail2>::Result };
		};

		template<typename Head1, class Tail1, typename Head2, class Tail2>
		struct StrictEquality<Typelist<Head1, Tail1>, Typelist<Head2, Tail2> >
		{
			// Does only match if Head1 is unequal to Head2
			enum { Result = false };
		};

		// --------------------------------------------------------------------
		// JODO Extension for Typelist:
		// class template MapType
		// MapType(F, Typelist<T1,...,Tn>) = Typelist<F<T1>,...,F<Tn> >
		// --------------------------------------------------------------------
		template<template<typename TypeT>class UnaryTemplate, typename Typelist>
		struct MapType;

		template<template<typename TypeT>class UnaryTemplate>
		struct MapType<UnaryTemplate, NullType>
		{
			typedef NullType Result;
		};

		template<template<typename TypeT>class UnaryTemplate, class Head, class Tail>
		struct MapType<UnaryTemplate, Typelist<Head, Tail> >
		{
			typedef Typelist<UnaryTemplate<Head>, typename MapType<UnaryTemplate, Tail>::Result> Result;
		};

	}

	/* class template GenTypeList. It serves to generate homogenious
	   Typelists of a given size.	*/
	template <class T, unsigned int size> struct GenTypeList;

	template <class T>
	struct GenTypeList<T, 0>
	{
		typedef NullType Result;
	};

	template <class T, unsigned int size>
	struct GenTypeList
	{
		typedef Typelist<T, typename GenTypeList<T, size-1>::Result > Result;
	};


#if defined(_MSC_VER) && _MSC_VER >= 1300
#pragma warning( pop ) 
#endif
}   // namespace Loki

#endif // end file guardian

