#include "func_dgl.h"

vec func_dgl::value(const vec& x)
{
    if(x.len() != d_from())
        return vec(0);

    rnum t = x[0];
    vec x_(dim_x);
    vec u_(dim_u);
    vec z_(dim_z);

    for(nnum i = 0; i < x_.len(); i++){
        x_[i] = x[1+i];
    }
    for(nnum i = 0; i < u_.len(); i++){
        u_[i] = x[1+x_.len()+i];
    }
    for(nnum i = 0; i < z_.len(); i++){
        z_[i] = x[1+x_.len()+z_.len()+i];
    }

    return value(t, x_, u_, z_);
}

vec func_dgl_p::value(rnum t, const vec& x, const vec& u, const vec& z)
{
    if(x.dimension() != d_x() || u.dimension() != d_u() || z.dimension() != d_z())
        return vec(0);

    return func(t, x, u, z);
}

