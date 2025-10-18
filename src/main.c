#include "common.h"
#include "aabb.h"
#include "sat.h"
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

void ray_draw(ray_t ray)
{
    const int line_length = 20;

    DrawLine(ray.position.x,
             ray.position.y,
             ray.position.x + (ray.direction.x * line_length),
             ray.position.y + (ray.direction.y * line_length),
             G_BLACK);

    DrawCircle(ray.position.x,
               ray.position.y,
               3, // radius
               G_RED);
}

void line_draw(line_t line, Color color)
{
    DrawLine(line.a.x,
             line.a.y,
             line.b.x,
             line.b.y,
             color);
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

    for (size_t i = 0; i < 770; i += 1)
    {
        collider_t c = {0};
        world_AddCollider(&phys_world, c);
    }

	poly_t poly_a = {
		.position = { 200, 200 },
		.points = (Vector2 []){
			{ -50, -50 },
			{ -50, 50 },
			{ 50, 50 },
			{ 50, -50 },
		},
		.points_count = 4,
	};

	poly_t poly_b = {
		.position = { 200, 200 },
		.points = (Vector2 []){
			{ 0, 40 },
			{ 50, -10 },
			{ -50, -10 },
		},
		.points_count = 3,
	};

    while (!WindowShouldClose())
    {
		poly_a.position = GetMousePosition();

		float poly_collision_depth = sat_getCollisionDepth(poly_b, poly_a);
		if (poly_collision_depth > 0)
		{
			Vector2 position = sat_getCorrectedLocation(poly_b, poly_a, poly_collision_depth);
			poly_b.position  = position;
		}

        BeginDrawing();
        ClearBackground(G_WHITE);

		polygon_draw(poly_a, G_RED);
		polygon_draw(poly_b, G_GREEN);

        EndDrawing();
    }

    world_Destroy(&phys_world);

    CloseWindow();
}
