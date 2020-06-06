#include "simulator_prefilter.h"

/*
void simulator_prefilter::step()
{
    vec time_vec(1);
    time_vec[0] = t;

    vec z_cur(func_->d_z());
    for(unsigned i = 0; i < z_cur.dimension(); i++)
        z_cur[i] = 0;
    if(z_func_)
        vec z_cur = z_func_->value(time_vec);

    vec w_cur = w_func_->value(time_vec);

    vec u_cur = contr_->compute(t, x_cur_, z_cur, w_cur) + filter_->compute(t, w_cur);

    vec x_next = solver_->step(t, x_cur_, u_cur, z_cur);

    x_values_.push_back(time_value(t, x_cur_));
    u_values_.push_back(time_value(t, u_cur));
    z_values_.push_back(time_value(t, z_cur));

    t += d_t_;
    x_cur_ = x_next;
}
*/

vec simulator_prefilter::calc_u(const vec& z_cur, const vec& w_cur)
{
    return contr_->compute(t, x_cur_, z_cur, w_cur) + filter_->compute(t, w_cur);
}
