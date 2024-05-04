#ifndef SUNFLOWER_H
#define SUNFLOWER_H

#include "plant.h"
#include "../other/sun.h"

//太阳花

class SunFlower : public Plant
{
public:
    SunFlower();
    void advance(int phase) override;
};

#endif // SUNFLOWER_H
