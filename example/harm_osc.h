#ifndef HARM_OSC_H
#define HARM_OSC_H

#include "linear_system/linear_system.h"

linear_system harm_osc(rnum alpha = 1, rnum beta = 0.2, rnum gamma = 0.1);

void harm_osc_test(std::ostream& os = std::cout);

#endif // PENDEL_WAGEN_LIN_H

