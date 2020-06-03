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

void visualizer::visualize_result(const std::vector<time_value>& data_x, const std::vector<nnum>&  x_ind,
                                  const std::vector<time_value>& data_u, const std::vector<nnum>&  u_ind,
                                  const std::vector<time_value>& data_y, const std::vector<nnum>&  y_ind,
                                  const std::vector<time_value>& data_x_est)
{
    QLineSeries series_x, series_u, series_y, series_x_est;

    QApplication a(argc_, argv_);
    a.setWindowIcon(QIcon(":/ressources/icon.ico"));

    visualizer_window w;
    for(nnum i = 0; i < x_ind.size(); i++){
        series.push_back(new QLineSeries);
        series.back()->setName(QString("x_") + QString::number(x_ind[i]));
        convert_data(series.back(), data_x, x_ind[i]);
        w.add_data(series.back(), VW_CHARTS::CHART_X);
    }
    for(nnum i = 0; i < u_ind.size(); i++){
        series.push_back(new QLineSeries);
        series.back()->setName(QString("u_") + QString::number(u_ind[i]));
        convert_data(series.back(), data_u, u_ind[i]);
        w.add_data(series.back(), VW_CHARTS::CHART_U);
    }
    for(nnum i = 0; i < y_ind.size(); i++){
        series.push_back(new QLineSeries);
        series.back()->setName(QString("y_") + QString::number(y_ind[i]));
        convert_data(series.back(), data_y, y_ind[i]);
        w.add_data(series.back(), VW_CHARTS::CHART_Y);
    }
    for(nnum i = 0; i < x_ind.size(); i++){
        series.push_back(new QLineSeries);
        series.back()->setName(QString("x̂_") + QString::number(x_ind[i]));
        convert_data(series.back(), data_x_est, x_ind[i]);
        w.add_data(series.back(), VW_CHARTS::CHART_X_EST);
    }
    w.start();
    w.show();

    a.exec();
}

void visualizer::convert_data(QLineSeries* lseries, const std::vector<time_value>& data, unsigned data_ind)
{
    for(unsigned i = 0; i < data.size(); i++)
        lseries->append(data[i].time_, data[i].value_[data_ind]);
}
