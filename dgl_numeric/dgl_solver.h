#ifndef DGL_SOLVER_H
#define DGL_SOLVER_H

#include "base/vec.h"
#include "base/func_dgl.h"

class dgl_solver
{
public:
    dgl_solver(rnum d_t, func_dgl* f) : delta_t(d_t), func(f) {};

    virtual vec step(rnum t, const vec& x, const vec& u, const vec& z) const = 0;

    rnum& delta_time() {return delta_t;}

protected:
    rnum delta_t;
    func_dgl* func;
};

#endif // DGL_SOLVER_H
