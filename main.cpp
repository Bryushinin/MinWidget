#include "mywidget.h"
#include "definitions.h"
#include "catcher.h"


int main(int argc, char* argv[])
{

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
