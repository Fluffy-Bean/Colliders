#ifndef COLLIDERS_SAT_H
#define COLLIDERS_SAT_H

#include "common.h"

#define sat_isColliding(a, b) (sat_getCollisionDepth(a, b) > 0)

float   sat_getCollisionDepth(poly_t a, poly_t b);
void    sat_projectToAxis(poly_t polygon, Vector2 axis, float * min_r, float * max_r);
Vector2 sat_getCorrectedLocation(poly_t a, poly_t b, float overlap_depth);

#endif //COLLIDERS_SAT_H