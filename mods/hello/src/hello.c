#include <platform.h>

#include <dolphin/os.h>
#include <baselib/random.h>

/// Static in gm_1A3F.c, so no game header declares it; without a prototype
/// the call would compile as an implicit int(int) declaration.
u8 runGameMode(u8 mode_kind);

/// Full replacement
f32 HSD_Randf(void) { return 0.5F; }

/// Static mod function
void my_mod_func(void) {
    OSReport("hello-mod: my_mod_func called\n\n");
}

/// Wrapper
u8 hook_runGameMode(u8 mode_kind)
{
    u8 pending_mode;

    OSReport("hello-mod: running game mode %d\n", mode_kind);           /// pre-hook
    pending_mode = runGameMode(mode_kind);                              /// call original
    OSReport("hello-mod: runGameMode returned %d\n\n", pending_mode);   /// post-hook

    my_mod_func();                                                      /// call my own function

    return pending_mode;                                                /// return original
}
