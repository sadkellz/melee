#include <platform.h>

#include <melee/lb/lbcollision.h>

/**
 * Shift canary: grow .data, .sbss and .text so every section (and the SDA
 * bases, stack and arena) moves relative to the retail layout.
 */
char mod_pad_data[32768] = { 1 };
int mod_canary_counter;

/**
 * hook_-style wrap of a function in a dtk-extracted unit (lbcollision.c):
 * the wrapper takes over #lbColl_80005BB0 and calls the original by its real
 * name (typed by the game header) — no declarations needed.
 */
int hook_lbColl_80005BB0(HitCapsule* arg0, int arg1)
{
    /// mwld strips unreferenced symbols, so keep the pad alive.
    mod_canary_counter += mod_pad_data[0];
    return lbColl_80005BB0(arg0, arg1);
}

/**
 * Wrap of a local (static) function in the same-name style: define it and
 * call the renamed original. #__fill_mem backs memset on the early boot
 * path, so a successful boot proves the retargeted intra-unit calls.
 */
int mod_canary_fills;

extern void orig___fill_mem(void* dst, int val, unsigned long n);
void __fill_mem(void* dst, int val, unsigned long n)
{
    mod_canary_fills++;
    orig___fill_mem(dst, val, n);
}
