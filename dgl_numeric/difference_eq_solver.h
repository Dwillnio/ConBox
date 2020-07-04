#ifndef DIFFERENCE_EQ_SOLVER_H
#define DIFFERENCE_EQ_SOLVER_H

#include "base/func_d_dgl.h"
#include "dgl_solver.h"

class difference_eq_solver : public dgl_solver
{
public:
    difference_eq_solver(rnum dt_, func_d_dgl* f)
        : dgl_solver(dt, f), func(f), dt(dt_) {}

    virtual vec step(rnum t, const vec& x, const vec& u, const vec& z) const;
    virtual vec step(nnum k, const vec& x, const vec& u, const vec& z) const;

protected:
    func_d_dgl* func;
    rnum dt;
};

#endif // DIFFERENCE_EQ_SOLVER_H
