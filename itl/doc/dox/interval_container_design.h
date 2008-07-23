/*----------------------------------------------------------------------------+
Copyright (c) 2008-2008: Joachim Faulhaber
+-----------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+----------------------------------------------------------------------------*/

/*
	\subsection sec2_itv_cnt_holo A hologrammatic nature of interval conainers

	An interval set(map) implements a set(map) as a set(map) of intervals (with associated values).
	So the 
*/

/** \file interval_container_design.h

	\section sec1_itv_cnt_dsgn Design considerations for the ITL's interval container

	The documentation of the ITL's design is work in progress and not considered
	to be complete. In the process of refactoring and augmenting the ITL for becoming
	boost compliant (boostification;) this documentaion may change and it will also
	grow and become more complete.


	\subsection sec2_itv_cnt_dsgn_map_add_sub Relations between std::map, itl::map and itl::interval_map

	Interval sets and maps are designed to be addable and subtractable objects.
	They implement operators += (add) and -= (subtract). Moreover interval_maps
	propagate addition (+=) and subtraction (-=) to	the associated values so that
	for overlapping intervals the associated values are added or subtracted
	respectively (aggregate on overlap).

	With respect to addability and subtractability, the member functions
	interval_base_map::add and interval_base_map::subtract are of pivotal
	importance for the design of the itl. They are also provided as operators:
	interval_base_map::operator+= and interval_base_map::operator-= . 
	
	In order to generalize addition and subraction even further there are 
	parameterized member function templates add<operator> and
	subtract<operator>, that allow aggregate on overlap to be performed
	with arbitrary functors. So	m.add(x) is equivalent to m.add<itl::inplace_plus>(x)
	but you can compute also say a maximum of associated values on 'addition'
	using m.add<itl::inplace_max>(x).

	On the other hand, interval_maps and sets are intended to implement stl 
	maps as closely as possible. To provide the interface of std::container
	there are also functions insert and erase. Interestingly there is a
	relationship between insert and add as well as subtract and erase.
	There are functors itl::inplace_identity and itl::inplace_erasure such that
	the following are equivalent functions:

	<table>
		<tr><th colspan=3 align="center">equivalent functions on itl maps</th></tr>
		<tr><td>add<inplace_identity>(value_type&)</td>   <td>insert(value_type&)</td> <td></td></tr>
		<tr><td>subtract<inplace_erase>(value_type&)</td> <td>erase(value_type&)</td>  <td></td></tr>
		<tr><td>add<inplace_plus>(value_type&)</td>       <td>add(value_type&)</td>    <td>operator+=(value_type&)</td></tr>
		<tr><td>subtract<inplace_minus>(value_type&)</td> <td>subtract(value_type&)    <td>operator-=(value_type&)</td></td></tr>
	</table>

	So the common insert and erase functions can be expressed as 
	specialisations of the more general member function templates 
	add and subtract.

	The following table gives an overview over addition, subtraction
	insertion and erasure functions of itl maps and interval maps and
	their relation to stl maps.

	<table>
		<!--    |1                                    |2         ||3                  |4               |5                    ||6                  |7                    |8                           ||9                     |10                 |11                   |12                         -->
		<tr><th>                             </th><th>   </th><th colspan=3>std::map                       </th><th colspan=3>itl::map                                             </th><th colspan=4>itl::interval_map                                                                          </th></tr>
		<tr><th>view                         </th><th>+|-</th><th>return type</th><th>function</th><th>argument types</th><th>return type</th><th>function     </th><th>argument types       </th><th>view          </th><th>return type</th><th>function     </th><th>argument types            </th></tr>
		<tr bgcolor="#F7BE81"><td>aggregating</td><td>+  </td><td colspan=3 bgcolor="white">               </td><td>iterator   </td><td>add&lt;op&gt;</td><td>const value_type&amp;</td><td>interval based</td><td>void                 </td><td>add&lt;op&gt;</td><td>const value_type&amp;     </td></tr>
		<tr bgcolor="#F3F781"><td>adding     </td><td>+  </td><td colspan=3 bgcolor="white">               </td><td>iterator   </td><td>add          </td><td>const value_type&amp;</td><td>interval based</td><td>void                 </td><td>add          </td><td>const value_type&amp;     </td></tr>
		<tr bgcolor="#F3F781"><td>adding     </td><td>+  </td><td colspan=6 bgcolor="white">                                                                                       </td><td>element based </td><td>void                 </td><td>add          </td><td>const base_value_type&amp;</td></tr>
		<tr bgcolor="#D0F5A9"><td>iterator based</td><td>+</td><td>iterator</td><td>insert</td><td>iterator, const value_type&amp;</td><td>iterator</td><td>insert</td><td>iterator, const value_type&amp;</td><td colspan=4 bgcolor="white">                                                    </td></tr>
		<tr bgcolor="#A9F5F2"><td>interval based</td><td>+</td><td colspan=6 bgcolor="white">                                                                                       </td><td>interval based</td><td>void                </td><td>insert       </td><td>const value_type&amp;     </td></tr>
		<tr bgcolor="#CEE3F6"><td>element based</td><td>+</td><td>(iterator, bool)</td><td>insert</td><td>const value_type&amp;</td><td>(iterator,bool)</td><td>insert</td><td>const value_type&amp;</td><td>element based </td><td>void</td><td>insert       </td><td>const base_value_type&amp;</td></tr>
		<tr bgcolor="#CEE3F6"><td>element based</td><td>-</td></td><td colspan=3 bgcolor="white">               </td><td>size_type</td><td>erase</td><td>const value_type&amp;</td>          <td>element based</td><td>void      </td><td>erase        </td><td>const base_value_type&amp;</td></tr>
		<tr bgcolor="#CEE3F6"><td>key based    </td><td>-</td><td>size_type</td><td>erase</td><td>const key_type&amp;  </td><td>size_type</td><td>erase</td><td>const key_type&amp;</td>          <td>element based</td><td>void        </td><td>erase        </td><td>const base_value_type&amp;</td></tr>
		<tr bgcolor="#A9F5F2"><td>key based    </td><td>-</td><td colspan=6 bgcolor="white">                                                                                       </td><td>interval based</td><td>void                 </td><td>erase        </td><td>const interval_type&amp;  </td></tr>
		<tr bgcolor="#A9F5F2"><td>interval based</td><td>-</td><td colspan=6 bgcolor="white">                                                                                       </td><td>interval based</td><td>void                </td><td>erase        </td><td>const value_type&amp;     </td></tr>
		<tr bgcolor="#D0F5A9"><td>iterator based</td><td>-</td><td>void      </td><td>erase</td><td>iterator          </td><td>void</td>     <td>erase</td><td>iterator</td>             <td colspan=4 bgcolor="white">                                                    </td></tr>
		<tr bgcolor="#F3F781"><td>subtracting</td>   <td>-</td><td colspan=6 bgcolor="white">                                                                                       </td><td>element based </td><td>void</td>           <td>subtract</td>          <td>const base_value_type&amp;</td></tr>
		<tr bgcolor="#F3F781"><td>subtracting</td>   <td>-</td><td colspan=3 bgcolor="white">               </td><td>iterator   </td><td>subtract     </td><td>const value_type&amp;</td><td>interval based</td><td>void                 </td><td>subtract     </td><td>const value_type&amp;     </td></tr>
		<tr bgcolor="#F7BE81"><td>aggregating</td>   <td>-</td><td colspan=3 bgcolor="white">               </td><td>iterator   </td><td>subtract&lt;op&gt;</td><td>const value_type&amp;</td><td>interval based</td><td>void                 </td><td>subtract&lt;op&gt;</td><td>const value_type&amp;     </td></tr>
	</table>

*/

