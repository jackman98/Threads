#include <QGuiApplication>
#include <QQmlContext>
#include <QQmlApplicationEngine>
#include <QObject>
#include "backend.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

//    BackEnd b;
    Logic logic;
    Draw draw;
    QThread logicThread;
    QThread drawThread;
    logic.setRunning(true);
    draw.setRunning(true);
    QObject::connect(&logicThread, &QThread::started, &logic, &Logic::run);
    QObject::connect(&drawThread, &QThread::started, &draw, &Draw::run);
    QObject::connect(&logic, &Logic::sendCoord, &draw, &Draw::setCoord, Qt::DirectConnection);
    QObject::connect(&logic, &Logic::finished, &logicThread, &QThread::terminate);
    logic.moveToThread(&logicThread);
    logicThread.start();

    QQmlApplicationEngine engine;
    qmlContext(engine.rootContext())->setContextProperty("draw", &draw);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;


    return app.exec();
}
