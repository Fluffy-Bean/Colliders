// Most of the code originates from https://www.youtube.com/watch?v=7Ik2vowGcU0

#include "common.h"
#include "types.h"
#include "sat.h"

void sat_ProjectToAxis(polygon_t polygon, Vector2 axis, float * min_r, float * max_r)
{
    *min_r = INFINITY;
    *max_r = -INFINITY;

    for (size_t p = 0; p < polygon.count; p += 1)
    {
        float q = Vector2DotProduct(polygon_GetPointGlobal(polygon, p), axis);

        *min_r = min(*min_r, q);
        *max_r = max(*max_r, q);
    }
}

Vector2 sat_FindArithmeticMean(polygon_t polygon) {
    float sum_x, sum_y;

    for (size_t i = 0; i < polygon.count; i += 1)
    {
        Vector2 point = polygon_GetPointGlobal(polygon, i);
        sum_x += point.x;
        sum_y += point.y;
    }

    return (Vector2){
        .x = sum_x / polygon.count,
        .y = sum_y / polygon.count,
    };
}

bool sat_TestPolygonPolygon(polygon_t a, polygon_t b, float *depth, Vector2 *normal)
{
	polygon_t poly_1 = a;
	polygon_t poly_2 = b;

	*depth = INFINITY;

    for (size_t i = 0; i < poly_1.count; i += 1)
    {
        Vector2 point_a = polygon_GetPointGlobal(poly_1, i);
        Vector2 point_b = polygon_GetPointGlobal(poly_1, i + 1);

        Vector2 edge = Vector2Subtract(point_a, point_b);
        Vector2 axis = Vector2Normalize((Vector2){-edge.y, edge.x});

        float min_r1, max_r1;
        sat_ProjectToAxis(poly_1, axis, &min_r1, &max_r1);

        float min_r2, max_r2;
        sat_ProjectToAxis(poly_2, axis, &min_r2, &max_r2);

        if (!(max_r2 >= min_r1 && max_r1 >= min_r2))
            return false;

        float axis_depth = min(max_r1, max_r2) - max(min_r1, min_r2);
        if (axis_depth < *depth)
        {
            *depth  = axis_depth;
            *normal = axis;
        }
    }

    for (size_t i = 0; i < poly_2.count; i += 1)
    {
        Vector2 point_a = polygon_GetPointGlobal(poly_2, i);
        Vector2 point_b = polygon_GetPointGlobal(poly_2, i + 1);

        Vector2 edge = Vector2Subtract(point_a, point_b);
        Vector2 axis = Vector2Normalize((Vector2){-edge.y, edge.x});

        float min_r1, max_r1;
        sat_ProjectToAxis(poly_1, axis, &min_r1, &max_r1);

        float min_r2, max_r2;
        sat_ProjectToAxis(poly_2, axis, &min_r2, &max_r2);

        if (!(max_r2 >= min_r1 && max_r1 >= min_r2))
            return false;

        float axis_depth = min(max_r1, max_r2) - max(min_r1, min_r2);
        if (axis_depth < *depth)
        {
            *depth  = axis_depth;
            *normal = axis;
        }
    }

    *depth /= Vector2Length(*normal);
    *normal = Vector2Normalize(*normal);

    Vector2 center_a  = sat_FindArithmeticMean(poly_1);
    Vector2 center_b  = sat_FindArithmeticMean(poly_2);
    Vector2 direction = Vector2Subtract(center_a, center_b);

    if (Vector2DotProduct(direction, *normal) > 0)
        *normal = Vector2Scale(*normal, -1);

	return true;
}
