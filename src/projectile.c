#include "projectile.h"
#include <GLFW/glfw3.h>
#include <stdio.h>
void Projectile_move(Projectile* projectile){
    add_mut(&projectile->pos, &projectile->vel);
}

void Projectile_draw(Projectile* projectile){
    if(projectile->explosion.state == 1){
        projectile->dead = Explosion_draw(&projectile->explosion);
        if(projectile->dead)
            projectile->index = -1;
    }
    if(!projectile->shouldDraw) return;

    glBegin(GL_LINE_STRIP);
        glColor4f(1, 1, 1, 0.5);
        vertex(&projectile->pos);
        glColor4f(1, 1, 1, 1);
        _vertex( _add(_setMag(projectile->vel, 20), projectile->pos) );
    glEnd();
}

extern int width, height, MISSED;
void ellipse(Vector2 pos, double r, double res);
void Projectile_offscreen(Projectile* projectile){
    if(projectile->explosion.state == 1) return;

    Vector2 temp = _add(_setMag(projectile->vel, 20), projectile->pos);
    double 
        x = temp.x,
        y = temp.y;

    if(x < 0 || y < 0 || x > width || y > height) {
        MISSED ++;
        projectile->shouldDraw = false;
        projectile->explosion = new_Explosion(temp, 31, 1);
    }
}

typedef struct Enemy Enemy;
struct Enemy {
    Vector2 pos;
    Vector2 size; // 25x25
    bool dead;
};
extern Enemy EM_enemies[48];
extern int SCORE;
void Projectile_hasCollided(Projectile* projectile){

        if(projectile->explosion.state == 1)
            return;

        _add(projectile->pos, _mul(projectile->vel, v(10)));
        for(int i = 0; i < 48; i ++){
            if(EM_enemies[i].dead) continue;
            double px = projectile->pos.x, py = projectile->pos.y, 
            rx = EM_enemies[i].pos.x, ry = EM_enemies[i].pos.y, rw = EM_enemies[i].size.x, rh = EM_enemies[i].size.y;

            if(px >= rx &&         // right of the left edge AND
               px <= rx + rw &&    // left of the right edge AND
               py >= ry &&         // below the top AND
               py <= ry + rh 
            ) {
                EM_enemies[i].dead = true;
                projectile->explosion = new_Explosion(projectile->pos, 47, 1);
                projectile->collided = true;
                projectile->shouldDraw = false;
                SCORE += 10;
            }
        }
        _sub(projectile->pos, _mul(projectile->vel, v(10)));
    }

void Projectile_do(Projectile* projectile){
    Projectile_move(projectile);
    Projectile_offscreen(projectile);
    Projectile_draw(projectile);
    Projectile_hasCollided(projectile);
}

Projectile new_Projectile(Vector2 pos, Vector2 vel, double index){
    Projectile projectile;
    projectile.pos = pos;
    projectile.vel = vel;
    projectile.index = index;
    projectile.shouldDraw = true;
    projectile.explosion = new_Explosion(pos, 5, 0);
    return projectile;
}