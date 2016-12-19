#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include <QRect>
#include "gameobject.h"
#include <memory>

class Bullet : public GameObject, public std::enable_shared_from_this<Bullet>
{
    Q_OBJECT
public:
    Bullet()
    {
        connect(this, SIGNAL(signalMoveBullet(QString, int)), SLOT(moveBullet(QString,int)));
    }

    ~Bullet()
    {
    }

    enum Direction
    {
        dir_up,
        dir_down,
        dir_left,
        dir_right
    };

    bool hit(QRect object);
    bool hit(QObject* object);
    bool outOfFiled(QRect field);

    bool isActive = false;
    void activate(Direction direction);
    void setBulletOwner(bool isPlayer)
    {
        m_isPlayerShot = isPlayer;
    }


signals:
    void signalMoveBullet(QString asix, int step);

public slots:
     void moveBullet(QString asix, int step);

private:
    Direction m_direction = dir_up;

    bool m_isPlayerShot;
    int m_x;
    int m_y;
    int m_width;
    int m_height;

    void moveToTarget();
};

#endif // BULLET_H
