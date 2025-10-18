#pragma once

#include "common.h"
#include "array.h"

typedef struct {
    bool    active;
    Vector2 position;
    poly_t  shape;
    rect_t  bounding_box;
} collider_t;

DEFINE_ARRAY(collider_t, collider);

typedef struct {
    collider_array_t colliders;
} world_t;

void world_Create(world_t *world);
void world_Destroy(world_t *world);
void world_Update(world_t *world, float dt);
void world_AddCollider(world_t *world, collider_t item);
