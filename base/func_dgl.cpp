#include "func_dgl.h"

vec func_dgl::value(const vec& x)
{
    if(x.dimension() != d_from())
        return vec(0);

    rnum t = x[0];
    vec x_(dim_x);
    vec u_(dim_u);
    vec z_(dim_z);

    for(nnum i = 0; i < x_.dimension(); i++){
        x_[i] = x[1+i];
    }
    for(nnum i = 0; i < u_.dimension(); i++){
        u_[i] = x[1+x_.dimension()+i];
    }
    for(nnum i = 0; i < z_.dimension(); i++){
        z_[i] = x[1+x_.dimension()+z_.dimension()+i];
    }

    return value(t, x_, u_, z_);
}

vec func_dgl_p::value(rnum t, const vec& x, const vec& u, const vec& z)
{
    if(x.dimension() != d_x() || u.dimension() != d_u() || z.dimension() != d_z())
        return vec(0);

    return func(t, x, u, z);
}

