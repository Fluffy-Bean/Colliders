// Most of the code originates from https://community.monogame.net/t/trouble-with-solid-collision-response/17008/2
// with slight adjustments

#include "stdbool.h"

#include "raylib.h"
#include "raymath.h"

#include "aabb.h"

bool aabb_isColliding(rect_t a, rect_t b)
{
    return rect_right(a) > rect_left(b) &&
           rect_left(a) < rect_right(b) &&
           rect_bottom(a) > rect_top(b) &&
           rect_top(a) < rect_bottom(b);
}

collision_side_t aabb_getCollisionSide(rect_t a, rect_t b)
{
    float corner_slope_rise = 0;
    float corner_slope_run  = 0;

    float velocity_slope = a.vy / a.vx;

    collision_side_t collision_side = COLLISION_NONE;

    if (rect_right(a) <= rect_left(b))
    {
        collision_side  |= COLLISION_LEFT;
        corner_slope_run = rect_left(b) - rect_right(a);

        if (rect_bottom(a) <= rect_top(b))
        {
            collision_side   |= COLLISION_TOP;
            corner_slope_rise = rect_top(b) - rect_bottom(a);
        }
        else if (rect_top(a) >= rect_bottom(b))
        {
            collision_side   |= COLLISION_BOTTOM;
            corner_slope_rise = rect_bottom(b) - rect_top(a);
        }
        else
        {
            return COLLISION_LEFT;
        }
    }
    else if (rect_left(a) >= rect_right(b))
    {
        collision_side  |= COLLISION_RIGHT;
        corner_slope_run = rect_right(b) - rect_left(a);

        if (rect_bottom(a) <= rect_top(b))
        {
            collision_side   |= COLLISION_TOP;
            corner_slope_rise = rect_bottom(a) - rect_top(b);
        }
        else if (rect_top(a) >= rect_bottom(b))
        {
            collision_side   |= COLLISION_BOTTOM;
            corner_slope_rise = rect_top(a) - rect_bottom(b);
        }
        else
        {
            return COLLISION_RIGHT;
        }
    }
    else
    {
        if (rect_bottom(a) <= rect_top(b))
            return COLLISION_TOP;
        else if (rect_top(a) >= rect_bottom(b))
            return COLLISION_BOTTOM;
        else
            return COLLISION_NONE;
    }

    return aabb_getCollisionSideFromSlope(collision_side,
                                          velocity_slope,
                                          corner_slope_rise / corner_slope_run);
}

collision_side_t aabb_getCollisionSideFromSlope(collision_side_t collision_side, float velocity_slope, float nearest_corner_slope)
{
    if ((collision_side & COLLISION_TOP) == COLLISION_TOP)
    {
        if ((collision_side & COLLISION_LEFT) == COLLISION_LEFT)
            return velocity_slope > nearest_corner_slope ? COLLISION_TOP
                                                         : COLLISION_LEFT;
        else if ((collision_side & COLLISION_RIGHT) == COLLISION_RIGHT)
            return velocity_slope < nearest_corner_slope ? COLLISION_TOP
                                                         : COLLISION_RIGHT;
    }
    else if ((collision_side & COLLISION_BOTTOM) == COLLISION_BOTTOM)
    {
        if ((collision_side & COLLISION_LEFT) == COLLISION_LEFT)
            return velocity_slope < nearest_corner_slope ? COLLISION_BOTTOM
                                                         : COLLISION_LEFT;
        else if ((collision_side & COLLISION_RIGHT) == COLLISION_RIGHT)
            return velocity_slope > nearest_corner_slope ? COLLISION_BOTTOM
                                                         : COLLISION_RIGHT;
    }

    return COLLISION_NONE;
}

Vector2 aabb_getCorrectedLocation(rect_t a, rect_t b, collision_side_t collision_side)
{
    Vector2 corrected_location = { a.x, a.y };

    switch (collision_side) {
        case COLLISION_LEFT:   corrected_location.x = b.x - a.w; break;
        case COLLISION_RIGHT:  corrected_location.x = b.x + b.w; break;
        case COLLISION_TOP:    corrected_location.y = b.y - a.h; break;
        case COLLISION_BOTTOM: corrected_location.y = b.y + b.h; break;
    }

    return corrected_location;
}

float aabb_getDistance(rect_t a, rect_t b)
{
    Vector2 a_center = {rect_middleX(a), rect_middleY(a)};
    Vector2 b_center = {rect_middleX(b), rect_middleY(b)};

    return Vector2Distance(a_center, b_center);
}

float aabb_getDistanceSquared(rect_t a, rect_t b)
{
    Vector2 a_center = {rect_middleX(a), rect_middleY(a)};
    Vector2 b_center = {rect_middleX(b), rect_middleY(b)};

    return Vector2DistanceSqr(a_center, b_center);
}
