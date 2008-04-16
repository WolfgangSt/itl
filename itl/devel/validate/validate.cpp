// verify.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//
#include <iostream>
#include <stdio.h>
#include <lokixt/Tuple.h>
#include <itl/itl_set.hpp>
#include <itl/itl_map.hpp>
#include <validate/lawvalidater.h>
#include <validate/laws/monoid.h>
#include <validate/laws/pushouts.h>
#include <validate/gentor/gentorprofile.h>
#include <validate/gentor/rangegentor.h>
#include <validate/realmvalidater.h>
#include <itl/interval_set.hpp>
#include <itl/numbergentor.hpp>
#include <itl/setgentor.hpp>
#include <itl/mapgentor.hpp>
#include <itl/interval_morphism.hpp>
#include <itl/functors.hpp>

using namespace std;
using namespace Loki;
using namespace itl;


void what_comes_next()
{
    // select a law
    // select a type instance
    // choose a profile (value ranges)
    // select an iteration count.
    // perform the validation.

}

void test_Validater()
{
    GentorProfileSgl::it()->set_range_int(-10, 10);
    GentorProfileSgl::it()->set_range_double(-10.0, 10.0);
    GentorProfileSgl::it()->set_range_ContainerSize(0, 20);
    GentorProfileSgl::it()->set_range_interval_int(-20, 20);
    GentorProfileSgl::it()->set_maxIntervalLength(5);


    typedef BinaryPushout<itl::split_interval_map<int,double>, itl::map<int,double>, Interval::Atomize, InplacePlus>
        Map_Atomize_Union_DiagramT;
    LawValidater<Map_Atomize_Union_DiagramT, RandomGentor> map_atomize_plus_pushout;
    map_atomize_plus_pushout.setTrialsCount(1000);
    map_atomize_plus_pushout.run();

    typedef BinaryPushout<itl::map<int,double>, itl::split_interval_map<int,double>, Interval::Cluster, InplaceStar>
        Map_Cluster_Intersect_DiagramT;
    LawValidater<Map_Cluster_Intersect_DiagramT, RandomGentor> map_cluster_star_pushout;
    map_cluster_star_pushout.setTrialsCount(1000);
    map_cluster_star_pushout.run();


    //typedef BinaryPushout<itl::interval_set<int>, itl::set<int>, Interval::Atomize, InplacePlus>
    //    Set_Atomize_Union_DiagramT;
    //LawValidater<Set_Atomize_Union_DiagramT, RandomGentor> set_atomize_plus_pushout;
    //set_atomize_plus_pushout.setTrialsCount(1000);
    //cout << "set_atomize_plus_pushout.run()" << endl;
    //set_atomize_plus_pushout.run();
    //cout << "set_atomize_plus_pushout.run() feddich" << endl;

    //typedef BinaryPushout<itl::set<int>, itl::interval_set<int>, Interval::Cluster, InplaceStar>
    //    Set_Cluster_Intersect_DiagramT;
    //LawValidater<Set_Cluster_Intersect_DiagramT, RandomGentor> set_cluster_star_pushout;
    //set_cluster_star_pushout.setTrialsCount(1000);
    //set_cluster_star_pushout.run();

    //LawValidater<AtomizePushout<itl::interval_set<int>, itl::set<int>, InplaceStar>, RandomGentor> tester_star_pushout;
    //tester_star_pushout.setTrialsCount(1000);
    //tester_star_pushout.run();

    //LawValidater<StarPushout<itl::split_interval_map<int,double>, itl::map<int,double> >, RandomGentor> tester_map_star_pushout;
    //tester_map_star_pushout.setTrialsCount(1000);
    //tester_map_star_pushout.run();

    //LawValidater<SectionAbsorbtion<itl::map<int,int> >, RandomGentor> tester_sec_absorb;
    //tester_sec_absorb.setTrialsCount(1000);
    //tester_sec_absorb.run();

    //LawValidater<AdditionCommutativity<int>, RandomGentor> tester_commut;
    //tester_commut.setTrialsCount(100);
    //tester_commut.run();

    //LawValidater<MixedAdditionCommutativity<int,double>, RandomGentor> tester_mix_commut;
    //tester_mix_commut.setTrialsCount(100);
    //tester_mix_commut.run();

    //LawValidater<InplacePlusCommutativity<itl::set<int> >, RandomGentor> tester_inplace_commut;
    //tester_inplace_commut.setTrialsCount(1000);
    //tester_inplace_commut.run();

    //LawValidater<InplacePlusCommutativity<itl::interval_set<int> >, RandomGentor> tester_inplace_commut4itvset;
    //tester_inplace_commut4itvset.setTrialsCount(10);
    //tester_inplace_commut4itvset.run();
}

// Gentor<tuple<T1,...,Tn>> = tuple< Gentor<T1>,..., Gentor<Tn> >
// template <typename ValueT> class RandomGentor;
// Wie kriege ich das hin? Ich muss aus der typelist des tupels eine
// gentorisierte typelist ausrechnen und daraus dann das gentorentupel
// kreieren

//CL Mappi
template <typename TypeT> struct Mappi
{

    std::string asString()const 
    {
        std::string result("mappi: ");
        result += value<TypeT>::toString(_value);
        return result;
    }
    TypeT _value;

    Mappi(): _value() {} 
    Mappi(const TypeT& val): _value(val) {} 
};



void test_Tuple()
{
    using namespace tup;
    // Generating type homogenious typelists
    typedef GenTypeList<int, 1>::Result int1;
    typedef GenTypeList<int, 2>::Result int2;
    typedef GenTypeList<int, 3>::Result int3;

    typedef TL::MapType<Mappi, int2>::Result mappi_int2;

    typedef tuple<int2> t_int2;
    typedef tuple<mappi_int2> tm_int2;

    t_int2 t_i2;

    refer<0>(t_i2) = 8;
    refer<1>(t_i2) = 11;

    t_int2 t_i2_twice;
    //t_i2.map<RefTwiceFun, t_int2>(t_i2_twice);
    t_i2.map<RefTwiceFun>(t_i2_twice);

    cout << t_i2.asString() << endl;
    cout << t_i2_twice.asString() << endl;

    tm_int2 tm_i2;
    refer<0>(tm_i2) = Mappi<int>(8);
    refer<1>(tm_i2) = Mappi<int>(11);

    cout << tm_i2.asString() << endl;
}

void test_Law()
{
    using namespace tup;
    typedef tuple<LOKI_TYPELIST_1(int) > single_int;
    typedef tuple<LOKI_TYPELIST_2(int, int) > int_int;
    single_int inval;  refer<0>(inval) = 42;
    single_int outval; refer<0>(outval) = -1;

    AdditionNeutrality<std::string> addNeut;
    addNeut.setValue("hallo");
    bool law_holds = addNeut.holds();
    printf("Law Neut(+) %s result=%s\n", law_holds ? "holds":"is violated", addNeut.getResult().c_str());

    AdditionCommutativity<int> addCommut;
    addCommut.setInstance(tup::le(2,3));
    law_holds = addCommut.holds();
    printf("Law Commut(+) %s result=(%d,%d)\n", 
        law_holds ? "holds":"is violated", addCommut.getLhsSum(), addCommut.getRhsSum());

}

void test_rangegentor()
{
    RangeGentor<int> itvG;
    itvG.setLowerBoundRange(closed_interval(1,5));
    itvG.setUpperBoundRange(closed_interval(7,7));

    for(int idx=0; idx < 20; idx++)
    {
        interval<int> itv;
        itvG.some(itv);
        printf("%s%s\n", itv.asString().c_str(), itv.empty()?" mt":"");
    }
}

void test_weightedNumberGentor()
{
    //WeightedNumberGentor<int> choice(3,100);
    WeightedNumberGentor<int> choice; //(3,100);
    choice.setSize(3);
    choice.setMaxWeights(100);
    choice[0] = 20;
    choice[1] = 60;
    choice.init();

    int chosen = -1;
    int weighted = -1;
    bool lawIsViolated = false;

    for(int idx=1; idx < 1000; idx++)
    {
        chosen = choice.some();
        weighted = choice.chosenValue();

        if(!choice.isRangeValid())
        {
            lawIsViolated = true;
            cout << "Range violation" << endl;
        }
    }
    if(!lawIsViolated)
        cout << "All ranges valid" << endl;

}

void test_typevalidater()
{
    InplaceSetBaseValidater<itl::map<int,int> > validater;
    validater.validate();
};

void test_stringify()
{
    cout << TypeAsString<int>::it() << endl;
    cout << TypeAsString<itl::set<int> >::it() << endl;
}

void test_realmvalidater()
{
    RealmValidater validater;
    //CL validater.setProfile();
    validater.validate();
};

void test_misc()
{
    itl::set<int> eset;
    itl::interval_set<int> iset;
    eset.insert(3);
    eset.insert(4);
    eset.insert(5);
    eset.insert(7);
    eset.insert(9);
    eset.insert(10);

    Interval::cluster(iset, eset);

    cout << eset.asString() << endl;
    cout << iset.asString() << endl;
}

int main()
{
    //test_Tuple();
    //test_Law();
    //test_Validater();
    //test_ewnet();
    //test_weightedNumberGentor();
    //test_stringify();
    //test_typevalidater();
    test_realmvalidater();
    //test_misc();

    return 0;
}
