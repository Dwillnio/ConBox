#include "difference_eq_solver.h"

vec difference_eq_solver::step(nnum k, const vec& x, const vec& u, const vec& z) const
{
    return x + (*func)(k,x,u,z);
}


vec difference_eq_solver::step(rnum t, const vec& x, const vec& u, const vec& z) const
{
    return x + (*func)(t,x,u,z);    // appropiate conversion from t -> k in func_d_dgl
}
