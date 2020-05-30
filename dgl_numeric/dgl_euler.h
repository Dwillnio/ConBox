#ifndef DGL_NEWTON_H
#define DGL_NEWTON_H

#include "dgl_solver.h"

class dgl_euler : public dgl_solver
{
public:
    dgl_euler(rnum d_t, func_dgl& f) : dgl_solver(d_t, f) {};

    virtual vec step(rnum t, const vec& x, const vec& u, const vec& z) const;
};

#endif // DGL_NEWTON_H
