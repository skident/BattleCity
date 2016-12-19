#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QQuickItem>
#include <QPoint>
#include <QSize>


class GameObject : public QQuickItem
{
    Q_OBJECT
public:
    GameObject();
    virtual ~GameObject() = 0;

    bool isDestroyable() const
    {
        return m_isDestroyable;
    }

    void setPosition(QPoint pos)
    {
        setProperty("x", pos.x());
        setProperty("y", pos.y());
    }

    void visible(bool state)
    {
        setProperty("visible", state);
    }

    QPoint getPosition()
    {
        return QPoint(property("x").toInt(), property("y").toInt());
    }

    QSize getSize()
    {
        return QSize(property("width").toInt(), property("height").toInt());
    }

    QRect getInfo()
    {
        QRect info( property("x").toInt(),
                    property("y").toInt(),
                    property("width").toInt(),
                    property("height").toInt()
                 );
        return info;
    }

protected:
    bool m_isDestroyable = true;

signals:

public slots:
};

#endif // GAMEOBJECT_H
