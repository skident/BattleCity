#ifndef GAMEOBJECTFACTORY_H
#define GAMEOBJECTFACTORY_H

#include <QObject>
#include <QQuickItem>
#include <QQmlApplicationEngine>
#include <memory>

class Bullet;
class BaseTank;

class GameObjectFactory/* : public QObject*/
{
public:
    static GameObjectFactory& get()
    {
        static GameObjectFactory self;
        return self;
    }

    enum TankType
    {
        bot,
        player
    };

    void init(QQmlApplicationEngine* engine, QQuickItem* field);
    std::shared_ptr<Bullet> getBullet();
    std::shared_ptr<BaseTank> getTank(TankType tankType);

private:
    QQuickItem* m_field = nullptr;
    QQmlApplicationEngine* m_engine = nullptr;

    GameObjectFactory();
    ~GameObjectFactory();

signals:
    void attachBullet(BaseTank*);

public slots:
    void getBullet(BaseTank* tank);
};

#endif // GAMEOBJECTFACTORY_H
