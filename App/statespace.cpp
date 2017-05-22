#include "statespace.h"

Player StateSpace::getPlayer() const
{
    return player;
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

bool StateSpace::equals(StateSpace *state)
{
    if (state->player.position == player.position
            && state->getPlayer().speed == player.speed) {
        return true;
    }
    return false;
}

// Initilize the starting point and finishing point
void StateSpace::setPlayer(const Player &value)
{
    player = value;
}

void StateSpace::setPlayerPosition(int x, int y)
{
    this->player.position = qMakePair(x, y);
}

std::array<std::array<State, 8>, 8> StateSpace::getBoard() const
{
    return board;
}

void StateSpace::setBoard(const std::array<std::array<State, 8>, 8> &value)
{
    board = value;
}


void StateSpace::setFinishPoint(QPair<int, int> point)
{
    this->finishPoint= point;
}

void StateSpace::setFinishPoint(int x, int y)
{
    this->finishPoint.first = x;
    this->finishPoint.second = y;
}


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
