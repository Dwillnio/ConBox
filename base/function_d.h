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

class const_function_d : public function_d
{
public:
    const_function_d(rnum const_value, nnum d_from, nnum d_to) : function_d(d_from, d_to),
        const_value_(const_value) {};

    virtual vec value(nnum k, const vec& x)
    {
        vec temp(d_to());
        for(unsigned i = 0; i < x.dimension(); i++)
            temp[i] = const_value_;

        return temp;
    }

private:
    rnum const_value_;
};


#endif // FUNCTION_D_H
