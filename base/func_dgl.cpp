#include "func_dgl.h"

vec func_dgl::value(rnum t, const vec& x, const vec& u, const vec& z) const
{
    if(x.dimension() != dim_x || u.dimension() != dim_u || z.dimension() != dim_z)
        return vec(0);

    return func(t, x, u, z);
}
