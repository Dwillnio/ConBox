#include "coupled_spring_oscillator.h"


linear_system coupled_spring_oscillator(rnum m1, rnum m2, rnum d1, rnum d2, rnum c1, rnum c2)
{
    matrix A({0,1,0,0,
              -c1/m1, -d1/m1, c1/m1, d1/m1,
              0,0,0,1,
              c1/m2, d1/m2, -(c1+c2)/m2, -(d1+d2)/m2},4);
    matrix B({0,-1/m1,0,0},4);
    matrix C({0,0,1,0},1);
    matrix E({0,0,0,-1/m2},4);

    return linear_system(A,B,C,E);
}
