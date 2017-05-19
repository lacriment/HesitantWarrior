#ifndef STATESPACE_H
#define STATESPACE_H

#include <QObject>


struct Player {
    QPair<int, int> position; // X and Y coordinates of the player
    int speed;     // Distance of the next movement: 2 or 3
};

enum class State {
    empty,   // free area
    shift,  // change point
    block   // banned area
};

enum class Direction {
    up,
    right,
    down,
    left
};

class StateSpace : public QObject
{
    Q_OBJECT
private:
    Player player;
    State board[8][8];
    QPair<int, int> finishPoint;

public:
    explicit StateSpace(QObject *parent = 0);

    State getBoardElement(int x, int y);
    State getBoardElement(QPair<int, int> pos);
    void setBoardElement(int x, int y, State value);
    void setBoardElement(QPair<int, int> pos, State value);

    QPair<int, int> getFinishPoint() const;

    Player getPlayer() const;
    void setPlayerPosition(int x, int y);
    void setFinishingPosition(int x, int y);
    void setPlayerSpeed(int s);
    bool isItGoal();

signals:

public slots:
};

#endif // STATESPACE_H
