#include "stationary_filter.h"

vec stationary_filter::compute(rnum t, const vec& w)
{
    vec u(dim_u_);
    u = S_ * w;
    return u;
}
