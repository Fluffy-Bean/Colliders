#include "common.h"
#include "aabb.h"
#include "sat.h"

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

    rect_t rect = {
        .x = 100,
        .y = 100,
        .w = 25,
        .h = 25,
    };

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

    rect_t walls[255];
    size_t wall_size = 0;

    for (size_t i = 0; i < 5; i += 1)
    {
        walls[wall_size] = (rect_t){
            .x = 300 + (50 * i),
            .y = 200 + (50 * i),
            .w = 50,
            .h = 50,
        };
        wall_size += 1;
    }

    while (!WindowShouldClose())
    {
		poly_a.position = GetMousePosition();

        rect_t rect_previous = rect;

		Vector2 velocity = Vector2Normalize((Vector2){ rect.vx, rect.vy });
        Vector2 position = Vector2Add((Vector2){ rect.x, rect.y }, Vector2Scale((Vector2){ velocity.x, velocity.y }, PLAYER_SPEED * GetFrameTime()));

        rect.x = position.x;
        rect.y = position.y;

        for (size_t i = 0; i < wall_size; i += 1)
		{
            rect_t target = walls[i];

            if (aabb_isColliding(rect, target))
            {
                collision_side_t collision_side = aabb_getCollisionSide(rect_previous, target);

                Vector2 position = aabb_getCorrectedLocation(rect, target, collision_side);
                rect.x           = position.x;
                rect.y           = position.y;
            }
        }

		float poly_collision_depth = sat_getCollisionDepth(poly_b, poly_a);
		if (poly_collision_depth > 0)
		{
			Vector2 position = sat_getCorrectedLocation(poly_b, poly_a, poly_collision_depth);
			poly_b.position  = position;
		}

        BeginDrawing();
        ClearBackground(G_WHITE);

        rect_draw(rect, G_RED);

        for (size_t i = 0; i < wall_size; i += 1)
		{
            rect_draw(walls[i], G_BLACK);
        }

		polygon_draw(poly_a, G_BLACK);
		polygon_draw(poly_b, G_BLACK);

        EndDrawing();
    }

    CloseWindow();
}
