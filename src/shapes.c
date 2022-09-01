#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <math.h>
#include "shapes.h"

void rect(int x, int y, int w, int h){
    
    int x2 = x + w,
        y2 = y + h; 

    glBegin(GL_QUADS);
        glVertex3i(x,  y,  0);
        glVertex3i(x2, y,  0);
        glVertex3i(x2, y2, 0);
        glVertex3i(x,  y2, 0);
    glEnd();
}

void ellipse(Vector2 pos, double r, double res){
    int vertN = res + 2; 
    // it's supposed to be 1, but it works with 2 and not 1, so I'll just forget about it. I'm pretty sure this is how the mathematicians do it.
    double TWO_PI = 6.283185;

    int* verts = malloc(sizeof(int) * vertN * 2);

    verts[0] = pos.x;
    verts[1] = pos.y;

    for (int i = 1; i < vertN; i ++){
        verts[i * 2]     = (int) round(pos.x + ( r * cos( i * TWO_PI / res ) ));
        verts[i * 2 + 1] = (int) round(pos.y + ( r * sin( i * TWO_PI / res ) ));
    }

    glPushMatrix();
    glBegin(GL_TRIANGLE_FAN);
    for(int i = 0; i < vertN * 2; i += 2)
        glVertex2d(verts[i], verts[i + 1]);
    glEnd();
    glPopMatrix();

    free(verts);

}
extern bool imagesEnabled;
void character(int x, int y, int w, int h, double tx, double ty, double tw, double th, int textureId){
    if(!imagesEnabled){
        glEnable(GL_TEXTURE_2D);
        imagesEnabled = true;
    }

    int x2 = x + w, y2 = y + h;
    double tx2 = tx + tw, ty2 = ty + th;
    // tx2 = 256, ty2 = 256;

    // glColor3ub(255, 0, 255);
    
    // debug_name("x ,y ", new_Vector2(tx, ty));
    // debug_name("x2,y2", new_Vector2(tx2, ty2));
    glBindTexture(GL_TEXTURE_2D, textureId);
    glBegin(GL_QUADS);
        glTexCoord2d(tx, ty);
        glVertex2i(x , y );
        glTexCoord2d(tx2, ty);
        glVertex2i(x2, y );
        glTexCoord2d(tx2, ty2);
        glVertex2i(x2, y2);
        glTexCoord2d(tx, ty2);
        glVertex2i(x , y2);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
}