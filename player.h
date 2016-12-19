#ifndef TANK_H
#define TANK_H

#include "basetank.h"

class Player : public BaseTank
{
    Q_OBJECT

public:
    Q_INVOKABLE void keyPressed(Qt::Key key);

};

#endif // TANK_H
