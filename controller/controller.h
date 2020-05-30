#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "base/vec.h"
#include "base/function.h"

class controller
{
public:
    controller(nnum dim_x, nnum dim_u, nnum dim_z, nnum dim_w)
        : dim_x_(dim_x), dim_u_(dim_u), dim_z_(dim_z), dim_w_(dim_w) {}

    virtual vec compute(rnum t, const vec& x, const vec& z, const vec& w) = 0;

    void dim_x(nnum d_x) {dim_x_ = d_x;}
    nnum dim_x() {return dim_x_;}

    void dim_u(nnum d_u) {dim_u_ = d_u;}
    nnum dim_u() {return dim_u_;}

    void dim_z(nnum d_z) {dim_z_ = d_z;}
    nnum dim_z() {return dim_z_;}

    void dim_w(nnum d_w) {dim_w_ = d_w;}
    nnum dim_w() {return dim_w_;}

protected:
    nnum dim_x_, dim_u_, dim_z_, dim_w_;
};

#endif // CONTROLLER_H
