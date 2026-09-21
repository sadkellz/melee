#ifndef UCF_INLINES_H
#define UCF_INLINES_H

#include <Runtime/platform.h>

#include <ucf/forward.h>

#include <dolphin/mtx.h>

static inline bool ucfCheckTravel(int dx, int dy, int min)
{
    return dx * dx + dy * dy > min * min;
}

/// The bias makes Popo's coords round the same as Nana's.
static inline int ucfCoordToInt(float x)
{
    return (int) (ABS(x) * (float) UCF_STICK_MAX - 0.0001f) + 1;
}

static inline bool ucfIsRimCoord(Vec2* stick)
{
    int x = ucfCoordToInt(stick->x) + 1;
    int y = ucfCoordToInt(stick->y) + 1;
    return x * x + y * y > UCF_STICK_MAX * UCF_STICK_MAX;
}

#endif
