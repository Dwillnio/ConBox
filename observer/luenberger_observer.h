#ifndef LUENBERGER_OBSERVER_H
#define LUENBERGER_OBSERVER_H

#include "observer.h"
#include "base/matrix.h"
#include "base/vec.h"
#include "dgl_numeric/dgl_solver.h"

class luenberger_observer : public observer
{
public:
    luenberger_observer(dimensions d, const vec& x_est_start,
                        const matrix& A, const matrix& B, const matrix& C,
                        const matrix& E, const matrix& L)
        : luenberger_observer(d.dim_x, d.dim_u, d.dim_z, d.dim_w, x_est_start, A, B, C, E, L){}

    luenberger_observer(dimensions d, const vec& x_est_start,
                        const matrix& A, const matrix& B, const matrix& C, const matrix& L)
        : luenberger_observer(d, x_est_start, A, B, C, matrix(d.dim_x, d.dim_z), L) {}


    luenberger_observer(nnum dim_x, nnum dim_u, nnum dim_z, nnum dim_w, const vec& x_est_start,
                        const matrix& A, const matrix& B, const matrix& C, const matrix& L)
        : luenberger_observer(dim_x, dim_u, dim_z, dim_w, x_est_start, A, B, C, matrix(dim_x,dim_z), L) {}


    luenberger_observer(nnum dim_x, nnum dim_u, nnum dim_z, nnum dim_w, const vec& x_est_start,
                        const matrix& A, const matrix& B, const matrix& C,
                        const matrix& E, const matrix& L)
        : observer(dim_x, dim_u, dim_z, dim_w, x_est_start), A_(A), B_(B), C_(C), E_(E), L_(L)
    {
        if(A_.d_col() != A_.d_row() || A.d_col() != dim_x)
            throw new std::runtime_error("L-OBSERVER A DIM ERROR");

        if(B_.d_row() != dim_x || B.d_col() != dim_u)
            throw new std::runtime_error("L-OBSERVER B DIM ERROR");

        if(C.d_row() != dim_w || C_.d_col() != dim_x)
            throw new std::runtime_error("L-OBSERVER C DIM ERROR");

        if(E.d_row() != dim_x || E_.d_col() != dim_z)
            throw new std::runtime_error("L-OBSERVER E DIM ERROR");

        if(L.d_row() != dim_x || L_.d_col() != dim_w)
            throw new std::runtime_error("L-OBSERVER L DIM ERROR");
    }

    virtual const vec& compute(const vec& x, const vec& u, const vec& z, const vec& w);

    vec value(const vec& x, const vec& u, const vec& z);

protected:
    matrix A_, B_, C_, E_, L_;

    //dgl_solver_cl* solver;
};

#endif // LUENBERGER_OBSERVER_H
