#include "logic.h"
#include <QDebug>
#include <QThread>
#include <QQmlEngine>
#include <QQmlComponent>

Logic::Logic(QObject *parent) : QObject(parent)
{
    setRunning(true);
}

bool Logic::running() const
{
    return m_running;
}

int Logic::x() const
{
    return m_x;
}

int Logic::y() const
{
    return m_y;
}

void Logic::run()
{
    qDebug() << m_x << m_y;
    bool isGrow = true;
    while (m_running) {
        if (isGrow) {
            m_y += 10;
            if (m_y >= m_heightWindow - 100) {
                isGrow = false;
            }
        }
        else {
            m_y -= 10;
            if (m_y <= 30) {
                isGrow = true;
            }
        }
        emit sendCoord(m_x, m_y);
        QThread::msleep(20);
    }
    emit finished();
}

void Logic::setRunning(bool running)
{
    if (m_running == running)
        return;

    m_running = running;
    emit runningChanged(m_running);
}

void Logic::setX(int x)
{
    qDebug() << "Logic X:" << x;
    if (m_x == x)
        return;

    m_x = x;
    emit xChanged(m_x);
}

void Logic::setY(int y)
{
    qDebug() << "Logic Y:" << y;
    if (m_y == y)
        return;

    m_y = y;
    emit yChanged(m_y);
}

void Logic::setHeightWindow(int heightWindow)
{
    m_heightWindow = heightWindow;
}
