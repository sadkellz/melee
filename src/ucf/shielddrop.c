#include "shielddrop.h"

#include <Runtime/platform.h>

#include <melee/mp/forward.h>
#include <ucf/forward.h>

#include "input.h"
#include <melee/ft/fighter.h>
#include <melee/ft/types.h>
#include <melee/mp/mpcoll.h>
#include <ucf/inlines.h>

/// Whether a spot dodge input is really a shield drop.
bool ucfEscape_IsPassInput(Fighter* fp)
{
    return fp->input.cstick[0].y > p_ftCommonData->x314 &&
           fp->active_timer.lstick.x >= p_ftCommonData->x320 &&
           fp->input.lstick[0].y > UCF_ESCAPEN_PASS_MIN_Y &&
           fp->coll_data.floor.index != -1 &&
           fp->coll_data.floor.flags & LINE_FLAG_PLATFORM &&
           ucfIsRimCoord(&fp->input.lstick[0]);
}

bool ucfPass_CheckGuardInput(Fighter* fp)
{
    return ucfInput_GetPassFrames(fp) >= 2 &&
           fp->active_timer.lstick.y < p_ftCommonData->x468 &&
           mpColl_IsOnPlatform(&fp->coll_data);
}
