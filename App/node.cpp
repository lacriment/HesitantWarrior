#include "node.h"


ushort Node::getOperatorIndex() const
{
    return operatorIndex;
}

void Node::setOperatorIndex(const ushort &value)
{
    operatorIndex = value;
}

StateSpace *Node::getCurrentState() const
{
    return currentState;
}

bool Node::equals(Node *node)
{
    return node->currentState->equals(this->currentState) &&
            node->getOperatorIndex() == this->operatorIndex;
}

Node::Node(QObject *parent) : QObject(parent)
{

}

Node::Node(StateSpace *state, int index)
{
    this->currentState = state;
    this->operatorIndex = index;
}
