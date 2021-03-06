cmake_minimum_required(VERSION 3.5)

project(ConBox LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Widgets Charts REQUIRED)

add_executable(ConBox
    main.cpp

    base/function.cpp
    base/vec.cpp
    base/func_dgl.cpp
    base/definitions.cpp
    base/matrix.cpp
    base/computable.h
    base/cnum.cpp
    base/polynom.cpp
    base/function_data.cpp
    base/function_d.cpp
    base/func_d_dgl.cpp
    base/function_d_data.cpp
    base/transfer_function.cpp

    gui/window.cpp
    gui/visualizer.cpp
    gui/visualizer_window.cpp

    numeric/differentiator.cpp
    numeric/integrator.cpp

    dgl_numeric/dgl_solver.cpp
    dgl_numeric/dgl_euler.cpp
    dgl_numeric/dgl_rungekutta.cpp
    dgl_numeric/difference_eq_solver.cpp

    controller/dimensions.h
    controller/controller.cpp
    controller/pid_controller.cpp
    controller/state_controller.cpp
    controller/state_integral_controller.cpp
    controller/multi_controller.cpp
    controller/prefilter.cpp
    controller/stationary_filter.cpp

    observer/observer.cpp
    observer/luenberger_observer.cpp
    observer/kalman_filter.cpp
    observer/kalman_filter_ext.cpp
    observer/kalman_filter_unsc.cpp

    simulator/simulator.cpp
    simulator/simulator_2dof.cpp
    simulator/simulator_obs.cpp
    simulator/simulator_prefilter.cpp

    disturbance/disturbance.cpp
    disturbance/disturbance_const.cpp
    disturbance/disturbance_white.cpp

    linear_system/linear_system.cpp
    linear_system/linear_system_d.cpp

    identification/det_least_squares.cpp
    identification/stoch_least_squares.cpp

    test/test.h
    test/test_matrix.cpp
    test/test_cnum.cpp
    test/test_numeric.cpp
    test/test_dgl_solver.cpp
    test/test_disturbance.cpp
    test/test_gui.cpp
    test/test_linear_system.cpp
    test/test_observer.cpp
    test/test_controller.cpp
    test/test_simulator.cpp
    test/test_kalman_filter.cpp
    test/test_linear_system_d.cpp
    test/test_det_least_squares.cpp

    example/harm_osc.cpp
    example/pendel_wagen_lin.cpp
    example/inverted_pend_lin.cpp
    example/coupled_spring_oscillator.cpp
)

target_link_libraries(ConBox Qt5::Widgets Qt5::Charts)

include_directories(ConBox Public
    .
    /usr/include/eigen3
)

