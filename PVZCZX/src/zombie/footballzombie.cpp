#include "footballzombie.h"

FootballZombie::FootballZombie()
{
    hp = hp_FootballZombie;
    atk = atk_Zombie;
    speed = speed_zombie_2;
    setMovie(":/images/FootballZombieWalk.gif");
}

void FootballZombie::advance(int phase)
ZOMBIE_ADVANCE(
        ":/images/FootballZombieDie.gif",
        ":/images/ZombieHead.gif",
        ":/images/FootballZombieAttack.gif",
        ":/images/FootballZombieWalk.gif")
