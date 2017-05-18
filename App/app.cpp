#include "app.h"
#include "ui_app.h"

#include "filehelper.h"
#include <QDebug>

#include "operator.h"

App::App(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::App)
{
    ui->setupUi(this);
    stepIndex = 0;

    startState = new StateSpace();
    // Read Initial State from the File
    QString boardMatrixRaw = FileHelper::fileToString("board.matrix");
    int x = 0;
    int y = 0;
    for (int i = 0; i < boardMatrixRaw.size(); ++i) {
        if (boardMatrixRaw.at(i) == "S") {
            startState->setBoardElement(x,y, State::shift);
            x++;
        }
        else if (boardMatrixRaw.at(i) == "E") {
            startState->setBoardElement(x, y, State::empty);
            x++;
        }
        else if (boardMatrixRaw.at(i) == "B") {
            startState->setBoardElement(x, y, State::block);
            x++;
        }
        else if (boardMatrixRaw.at(i) == "P") {
            startState->setPlayerPosition(x, y);
            x++;
        }
        else if (boardMatrixRaw.at(i) == "F") {
            startState->setFinishingPosition(x, y);
            x++;
        }
        else if (boardMatrixRaw.at(i) == "\xa") {
            y++;
            x = 0;
        }

    }
    DrawGameState(startState);
}

App::~App()
{
    delete ui;
}

void App::DrawGameState(StateSpace *currentState)
{
    scene = new QGraphicsScene(this);

    ui->canvas->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->canvas->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->canvas->setFixedSize(484,484);
    ui->canvas->setScene(scene);
    ui->canvas->setRenderHints(QPainter::Antialiasing);

    QPen blackPen(Qt::black);
    blackPen.setWidth(1);

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j< 8; ++j) {
            rectangle = scene->addRect(i*60, j*60, 60, 60, blackPen, Qt::white);
            if (currentState->getBoardElement(i, j) == State::block) {
                rectangle = scene->addRect(i*60, j*60, 60, 60, blackPen, Qt::black );
            }
            else if (currentState->getBoardElement(i, j) == State::shift) {
                ellipse = scene->addEllipse(i*60+15, j*60+15, 30, 30 , blackPen, Qt::gray);
            }
        }
    }
    ellipse = scene->addEllipse(currentState->getPlayer().position.first*60+15,
                                currentState->getPlayer().position.second*60+15, 30, 30 , blackPen, Qt::darkGreen);
    rectangle = scene->addRect(currentState->getFinishPoint().first*60+15,
                                currentState->getFinishPoint().second*60+15, 30, 30 , blackPen, Qt::magenta);
}

void App::on_btnBackTrack_clicked()
{

}

void App::on_btnQuit_clicked()
{
    this->close();
}

void App::on_btnStepBack_clicked()
{
    if (stepIndex == 0) return;
    stepIndex--;
    DrawGameState(solutionStates[stepIndex]);
}

void App::on_btnStepForward_clicked()
{
    if (stepIndex == solutionStates.count() - 1 || solutionStates.count() < 1) return;
    stepIndex++;
    DrawGameState(solutionStates[stepIndex]);
}

void App::on_App_destroyed()
{

}

void App::on_btnRight_clicked()
{
    Operator *o = new Operator(Direction::right);
    StateSpace *newState = new StateSpace();
    if (o->precondition(startState)) {
        newState = o->apply(startState);
        DrawGameState(newState);
    };
    qDebug() << newState->getPlayer().position;
    qDebug() << newState->getPlayer().speed;
}

void App::on_btnLeft_clicked()
{
    Operator *o = new Operator(Direction::left);
    StateSpace *newState = new StateSpace();
    if (o->precondition(startState)) {
        newState = o->apply(startState);
        DrawGameState(newState);
    };
    qDebug() << newState->getPlayer().position;
    qDebug() << newState->getPlayer().speed;
}

void App::on_btnUp_clicked()
{
    Operator *o = new Operator(Direction::up);
    StateSpace *newState = new StateSpace();
    if (o->precondition(startState)) {
        newState = o->apply(startState);
        DrawGameState(newState);
    };
    qDebug() << newState->getPlayer().position;
    qDebug() << newState->getPlayer().speed;
}

void App::on_btnDown_clicked()
{
    Operator *o = new Operator(Direction::down);
    StateSpace *newState = new StateSpace();
    if (o->precondition(startState)) {
        newState = o->apply(startState);
        DrawGameState(newState);
    };
    qDebug() << newState->getPlayer().position;
    qDebug() << newState->getPlayer().speed;
}
