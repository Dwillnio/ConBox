#ifndef TEST_KALMAN_FILTER_H
#define TEST_KALMAN_FILTER_H

#include <iostream>

#include "observer/kalman_filter.h"
#include "disturbance/disturbance_white.h"
#include "simulator/simulator.h"
#include "gui/visualizer.h"

void kalman_filter_test_1(std::ostream& os = std::cout);


#endif // TEST_KALMAN_FILTER_H
