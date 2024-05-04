#ifndef PEASHOOTER_H
#define PEASHOOTER_H

#include "plant.h"
#include "../zombie/zombie.h"
#include "../other/pea.h"

//豌豆射手

class Peashooter : public Plant
{
public:
    Peashooter();
    void advance(int phase) override;
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const override;
    int atk;
        int hp;
        int time;
        int counter = 0;
        QMovie* movie;
};
#endif // PEASHOOTER_H
