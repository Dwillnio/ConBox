#ifndef DGL_RUNGEKUTTA_H
#define DGL_RUNGEKUTTA_H

#include "dgl_solver.h"

class dgl_rungekutta : public dgl_solver
{
public:
    dgl_rungekutta(rnum d_t, func_dgl* f) : dgl_solver(d_t, f) {};

    virtual vec step(rnum t, const vec& x, const vec& u, const vec& z) const;
};

#endif // DGL_RUNGEKUTTA_H
