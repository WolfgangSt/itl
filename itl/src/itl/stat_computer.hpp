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

#ifndef __stat_computer_JOFA_040826_H__
#define __stat_computer_JOFA_040826_H__

#include <itl/itl_vector.hpp>
//CL #include <itl/string_list.hpp>
#include <itl/tuple_computer.hpp>
#include <itl/stattd.hpp> //JODO extract typedefs that are essental. Remove StatTD or rename

#include <Cfx\ProgressIT.h> //JODO URG: remove

namespace itl
{
    typedef vector<double> dvar_vector_type;

    enum TupelComputerTypeET { amount_computer, date_computer, interval_computer };

    // Indexzuordnung, Indexmapping
    template <int IndexTC>
    class index_limits
    {
    public:
        index_limits(): m_Begin(0), m_Size(0) {}
        index_limits(int begin, int size): m_Begin(begin), m_Size(size) {}

        /// erster polymorpher Index der Variablengruppe
        int    begin()const { return m_Begin;}
        /// Groesse der Variablengruppe
        int    size()const  { return m_Size; }
        /// letzter polymorpher Index der Variablengruppe PLUS 1
        int    end()const   { return m_Begin + m_Size; }

        /// Gehoert der polymorphe Index 'podex' zu dieser Variablengruppe?
        bool contains(int podex)const { return m_Begin <= podex && podex < end(); }

        // Indexzuordnung, Indexmapping
        /** Ordne dem polymorphen Index 'podex' (laeuft ueber alle Variablensorten) 
            den urspruengliche Index 'index(podex)' zu, der fuer den speziellen
            Vector von ZaehlComputern gueltig ist.    */
        int index(int podex)const { return podex - m_Begin; }

        /** Ordne dem lokalen Index 'index' (laeuft ueber die aktuelle Variablensorte) 
            den polymorphen Index 'podex(index)' zu, der fuer den globalen
            Vector von ZaehlComputern gueltig ist.    */
        int podex(int index)const { return index + m_Begin; }

    private:
        int    m_Begin;
        int    m_Size;
    };



    class depend_var_signat
    {
    public:
        depend_var_signat():
            m_AmountVars(0), m_DateVars(0), m_ItvVars(0)
            {}
            
        depend_var_signat(int AmountVars, int DateVars, int ItvVars):
            m_AmountVars(AmountVars), m_DateVars(DateVars), m_ItvVars(ItvVars)
            {}

        int getAmountVarsCount()const { return m_AmountVars; }
        int getDateVarsCount()const      { return m_DateVars; }
        int getItvVarsCount()const    { return m_ItvVars; }

        int getAmountIdxBegin()const  { return 0; }
        int getDateIdxBegin()const      { return m_AmountVars; }
        int getItvIdxBegin()const      { return m_AmountVars + m_DateVars; }

        int getVarCount()const          { return m_AmountVars + m_DateVars + m_ItvVars; }

    private:
        int m_AmountVars;
        int m_DateVars;
        int m_ItvVars;
    };

    /** class stat_computer
    
        Zust�ndigkeit: Er h�lt f�r jede abh�ngige Variable einen passenden
        TupelComputerT.

        Zusammenarbeit: TupelComputerT
    */
    template<int IVarsV, class TimeTV = DateNumTD>
    class stat_computer
    {
    public:
        typedef TimeTV TimeTD;
        typedef var_tuple<IVarsV> var_tuple_type;
        typedef var_tuple_order<var_tuple_type> tuple_order_type;
        typedef itl::set<var_tuple_type, var_tuple_order> tuple_set_type;

    private:
        typedef var_permutation<IVarsV>                    var_permutationT;

        typedef AmountTupelComputerT<IVarsV, double>    AmountComputerTD; 
        typedef DateTupelComputerT<IVarsV, TimeTV, int>    DateComputerTD; 
        typedef ItvTupelComputerT<IVarsV, TimeTV, int>    ItvComputerTD; 
        
        typedef TupelComputerIT<IVarsV>        TupelComputerITD; 

        typedef VectorT<AmountComputerTD>        AmountComputerVecTD; 
        typedef VectorT<DateComputerTD>            DateComputerVecTD; 
        typedef VectorT<ItvComputerTD>            ItvComputerVecTD; 

        // Vector von polymorphen TupelComputer pointern zur Iteration �ber alle
        typedef itl::ptr_vector<TupelComputerITD>    TupelComputerVecTD; 

        typedef index_limits<AmountComputer>    AmountIdxLimitsTD;
        typedef index_limits<DateComputer>        DateIdxLimitsTD;
        typedef index_limits<ItvComputer>        ItvIdxLimitsTD;

    public:
        stat_computer(){}
        stat_computer(const depend_var_signat& signat, const tuple_order_type& order);

        void clear();

        AmountIdxLimitsTD getAmountIdxLimits()const { return m_Amounts;    }
        DateIdxLimitsTD getDateIdxLimits()const        { return m_Dates;    }
        ItvIdxLimitsTD getItvIdxLimits()const        { return m_Itvs;    }

        int amountComputers_count()const { return m_AmountComputers.size(); }
        int dateComputers_count()const   { return m_DateComputers.size(); }
        int itvComputers_count()const    { return m_ItvComputers.size(); }
        int computers_count()const         { return m_Computers.size(); }

        void insertAmount(int varIdx, const var_tuple_type& tupel, int amount);
        void insertDate(int varIdx, const var_tuple_type& tupel, TimeTV date);
        void insertItv(int varIdx, const var_tuple_type& tupel, const IntervalT<TimeTV>& itv);

        tuple_order_type getVarTupelOrder()const { return m_TupelOrder; }
        var_permutationT getPermutation()const { return m_TupelOrder.getPermutation(); }

        const AmountComputerTD& getAmountComputer(int varIdx)const { return m_AmountComputers[varIdx]; }
        const DateComputerTD&    getDateComputer(int varIdx)const { return m_DateComputers[varIdx]; }
        const ItvComputerTD&    getItvComputer(int varIdx)const { return m_ItvComputers[varIdx]; }

        // Vereinigungsmenge der Tupel-Mengen (domains) aller Computers
        void domainClosure(tuple_set_type& domain)const;

        void setProgress(CTX::ProgressIT* progress) { p_Progress = progress; }
        CTX::ProgressIT* getProgress()const { return p_Progress;    }

        // TESTCODE
        void printDateComputer(int var)const;
        void sumComputer(AmountTupelComputerT<IVarsV,int>& sums, int var)const;

    private:
        AmountIdxLimitsTD    m_Amounts;
        DateIdxLimitsTD        m_Dates;
        ItvIdxLimitsTD        m_Itvs;

        tuple_order_type        m_TupelOrder; 
            // W�re auch �ber jeden einzelnen TupelComputer zugreifbar via key_compare
            // So ist es einfacher

        AmountComputerVecTD m_AmountComputers;
        DateComputerVecTD    m_DateComputers;
        ItvComputerVecTD    m_ItvComputers;
        TupelComputerVecTD    m_Computers;

        CTX::ProgressIT*    p_Progress; //JODO URG make it a template parameter
    };


    template<int IVarsV, class TimeTV>
    stat_computer<IVarsV,TimeTV>::stat_computer(const depend_var_signat& signat, const tuple_order_type& order):
        m_Amounts(signat.getAmountIdxBegin(), signat.getAmountVarsCount()),
        m_Dates(signat.getDateIdxBegin(), signat.getDateVarsCount()),
        m_Itvs(signat.getItvIdxBegin(), signat.getItvVarsCount()),

        m_TupelOrder(order),
        m_AmountComputers(signat.getAmountVarsCount(), AmountComputerTD(order)),
        m_DateComputers(signat.getDateVarsCount(), DateComputerTD(order)),
        m_ItvComputers(signat.getItvVarsCount(), ItvComputerTD(order)),
        m_Computers(signat.getVarCount())

    {
        // podex = (po)lymorpher In(dex), der �ber ALLE TupelComputerITs iteriert 
        int podex = 0;
        for(podex = m_Amounts.begin(); podex < m_Amounts.end(); podex++)
            m_Computers[podex] = &m_AmountComputers[m_Amounts.index(podex)];
        for(podex = m_Dates.begin(); podex < m_Dates.end(); podex++)
            m_Computers[podex] = &m_DateComputers[m_Dates.index(podex)];
        for(podex = m_Itvs.begin(); podex < m_Itvs.end(); podex++)
            m_Computers[podex] = &m_ItvComputers[m_Itvs.index(podex)];
    }


    template<int IVarsV, class TimeTV>
    void stat_computer<IVarsV,TimeTV>::clear()
    {
        int idx=0;
        for(idx=0; idx<m_AmountComputers.size(); idx++)
            m_AmountComputers[idx].clear();
        for(idx=0; idx<m_DateComputers.size(); idx++)
            m_DateComputers[idx].clear();
        for(idx=0; idx<m_ItvComputers.size(); idx++)
            m_ItvComputers[idx].clear();
    }

    template<int IVarsV, class TimeTV>
    void stat_computer<IVarsV,TimeTV>::domainClosure(tuple_set_type& domain)const
    {
        domain.clear();
        for(int podex = m_Amounts.begin(); podex < m_Itvs.end(); podex++)
            m_Computers[podex]->addDomain(domain);
    }


    template<int IVarsV, class TimeTV>
    void stat_computer<IVarsV,TimeTV>::insertAmount(int varIdx, const var_tuple_type& tupel, int amount)
    {
        m_AmountComputers[varIdx].insert(tupel, amount);
    }

    template<int IVarsV, class TimeTV>
    void stat_computer<IVarsV,TimeTV>::insertDate(int varIdx, const var_tuple_type& tupel, TimeTV date)
    {
        DateComputerTD::CounterTD singularDateCounter;
        singularDateCounter.insert(DateComputerTD::CounterTD::value_type(date, 1));
        m_DateComputers[varIdx].insert(DateComputerTD::value_type(tupel, singularDateCounter));
    }

    template<int IVarsV, class TimeTV>
    void stat_computer<IVarsV,TimeTV>::insertItv(int varIdx, const var_tuple_type& tupel, const IntervalT<TimeTV>& itv)
    {
        ItvComputerTD::CounterTD singularItvCounter;
        singularItvCounter.insert(ItvComputerTD::CounterTD::value_type(itv, 1));
        m_ItvComputers[varIdx].insert(ItvComputerTD::value_type(tupel, singularItvCounter));
    }

    template<int IVarsV, class TimeTV>
    void stat_computer<IVarsV,TimeTV>::printDateComputer(int var)const
    {
        const DateComputerTD& cmp = m_DateComputers[var];

        const_FORALL(DateComputerTD, rec_, cmp)
        {
            var_tuple<IVarsV> tupel = (*rec_).KEY_VALUE; 
            printf("%s->%s\n", tupel.asString().c_str(), (*rec_).CONT_VALUE.asString().c_str());
        }
    }

    
    
    template<int IVarsV, class TimeTV>
    void stat_computer<IVarsV,TimeTV>::sumComputer(AmountTupelComputerT<IVarsV,int>& sums, int var)const
    {
        const DateComputerTD& cmp = m_DateComputers[var];

        const_FORALL(DateComputerTD, rec_, cmp)
        {
            var_tuple<IVarsV> tupel = (*rec_).KEY_VALUE; 
            const DateComputerTD::CounterTD&  freqs  = (*rec_).CONT_VALUE;
            //MapT<TimeTV, CounteeTV>&  freqs  = (*rec_).CONT_VALUE;

            const_FORALL(DateComputerTD::CounterTD, it_, freqs)
            {
                int freq = (*it_).CONT_VALUE;
                sums.insert(tupel, freq);
            }
            //printf("%s->%s\n", tupel.asString().c_str(), (*rec_).CONT_VALUE.asString().c_str());
        }
    }
    

}

#endif // __stat_computer_JOFA_040826_H__


