#include "common.h"
#include "types.h"
#include "array.h"
#include "sat.h"
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
{
	ARRAY_FOR(world->colliders, i)
	{
		collider_t *collider_i = collider_array_Get(&world->colliders, i);
		if (collider_i->kind == COLLIDER_KIND_STRUCTURE) continue;
		if (!collider_i->enabled)                        continue;

        ARRAY_FOR(world->colliders, j) {
			if (i == j) continue;

			collider_t *collider_j = collider_array_Get(&world->colliders, j);
			if (!collider_j->enabled) continue;

		    float depth = sat_GetCollisionDepth(collider_i->shape, collider_j->shape);
	        if (depth <= 0) continue;

            switch (collider_j->kind) {
				case COLLIDER_KIND_STRUCTURE: {
					collider_i->shape.position = sat_GetCorrectedLocation(collider_i->shape, collider_j->shape, depth);
					break;
				}

				case COLLIDER_KIND_ENTITY: {
					collider_i->shape.position = sat_GetCorrectedLocation(collider_i->shape, collider_j->shape, depth / 2);
					break;
				}

				case COLLIDER_KIND_AREA: {
					 // ToDo: Call a function or something here
					break;
				}
			}
		}
	}
}

void world_AddCollider(world_t *world, collider_t item)
{
    collider_array_Push(&world->colliders, item);
}
