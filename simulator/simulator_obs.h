#ifndef SIMULATOR_OBS_H
#define SIMULATOR_OBS_H

#include "simulator.h"
#include "controller/prefilter.h"
#include "observer/observer.h"

class simulator_obs : public simulator
{
public:
    simulator_obs(dgl_solver* solver, func_dgl* func, controller* contr, vec& x_start,
                  rnum d_t, rnum t_end, prefilter* filter, observer* observer,
                  function* w_func, function* z_func = nullptr)
    : simulator(solver, func, contr, x_start, d_t, t_end, w_func, z_func),
      filter_(filter), observer_(observer) {}

    virtual void step();

protected:
    prefilter* filter_;
    observer* observer_;

    std::vector<time_value> x_estimates;
};

#endif // SIMULATOR_OBS_H
