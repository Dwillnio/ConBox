#ifndef FUNCTION_DATA_H
#define FUNCTION_DATA_H

#include <vector>

#include "function.h"

class function_data : public function
{
public:
    function_data(std::vector<vec>* data_points_, rnum dt_)
        : function(1, (*data_points_)[0].len()), dt(dt_) {}

    virtual vec value(const vec &x);
    virtual vec value(nnum k) {return (*data_points)[k];}

protected:
    const std::vector<vec>* data_points;
    rnum dt;
};

#endif // FUNCTION_DATA_H
