#include "linear_system_d.h"

vec linear_system_d::value(nnum k, const vec& x, const vec& u, const vec& z)
{
    return A*x + B*u + E*z;
}

vec linear_system_d::y_val(const vec& x) const
{
    return C*x;
}
