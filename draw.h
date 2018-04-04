#ifndef DRAW_H
#define DRAW_H

#include <QObject>

class Draw : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int coordX READ coordX WRITE setCoordX NOTIFY coordXChanged)
    Q_PROPERTY(int coordY READ coordY WRITE setCoordY NOTIFY coordYChanged)
    Q_PROPERTY(bool running READ running WRITE setRunning NOTIFY runningChanged)

    int m_coordY;
    int m_coordX;
    int tempCoordX;
    int tempCoordY;
    bool m_running;

public:
    explicit Draw(QObject *parent = nullptr);

    int coordY() const;
    int coordX() const;
    bool running() const;

signals:
    void coordYChanged(int coordY);
    void coordXChanged(int coordX);
    void runningChanged(bool running);
    void finished();

public slots:
    void setCoord(int x, int y);
    void setCoordY(int coordY);
    void setCoordX(int coordX);
    void run();
    void setRunning(bool running);
};

#endif // DRAW_H
