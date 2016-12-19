#include "gamecontroller.h"

#include "player.h"
#include "bot.h"
#include "brick.h"

#include "gameobjectfactory.h"


GameController::GameController()
{
    activeTimer = new QTimer(this);
    activeTimer->setInterval(lim_respawn_millisec);
    activeTimer->setSingleShot(true);
    connect(activeTimer, SIGNAL(timeout()), this, SLOT(respawn()));
}

GameController::~GameController()
{

}

void GameController::reinitTimer()
{
    activeTimer->start();
}

void GameController::updateStatistics(int total, int killed)
{
    QString sInfo = "Total enemies: " + QString::number(total);
    sInfo += "\tKilled enemies: " + QString::number(killed);

    m_statisticInfo->setProperty("information", sInfo);
}


void GameController::init(QObject *rootObject)
{
    m_bricks = rootObject->findChildren<Brick*>(m_qmlNames[name_brick].c_str());

    QObject* field = rootObject->findChild<QObject*>(m_qmlNames[name_gameField].c_str());
    m_fieldSize = QSize(field->property("width").toInt(), field->property("height").toInt());

    m_eagle = rootObject->findChild<Eagle*>(m_qmlNames[name_eagle].c_str());
    connect(m_eagle, SIGNAL(dead()), this, SLOT(eagleDead()));

    for (int i = 0; i < lim_max_alive_bots; i++)
        m_bots.append(GameObjectFactory::get().getTank(GameObjectFactory::bot));
//    m_bots = rootObject->findChildren<BaseTank*>(m_qmlNames[name_enemy].c_str());
//    m_players = rootObject->findChildren<BaseTank*>(m_qmlNames[name_player].c_str());

    m_players.append(GameObjectFactory::get().getTank(GameObjectFactory::player));

    m_endWindow = rootObject->findChild<QObject*>("game_over");
    m_statisticInfo = rootObject->findChild<QObject*>("statistics");
    updateStatistics(lim_total_bots, 0);


    for (auto bot : m_bots)
    {
        bot->visible(false);
        bot->setBullet(GameObjectFactory::get().getBullet());
    }

    for (auto player : m_players)
    {
//        player->visible(false);
        player->setBullet(GameObjectFactory::get().getBullet());
    }
}

void GameController::start()
{
    updateStatistics(lim_total_bots, 0);

    m_statistics.clear();
    m_statistics =
    {
        {dead_bots,     0},
        {alive_bots,    0},
        {dead_players,  0}
    };

    m_eagle->setProperty("state", "default");

    for (auto brick : m_bricks)
    {
        brick->setProperty("visible", true);
    }

    auto itPlayer = m_players.begin();
    for (auto spawn : m_playerSpawns)
    {
        if (itPlayer == m_players.end())
            break;

        auto player = *itPlayer;
        player->setProperty("x", spawn.x());
        player->setProperty("y", spawn.y());
        player->unfreeze();
        connect(player.get(), SIGNAL(dead()), this, SLOT(killed()));

        ++itPlayer;
    }


    m_field.reset(m_fieldSize, m_bricks, m_eagle, m_bots, m_players);

    int counter = 0;
    for (auto bot : m_bots)
    {
        if (counter == lim_max_alive_bots)
            break;
        connect(bot.get(), SIGNAL(dead()), this, SLOT(killed()));
        spawn(bot.get());
        bot->unfreeze();
        counter++;
    }

    m_endWindow->setProperty("visible", false);
    m_isGameOver = false;
}

void GameController::stop(EndReason reason)
{
    m_isGameOver = true;
    activeTimer->stop();

    for (auto bot : m_bots)
    {
        bot->freeze();
        disconnect(bot.get(), SIGNAL(dead()), this, SLOT(killed()));
    }
    for (auto player : m_players)
    {
        player->freeze();
        disconnect(player.get(), SIGNAL(dead()), this, SLOT(killed()));
    }


    QString strReason;
    switch (reason)
    {
    case player_restarted:
        return;

    case player_won:
        strReason = "You won";
        break;
    case player_lose:
        strReason = "You lose";
        break;
    }

    m_endWindow->setProperty("info", strReason);
    m_endWindow->setProperty("visible", true);
}

void GameController::restart()
{
    if (m_isGameOver)
        start();
}

bool GameController::isStepAllowed(BaseTank* tank, QRect newPosition)
{
    bool isAllowed = m_field.isStepAllowed(newPosition, tank);
    return isAllowed;
}

bool GameController::isHit(Bullet* bullet, bool isPlayerShot)
{
    return m_field.isHit(bullet, isPlayerShot);
}


void GameController::killed()
{
    BaseTank* tank = qobject_cast<BaseTank*>(sender());

    tank->freeze();
    tank->setPosition(m_outOfField);
    tank->visible(false);

    if (dynamic_cast<Player*>(tank))
    {
        m_statistics[dead_players]++;
        if (m_statistics[dead_players] == lim_total_players)
        {
            stop(player_lose);
            return;
        }
    }

    if (dynamic_cast<Bot*>(tank))
    {
        auto dead = ++m_statistics[dead_bots];
        auto alive = --m_statistics[alive_bots];

        updateStatistics(lim_total_bots, dead);

        if (dead == lim_total_bots)
        {
            stop(player_won);
            return;
        }

        if (dead + alive < lim_total_bots)
        {
            m_respawnQueue.push_back(tank);
            reinitTimer();
        }
    }
}


void GameController::spawn(BaseTank* tank)
{
    bool isSpawned = false;
    for (auto spawn : m_botSpawns)
    {
        if (!isStepAllowed(tank, QRect(spawn, tank->getSize())))
            continue;

        tank->setPosition(spawn);
        tank->visible(true);
        isSpawned = true;
        m_statistics[alive_bots]++;
        break;
    }

    if (!isSpawned)
    {
        m_respawnQueue.push_back(tank);
        reinitTimer();
    }
}

void GameController::respawn()
{
    if (m_isGameOver)
    {
        qDebug() << "game over";
        return;
    }

    if (m_respawnQueue.empty())
    {
        qDebug() << "queue is empty";
        return;
    }

    BaseTank* tank = m_respawnQueue.front();
    m_respawnQueue.pop_front();

    bool isSpawned = false;
    for (auto spawn : m_botSpawns)
    {
        auto size = tank->getSize();
        QRect newPos(spawn, size);

        if (isStepAllowed(tank, newPos))
        {
            tank->setPosition(spawn);
            tank->visible(true);

            if (!m_isGlobalFreeze)
                tank->unfreeze();
            isSpawned = true;
            m_statistics[alive_bots]++;
            break;
        }
    }

    // put back
    if (!isSpawned)
    {
        m_respawnQueue.push_back(tank);
        reinitTimer();
    }
}

void GameController::eagleDead()
{
    stop(player_lose);
}

void GameController::freezeBots()
{
    m_isGlobalFreeze = true;
    for (auto bot : m_bots)
    {
        bot->freeze();
    }
    unfreezeTimer->start();
}

void GameController::unfreezeBots()
{
    m_isGlobalFreeze = false;
    for (auto bot : m_bots)
    {
        bot->unfreeze();
    }
}

void GameController::keyPressed(Qt::Key key)
{
    switch(key)
    {
    case Qt::Key_Up:
    case Qt::Key_Down:
    case Qt::Key_Left:
    case Qt::Key_Right:
    case Qt::Key_Space:
    {
        if (m_players.size() == 0)
            return;

        std::shared_ptr<Player> player = std::dynamic_pointer_cast<Player>( m_players.at(0));
        player->keyPressed(key);
    }
        return;


    case Qt::Key_W:
    case Qt::Key_A:
    case Qt::Key_S:
    case Qt::Key_D:
    case Qt::Key_Control:
    {
        if (m_players.size() < 2)
            return;

        std::shared_ptr<Player> player = std::dynamic_pointer_cast<Player>( m_players.at(1));
        player->keyPressed(key);
    }
        return;


    case Qt::Key_Escape:
        restart();
        return;

    default:
        return;
    }
}
