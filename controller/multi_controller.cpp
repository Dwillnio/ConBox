#include "multi_controller.h"
#include <exception>

vec multi_controller::compute(rnum t, const vec& x, const vec& z, const vec& w)
{
    if(controller1_ && controller2_) {
        return controller1_->compute(t, x, z, w) + controller2_->compute(t, x, z, w);

    } else throw new std::runtime_error("Multicontroller missing one or more controllers");
}
