#ifndef KALMAN_FILTER_H
#define KALMAN_FILTER_H

#include "base/matrix.h"
#include "base/vec.h"
#include "observer.h"
#include "linear_system/linear_system_d.h"

class kalman_filter : public observer
{
public:
    kalman_filter(const linear_system_d& sys_, const vec& x0_,
                  const matrix& P0_, const matrix& Q_, const matrix& R_)
        : observer(sys_.dims(), x0_), sys(sys_), P(P0_), Q(Q_), R(R_)
    {
        if(P.rows() != P.cols() || P.rows() != dim_x_)
            throw new std::runtime_error("KALMAN-FILTER P DIM ERROR");

        if(Q.rows() != Q.cols() || Q.rows() != dim_x_)
            throw new std::runtime_error("KALMAN-FILTER Q DIM ERROR");

        if(R.rows() != R.cols() || R.rows() != dim_w_)
            throw new std::runtime_error("KALMAN-FILTER R DIM ERROR");
    }

    virtual const vec& compute(rnum t, const vec& x, const vec& u, const vec& z);

    const matrix& uncertainty() {return P;}

protected:
    linear_system_d sys;

    matrix P, Q, R;

};

#endif // KALMAN_FILTER_H
