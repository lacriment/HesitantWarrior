#include "operator.h"

Operator::Operator(QObject *parent) : QObject(parent)
{

}

Operator::Operator(Direction dir)
{
    this->dir = dir;
}

StateSpace *Operator::apply(StateSpace *currentState)
{
    StateSpace *newState = new StateSpace();
    newState = currentState;
    int x = currentState->getPlayer().position.first;
    int y = currentState->getPlayer().position.second;
    int speed = currentState->getPlayer().speed;

    if (dir == Direction::up) {
        newState->setPlayerPosition(x, y-speed);
    }
    else if (dir == Direction::right) {
        newState->setPlayerPosition(x+speed, y);
    }
    else if (dir == Direction::down) {
        newState->setPlayerPosition(x, y+speed);
    }
    else if (dir == Direction::left) {
        newState->setPlayerPosition(x-speed, y);
    }
    return newState;
}

bool Operator::precondition(StateSpace *currentState)
{
    int x = currentState->getPlayer().position.first;
    int y = currentState->getPlayer().position.second;
    int speed = currentState->getPlayer().speed;
    int new_x = x;
    int new_y = y;

    //check is it the point of change for speed -- current state
    if (currentState->getBoardElement(x, y) == State::shift) {
        if (speed == 3)
            currentState->setPlayerSpeed(2);
        else
            currentState->setPlayerSpeed(3);
    }

    if (dir == Direction::up) {
        new_y = y - speed;
    }
    else if (dir == Direction::right) {
        new_x = x + speed;
    }
    else if (dir == Direction::down) {
        new_y = y + speed;
    }
    else if (dir == Direction::left) {
        new_x = x - speed;
    }

    // check is the next step inside the walls
    if (new_x < 0 || new_x > 7 || new_y < 0 || new_y > 7) {
        return false;
    }

    // check is the next step a block
    if (currentState->getBoardElement(new_x, new_y) == State::block) {
        return false;
    }

    return true;
}
