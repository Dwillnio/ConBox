#ifndef VISUALIZER_H
#define VISUALIZER_H

#include <QLineSeries>
#include <vector>

#include "window.h"
#include "visualizer_window.h"
#include "simulator/simulator.h"

class visualizer
{
public:
    visualizer(int argc, char** argv) : argc_(argc), argv_(argv) {}

    void visualize_result(std::vector<time_value>* data_u, unsigned u_ind,
                          std::vector<time_value>* data_x, unsigned y_ind);

    void visualize_result(const std::vector<time_value>& data_x, const std::vector<nnum>&  x_ind,
                          const std::vector<time_value>&  data_u, const std::vector<nnum>&  u_ind,
                          const std::vector<time_value>&  data_y, const std::vector<nnum>&  y_ind,
                          const std::vector<time_value>&  data_x_est = std::vector<time_value>());

    ~visualizer() {
        for(nnum i = 0; i < series.size(); i++){
            delete series[i];
        }
    }

private:
    void convert_data(QLineSeries* lseries, const std::vector<time_value>& data, unsigned data_ind);
    std::vector<QLineSeries*> series;

    int argc_;
    char** argv_;
};

#endif // VISUALIZER_H
