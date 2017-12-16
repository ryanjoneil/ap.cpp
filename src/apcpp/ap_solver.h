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

#ifndef APCPP_AP_SOLVER_H
#define APCPP_AP_SOLVER_H

#include <ostream>
#include <utility>

namespace APCPP {
    typedef std::pair<unsigned int, unsigned int> APIndex;

    class APSolver {
    public:
        APSolver(const unsigned int size);
        virtual ~APSolver() { }

        virtual void solve() = 0;

        virtual void set_obj(APIndex index, int obj) = 0;
        virtual void remove_arc(APIndex index) = 0;
        virtual void remove_arc(APIndex index, int obj) = 0;

        virtual int get_z() const = 0;
        virtual bool get_x(APIndex index) = 0;
        virtual int get_rc(APIndex index) = 0;
        virtual int get_u(unsigned int row) = 0;
        virtual int get_v(unsigned int col) = 0;

        void print(std::ostream& out);

    protected:
        const unsigned int size;
    };
}

#endif
