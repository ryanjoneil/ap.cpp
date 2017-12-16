# AP.CPP: Incremental Primal-Dual Assignment Problem Solver

This code provides a C++ implementation of an incremental primal-dual assignment problem solver. It is a port of the original Fortran for the dense AP discussed in the following paper.

```
Giorgio Carpaneto, Silvano Martello, and Paolo Toth.
"Algorithms and codes for the assignment problem."
Annals of Operations Research 13, no. 1 (1988): 191-223.
```

This code can efficiently optimize any model in the form of an Assignment Problem.

```
min   sum {i,j} c_ij * x_ij
s.t.  sum {i} x_ij = 1       for all j
      sum {j} x_ij = 1       for all i
      x_ij in {0,1}          for all i, j
```

## What is this for?

While there are a number of codes available for solving APs directly, and indeed a Linear Optimization solver can also make quick work of them, most implementations are not intended for _incremental_ solution. Incremental solving of assignment problems is important when an AP forms a relaxation of some other model, such as a Traveling Salesman Problem, and variable filtering is achieved through reduced cost-based domain filtering.

In such scenarios, an initial relaxation of a more complex model into an AP is solved in `O(n^3)` time, arcs are typically removed from the AP solution in the search tree, and successive solutions that do not include those arcs are computed in `O(n^2)` time. The efficiency gained by incremental solution makes the AP relaxation effective in furthering domain propagation. See the following paper for more details.

```
Filippo Focacci, Andrea Lodi, and Michela Milano.
"A hybrid exact algorithm for the TSPTW."
INFORMS Journal on Computing 14, no. 4 (2002): 403-417.
```

## How do I use it?

An `APSolver` instance provides the following methods.

* `void solve()`: optimizes the current AP
* `void set_obj({row, col}, obj)`: sets a cell objective value
* `void remove_arc({row, col}}`: removes an arc from the current solution
* `void remove_arc({row, col}, obj)`: removes an arc from the current solution, sets its objective value
* `int get_z()`: returns the current objective value
* `bool get_x({row, col})`: returns true if the cell is in the current solution, false otherwise
* `int get_rc({row, col})`: returns the current reduced cost for a cell
* `int get_u(row)`: returns the dual price for a row
* `int get_v(col)`: returns the dual price for a column
* `void print(ostream)`: prints the current solution data to an output stream

### Basic Example

The following example shows how to optimize a simple 5x5 AP. First initialize the solver with the correct size (5 in this case). Use `set_obj` to set the objective value of each cell. Then simply call `solve`. This algorithm runs in `O(n^3)` time.

```cpp
#include <iostream>
#include <vector>

#include <apcpp/primal_dual_ap_solver.h>

using namespace std;

int main(int argc, char** argv) {
    vector<vector<int>> obj = {
        {25, 40,  9, 15},
        {12, 33, 22, 31},
        {18, 37, 18, 30},
        {32, 11, 12, 26}
    };

    APCPP::PrimalDualAPSolver solver(obj.size());

    for (unsigned int row = 0; row < obj.size(); ++row)
        for (unsigned int col = 0; col < obj[row].size(); ++col)
            solver.set_obj({row, col}, obj[row][col]);

    solver.solve();
    solver.print(cout);
}
```

The call to `print` produces the following output.

```
========================================================================
z	   56

u	    0    3    9    0
v	    9   11    9   15

rc	   16   29    0    0
	    0   19   10   13
	    0   17    0    6
	   23    0    3   11

x	    -    -    -    1
	    1    -    -    -
	    -    -    1    -
	    -    1    -    -
------------------------------------------------------------------------
```

### Incremental Example

A more complex use case removes arcs from the AP's feasible set. In this case we don't want those arcs being added back in subsequent solutions, so we set their objective values to something large (`M`) to discourage that. The first call to `solve` runs in `O(n^3)` time, while subsequent calls after an arc removal run in `O(n^2)`.

```cpp
#include <iostream>
#include <vector>

#include <apcpp/primal_dual_ap_solver.h>

using namespace std;

int main(int argc, char** argv) {
    int M = 1000;

    vector<vector<int>> obj = {
        {25, 40,  9, 15},
        {12, 33, 22, 31},
        {18, 37, 18, 30},
        {32, 11, 12, 26}
    };

    APCPP::PrimalDualAPSolver solver(obj.size());

    for (unsigned int row = 0; row < obj.size(); ++row)
        for (unsigned int col = 0; col < obj[row].size(); ++col)
            solver.set_obj({row, col}, obj[row][col]);

    solver.solve();
    solver.print(cout);
    solver.remove_arc({2, 2}, M);
    solver.remove_arc({1, 0}, M);
    solver.remove_arc({0, 3}, M);
    solver.remove_arc({3, 1}, M);
    solver.remove_arc({2, 0}, M);
    solver.remove_arc({3, 3}, M);
    solver.solve();
    solver.print(cout);
}
```

This produces the following output.

```
========================================================================
z	   56

u	    0    3    9    0
v	    9   11    9   15

rc	   16   29    0    0
	    0   19   10   13
	    0   17    0    6
	   23    0    3   11

x	    -    -    -    1
	    1    -    -    -
	    -    -    1    -
	    -    1    -    -
------------------------------------------------------------------------
========================================================================
z	  100

u	   16   22   21   19
v	    9   11   -7    9

rc	    0   13    0  975
	  969    0    7    0
	  970    5  986    0
	    4  970    0  972

x	    1    -    -    -
	    -    1    -    -
	    -    -    -    1
	    -    -    1    -
------------------------------------------------------------------------
```