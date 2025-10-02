#ifndef COLLIDERS_COMMON_H
#define COLLIDERS_COMMON_H

#define G_WHITE (Color){ 239, 239, 239, 255 }
#define G_BLACK (Color){ 44,  44,  44,  255 }
#define G_RED   (Color){ 240, 96,  39,  255 }
#define G_GREEN (Color){ 6,   167, 125, 255 }

typedef struct {
    Vector2 position;
    Vector2 direction;
} ray_t;

typedef struct {
    Vector2 a;
    Vector2 b;
} line_t;

typedef struct {
    float x,  y;
    float w,  h;
    float vx, vy;
} rect_t;

#define rect_left(r)    (r.x)
#define rect_right(r)   (r.x + r.w)
#define rect_top(r)     (r.y)
#define rect_bottom(r)  (r.y + r.h)
#define rect_middleX(r) (r.x + (r.w / 2))
#define rect_middleY(r) (r.y + (r.h / 2))

#endif
