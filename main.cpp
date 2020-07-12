
#include <QLineSeries>
#include <QPushButton>
#include <iostream>
#include <QImageReader>

#include "gui/window.h"
#include "gui/visualizer.h"
#include "dgl_numeric/dgl_euler.h"
#include "dgl_numeric/dgl_rungekutta.h"
#include "dgl_numeric/difference_eq_solver.h"

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
#include "base/transfer_function.h"

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
#include "example/coupled_spring_oscillator.h"

#include "disturbance/disturbance_white.h"

#include "identification/det_least_squares.h"
#include "identification/stoch_least_squares.h"

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
    rnum dt = 0.2, T = 10;
    transfer_function tf({1,2,1},{1},dt);
    std::cout << tf << std::endl;
    linear_system csys = tf.cnf();
    linear_system_d dsys = linear_system_d::convert(csys, dt);
    std::cout << "Continuous:\n" << csys.A_mat() << csys.B_mat();
    std::cout << "\nDiscrete:\n" << dsys.A_mat() << dsys.B_mat();
    difference_eq_solver solver(dt, &dsys);
    vec x_cur(dsys.A_mat().rows());

    const_function_d u_func(1,0,1);
    std::vector<time_value> y_vals;
    std::vector<time_value> x_vals;
    std::vector<time_value> u_vals;
    for(nnum i=0; i<T/dt; i++){
        y_vals.push_back(time_value(i*dt, dsys.C_mat()*x_cur));
        x_vals.push_back(time_value(i*dt, x_cur));
        u_vals.push_back(time_value(i*dt, u_func.value(i,x_cur)));
        x_cur = solver.step(i*dt, x_cur, u_func.value(i,x_cur), vec(0));
    }


    nnum order = 2;
    vec y(y_vals.size()), y2(y_vals.size()-1);
    vec u(y_vals.size()-1);
    y[0] = y_vals[0].value_[0];
    for(nnum i=0; i<y2.dimension(); i++){
        y[i+1]=y_vals[i+1].value_[0];
        y2[i]=y_vals[i+1].value_[0];
        u[i]=u_vals[i].value_[0];
    }
    matrix m = compute_m(y, u, order);
    vec v = project_vector_solution(m, y2);
    std::cout << std::endl << "y_vals:" << y << "\nu_vals:" << u << "\nSolution:" << v << "\nM:" << m;

    vec y_start({y_vals[0].value_[0], y_vals[1].value_[0]});
    vec u_start({1,1});
    matrix m0 = compute_m(y_start, u_start, order);
    vec v0 = project_vector_solution(m0, {y_vals[1].value_[0], y_vals[2].value_[0]});
    std::cout << "Solutions:\n";
    std::cout << v0;
    det_rlse identifier(m0, v0, order);
    std::vector<time_value> thetas;
    thetas.push_back({0,0*v0});
    thetas.push_back({dt,v0});
    for(nnum i=2; i<T/dt-1; i++){
        vec theta = identifier.compute(y_vals[i].value_[0], u_vals[i].value_[0]);
        thetas.push_back({i*dt,v0});
    }

    std::cout << thetas[thetas.size()-1].value_;
    visualizer gui(argc, argv);
    gui.visualize_result(x_vals, {0,1}, thetas, {0,1,2,3}, y_vals, {0}, std::vector<time_value>());

    return 0;
    //PUT TO COUPLED SPRING OSCILLATOR
    linear_system sys = coupled_spring_oscillator(1,10,1,1,1,1);
    std::cout << sys.t_S() << std::endl;
    std::cout << sys.feedback_ackermann(polynom({1,3.5,5.5,4,1})) << std::endl;
    std::cout << sys.H_y().second[0] << std::endl;
    std::cout << sys.feedback_decoupling(polynom({1,3,3,1}));
    return 0;
}
