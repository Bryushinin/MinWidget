#ifndef CATCHER_H
#define CATCHER_H
#include <definitions.h>
#include <mywidget.h>

class Catcher: public QObject{
    Q_OBJECT
    //const QMetaObject staticMetaObject;
public:
    Catcher(){}
    virtual ~Catcher(){}
    string Result(OptimizationMethod *OM)
    {
        vector<double> x_0 = OM->x_0, x_n = OM->trajectory.back();
        double f_x_n = OM->answer;
        int num = OM->SC->num;
        string result = "x_0 = (" + std::to_string(x_0[0]) + ", " + std::to_string(x_0[1]) + "); " +
                    "x_n = (" + std::to_string(x_n[0]) + ", " + std::to_string(x_n[1]) + "); f(x_n) = " +
                    std::to_string(f_x_n) + "; number of iterations = " + std::to_string(num);

        return result;
    }
signals:
    void DrawIt(vector<vector<double>> a, Area D, bool rdy, Function* f, string res);
public slots:

    void CatchIt(int func_num, int sc_num, int det_or_stoc, double x_1, double x_2, double y_1, double y_2, double eps, double x0x, double x0y)
    {
        vector<Function*> funcs;

        Function* f_1 = new Function_1;
        funcs.push_back(f_1);

        Function* f_2 = new Function_2;
        funcs.push_back(f_2);

        Function* f_3 = new Function_3;
        funcs.push_back(f_3);

        Function* f = funcs[func_num - 1];
        vector<vector<double>> traj;

        vector<double> lefts, rights, x_0, min_point;
        lefts.clear(); rights.clear();
        lefts.push_back(x_1);lefts.push_back(y_1);
        rights.push_back(x_2);rights.push_back(y_2);
        x_0.push_back(x0x); x_0.push_back(x0y);
        //x_0.push_back((lefts[0] + rights[0]) / 3.);
        //x_0.push_back((lefts[1] + rights[1]) / 2.);
        if (det_or_stoc == 1)
        {
            Newton OM(f, x_0, lefts, rights, sc_num, eps);
            //QObject::connect(&OM, &Newton::DrawIt, &DB, &DrawBoard::Drawing);
            min_point = OM.optimize();
            traj = OM.trajectory;
            emit DrawIt(traj, OM.D, OM.traj_ready, OM.f, Result(&OM));
        }
        else
        {
            rninit(time(0));
            Stochastic OM(f, x_0, lefts, rights, sc_num, eps);
            //QObject::connect(&OM, &OptimizationMethod::DrawIt, &DB, &DrawBoard::Drawing);
            min_point = OM.optimize();
            traj = OM.trajectory;
            emit DrawIt(traj, OM.D, OM.traj_ready, OM.f, Result(&OM));
        }
    }
};
#endif // CATCHER_H
