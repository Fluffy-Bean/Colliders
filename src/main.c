#include "stdio.h"
#include "stdbool.h"

#include "raylib.h"
#include "raymath.h"

#include "common.h"
#include "aabb.h"

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

    rect_t rect_a = {
        .x = 100,
        .y = 100,
        .w = 25,
        .h = 25,
    };

    rect_t walls[255];
    size_t wall_size = 0;

    for (size_t i = 0; i < 12; i += 1) {
        walls[wall_size] = (rect_t){
            .x = 0,
            .y = (50 * i),
            .w = 50,
            .h = 50,
        };
        wall_size += 1;
    }

    for (size_t i = 0; i < 12; i += 1) {
        walls[wall_size] = (rect_t){
            .x = 750,
            .y = (50 * i),
            .w = 50,
            .h = 50,
        };
        wall_size += 1;
    }

    for (size_t i = 0; i < 14; i += 1) {
        walls[wall_size] = (rect_t){
            .x = 50 + (50 * i),
            .y = 0,
            .w = 50,
            .h = 50,
        };
        wall_size += 1;
    }

    for (size_t i = 0; i < 14; i += 1) {
        walls[wall_size] = (rect_t){
            .x = 50 + (50 * i),
            .y = 550,
            .w = 50,
            .h = 50,
        };
        wall_size += 1;
    }

    while (!WindowShouldClose())
    {
        rect_a.vx = 0;
        rect_a.vy = 0;

        if (IsKeyDown(KEY_W)) rect_a.vy -= 1;
        if (IsKeyDown(KEY_S)) rect_a.vy += 1;
        if (IsKeyDown(KEY_A)) rect_a.vx -= 1;
        if (IsKeyDown(KEY_D)) rect_a.vx += 1;

        Vector2 velocity = Vector2Normalize((Vector2){ rect_a.vx, rect_a.vy });
        rect_a.vx        = velocity.x;
        rect_a.vy        = velocity.y;

        rect_t rect_a_previous = rect_a;

        float player_speed = 200 * GetFrameTime();

        Vector2 position = Vector2Add((Vector2){ rect_a.x, rect_a.y }, Vector2Scale((Vector2){ rect_a.vx, rect_a.vy }, player_speed));
        rect_a.x         = position.x;
        rect_a.y         = position.y;

        for (size_t i = 0; i < wall_size; i += 1) {
            rect_t target = walls[i];

            if (aabb_isColliding(rect_a, target))
            {
                collision_side_t collision_side = aabb_getCollisionSide(rect_a_previous, target);

                Vector2 position = aabb_getCorrectedLocation(rect_a, target, collision_side);
                rect_a.x         = position.x;
                rect_a.y         = position.y;
            }
        }

        BeginDrawing();
        ClearBackground(G_WHITE);

        rect_draw(rect_a, G_RED);

        for (size_t i = 0; i < wall_size; i += 1) {
            rect_draw(walls[i], G_BLACK);
        }

        EndDrawing();
    }

    CloseWindow();
}
