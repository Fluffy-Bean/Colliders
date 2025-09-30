#include "stdio.h"
#include "stdbool.h"
#include "raylib.h"
#include "raymath.h"

#define G_WHITE (Color){ 239, 239, 239, 255 }
#define G_BLACK (Color){ 44,  44,  44,  255 }
#define G_RED   (Color){ 240, 96,  39,  255 }
#define G_GREEN (Color){ 6,   167, 125, 255 }

typedef struct {
    Vector2 position;
    Vector2 direction;
} ray_t;

typedef struct {
    Vector2 a;
    Vector2 b;
} line_t;

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

void line_draw(line_t line)
{
    DrawLine(line.a.x,
             line.a.y,
             line.b.x,
             line.b.y,
             G_BLACK);
}

typedef struct {
    Vector2 point;
    bool    hit;
} line_projection_result_t;

line_projection_result_t line_projectPoint(line_t line, Vector2 point)
{
    float abx = line.b.x - line.a.x;
    float aby = line.b.y - line.a.y;
    float acx = point.x - line.a.x;
    float acy = point.y - line.a.y;

    float coeff = (abx * acx + aby * acy) /
                  (abx * abx + aby * aby);
    float dx    = line.a.x + abx * coeff;
    float dy    = line.a.y + aby * coeff;

    bool hit = (coeff >= 0.0f - EPSILON) &&
               (coeff <= 1.0f + EPSILON);

    return (line_projection_result_t){
        .point = { dx, dy },
        .hit   = hit,
    };
}

int main(int argc, char ** argv)
{
    InitWindow(800, 600, "Hello, Worm");
    SetTargetFPS(60);

    ray_t ray = {
        .position  = { 400, 200 },
        .direction = { 0.5, 1 },
    };

    line_t line = {
        .a = { 100, 300 },
        .b = { 600, 500 },
    };

    while (!WindowShouldClose())
    {
        ray.position = Vector2Add(ray.position, Vector2Scale(ray.direction, 30 * GetFrameTime()));

        line_projection_result_t res = line_projectPoint(line, ray.position);

        Vector2 to_projection = Vector2Normalize((Vector2){ res.point.x - ray.position.x, res.point.y - ray.position.y });

        if (Vector2DotProduct(ray.direction, to_projection) < 0 && res.hit) {
            ray.position = res.point;
        }

        BeginDrawing();
        ClearBackground(G_WHITE);

        ray_draw(ray);
        line_draw(line);

        if (res.hit) {
            const int line_length = 20;

            DrawLine(res.point.x,
                     res.point.y,
                     res.point.x + (to_projection.x * line_length),
                     res.point.y + (to_projection.y * line_length),
                     G_BLACK);
            DrawCircle(res.point.x,
                       res.point.y,
                       3, // radius
                       G_GREEN);
        }

        EndDrawing();
    }

    CloseWindow();    
}

