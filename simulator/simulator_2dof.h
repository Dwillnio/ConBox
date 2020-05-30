#ifndef SIMULATOR_2DOF_H
#define SIMULATOR_2DOF_H

#include "simulator.h"

class simulator_2dof : public simulator
{
public:
    simulator_2dof(dgl_solver* solver, func_dgl* func, controller* contr, vec& x_start,
                   rnum d_t, rnum t_end,
                   function* traj_func,
                   function* w_func, function* z_func = nullptr);
};

#endif // SIMULATOR_2DOF_H
