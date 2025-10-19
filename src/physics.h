#pragma once

#include "common.h"
#include "array.h"

DEFINE_ARRAY(poly_t, collider);

typedef struct {
    collider_array_t colliders;
} world_t;

void world_Create(world_t *world);
void world_Destroy(world_t *world);
void world_Update(world_t *world, float dt);
void world_AddCollider(world_t *world, poly_t item);
