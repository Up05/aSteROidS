#include "enemy.h"
#include <stdio.h>
#include "stats.h"

extern int width, height;
double randf();
Enemy new_Enemy(){
    Enemy enemy;

    double x, y;
    if(randf() > 0.5) {
        x = randf() * width;
        y = randf() > 0.5 ? 0 : height;
        x = x < width / 2 ? x : x - 25;
        y = y == 0 ? y : y - 25;
    } else {
        x = randf() > 0.5 ? 0 : width;
        y = randf() * height;
        x = x == 0 ? x : x - 25;
        y = y < width / 2 ? y : y - 25;
    } enemy.pos = new_Vector2(x, y);

    enemy.size = new_Vector2(25, 25);
    enemy.dead = false;

    return enemy;
}
void rect(int x, int y, int w, int h);
void Enemy_draw(Enemy enemy){
    if(!enemy.dead)
        rect(enemy.pos.x, enemy.pos.y, enemy.size.x, enemy.size.y);
}

extern bool gameLost;
void Enemy_move(Player* player, Enemy* enemy){
    if(gameLost) return;

    enemy->pos = _add(enemy->pos, _mul(_mul(_normalize(_sub(player->pos, center(enemy->pos, enemy->size))), v(1)), v(SCORE / 2500.0 > 3 ? 4 : SCORE / 2500.0 + 1)));
    enemy->pos.y += 0.5; 

    if(!enemy->dead && isInCenterOfScreen(enemy->pos, enemy->size)) {
        player->health --;
        if(player->health < 1){
            gameLost = true;
        }

        if(!gameLost)
            enemy->dead = true;

    }

}

extern Enemy EM_enemies[48];

void EM_init(){
    for(int i = 0; i < 48; i ++){
        EM_enemies[i] = new_Enemy();
        EM_enemies[i].dead = true;
    }
}

void EM_trySpawn(){
    if(randf() < 0.01 && !gameLost)
        for(int i = 0; i < 48; i ++){
            if(EM_enemies[i].dead){
                EM_enemies[i] = new_Enemy();
                break;
            }
        }
}

extern Player player;
void EM_tick(){
    for(int i = 0; i < 48; i ++){
        if(EM_enemies[i].dead) continue;

        Enemy_draw( EM_enemies[i]);
        Enemy_move(&player, &EM_enemies[i]);



    }

}
