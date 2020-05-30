cmake_minimum_required(VERSION 3.5)

project(DGLSim LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Widgets Charts REQUIRED)

add_executable(DGLSim
    main.cpp

    base/function.cpp
    base/vec.cpp
    base/func_dgl.cpp
    base/definitions.cpp
    base/matrix.cpp
    base/computable.h
    base/cnum.cpp

    gui/window.cpp
    gui/visualizer.cpp

    numeric/differentiator.cpp
    numeric/integrator.cpp

    dgl_numeric/dgl_solver.cpp
    dgl_numeric/dgl_euler.cpp
    dgl_numeric/dgl_rungekutta.cpp

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

    simulator/simulator.cpp
    simulator/simulator_2dof.cpp
    simulator/simulator_obs.cpp

    disturbance/disturbance.cpp
    disturbance/disturbance_const.cpp
    disturbance/disturbance_white.cpp

    linear_system/linear_system.cpp
)

include_directories(DGLSim Public .)

target_link_libraries(DGLSim Qt5::Widgets Qt5::Charts)
