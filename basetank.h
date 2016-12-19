#ifndef ITANK_H
#define ITANK_H


#include <QObject>
#include <QQuickItem>
#include <QPoint>
#include <memory>
#include "bullet.h"
#include <atomic>
#include "gameobject.h"

class BaseTank : public GameObject
{
    Q_OBJECT
public:
    enum Step
    {
        step_up,
        step_down,
        step_left,
        step_right,
        step_none,
    };


    BaseTank();
    virtual ~BaseTank() = 0;

    Q_INVOKABLE void init();
    void setBullet(std::shared_ptr<Bullet> bullet)
    {
        m_bullet = bullet;
        m_bullet->setBulletOwner(m_isPlayer);
    }

    QPoint bulletCoord();
    void freeze();
    void unfreeze();

protected:
    enum
    {
        step_size = 10,
    };

    Step m_lastStep = step_up;
    bool m_isPlayer = true;
    std::atomic<bool> m_isFreezed;
    std::shared_ptr<Bullet> m_bullet;

    const QMap<Step, int> m_angles = {
        {step_up, 0},
        {step_right, 90},
        {step_down, 180},
        {step_left, 270}
    };


    void rotate(Step shouldFaced);
    void concreteStep(Step step);
    void fire();

signals:
    void dead();
    void getBullet(BaseTank*);
};

#endif // ITANK_H
