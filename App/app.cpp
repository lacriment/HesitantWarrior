#include "app.h"
#include "ui_app.h"

#include "filehelper.h"
#include <QDebug>

#include "operator.h"
#include "breadthfirstsearch.h"

App::App(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::App)
{
    ui->setupUi(this);

    currentState = new StateSpace();
    // Read Initial State from the File
    QString boardMatrixRaw = FileHelper::fileToString("board.matrix");
    int x = 0;
    int y = 0;
    for (int i = 0; i < boardMatrixRaw.size(); ++i) {
        if (boardMatrixRaw.at(i) == "S") {
            currentState->setBoardElement(x,y, State::shift);
            x++;
        }
        else if (boardMatrixRaw.at(i) == "E") {
            currentState->setBoardElement(x, y, State::empty);
            x++;
        }
        else if (boardMatrixRaw.at(i) == "B") {
            currentState->setBoardElement(x, y, State::block);
            x++;
        }
        else if (boardMatrixRaw.at(i) == "P") {
            currentState->setFinishPoint(x, y);
            x++;
        }
        else if (boardMatrixRaw.at(i) == "F") {
            currentState->setFinishPoint(x, y);
            x++;
        }
        else if (boardMatrixRaw.at(i) == "\xa") {
            y++;
            x = 0;
        }

    }
    DrawGameState(currentState);
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

void App::on_btnQuit_clicked()
{
    this->close();
}

void App::on_btnStepBack_clicked()
{
    if (stepIndex == 0) return;
    stepIndex--;
    DrawGameState(solutionStates->at(stepIndex));
    qDebug() << stepIndex;
}

void App::on_btnStepForward_clicked()
{
    if (stepIndex == solutionStates->count() - 1 || solutionStates->count() < 1) return;
    stepIndex++;
    DrawGameState(solutionStates->at(stepIndex));
    qDebug() << stepIndex;
}

void App::on_App_destroyed()
{

}

void App::on_btnRight_clicked()
{
    Operator *o = new Operator(Direction::right);
    StateSpace *state = new StateSpace();
    if (o->precondition(currentState)) {
        state = o->apply(currentState);
        DrawGameState(state);
        currentState = state;
    };
    qDebug() << "Pos   : (" << currentState->getPlayer().position.first << ", " <<
                currentState->getPlayer().position.second << ")";
    qDebug() << "Speed : " << currentState->getPlayer().speed;
}

void App::on_btnLeft_clicked()
{
    Operator *o = new Operator(Direction::left);
    StateSpace *state = new StateSpace();
    if (o->precondition(currentState)) {
        state = o->apply(currentState);
        DrawGameState(state);
        currentState = state;
    };
    qDebug() << "Pos   : (" << currentState->getPlayer().position.first << ", " <<
                currentState->getPlayer().position.second << ")";
    qDebug() << "Speed : " << currentState->getPlayer().speed;
}

void App::on_btnUp_clicked()
{
    Operator *o = new Operator(Direction::up);
    StateSpace *state = new StateSpace();
    if (o->precondition(currentState)) {
        state = o->apply(currentState);
        DrawGameState(state);
        currentState = state;
    };
    qDebug() << "Pos   : (" << currentState->getPlayer().position.first << ", " <<
                currentState->getPlayer().position.second << ")";
    qDebug() << "Speed : " << currentState->getPlayer().speed;
}

void App::on_btnDown_clicked()
{
    Operator *o = new Operator(Direction::down);
    StateSpace *state = new StateSpace();
    if (o->precondition(currentState)) {
        state = o->apply(currentState);
        DrawGameState(state);
        currentState = state;
    };
    qDebug() << "Pos   : (" << currentState->getPlayer().position.first << ", " <<
                currentState->getPlayer().position.second << ")";
    qDebug() << "Speed : " << currentState->getPlayer().speed;
}

void App::on_btnBFS_clicked()
{
    BreadthFirstSearch *bfs = new BreadthFirstSearch();
    solutionStates = bfs->search(this->currentState);
    if (solutionStates->count() == 0) {
        ui->lblStatus->setText("No solution!");
    }
    else {
        stepIndex = 0;
        ui->lblCountOfSteps->setText(QString::number(solutionStates->count()-1));
        DrawGameState(solutionStates->at(0));
    }
    qDebug() << "solution : " << solutionStates->count();
}
