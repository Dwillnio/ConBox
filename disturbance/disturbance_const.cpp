#include "disturbance_const.h"

vec disturbance_const::compute(rnum t, const vec& x)
{
    vec v(dim_z_);
    for(nnum i=0; i<dim_z_; i++) {
        v[i] = val;
    }
    return v;
}
