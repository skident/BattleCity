#ifndef LEVEL_H
#define LEVEL_H

#include <QVector>
#include <QPoint>
#include <QString>

struct Level
{
public:
    Level();


    QVector<QPoint> m_botsPos;
    QVector<QPoint> m_playersPos;
    QPoint m_eaglePos;
    QVector<QString> m_map;
};

#endif // LEVEL_H
