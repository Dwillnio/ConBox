#ifndef VISUALIZER_WINDOW_H
#define VISUALIZER_WINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QtCharts/QLineSeries>
#include <QChart>
#include <QChartView>
#include <QPushButton>
#include <QApplication>
#include <QValueAxis>

using namespace QtCharts;

typedef enum {CHART_X, CHART_U, CHART_Y, CHART_X_EST} VW_CHARTS;

QT_CHARTS_USE_NAMESPACE

class visualizer_window: public QWidget
{
Q_OBJECT

public:
    explicit visualizer_window(QWidget *parent = nullptr);

    void add_data(QLineSeries* data, VW_CHARTS c);
    void start();

private:
    QChart* chart_x,* chart_u,* chart_y,* chart_x_est;
    QChartView* chartview_x,* chartview_u,* chartview_y,* chartview_x_est;
};

#endif // VISUALIZER_WINDOW_H
