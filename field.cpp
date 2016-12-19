#include "field.h"
#include <QVariant>
#include <QDebug>
#include "basetank.h"
#include "bot.h"
#include "eagle.h"
#include "brick.h"

//#define __TRACE__


Field::Field()
{
}

Field::~Field()
{

}

void Field::reset(QSize size,
                  QList<Brick*> bricks,
                  Eagle* eagle,
                  Bots bots,
                  Players players
                  )
{
    m_width = size.width();
    m_height = size.height();

    m_bricks = bricks;
    m_pEagle = eagle;
    m_bots = bots;
    m_players = players;
}

bool Field::isStepAllowed(QRect tankNewPosition, BaseTank* ptr)
{
     if (tankNewPosition.x() < 0 ||
        tankNewPosition.x() + tankNewPosition.width() > m_width ||
        tankNewPosition.y() < 0 ||
        tankNewPosition.y() + tankNewPosition.height() > m_height
        )
    {
        #ifdef __TRACE__
        qDebug() << "overlaps with field border";
        #endif
        return false;
    }

    bool isOverlapped = false;
    isOverlapped = tankNewPosition.intersects(m_pEagle->getInfo());
    if (isOverlapped)
    {
        #ifdef __TRACE__
        qDebug() << "overlaps with eagle";
        #endif
        return false;
    }

    for (auto it = m_bots.begin(); it != m_bots.end(); ++it)
    {
        BaseTank* enemy = (*it).get();
        if (ptr == enemy)
            continue;

        isOverlapped = tankNewPosition.intersects(enemy->getInfo());
        if (isOverlapped)
        {
            #ifdef __TRACE__
            qDebug() << "overlaps with " << enemy;
            #endif
            return false;
        }
    }

    for (auto it = m_players.begin(); it != m_players.end(); ++it)
    {
        BaseTank* player = (*it).get();
        if (ptr == player)
            continue;

        isOverlapped = tankNewPosition.intersects(player->getInfo());
        if (isOverlapped)
        {
            #ifdef __TRACE__
            qDebug() << "overlaps with " << player;
            #endif
            return false;
        }
    }

    for (auto it = m_bricks.begin(); it != m_bricks.end(); ++it)
    {
        isOverlapped = tankNewPosition.intersects((*it)->getInfo());
        if (isOverlapped)
        {
            return false;
        }
    }
    return true;
}

bool Field::isHit(Bullet* bullet, bool isPlayer)
{
    if (bullet->outOfFiled(QRect(0, 0, m_width, m_height)))
    {
        return true;
    }

    if (bullet->hit(m_pEagle))
    {
        m_pEagle->setProperty("state", "dead");
        emit m_pEagle->dead();
        return true;
    }

    auto& tanks = (isPlayer ? m_bots : m_players);
    for (auto it = tanks.begin(); it != tanks.end(); ++it)
    {
        auto tank = *it;
        if (bullet->hit(tank.get()))
        {
            emit tank->dead();
            return true;
        }
    }

    bool hit = false;
    for (auto it = m_bricks.begin(); it != m_bricks.end();/* ++it*/)
    {
        if (bullet->hit(*it))
        {
            hit = true;
            (*it)->setProperty("visible", false);
            auto tmpIt = it;
            ++it;
            m_bricks.erase(tmpIt);
        }
        else
            ++it;
    }

    return hit;
}
