#include "func_d_dgl.h"


vec func_d_dgl::value(nnum k, const vec& x)
{
    if(x.dimension() != dx_from())
        return vec(0);

    vec x_(d_x());
    vec u_(d_u());
    vec z_(d_z());

    for(nnum i = 0; i < x_.dimension(); i++){
        x_[i] = x[i];
    }
    for(nnum i = 0; i < u_.dimension(); i++){
        u_[i] = x[x_.dimension()+i];
    }
    for(nnum i = 0; i < z_.dimension(); i++){
        z_[i] = x[x_.dimension()+z_.dimension()+i];
    }

    return value(k, x_, u_, z_);
}

vec func_d_dgl::value(rnum t, const vec& x, const vec& u, const vec& z)
{
    return value(static_cast<nnum>(t/dt), x, u, z);
}
