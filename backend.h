#ifndef BACKEND_H
#define BACKEND_H

#include "draw.h"
#include "logic.h"
#include <QObject>
#include <QThread>

class BackEnd : public QObject
{
    Q_OBJECT

    Logic logic;
    Draw draw;
    QThread logicThread;
    QThread drawThread;
public:
    explicit BackEnd(QObject *parent = nullptr);

signals:

public slots:
};

#endif // BACKEND_H
