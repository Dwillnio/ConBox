#ifndef LUENBERGER_OBSERVER_H
#define LUENBERGER_OBSERVER_H

#include "observer.h"
#include "base/matrix.h"
#include "base/vec.h"
#include "dgl_numeric/dgl_rungekutta.h"

class luenberger_observer : public observer, public func_dgl
{
public:
    luenberger_observer(const vec& x_est_start, rnum d_t,
                        const matrix& A, const matrix& B, const matrix& C, const matrix& L)
        : luenberger_observer(x_est_start, d_t, A, B, C, matrix(A.rows(),0), L){}


    luenberger_observer(const vec& x_est_start, rnum d_t,
                        const matrix& A, const matrix& B, const matrix& C,
                        const matrix& E, const matrix& L)
        : observer(A.rows(), B.cols(), E.cols(), C.rows(), x_est_start),
          func_dgl(A.rows(), B.cols(), E.cols()), solver_(d_t, this),
          A_(A), B_(B), C_(C), E_(E), L_(L), x_cur(vec(A.rows()))
    {
        if(B_.rows() != dim_x_)
            throw new std::runtime_error("L-OBSERVER B DIM ERROR");

        if(C_.cols() != dim_x_)
            throw new std::runtime_error("L-OBSERVER C DIM ERROR");

        if(E.rows() != dim_x_)
            throw new std::runtime_error("L-OBSERVER E DIM ERROR");

        if(L.rows() != dim_x_ || L_.cols() != dim_w_)
            throw new std::runtime_error("L-OBSERVER L DIM ERROR");
    }

    virtual const vec& compute(rnum t, const vec& x, const vec& u, const vec& z);

    virtual vec value(rnum t, const vec& x, const vec& u, const vec& z);

protected:
    dgl_rungekutta solver_; //make changeable?
    matrix A_, B_, C_, E_, L_;
    vec x_cur;
};

#endif // LUENBERGER_OBSERVER_H
