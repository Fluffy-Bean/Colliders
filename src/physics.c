#include "common.h"
#include "array.h"
#include "physics.h"

IMPLEMENT_ARRAY(collider_t, collider);

void world_Create(world_t *world)
{
    collider_array_Create(&world->colliders);
}

void world_Destroy(world_t *world)
{
    collider_array_Destroy(&world->colliders);
}

void world_Update(world_t *world, float dt)
{}

void world_AddCollider(world_t *world, collider_t item)
{
    collider_array_Push(&world->colliders, item);
}
