#ifndef KEYPROCESSOR_H
#define KEYPROCESSOR_H

#include <QQuickItem>

class KeyProcessor : public QQuickItem
{
    Q_OBJECT
public:
    KeyProcessor();
    ~KeyProcessor();

    Q_INVOKABLE void pressed(Qt::Key key);

signals:
    void keyPressed(Qt::Key);
    void player1Controls(Qt::Key);
    void gameControls(Qt::Key);
public slots:
};

#endif // KEYPROCESSOR_H
