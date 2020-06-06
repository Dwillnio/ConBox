#include "test_matrix.h"

void matrix_test_1(std::ostream& os)
{
    matrix m1 = matrix::unit(4), m2(4,4),
           m3({1,2,3,4,5,6,7,8,9,10,11,12},3),
           m4({1,2,3,4,5,6,7,8,9,10,11,12},4),
           m5({1,5,6,2,1,4,6,7,1,2,5,7,3,6,7,2},4),
           m6(0,0), m7(0,1), m8(1,0);

    os << "Matrices:\n";
    os << m1 << "----\n" << m2 << "----\n" << m3 << "----\n" << m4 << "----\n" << m5<< "----\n" ;

    os << "Addition:\n";
    os << m1 + m2 << "----\n" << m1 - m5<< "----\n"<< m6 + m6<< "----\n"<< m7 - m7<< "----\n" ;

    os << "Multiplication:\n";
    os << m6 * m6 << "----\n" << m7 * m8 << "----\n" << m1 * m2 << "----\n" << m1 * m5 << "----\n" << m3 * m4<< "\n=\n" << matrix({70,    80,    90,
                                                                                      158,   184,   210,
                                                                                      246,   288,   330},3)<< "----\n";

    vec v({1,2,3,4});
    os << "Vectormultiplication:\n";
    os << m1 * v << "----\n" << m3 * v << "\n=\n" << vec({30,70,110}) << "----\n";

    os << "Scalarmultiplication:\n";
    os << -1 * m3 << "----\n";

    os << "Row and Col operations:\n";
    os << m1.repl_row(0, vec({2,2,2,2})) << "----\n" << m1.repl_col(3, vec({2,2,2,2})) << "----\n"
       << m1.del(0,0) << "----\n";

    os << "Transpose:\n";
    os << m3.transpose() << "----\n" << m4.transpose() << "----\n" << m6.transpose() << "----\n" << m7.transpose() << "----\n";

    os << "Determinant:\n";
    os << m1.det() << "=1, " << m2.det() << "=0, " << m5.det() << "=61" << m6.det() << "=0\n";

    os << "Inverse:\n";
    os << m1.inverse() << "----\n" << m5.inverse() << "\n =\n" << matrix({-0.655738,  -0.016393,   0.049180,   0.540984,
                                                                          -0.311475,   0.967213,  -0.901639,   0.081967,
                                                                           0.622951,  -0.934426,   0.803279,  -0.163934,
                                                                          -0.262295,   0.393443,  -0.180328,   0.016393},4) << "----\n";

    os << "Rank and kernel:\n";
    os << m1.rank() << "=4, " << m1.kerneldim() << "=0, " << m2.rank() << "=0, " << m2.kerneldim() << "=4, "
       << m3.rank() << "=2, " << m3.kerneldim() << "=2, " << m5.rank() << "=5, " << m5.kerneldim() << "=0\n";

    os << "Eigenvalues:\n";
    os << m1.eigenvalues() << "\n = (1,0)x4 \n" << m5.eigenvalues() << "\n = (16.533, 0),(-2.54, 0.529i),(-2.54, -0.529i),(0.548, 0) \n" ;
}
