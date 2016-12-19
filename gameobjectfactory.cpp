#include "gameobjectfactory.h"

#include <QQmlEngine>

#include "bullet.h"
#include "basetank.h"

GameObjectFactory::GameObjectFactory()
{

}

GameObjectFactory::~GameObjectFactory()
{

}

void GameObjectFactory::getBullet(BaseTank *tank)
{
    QQmlComponent component(m_engine, QUrl(QStringLiteral("qrc:/qml/Bullet.qml")));
    Bullet *object = qobject_cast<Bullet*>(component.create());

    QQmlEngine::setObjectOwnership(object, QQmlEngine::CppOwnership);
    object->setParentItem(m_field);
    object->setParent(m_field);

    tank->setBullet(std::shared_ptr<Bullet>(object));
}

void GameObjectFactory::init(QQmlApplicationEngine* engine, QQuickItem *field)
{
    m_engine = engine;
    m_field = field;
}

std::shared_ptr<Bullet> GameObjectFactory::getBullet()
{
    QQmlComponent component(m_engine, QUrl(QStringLiteral("qrc:/qml/Bullet.qml")));
    Bullet *object = qobject_cast<Bullet*>(component.create());

    QQmlEngine::setObjectOwnership(object, QQmlEngine::CppOwnership);
    object->setParentItem(m_field);
    object->setParent(m_field);

    return std::shared_ptr<Bullet>(object);
}


std::shared_ptr<BaseTank> GameObjectFactory::getTank(TankType tankType)
{
    QString qmlFile = QStringLiteral("qrc:/qml/EnemyTank.qml");
    if (tankType == player)
        qmlFile = QStringLiteral("qrc:/qml/Player.qml");

    QQmlComponent component(m_engine, QUrl(qmlFile));
    auto object = qobject_cast<BaseTank*>(component.create());

    QQmlEngine::setObjectOwnership(object, QQmlEngine::CppOwnership);
    object->setParentItem(m_field);
    object->setParent(m_field);

    object->setBullet(getBullet());

    return std::shared_ptr<BaseTank>(object);
}
