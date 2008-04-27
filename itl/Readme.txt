/*----------------------------------------------------------------------------+
Interval Template Library (ITL) Version 2.0.0
Author: Joachim Faulhaber
Copyright (c) 2007-2008: Joachim Faulhaber
Copyright (c) 1999-2006: Cortex Software GmbH, Kantstrasse 57, Berlin
+-----------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+----------------------------------------------------------------------------*/

1. Overview

The ITL is a collection of generic c++ template classes for computations
dealing with 'collections of intervals'. The most important instance of their
use is the computation with containers of time intervals that are associated to
values. We call such containers histories and their elements episodes. In
addition to intervals and interval containers the library contains classes for
generalized crosstables, which are tupel containers. We call such containers
'tupel computers' or 'cubes'.

2. Licence

The ITL is open source under the Boost Software License - Version 1.0
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)

3. Installation
3.1. Windows
ITL 2.0.0 comes as zip-file. Unzip to a directory <itl-location> of your
choice. To use the ITL add <itl-location/src> to your include path. The included
vc++ sample projects <itl-location>/itl/sample/samples/samples.sln and test
projects <itl-location>/itl/sample/test/tests/tests.sln are supposed to compile
and run with vc++ 8.x

3.2. Linux (Unixoide)
JODO URG

4. Files and Directories
<itl-location>
  readme.txt      this readme file
  licence.txt     Boost Software License - Version 1.0
  doxfile         doxygen file for the generation of html-documentation
  
  /src/itl        sourcecode of the itl
  /src/loki       small parts of the Loki library used for itl/validater
  /src/lokixt     own loki extensions used for itl/validater
  /src/validate   sourcecode for validater 'ape' for law based validation  
  
  /example        examples (in different directories)
  /test           tests (in different directories)
  /test/validate  law based test automaton (LaBaTeA)
  
  /devel          current developments
  /devel/validate law based automated test for the itl
  
  /doc/html       doxygen generated html-documentaion
  /doc/html/index.html documentaion root
  
  /build/cygwin/makefile makefile for all projects   
  /build/linux/makefile  makefile for all projects   
  /build/win32/all.sln   ms-vc8 sln-file for all projects   
  
  
5. Portability

Portability is not yet tested for compilers other than vc6.0 - vc8.x. Checking
portability for gnu gcc will be done soon.

6. Documentation:

The source code comes with a html-documentation generated with doxygen:
<itl-location>/itl/doc/html/index.html. Further information can be found there.

enjoy

Joachim Faulhaber
