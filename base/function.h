#ifndef FUNCTION_H
#define FUNCTION_H

#include "vec.h"

class function
{
public:
    function(const function& f) : func(f.func), dim_from(f.d_from()), dim_to(f.dim_to){};
    function(vec (*f) (const vec& v), nnum d_from, nnum d_to) : func(f),
        dim_from(d_from), dim_to(d_to) {};

    virtual vec value(const vec& x) const;

    nnum d_from() const {return dim_from;}
    nnum d_to() const {return dim_to;}

private:
    vec (*func) (const vec& v);
    const nnum dim_from, dim_to;
};

class const_function : public function
{
public:
    //const_function(const const_function& f) : func(f.func), dim_from(f.d_from()), dim_to(f.dim_to){};

    const_function(rnum const_value, nnum d_from, nnum d_to) : function(nullptr, d_from, d_to),
        const_value_(const_value) {};

    virtual vec value(const vec& x) const
    {
        vec temp(d_to());
        for(unsigned i = 0; i < x.dimension(); i++)
            temp[i] = const_value_;

        return temp;
    }

private:
    rnum const_value_;
};

#endif // FUNCTION_H
