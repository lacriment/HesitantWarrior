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
    std::array<std::array<State, 8>, 8> board;
    QPair<int, int> finishPoint;

public:
    explicit StateSpace(QObject *parent = 0);

    State getBoardElement(int x, int y);
    State getBoardElement(QPair<int, int> pos);
    void setBoardElement(int x, int y, State value);
    void setBoardElement(QPair<int, int> pos, State value);
    void setPlayer(const Player &value);
    void setPlayerPosition(int x, int y);
    void setPlayerSpeed(int s);

    QPair<int, int> getFinishPoint() const;
    Player getPlayer() const;

    bool isItGoal();
    bool equals(StateSpace *state);

    void setFinishPoint(int x, int y);
    void setFinishPoint(QPair<int, int> point);

    std::array<std::array<State, 8>, 8> getBoard() const;
    void setBoard(const std::array<std::array<State, 8>, 8> &value);

signals:

public slots:
};

#endif // STATESPACE_H
