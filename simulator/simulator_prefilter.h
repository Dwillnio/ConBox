#ifndef SIMULATOR_PREFILTER_H
#define SIMULATOR_PREFILTER_H

#include "simulator.h"
#include "controller/prefilter.h"

class simulator_prefilter : public simulator
{
public:
    simulator_prefilter(dgl_solver* solver, func_dgl* func, controller* contr, vec& x_start,
                        rnum d_t, rnum t_end, prefilter* filter,
                        function* w_func, function* z_func = nullptr)
        : simulator(solver, func, contr, x_start, d_t, t_end, w_func, z_func),
          filter_(filter) {}

    //virtual void step();
    virtual vec calc_u(const vec& z_cur, const vec& w_cur);

protected:
    prefilter* filter_;
};

#endif // SIMULATOR_PREFILTER_H
