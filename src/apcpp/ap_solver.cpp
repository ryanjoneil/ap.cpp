/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                           */
/*  This file is part of the apcpp library for iterative solution of         */
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

#include <iomanip>

#include <apcpp/ap_solver.h>

using namespace APCPP;
using namespace std;

APSolver::APSolver(const unsigned int size) : size(size) { }

void APSolver::print(ostream& out) {
    out << "========================================================================" << endl;
    out << "z\t" << setw(5) << setfill(' ') << right << get_z() << endl << endl;

    out << "u\t";
    for (unsigned int row = 0; row < size; ++row)
        out << setw(5) << setfill(' ') << right << get_u(row);
    out << endl;

    out << "v\t";
    for (unsigned int col = 0; col < size; ++col)
        out << setw(5) << setfill(' ') << right << get_v(col);
    out << endl << endl;

    out << "rc\t";
    for (unsigned int row = 0; row < size; ++row) {
        for (unsigned int col = 0; col < size; ++col)
            out << setw(5) << setfill(' ') << right << get_rc({row, col});
        out << endl << "\t";
    }
    out << endl;

    out << "x\t";
    for (unsigned int row = 0; row < size; ++row) {
        for (unsigned int col = 0; col < size; ++col) {
            out << setw(5) << setfill(' ') << right
                << (get_x({row, col}) ? "1" : "-");
        }
        out << endl;
        if (row < size - 1)
            out << "\t";
    }

    out << "------------------------------------------------------------------------" << endl;
}
