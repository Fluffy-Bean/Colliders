#include "common.h"
#include "array.h"
#include "sat.h"
#include "physics.h"

IMPLEMENT_ARRAY(poly_t, collider);

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
	for (size_t i = 0; i < world->colliders.count; i += 1)
	{
        for (size_t j = 0; j < world->colliders.count; j += 1)
		{
			if (i == j) continue;

			poly_t *poly_i = collider_array_Get(&world->colliders, i);
			poly_t *poly_j = collider_array_Get(&world->colliders, j);

		    float depth = sat_getCollisionDepth(*poly_i, *poly_j);
	        if (depth > 0)
			{
				// ToDo: I dont like how I have to divide the depth by 2... it doesn't feel right
				poly_i->position = sat_getCorrectedLocation(*poly_i, *poly_j, depth/2);
			}
		}
	}
}

void world_AddCollider(world_t *world, poly_t item)
{
    collider_array_Push(&world->colliders, item);
}
