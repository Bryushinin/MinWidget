#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QMainWindow>
#include <QPainter>
#include <iostream>
#include "Eigen/QR"
#include <vector>
#include <cmath>
#include "R64M.hpp"
#include "definitions.h"

using namespace std;




QT_BEGIN_NAMESPACE
namespace Ui { class MyWidget; }
QT_END_NAMESPACE

class MyWidget : public QMainWindow
{
    Q_OBJECT
    void DrawTrajectory();
    void DrawAxis();
    void DrawArea();
    void paintEvent(QPaintEvent *);

public:
    int func_num_;
    int sc_num_;
    int det_or_stoc_;
    double x_1_,x_2_,y_1_,y_2_, eps_;
    vector<vector<double>> trajectory;
    Area D;
    Function* f;
    bool ReadySir;
    MyWidget(QWidget *parent = nullptr);
    ~MyWidget();
private slots:
    void on_OKbutton_clicked();
public slots:
    void Drawing(vector<vector<double>> a, Area D, bool rdy, Function* f, string res);
private:
    Ui::MyWidget *ui;
signals:
    void OptimizingTime(int func_num__, int sc_num__, int det_or_stoc__, double x_1__, double x_2__, double y_1__, double y_2__, double eps__);
};


#endif // MYWIDGET_H
