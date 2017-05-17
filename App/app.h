#ifndef APP_H
#define APP_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include "statespace.h"

#include <QList>

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

    void on_btnBackTrack_clicked();

    void on_btnQuit_clicked();

    void on_btnStepBack_clicked();

    void on_btnStepForward_clicked();

private:
    Ui::App *ui;
    QGraphicsScene *scene;
    QGraphicsEllipseItem *ellipse;
    QGraphicsRectItem *rectangle;
    QGraphicsTextItem *text;
    QList<StateSpace*> solutionStates;
    int stepIndex;

};

#endif // APP_H
