#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include <QVector>
#include <QPoint>
#include <QMap>
#include <QList>
#include <QTimer>
#include <QQueue>

#include "basetank.h"
#include "field.h"
#include "bullet.h"
#include "bot.h"
#include "eagle.h"
#include "brick.h"


class GameController : public QObject
{
    Q_OBJECT
public:
    enum EndReason
    {
        player_won,
        player_lose,
        player_restarted,
    };

    static GameController& get()
    {
        static GameController self;
        return self;
    }

    void init(QObject* root);

    void start();
    void stop(EndReason reason);

    void pause();
    void resume();


    bool isGameOver();
    bool isStepAllowed(BaseTank* tank, QRect newPosition);
    bool isHit(Bullet* bullet, bool isPlayerShot);



private:
    enum Limits
    {
        lim_total_bots = 10,
        lim_max_alive_bots = 3,
        lim_total_players = 1,
        lim_respawn_millisec = 2*1000,
    };

    enum State
    {
        started,
        stopped,
        paused
    };

    enum Statistic
    {
        dead_bots,
        alive_bots,
        dead_players,
    };

    enum QmlName
    {
        name_bullet,
        name_player,
        name_enemy,
        name_eagle,
        name_brick,
        name_gameField,
    };


    Field m_field;
//    QList<BaseTank*> m_bots;
    QList<std::shared_ptr<BaseTank>> m_bots;
    QList<std::shared_ptr<BaseTank>> m_players;
    QList<Brick*> m_bricks;
    QObject* m_statisticInfo;
    QObject* m_endWindow;

    Eagle* m_eagle;
    bool m_isGlobalFreeze = false;
    bool m_isGameOver = true;

    QQueue<BaseTank*> m_respawnQueue;

    QTimer* activeTimer;
    QTimer* freezeTimer;
    QTimer* unfreezeTimer;

    const QVector<QPoint> m_botSpawns =
    {
        QPoint(0,   0),
        QPoint(250, 0),
        QPoint(470, 0)
    };

    const QVector<QPoint> m_playerSpawns =
    {
        QPoint(180, 480),
        QPoint(250, 480)
    };

    const QPoint m_outOfField = QPoint(-100, -100);
    const QPoint m_eaglePos = QPoint(220, 480);
    QSize m_fieldSize;

    QMap<Statistic, int> m_statistics;

    QMap<QmlName, std::string> m_qmlNames =
    {
        {name_bullet,       "bullet"},
        {name_player,       "player"},
        {name_enemy,        "enemy"},
        {name_eagle,        "eagle"},
        {name_brick,        "brick"},
        {name_gameField,    "gameField"},
    };


    GameController();
    ~GameController();

    void spawn(BaseTank* tank);
    void reinitTimer();
    void updateStatistics(int total, int killed);

public slots:
    void killed();
    void respawn();
    void eagleDead();
    void restart();

    // For future
    void freezeBots();
    void unfreezeBots();

};

#endif // GAMECONTROLLER_H
