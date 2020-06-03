#include "test_cnum.h"


void cnum_test_1(std::ostream& os)
{
    cnum zero, two = 2, deg45 = {1,1}, img(std::vector<rnum>{0,1}), arb(4,3);
    os << "Numbers:\n";
    os << zero << " " << two << " " << deg45 << " " << img << " " << arb << std::endl;
    os << arb.real << " = 4 | " << arb.imag << " = 3\n";

    os << "\nAddition:\n";
    os << zero + two << " = 2\n";
    os << deg45 + arb << " = 5+i4\n";
    os << deg45 - arb << " = -3-i2\n";

    os << "\nMultiplikation:\n";
    os << zero * deg45 << " = 0\n";
    os << two * img << " = i2\n";
    os << deg45 * arb << " = 1+i7\n";

    os << "\nDivision:\n";
    os << zero / deg45 << " = 0\n";
    os << two / img << " = -i2\n";
    os << deg45 / arb << " = 0.28+i0.04\n";
}
