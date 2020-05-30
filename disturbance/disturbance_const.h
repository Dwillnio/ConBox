#ifndef DISTURBANCE_CONST_H
#define DISTURBANCE_CONST_H

#include "disturbance.h"

class disturbance_const : public disturbance
{
public:
    disturbance_const(nnum dim_x, nnum dim_z, rnum value)
        : disturbance(dim_x, dim_z), val(value) {}

    virtual vec compute(rnum t, const vec& x);

protected:
    rnum val;
};

#endif // DISTURBANCE_CONST_H
