#ifndef FUNCTION_D_H
#define FUNCTION_D_H

#include "base/definitions.h"
#include "vec.h"

class function_d
{
public:
    function_d(nnum dx_from, nnum d_to) : dimx_from(dx_from), dim_to(d_to) {}

    virtual vec value(nnum k, const vec& x) = 0;

    nnum dx_from() const {return dimx_from;}
    nnum d_to() const {return dim_to;}

    vec operator() (nnum k, const vec& x)
    {return value(k, x);}

private:
    const nnum dimx_from, dim_to;
};

#endif // FUNCTION_D_H
