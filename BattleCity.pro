TEMPLATE = app

CONFIG += c++11 thread
QT += quick qml

SOURCES += main.cpp \
    basetank.cpp \
    bot.cpp \
    bullet.cpp \
    eagle.cpp \
    field.cpp \
    gamecontroller.cpp \
    player.cpp \
    gameobject.cpp \
    brick.cpp \
    gameobjectfactory.cpp \
    level.cpp \
    keyprocessor.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    basetank.h \
    bot.h \
    bullet.h \
    eagle.h \
    field.h \
    gamecontroller.h \
    player.h \
    gameobject.h \
    brick.h \
    gameobjectfactory.h \
    level.h \
    keyprocessor.h
