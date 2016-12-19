#ifndef EAGLE_H
#define EAGLE_H

#include "gameobject.h"

class Eagle : public GameObject
{
    Q_OBJECT
public:
    Eagle();
    ~Eagle();

signals:
    void dead();
};


#endif // EAGLE_H
