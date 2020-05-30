#include "simulator.h"


simulator::simulator(dgl_solver* solver, func_dgl* func, controller* contr, vec& x_start,
                     rnum d_t, rnum t_end,
                     function* w_func, function* z_func)
    : solver_(solver), func_(func), contr_(contr), x_start_(x_start),
      d_t_(d_t), t_end_(t_end),
      w_func_(w_func), z_func_(z_func), x_cur_(x_start)
{
    t = 0;
}

void simulator::run()
{
    while(t < t_end_)
        step();
}

void simulator::step()
{
    vec time_vec(1);
    time_vec[0] = t;

    vec z_cur(func_->d_z());
    for(unsigned i = 0; i < z_cur.dimension(); i++)
        z_cur[i] = 0;
    if(z_func_)
        vec z_cur = z_func_->value(time_vec);

    vec w_cur = w_func_->value(time_vec);

    vec u_cur = contr_->compute(t, x_cur_, z_cur, w_cur);

    vec x_next = solver_->step(t, x_cur_, u_cur, z_cur);

    x_values_.push_back(time_value(t, x_cur_));
    u_values_.push_back(time_value(t, u_cur));
    z_values_.push_back(time_value(t, z_cur));

    t += d_t_;
    x_cur_ = x_next;
}



