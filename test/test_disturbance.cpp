#include "test_disturbance.h"

void disturbance_test_1(std::ostream& os)
{
    disturbance_const dconst1(0,0,1);
    disturbance_const dconst2(0,2,2);
    disturbance_const dconst3(2,0,3);
    disturbance_const dconst4(2,2,4);
    disturbance_const dconst5(4,1,5);

    vec x0(0);
    vec x2(2);
    vec x4(4);

    rnum t = 0;

    os << "Disturbancevalues:\n";
    os << "1 = " << dconst1.compute(t,x0) << "\n";
    os << "2 = " << dconst2.compute(t,x0) << "\n";
    os << "3 = " << dconst3.compute(t,x2) << "\n";
    os << "4 = " << dconst4.compute(t,x2) << "\n";
    os << "5 = " << dconst5.compute(t,x4) << "\n";
}

#define DIST_TEST_SAMPLES 20
void disturbance_test_2(std::ostream& os)
{
    disturbance_white dconst1(2,1,0,1,false);
    disturbance_white dconst2(2,2,4,1,false);

    vec x2(2);

    rnum t = 0;

    rnum mean = 0;
    rnum std_dev = 0;
    std::vector<rnum> v;
    for(nnum i = 0; i < DIST_TEST_SAMPLES; i++){
        v.push_back(dconst1.compute(t, x2)[0]);
        os << dconst2.compute(t, x2) << " ";
    }

    for(nnum i = 0; i < v.size(); i++){
        mean += v[i];
    }
    mean /= v.size();

    for(nnum i = 0; i < v.size(); i++){
        std_dev += std::pow(v[i] - mean, 2);
    }
    std_dev /= v.size();
    std_dev = std::sqrt(std_dev);
    os << "\nmean: " << mean << "\tstd_dev: " << std_dev << std::endl;

    mean = 0;
    std_dev = 0;
    v = std::vector<rnum>();
    for(nnum i = 0; i < DIST_TEST_SAMPLES; i++){
        v.push_back(dconst2.compute(t, x2)[0]);
    }

    for(nnum i = 0; i < v.size(); i++){
        mean += v[i];
    }
    mean /= v.size();

    for(nnum i = 0; i < v.size(); i++){
        std_dev += std::pow(v[i] - mean, 2);
    }
    std_dev /= v.size();
    std_dev = std::sqrt(std_dev);
    os << "\nmean: " << mean << "\tstd_dev: " << std_dev << std::endl;
}







































