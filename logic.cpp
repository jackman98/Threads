#include "logic.h"

Logic::Logic(QObject *parent) : QObject(parent)
{

}

bool Logic::running() const
{
    return m_running;
}

void Logic::run()
{
    bool isGrow = true;
    while (m_running) {
        emit sendCoord(5, 10);
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
