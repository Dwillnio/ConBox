#ifndef OBSERVER_H
#define OBSERVER_H

#include "base/definitions.h"
#include "base/vec.h"
#include "controller/dimensions.h"

class observer
{
public:
    observer(dimensions d, const vec& x_est_start)
        : observer(d.dim_x, d.dim_u, d.dim_z, d.dim_w, x_est_start) {}

    observer(dimensions d)
        : observer(d.dim_x, d.dim_u, d.dim_z, d.dim_w) {}

    observer(nnum dim_x, nnum dim_u, nnum dim_z, nnum dim_w, const vec& x_est_start)
        : dim_x_(dim_x), dim_u_(dim_u), dim_z_(dim_z), dim_w_(dim_w), x_est_(x_est_start) {}

    observer(nnum dim_x, nnum dim_u, nnum dim_z, nnum dim_w)
        : dim_x_(dim_x), dim_u_(dim_u), dim_z_(dim_z), dim_w_(dim_w), x_est_(dim_x) {}

    virtual const vec& compute(const vec& x, const vec& u, const vec& z, const vec& w) = 0;

    const vec& get() {return x_est_;}

protected:
    nnum dim_x_, dim_u_, dim_z_, dim_w_;
    vec x_est_;
    //vec x_est_start_;
};

#endif // OBSERVER_H
