// Most of the code originates from https://www.youtube.com/watch?v=7Ik2vowGcU0

#include "common.h"
#include "sat.h"

void sat_projectToAxis(poly_t polygon, Vector2 axis, float * min_r, float * max_r)
{
	*min_r = INFINITY;
	*max_r = -INFINITY;

	for (int p = 0; p < polygon.points_count; p += 1)
	{
		float q = Vector2DotProduct(poly_g(polygon, p), axis);

		*min_r = min(*min_r, q);
		*max_r = max(*max_r, q);
	}
}

bool sat_isColliding(poly_t a, poly_t b)
{
	poly_t poly_1 = a;
	poly_t poly_2 = b;

	for (int shape = 0; shape < 2; shape += 1)
	{
		if (shape == 1)
		{
			poly_1 = b;
			poly_2 = a;
		}

		for (int i = 0; i < poly_1.points_count; i += 1)
		{
			Vector2 axis_projection = {-(poly_g(poly_1, i + 1).y - poly_g(poly_1, i).y),
									     poly_g(poly_1, i + 1).x - poly_g(poly_1, i).x};

			float min_r1, max_r1;
			sat_projectToAxis(poly_1, axis_projection, &min_r1, &max_r1);

			float min_r2, max_r2;
			sat_projectToAxis(poly_2, axis_projection, &min_r2, &max_r2);

			if (!(max_r2 >= min_r1 && max_r1 >= min_r2))
				return false;
		}
	}

	return true;
}

float sat_getCollisionDepth(poly_t a, poly_t b)
{
	poly_t poly_1 = a;
	poly_t poly_2 = b;

	float overlap_depth = INFINITY;

	for (int shape = 0; shape < 2; shape += 1)
	{
		if (shape == 1)
		{
			poly_1 = b;
			poly_2 = a;
		}

		for (int i = 0; i < poly_1.points_count; i += 1)
		{
			Vector2 axis_projection = {-(poly_g(poly_1, i + 1).y - poly_g(poly_1, i).y),
									     poly_g(poly_1, i + 1).x - poly_g(poly_1, i).x};

			float min_r1, max_r1;
			sat_projectToAxis(poly_1, axis_projection, &min_r1, &max_r1);

			float min_r2, max_r2;
			sat_projectToAxis(poly_2, axis_projection, &min_r2, &max_r2);

			overlap_depth = min(min(max_r1, max_r2) - max(min_r1, min_r2), overlap_depth);

			if (!(max_r2 >= min_r1 && max_r1 >= min_r2))
				return 0;
		}
	}

	return overlap_depth;
}

Vector2 sat_getCorrectedLocation(poly_t a, poly_t b, float overlap_depth)
{
		Vector2 d = {b.position.x - a.position.x,
					 b.position.y - a.position.y};
		float   s = sqrtf(d.x * d.x + d.y * d.y);

		// ToDo: Why do I need to divide by 100????
		//       This wont work for swept collisions / moving a back towards its previous poisition anyway...
		Vector2 position = a.position;
		position.x      -= (overlap_depth / 100) * d.x / s;
		position.y      -= (overlap_depth / 100) * d.y / s;

		return position;
}
