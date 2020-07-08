#ifndef KALMAN_FILTER_EXT_H
#define KALMAN_FILTER_EXT_H

#include "base/matrix.h"
#include "kalman_filter.h"

class func_matrix_lin
{
public:
    virtual const matrix& value(rnum t, const vec& x, const vec& u) = 0;

    const matrix& operator() (rnum t, const vec& x, const vec& u)
    {return value(t,x,u);}

};

class func_matrix_lin_p : func_matrix_lin
{
public:
    func_matrix_lin_p(const matrix& (*const fpointer_)(rnum t, const vec& x, const vec& u))
        : fpointer(fpointer_) {}

    virtual const matrix& value(rnum t, const vec& x, const vec& u) {return fpointer(t,x,u);}

protected:
    const matrix& (*const fpointer)(rnum t, const vec& x, const vec& u);

};

class kalman_filter_ext : public observer
{
public:
    kalman_filter_ext(func_dgl* f_func_, function_time* h_func_, const vec& x0_,
                      const matrix& P0_, const matrix& Q_, const matrix& R_,
                      func_matrix_lin* f_lin_, func_matrix_lin* h_lin_)
        : observer(f_func_->d_x(), f_func_->d_u(), f_func_->d_z(), h_func_->d_to()),
          f_func(f_func_), h_func(h_func_),
          P(P0_), Q(Q_), R(R_), f_lin(f_lin_), h_lin(h_lin_) {}

    virtual const vec& compute(rnum t, const vec& x, const vec& u, const vec& z);

    const matrix& uncertainty() {return P;}

protected:
    func_dgl* f_func;
    function_time* h_func;
    matrix P, Q, R;
    func_matrix_lin* f_lin,* h_lin;
};

#endif // KALMAN_FILTER_EXT_H
