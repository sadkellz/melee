#ifndef UCF_INPUT_H
#define UCF_INPUT_H

#include <Runtime/platform.h>

#include <melee/ft/forward.h>

/// #Fighter_procInput
void ucfInput_Update(Fighter* fp);

/// Raw lstick travel over two frames.
int ucfInput_GetTravelX(Fighter* fp);
int ucfInput_GetTravelY(Fighter* fp);

/// Frames the lstick has been held in the Guard pass zone.
u8 ucfInput_GetPassFrames(Fighter* fp);

#endif
