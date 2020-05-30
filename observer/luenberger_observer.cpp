#include "luenberger_observer.h"

const vec& luenberger_observer::compute(const vec& x, const vec& u, const vec& z, const vec& w)
{

}

vec luenberger_observer::value(const vec& x, const vec& u, const vec& z)
{
    vec v(dim_x_);

    v = A_ * x + B_ * u + E_ * z + L_*C_*(x + (-1 * x_est_));

    return v;
}
