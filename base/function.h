#ifndef FUNCTION_H
#define FUNCTION_H

#include "vec.h"

class function
{
public:
    function(nnum d_from, nnum d_to) : dim_from(d_from), dim_to(d_to) {};

    virtual vec value(const vec& x) = 0;

    nnum d_from() const {return dim_from;}
    nnum d_to() const {return dim_to;}

private:
    const nnum dim_from, dim_to;
};

class function_p : public function
{
public:
    function_p(vec (*f) (const vec& v), nnum d_from, nnum d_to) :
        function(d_from, d_to), func(f) {};

    virtual vec value(const vec& x);
private:
    vec (*func) (const vec& v);
};

class const_function : public function
{
public:
    //const_function(const const_function& f) : func(f.func), dim_from(f.d_from()), dim_to(f.dim_to){};

    const_function(rnum const_value, nnum d_from, nnum d_to) : function(d_from, d_to),
        const_value_(const_value) {};

    virtual vec value(const vec& x)
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
