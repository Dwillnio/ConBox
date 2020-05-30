#ifndef DIMENSIONS_H
#define DIMENSIONS_H

#include "base/definitions.h"

struct dimensions
{
    dimensions(nnum d_x = 0, nnum d_u = 0, nnum d_z = 0, nnum d_w = 0)
        : dim_x(d_x), dim_u(d_u), dim_z(d_z), dim_w(d_w) {}

    nnum dim_x, dim_u, dim_z, dim_w;
};

#endif // DIMENSIONS_H
