#include "harm_osc.h"

linear_system harm_osc()
{
    rnum alpha = 1, beta = 0.2, gamma = 0.1;

    matrix A = matrix(std::vector<rnum>{0,1,-alpha,-beta},2);

    matrix B = matrix(std::vector<rnum>{0, gamma}, 2);

    matrix C = matrix(std::vector<rnum>{1,0}, 1);

    return linear_system(A,B,C);
}
