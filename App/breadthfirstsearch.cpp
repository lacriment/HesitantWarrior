#include "breadthfirstsearch.h"

BreadthFirstSearch::BreadthFirstSearch()
{

}

QList<StateSpace *> *BreadthFirstSearch::search(StateSpace *startState)
{
    TreeNode *startNode = new TreeNode(startState, nullptr);
    QList<TreeNode*> *closedNodes = new QList<TreeNode*>();
    QQueue<TreeNode*> *openNodes = new QQueue<TreeNode*>();
    openNodes->enqueue(startNode);
    TreeNode *actNode = nullptr;

    while ( (openNodes->count() > 0)
            && !((actNode = openNodes->dequeue())->getCurrentState()->isItGoal())) {
        Direction dirs[4] = { Direction::up, Direction::right, Direction::down, Direction::left };
        for (Direction dir: dirs) {
            Operator *o = new Operator(dir);
            if (o->precondition(actNode->getCurrentState())) {
                TreeNode *newNode = new TreeNode(o->apply(actNode->getCurrentState()), actNode);
                if (!openNodes->contains(newNode) && !closedNodes->contains(newNode)) {
                    openNodes->enqueue(newNode);
                }
            }
            delete o;
        }
        closedNodes->append(actNode);
    }
    QList<StateSpace*> *solution = new QList<StateSpace*>();
    if (openNodes->count() > 0) {
        TreeNode *act = actNode;
        for (;  act != nullptr; act = act->getParent()) {
            solution->append(act->getCurrentState());
        }
    }
    return solution;
}
