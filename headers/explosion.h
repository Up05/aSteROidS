#pragma once

#include "vector2.h"

typedef struct Explosion Explosion;
struct Explosion {
    Vector2 pos;
    double radius, max;
    int state;
    bool defined;

};

Explosion new_Explosion(Vector2 pos, double radius, int state);
bool Explosion_draw(Explosion* explosion);