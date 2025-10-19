#include "common.h"
#include "types.h"
#include "physics.h"

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 600
#define PLAYER_SPEED  250

// Inefficient, but its for testing anyways...
void polygon_Draw(polygon_t polygon, Color color)
{
    for (int i = 0; i < polygon.count; i += 1)
    {
		DrawTriangle(polygon.position,
					 polygon_GetPointGlobal(polygon, i),
					 polygon_GetPointGlobal(polygon, i + 1),
					 color);
    }
}

void polygon_DrawLines(polygon_t polygon, Color color)
{
    for (int i = 0; i < polygon.count; i += 1)
    {
    	DrawLineV(polygon_GetPointGlobal(polygon, i),
                  polygon_GetPointGlobal(polygon, i + 1),
                  color);
    }
}

void rect_Draw(rectangle_t rect, Color color)
{
    DrawRectangle(rect.x,
                  rect.y,
                  rect.w,
                  rect.h,
                  color);
}

int main(int argc, char ** argv)
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello, Worm");
    SetTargetFPS(60);

    Camera2D camera = {0};
    camera.offset = (Vector2){ WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 };
    camera.rotation = 0;
    camera.zoom = 1;

    world_t phys_world = {0};
    world_Create(&phys_world);

    for (size_t i = 0; i < 128; i += 1)
    {
		collider_t c = {
            .shape = {
				.position = {
                    .x = GetRandomValue(0, 200),
                    .y = GetRandomValue(0, 200),
			    },
                .points = (Vector2[]){
	                { -25, -25 },
	                { -25, 25 },
	                { 25, 25 },
	                { 25, -25 },
                },
                .count = 4,
			},
			.kind = COLLIDER_KIND_ENTITY,
			.enabled = true,
        };
        world_AddCollider(&phys_world, c);
    }

    for (size_t i = 0; i < 5; i += 1)
    {
		collider_t c = {
            .shape = {
				.position = {
                    .x = 100 * i,
                    .y = 100 * i,
			    },
                .points = (Vector2[]){
	                { -50, -50 },
	                { -50, 50 },
	                { 50, 50 },
                },
                .count = 3,
			},
			.kind = COLLIDER_KIND_STRUCTURE,
			.enabled = true,
        };
        world_AddCollider(&phys_world, c);
    }

	collider_t *collider = collider_array_Get(&phys_world.colliders, 0);

    while (!WindowShouldClose())
    {
        float   player_speed = PLAYER_SPEED * GetFrameTime();
        Vector2 direction    = {0};

        if (IsKeyDown(KEY_W)) direction.y -= 1;
        if (IsKeyDown(KEY_S)) direction.y += 1;
        if (IsKeyDown(KEY_A)) direction.x -= 1;
        if (IsKeyDown(KEY_D)) direction.x += 1;

        direction                = Vector2Scale(Vector2Normalize(direction), player_speed);
        collider->shape.position = Vector2Add(collider->shape.position, direction);

        world_Update(&phys_world, GetFrameTime());

        camera.target = collider->shape.position;

        BeginDrawing();
        ClearBackground(G_WHITE);
        BeginMode2D(camera);

        polygon_Draw(collider->shape, G_RED);
		ARRAY_FOR(phys_world.colliders, i)
	    {
	    	collider_t *collider_i     = collider_array_Get(&phys_world.colliders, i);
            Color       collider_color = collider_i->kind == COLLIDER_KIND_STRUCTURE ? G_BLACK : G_GREEN;

            polygon_DrawLines(collider_i->shape, collider_color);
	    }

        EndMode2D();
        DrawFPS(10, 10);
        EndDrawing();
    }

    world_Destroy(&phys_world);

    CloseWindow();
}
