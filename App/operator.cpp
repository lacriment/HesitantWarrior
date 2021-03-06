#include "operator.h"

const Direction Operator::dirs[4] = { Direction::up, Direction::right, Direction::down, Direction::left };

Operator::Operator(QObject *parent) : QObject(parent)
{

}

Operator::Operator(Direction dir)
{
    this->dir = dir;

    // Convert to cartesian direction
    if (dir == Direction::down) {
        this->dirCartesian = qMakePair(0, 1);
    }
    else if (dir == Direction::up) {
        this->dirCartesian = qMakePair(0, -1);
    }
    else if (dir == Direction::left) {
        this->dirCartesian = qMakePair(-1, 0);
    }
    else if (dir == Direction::right) {
        this->dirCartesian = qMakePair(1, 0);
    }
}

StateSpace *Operator::apply(StateSpace *currentState)
{
    StateSpace *newState = new StateSpace();
    newState->setBoard(currentState->getBoard());
    newState->setPlayer(currentState->getPlayer());
    newState->setFinishPoint(currentState->getFinishPoint());
    int x = newState->getPlayer().position.first;
    int y = newState->getPlayer().position.second;
    int speed = newState->getPlayer().speed;

    // Apply
    newState->setPlayerPosition( x + ( dirCartesian.first * speed ),
                                 y + ( dirCartesian.second * speed) );

    //check is it the point of change for speed -- current state
    if (newState->getBoardElement(newState->getPlayer().position) == State::shift) {
        if (speed == 3)
            newState->setPlayerSpeed(2);
        else
            newState->setPlayerSpeed(3);
    }
    return newState;
}

bool Operator::precondition(StateSpace *currentState)
{
    int x = currentState->getPlayer().position.first;
    int y = currentState->getPlayer().position.second;
    int speed = currentState->getPlayer().speed;

    // check is the next step inside the walls
    int next_x = x + (speed * dirCartesian.first);
    int next_y = y + (speed * dirCartesian.second);
    if (next_x < 0 || next_x > 7 || next_y < 0 || next_y > 7) {
        return false;
    }

    // check is the next step path has any block
    for (int i = 1; i <= speed; i++) {
        int next_x = x + (i * dirCartesian.first);
        int next_y = y + (i * dirCartesian.second);
        if (currentState->getBoardElement(next_x, next_y)
                == State::block) {
            return false;
        }
    }

    return true;
}
