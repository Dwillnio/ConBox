#ifndef FUNCTION_D_DATA_H
#define FUNCTION_D_DATA_H

#include "function_d.h"

class function_d_data : public function_d
{
public:
    function_d_data(nnum d_to, const std::vector<vec>* data_points_)
        : function_d(1, d_to), data_points(data_points_) {}

    virtual vec value(nnum k, const vec& x) {return value(k);}
    virtual vec value(nnum k) {return (*data_points)[k];}

protected:
    const std::vector<vec>* data_points;
};

#endif // FUNCTION_D_DATA_H
