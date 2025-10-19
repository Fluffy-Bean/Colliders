#pragma once

#include "common.h"
#include "types.h"

#define sat_IsColliding(a, b) (sat_getCollisionDepth(a, b) > 0)

float   sat_GetCollisionDepth(polygon_t a, polygon_t b);
Vector2 sat_GetCorrectedLocation(polygon_t a, polygon_t b, float overlap_depth);
