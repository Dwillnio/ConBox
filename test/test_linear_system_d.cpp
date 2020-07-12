#include "test_linear_system_d.h"

void linear_system_d_test_1(std::ostream& os)
{
    rnum ssig_w = 1;
    matrix A({0,1, 0,0},2), B({0,1},2), C({1,0},1), Q({0,0,0,ssig_w},2);
    linear_system csys(A,B,C);

    rnum dt=0.1;
    linear_system_d dsys = linear_system_d::convert(csys,dt);
    matrix Qk = linear_system_d::convert_noise(A,Q,dt);

    std::cout << "A:\n" << dsys.A_mat() << std::endl;
    std::cout << "B:\n" << dsys.B_mat() << std::endl;
    std::cout << "Q:\n" << Qk << std::endl;
}
