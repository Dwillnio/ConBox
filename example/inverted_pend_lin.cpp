#include "inverted_pend_lin.h"


linear_system inv_pend_lin(bool output_angle, rnum m, rnum M, rnum I, rnum l, rnum b)
{
    rnum g = 9.81;
    rnum e22 = -(I+m*l*l)*b/(I*(m+M) + M*m*l*l);
    rnum e23 = m*m*g*l*l/(I*(m+M) + M*m*l*l);
    rnum e42 = -m*l*b/(I*(m+M) + M*m*l*l);
    rnum e43 = m*g*l*(m+M)/(I*(m+M) + M*m*l*l);

    rnum b2 = I + m *l*l/(I*(m+M) + M*m*l*l);
    rnum b4 = m*l/(I*(m+M) + M*m*l*l);

    matrix A({0,1,0,0, 0,e22,e23,0, 0,0,0,1, 0,e42,e43,0},4);
    matrix B({0,b2,0,b4},4);
    matrix C(1,4);
    if(output_angle)
        C = matrix({0,0,1,0},1);
    else
        C = matrix({1,0,0,0},1);

    return linear_system(A,B,C);
}
