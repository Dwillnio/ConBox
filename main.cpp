
#include <QLineSeries>
#include <QPushButton>
#include <iostream>
#include <QImageReader>

#include "gui/window.h"
#include "gui/visualizer.h"
#include "dgl_numeric/dgl_euler.h"
#include "dgl_numeric/dgl_rungekutta.h"

#include "simulator/simulator.h"
#include "simulator/simulator_prefilter.h"
#include "controller/pid_controller.h"
#include "controller/state_controller.h"
#include "controller/stationary_filter.h"

#include "base/function.h"
#include "base/func_dgl.h"
#include "base/matrix.h"
#include "base/cnum.h"
#include "base/polynom.h"

#include "observer/kalman_filter.h"
#include "linear_system/linear_system_d.h"

#include "test/test_cnum.h"
#include "test/test_disturbance.h"
#include "test/test_linear_system.h"
#include "test/test_matrix.h"
#include "test/test_observer.h"
#include "test/test_kalman_filter.h"

#include "example/inverted_pend_lin.h"
#include "example/pendel_wagen_lin.h"

#include "disturbance/disturbance_white.h"

using namespace std;

//TODO: tests for different systems, mimo, 2dof trajectory control, parameter estimation, digital control, optimization, nonlinear, animation gui

vec func_e(rnum t, const vec& x, const vec& u, const vec& z)
{
    vec v(1);
    v[0] = x[0];
    return v;
}

vec func_osc(rnum t, const vec& x, const vec& u, const vec& z)
{
    rnum alpha = 0.2;
    vec v(2);
    v[0] = x[1];
    v[1] = -1*x[0] - alpha*x[1];
    return v;
}

vec func_osc_contrl(rnum t, const vec& x, const vec& u, const vec& z)
{
    rnum alpha = 0.2, beta = 0.1;
    vec v(2);
    v[0] = x[1];
    v[1] = -1*x[0] - alpha*x[1] + beta * u[0];
    return v;
}


void pid_osc(QLineSeries* data_x, QLineSeries* data_u)
{

    rnum P_const = 50, I_const = 30, D_const = 30;
    rnum y_target = 2, y_prev = 0;
    rnum integr = 0;
    rnum u_max = 10000, u_min = -10000;
    std::cout.precision(3);

    rnum t = 0;
    rnum t_end = 10;
    rnum d_t = 0.010;
    int steps = (t_end - t)/d_t;

    func_dgl_p function(func_osc_contrl, 2, 1, 0);
    vec x(2);
    x[0] = 1;
    x[1] = 0;

    y_prev = x[0];
    vec u(1), z(0);

    dgl_rungekutta solver(d_t, &function);

    std::cout << t << ":\t" << x[0] << "\n";

    if(data_x && data_u) {
        data_x->append(t, x[0]);
        data_u->append(t, u[0]);
    }

    for(int i = 0; i < steps; ++i) {
        integr += d_t * (y_target - x[0]);
        u[0] = P_const*(y_target - x[0]);// + I_const * integr + D_const/d_t*(y_prev - x[0]);
        u[0] += I_const * integr;
        u[0] += D_const/d_t*(y_prev - x[0]);

        if(u[0] > u_max)
            u[0] = u_max;
        if(u[0] < u_min)
            u[0] = u_min;

        std::cout << t << ":\t" << "x: "<< x[0]
                  << "\tu: "<< u[0]
                  << "\n\tP: "<< P_const*(y_target - x[0])
                  << "\tI: "<< I_const * integr
                  << "\tD: "<< D_const/d_t*(y_prev - x[0]) << "\n";

        y_prev = x[0];

        x = solver.step(t, x, u, z);
        t += d_t;

        if(data_x && data_u) {
            data_x->append(t, x[0]);
            data_u->append(t, u[0]);
        }
    }

    std::cout << std::flush;
}

void display_result(int argc, char** argv, QLineSeries* data_x, QLineSeries* data_u)
{
    QApplication a(argc, argv);

    Window w(data_x, data_u);
    w.show();

    a.exec();
}

int main(int argc, char** argv)
{
    return 0;
}
