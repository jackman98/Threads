#include "draw.h"
#include <QDebug>

Draw::Draw(QObject *parent) : QObject(parent)
{

}



void Draw::setCoord(int x, int y)
{
    tempCoordX = x;
    tempCoordX = y;
    qDebug() << x << y;
}

int Draw::coordY() const
{
    return m_coordY;
}

int Draw::coordX() const
{
    return m_coordX;
}

bool Draw::running() const
{
    return m_running;
}

void Draw::setCoordY(int coordY)
{
    if (m_coordY == coordY)
        return;

    m_coordY = coordY;
    emit coordYChanged(m_coordY);
}

void Draw::setCoordX(int coordX)
{
    if (m_coordX == coordX)
        return;

    m_coordX = coordX;
    emit coordXChanged(m_coordX);
}

void Draw::run()
{
    int i = 0;
    while (i < 5) {
        setCoordX(tempCoordX);
        setCoordY(tempCoordY);
        qDebug() << i;
    }
    emit finished();

}

void Draw::setRunning(bool running)
{
    if (m_running == running)
        return;

    m_running = running;
    emit runningChanged(m_running);
}
