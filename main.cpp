#include "mywidget.h"
#include "definitions.h"
#include "catcher.h"


int main(int argc, char* argv[])
{
//    cout << "Enter the number of the function:\n"
//        << "1. f(x, y) = sin(x)*cos(y)\n"
//        << "2. f(x, y) = 20*exp(sin((x+y)/20))+x*y\n"
//        << "3. f(x, y) = (1-x)^2 + 100(y-x^2)^2\n";
//    int func_num = 0;
//    while((func_num < 1) || (func_num > 3))
//        cin >> func_num;
//    cout << "Choose the stop criterion:\n"
//        << "1. The norm of the function's gradient is less than eps.\n"
//        << "2. The distance between points representing adjacent iterations is less than eps.\n"
//        << "3. The quotient of values of the function at points\nrepresenting adjacent iterations is less than eps.\n";
//    int sc_num = 0;
//    while ((sc_num < 1) || (sc_num > 3))
//        cin >> sc_num;
//    cout << "Choose the optimization method:\n"
//        << "1. Determined Newton's method with derivatives and Hessian derived manually.\n"
//        << "2. Stochastic search.\n";
//    int det_or_stoc = -1;
//    while ((det_or_stoc < 1) || (det_or_stoc > 2))
//        cin >> det_or_stoc;
//    cout << "Enter the eps\n";
//    double eps;
//    cin >> eps;
//    std::cout << "  Enter left and right borders (x_1, y_1), (x_2, y_2) in format \"x_1 y_1 x_2 y_2\"\n";
//    vector<double> lefts, rights, x_0;
//    double a;
//    std::cin >> a; lefts.push_back(a); std::cin >> a; lefts.push_back(a);
//    std::cin >> a; rights.push_back(a); std::cin >> a; rights.push_back(a);
//    x_0.push_back((lefts[0] + rights[0]) / 3.);
//    x_0.push_back((lefts[1] + rights[1]) / 2.);
//    std::cout << "  Starting point (" << x_0[0] << ", " << x_0[1] << ")\n";

//    vector<Function*> funcs;

//    Function* f_1 = new Function_1;
//    funcs.push_back(f_1);

//    Function* f_2 = new Function_2;
//    funcs.push_back(f_2);

//    Function* f_3 = new Function_3;
//    funcs.push_back(f_3);

//    Function* f = funcs[func_num - 1];
//    vector<double> ans;
//    if (det_or_stoc == 1)
//    {
//        Newton OM(f, x_0, lefts, rights, sc_num, eps);
//        ans = OM.optimize();
//        std::cout << "  Result of optimization: " << OM.answer << endl;
//    }
//    else
//    {
//        rninit(time(0));
//        Stochastic OM(f, x_0, lefts, rights, sc_num, eps);
//        ans = OM.optimize();
//        std::cout << "  Result of optimization: " << OM.answer << endl;
//    }
//    std::cout << "  At point: " << endl;
//    for (size_t i = 0; i < ans.size(); ++i)
//        std::cout << " " << ans[i];
//    std::cout << endl << endl;

    QApplication app(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "MinWidget_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            app.installTranslator(&translator);
            break;
        }
    }
    MyWidget w; Catcher Catching;
    QObject::connect(&w, &MyWidget::OptimizingTime, &Catching, &Catcher::CatchIt);
    QObject::connect(&Catching, &Catcher::DrawIt, &w, &MyWidget::Drawing);
    w.show();
    return app.exec();
}
