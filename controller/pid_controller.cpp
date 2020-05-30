#include "pid_controller.h"

pid_controller::pid_controller(rnum P_const, rnum I_const, rnum D_const, rnum d_t,
               nnum d_x, nnum d_z,
               nnum y_ind, nnum u_ind, nnum w_ind)
    : controller(d_x, 1, d_z, 1),
      P_const_(P_const), I_const_(I_const), D_const_(D_const), d_t_(d_t),
      u_max_(STD_ULIMIT), u_min_(-STD_ULIMIT),
      integr_(0), y_ind_(y_ind), u_ind_(u_ind), w_ind_(w_ind), start(true) {}


vec pid_controller::compute(rnum t, const vec& x, const vec& z, const vec& w)
{
    rnum u = 0;
    rnum y_target = w[w_ind_];
    rnum y_cur = x[y_ind_];

    integr_ += d_t_ * (y_target - y_cur);

    u += P_const_*(y_target - y_cur);
    u += I_const_ * integr_;

    if(!start)
        u += D_const_/d_t_*(y_prev_ - y_cur);
    else
        start = false;

    if(u > u_max_)
        u = u_max_;
    if(u < u_min_)
        u = u_min_;

    y_prev_ = y_cur;

    vec v(dim_u_);
    v[u_ind_] = u;
    return v;
}
