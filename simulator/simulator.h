#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <vector>

#include "dgl_numeric/dgl_solver.h"
#include "base/func_dgl.h"
#include "base/function.h"
#include "controller/controller.h"
#include "base/vec.h"

struct time_value
{
    time_value(rnum time, vec value) : time_(time), value_(value){}

    rnum time_;
    vec value_;
};

class simulator
{
public:
    simulator(dgl_solver* solver, func_dgl* func, controller* contr, vec& x_start,
              rnum d_t, rnum t_end,
              function* w_func, function* z_func = nullptr);

    virtual void run();
    virtual void step();
    virtual vec calc_u(const vec& z_cur, const vec& w_cur);

    std::vector<time_value> get_xresult() {return x_values_;}
    std::vector<time_value> get_uresult() {return u_values_;}
    std::vector<time_value> get_zresult() {return u_values_;}

protected:
    dgl_solver* solver_;
    func_dgl* func_;
    controller* contr_;

    rnum t, d_t_, t_end_;

    vec x_start_;
    vec x_cur_;

    function* w_func_;
    function* z_func_;

    rnum u_max, u_min;

    std::vector<time_value> x_values_;
    std::vector<time_value> u_values_;
    std::vector<time_value> z_values_;
};

#endif // SIMULATOR_H
