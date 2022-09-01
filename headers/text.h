#pragma once

#include "vector2.h"

typedef struct Text Text;
struct Text {
    Vector2 pos;
    int cs; // character spacing
    bool shouldCenter;
    char text[64];
};

Text new_Text(char* str, Vector2 pos);
void Text_init();
void Text_draw(Text text);