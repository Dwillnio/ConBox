#ifndef INVERTED_PEND_LIN_H
#define INVERTED_PEND_LIN_H

#include <ostream>
#include "linear_system/linear_system.h"

linear_system inv_pend_lin(bool output_angle = true, rnum m = 1, rnum M = 5, rnum I = 1, rnum l = 1, rnum b = 0.2);

void inv_pend_lin_test(std::ostream& os = std::cout);

#endif // INVERTED_PEND_LIN_H
