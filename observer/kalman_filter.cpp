#include "kalman_filter.h"

const vec& kalman_filter::compute(rnum t, const vec& x, const vec& u, const vec& z)
{
    vec x_hat_pre = sys.value(t, x_est_, u, vec(0));
    matrix P_pre = sys.A_mat() * P * sys.A_mat().transpose() + Q;

    vec alpha = sys.C_mat() * (x - x_hat_pre);
    matrix K = P_pre * sys.C_mat().transpose()
            * (sys.C_mat()*P_pre*sys.C_mat().transpose() + R).inverse();
    x_est_ = x_hat_pre + K * alpha;
    P = (matrix::unit(dim_x_) - K*sys.C_mat()) * P_pre;

    return x_est_;
}
