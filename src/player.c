#include "player.h"
#include <GLFW/glfw3.h>

#include <stdio.h>

Player new_Player(Vector2 pos){
    Player player = getDefaultPlayer();
    for(int i = 0; i < 32; i ++)
        player.projs[i].index = -1;
    return player;
}


extern Vector2 mouse;
extern int height;
void draw(Player* player){

    glBegin(GL_LINE_STRIP);
        vertex(&player->pos);
        Vector2 vec = mouse;
        setMag(&vec, 40, &player->pos);
        vertex(&vec);
    glEnd();

    {
        unsigned char color = 255 / 10 * player->health; // truly... math!
        glColor3ub(0xff, color, color);

        const int x = 20, y = 20, w = 20, h = 20, o = 4;

        for(int i = 0; i < player->health; i ++){
            glBegin(GL_QUADS);
                glVertex3i(x + w + (w + o) * i,  height - y    ,  -1); // 1 1
                glVertex3i(x     + (w + o) * i,  height - y - h,  -1); // 0 0
                glVertex3i(x     + (w + o) * i,  height - y    ,  -1); // 0 1
                glVertex3i(x + w + (w + o) * i,  height - y - h,  -1); // 1 0
            glEnd();
        }
        glColor3ub(0xff, 0xff, 0xff);
        
    }

    for (int i = 0; i < 32; i ++)
        if (player->projs[i].index > -1) 
            Projectile_do(&player->projs[i]);
}

extern bool gameLost;
extern int SHOT;
void shoot(Player* player){
    if(gameLost == true) return;

    for(int i = 0; i < 32; i ++)
        if(player->projs[i].index == -1) {
            Projectile proj = new_Projectile( player->pos,  _mul(_sub(mouse, player->pos), v(0.01)) , i );
            player->projs[i] = proj;

            SHOT ++;
            break;
        }
}

extern int width, height;
Player getDefaultPlayer(){
    Vector2 pos;
    pos.x = width / 2; pos.y = height / 2;
    Player player;
    player.pos = pos;
    player.health = 10;
    player.dead = false;

    return player;
}