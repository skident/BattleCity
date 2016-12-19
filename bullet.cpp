#include "bullet.h"
#include <exception>
#include <QVariant>
#include <thread>

#include "gamecontroller.h"

using namespace std;

void Bullet::activate(Direction direction)
{
    visible(true);
    m_direction = direction;
    isActive = true;
    std::thread(&Bullet::moveToTarget, shared_from_this()).detach();
}

bool Bullet::hit(QRect object)
{
    return getInfo().intersects(object);
}

bool Bullet::hit(QObject* object)
{
    QRect position(object->property("x").toInt(),
          object->property("y").toInt(),
          object->property("width").toInt(),
          object->property("height").toInt()
    );
    return getInfo().intersects(position);
}

bool Bullet::outOfFiled(QRect field)
{
    QRect info = getInfo();
    if (info.x() < field.x() ||
        info.x() + info.width() > field.width() ||
        info.y() < field.y() ||
        info.y() + info.height() > field.height()
        )
    {
        return true;
    }
    return false;
}

void Bullet::moveBullet(QString asix, int step)
{
    QRect bulletPosition = getInfo();   //(m_x, m_y, m_width, m_height);

    bool isHit = GameController::get().isHit(this, m_isPlayerShot);
    if (isHit)
    {
        visible(false);
        isActive = false;

//        QObject* explosion = m_bullet->findChild<QObject*>("explosion"); //m_explosions.first();
//        explosion->setProperty("visible", true);
//        explosion->setProperty("playing", true);
    }

    int times = 4;
    setProperty(asix.toStdString().c_str(),
                property(asix.toStdString().c_str()).toInt() + (times * step));
}

void Bullet::moveToTarget()
{
    QString asix;
    int step;

    while (isActive)
    {
        asix = "x";
        step = 1;
        if (m_direction == dir_down || m_direction == dir_up)
            asix = "y";
        if (m_direction == dir_left || m_direction == dir_up)
            step = -1;

        emit signalMoveBullet(asix, step);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}


