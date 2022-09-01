#pragma once

#include "player.h"

typedef struct Enemy Enemy;
struct Enemy {
    Vector2 pos;
    Vector2 size; // 25x25
    bool dead;
};


void EM_init();
void EM_trySpawn();
void EM_tick();