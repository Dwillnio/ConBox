#include "window.h"

Window::Window(QLineSeries* data_x, QLineSeries* data_u, QMainWindow *parent)
    : QMainWindow(parent), data_x_(data_x), data_u_(data_u)
{
    this->setFixedSize(1200, 720);
    btn = new QPushButton("QUIT", this);
    btn->setGeometry(810,5,80,30);
    connect(btn, SIGNAL (clicked()), this, SLOT (close()));

    chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(data_x_);
    chart->createDefaultAxes();

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setGeometry(0,0,800,360);
    chartView->setParent(this);

    QChart *chart2 = new QChart();
    chart2->legend()->hide();
    chart2->addSeries(data_u_);
    chart2->createDefaultAxes();

    QChartView *chartView2 = new QChartView(chart2);
    chartView2->setRenderHint(QPainter::Antialiasing);
    chartView2->setGeometry(0,360,800,360);
    chartView2->setParent(this);
}


