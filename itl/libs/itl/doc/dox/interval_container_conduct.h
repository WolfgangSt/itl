/*----------------------------------------------------------------------------+
Author: Joachim Faulhaber
Copyright (c) 2008-2008: Joachim Faulhaber
+-----------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+----------------------------------------------------------------------------*/

/** \file interval_container_conduct.h

    \section sec1_itv_cnt_conduct Different behaviors or conducts of interval containers.

    <table>
        <tr>
            <th></td>
            <th>joining</td>
            <th>separating</td>    
            <th>splitting</td>       
        </tr>
        <tr>
            <th>set</th>
            <td colspan=3 align="center">baseclass itl::interval_base_set</td>
        </tr>
        <tr align="center" valign="top">
            <td></td>
            <td>itl::interval_set</td>
            <td>itl::separate_interval_set</td>    
            <td>itl::split_interval_set</td>       
        </tr>

        <tr>
            <td></td>
            <td>
                <table border=0>
                    <tr><td> </td><td>[1</td><td>  </td><td>  </td><td>3)</td><td>  </td><td>  </td><td>  </td></tr>
                    <tr><td>+</td><td>  </td><td>  </td><td>[2</td><td>  </td><td>  </td><td>4)</td><td>  </td></tr>
                    <tr><td>+</td><td>  </td><td>  </td><td>  </td><td>  </td><td>  </td><td>  </td><td>[4</td><td>5)</td></tr>
                    <tr><td>=</td><td>[1</td><td>  </td><td>  </td><td>  </td><td>  </td><td>  </td><td>  </td><td>5)</td></tr>
                </table>
            </td>

            <td>
                <table border=0>
                    <tr><td> </td><td>[1</td><td>  </td><td>  </td><td>3)</td><td>  </td><td>  </td><td>  </td></tr>
                    <tr><td>+</td><td>  </td><td>  </td><td>[2</td><td>  </td><td>  </td><td>4)</td><td>  </td></tr>
                    <tr><td>+</td><td>  </td><td>  </td><td>  </td><td>  </td><td>  </td><td>  </td><td>[4</td><td>5)</td></tr>
                    <tr><td>=</td><td>[1</td><td>  </td><td>  </td><td>  </td><td>  </td><td>4)</td><td>[4</td><td>5)</td></tr>
                </table>
            </td>

            <td>
                <table border=0>
                    <tr><td> </td><td>[1</td><td>  </td><td>  </td><td>3)</td><td>  </td><td>  </td><td>  </td></tr>
                    <tr><td>+</td><td>  </td><td>  </td><td>[2</td><td>  </td><td>  </td><td>4)</td><td>  </td></tr>
                    <tr><td>+</td><td>  </td><td>  </td><td>  </td><td>  </td><td>  </td><td>  </td><td>[4</td><td>5)</td></tr>
                    <tr><td>=</td><td>[1</td><td>2)</td><td>[2</td><td>3)</td><td>[3</td><td>4)</td><td>[4</td><td>5)</td></tr>
                </table>
            </td>
        </tr>

        <tr>
            <th>map</th>
            <td colspan=3 align="center">baseclass itl::interval_base_map</td>
        </tr>
        <tr align="center" valign="top">
            <td></td>
            <td>itl::interval_map</td>
            <td></td>                   
            <td>itl::split_interval_map</td>
        </tr>

        <tr>
            <td></td>
            <td>
                <table border=0>
                    <!--|1        |2         |3         |4         |5         |6         |7         |8         |9         |10                              -->
                    <tr><td> </td><td>[1</td><td>  </td><td>  </td><td>3)</td><td colspan=3>\htmlonly &rarr;1\endhtmlonly</td></tr>
                    <tr><td>+</td><td>  </td><td>  </td><td>[2</td><td>  </td><td>  </td><td>4)</td><td colspan=2>\htmlonly &rarr;1\endhtmlonly</td></tr>
                    <tr><td>+</td><td>  </td><td>  </td><td>  </td><td>  </td><td>  </td><td>  </td><td>[4</td><td>5)</td><td>\htmlonly &rarr;1\endhtmlonly<td></tr>
                    <tr><td>=</td><td>[1</td><td>2)</td><td>[2</td><td>3)</td><td>[3</td><td>  </td><td>  </td><td>5)</td></tr>
                    <tr align="center">
                        <td> </td><td colspan=2>\htmlonly &rarr;1\endhtmlonly</td> 
                                                         <td colspan=2>\htmlonly &rarr;2\endhtmlonly</td>
                                                                               <td></td><td></td>   <td colaspan=2 align="center">\htmlonly &rarr;1\endhtmlonly</td>     
                                                                                                                          <td></td></tr>
                </table>
            </td>

            <td>
            </td>

            <td>
                <table border=0>
                    <!--|1        |2         |3         |4         |5         |6         |7         |8         |9         |10                              -->
                    <tr><td> </td><td>[1</td><td>  </td><td>  </td><td>3)</td><td colspan=3>\htmlonly &rarr;1\endhtmlonly</td></tr>
                    <tr><td>+</td><td>  </td><td>  </td><td>[2</td><td>  </td><td>  </td><td>4)</td><td colspan=2>\htmlonly &rarr;1\endhtmlonly</td></tr>
                    <tr><td>+</td><td>  </td><td>  </td><td>  </td><td>  </td><td>  </td><td>  </td><td>[4</td><td>5)</td><td>\htmlonly &rarr;1\endhtmlonly<td></tr>
                    <tr><td>=</td><td>[1</td><td>2)</td><td>[2</td><td>3)</td><td>[3</td><td>4)</td><td>[4</td><td>5)</td></tr>
                    <tr align="center">
                        <td> </td><td colspan=2>\htmlonly &rarr;1\endhtmlonly</td> 
                                                         <td colspan=2>\htmlonly &rarr;2\endhtmlonly</td>
                                                                               <td colspan=2>\htmlonly &rarr;1\endhtmlonly</td>
                                                                                                    <td colaspan=2 align="center">\htmlonly &rarr;1\endhtmlonly</td><td></td></tr>
                </table>
            </td>
        </tr>


        <tr>
            <td></td>
            <td><em>intervals are joined on overlap or touch<br>
                    (if associated values are equal)</em></td>
            <td><em>intervals are joined on overlap, not on touch</em></td>                   
            <td><em>intervals are split on overlap.<br>All interval borders are thus preserved</em></td>
        </tr>
    </table>

    \subsection sec2_joining_itv_cnt The joining interval containers

    itl::interval_set and itl::interval_map are always in a <b><em>minimal representation</em></b>.
    This is useful in many instances, where the points of insertion or intersecton of
    intervals is not relevant. So in most instances itl::interval_set and 
    itl::interval_map will be the first choice for an interval container.

    \subsection sec2_splitting_itv_cnt The splitting interval containers

    itl::split_interval_set and itl::split_interval_map    on the contrary have an
    <b><em>insertion memory</em></b>. They do accumulate interval borders both 
    from additions and intersections. This is specifically useful, if we want
    to enrich an interval container with certain time grids, like e.g. months
    or calendar weeks or both. See example month_and_week_grid.cpp.

    \subsection sec2_separating_itv_cnt The separating interval containers

    itl::separate_interval_set is hybrid between joining and splitting interval
    sets. It does neither split intervals on overlap nor does it join intervals
    that only touch neighbouring intervals in the container. This behavior may
    sometimes be desired.
*/

