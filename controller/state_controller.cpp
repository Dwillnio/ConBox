#include "state_controller.h"

vec state_controller::compute(rnum t, const vec& x, const vec& z, const vec& w)
{
    return -1.0 * K * x;
}
