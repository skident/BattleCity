#ifndef ENEMY_H
#define ENEMY_H

//#include <QQuickItem>
#include <atomic>
#include "basetank.h"

class Bot : public BaseTank
{
    Q_OBJECT
public:
    Bot();
    ~Bot();

private:
    std::atomic<Step> m_nextStep;

    void navigator();

signals:
    void nextStep();

public slots:
    void moveProcess();
};

#endif // ENEMY_H
