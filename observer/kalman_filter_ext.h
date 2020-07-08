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

class kalman_filter_ext : public kalman_filter
{
public:
    kalman_filter_ext(const linear_system_d& sys_, const vec& x0_,
                      const matrix& P0_, const matrix& Q_, const matrix& R_,
                      const func_matrix_lin& f_lin_, const func_matrix_lin& h_lin_);

protected:
    func_matrix_lin f_lin, h_lin;
};

#endif // KALMAN_FILTER_EXT_H
