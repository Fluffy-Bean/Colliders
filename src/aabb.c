// Most of the code originates from https://community.monogame.net/t/trouble-with-solid-collision-response/17008/2
// with slight adjustments

#include "common.h"
#include "aabb.h"

bool aabb_IsColliding(rectangle_t a, rectangle_t b)
{
    return rectangle_GetRight(a) > rectangle_GetLeft(b) &&
           rectangle_GetLeft(a) < rectangle_GetRight(b) &&
           rectangle_GetBottom(a) > rectangle_GetTop(b) &&
           rectangle_GetTop(a) < rectangle_GetBottom(b);
}

collision_side_t aabb_GetCollisionSideFromSlope(collision_side_t collision_side, float velocity_slope, float nearest_corner_slope)
{
    if ((collision_side & COLLISION_TOP) == COLLISION_TOP)
    {
        if ((collision_side & COLLISION_LEFT) == COLLISION_LEFT)
            return velocity_slope > nearest_corner_slope ? COLLISION_TOP : COLLISION_LEFT;
        else if ((collision_side & COLLISION_RIGHT) == COLLISION_RIGHT)
            return velocity_slope < nearest_corner_slope ? COLLISION_TOP : COLLISION_RIGHT;
    }
    else if ((collision_side & COLLISION_BOTTOM) == COLLISION_BOTTOM)
    {
        if ((collision_side & COLLISION_LEFT) == COLLISION_LEFT)
            return velocity_slope < nearest_corner_slope ? COLLISION_BOTTOM : COLLISION_LEFT;
        else if ((collision_side & COLLISION_RIGHT) == COLLISION_RIGHT)
            return velocity_slope > nearest_corner_slope ? COLLISION_BOTTOM : COLLISION_RIGHT;
    }

    return COLLISION_NONE;
}

collision_side_t aabb_GetCollisionSide(rectangle_t a, rectangle_t b)
{
    float corner_slope_rise = 0;
    float corner_slope_run  = 0;

    float velocity_slope = a.vy / a.vx;

    collision_side_t collision_side = COLLISION_NONE;

    if (rectangle_GetRight(a) <= rectangle_GetLeft(b))
    {
        collision_side  |= COLLISION_LEFT;
        corner_slope_run = rectangle_GetLeft(b) - rectangle_GetRight(a);

        if (rectangle_GetBottom(a) <= rectangle_GetTop(b))
        {
            collision_side   |= COLLISION_TOP;
            corner_slope_rise = rectangle_GetTop(b) - rectangle_GetBottom(a);
        }
        else if (rectangle_GetTop(a) >= rectangle_GetBottom(b))
        {
            collision_side   |= COLLISION_BOTTOM;
            corner_slope_rise = rectangle_GetBottom(b) - rectangle_GetTop(a);
        }
        else
        {
            return COLLISION_LEFT;
        }
    }
    else if (rectangle_GetLeft(a) >= rectangle_GetRight(b))
    {
        collision_side  |= COLLISION_RIGHT;
        corner_slope_run = rectangle_GetRight(b) - rectangle_GetLeft(a);

        if (rectangle_GetBottom(a) <= rectangle_GetTop(b))
        {
            collision_side   |= COLLISION_TOP;
            corner_slope_rise = rectangle_GetBottom(a) - rectangle_GetTop(b);
        }
        else if (rectangle_GetTop(a) >= rectangle_GetBottom(b))
        {
            collision_side   |= COLLISION_BOTTOM;
            corner_slope_rise = rectangle_GetTop(a) - rectangle_GetBottom(b);
        }
        else
        {
            return COLLISION_RIGHT;
        }
    }
    else
    {
        if (rectangle_GetBottom(a) <= rectangle_GetTop(b))
            return COLLISION_TOP;
        else if (rectangle_GetTop(a) >= rectangle_GetBottom(b))
            return COLLISION_BOTTOM;
        else
            return COLLISION_NONE;
    }

    return aabb_GetCollisionSideFromSlope(collision_side, velocity_slope, corner_slope_rise / corner_slope_run);
}

Vector2 aabb_GetCorrectedLocation(rectangle_t a, rectangle_t b, collision_side_t collision_side)
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
