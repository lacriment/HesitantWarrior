#include "breadthfirstsearch.h"

BreadthFirstSearch::BreadthFirstSearch()
{

}
#include <QDebug>

QList<StateSpace *> *BreadthFirstSearch::search(StateSpace *startState)
{
    Node *startNode = new Node(startState, nullptr);
    QList<Node*> *explored = new QList<Node*>();
    QQueue<Node*> *frontier = new QQueue<Node*>();
    Node *currentNode = new Node();
    frontier->enqueue(startNode);

    while (frontier->length() > 0) {
        currentNode = frontier->dequeue();
        qDebug() << "Cur Pos:" << currentNode->getCurrentState()->getPlayer().position;
        qDebug() << "Cur Speed:" << currentNode->getCurrentState()->getPlayer().speed;
        if (currentNode->getCurrentState()->isItGoal()) {
            break;
        }
        Direction dirs[4] = { Direction::up, Direction::right, Direction::down, Direction::left };
        for (Direction dir: dirs) {
            Operator *o = new Operator(dir);
            if (o->precondition(currentNode->getCurrentState())) {
                qDebug() << "Dir      :" << static_cast<int>(dir);
                qDebug() << "Cur Pos  :" << currentNode->getCurrentState()->getPlayer().position;
                qDebug() << "Cur Speed:" << currentNode->getCurrentState()->getPlayer().speed;
                Node *newNode = new Node(o->apply(currentNode->getCurrentState()), currentNode);
                if (!explored->contains(newNode) && !frontier->contains(newNode)) {
                    explored->append(newNode);
                    newNode->setParent(currentNode);
                    frontier->enqueue(newNode);
                }
            }
            delete o;
        }
        explored->append(currentNode);
    }

    QList<StateSpace*> *solution = new QList<StateSpace*>();
    if (frontier->count() > 0) {
        Node *curr = currentNode;
        for (;  curr != nullptr; curr = curr->getParent()) {
            solution->push_front(curr->getCurrentState());
        }
    }
    return solution;
}
