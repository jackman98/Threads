#include "data.h"
#include <QDebug>
#include <QTextStream>

Data::Data(QObject *parent) : QObject(parent)
{
//    connect(this, &Data::xChanged, &logic, &Logic::setX, Qt::DirectConnection);
//    connect(this, &Data::yChanged, &logic, &Logic::setY, Qt::DirectConnection);
    connect(this, &Data::heightWindowChanged, &logic, &Logic::setHeightWindow, Qt::DirectConnection);
    connect(&draw, &Draw::coordXChanged, this, &Data::setX);
    connect(&draw, &Draw::coordYChanged, this, &Data::setY);
    connect(&logicThread, &QThread::started, &logic, &Logic::run);
    connect(&drawThread, &QThread::started, &draw, &Draw::run);
    connect(&logic, &Logic::sendCoord, &draw, &Draw::setCoord, Qt::DirectConnection);
    connect(&logic, &Logic::finished, &logicThread, &QThread::quit);
    connect(&draw, &Draw::finished, &drawThread, &QThread::quit);
    connect(this, &Data::destroyed, this, &Data::save);
   saveFile.setFileName("save.txt");
    if (saveFile.exists()) {
        saveFile.open(QIODevice::ReadOnly);
        QString str = saveFile.readAll();
        QStringList listStr = str.split(" ");
        logic.setX(listStr[0].toInt());
        logic.setY(listStr[1].toInt());
        draw.setCoordX(listStr[0].toInt());
        draw.setCoordY(listStr[1].toInt());
        saveFile.close();
    }
    else {
        logic.setX(0);
        logic.setY(0);
        qDebug() << "Not exists";
    }
}

int Data::x() const
{
    return m_x;
}

int Data::y() const
{
    return m_y;
}

void Data::setX(int x)
{
//    qDebug() << "Data X" << x;
    if (m_x == x)
        return;

    m_x = x;
    emit xChanged(m_x);
}

void Data::setY(int y)
{
//    qDebug() << "Data Y" << y;
    if (m_y == y)
        return;

    m_y = y;
    emit yChanged(m_y);
}

void Data::stopThreads()
{
    logic.setRunning(false);
    draw.setRunning(false);
    saveFile.open(QIODevice::WriteOnly);
    QTextStream out(&saveFile);
    out << QString::number(x()) << " " << QString::number(y());
    saveFile.close();
}

void Data::startThreads()
{
    logic.setRunning(true);
    draw.setRunning(true);
    logic.setX(x());
    logic.setY(y());
    logic.moveToThread(&logicThread);
    draw.moveToThread(&drawThread);
    logicThread.start();
    drawThread.start();
}

void Data::resetCoord()
{
    logic.setX(0);
    logic.setY(0);
    draw.setCoordX(0);
    draw.setCoordY(0);
}

void Data::save()
{

}

void Data::setHeightWindow(int heightWindow)
{
    emit heightWindowChanged(heightWindow);
}
