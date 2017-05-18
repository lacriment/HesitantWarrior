#ifndef NODE_H
#define NODE_H

#include <QObject>
#include "statespace.h"

class Node : public QObject
{
    Q_OBJECT
private:
    StateSpace *currentState;
    ushort operatorIndex;
public:
    explicit Node(QObject *parent = 0);
    Node(StateSpace *state, int index);

    ushort getOperatorIndex() const;
    void setOperatorIndex(const ushort &value);

    StateSpace *getCurrentState() const;

signals:

public slots:
};

#endif // NODE_H
