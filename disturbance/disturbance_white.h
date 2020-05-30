#ifndef DISTURBANCE_WHITE_H
#define DISTURBANCE_WHITE_H

#include <random>

#include "disturbance.h"

class disturbance_white : public disturbance
{
public:
    disturbance_white(nnum dim_x, nnum dim_z, rnum mean_value, rnum standard_deviation, bool chained = true)
        : disturbance(dim_x, dim_z), mean(mean_value), std_dev(standard_deviation), chain(chained),
          num_generator(mean, std_dev){}

    virtual vec compute(rnum t, const vec& x);

protected:
    rnum mean, std_dev;
    bool chain;
    vec last_val = 0;
    std::default_random_engine generator;
    std::normal_distribution<> num_generator;
};

#endif // DISTURBANCE_WHITE_H
