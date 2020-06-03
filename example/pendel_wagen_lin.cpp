#include "pendel_wagen_lin.h"

linear_system pendel_wagen_lin()
{
    rnum g = 9.81, m = 1, M = 10, l = 1;

    matrix A = matrix(std::vector<rnum>({0, 1, 0, 0,
                       (6*g*(m+M)/(l*(m+4*M))), 0, 0, 0,
                       0, 0, 0, 1,
                       -3*m*g/(m+4*M), 0, 0, 0}),4);

    std::vector<rnum> v({0, -6/(l*(m+M)), 0, 4/(m+4*M)});
    matrix B = matrix(v, 4);

    matrix C = matrix(std::vector<rnum>({1,0,0,0}), 1);

    return linear_system(A,B,C);
}
