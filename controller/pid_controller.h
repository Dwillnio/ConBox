#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H

#include <tuple>

#include "controller.h"

#define STD_ULIMIT 1000000

class pid_controller : public controller
{
public:
    pid_controller(rnum P_const, rnum I_const, rnum D_const, rnum d_t,
                   nnum d_x, nnum d_z,
                   nnum y_ind, nnum u_ind = 0, nnum w_ind = 0);

    virtual vec compute(rnum t, const vec& x, const vec& z, const vec& w);

    void ulimit(rnum d) {u_max_ = u_min_ = d;}
    void ulimit(rnum u_min, rnum u_max) {u_max_  = u_max; u_min_ = u_min;}
    std::tuple<rnum, rnum> u_limit() {return std::tuple<rnum, rnum> (u_min_, u_max_);}

    void constants(rnum P_const, rnum I_const, rnum D_const)
        {P_const_ = P_const; I_const_ = I_const; D_const_ = D_const;}
    std::tuple<rnum, rnum, rnum> constants()
        {return std::tuple<rnum, rnum, rnum>(P_const_, I_const_, D_const_);}

    void delta_time(rnum d_t) {d_t_ = d_t;}
    rnum delta_time() {return d_t_;}

    void y_index(nnum y_ind) {y_ind_ = y_ind;}
    nnum y_index() {return y_ind_;}

protected:
    rnum P_const_, I_const_, D_const_;
    rnum u_max_, u_min_;
    rnum d_t_;

    nnum y_ind_, u_ind_, w_ind_; // x[y_ind] ==> w[0]

    rnum integr_;
    rnum y_prev_;
    bool start;
};

#endif // PID_CONTROLLER_H
