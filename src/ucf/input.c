#include "input.h"

#include <Runtime/platform.h>

#include <melee/ft/kinds/ftZelda/forward.h>
#include <ucf/forward.h>

#include <dolphin/pad.h>
#include <melee/ft/kinds/ftCommon/ftCo_0A01.h>
#include <melee/ft/types.h>
#include <sysdolphin/baselib/controller.h>
#include <ucf/inlines.h>

typedef struct PadBuffer {
    /* +0 */ S8Vec2 lstick[UCF_PAD_BUFFER_SIZE]; ///< raw, one per frame
    /* +8 */ u8 index;                           ///< entry written this frame
    /* +9 */ u8 guard_pass_frames; ///< frames held in the Guard pass zone
} PadBuffer;

static PadBuffer pad_buffers[4];

static inline PadBuffer* getPadBuffer(Fighter* fp)
{
    return &pad_buffers[fp->x618_player_id];
}

/// @param offset Frames from the current one; 0 or negative.
static inline S8Vec2* getRawLstick(Fighter* fp, int offset)
{
    PadBuffer* buf = getPadBuffer(fp);
    return &buf->lstick[(buf->index + offset) & UCF_PAD_BUFFER_MASK];
}

/// #HSD_PadGameStatus is no use here as it has been through #HSD_PadClamp.
static inline PADStatus* getRawPad(Fighter* fp)
{
    PadLibData* p = &HSD_PadLibData;
    u8 idx = (p->qread + p->qnum - 1) % p->qnum;
    return &p->queue[idx].stat[fp->x618_player_id];
}

static inline bool canSnapToCardinal(Fighter* fp)
{
    switch (fp->kind) {
    case Ft_Kind_Zelda:
        return fp->motion_id != ftZd_MS_SpecialHiStart_0;
    default:
        return true;
    }
}

static inline void snapToCardinal(S8Vec2* raw, Vec2* stick)
{
    if (ABS(raw->x) >= UCF_STICK_MAX && ABS(raw->y) <= UCF_CARDINAL_RANGE) {
        stick->x = raw->x < 0 ? -1.0f : 1.0f;
        stick->y = 0.0f;
    } else if (ABS(raw->y) >= UCF_STICK_MAX &&
               ABS(raw->x) <= UCF_CARDINAL_RANGE)
    {
        stick->x = 0.0f;
        stick->y = raw->y < 0 ? -1.0f : 1.0f;
    }
}

static inline bool checkGuardPass(Fighter* fp)
{
    if (fp->input.lstick[0].y > UCF_GUARD_PASS_MAX_Y ||
        !ucfIsRimCoord(&fp->input.lstick[0]))
    {
        return false;
    }
    return getPadBuffer(fp)->guard_pass_frames != 0 ||
           (fp->active_timer.lstick.y < 2 &&
            ucfCheckTravel(0, ucfInput_GetTravelY(fp), UCF_GUARD_PASS_TRAVEL));
}

void ucfInput_Update(Fighter* fp)
{
    PadBuffer* buf;
    PADStatus* raw;

    if (ftCo_IsCpuControlled(fp)) {
        return;
    }

    raw = getRawPad(fp);
    buf = getPadBuffer(fp);
    buf->index = (buf->index + 1) & UCF_PAD_BUFFER_MASK;
    buf->lstick[buf->index] = *(S8Vec2*) &raw->stickX;

    if (canSnapToCardinal(fp)) {
        snapToCardinal((S8Vec2*) &raw->stickX, &fp->input.lstick[0]);
        snapToCardinal((S8Vec2*) &raw->substickX, &fp->input.cstick[0]);
    }

    /// After the snap, which can move the lstick onto the rim.
    if (checkGuardPass(fp)) {
        buf->guard_pass_frames++;
    } else {
        buf->guard_pass_frames = 0;
    }
}

int ucfInput_GetTravelX(Fighter* fp)
{
    return getRawLstick(fp, 0)->x - getRawLstick(fp, -2)->x;
}

int ucfInput_GetTravelY(Fighter* fp)
{
    return getRawLstick(fp, 0)->y - getRawLstick(fp, -2)->y;
}

u8 ucfInput_GetPassFrames(Fighter* fp)
{
    return getPadBuffer(fp)->guard_pass_frames;
}
