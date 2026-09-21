#include "dashback.h"

#include <Runtime/platform.h>

#include <ucf/forward.h>

#include "input.h"
#include <melee/ft/fighter.h>
#include <melee/ft/inlines.h>
#include <melee/ft/types.h>
#include <melee/pl/player.h>
#include <ucf/inlines.h>

bool ucfTurn_CheckSmash(Fighter* fp)
{
    Fighter_GObj* nana_gobj;

    /// The caller has already flipped #Fighter::facing_dir.
    if (fp->is_sub_fighter || fp->cur_anim_frame != 2.0f ||
        fp->input.lstick[0].x * fp->facing_dir <
            p_ftCommonData->dash_smash_stick_threshold ||
        fp->active_timer.lstick.x >= 2 ||
        !ucfCheckTravel(ucfInput_GetTravelX(fp), 0, UCF_SMASH_TRAVEL))
    {
        return false;
    }

    fp->mv.co.turn.has_turned = true;
    fp->mv.co.turn.just_turned = true;

    /// Nana replays recorded inputs.
    nana_gobj = Player_GetEntityAtIndex(fp->player_id, 1);
    if (nana_gobj != NULL) {
        Fighter* nana = GET_FIGHTER(nana_gobj);
        nana->cpu.x448->facing_dir = fp->facing_dir;
        nana->cpu.x448->lstick.x = fp->facing_dir < 0.0f ? -128 : 127;
    }
    return true;
}

float ucfSquatRv_GetThreshold(Fighter* fp)
{
    if (fp->active_timer.lstick.x < 1 && ucfIsRimCoord(&fp->input.lstick[0])) {
        return UCF_SQUATRV_THRESHOLD;
    }
    return p_ftCommonData->x94;
}
