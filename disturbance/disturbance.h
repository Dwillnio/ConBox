#ifndef DISTURBANCE_H
#define DISTURBANCE_H

#include "base/definitions.h"
#include "base/vec.h"
#include "base/function.h"

class disturbance : public function
{
public:
    disturbance(nnum dim_x, nnum dim_z) : function(dim_x+1, dim_z), dim_x_(dim_x), dim_z_(dim_z) {}

    virtual vec compute(rnum t, const vec& x) = 0;
    virtual vec value(const vec& x);

protected:
    nnum dim_x_, dim_z_;
};

#endif
