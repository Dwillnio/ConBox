#include "test_kalman_filter.h"

void kalman_filter_test_1(std::ostream& os)
{
    rnum dt = 0.01;
    rnum ssig_u = 2, ssig_x = 10, ssig_n = 1;
    matrix A({1,dt, 0,1},2);
    matrix B({0,0},2);
    matrix C({1,0},1);
    matrix Q({dt*dt*dt/3, dt*dt/2, dt*dt/2, dt},2);
    Q = ssig_u * Q;
    matrix R(1,1);
    R(0,0) = ssig_n;
    matrix P({ssig_x, 0, 0, ssig_x},2);
    linear_system sys(matrix({0,1,0,0},2), matrix({0,0},2), matrix({1,0},1));
    linear_system_d dsys(A,B,C);

    vec x_est_start({0,10});


    kalman_filter obs(dsys, x_est_start, P, Q, R);
    const nnum num_steps = 100;
    const rnum path_length = 10;
    disturbance_white dist(0,1,0,sqrt(ssig_n),false);
    std::vector<time_value> x_estimates;
    x_estimates.push_back(time_value(0, x_est_start));
    std::vector<time_value> y_vals;
    y_vals.push_back(time_value(0, vec({0})));
    vec x_est = x_est_start;
    std::vector<time_value> p_vals;
    for(nnum i = 1; i < num_steps; i++){
        rnum y = path_length / num_steps * i + dist.compute(0, vec(0))[0];
        y_vals.push_back(time_value(i * dt, vec({y})));
        x_est = obs.compute(i * dt, vec({y, 0}), vec(1), vec(0));
        x_estimates.push_back(time_value(i * dt, x_est));
        matrix p = obs.uncertainty();
        p_vals.push_back(time_value(i*dt, vec({p(0,0), p(1,1), p(0,1)})));
    }

    std::vector<time_value> x_result;
    for(nnum i = 0; i < num_steps; i++){
        x_result.push_back(time_value(i*dt, vec({path_length / num_steps * i, path_length / (dt * num_steps)})));
    }

    visualizer display(0, 0);
    display.visualize_result(x_result, std::vector<nnum>({0,1}), p_vals, std::vector<nnum>({0,1,2}),
                             y_vals, std::vector<nnum>({0}), x_estimates);
    return;
}
