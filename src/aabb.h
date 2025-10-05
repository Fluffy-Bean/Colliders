#ifndef COLLIDERS_AABB_H
#define COLLIDERS_AABB_H

#include "common.h"

typedef enum {
    COLLISION_NONE   = 0b00000000,
    COLLISION_TOP    = 0b00000001,
    COLLISION_BOTTOM = 0b00000010,
    COLLISION_LEFT   = 0b00000100,
    COLLISION_RIGHT  = 0b00001000,
} collision_side_t;

bool             aabb_isColliding(rect_t a, rect_t b);
collision_side_t aabb_getCollisionSide(rect_t a, rect_t b);
collision_side_t aabb_getCollisionSideFromSlope(collision_side_t collision_side, float velocity_slope, float nearest_corner_slope);
Vector2          aabb_getCorrectedLocation(rect_t a, rect_t b, collision_side_t collision_side);
float            aabb_getDistance(rect_t first, rect_t second);
float            aabb_getDistanceSquared(rect_t first, rect_t second);

#endif //COLLIDERS_AABB_H
