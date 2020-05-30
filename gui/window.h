#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QtCharts/QLineSeries>
#include <QChart>
#include <QChartView>
#include <QPushButton>
#include <QApplication>

using namespace QtCharts;

QT_CHARTS_USE_NAMESPACE

class Window: public QMainWindow
{
Q_OBJECT

public:
    explicit Window(QLineSeries* data_x = new QLineSeries(), QLineSeries* data_u = new QLineSeries(), QMainWindow *parent = nullptr);

    ~Window()
    {
        delete btn;
        delete chart;
    }

private:
    QPushButton* btn;
    QLineSeries* data_x_;
    QLineSeries* data_u_;
    QChart* chart;
};

#endif // WINDOW_H
