#ifndef STATIONARY_FILTER_H
#define STATIONARY_FILTER_H

#include "prefilter.h"
#include "base/matrix.h"

class stationary_filter : public prefilter
{
public:
    stationary_filter(nnum dim_u, nnum dim_w, const matrix& S)
        : prefilter(dim_u, dim_w), S_(S) {}

    virtual vec compute(rnum t, const vec& w);

protected:
    matrix S_;
};

#endif // STATIONARY_FILTER_H
