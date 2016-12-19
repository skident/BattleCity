#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <QQuickItem>
#include <QQuickView>

#include "player.h"
#include "bot.h"
#include "field.h"
#include "eagle.h"
#include "brick.h"
#include "gamecontroller.h"

#include "gameobjectfactory.h"


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;


    qmlRegisterType<Player>("com.skident.tank", 1, 0, "PlayerCpp");
    qmlRegisterType<Bot>("com.skident.enemy", 1, 0, "EnemyCpp");
    qmlRegisterType<Eagle>("com.skident.eagle", 1, 0, "EagleCpp");
    qmlRegisterType<Brick>("com.skident.brick", 1, 0, "BrickCpp");
    qmlRegisterType<Bullet>("com.skident.bullet", 1, 0, "BulletCpp");


    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    QObject* rootObject = engine.rootObjects().first();

    QQuickItem* field = rootObject->findChild<QQuickItem*>("gameField");
    auto& goFactory = GameObjectFactory::get();
    goFactory.init(&engine, field);

    GameController::get().init(rootObject);
    GameController::get().start();


    return app.exec();
}
