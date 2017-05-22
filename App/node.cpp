#include "node.h"


StateSpace *Node::getCurrentState() const
{
    return currentState;
}

Node *Node::getParent() const
{
    return parent;
}


Node::Node(QObject *parent) : QObject(parent)
{
    
}

Node::Node(StateSpace *state, Node *node)
{
    this->currentState = state;
    this->parent = node;
}
