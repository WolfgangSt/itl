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
generalized crosstables, which are tuple containers. We call such containers
'tuple computers' or 'cubes'.

2. Licence

The ITL is open source under the Boost Software License - Version 1.0
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)

3. Changes

A series of major changes have been performed since the initial library version
ITL.1.0.0. The changes exclusively apply to design, naming conventions and 
validation tools. The functionality of the library is unchanged.

The ITL.2.0.0 class templates have been generalized to match the abstraction
level and the stl/boost standards. Template parameters like e.g. Allocator
have been added.

Class template parameters like, Interval, Compare or Allocator have been designed
as template template parameter which made it possible to export derived types
of class template in more flexible an generic fashion.

Names for class templates and their member functions have been refactored to
conform the stl/boost standards.

Interval sets and interval maps have been validated for a series of semantic
laws using LaBatea: A law based tests automaton.


4. Installation
4.1. Windows
ITL 2.0.0 comes as zip-file. Unzip to a directory <itl-location> of your
choice. To use the ITL add <itl-location/src> to your include path. The included
vc++ sample projects <itl-location>/example/examples.sln and test
projects <itl-location>/test/tests.sln are supposed to compile
and run with vc++ 8.x. Another solution-file for all example and test projects
can be found in <itl-location>/build/win32/all.sln.

4.2. Cygwin
If you run a cygwin unix emulation you can use the makefile
<itl-location>/build/cygwin/makefile
to compile example and test projects with gcc.

4.3. Linux (Unixoide)
ITL 2.0.0 comes as a tar ball itl_2_0_0.tgz. Extract using
tar -xcf itl_2_0_0.tgz
at the installation directory of your choice.
A makefile is provided in
<itl-location>/build/linux/makefile
There are targets
make examples
make tests
make all
make <specific-project>
to compile example or test projects.

To use the ITL in your own projects add <itl-location>/src/ to your include-path


5. Files and Directories
<itl-location>
  readme.txt      this readme file
  licence.txt     Boost Software License - Version 1.0
  doxfile         doxygen file for the generation of html-documentation
  
  /src/itl        sourcecode of the itl
  /src/loki       small parts of the Loki library used for itl/validate
  /src/lokixt     loki extensions used for itl/validate
  /src/validate   sourcecode for validater LaBatea (law based test automaton)  
  
  /example        examples (in different directories)
  /test           tests (in different directories)
  /test/labatea   law based test automaton (LaBatea)
    
  /doc/html       doxygen generated html-documentaion
  /doc/html/index.html documentaion root
  
  /build/cygwin/makefile makefile for all projects   
  /build/linux/makefile  makefile for all projects   
  /build/win32/all.sln   ms-vc8 sln-file for all projects   
  /build/script/  auxiliary bash scritps for makefile
  
  /lib/stlport.5.0.lib   only used, if linked against stlport.5.0.lib
  
  
6. Portability

The code has been compiled and tested with three compilers
(gcc 3.4.4, conceptgcc-boostcon, msvc 8.0 sp1) and with three 
implementations of the stl (linux/gnu, stlport, msvc8) under 
suse linux 10.1. and ms-windows xp.

7. Documentation:

The source code comes with a html-documentation generated with doxygen:
<itl-location>/doc/html/index.html. Further information can be found there.

enjoy

Joachim Faulhaber
