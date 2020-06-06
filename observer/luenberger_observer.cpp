#include "luenberger_observer.h"

const vec& luenberger_observer::compute(rnum t, const vec& x, const vec& u, const vec& z)
{
    x_cur = x;
    x_est_ = solver_.step(t, x_est_, u, z);
    return x_est_;
}

// make it func + lc(xc - xest)
vec luenberger_observer::value(rnum t, const vec& x, const vec& u, const vec& z)
{
    vec v(dim_x_);

    v = A_ * x_est_ + B_ * u + E_ * z + L_*C_*(x_cur - x);

    return v;
}
