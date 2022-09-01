#include "explosion.h"
#include "shapes.h"
#include <stdio.h>
Explosion new_Explosion(Vector2 pos, double radius, int state){
    Explosion explosion;
    explosion.pos = pos;
    explosion.max = radius;
    explosion.radius = 0;
    explosion.state = state;
    return explosion;
}

bool Explosion_draw(Explosion* explosion){
    if(explosion->state == 0) return false;
    if(explosion->radius > explosion->max) return true;

    explosion->radius += 4;

    ellipse(explosion->pos, explosion->radius, 8);

    return false;
}