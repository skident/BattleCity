#include "bullet.h"
#include <exception>
#include <QVariant>
#include <thread>

#include "gamecontroller.h"

using namespace std;

//void Bullet::updatePosition()
//{
//    m_x = m_bullet->property("x").toInt();
//    m_y = m_bullet->property("y").toInt();
//    m_width = m_bullet->property("width").toInt();
//    m_height = m_bullet->property("height").toInt();
//}

//Bullet::Bullet(QObject* bullet, bool isPlayerShot)
//    : m_bullet(bullet)
//    , m_isPlayerShot(isPlayerShot)
//{
//    if (m_bullet == nullptr)
//        throw runtime_error("Invalid ptr to qml object");

//    updatePosition();
////    std::thread(&Bullet::moveToTarget, this).detach();

//    connect(this, SIGNAL(signalMoveBullet(QString, int)), SLOT(moveBullet(QString,int)));
//}

void Bullet::activate(Direction direction)
{
    visible(true);
    m_direction = direction;
    isActive = true;
    std::thread(&Bullet::moveToTarget, shared_from_this()).detach();
}



//QRect Bullet::getPosition()
//{
//     return QRect(m_x, m_y, m_width, m_height);
//}



//void Bullet::setPosition(QPoint pos)
//{
//    m_x = pos.x();
//    m_y = pos.y();

//    m_bullet->setProperty("x", m_x);
//    m_bullet->setProperty("y", m_y);
//}




bool Bullet::hit(QRect object)
{
//    QRect bulletPosition(m_x, m_y, m_width, m_height);
//    return bulletPosition.intersects(getInfo());
    return getInfo().intersects(object);
}



bool Bullet::hit(QObject* object)
{
    QRect position(object->property("x").toInt(),
          object->property("y").toInt(),
          object->property("width").toInt(),
          object->property("height").toInt()
    );

//    QRect bulletPosition(m_x, m_y, m_width, m_height);

//    return bulletPosition.intersects(getInfo());
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



//void Bullet::dumpPos()
//{
//    QRect bulletPosition(m_x, m_y, m_width, m_height);
////    qDebug() << bulletPosition;
//}



void Bullet::moveBullet(QString asix, int step)
{
//    updatePosition();
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
    /*m_bullet->*/setProperty(asix.toStdString().c_str(),
                          /*m_bullet->*/property(asix.toStdString().c_str()).toInt() + (times * step));
}

void Bullet::moveToTarget()
{
    QString asix;
    int step;
//    auto sp = shared_from_this();

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


