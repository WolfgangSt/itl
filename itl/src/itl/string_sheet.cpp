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
#include <stdafx.h>
#include "string_sheet.h"
#include <itl/ctxreprbase.hpp>

using namespace itl;


string diff_desc::afxReport(const string& file)const
{
    string msg = "Difference in:\n";
    msg    += file + "\n";
    msg    += "d_size=" + ReprBaseT<int>::toString(m_SizeDiff);
    msg    += "  col=" + ReprBaseT<int>::toString(m_RowSizeDiff) + "\n";
    msg    += "First Difference 1:ref 2:cur:\n";
    msg    += "First Difference 1:ref 2:cur:\n";
    msg    += m_Lhs + "\n";
    msg    += m_Rhs + "\n";

    return msg;    
}


void string_sheet::fprint(FILE* file, const char* sep)const
{
    const_FORALL_THIS(row_)
    {
        const string_list& row = (*row_);
        fprintf(file, "%s\n", row.join(sep).c_str());
    }
}

void string_sheet::fscan(ifstream& infile, const char* sep)
{
    char rawLine[MAX_INPUT_ROW_SIZE]; //JODO flex

    while(!infile.eof())
    {
        infile.getline(rawLine, MAX_INPUT_ROW_SIZE);
        string_list row;
        row.split(rawLine, sep);
        push_back(row);
    }
    pop_back(); // Schliessende Leerzeile wegnehmen
}


diff_desc string_sheet::diff(const string_sheet& rhs)const
{
    int thisSize = size();
    int rhsSize = rhs.size();

    diff_desc diff;
    diff.setSizeDiff(thisSize - rhsSize);

    int rowSize = std::min(thisSize, rhsSize);

    string_sheet::const_iterator thisRow_ = begin();
    string_sheet::const_iterator rhsRow_  = rhs.begin();

    for(int rowIdx = 1; rowIdx <= rowSize; rowIdx++)
    {
        const string_list& thisRow = (*thisRow_);
        const string_list& rhsRow  = (*rhsRow_);

        int lhsRowSize = thisRow.size();
        int rhsRowSize = rhsRow.size();
        if(lhsRowSize != rhsRowSize)
        {
            diff.setRow(rowIdx);
            diff.setCol(std::min(lhsRowSize, rhsRowSize)+1);
            diff.setRowSizeDiff(lhsRowSize - rhsRowSize);
            return diff;
        }

        string_list::const_iterator lhsCol_ = thisRow.begin();
        string_list::const_iterator rhsCol_ = rhsRow.begin();

        for(int colIdx=1; colIdx <= lhsRowSize; colIdx++)
        {
            if((*lhsCol_) != (*rhsCol_))
            {
                diff.setRow(rowIdx);
                diff.setCol(colIdx);
                diff.setLhs(*lhsCol_);
                diff.setRhs(*rhsCol_);
                return diff;
            }
            lhsCol_++;
            rhsCol_++;
        }

        thisRow_++;
        rhsRow_++;
    }

    return diff;
}
