#include "conezombie.h"

ConeZombie::ConeZombie()
{
    hp = hp_ConeZombie;
    atk = atk_Zombie;
    speed = speed_zombie_1;
    setMovie(":/images/ConeZombieWalk.gif");
}

void ConeZombie::advance(int phase)
ZOMBIE_ADVANCE(
        ":/images/ZombieDie.gif",
        ":/images/ZombieHead.gif",
        ":/images/ConeZombieAttack.gif",
        ":/images/ConeZombieWalk.gif")
