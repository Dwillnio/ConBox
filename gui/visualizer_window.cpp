#include "visualizer_window.h"

visualizer_window::visualizer_window(QWidget *parent)
    : QWidget(parent)
{
    this->setFixedSize(1600, 720);
    this->setWindowTitle("Control box");
    this->setWindowIcon(QIcon("./ressources/icon.png"));

    chart_x = new QChart();
    chart_x->setTitle("State variables: x");
    chart_x->setMargins(QMargins(5,5,5,5));

    chart_u = new QChart();
    chart_u->setTitle("Input variables: u");
    chart_u->setMargins(QMargins(5,5,5,5));

    chart_y = new QChart();
    chart_y->setTitle("Output variables: y");
    chart_y->setMargins(QMargins(5,5,5,5));

    chart_x_est = new QChart();
    chart_x_est->setTitle("Estimated state variables: x̂");
    chart_x_est->setMargins(QMargins(5,5,5,5));
}

void visualizer_window::start()
{
    chart_x->createDefaultAxes();
    chartview_x = new QChartView(chart_x);
    chartview_x->setRenderHint(QPainter::Antialiasing);
    chartview_x->setGeometry(0,0,800,360);
    chartview_x->setParent(this);
    chart_x->legend()->detachFromChart();
    chart_x->legend()->setGeometry(50,5,400,100);
    reinterpret_cast<QValueAxis*>(chart_x->axes(Qt::Vertical)[0])->applyNiceNumbers();

    chart_u->createDefaultAxes();
    chartview_u = new QChartView(chart_u);
    chartview_u->setRenderHint(QPainter::Antialiasing);
    chartview_u->setGeometry(0,360,800,360);
    chartview_u->setParent(this);
    chart_u->legend()->detachFromChart();
    chart_u->legend()->setGeometry(50,5,400,100);
    reinterpret_cast<QValueAxis*>(chart_u->axes(Qt::Vertical)[0])->applyNiceNumbers();

    chart_x_est->createDefaultAxes();
    chartview_x_est = new QChartView(chart_x_est);
    chartview_x_est->setRenderHint(QPainter::Antialiasing);
    chartview_x_est->setGeometry(800,0,800,360);
    chartview_x_est->setParent(this);
    chart_x_est->legend()->detachFromChart();
    chart_x_est->legend()->setGeometry(50,5,400,100);
    reinterpret_cast<QValueAxis*>(chart_x_est->axes(Qt::Vertical)[0])->applyNiceNumbers();

    chart_y->createDefaultAxes();
    chartview_y = new QChartView(chart_y);
    chartview_y->setRenderHint(QPainter::Antialiasing);
    chartview_y->setGeometry(800,360,800,360);
    chartview_y->setParent(this);
    chart_y->legend()->detachFromChart();
    chart_y->legend()->setGeometry(50,5,400,100);
    reinterpret_cast<QValueAxis*>(chart_y->axes(Qt::Vertical)[0])->applyNiceNumbers();
}

void visualizer_window::add_data(QLineSeries* data, VW_CHARTS c)
{
    switch(c) {
    case CHART_X:
        chart_x->addSeries(data);
        break;
    case CHART_U:
        chart_u->addSeries(data);
        break;
    case CHART_Y:
        chart_y->addSeries(data);
        break;
    case CHART_X_EST:
        chart_x_est->addSeries(data);
        break;
    }
}
