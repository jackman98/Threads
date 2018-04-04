#ifndef LOGIC_H
#define LOGIC_H

#include <QObject>

class Logic : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool running READ running WRITE setRunning NOTIFY runningChanged)

    bool m_running;

public:
    explicit Logic(QObject *parent = nullptr);

    bool running() const;

signals:
    void sendCoord(int x, int y);
    void finished();
    void runningChanged(bool running);

public slots:
    void run();
    void setRunning(bool running);
};

#endif // LOGIC_H
