#ifndef TRANSFER_FUNCTION_H
#define TRANSFER_FUNCTION_H

#include <iostream>

#include "polynom.h"
#include "func_dgl.h"
#include "linear_system/linear_system.h"
#include "dgl_numeric/dgl_rungekutta.h"

class transfer_function : public func_dgl
{
    friend std::ostream& operator<< (std::ostream& os, const transfer_function& tf);

public:
    transfer_function(const polynom& y_coeffs_, const polynom& u_coeffs_, rnum dt_=0.1)
        : func_dgl(y_coeffs.deg_c(), 1, 0), y_coeffs(y_coeffs_), u_coeffs(u_coeffs_),
          x_vals(y_coeffs_.deg_c()), lin_form(cnf(y_coeffs_, u_coeffs_)), dt(dt_), t(0),
          dgl_solver(dt_, this) {}
    //transfer_function(const linear_system& sys);

    static linear_system cnf(const polynom& y_coeffs_, const polynom& u_coeffs_);
    const linear_system& cnf() const {return lin_form;}

    rnum step(const vec& u);
    virtual vec value(rnum t, const vec& x, const vec& u, const vec& z);


protected:
    polynom y_coeffs, u_coeffs;
    vec x_vals;
    linear_system lin_form;

    rnum dt, t;

    dgl_rungekutta dgl_solver;
};


std::ostream& operator<< (std::ostream& os, const transfer_function& tf);

#endif // TRANSFER_FUNCTION_H
