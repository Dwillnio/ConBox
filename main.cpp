
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

#include "test/test_cnum.h"
#include "test/test_disturbance.h"
#include "test/test_linear_system.h"

using namespace std;

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
    //linear_system_test_2();
    //return 0;

    rnum d_t = 0.01;
    rnum y_target = -2;

    func_dgl_p func(func_osc_contrl, 2, 1, 0);

    const_function w_func(y_target, 1, 1);

    state_controller contr(2, 1, 0, 1, matrix(std::vector<rnum>{0,18},1));

    vec x_start(2);
    x_start[0] = 1;
    x_start[1] = 0;

    dgl_rungekutta solver(d_t, &func);

    stationary_filter filt(1,1, matrix(std::vector<rnum>{10},1));

    simulator_prefilter sim(&solver, &func, &contr, x_start, d_t, 10, &filt, &w_func);
    sim.run();

    std::vector<time_value> x_result = sim.get_xresult();
    std::vector<time_value> u_result = sim.get_uresult();
    visualizer display(argc, argv);
    //display.visualize_result(&u_result, 0, &x_result, 0);
    display.visualize_result(x_result, std::vector<nnum>({0,1}), u_result, std::vector<nnum>({0}), x_result, std::vector<nnum>({0}));
    return 0;

    std::vector<rnum> np({1,1,1}), nq({1,2}), zeros({-1,-2});
    polynom p(np);
    polynom q(nq);
    std::cout << p << "\n" << q << "\n" << p * q << "\n" << polynom::zeros2polynom(zeros) << "\n";
    return 0;

    cnum c(1,1), d(2,0), e(1,-1);
    rnum r(2);
    Eigen::MatrixXcd z;
    vec v(std::vector<rnum>({1,2,3}));
    matrix m(std::vector<rnum>({1,2,3,4,5,6,7,8,9}), 3);
    matrix a(std::vector<rnum>({-1/sqrt(2),-1/sqrt(2),0,1/sqrt(2),-1/sqrt(2),0,0,0,1}), 3);
    matrix temp(m);
    matrix b({12,-51,4,6,167,-68,-4,24,-41}, 3);
    //std::cout << 2.0*matrix::unit(4);
    //std::cout << b.det() << "\n";
    //std::cout << b.inverse();
    std::cout << b;
    std::pair<matrix,matrix> qr = b.QR_decomposition();
    std::cout << qr.first << qr.second << qr.first * qr.second;
    for(nnum i = 0; i<20; i++) {
        qr = b.QR_decomposition();
        b = qr.second * qr.first;
    }
    std::cout << qr.second;

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
