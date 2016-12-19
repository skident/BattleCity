#include "player.h"

#include <QDebug>
#include <exception>
#include <gamecontroller.h>

void Player::keyPressed(Qt::Key key)
{
    // FIXME: DIRTY HACK for restart game!
    if (key == Qt::Key_Escape)
        GameController::get().restart();

    Step nextStep = step_none;
    switch(key)
    {
    case Qt::Key_Up:
        nextStep = step_up;
        break;

    case Qt::Key_Down:
        nextStep = step_down;
        break;

    case Qt::Key_Left:
        nextStep = step_left;
        break;

    case Qt::Key_Right:
        nextStep = step_right;
        break;

    case Qt::Key_Space:
        fire();
        return;

    default:
        return;
    }

     concreteStep(nextStep);
}
