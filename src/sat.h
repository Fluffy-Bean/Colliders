#ifndef COLLIDERS_SAT_H
#define COLLIDERS_SAT_H

#include "common.h"

void    sat_projectToAxis(poly_t polygon, Vector2 axis, float * min_r, float * max_r);
bool    sat_isColliding(poly_t a, poly_t b);
float   sat_getCollisionDepth(poly_t a, poly_t b);
Vector2 sat_getCorrectedLocation(poly_t a, poly_t b, float overlap_depth);

#endif //COLLIDERS_SAT_H