#include "inverted_pend_lin.h"
#include "gui/visualizer.h"
#include "controller/state_controller.h"
#include "dgl_numeric/dgl_rungekutta.h"
#include "observer/luenberger_observer.h"
#include "simulator/simulator_obs.h"
#include "controller/stationary_filter.h"

linear_system inv_pend_lin(bool output_angle, rnum m, rnum M, rnum I, rnum l, rnum b)
{
    rnum g = 9.81;
    rnum e22 = -(I+m*l*l)*b/(I*(m+M) + M*m*l*l);
    rnum e23 = m*m*g*l*l/(I*(m+M) + M*m*l*l);
    rnum e42 = -m*l*b/(I*(m+M) + M*m*l*l);
    rnum e43 = m*g*l*(m+M)/(I*(m+M) + M*m*l*l);

    rnum b2 = I + m *l*l/(I*(m+M) + M*m*l*l);
    rnum b4 = m*l/(I*(m+M) + M*m*l*l);

    matrix A({0,1,0,0, 0,e22,e23,0, 0,0,0,1, 0,e42,e43,0},4);
    matrix B({0,b2,0,b4},4);
    matrix C(1,4);
    if(output_angle)
        C = matrix({0,0,1,0},1);
    else
        C = matrix({1,0,0,0},1);

    return linear_system(A,B,C);
}


void inv_pend_lin_test(std::ostream& os)
{

    linear_system invpend = inv_pend_lin(false);
    rnum d_t = 0.01;
    rnum y_target = 1;
    const_function w_func(y_target, 1, 1);
    matrix K(invpend.feedback_ackermann(polynom::zeros2polynom({-1,-1,-1,-1})));
    state_controller contr(4, 1, 0, 1, K);
    vec x_start({0,0,0.1,0});
    vec x_est_start({0,0,0,0});

    dgl_rungekutta solver(d_t, &invpend);
    stationary_filter filt(1,1, invpend.static_prefilter(K));
    matrix L = invpend.L(polynom::zeros2polynom({-5,-5,-5,-5}));
    luenberger_observer obs(x_est_start, d_t, invpend.A_mat(), invpend.B_mat(), invpend.C_mat(), L);
    simulator_obs sim(&solver, &invpend, &contr, x_start, d_t, 10, &filt, &obs, &w_func);
    //simulator_prefilter sim(&solver, &invpend, &contr, x_start, d_t, 10, &filt, &w_func);
    sim.run();

    std::vector<time_value> x_result = sim.get_xresult();
    std::vector<time_value> u_result = sim.get_uresult();
    std::vector<time_value> x_est_result = sim.get_x_estimates();
    //std::vector<time_value> x_est_result = sim.get_xresult();
    visualizer display(0, 0);
    display.visualize_result(x_result, std::vector<nnum>({2}), u_result, std::vector<nnum>({0}), x_result, std::vector<nnum>({2}), x_est_result);
}
