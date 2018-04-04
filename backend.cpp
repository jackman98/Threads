#include "backend.h"

BackEnd::BackEnd(QObject *parent) : QObject(parent)
{
    connect(&logicThread, &QThread::started, &logic, &Logic::run);
//    connect(&drawThread, &QThread::started, &draw, &Draw::run);
    connect(&logic, &Logic::sendCoord, &draw, &Draw::setCoord, Qt::DirectConnection);
    connect(&logic, &Logic::finished, &logicThread, &QThread::terminate);
    logic.moveToThread(&logicThread);
    logicThread.start();
}
