#pragma once

typedef struct {
    float x,  y;
    float w,  h;
    float vx, vy;
} rectangle_t;

#define rectangle_GetLeft(RECTANGLE)    (RECTANGLE.x)
#define rectangle_GetRight(RECTANGLE)   (RECTANGLE.x + RECTANGLE.w)
#define rectangle_GetTop(RECTANGLE)     (RECTANGLE.y)
#define rectangle_GetBottom(RECTANGLE)  (RECTANGLE.y + RECTANGLE.h)
#define rectangle_GetMiddleX(RECTANGLE) (RECTANGLE.x + (RECTANGLE.w / 2))
#define rectangle_GetMiddleY(RECTANGLE) (RECTANGLE.y + (RECTANGLE.h / 2))
#define rectangle_GetMiddle(RECTANGLE)  ((Vector2){rectangle_GetMiddleX(RECTANGLE), rectangle_GetMiddleY(RECTANGLE)})

typedef struct {
    Vector2  position;
    Vector2 *points;
    size_t   count;
} polygon_t;

#define polygon_GetPoint(POLYGON, INDEX) (POLYGON.points[(INDEX) % POLYGON.count])
#define polygon_GetPointGlobal(POLYGON, INDEX) (Vector2Add(POLYGON.position, polygon_GetPoint(POLYGON, INDEX)))
