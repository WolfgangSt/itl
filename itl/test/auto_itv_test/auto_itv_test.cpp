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

/*----------------------------------------------------------------------------+
auto_itv_test.cpp provides automated tests:
A geneator generates instances of interval container. For each instance
properties are checked, e. g. symmetric difference on ItvSets:
(x + y) - (x * y) == (x - y) + (y - x)
As you can see, within a law like that a great deal of operations are
applied and tested.

The test procedures allow for specifying the number of tests to be performed
and the maximum size of generated interval containers. The error file collects
information on the erroneous testcases if there are any.
+----------------------------------------------------------------------------*/
#include <iostream>

#include <itl/split_interval_set.hpp>
#include <itl/split_interval_map.hpp>
#include "../itvmaptester.h"
#include "../test/itvsettester.h"

using namespace std;
using namespace itl;

// -------------------------------------------------
void autoPropertyTest_ItvSet_int()
{
    try 
    {
        int nTries=0, maxSamSize=0;
        char errFile[256];

        cout << "Property test for interval_set<int>: " << endl;
        cout << "how many ? >> ";
        cin >> nTries;
        cout << "max sample ? >> ";
        cin >> maxSamSize;
        cout << "errfile ? >> ";
        cin >> errFile ;

        typedef ItvSetTesterT< interval_set<int> > TesterT;
        TesterT::domain_generator_type* domain_gentor 
            = new TesterT::domain_generator_type();
        domain_gentor->setValueRange(0, 100);
        domain_gentor->setMaxIntervalLength(50);

        TesterT cntTester;
        cntTester.set_domain_generator(domain_gentor);
        cntTester.setRangeOfSampleSize(0, maxSamSize);

        cntTester.testInsertionIndependence(nTries);
        cntTester.testJoinIndependence(nTries);
        cntTester.testInsertReversibility(nTries, errFile);
        cntTester.testSymmetricDifference(nTries, errFile);

        cout << ">> auto tests completed\n";
    }
    catch (exception e)
    {
        cout << "autoPropertyTest_ItvSet_int(): exception caught\n";
        cout << e.what() << endl;
    }    
    catch (...)
    {
        cout << "autoPropertyTest_ItvSet_int(): unknown exception caught\n";
    }
}

// -------------------------------------------------
void autoPropertyTest_SplitItvMap_double_int()
{
    try 
    {
        int nTries=0, maxSamSize=0;
        char errFile[256];

        cout << "Property test for split_interval_map<double,int>: " << endl;
        cout << "how many ? >> ";
        cin >> nTries;
        cout << "max sample ? >> ";
        cin >> maxSamSize;
        cout << "errfile ? >> ";
        cin >> errFile ;


        typedef ItvMapTesterT< split_interval_map<double,int> > TesterT;
        TesterT::domain_generator_type* domain_gentor 
            = new TesterT::domain_generator_type();
        TesterT::codomain_generator_type* codomain_gentor 
            = new TesterT::codomain_generator_type();


        domain_gentor->setValueRange(0.0, 1.0);
        domain_gentor->setMaxIntervalLength(1.0);
        codomain_gentor->setRange(1,5);

        TesterT cntTester;
        cntTester.set_domain_generator(domain_gentor);
        cntTester.set_codomain_generator(codomain_gentor);

        cntTester.setRangeOfSampleSize(0, maxSamSize);

        cntTester.testInsertReversibility2(nTries, errFile);
        cntTester.testErasureAsIntersectionComputability(nTries, errFile);

        cout << ">> auto tests completed\n";
    }
    catch (exception e)
    {
        printf("autoPropertyTest_SplitItvMap_double_int(): exception caught\n");
        printf("%s\n", e.what());
    }    
    catch (...)
    {
        printf("autoPropertyTest_SplitItvMap_double_int(): unknown exception caught\n");
    }
}



int main()
{
    // Select a test by (re)moving the comment tokens!

    cout << ">> Interval Template Library: Test auto_itv_test.cpp <<\n";
    cout << "-------------------------------------------------------\n";
    // Test programmed properties on a sample of generated interval_set<int>
    //autoPropertyTest_ItvSet_int();
    autoPropertyTest_SplitItvMap_double_int();

    // Test programmed properties on a sample of generated split_interval_map<double,int>
    // autoPropertyTest_SplitItvMap_double_int();
    system("pause");

    return 0;
}

