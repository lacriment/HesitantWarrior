#include "statespace.h"

Player StateSpace::getPlayer() const
{
    return player;
}

void StateSpace::setPlayerPosition(int x, int y)
{
    player.position.first = x;
    player.position.second = y;
}

void StateSpace::setFinishingPosition(int x, int y)
{
    finishPoint.first = x;
    finishPoint.second = y;
}

void StateSpace::setPlayerSpeed(int s)
{
    this->player.speed = s;
}

// Has the player arrived to the finishing point?
bool StateSpace::isItGoal()
{
    return finishPoint.first == player.position.first &&
            finishPoint.second == player.position.second;
}

// Initilize the starting point and finishing point
StateSpace::StateSpace(QObject *parent) : QObject(parent)
{
    this->player.speed = 2;
}

QPair<int, int> StateSpace::getFinishPoint() const
{
    return finishPoint;
}

State StateSpace::getBoardElement(int x, int y)
{
    return this->board[x][y];
}

State StateSpace::getBoardElement(QPair<int, int> pos)
{
    return this->board[pos.first][pos.second];
}

void StateSpace::setBoardElement(int x, int y, State value)
{
    this->board[x][y] = value;
}

void StateSpace::setBoardElement(QPair<int, int> pos, State value)
{
    this->board[pos.first][pos.second] = value;
}
