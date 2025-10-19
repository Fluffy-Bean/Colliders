#pragma once

#include "common.h"
#include "types.h"

typedef enum {
    COLLISION_NONE   = 0b00000000,
    COLLISION_TOP    = 0b00000001,
    COLLISION_BOTTOM = 0b00000010,
    COLLISION_LEFT   = 0b00000100,
    COLLISION_RIGHT  = 0b00001000,
} collision_side_t;

bool             aabb_IsColliding(rectangle_t a, rectangle_t b);
collision_side_t aabb_GetCollisionSide(rectangle_t a, rectangle_t b);
Vector2          aabb_GetCorrectedLocation(rectangle_t a, rectangle_t b, collision_side_t collision_side);
