#include "function.h"

vec function::value(const vec& x) const {
    if(x.dimension() != dim_from)
        return vec(0);

    return func(x);
}

vec empty_func(const vec& v) {return vec(0);}
function empty_func_class = function(empty_func, 0, 0);
