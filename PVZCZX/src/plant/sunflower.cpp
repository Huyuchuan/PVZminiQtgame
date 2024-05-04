#include "sunflower.h"
#include <QDebug>

SunFlower::SunFlower()
{
    hp = hp_NormalPlant;
    time = int(10.0 * 1000 / 33);
    setMovie(":/images/SunFlower.gif");
    L_INFO("Plant a Sunflower");
}

//生产阳光
void SunFlower::advance(int phase)
{
    if (!phase)
        return;
    update();
    if (hp <= 0)
        delete this;

    //无论是否执行里面的语句，都会++counter
    else if (++counter >= time)
    {
        counter = 0;
        scene()->addItem(new Sun(pos()));
    }
}


