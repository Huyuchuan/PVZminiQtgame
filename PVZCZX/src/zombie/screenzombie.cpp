#include "screenzombie.h"

ScreenZombie::ScreenZombie()
{
    hp = hp_ScreenZombie;
    atk = atk_Zombie;
    speed = speed_zombie_1;
    setMovie(":/images/ScreenZombieWalk.gif");
}

void ScreenZombie::advance(int phase)
ZOMBIE_ADVANCE(
        ":/images/ZombieDie.gif",
        ":/images/ZombieHead.gif",
        ":/images/ScreenZombieAttack.gif",
        ":/images/ScreenZombieWalk.gif")
