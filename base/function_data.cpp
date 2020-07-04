#include "function_data.h"



vec function_data::value(const vec &x)
{
    if(x.len() != 1)
        return vec(0);

    rnum t = x[0];
    nnum ind = static_cast<nnum>(t/dt);
    return (*data_points)[ind];
}
