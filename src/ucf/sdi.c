#include "sdi.h"

#include <Runtime/platform.h>

#include <ucf/forward.h>

#include "input.h"
#include <melee/ft/fighter.h>
#include <melee/ft/types.h>
#include <sysdolphin/baselib/mtx.h>
#include <ucf/inlines.h>

bool ucfDamage_CheckSDI(Fighter* fp)
{
    return (fp->active_sticky.lstick.x < 2 ||
            fp->active_sticky.lstick.y < 2) &&
           VEC2_SQ_LEN(fp->input.lstick[1]) <
               SQ(p_ftCommonData->sdi_min_stick_mag) &&
           ucfCheckTravel(ucfInput_GetTravelX(fp), ucfInput_GetTravelY(fp),
                          UCF_SDI_TRAVEL);
}

bool ucfGuard_CheckSDI(Fighter* fp)
{
    return fp->active_sticky.lstick.x < 2 &&
           fp->input.lstick[1].x < p_ftCommonData->sdi_min_stick_mag &&
           ucfCheckTravel(ucfInput_GetTravelX(fp), 0, UCF_SDI_TRAVEL);
}
