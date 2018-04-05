#ifndef LOGIC_H
#define LOGIC_H

#include <QObject>

class Logic : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool running READ running WRITE setRunning NOTIFY runningChanged)
    Q_PROPERTY(int x READ x WRITE setX NOTIFY xChanged)
    Q_PROPERTY(int y READ y WRITE setY NOTIFY yChanged)

    bool m_running;

    int m_x;
    int m_y;
    int m_heightWindow;

public:
    explicit Logic(QObject *parent = nullptr);

    bool running() const;

    int x() const;
    int y() const;

signals:
    void sendCoord(int x, int y);
    void finished();
    void runningChanged(bool running);

    void xChanged(int x);
    void yChanged(int y);

public slots:
    void run();
    void setRunning(bool running);
    void setX(int x);
    void setY(int y);
    void setHeightWindow(int heightWindow);
};

#endif // LOGIC_H
