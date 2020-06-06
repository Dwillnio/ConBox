#include "test_observer.h"


void luenberger_observer_test_1(int argc, char** argv, std::ostream& os)
{
    rnum d_t = 0.01;
    rnum y_target = -2;

    linear_system osc = harm_osc();
    //func_dgl_p func(func_osc_contrl, 2, 1, 0);

    const_function w_func(y_target, 1, 1);

    state_controller contr(2, 1, 0, 1, matrix(std::vector<rnum>{0,18},1));

    vec x_start(2);
    x_start[0] = 1;
    x_start[1] = 0;

    dgl_rungekutta solver(d_t, &osc);

    stationary_filter filt(1,1, matrix(std::vector<rnum>{10},1));

    luenberger_observer obs(vec({5,5}), d_t, osc.A_mat(), osc.B_mat(), osc.C_mat(), matrix({9.8,22.04}, 2));

    simulator_obs sim(&solver, &osc, &contr, x_start, d_t, 50, &filt, &obs, &w_func);
    sim.run();

    std::vector<time_value> x_result = sim.get_xresult();
    std::vector<time_value> u_result = sim.get_uresult();
    std::vector<time_value> x_est_result = sim.get_x_estimates();
    visualizer display(argc, argv);
    //display.visualize_result(&u_result, 0, &x_result, 0);
    display.visualize_result(x_result, std::vector<nnum>({0,1}), u_result, std::vector<nnum>({0}),
                             x_result, std::vector<nnum>({0}), x_est_result);
}
