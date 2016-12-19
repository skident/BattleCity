#ifndef FIELD_H
#define FIELD_H

#include <QList>
#include <QObject>

class Eagle;
class BaseTank;
class Bullet;
class Brick;

class Field : public QObject
{
    Q_OBJECT
public:
    typedef QList<Brick*> Bricks;
    typedef QList<std::shared_ptr<BaseTank>> Bots;
    typedef QList<std::shared_ptr<BaseTank>> Players;

    Field();
    ~Field();

    void reset(QSize size,
               Bricks bricks,
               Eagle* eagle,
               Bots bots,
               Players players
               );

    bool isStepAllowed(QRect tankNewPosition, BaseTank* ptr = nullptr);
    bool isHit(Bullet* bullet, bool isPlayer);

private:
    int     m_width = 0;
    int     m_height = 0;

    Bricks  m_bricks;
    Bots    m_bots;
    Players m_players;
    Eagle*  m_pEagle = nullptr;
};

#endif // FIELD_H
