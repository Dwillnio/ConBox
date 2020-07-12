#ifndef COUPLED_SPRING_OSCILLATOR_H
#define COUPLED_SPRING_OSCILLATOR_H

#include "linear_system/linear_system.h"

linear_system coupled_spring_oscillator(rnum m1=2, rnum m2=2,
                                        rnum d1=0.5, rnum d2=0.5,
                                        rnum c1=1, rnum c2=1);

#endif // COUPLED_SPRING_OSCILLATOR_H
