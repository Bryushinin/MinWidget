#include "mywidget.h"
#include "ui_mywidget.h"

MyWidget::MyWidget(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MyWidget), D({{0, 0},{1, 1}})
{
    ui->setupUi(this);
    ui->func_rad_1->setChecked(true);
    ui->SC_button_1->setChecked(true);
    ui->stoc_rad_button->setChecked(true);
    ui->edit_x_1->setText(QString("0"));
    ui->edit_x_2->setText(QString("20"));
    ui->edit_y_1->setText(QString("0"));
    ui->edit_y_2->setText(QString("10"));
    ui->eps_edit->setText(QString("0.001"));
    x_0_x = 20./3;
    x_0_y = 10./2;
    f = new Function_0;
    ReadySir = false;
    sverhu = false;
    setMouseTracking(true);
}

MyWidget::~MyWidget()
{
    delete ui;
}


void MyWidget::on_OKbutton_clicked()
{
    if(ui->func_rad_1->isChecked())
        func_num_ = 1;
    else if(ui->func_rad_2->isChecked())
        func_num_ = 2;
    else if(ui->func_rad_3->isChecked())
        func_num_ = 3;

    if(ui->SC_button_1->isChecked())
        sc_num_ = 1;
    else if(ui->SC_button_2->isChecked())
        sc_num_ = 2;
    else if(ui->SC_button_3->isChecked())
        sc_num_ = 3;

    if(ui->det_rad_button->isChecked())
        det_or_stoc_ = 1;
    else det_or_stoc_ = 2;

    x_1_ = (ui->edit_x_1->text()).toDouble();
    x_2_ = (ui->edit_x_2->text()).toDouble();
    y_1_ = (ui->edit_y_1->text()).toDouble();
    y_2_ = (ui->edit_y_2->text()).toDouble();
    eps_ = (ui->eps_edit->text()).toDouble();
    if(!sverhu)
    {
        x_0_x = (x_2_ - x_1_)/3.;
        x_0_y = (y_2_ - y_1_)/2.;
    }
    else
        sverhu = false;
    emit OptimizingTime(func_num_, sc_num_, det_or_stoc_, x_1_, x_2_, y_1_, y_2_, eps_, x_0_x, x_0_y);
}

void MyWidget::mousePressEvent(QMouseEvent *event){
    double x1 = D.left_borders[0];
    double x2 = D.right_borders[0];
    double y1 = D.left_borders[1];
    double y2 = D.right_borders[1];

    double xx = event->pos().x(), yy = event->pos().y();

    double x = (xx - 100) / 900 * (x2 - x1) + x1, y = (450 - yy + 70) / 450 * (y2 - y1) + y1;

    if(x1 < x && x < x2 && y1 < y && y < y2) {
        x_0_x = x;
        x_0_y = y;
        sverhu = true;
        on_OKbutton_clicked();
    }
}


void MyWidget::DrawTrajectory()
{
    QPainter painter;
    painter.begin(this);
    double x1 = D.left_borders[0];
    double x2 = D.right_borders[0];
    double y1 = D.left_borders[1];
    double y2 = D.right_borders[1];
    size_t length = trajectory.size();
    painter.setPen(QPen(Qt::blue, 2));
    for(size_t i = 0; i < length - 1; ++i)
    {
        painter.drawLine(100 + (trajectory[i][0] - x1) / (x2 - x1) * 900, cure(100 + (trajectory[i][1]-y1) / (y2 - y1) * 450),
                100 + (trajectory[i + 1][0]-x1) / (x2 - x1) * 900, cure(100 + (trajectory[i + 1][1]-y1) / (y2 - y1) * 450));
    }
    painter.setPen(QPen(Qt::red, 4));
    painter.drawPoint(100 + (trajectory[0][0]-x1) / (x2 - x1) * 900,
                          cure(100 + (trajectory[0][1]-y1) / (y2 - y1) * 450));
    painter.setPen(QPen(Qt::green, 4));
    painter.drawPoint(100 + (trajectory.back()[0]-x1) / (x2 - x1) * 900,
                      cure(100 + (trajectory.back()[1]-y1) / (y2 - y1) * 450));
}

void MyWidget::DrawAxis()
{
    QPainter painter;
    painter.begin(this);

    painter.setBrush(QBrush(QColor::fromHsl(0, 0, 255)));
    painter.setPen(QPen(QColor::fromHsl(0, 0, 0)));
    painter.drawRect(15, 40, 1010, 560);

    painter.drawLine(100, cure(50 + 10), 1020, cure(50 + 10));
    painter.drawLine(25 + 25, cure(100), 25 + 25, cure(570));
    painter.drawLine(1015, cure(55 + 10), 1020, cure(50 + 10));
    painter.drawLine(1015, cure(45 + 10), 1020, cure(50 + 10));
    painter.drawLine(20 + 25, cure(565), 25 + 25, cure(570));
    painter.drawLine(30 + 25, cure(565), 25 + 25, cure(570));
    painter.drawText(1015, cure(70 - 25), "x");
    painter.drawText(35 + 25, cure(572), "y");
    double x1 = D.left_borders[0];
    double x2 = D.right_borders[0];
    double y1 = D.left_borders[1];
    double y2 = D.right_borders[1];
    for(int i = 0; i <= 10; ++i)
    {
        double x = 100 + 900 / 10 * i,
            y = (100 + 450 / 10 * i);
        double xText = (double) i / 10 * (x2 - x1) + x1,
            yText = (double) i / 10 * (y2 - y1) + y1;

        painter.drawLine(x, cure(53 + 10), x, cure(47 + 10));
        painter.drawText(x - 5, cure(70-25), QString::number(xText, 'g', 2));
        painter.drawLine(22 + 25, cure(y), 28 + 25, cure(y));
        painter.drawText(35 - 4, cure(y + 3), QString::number(yText, 'g', 2));
    }
}

void MyWidget::DrawArea()
{
    QPainter painter;
    painter.begin(this);
    double x1 = D.left_borders[0];
    double x2 = D.right_borders[0];
    double y1 = D.left_borders[1];
    double y2 = D.right_borders[1];

    int numberOfBoxes_y = 150, numberOfBoxes_x = 300;
    double hx = double(x2-x1)/numberOfBoxes_x, hy = double(y2-y1)/numberOfBoxes_y;
    double max_ = f->eval({x1 + hx/2., y1 + hy/2.}), min_ = max_;
    std::vector<std::vector<double>> m(numberOfBoxes_y);
    for(int i = 0; i < numberOfBoxes_y; ++i)
    {
        m[i].resize(numberOfBoxes_x);
        for(int j = 0; j < numberOfBoxes_x; ++j)
        {
            std::vector<double> curr = {x1 + hx*(j+0.5), y1 + hy*(i+0.5)};
            m[i][j] = (f->eval(curr));
            if(m[i][j]< min_)
                min_ = m[i][j];
            if(m[i][j] > max_)
                max_ = m[i][j];
        }
    }
    int h = 10, s = 120;
    for(int i = 0; i < numberOfBoxes_y; ++i)
    {
        for(int j = 0; j < numberOfBoxes_x; ++j)
        {
            int l = 15+240*double((m[i][j] - min_) / (max_ - min_));
            painter.setBrush(QBrush(QColor::fromHsl(h, s, l)));
            painter.setPen(QPen(QColor::fromHsl(h, s, l)));
            painter.drawRect(100 + j * 3, cure(100 + i * 3 + 3), 3, 3);
        }
    }
}

void MyWidget::paintEvent(QPaintEvent *) {
    DrawAxis();
    if(ReadySir)
    {
        DrawArea();
        DrawTrajectory();
    }


}

void MyWidget::Drawing(vector<vector<double>> a, Area D_, bool rdy, Function* f_, string res)
{
    //////////////////
    trajectory = a;
    D = D_;
    f = f_;
    ReadySir = rdy;
    repaint();
    ui->label->setText(QString::fromStdString(res));
}
