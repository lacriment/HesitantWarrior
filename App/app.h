#ifndef APP_H
#define APP_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QList>

#include "statespace.h"

namespace Ui {
class App;
}

class App : public QWidget
{
    Q_OBJECT

public:
    explicit App(QWidget *parent = 0);
    ~App();
    void DrawGameState(StateSpace* currentState);

private slots:

    void on_btnQuit_clicked();

    void on_btnStepBack_clicked();

    void on_btnStepForward_clicked();

    void on_App_destroyed();

    void on_btnRight_clicked();

    void on_btnLeft_clicked();

    void on_btnUp_clicked();

    void on_btnDown_clicked();

    void on_btnBFS_clicked();

private:
    Ui::App *ui;
    QGraphicsScene *scene;
    QGraphicsEllipseItem *ellipse;
    QGraphicsRectItem *rectangle;
    QGraphicsTextItem *text;
    QList<StateSpace*> *solutionStates;
    int stepIndex;
    StateSpace *currentState;

protected:
    void keyPressEvent(QKeyEvent *e);

};

#endif // APP_H
