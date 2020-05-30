#ifndef MULTI_CONTROLLER_H
#define MULTI_CONTROLLER_H

#include "controller.h"

class multi_controller : public controller
{
public:
    multi_controller(controller* controller1, controller* controller2, nnum dim_x, nnum dim_u, nnum dim_z, nnum dim_w)
        : controller(dim_x, dim_u, dim_z, dim_w), controller1_(controller1), controller2_(controller2){};

    virtual vec compute(rnum t, const vec& x, const vec& z, const vec& w);

    controller* contr1() {return controller1_;}
    void contr1(controller* contr) {controller1_ = contr;}

    controller* contr2() {return controller2_;}
    void contr2(controller* contr) {controller2_ = contr;}

protected:
    controller* controller1_;
    controller* controller2_;
};

#endif // MULTI_CONTROLLER_H
