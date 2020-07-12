#include "test_det_least_squares.h"


void det_least_squares_test_1(std::ostream& os)
{
    nnum n = 3;
    vec y({0,0,4,-2,8,-14,38,-84});
    vec ysol(y.dimension()-1);
    for(nnum i=0; i<ysol.dimension(); i++)
        ysol[i] = y[i+1];
    vec u({2,2,2,2,2,2,2,2});
    matrix M = compute_m(y,u,n);
    vec m_new = compute_mline(y,u,n);
    std::cout << M << std::endl;
    std::cout << m_new << std::endl;
    std::cout << "\nSolution:\n" << project_vector_solution(M,ysol)
              << "\n" << project_vector(M,ysol);

    matrix M_acausal = compute_m(y,u,n,false);
    std::cout << "Acausal:\n" << M_acausal << std::endl;
    std::cout << "\nSolution:\n" << project_vector_solution(M_acausal,y)
              << "\n" << project_vector(M_acausal,y);
}
