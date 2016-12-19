#include "basetank.h"

#include <QDebug>
#include <exception>
#include "gamecontroller.h"
#include "gameobjectfactory.h"


BaseTank::BaseTank()
{
    m_isFreezed = true;
    qDebug() << "Object created";

//    connect(this, SIGNAL(getBullet(BaseTank*)), &GameObjectFactory::get(), SIGNAL(attachBullet(BaseTank*)));
//    emit GameObjectFactory::attachBullet(this);
}

BaseTank::~BaseTank()
{

}

QPoint BaseTank::bulletCoord()
{
    int halfWidth = 5; //m_bullet->property("width").toInt() / 2;
    int halfHeight = 5; //m_bullet->property("height").toInt() / 2;

    auto info = getInfo();
    auto x = info.x();
    auto y = info.y();
    auto width = info.width();
    auto height = info.height();


    QPoint m_bulletCoord;
    if (m_lastStep == step_up)
    {
        m_bulletCoord.setX(x + width / 2 - halfWidth);
        m_bulletCoord.setY(y);
    }
    else if (m_lastStep == step_down)
    {
        m_bulletCoord.setX(x + width / 2 - halfWidth);
        m_bulletCoord.setY(y + height);
    }
    else if (m_lastStep == step_left)
    {
        m_bulletCoord.setX(x);
        m_bulletCoord.setY(y + height / 2 - halfHeight);
    }
    else if (m_lastStep == step_right)
    {
        m_bulletCoord.setX(x + width);
        m_bulletCoord.setY(y + height / 2 - halfHeight);
    }

//    m_bullet->setProperty("x", m_bulletCoord.x());
//    m_bullet->setProperty("y", m_bulletCoord.y());

//    qDebug() << m_bulletCoord;
    return m_bulletCoord;
}


void BaseTank::init()
{
//    QObject* bullet = nullptr;
//    if (!m_isPlayer)
//        bullet = findChild<QObject*>("bullet");
//    else
//        bullet = parent()->findChild<QObject*>("bullet");
//    qDebug() << bullet;

//    m_bullet.reset(new Bullet(bullet, m_isPlayer));
//    m_bullet->dumpPos();

    rotate(step_down);

}


void BaseTank::rotate(Step stepType)
{
    if (stepType == m_lastStep || stepType == step_none)
        return;

    setProperty("rotation", m_angles[stepType]);
    m_lastStep = stepType;
}


void BaseTank::concreteStep(Step step)
{
    if (m_isFreezed)
        return;

    if (step == step_none)
        return;

    rotate(step);
    QPoint coord = getPosition();

    if (step == step_up)
        coord.setY(coord.y() - step_size);
    else if (step == step_down)
        coord.setY(coord.y() + step_size);
    else if (step == step_left)
        coord.setX(coord.x() - step_size);
    else if (step == step_right)
         coord.setX(coord.x() + step_size);

    auto isAllowed = GameController::get().isStepAllowed(this, QRect(coord, getSize()));
    if (isAllowed)
        setPosition(coord);

//    m_bullet->setPosition(bulletCoord());
}


void BaseTank::fire()
{
//    qDebug() << "fire";
    if (m_isFreezed)
        return;

    auto stepToDirection = [](Step step) -> Bullet::Direction
    {
        if (step == step_up)
            return Bullet::dir_up;
        else if (step == step_down)
            return Bullet::dir_down;
        else if (step == step_left)
            return Bullet::dir_left;
        else
            return Bullet::dir_right;
    };

//    auto m_bullet = GameObjectFactory::get().getBullet();

    if (!m_bullet->isActive)
    {
        m_bullet->setPosition(bulletCoord());
        m_bullet->activate(stepToDirection(m_lastStep));
    }
    qDebug() << "Direction: " << stepToDirection(m_lastStep)
             << " | Bullet coord: " << bulletCoord()
             << " | tank pos: " << getInfo();
}


void BaseTank::freeze()
{
    m_isFreezed = true;
}
void BaseTank::unfreeze()
{
    m_isFreezed = false;
}
