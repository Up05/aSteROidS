#ifndef PLAYER_H
#define PLAYER_H
#include "projectile.h"

typedef struct Player Player;
struct Player {
    Vector2 pos;
    Projectile projs[32];
    int health;
    bool dead;
};

void draw(Player* player);
void shoot(Player* player);
Player new_Player(Vector2 pos);
Player getDefaultPlayer();

#endif
