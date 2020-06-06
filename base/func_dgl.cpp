#include "func_dgl.h"

vec func_dgl_p::value(rnum t, const vec& x, const vec& u, const vec& z)
{
    if(x.dimension() != d_x() || u.dimension() != d_u() || z.dimension() != d_z())
        return vec(0);

    return func(t, x, u, z);
}
