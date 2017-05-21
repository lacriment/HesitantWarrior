#ifndef TREENODE_H
#define TREENODE_H

#include <QObject>
#include "statespace.h"

class TreeNode : public QObject
{
    Q_OBJECT
private:
    StateSpace *currentState;
    TreeNode *parent;
public:
    explicit TreeNode(QObject *parent = 0);
    TreeNode(StateSpace *s, TreeNode *p);

    StateSpace *getCurrentState() const;

    TreeNode *getParent() const;

    bool equals(TreeNode *node);

signals:

public slots:
};

#endif // TREENODE_H
