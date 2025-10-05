#ifndef COLLIDERS_COMMON_H
#define COLLIDERS_COMMON_H

#include "stdio.h"
#include "stddef.h"
#include "stdint.h"
#include "stdbool.h"

#include "raylib.h"
#include "raymath.h"

#define G_WHITE (Color){ 239, 239, 239, 255 }
#define G_BLACK (Color){ 44,  44,  44,  255 }
#define G_RED   (Color){ 240, 96,  39,  255 }
#define G_GREEN (Color){ 6,   167, 125, 255 }

#define min(a, b) (a < b ? a : b)
#define max(a, b) (a > b ? a : b)

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
#define rect_middle(r)  ((Vector2){rect_middleX(r), rect_middleY(r)})

typedef struct {
    Vector2   position;
    Vector2 * points;
    size_t    points_count;
} poly_t;

// Get polygon point but wrap it to the start
#define poly_p(p, i) (p.points[(i) % p.points_count])
// Get polygon point but in the global cord space
#define poly_g(p, i) (Vector2Add(p.position, poly_p(p, i)))

#endif
