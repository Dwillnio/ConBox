#include "function.h"

vec function_p::value(const vec& x) {
    if(x.dimension() != d_from())
        return vec(0);

    return func(x);
}

vec empty_func(const vec& v) {return vec(0);}
function_p empty_func_class = function_p(empty_func, 0, 0);
