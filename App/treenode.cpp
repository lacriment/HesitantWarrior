#include "treenode.h"

StateSpace *TreeNode::getCurrentState() const
{
    return currentState;
}

TreeNode *TreeNode::getParent() const
{
    return parent;
}

bool TreeNode::equals(TreeNode *node)
{
    return this->parent->currentState->equals(node->parent->currentState)
            && this->currentState->equals(node->currentState);
}

TreeNode::TreeNode(QObject *parent) : QObject(parent)
{

}

TreeNode::TreeNode(StateSpace *s, TreeNode *p)
{
    this->currentState = s;
    this->parent = p;
}
