#include "visualizer.h"


void visualizer::visualize_result(std::vector<time_value>* data_u, unsigned u_ind,
                                  std::vector<time_value>* data_x, unsigned y_ind)
{
    QLineSeries series_u, series_x;
    convert_data(&series_u, *data_u, u_ind);
    convert_data(&series_x, *data_x, y_ind);

    QApplication a(argc_, argv_);

    Window w(&series_x, &series_u);
    w.show();

    a.exec();
}


void visualizer::convert_data(QLineSeries* lseries, const std::vector<time_value>& data, unsigned data_ind)
{
    for(unsigned i = 0; i < data.size(); i++)
        lseries->append(data[i].time_, data[i].value_[data_ind]);
}
