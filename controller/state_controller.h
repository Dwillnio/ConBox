#ifndef STATE_CONTROLLER_H
#define STATE_CONTROLLER_H

#include "controller.h"
#include "base/matrix.h"

class state_controller : public controller
{
public:
    state_controller(nnum dim_x, nnum dim_u, nnum dim_z, nnum dim_w)
        : controller(dim_x, dim_u, dim_z, dim_w), K(dim_u, dim_x) {}

    state_controller(nnum dim_x, nnum dim_u, nnum dim_z, nnum dim_w, const matrix& m)
        : controller(dim_x, dim_u, dim_z, dim_w), K(m)
    {
        if(m.d_col()!=dim_x || m.d_row()!=dim_u)
            throw new std::runtime_error("WRONG K MATRIX DIM");
    }

    virtual vec compute(rnum t, const vec& x, const vec& z, const vec& w);

    void K_matrix(const matrix& m) {K = m;}
    const matrix& K_matrix() const {return K;}

private:
    matrix K;
};

#endif // STATE_CONTROLLER_H
