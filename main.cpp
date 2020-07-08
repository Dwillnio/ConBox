
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

    visualizer display(argc, argv);
    display.visualize_result(x_result, std::vector<nnum>({0,1}), p_vals, std::vector<nnum>({0,1,2}),
                             y_vals, std::vector<nnum>({0}), x_estimates);
    return 0;

//    matrix A({0,3,2, 1,0,4, 0,1,0}, 3), B({0,1,2, 0,0,1, 1,0,0}, 3), C(matrix::unit(3));
//    linear_system exampl(A,B,C);
//    auto cind = exampl.contr_ind();
//    for(nnum i: cind)
//        std::cout << i << " , ";
//    std::cout << std::endl;

//    matrix A2({0,0,1,0, 1,0,2,0, 0,1,3,1, 0,0,-1,2}, 4), B2({1,0, 0,0, 0,0, 0,1}, 4), C2({1,0,0,0},1);
//    linear_system exampl2(A2,B2,C2);
//    auto cind2 = exampl2.contr_ind();
//    for(nnum i: cind2)
//        std::cout << i << " , ";
//    std::cout << std::endl;
//    std::cout << exampl2.control_normal_form().A_mat() << std::endl;
//    std::cout << exampl2.control_normal_form().B_mat() << std::endl;
//    std::cout << exampl2.control_normal_form().C_mat() << std::endl;
//    return 0;

//    linear_system invpend = inv_pend_lin(false);
//    rnum d_t = 0.01;
//    rnum y_target = 1;
//    const_function w_func(y_target, 1, 1);
//    matrix K(invpend.feedback_ackermann(polynom::zeros2polynom({-1,-1,-1,-1})));
//    state_controller contr(4, 1, 0, 1, K);
//    vec x_start({0,0,0.1,0});
//    vec x_est_start({0,0,0,0});

//    dgl_rungekutta solver(d_t, &invpend);
//    stationary_filter filt(1,1, invpend.static_prefilter(K));
//    matrix L = invpend.L(polynom::zeros2polynom({-5,-5,-5,-5}));
//    luenberger_observer obs(x_est_start, d_t, invpend.A_mat(), invpend.B_mat(), invpend.C_mat(), L);
//    simulator_obs sim(&solver, &invpend, &contr, x_start, d_t, 10, &filt, &obs, &w_func);
//    //simulator_prefilter sim(&solver, &invpend, &contr, x_start, d_t, 10, &filt, &w_func);
//    sim.run();

//    std::vector<time_value> x_result = sim.get_xresult();
//    std::vector<time_value> u_result = sim.get_uresult();
//    std::vector<time_value> x_est_result = sim.get_x_estimates();
//    //std::vector<time_value> x_est_result = sim.get_xresult();
//    visualizer display(argc, argv);
//    display.visualize_result(x_result, std::vector<nnum>({2}), u_result, std::vector<nnum>({0}), x_result, std::vector<nnum>({2}), x_est_result);
//    return 0;

//    rnum d_t = 0.01;
//    rnum y_target = -2;

//    //linear_system osc = harm_osc();
//    func_dgl_p func(func_osc_contrl, 2, 1, 0);

//    const_function w_func(y_target, 1, 1);

//    state_controller contr(2, 1, 0, 1, matrix(std::vector<rnum>{0,18},1));

//    vec x_start(2);
//    x_start[0] = 1;
//    x_start[1] = 0;

//    dgl_rungekutta solver(d_t, &func);

//    stationary_filter filt(1,1, matrix(std::vector<rnum>{10},1));

//    simulator_prefilter sim(&solver, &func, &contr, x_start, d_t, 10, &filt, &w_func);
//    sim.run();

//    std::vector<time_value> x_result = sim.get_xresult();
//    std::vector<time_value> u_result = sim.get_uresult();
//    visualizer display(argc, argv);
//    //display.visualize_result(&u_result, 0, &x_result, 0);
//    display.visualize_result(x_result, std::vector<nnum>({0,1}), u_result, std::vector<nnum>({0}), x_result, std::vector<nnum>({0}));
//    return 0;

//    std::vector<rnum> np({1,1,1}), nq({1,2}), zeros({-1,-2});
//    polynom p(np);
//    polynom q(nq);
//    std::cout << p << "\n" << q << "\n" << p * q << "\n" << polynom::zeros2polynom(zeros) << "\n";
//    return 0;

    //std::cout << c/c << "\n";
    /*
    rnum d_t = 0.01;
    rnum y_target = 2;

    pid_controller contr(50, 30, 30, d_t, 2, 0, 0);
    contr.ulimit(0, 30);

    func_dgl_p func(func_osc_contrl, 2, 1, 0);

    const_function w_func(y_target, 1, 1);

    vec x_start(2);
    x_start[0] = 1;
    x_start[1] = 0;

    dgl_rungekutta solver(d_t, &func);

    simulator sim(&solver, &func, &contr, x_start, d_t, 10, &w_func);
    sim.run();

    std::vector<time_value> x_result = sim.get_xresult();
    std::vector<time_value>  u_result = sim.get_uresult();
    visualizer display(argc, argv);
    display.visualize_result(&u_result, 0, &x_result, 0);
    //*/
}
