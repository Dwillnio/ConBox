#include "simulator_obs.h"

/*
void simulator_obs::step()
{
    vec time_vec(1);
    time_vec[0] = t;

    vec z_cur(func_->d_z());
    for(unsigned i = 0; i < z_cur.dimension(); i++)
        z_cur[i] = 0;
    if(z_func_)
        vec z_cur = z_func_->value(time_vec);

    vec w_cur = w_func_->value(time_vec);

    vec u_cur = contr_->compute(t, observer_->get(), z_cur, w_cur) + filter_->compute(t, w_cur);

    observer_->compute(t, x_cur_, u_cur, z_cur);
    vec x_next = solver_->step(t, x_cur_, u_cur, z_cur);

    x_values_.push_back(time_value(t, x_cur_));
    u_values_.push_back(time_value(t, u_cur));
    z_values_.push_back(time_value(t, z_cur));
    x_estimates.push_back(time_value(t, observer_->get()));

    t += d_t_;
    x_cur_ = x_next;
}
*/

vec simulator_obs::calc_u(const vec& z_cur, const vec& w_cur)
{
    vec u_cur = contr_->compute(t, observer_->get(), z_cur, w_cur) + filter_->compute(t, w_cur);
    x_estimates.push_back(time_value(t, observer_->get()));
    observer_->compute(t, x_cur_, u_cur, z_cur);
    return u_cur;
}
