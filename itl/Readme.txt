/*----------------------------------------------------------------------------+
Interval Template Library (ITL) Version 2.0.1
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

Version 2.0.1 is the first version in a process of adapting the ITL to
boost coding and design standards.
+ The design of interval containers has been reviewed. class templates
  interval_map and sepatate_interval_set have been added.
+ All virtual functions of interval container class templates have been
  removed using the couriously recurring template pattern CRTP.
+ Documentation on the design of interval containers have been added.
+ Examples using boost/date_time have been added


4. Installation

4.1. Windows

ITL 2.0.1 comes as zip-file. Unzip to a directory <itl-location> of your
choice. To use the ITL add <itl-location/src> to your include path. The included
vc++ sample projects <itl-location>/example/examples.sln and test
projects <itl-location>/test/tests.sln are supposed to compile
and run with vc++ 8.x. Another solution-file for all example and test projects
can be found in <itl-location>/build/win32/all.sln.

To run the new boost date_time examples you need boost::date_time and
some related libs and dlls. If you compile with msvc 8.0, the files,
that are shipped with this release should compile, link and run. 
A partial boost library and the related lib- and dll-files are provided.

For all other compilers you need a version of the boost libraries installed
on your machine. See http://boost.org or http://sourceforge.net/projects/boost


4.2. Cygwin

If you run a cygwin unix emulation you can use the makefile
<itl-location>/build/cygwin/makefile
to compile example and test projects with gcc.


4.3. Linux (Unixoide)

ITL 2.0.1 comes as a tar ball itl_2_0_1.tgz. Extract using
tar -xzf itl_2_0_1.tgz
at the installation directory of your choice.

A makefile is provided in
<itl-location>/build/linux/makefile

You might have to customize the makefile for 64bit machines
LOAD_LIBS  = -L/usr/lib64 
Also you might want to change the BIN_PATH to a path of your choice e.g.
BIN_PATH = $(HOME)/bin

If you'd like to run boost related examples you have to get a release
of the boost libraries from http://sourceforge.net/projects/boost.

Adjust the makefile for your BOOST_PATH, if it is different from 
BOOST_PATH = /usr/include/boost_1_33_5

There are targets
make examples
make tests
make all
make <specific-project>
to compile example and test projects.

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

  /boost_1_35_0_mini 
                  A mininal boost fragment to run ITL-examples using
                  boost date_time
  
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
                         libs to use for boost::data_time with msvc 8.0
  /lib/boost_date_time-vc80-mt-gd-1_35.lib
  /lib/libboost_date_time-vc80-mt-1_35.lib
  /lib/libboost_date_time-vc80-mt-gd-1_35.lib
  
6. Portability

The code has been compiled and tested with three compilers
(gcc 3.4.4, conceptgcc-boostcon, msvc 8.0 sp1) and with three 
implementations of the stl (linux/gnu, stlport, msvc8) under 
suse linux 10.1. and ms-windows xp.

7. Documentation:

The source code comes with a html-documentation generated by doxygen:
<itl-location>/doc/html/index.html. Further information can be found there.

enjoy

Joachim Faulhaber
