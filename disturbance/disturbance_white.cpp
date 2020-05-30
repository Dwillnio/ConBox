#include "disturbance_white.h"

vec disturbance_white::compute(rnum t, const vec& x)
{
    vec v(dim_z_);
    for(nnum i=0; i<dim_z_; i++) {
        rnum num = num_generator(generator);
        if(chain) {
            last_val[i] += num;
            v[i] = last_val[i];
        } else {
            v[i] = num;
        }
    }
    return v;
}
