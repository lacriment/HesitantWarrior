#ifndef OPERATOR_H
#define OPERATOR_H

#include <QObject>
#include <QList>
#include <QPair>

#include "statespace.h"

class Operator : public QObject
{
    Q_OBJECT
private:
    Direction dir;
    QPair<short, short> dirCartesian;

public:
    explicit Operator(QObject *parent = 0);
    Operator(Direction dir);
    void *apply(StateSpace *currentState);
    bool precondition(StateSpace *currentState);


signals:

public slots:
};

#endif // OPERATOR_H
