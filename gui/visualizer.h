#ifndef VISUALIZER_H
#define VISUALIZER_H

#include <QLineSeries>
#include <vector>

#include "window.h"
#include "simulator/simulator.h"

class visualizer
{
public:
    visualizer(int argc, char** argv) : argc_(argc), argv_(argv) {}

    void visualize_result(std::vector<time_value>* data_u, unsigned u_ind,
                          std::vector<time_value>* data_x, unsigned y_ind);

private:
    void convert_data(QLineSeries* lseries, const std::vector<time_value>& data, unsigned data_ind);

    int argc_;
    char** argv_;
};

#endif // VISUALIZER_H
