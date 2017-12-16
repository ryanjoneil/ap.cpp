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

#ifndef APCPP_PRIMAL_DUAL_AP_SOLVER_H
#define APCPP_PRIMAL_DUAL_AP_SOLVER_H

#include <set>
#include <vector>

#include <apcpp/ap_solver.h>

namespace APCPP {
    class PrimalDualAPSolver : public APSolver {
    public:
        PrimalDualAPSolver(const unsigned int size);

        virtual void solve() override;

        virtual void set_obj(APIndex index, int _obj) override;
        virtual void remove_arc(APIndex index) override;
        virtual void remove_arc(APIndex index, int obj) override;

        virtual int get_z() const override;
        virtual bool get_x(APIndex index) override;
        virtual int get_rc(APIndex index) override;
        virtual int get_u(unsigned int row) override;
        virtual int get_v(unsigned int col) override;

    protected:
        int z;
        std::vector<std::vector<int>> a;
        std::vector<int> u;
        std::vector<int> v;

        std::vector<APIndex> zeroes;
        std::vector<bool> covered_rows;
        std::vector<bool> covered_cols;

    private:
        void initialize();
        int path(int i);
        void increase(int i, int j);

        void initialize_phase_1();
        void initialize_phase_2();

        int min_row(int j);
        int min_col(int i);

        std::vector<int> f;        // f[i] = j if i assigned to j, -1 if i unassigned
        std::vector<int> f_bar;    // f_bar[j] = row assigned to column j, -1 if unassigned
        std::vector<int> p;        // first column of row i not yet examined in phase 2

        std::vector<int> LR;       // vector of labelled rows
        std::set<int> UC;          // set of unlabelled columns
        std::vector<int> c;        // c[j] = row preceding column j in current alternating path
        std::vector<int> pi;       // pi[j] = min { a[i,j] - u[i] - v[j] | i in LR, i != f_bar[j] }

        bool initialized;
    };
}

#endif
