#ifndef TEST_OBSERVER_H
#define TEST_OBSERVER_H

#include <iostream>

#include "observer/luenberger_observer.h"
#include "example/harm_osc.h"
#include "controller/state_controller.h"
#include "simulator/simulator_prefilter.h"
#include "simulator/simulator_obs.h"
#include "gui/visualizer.h"
#include "controller/stationary_filter.h"

void luenberger_observer_test_1(int argc, char** argv, std::ostream& os = std::cout);

#endif // TEST_OBSERVER_H
