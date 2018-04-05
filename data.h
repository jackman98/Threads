#ifndef DATA_H
#define DATA_H

#include <QObject>
#include "logic.h"
#include "draw.h"
#include <QThread>
#include <QFile>

class Data : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int x READ x WRITE setX NOTIFY xChanged)
    Q_PROPERTY(int y READ y WRITE setY NOTIFY yChanged)

    int m_x;
    int m_y;
    Logic logic;
    Draw draw;
    QThread logicThread;
    QThread drawThread;
    QFile saveFile;

public:
    explicit Data(QObject *parent = nullptr);

    int x() const;
    int y() const;

signals:

    void xChanged(int x);
    void yChanged(int y);
    void signalToThreads(bool run);
    void heightWindowChanged(int heightWindow);

public slots:
    void setX(int x);
    void setY(int y);
    void stopThreads();
    void startThreads();
    void resetCoord();
    void save();
    void setHeightWindow(int heightWindow);
};

#endif // DATA_H
