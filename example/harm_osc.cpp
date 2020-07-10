#include "harm_osc.h"
#include "gui/visualizer.h"
#include "controller/state_controller.h"
#include "dgl_numeric/dgl_rungekutta.h"
#include "observer/luenberger_observer.h"
#include "simulator/simulator_prefilter.h"
#include "controller/stationary_filter.h"

linear_system harm_osc(rnum alpha, rnum beta, rnum gamma)
{
    matrix A = matrix(std::vector<rnum>{0,1,-alpha,-beta},2);

    matrix B = matrix(std::vector<rnum>{0, gamma}, 2);

    matrix C = matrix(std::vector<rnum>{1,0}, 1);

    return linear_system(A,B,C);
}

void harm_osc_test(std::ostream& os)
{
    rnum d_t = 0.01;
    rnum y_target = -2;

    linear_system sys = harm_osc(1, 0.2, 0.1);

    const_function w_func(y_target, 1, 1);

    state_controller contr(2, 1, 0, 1, matrix(std::vector<rnum>{0,18},1));

    vec x_start(2);
    x_start[0] = 1;
    x_start[1] = 0;

    dgl_rungekutta solver(d_t, &sys);

    stationary_filter filt(1,1, matrix(std::vector<rnum>{10},1));

    simulator_prefilter sim(&solver, &sys, &contr, x_start, d_t, 10, &filt, &w_func);
    sim.run();

    std::vector<time_value> x_result = sim.get_xresult();
    std::vector<time_value> u_result = sim.get_uresult();
    visualizer display(0, 0);
    display.visualize_result(x_result, std::vector<nnum>({0,1}), u_result, std::vector<nnum>({0}), x_result, std::vector<nnum>({0}));
}
