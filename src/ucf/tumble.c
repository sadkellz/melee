#include "tumble.h"

#include <Runtime/platform.h>

#include <ucf/forward.h>

#include "input.h"
#include <melee/ft/fighter.h>
#include <melee/ft/types.h>
#include <ucf/inlines.h>

bool ucfDamageFall_CheckInput(Fighter* fp)
{
    return fp->active_timer.lstick.x == 1 &&
           ABS(fp->input.lstick[1].x) < p_ftCommonData->x210 &&
           ucfCheckTravel(ucfInput_GetTravelX(fp), 0, UCF_SMASH_TRAVEL);
}
