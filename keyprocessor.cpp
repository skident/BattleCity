#include "keyprocessor.h"
#include "gamecontroller.h"

KeyProcessor::KeyProcessor()
{
    connect(this, SIGNAL(gameControls(Qt::Key)), &GameController::get(), SLOT(keyPressed(Qt::Key)));
}

KeyProcessor::~KeyProcessor()
{

}

void KeyProcessor::pressed(Qt::Key key)
{
//    qDebug() << "presssss";
//    // FIXME: DIRTY HACK for restart game!
//    if (key == Qt::Key_Escape)
//        GameController::get().restart();

    switch(key)
    {
    case Qt::Key_Up:
    case Qt::Key_Down:
    case Qt::Key_Left:
    case Qt::Key_Right:
    case Qt::Key_Space:
//        emit player1Controls(key);
//        return;

    case Qt::Key_Escape:
        emit gameControls(key);
        return;

    default:
        return;
    }
}
