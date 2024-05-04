#include "bucketzombie.h"

BucketZombie::BucketZombie()
{
    hp = hp_BucketZombie;
    atk = atk_Zombie;
    speed = speed_zombie_1;
    setMovie(":/images/BucketZombieWalk.gif");
}


void BucketZombie::advance(int phase)
 //宏定义
ZOMBIE_ADVANCE(
        ":/images/ZombieDie.gif",
        ":/images/ZombieHead.gif",
        ":/images/BucketZombieAttack.gif",
        ":/images/BucketZombieWalk.gif")
