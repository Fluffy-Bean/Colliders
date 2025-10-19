#include "common.h"
#include "physics.h"

#define PLAYER_SPEED 200

// Inefficient, but its for testing anyways...
void polygon_draw(poly_t polygon, Color color)
{
    for (int i = 0; i < polygon.points_count; i += 1)
    {
		DrawTriangle(polygon.position,
					 poly_g(polygon, i),
					 poly_g(polygon, i + 1),
					 color);
    }
}

void polygon_drawLines(poly_t polygon, Color color)
{
    for (int i = 0; i < polygon.points_count; i += 1)
    {
    	DrawLineV(poly_g(polygon, i),
                  poly_g(polygon, i + 1),
                  color);
    }
}

void rect_draw(rect_t rect, Color color)
{
    DrawRectangle(rect.x,
                  rect.y,
                  rect.w,
                  rect.h,
                  color);
}

int main(int argc, char ** argv)
{
    InitWindow(800, 600, "Hello, Worm");
    SetTargetFPS(60);

    world_t phys_world = {0};
    world_Create(&phys_world);

    for (size_t i = 0; i < 128; i += 1)
    {
		collider_t c = {
            .shape = {
				.position = {
                    GetRandomValue(100, 700),
                    GetRandomValue(100, 500),
			    },
                .points = (Vector2[]){
	                { -25, -25 },
	                { -25, 25 },
	                { 25, 25 },
	                { 25, -25 },
                },
                .points_count = 4,
			},
			.kind = COLLIDER_KIND_ENTITY,
			.enabled = true,
        };
        world_AddCollider(&phys_world, c);
    }

	collider_t *collider = collider_array_Get(&phys_world.colliders, 0);
	collider->kind       = COLLIDER_KIND_STRUCTURE;
    while (!WindowShouldClose())
    {
        collider->shape.position = GetMousePosition();

        world_Update(&phys_world, GetFrameTime());

        BeginDrawing();
        ClearBackground(G_WHITE);

		polygon_draw(collider->shape, G_RED);
		for (size_t i = 1; i < phys_world.colliders.count; i += 1)
	    {
	    	collider_t *collider_i = collider_array_Get(&phys_world.colliders, i);
            polygon_draw(collider_i->shape, G_GREEN);
	    }

        EndDrawing();
    }

    world_Destroy(&phys_world);

    CloseWindow();
}
