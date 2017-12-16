/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                           */
/*  This file is part of the apcpp library for incremental solution of       */
/*  assignments problems. The code is a C++ port of the original Fortran     */
/*  from the following paper:                                                */
/*                                                                           */
/*      Giorgio Carpaneto, Silvano Martello, and Paolo Toth.                 */
/*      "Algorithms and codes for the assignment problem."                   */
/*      Annals of Operations Research 13, no. 1 (1988): 191-223.             */
/*                                                                           */
/*  apcpp is distributed under the terms of the MIT License. You should      */
/*  have received a copy with the source If not, email roneil1@gmu.edu.      */
/*                                                                           */
/*      Copyright (C) 2017 Ryan J. O'Neil <roneil1@gmu.edu>                  */
/*                                                                           */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

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
