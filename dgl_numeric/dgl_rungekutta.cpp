#include "dgl_rungekutta.h"

vec dgl_rungekutta::step(rnum t, const vec& x, const vec& u, const vec& z) const
{
    if(x.dimension() != func->d_x() || u.dimension() != func->d_u() || z.dimension() != func->d_z())
        return vec(0);

    rnum b1 = 1.0/6, b2 = 1.0/3, b3 = 1.0/3, b4 = 1.0/6;
    rnum c1 = 0, c2 = 0.5, c3 = 0.5, c4 = 1;
    rnum a21 = 0.5, a32 = 0.5, a43 = 1;
    vec k1(x.dimension()), k2(x.dimension()), k3(x.dimension()), k4(x.dimension());

    k1 = func->value(t + c1 * delta_t, x, u, z);
    k2 = func->value(t + c2 * delta_t, x + k1 * a21 * delta_t, u, z);
    k3 = func->value(t + c3 * delta_t, x + k2 * a32 * delta_t, u, z);
    k4 = func->value(t + c4 * delta_t, x + k3 * a43 * delta_t, u, z);

    vec v(x.dimension());
    v = x + (k1 * b1 + k2 * b2 + k3 * b3 + k4 * b4) * delta_t;

    return v;
}
