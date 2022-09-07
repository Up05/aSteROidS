#ifndef VECTOR2_H
#define VECTOR2_H
#include <stdbool.h>

typedef struct Vector2 Vector2;
struct Vector2 {
    double x, y;
};


void add_mut(Vector2* vec, Vector2* vec2);
void sub_mut(Vector2* vec, Vector2* vec2);
void mul_mut(Vector2* vec, Vector2* vec2);

void mul_mutd(Vector2* vec, double ammount);

Vector2 add(Vector2 vec, Vector2 vec2);
Vector2 sub(Vector2 vec, Vector2 vec2);
Vector2 mul(Vector2 vec, Vector2 vec2);
Vector2 muld(Vector2 vec, double ammount);

void vertex(Vector2* vec);

void normalize(Vector2* vec);
void setMag(Vector2* vec, double magnitude, Vector2* pos);

Vector2 centered(Vector2* size);

bool equals(Vector2 vec, Vector2 vec2);

bool isInCenterOfScreen(Vector2 vec, Vector2 size);

Vector2 getMousePos();


Vector2 _normalize(Vector2 vec);
void _vertex(Vector2 vec);

Vector2 _add(Vector2 a, Vector2 b);
Vector2 _sub(Vector2 a, Vector2 b);
Vector2 _mul(Vector2 a, Vector2 b);
Vector2 _setMag(Vector2 vec, double magnitude);
Vector2 v(double a);
Vector2 new_Vector2(double x, double y);
void debug_name(const char* name, Vector2 vec);
Vector2 center(Vector2 pos, Vector2 size);

;;;;
#endif
