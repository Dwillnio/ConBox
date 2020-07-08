#include "kalman_filter_ext.h"

const vec& kalman_filter_ext::compute(rnum t, const vec& x, const vec& u, const vec& z)
{
    vec x_hat_pre = f_func->value(t, x_est_, u, vec(0));
    matrix P_pre = f_lin->value(t,x,u) * P * f_lin->value(t,x,u).transpose() + Q;

    matrix H = h_lin->value(t,x,u);

    vec alpha = h_func->value(t,x) - h_func->value(t,x_hat_pre);
    matrix K = P_pre * H.transpose() * (H*P_pre*H.transpose() + R).inverse();
    x_est_ = x_hat_pre + K * alpha;
    P = (matrix::unit(dim_x_) - K*H) * P_pre;

    return x_est_;
}
