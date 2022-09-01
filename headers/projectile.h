#ifndef PROJECTILE_H
#define PROJECTILE_H

// #include "vector2.h"
#include "explosion.h"

typedef struct Projectile Projectile;
struct Projectile {
    Vector2 pos;
    Vector2 vel;
    Explosion explosion;
    int index;
    bool dead, collided, shouldDraw;

};

void Projectile_do(Projectile* projectile);
Projectile new_Projectile(Vector2 pos, Vector2 vel, double index);

#endif
