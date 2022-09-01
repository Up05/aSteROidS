#include <math.h>
#include "vector2.h"
#include <GLFW/glfw3.h>
#include <stdio.h>

/** @deprecated */
Vector2 clone(Vector2* vec){
    Vector2 _vec;
    _vec.x = vec->x;
    _vec.y = vec->y;
    return _vec;
}
void add_mut(Vector2* vec, Vector2* vec2){
    vec->x += vec2->x;
    vec->y += vec2->y;
}
void sub_mut(Vector2* vec, Vector2* vec2){
    vec->x -= vec2->x;
    vec->y -= vec2->y;
}
void mul_mut(Vector2* vec, Vector2* vec2){
    vec->x *= vec2->x;
    vec->y *= vec2->y;
}
void mul_mutd(Vector2* vec, double ammount){
    vec->x *= ammount;
    vec->y *= ammount;
}

Vector2 add(Vector2 vec, Vector2 vec2){
    Vector2 _vec;
    _vec.x = vec.x + vec2.x;
    _vec.y = vec.y + vec2.y;
    return _vec;
}
Vector2 sub(Vector2 vec, Vector2 vec2){
    Vector2 _vec;
    _vec.x = vec.x - vec2.x;
    _vec.y = vec.y - vec2.y;
    return _vec;
}
Vector2 mul(Vector2 vec, Vector2 vec2){
    Vector2 _vec;
    _vec.x = vec.x * vec2.x;
    _vec.y = vec.y * vec2.y;
    return _vec;
}
Vector2 muld(Vector2 vec, double ammount){
    Vector2 _vec;
    _vec.x = vec.x * ammount;
    _vec.y = vec.y * ammount;
    return _vec;
}

// void glVertex2d(double x, double y);
void vertex(Vector2* vec){
    glVertex2d(vec->x, vec->y);
}

void normalize(Vector2* vec){
    double a = sqrt(vec->x*vec->x + vec->y*vec->y);
    vec->x /= a;
    vec->y /= a;
}


void setMag(Vector2* vec, double magnitude, Vector2* pos){
    sub_mut(vec, pos);
    normalize(vec);
    mul_mutd(vec, magnitude);
    add_mut(vec, pos);
}

Vector2 centered(Vector2* size){
    Vector2 _vec;
    _vec.x += size->x / 2;
    _vec.y += size->y / 2;
    return _vec;
}

bool equals(Vector2 vec, Vector2 vec2){
    return (vec.x == vec2.y && vec.y == vec2.y);
}

extern int width, height;
bool isInCenterOfScreen(Vector2 vec, Vector2 size){
    int hw = width / 2, hh = height / 2;
    int w = (int) size.x, h = (int) size.y;

    return 
        hw >= vec.x &&
        hw <= vec.x + w &&
        hh >= vec.y &&
        hh <= vec.y + h;
}

Vector2 _normalize(Vector2 vec){
    double a = sqrt(vec.x*vec.x + vec.y*vec.y);
    vec.x /= a;
    vec.y /= a;
    return vec;
}

void _vertex(Vector2 vec){
    glVertex2d(vec.x, vec.y);
}

Vector2 v(double a){
    Vector2 _ = {a, a};
    return _;
}

Vector2 new_Vector2(double x, double y){
    Vector2 _ = {x, y};
    return _;
}

Vector2 _add(Vector2 a, Vector2 b){
    a.x += b.x;
    a.y += b.y;
    return a;
}

Vector2 _sub(Vector2 a, Vector2 b){
    a.x -= b.x;
    a.y -= b.y;
    return a;
}

Vector2 _mul(Vector2 a, Vector2 b){
    a.x *= b.x;
    a.y *= b.y;
    return a;
}

Vector2 _setMag(Vector2 vec, double magnitude){

    // vec = _sub(pos, vec); // ! might be wrong!
    vec = _normalize(vec);
    vec = _mul(vec, v(magnitude));
    // vec = add(vec, pos);

    return vec;
}

void debug_name(const char* name, Vector2 vec){
    printf("%s: x: %f, y: %f\n", name, vec.x, vec.y);
}


Vector2 center(Vector2 pos, Vector2 size){
    return new_Vector2(pos.x + size.x/2, pos.y + size.y/2);
}