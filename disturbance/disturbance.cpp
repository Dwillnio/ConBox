#include "disturbance.h"

vec disturbance::value(const vec& x)
{
    vec v(x.dimension()-1);
    for(nnum i = 0; i < v.dimension(); i++)
        v[i] = x[i+1];

    return compute(x[0], v);
}
