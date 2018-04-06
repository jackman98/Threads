#include <QGuiApplication>
#include <QQmlContext>
#include <QQmlApplicationEngine>
#include <QObject>
//#include <QThread>
//#include "logic.h"
//#include "draw.h"
#include "data.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    Data data;
//    QObject::connect(, &QCoreApplication::destroyed, &data, &Data::stopThreads);
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("myData", &data);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;


    return app.exec();
}
