#ifndef DOF2_PID_CONTROLLER_H
#define DOF2_PID_CONTROLLER_H

#include "pid_controller.h"

class DOF2_pid_controller : public pid_controller
{
public:
    DOF2_pid_controller();

    virtual vec compute(rnum t, const vec& x, const vec& z, const vec& w);

protected:
    function* transfer_func_;
};

#endif // DOF2_PID_CONTROLLER_H
