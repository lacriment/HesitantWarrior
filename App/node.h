#ifndef NODE_H
#define NODE_H

#include <QObject>
#include "statespace.h"

class Node : public QObject
{
    Q_OBJECT
private:
    StateSpace *currentState;
    Node *parent;
public:
    explicit Node(QObject *parent = 0);
    Node(StateSpace *state, Node *node);
    StateSpace *getCurrentState() const;
    Node *getParent() const;

signals:

public slots:
};

#endif // NODE_H
