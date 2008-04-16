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
/* ------------------------------------------------------------------
Dieses File dient ausschlie�lich der Dokumentation von Template-Parametern
durch doc++. (Dokumentations-Typ)
Es soll und mu� niemals in Projekte includiert werden! 
--------------------------------------------------------------------*/

#pragma message(__LOC__"Don't include this file (it served to document template patameter only)!")

namespace itl
{

/**  
    <b>large definiert das implizite Interface aller
    Type-Domain-Parameter von Episoden- und Historien-Template-Klassen</b>
    
    TypeDomTV kapselt einen Aufz�hlungstyp. Ein solcher wird z.B. f�r
    Episoden benutzt, um den Typ von Episoden als Werte im Programm repr�sentieren
    zu k�nnen.

    Daher ist die wichtigste Komponente von TypeDomTV die Definition
    dieses Aufz�hlungstyps TypeDomTV::DomainET. Daneben gibt es noch
    eine Funktion as_string zur Repr�sentation von Typen als strings.

    @author  Joachim Faulhaber
*/


class TypeDomTV
{
public:
    /// Aufz�hlungstyp
    typedef enum {} DomainET;

    /// String-Repr�sentation
    static string as_string(DomainET val);
} ;

} // namespace itl