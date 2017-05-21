#ifndef BREADTHFIRSTSEARCH_H
#define BREADTHFIRSTSEARCH_H

#include <QList>
#include <QQueue>
#include "statespace.h"
#include "node.h"
#include "operator.h"

class BreadthFirstSearch
{
public:
    BreadthFirstSearch();
    QList<StateSpace*> *search(StateSpace *startState);
};

#endif // BREADTHFIRSTSEARCH_H
