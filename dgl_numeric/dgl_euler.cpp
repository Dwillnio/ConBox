#include "dgl_euler.h"

vec dgl_euler::step(rnum t, const vec& x, const vec& u, const vec& z) const
{
    if(x.dimension() != func->d_x() || u.dimension() != func->d_u() || z.dimension() != func->d_z())
        return vec(0);

    vec v(x.dimension());
    vec val = func->value(t, x, u, z);

    for(unsigned int i = 0; i < v.dimension(); ++i)
        v[i] = x[i] + delta_t * val[i];

    return v;
}
