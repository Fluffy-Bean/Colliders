#pragma once

#include "common.h"
#include "array.h"

typedef enum {
	COLLIDER_KIND_STRUCTURE, // Not movable
	COLLIDER_KIND_ENTITY,    // Affected by other forces
	COLLIDER_KIND_AREA,      // Callback on touch
} collider_kind_t;

typedef struct {
	collider_kind_t kind;
	polygon_t       shape;   // Currently holds the position
	bool            enabled;
} collider_t;

DEFINE_ARRAY(collider_t, collider);

typedef struct {
    collider_array_t colliders;
} world_t;

void world_Create(world_t *world);
void world_Destroy(world_t *world);
void world_Update(world_t *world, float dt);
void world_AddCollider(world_t *world, collider_t item);
