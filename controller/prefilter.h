#ifndef PREFILTER_H
#define PREFILTER_H

#include "base/definitions.h"
#include "base/vec.h"

class prefilter
{
public:
    prefilter(nnum dim_u, nnum dim_w) : dim_u_(dim_u), dim_w_(dim_w) {}

    virtual vec compute(rnum t, const vec& w) = 0;

protected:
    nnum dim_u_, dim_w_;
};

#endif // PREFILTER_H
