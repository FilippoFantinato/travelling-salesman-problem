Travelling Salesman Problem
===========================

The Travelling Salesman Problem is one of the most NP-hard famous problem. It asks you the following question:

    Given a list of cities and the distances between each pair of cities, what is the shortest possible route that visits each city exactly once and returns to the origin city?

In this repository you can find some exact methods and heuristics for solving TSP.

Done
++++

.. list-table::
    :widths: 25 25 25 25
    :header-rows: 1

    * - Name
      - Type
      - Solution
      - Resources
    * - 
      - 
      -
      -


TODO
++++

.. list-table::
    :widths: 25 25 25 25
    :header-rows: 1

    * - Name
      - Type
      - Solution
      - Resources
    * - Gavish - Graves
      - Mixed Integer Linear Programming
      - Exact
      - [1]_
    * - Closest Insertion
      - Heuristic
      - 2-approx *
      -
    * - Cheapest Insertion
      - Heuristic
      - 2-approx *
      -
    * - Nearest Neighbor
      - Heuristic
      - log(n)-approx *
      -
    * - Random Insertion
      - Heuristic
      - log(n)-approx *
      -
    * - Circuit-vertex distance
      - Heuristic
      - log(n)-approx *
      -
    * - Farthest Insertion
      - Heuristic
      - log(n)-approx *
      -


\* if the triangle inequality is respected

References
++++++++++

.. [1] `Gavish, Bezalel & Graves, Stephen. (2004). The Traveling Salesman Problem and Related Problems. <https://www.researchgate.net/publication/37596296_The_Traveling_Salesman_Problem_and_Related_Problems>`_
