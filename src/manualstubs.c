#include <platform.h>
#include "dolphin/ai.h"
#include "dolphin/ar.h"

#include <melee/gm/types.h>
#include <melee/gr/types.h>
#include <melee/it/items/types.h>
#include <dolphin/os.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/memory.h>

#include <dolphin/os.h>
#undef NOT_IMPLEMENTED
#define NOT_IMPLEMENTED \
    OSPanic(__FILE__, __LINE__, "Function is not implemented!")

int gmMainLib_8015F600()
{
    return 0;
}

int HSD_Synth_804D6018[2];

u8 lbl_80433710[0x20000];
void lbAudioAx_8002838C(void) {
    ARInit((u32*)(lbl_80433710 + 0x514), 0x10U);
    ARQInit();
    AIInit(0);
}

UNK_T mnGallery_804A0B90[4];

// related to character unlocks?
bool fn_80164B48() { return false; }

void hsd_80392E80(void) {}

void gm_801B14A0();
void gm_801B14DC();
void gm_801B1514();
void gm_801B154C();

void gm_801B1588();
void gm_801B15C8();
void gm_801B1648();
void gm_801B1688();


u8 HSD_SObjLib_804D7960[8];

void HSD_SObjLib_803A4740(HSD_Obj*);

GObjFunc HSD_SObjLib_8040C3A0[] = {
    HSD_SObjLib_803A4740,
};

GObjFuncs HSD_SObjLib_8040C3A4 = {
    0, 1, HSD_SObjLib_8040C3A0,
};

void gm_801B16A8();
void gm_801B16C8();

void gm_801BFA6C();

void gm_801BFCFC();
void gm_801A6308();

u8 un_804A1F48[0x50];

void gm_801BFABC();
void gm_801A6254();

void gm_801B087C();
void gm_801B089C();

u8 gm_804D6878[0x5000];

void gm_801B3500();
void gm_801B3A34();
void gm_801B3B40();
void gm_801B3D44();
void gm_801B3D84();
void gm_801B3DD8();
void gm_801B3E44();
void gm_801B3F18();
void gm_80470708();
void gm_80470850();

UNK_T gm_8047086C[0x200];
UNK_T gm_80472AF8[0x200];
UNK_T gm_804D68D0[0x200];
UNK_T gm_80490880[0x200];
UNK_T gm_8047086C[0x200];
UNK_T gm_80472AF8[0x200];
UNK_T gm_804D68D0[0x200];
UNK_T gm_80490880[0x200];
UNK_T gm_8047086C[0x200];
UNK_T gm_80472AF8[0x200];
UNK_T gm_804D68D0[0x200];
UNK_T gm_80490880[0x200];

void lbAudioAx_8002835C() {}
void lbAudioAx_80024030() {}
void lbAudioAx_8002392C() {}

int lbAudioAx_80026F2C() { return 0; }
int lbAudioAx_8002702C() { return 0; }
int lbAudioAx_80027168() { return 0; }
int lbAudioAx_80027DF8() { return 0; }
int lbAudioAx_80027648() { return 0; }

void hsd_803AAA48() {}

void* it_804D6D28;
UNK_T it_803F7D60[100] = { 0 };
UNK_T it_803F7CA0[100] = { 0 };
UNK_T it_803F7C40[100] = { 0 };
UNK_T it_803F7B58[100] = { 0 };
UNK_T it_803F7B08[100] = { 0 };
UNK_T it_803F7AD8[100] = { 0 };
UNK_T it_803F7A98[100] = { 0 };
UNK_T it_803F8BD8[100] = { 0 };
UNK_T it_803F94A0[100] = { 0 };
UNK_T it_803F7190[100] = { 0 };
UNK_T it_803F6F40[100] = { 0 };
UNK_T it_803F6B70[100] = { 0 };
UNK_T it_803F7760[100] = { 0 };
UNK_T it_803F6A28[100] = { 0 };
UNK_T it_803F6CA8[100] = { 0 };

UNK_T it_803B8570[200] = { 0 };
UNK_T it_803B857C[200] = { 0 };
UNK_T it_803F6C58[200] = { 0 };
UNK_T it_803F6F50[200] = { 0 };
UNK_T it_803F70A8[200] = { 0 };
UNK_T it_803F71D8[200] = { 0 };
UNK_T it_803F7288[200] = { 0 };
UNK_T it_803F7668[200] = { 0 };
UNK_T it_803F79E0[200] = { 0 };
UNK_T it_803F9378[200] = { 0 };
UNK_T it_803F93A8[200] = { 0 };
UNK_T it_803F7A28[200] = { 0 };
UNK_T it_803F7968[200] = { 0 };
UNK_T it_803F78F8[200] = { 0 };
UNK_T it_803F76B8[200] = { 0 };
UNK_T it_803F76F8[200] = { 0 };
UNK_T it_803F7558[200] = { 0 };
UNK_T it_803F6C68[200] = { 0 };
UNK_T it_803F7438[200] = { 0 };
UNK_T it_803F73A8[200] = { 0 };
UNK_T it_803F7340[200] = { 0 };
UNK_T it_803F7220[200] = { 0 };
UNK_T it_803F7118[200] = { 0 };
UNK_T it_803F70F8[200] = { 0 };
UNK_T it_803F70C8[200] = { 0 };
UNK_T it_803F6C08[200] = { 0 };
UNK_T it_803F6BC8[200] = { 0 };
UNK_T it_803F6B28[200] = { 0 };
UNK_T it_803F6998[200] = { 0 };
UNK_T it_803F6920[200] = { 0 };
UNK_T it_803F6888[200] = { 0 };
UNK_T it_803F6798[200] = { 0 };
UNK_T it_803F8E90[200] = { 0 };
UNK_T it_803B85A8[200] = { 0 };
UNK_T it_803F8320[200] = { 0 };
UNK_T it_803F8468[200] = { 0 };
UNK_T it_803F86C8[200] = { 0 };
UNK_T it_803F88C0[200] = { 0 };
UNK_T it_803F8940[200] = { 0 };
UNK_T it_803F89C8[200] = { 0 };
UNK_T it_803F8A88[200] = { 0 };
UNK_T it_803F8DE8[200] = { 0 };
UNK_T it_803F8FD0[200] = { 0 };
UNK_T it_803F9000[200] = { 0 };
UNK_T it_803F90D0[200] = { 0 };
UNK_T it_803F9260[200] = { 0 };
UNK_T it_803F9328[200] = { 0 };
UNK_T it_803F5FF0[200] = { 0 };
UNK_T it_803F6310[200] = { 0 };
UNK_T it_803F5F40[200] = { 0 };
UNK_T it_803F5EA8[200] = { 0 };
UNK_T it_803F5E00[200] = { 0 };
UNK_T it_803F5DB0[200] = { 0 };
UNK_T it_803F5D28[200] = { 0 };
UNK_T it_803F5C48[200] = { 0 };
UNK_T it_803F5BA8[200] = { 0 };
UNK_T it_803F5740[200] = { 0 };
UNK_T it_803F56C8[200] = { 0 };
UNK_T it_803F55D0[200] = { 0 };
UNK_T it_803F54D8[200] = { 0 };
UNK_T it_803F63C0[200] = { 0 };
UNK_T it_803F59F8[200] = { 0 };
UNK_T it_803F6728[200] = { 0 };
UNK_T it_803F82A0[200] = { 0 };
UNK_T it_803F8180[200] = { 0 };
UNK_T it_803F7FB8[200] = { 0 };
UNK_T it_803F7F48[200] = { 0 };
UNK_T it_803F7D90[200] = { 0 };
UNK_T it_803F7BB0[200] = { 0 };
UNK_T it_803F7B48[200] = { 0 };


StageData grPushOn_803E7B10;
StageData grFigureGet_803E7D34;
StageData grBb_Route_803E617C;
StageData grZe_Route_803E5E0C;
StageData grSh_Route_803E5988;
StageData grNKr_803E584C;
StageData grOk_803E65E8;
StageData grOy_803E650C;
StageData grOp_803E6748;
StageData grFz_803E7A00;
StageData grI2_803E4C00;
StageData grI1_803E4950;
StageData grIm_803E4800;
StageData grFs_803E3D94;
StageData grOt_803E2858;
StageData grBb_803E2D20;
StageData grMc_803E33DC;
StageData grPu_803E6A3C;
StageData grPs_803E1334;
StageData grVe_803E54CC;
StageData grCn_803E1F08;
StageData grGr_803E76D0;
StageData grYt_803E51CC;
StageData grKr_803E4D0C;
StageData grZe_803E1B2C;
StageData grGb_803E3F6C;
StageData grKg_803E1800;
StageData grRc_803E4ECC;
StageData grCs_803E11A4;
StageData grHeal_803E84C4;
StageData grHr_803E821C;

Article** it_804D6D24;
Article** it_804D6D38;
Article** it_804D6D30;
s8 it_804D6D00;

UNK_T cm_80453004[0x100];
HSD_ObjAllocData HSD_PSAppSrt_804D10B0;

void mpColl_80052A98() { NOT_IMPLEMENTED; }
void mpColl_800528CC() { NOT_IMPLEMENTED; }

u32 it_804D6D10;
s32 it_804D6D0C;
u32 it_804D6D14;

Article* it_804A0F60[30];
ItemStateTable it_803F7AC8[100];
ItemStateTable it_803F82F0[100];
ItemStateTable it_803F6640[100];

void Ground_801C28CC(void) { NOT_IMPLEMENTED; }
void Ground_801C34AC(void) { NOT_IMPLEMENTED; }
void Ground_801C20E0(void) { NOT_IMPLEMENTED; }

UNK_T it_803F6630[0x100];
UNK_T it_803F6568[0x100];
UNK_T it_803F6680[0x100];
UNK_T it_803F61B0[0x100];
UNK_T it_803F58E0[0x100];
UNK_T it_803F5850[0x100];
UNK_T it_8028428C[0x100];
UNK_T it_802841B4[0x100];
UNK_T it_8028428C[0x100];
UNK_T it_803F8270[0x100];
UNK_T it_803F8128[0x100];
UNK_T it_803F7F58[0x100];
UNK_T it_803F7EE8[0x100];

void lbRefract_800222A4() {}
void lb_8000FA94() {}

void* lbHeap_80015BD0(int x, int size)
{
    return HSD_MemAlloc(size);
}

void* HSD_AudioMalloc(int size)
{
    return HSD_MemAlloc(size);
}

// might be needed to load trophy data?
void un_8031C2CC(void) { }

void it_8026D018() {}
void lbAudioAx_8002785C() {}
void mpLib_8004D288() {}
void grMaterial_801C95C4() {}
void grAnime_801C8138() {}
void grAnime_801C7FF8() {}
void grAnime_801C8098() {}
void grAnime_801C7980() {}
void un_80321900() {}
void lbBgFlash_80021A18() {}
void lbAudioAx_80023F28() {}
void ifStatus_802F665C() {} // hud create?
void ifTime_802F446C() {} // hud timer?
void ifStatus_802F6EA4() {} // exclamation state change?
void fn_8016A4C8() {} // adventure mode spawn think?
void fn_8016758C(void) {}
void grMaterial_801C9698() {}
void fn_800301D0() {} // draw camera/ecb develop boxes?
void fn_80171DC4() {}
void fn_800587FC() {} // calculate range of lines?
void lbAudioAx_800236DC() {}
void lb_80011E24() {}
void gm_801BF128() {}
HSD_MObj* ft_804D6588;
HSD_Joint* ft_8045A1E0[6];
float ftYs_Init_804D9A64 = 20;
float ftYs_Init_804D9A5C = 1;
float ftYs_Init_804D9A60 = 0;
float ftYs_Init_804D9A38 = 0;
UNK_T ftNn_Init_MotionStateTable[0x200];
UNK_T ftKb_Init_MotionStateTable[0x200];
void lbHeap_80015F3C() {}
void lbArq_80014D2C() {}
void hsd_803B2374() {}
void lbMthp_8001F87C() {}
void lbMthp_8001F800() {}
void lbAudioAx_80028690() {}
void gm_801BF3F8() {} // menu title load demo

int hsd_804D78A0;

// Item callback stubs for NonMatching item files not linked in demo builds
// HSD_GObjEvent stubs (void(HSD_GObj*))
void itChicoritaLeaf_Logic30_Spawned(HSD_GObj* gobj) {}
void itEvYoshiEgg_Logic42_Destroyed(HSD_GObj* gobj) {}
void itEvYoshiEgg_Logic42_Dropped(HSD_GObj* gobj) {}
void itEvYoshiEgg_Logic42_EnteredAir(HSD_GObj* gobj) {}
void itEvYoshiEgg_Logic42_PickedUp(HSD_GObj* gobj) {}
void itEvYoshiEgg_Logic42_Spawned(HSD_GObj* gobj) {}
void itEvYoshiEgg_Logic42_Thrown(HSD_GObj* gobj) {}
void itFushigibana_Logic29_Spawned(HSD_GObj* gobj) {}
void itKabigon_Logic2_Destroyed(HSD_GObj* gobj) {}
void itLugia_Logic39_Spawned(HSD_GObj* gobj) {}
void itLugia_Logic40_Spawned(HSD_GObj* gobj) {}
void itLugia_Logic41_Spawned(HSD_GObj* gobj) {}
void itSeakNeedleHeld_Logic110_PickedUp(HSD_GObj* gobj) {}
void itSeakNeedleThrown_Logic109_Destroyed(HSD_GObj* gobj) {}
void itThunder_Logic7_Spawned(HSD_GObj* gobj) {}
void it_2725_Logic106_Destroyed(HSD_GObj* gobj) {}
void it_2725_Logic108_Destroyed(HSD_GObj* gobj) {}
void it_2725_Logic108_PickedUp(HSD_GObj* gobj) {}
void it_2725_Logic17_Spawned(HSD_GObj* gobj) {}
void it_2725_Logic18_Spawned(HSD_GObj* gobj) {}
void it_2725_Logic24_Spawned(HSD_GObj* gobj) {}
void it_2725_Logic31_Spawned(HSD_GObj* gobj) {}
void it_2725_Logic32_Spawned(HSD_GObj* gobj) {}
void it_2725_Logic33_Spawned(HSD_GObj* gobj) {}
void it_2725_Logic38_Spawned(HSD_GObj* gobj) {}
void it_2725_Logic42_Spawned(HSD_GObj* gobj) {}
void it_2725_Logic43_Spawned(HSD_GObj* gobj) {}

// HSD_GObjPredicate stubs (bool(HSD_GObj*))
bool itChicoritaLeaf_Logic30_HitShield(HSD_GObj* gobj) { return false; }
bool itChicoritaLeaf_Logic30_Reflected(HSD_GObj* gobj) { return false; }
bool itGameWatchChef_Logic112_DmgDealt(HSD_GObj* gobj) { return false; }
bool itGameWatchChef_Logic112_Reflected(HSD_GObj* gobj) { return false; }
bool itGameWatchChef_Logic112_ShieldBounced(HSD_GObj* gobj) { return false; }
bool itHitodeman_Logic43_Absorbed(HSD_GObj* gobj) { return false; }
bool itKamex_Logic31_DmgDealt(HSD_GObj* gobj) { return false; }
bool itKamex_Logic31_HitShield(HSD_GObj* gobj) { return false; }
bool itSamusChargeshot_Logic108_Absorbed(HSD_GObj* gobj) { return false; }
bool itSamusChargeshot_Logic108_Clanked(HSD_GObj* gobj) { return false; }
bool itSamusChargeshot_Logic108_DmgDealt(HSD_GObj* gobj) { return false; }
bool itSamusChargeshot_Logic108_HitShield(HSD_GObj* gobj) { return false; }
bool itSonans_Logic9_DmgDealt(HSD_GObj* gobj) { return false; }
bool it_2725_Logic106_Absorbed(HSD_GObj* gobj) { return false; }
bool it_2725_Logic106_Clanked(HSD_GObj* gobj) { return false; }
bool it_2725_Logic106_DmgDealt(HSD_GObj* gobj) { return false; }
bool it_2725_Logic106_HitShield(HSD_GObj* gobj) { return false; }
bool it_2725_Logic106_Reflected(HSD_GObj* gobj) { return false; }
bool it_2725_Logic106_ShieldBounced(HSD_GObj* gobj) { return false; }
bool it_2725_Logic107_Absorbed(HSD_GObj* gobj) { return false; }
bool it_2725_Logic107_Clanked(HSD_GObj* gobj) { return false; }
bool it_2725_Logic107_DmgDealt(HSD_GObj* gobj) { return false; }
bool it_2725_Logic107_HitShield(HSD_GObj* gobj) { return false; }
bool it_2725_Logic107_Reflected(HSD_GObj* gobj) { return false; }
bool it_2725_Logic107_ShieldBounced(HSD_GObj* gobj) { return false; }
bool it_2725_Logic108_Reflected(HSD_GObj* gobj) { return false; }
bool it_2725_Logic108_ShieldBounced(HSD_GObj* gobj) { return false; }
bool it_2725_Logic109_Clanked(HSD_GObj* gobj) { return false; }
bool it_2725_Logic109_DmgDealt(HSD_GObj* gobj) { return false; }
bool it_2725_Logic109_DmgReceived(HSD_GObj* gobj) { return false; }
bool it_2725_Logic109_HitShield(HSD_GObj* gobj) { return false; }
bool it_2725_Logic109_Reflected(HSD_GObj* gobj) { return false; }
bool it_2725_Logic109_ShieldBounced(HSD_GObj* gobj) { return false; }
bool it_2725_Logic112_Absorbed(HSD_GObj* gobj) { return false; }
bool it_2725_Logic112_Clanked(HSD_GObj* gobj) { return false; }
bool it_2725_Logic112_HitShield(HSD_GObj* gobj) { return false; }
bool it_2725_Logic27_DmgReceived(HSD_GObj* gobj) { return false; }
bool it_27CF_Logic114_DmgReceived(HSD_GObj* gobj) { return false; }
bool it_2E5A_Logic115_DmgDealt(HSD_GObj* gobj) { return false; }
bool it_3F14_Logic42_Clanked(HSD_GObj* gobj) { return false; }
bool it_3F14_Logic42_DmgDealt(HSD_GObj* gobj) { return false; }
bool it_3F14_Logic42_DmgReceived(HSD_GObj* gobj) { return false; }
bool it_3F14_Logic42_HitShield(HSD_GObj* gobj) { return false; }
bool it_3F14_Logic42_Reflected(HSD_GObj* gobj) { return false; }

// HSD_GObjInteraction stubs (void(HSD_GObj*, HSD_GObj*))
void itChicoritaLeaf_Logic30_EvtUnk(HSD_GObj* gobj0, HSD_GObj* gobj1) {}
void itChicorita_Logic1_EvtUnk(HSD_GObj* gobj0, HSD_GObj* gobj1) {}
void itEvYoshiEgg_Logic42_EvtUnk(HSD_GObj* gobj0, HSD_GObj* gobj1) {}
void itGameWatchChef_Logic112_EvtUnk(HSD_GObj* gobj0, HSD_GObj* gobj1) {}
void itKamex_Logic31_EvtUnk(HSD_GObj* gobj0, HSD_GObj* gobj1) {}
void itLugia_Logic17_EvtUnk(HSD_GObj* gobj0, HSD_GObj* gobj1) {}
void itMatadogas_Logic33_EvtUnk(HSD_GObj* gobj0, HSD_GObj* gobj1) {}
void itOldKuri_Logic29_EvtUnk(HSD_GObj* gobj0, HSD_GObj* gobj1) {}
void itPikachuTJoltAir_Logic107_EvtUnk(HSD_GObj* gobj0, HSD_GObj* gobj1) {}
void itPikachuTJoltGround_Logic106_EvtUnk(HSD_GObj* gobj0, HSD_GObj* gobj1) {}
void itSamusChargeshot_Logic108_EvtUnk(HSD_GObj* gobj0, HSD_GObj* gobj1) {}
void itSeakNeedleHeld_Logic110_EvtUnk(HSD_GObj* gobj0, HSD_GObj* gobj1) {}
void itSeakNeedleThrown_Logic109_EvtUnk(HSD_GObj* gobj0, HSD_GObj* gobj1) {}
void itUnknown_Logic38_EvtUnk(HSD_GObj* gobj0, HSD_GObj* gobj1) {}
void it_27CF_Logic114_EvtUnk(HSD_GObj* gobj0, HSD_GObj* gobj1) {}
void it_2E5A_Logic115_EvtUnk(HSD_GObj* gobj0, HSD_GObj* gobj1) {}

// Round 2 stubs
// Data stubs
UNK_T it_803B8588[4];
UNK_T it_803B8598[4];

// HSD_GObjEvent stubs (void(HSD_GObj*))
void itFoxBlaster_Logic96_PickedUp(HSD_GObj* gobj) {}
void itGameWatchJudge_Logic77_Destroyed(HSD_GObj* gobj) {}
void itGameWatchParachute_Logic74_Destroyed(HSD_GObj* gobj) {}
void itGameWatchParachute_Logic74_PickedUp(HSD_GObj* gobj) {}
void itLinkArrow_Logic98_Destroyed(HSD_GObj* gobj) {}
void itLinkArrow_Logic98_PickedUp(HSD_GObj* gobj) {}
void itNessYoyo_Logic59_PickedUp(HSD_GObj* gobj) {}
void itSamusGrapple_Logic53_PickedUp(HSD_GObj* gobj) {}
void itSamusGrapple_Logic53_Spawned(HSD_GObj* gobj) {}
void it_2725_Logic101_Destroyed(HSD_GObj* gobj) {}
void it_2725_Logic101_PickedUp(HSD_GObj* gobj) {}
void it_2725_Logic102_Destroyed(HSD_GObj* gobj) {}
void it_2725_Logic103_Destroyed(HSD_GObj* gobj) {}
void it_2725_Logic54_PickedUp(HSD_GObj* gobj) {}
void it_2725_Logic58_PickedUp(HSD_GObj* gobj) {}
void it_2725_Logic70_PickedUp(HSD_GObj* gobj) {}
void it_2725_Logic77_PickedUp(HSD_GObj* gobj) {}
void it_2725_Logic80_PickedUp(HSD_GObj* gobj) {}
void it_2725_Logic90_Destroyed(HSD_GObj* gobj) {}

// HSD_GObjPredicate stubs (bool(HSD_GObj*))
bool itClimbersIce_Logic90_Absorbed(HSD_GObj* gobj) { return false; }
bool itClimbersIce_Logic90_Clanked(HSD_GObj* gobj) { return false; }
bool itClimbersIce_Logic90_DmgDealt(HSD_GObj* gobj) { return false; }
bool itClimbersIce_Logic90_Reflected(HSD_GObj* gobj) { return false; }
bool itClimbersIce_Logic90_ShieldBounced(HSD_GObj* gobj) { return false; }
bool itCrazyHandBomb_Logic86_DmgDealt(HSD_GObj* gobj) { return false; }
bool itCrazyHandBomb_Logic86_Reflected(HSD_GObj* gobj) { return false; }
bool itLinkArrow_Logic98_Clanked(HSD_GObj* gobj) { return false; }
bool itLinkArrow_Logic98_DmgDealt(HSD_GObj* gobj) { return false; }
bool itLinkArrow_Logic98_HitShield(HSD_GObj* gobj) { return false; }
bool itLinkArrow_Logic98_Reflected(HSD_GObj* gobj) { return false; }
bool itMewtwoShadowball_Logic101_Absorbed(HSD_GObj* gobj) { return false; }
bool itMewtwoShadowball_Logic101_Clanked(HSD_GObj* gobj) { return false; }
bool itMewtwoShadowball_Logic101_DmgDealt(HSD_GObj* gobj) { return false; }
bool itMewtwoShadowball_Logic101_HitShield(HSD_GObj* gobj) { return false; }
bool itNessPKFlushExplode_Logic103_Absorbed(HSD_GObj* gobj) { return false; }
bool itNessPKFlushExplode_Logic103_Clanked(HSD_GObj* gobj) { return false; }
bool itNessPKFlushExplode_Logic103_HitShield(HSD_GObj* gobj) { return false; }
bool itNessPKFlushExplode_Logic103_ShieldBounced(HSD_GObj* gobj) { return false; }
bool itNessPKFlush_Logic102_Absorbed(HSD_GObj* gobj) { return false; }
bool itNessPKFlush_Logic102_Clanked(HSD_GObj* gobj) { return false; }
bool itNessPKFlush_Logic102_Reflected(HSD_GObj* gobj) { return false; }
bool itSamusBomb_Logic50_HitShield(HSD_GObj* gobj) { return false; }
bool itSamusBomb_Logic50_ShieldBounced(HSD_GObj* gobj) { return false; }
bool it_2725_Logic101_Reflected(HSD_GObj* gobj) { return false; }
bool it_2725_Logic101_ShieldBounced(HSD_GObj* gobj) { return false; }
bool it_2725_Logic52_Clanked(HSD_GObj* gobj) { return false; }
bool it_2725_Logic52_DmgDealt(HSD_GObj* gobj) { return false; }
bool it_2725_Logic52_HitShield(HSD_GObj* gobj) { return false; }
bool it_2725_Logic52_Reflected(HSD_GObj* gobj) { return false; }
bool it_2725_Logic52_ShieldBounced(HSD_GObj* gobj) { return false; }
bool it_2725_Logic90_HitShield(HSD_GObj* gobj) { return false; }

// HSD_GObjInteraction stubs (void(HSD_GObj*, HSD_GObj*))
void itCLinkMilk_Logic80_EvtUnk(HSD_GObj* gobj0, HSD_GObj* gobj1) {}
void itClimbersIce_Logic90_EvtUnk(HSD_GObj* gobj0, HSD_GObj* gobj1) {}
void itCrazyHandBomb_Logic86_EvtUnk(HSD_GObj* gobj0, HSD_GObj* gobj1) {}
void itFoxBlaster_Logic96_EvtUnk(HSD_GObj* gobj0, HSD_GObj* gobj1) {}
void itGameWatchJudge_Logic77_EvtUnk(HSD_GObj* gobj0, HSD_GObj* gobj1) {}
void itGameWatchParachute_Logic74_EvtUnk(HSD_GObj* gobj0, HSD_GObj* gobj1) {}
void itLinkArrow_Logic98_EvtUnk(HSD_GObj* gobj0, HSD_GObj* gobj1) {}
void itMasterHandLaser_Logic84_EvtUnk(HSD_GObj* gobj0, HSD_GObj* gobj1) {}
void itMewtwoShadowball_Logic101_EvtUnk(HSD_GObj* gobj0, HSD_GObj* gobj1) {}
void itNessBat_Logic58_EvtUnk(HSD_GObj* gobj0, HSD_GObj* gobj1) {}
void itNessPKFlushExplode_Logic103_EvtUnk(HSD_GObj* gobj0, HSD_GObj* gobj1) {}
void itNessPKFlush_Logic102_EvtUnk(HSD_GObj* gobj0, HSD_GObj* gobj1) {}
void itSamusBomb_Logic50_EvtUnk(HSD_GObj* gobj0, HSD_GObj* gobj1) {}
void itSamusGrapple_Logic53_EvtUnk(HSD_GObj* gobj0, HSD_GObj* gobj1) {}
void itSeakChain_Logic54_EvtUnk(HSD_GObj* gobj0, HSD_GObj* gobj1) {}
void it_2725_Logic52_EvtUnk(HSD_GObj* gobj0, HSD_GObj* gobj1) {}
void it_2725_Logic59_EvtUnk(HSD_GObj* gobj0, HSD_GObj* gobj1) {}
void it_2725_Logic70_EvtUnk(HSD_GObj* gobj0, HSD_GObj* gobj1) {}

// Round 3 stubs
f32 it_804DC73C;

void itKyasarinEgg_Logic28_Dropped(HSD_GObj* gobj) {}
void itKyasarinEgg_Logic28_PickedUp(HSD_GObj* gobj) {}
void itKyasarinEgg_Logic28_Thrown(HSD_GObj* gobj) {}
void itKyasarin_Logic25_Destroyed(HSD_GObj* gobj) {}
void itLinkBoomerang_Logic18_Destroyed(HSD_GObj* gobj) {}
void itLinkBomb_Logic16_EnteredAir(HSD_GObj* gobj) {}
void itLinkHookshot_Logic20_PickedUp(HSD_GObj* gobj) {}
void itMarioCape_Logic41_Destroyed(HSD_GObj* gobj) {}
void itOctarockstone_802E878C(HSD_GObj* gobj) {}
void itOldKuri_Logic0_PickedUp(HSD_GObj* gobj) {}
void itSamusBomb_Logic50_EnteredAir(HSD_GObj* gobj) {}
void itYoshiEggThrow_Logic43_PickedUp(HSD_GObj* gobj) {}
void itZGShell_Logic11_Dropped(HSD_GObj* gobj) {}
void itZGShell_Logic11_Thrown(HSD_GObj* gobj) {}
void itZrshell_UnkMotion11_Phys(HSD_GObj* gobj) {}
void it_2725_Logic0_Dropped(HSD_GObj* gobj) {}
void it_2725_Logic0_Thrown(HSD_GObj* gobj) {}
void it_2725_Logic11_EnteredAir(HSD_GObj* gobj) {}
void it_2725_Logic11_PickedUp(HSD_GObj* gobj) {}
void it_2725_Logic39_Destroyed(HSD_GObj* gobj) {}
void it_2725_Logic3_Destroyed(HSD_GObj* gobj) {}
void it_2725_Logic41_PickedUp(HSD_GObj* gobj) {}

bool itGreatFoxLaser_Logic27_Absorbed(HSD_GObj* gobj) { return false; }
bool itGreatFoxLaser_Logic27_Clanked(HSD_GObj* gobj) { return false; }
bool itGreatFoxLaser_Logic27_DmgDealt(HSD_GObj* gobj) { return false; }
bool itKirbyCutterBeam_Logic7_Absorbed(HSD_GObj* gobj) { return false; }
bool itKirbyCutterBeam_Logic7_Clanked(HSD_GObj* gobj) { return false; }
bool itKirbyCutterBeam_Logic7_DmgDealt(HSD_GObj* gobj) { return false; }
bool itKirbyCutterBeam_Logic7_HitShield(HSD_GObj* gobj) { return false; }
bool itKyasarinEgg_Logic28_ShieldBounced(HSD_GObj* gobj) { return false; }
bool itLinkBomb_Logic16_DmgReceived(HSD_GObj* gobj) { return false; }
bool itLinkBomb_Logic16_HitShield(HSD_GObj* gobj) { return false; }
bool itLinkBomb_Logic16_Reflected(HSD_GObj* gobj) { return false; }
bool itLinkBomb_Logic16_ShieldBounced(HSD_GObj* gobj) { return false; }
bool itLinkBoomerang_Logic18_Absorbed(HSD_GObj* gobj) { return false; }
bool itNessPKFire_Logic23_Absorbed(HSD_GObj* gobj) { return false; }
bool itNessPKFire_Logic23_HitShield(HSD_GObj* gobj) { return false; }
bool itNessPKFire_Logic23_Reflected(HSD_GObj* gobj) { return false; }
bool itNessPKThunderball_Logic26_DmgDealt(HSD_GObj* gobj) { return false; }
bool itOctarockstone_Logic4_Absorbed(HSD_GObj* gobj) { return false; }
bool itOctarockstone_Logic4_Clanked(HSD_GObj* gobj) { return false; }
bool itOctarockstone_Logic4_DmgDealt(HSD_GObj* gobj) { return false; }
bool itOctarockstone_Logic4_HitShield(HSD_GObj* gobj) { return false; }
bool itOctarockstone_Logic4_Reflected(HSD_GObj* gobj) { return false; }
bool itOctarockstone_Logic4_ShieldBounced(HSD_GObj* gobj) { return false; }
bool itPikachuThunder_Logic39_Absorbed(HSD_GObj* gobj) { return false; }
bool itPikachuThunder_Logic39_Clanked(HSD_GObj* gobj) { return false; }
bool itPikachuThunder_Logic39_DmgDealt(HSD_GObj* gobj) { return false; }
bool itPikachuThunder_Logic39_HitShield(HSD_GObj* gobj) { return false; }
bool itSamusBomb_Logic50_Clanked(HSD_GObj* gobj) { return false; }
bool itSamusBomb_Logic50_DmgDealt(HSD_GObj* gobj) { return false; }
bool itTincle_Logic13_DmgDealt(HSD_GObj* gobj) { return false; }
bool itTincle_Logic13_DmgReceived(HSD_GObj* gobj) { return false; }
bool itTools_Logic22_DmgDealt(HSD_GObj* gobj) { return false; }
bool itTools_Logic22_DmgReceived(HSD_GObj* gobj) { return false; }
bool itTools_Logic22_Reflected(HSD_GObj* gobj) { return false; }
bool itTools_Logic22_ShieldBounced(HSD_GObj* gobj) { return false; }
bool itZGShell_Logic11_DmgDealt(HSD_GObj* gobj) { return false; }
bool itZGShell_Logic11_DmgReceived(HSD_GObj* gobj) { return false; }
bool itZGShell_Logic11_Reflected(HSD_GObj* gobj) { return false; }
bool itZGShell_Logic11_ShieldBounced(HSD_GObj* gobj) { return false; }
bool itZrshell_UnkMotion11_Coll(HSD_GObj* gobj) { return false; }
bool it_2725_Logic0_DmgReceived(HSD_GObj* gobj) { return false; }
bool it_2725_Logic11_Clanked(HSD_GObj* gobj) { return false; }
bool it_2725_Logic11_HitShield(HSD_GObj* gobj) { return false; }
bool it_2725_Logic22_Absorbed(HSD_GObj* gobj) { return false; }
bool it_2725_Logic22_Clanked(HSD_GObj* gobj) { return false; }
bool it_2725_Logic22_HitShield(HSD_GObj* gobj) { return false; }
bool it_2725_Logic23_Clanked(HSD_GObj* gobj) { return false; }
bool it_2725_Logic23_DmgDealt(HSD_GObj* gobj) { return false; }
bool it_2725_Logic23_ShieldBounced(HSD_GObj* gobj) { return false; }
bool it_2725_Logic27_Reflected(HSD_GObj* gobj) { return false; }
bool it_2725_Logic28_Clanked(HSD_GObj* gobj) { return false; }
bool it_2725_Logic28_DmgDealt(HSD_GObj* gobj) { return false; }
bool it_2725_Logic28_HitShield(HSD_GObj* gobj) { return false; }
bool it_2725_Logic28_Reflected(HSD_GObj* gobj) { return false; }
bool it_2725_Logic43_Clanked(HSD_GObj* gobj) { return false; }
bool it_2725_Logic50_Reflected(HSD_GObj* gobj) { return false; }
bool it_2725_Logic7_Reflected(HSD_GObj* gobj) { return false; }
bool it_2725_Logic7_ShieldBounced(HSD_GObj* gobj) { return false; }
bool it_2725_Logic8_DmgReceived(HSD_GObj* gobj) { return false; }

void itOctarockstone_802E89B0(HSD_GObj* gobj0, HSD_GObj* gobj1) {}
void itPikachuThunder_Logic39_EvtUnk(HSD_GObj* gobj0, HSD_GObj* gobj1) {}

// Round 4 stubs
void itFoods_Logic18_PickedUp(HSD_GObj* gobj) {}
void itHammerHead_Logic40_Dropped(HSD_GObj* gobj) {}
void itHammerHead_Logic40_PickedUp(HSD_GObj* gobj) {}
void itHammerHead_Logic40_Spawned(HSD_GObj* gobj) {}
void itHarisen_Logic24_Dropped(HSD_GObj* gobj) {}
void itHarisen_Logic24_EnteredAir(HSD_GObj* gobj) {}
void itHarisen_Logic24_PickedUp(HSD_GObj* gobj) {}
void itHarisen_Logic24_Spawned(HSD_GObj* gobj) {}
void itHarisen_Logic24_Thrown(HSD_GObj* gobj) {}
void itKlap_Logic10_Destroyed(HSD_GObj* gobj) {}
void itLikeLike_Logic5_Destroyed(HSD_GObj* gobj) {}
void itLikeLike_Logic5_PickedUp(HSD_GObj* gobj) {}
void itLikeLike_Logic5_Thrown(HSD_GObj* gobj) {}
void itPatapata_Logic4_PickedUp(HSD_GObj* gobj) {}
void itWStar_Logic29_Dropped(HSD_GObj* gobj) {}
void itWStar_Logic29_EnteredAir(HSD_GObj* gobj) {}
void itWStar_Logic29_Spawned(HSD_GObj* gobj) {}
void itWhiteBea_Logic9_PickedUp(HSD_GObj* gobj) {}
void itZGShell_Logic11_Destroyed(HSD_GObj* gobj) {}
void itZrshell_UnkMotion0_Phys(HSD_GObj* gobj) {}
void itZrshell_UnkMotion10_Phys(HSD_GObj* gobj) {}
void itZrshell_UnkMotion1_Phys(HSD_GObj* gobj) {}
void itZrshell_UnkMotion2_Phys(HSD_GObj* gobj) {}
void itZrshell_UnkMotion3_Phys(HSD_GObj* gobj) {}
void itZrshell_UnkMotion4_Phys(HSD_GObj* gobj) {}
void itZrshell_UnkMotion6_Phys(HSD_GObj* gobj) {}
void itZrshell_UnkMotion8_Phys(HSD_GObj* gobj) {}
void itZrshell_UnkMotion9_Phys(HSD_GObj* gobj) {}
void it_2725_Logic4_Dropped(HSD_GObj* gobj) {}
void it_2725_Logic4_Thrown(HSD_GObj* gobj) {}
void it_2725_Logic5_Dropped(HSD_GObj* gobj) {}
void it_2725_Logic9_Dropped(HSD_GObj* gobj) {}
void it_2725_Logic9_Thrown(HSD_GObj* gobj) {}

bool itHammerHead_Logic40_Clanked(HSD_GObj* gobj) { return false; }
bool itHammerHead_Logic40_DmgDealt(HSD_GObj* gobj) { return false; }
bool itHammerHead_Logic40_DmgReceived(HSD_GObj* gobj) { return false; }
bool itHammerHead_Logic40_HitShield(HSD_GObj* gobj) { return false; }
bool itHammerHead_Logic40_Reflected(HSD_GObj* gobj) { return false; }
bool itHarisen_Logic24_Clanked(HSD_GObj* gobj) { return false; }
bool itHarisen_Logic24_DmgDealt(HSD_GObj* gobj) { return false; }
bool itHarisen_Logic24_HitShield(HSD_GObj* gobj) { return false; }
bool itHarisen_Logic24_Reflected(HSD_GObj* gobj) { return false; }
bool itHarisen_Logic24_ShieldBounced(HSD_GObj* gobj) { return false; }
bool itLGunBeam_Logic39_Absorbed(HSD_GObj* gobj) { return false; }
bool itLGunBeam_Logic39_Clanked(HSD_GObj* gobj) { return false; }
bool itLGunBeam_Logic39_DmgDealt(HSD_GObj* gobj) { return false; }
bool itLGunBeam_Logic39_HitShield(HSD_GObj* gobj) { return false; }
bool itLGunBeam_Logic39_Reflected(HSD_GObj* gobj) { return false; }
bool itLGunBeam_Logic39_ShieldBounced(HSD_GObj* gobj) { return false; }
bool itLipstickSpore_Logic37_Absorbed(HSD_GObj* gobj) { return false; }
bool itLipstickSpore_Logic37_Clanked(HSD_GObj* gobj) { return false; }
bool itLipstickSpore_Logic37_DmgDealt(HSD_GObj* gobj) { return false; }
bool itLipstickSpore_Logic37_HitShield(HSD_GObj* gobj) { return false; }
bool itLipstickSpore_Logic37_Reflected(HSD_GObj* gobj) { return false; }
bool itLipstickSpore_Logic37_ShieldBounced(HSD_GObj* gobj) { return false; }
bool itLipstick_Logic23_HitShield(HSD_GObj* gobj) { return false; }
bool itLipstick_Logic23_ShieldBounced(HSD_GObj* gobj) { return false; }
bool itSScopeBeam_Logic38_Absorbed(HSD_GObj* gobj) { return false; }
bool itSScopeBeam_Logic38_Clanked(HSD_GObj* gobj) { return false; }
bool itSScopeBeam_Logic38_DmgDealt(HSD_GObj* gobj) { return false; }
bool itSScopeBeam_Logic38_HitShield(HSD_GObj* gobj) { return false; }
bool itSScopeBeam_Logic38_Reflected(HSD_GObj* gobj) { return false; }
bool itSScopeBeam_Logic38_ShieldBounced(HSD_GObj* gobj) { return false; }
bool itZrshell_UnkMotion0_Anim(HSD_GObj* gobj) { return false; }
bool itZrshell_UnkMotion0_Coll(HSD_GObj* gobj) { return false; }
bool itZrshell_UnkMotion10_Anim(HSD_GObj* gobj) { return false; }
bool itZrshell_UnkMotion10_Coll(HSD_GObj* gobj) { return false; }
bool itZrshell_UnkMotion11_Anim(HSD_GObj* gobj) { return false; }
bool itZrshell_UnkMotion1_Anim(HSD_GObj* gobj) { return false; }
bool itZrshell_UnkMotion1_Coll(HSD_GObj* gobj) { return false; }
bool itZrshell_UnkMotion2_Anim(HSD_GObj* gobj) { return false; }
bool itZrshell_UnkMotion3_Anim(HSD_GObj* gobj) { return false; }
bool itZrshell_UnkMotion3_Coll(HSD_GObj* gobj) { return false; }
bool itZrshell_UnkMotion4_Anim(HSD_GObj* gobj) { return false; }
bool itZrshell_UnkMotion4_Coll(HSD_GObj* gobj) { return false; }
bool itZrshell_UnkMotion6_Anim(HSD_GObj* gobj) { return false; }
bool itZrshell_UnkMotion6_Coll(HSD_GObj* gobj) { return false; }
bool itZrshell_UnkMotion8_Anim(HSD_GObj* gobj) { return false; }
bool itZrshell_UnkMotion8_Coll(HSD_GObj* gobj) { return false; }
bool itZrshell_UnkMotion9_Anim(HSD_GObj* gobj) { return false; }
bool itZrshell_UnkMotion9_Coll(HSD_GObj* gobj) { return false; }
bool it_2725_Logic10_DmgReceived(HSD_GObj* gobj) { return false; }
bool it_2725_Logic4_DmgReceived(HSD_GObj* gobj) { return false; }
bool it_2725_Logic5_DmgReceived(HSD_GObj* gobj) { return false; }
void it_3F14_Logic29_PickedUp(HSD_GObj* gobj) {}

void itHammerHead_Logic40_EvtUnk(HSD_GObj* gobj0, HSD_GObj* gobj1) {}
void itHarisen_Logic24_EvtUnk(HSD_GObj* gobj0, HSD_GObj* gobj1) {}
void itLGunBeam_Logic39_EvtUnk(HSD_GObj* gobj0, HSD_GObj* gobj1) {}
void itLipstickSpore_Logic37_EvtUnk(HSD_GObj* gobj0, HSD_GObj* gobj1) {}
void itLipstick_Logic23_EvtUnk(HSD_GObj* gobj0, HSD_GObj* gobj1) {}
void itSScopeBeam_Logic38_EvtUnk(HSD_GObj* gobj0, HSD_GObj* gobj1) {}
void itWStar_Logic30_EvtUnk(HSD_GObj* gobj0, HSD_GObj* gobj1) {}

// it_3F14_Logic40_Thrown is Event (void(HSD_GObj*))
void it_3F14_Logic40_Thrown(HSD_GObj* gobj) {}

// Final batch: all remaining stubs from nm analysis
s32 it_804D6D08;
void itBombhei_Logic6_PickedUp(HSD_GObj* gobj) {}
void itBombhei_Logic6_Spawned(HSD_GObj* gobj) {}
void itBox_Logic1_Destroyed(HSD_GObj* gobj) {}
void itBox_Logic1_Dropped(HSD_GObj* gobj) {}
void itBox_Logic1_EnteredAir(HSD_GObj* gobj) {}
void itBox_Logic1_PickedUp(HSD_GObj* gobj) {}
void itBox_Logic1_Spawned(HSD_GObj* gobj) {}
void itBox_Logic1_Thrown(HSD_GObj* gobj) {}
void itFlipper_Logic20_Dropped(HSD_GObj* gobj) {}
void itFlipper_Logic20_EnteredAir(HSD_GObj* gobj) {}
void itFlipper_Logic20_PickedUp(HSD_GObj* gobj) {}
void itFlipper_Logic20_Spawned(HSD_GObj* gobj) {}
void itFlipper_Logic20_Thrown(HSD_GObj* gobj) {}
void itFoods_Logic18_Dropped(HSD_GObj* gobj) {}
void itFoods_Logic18_Spawned(HSD_GObj* gobj) {}
void itFreeze_Logic17_Destroyed(HSD_GObj* gobj) {}
void itFreeze_Logic17_Dropped(HSD_GObj* gobj) {}
void itFreeze_Logic17_PickedUp(HSD_GObj* gobj) {}
void itFreeze_Logic17_Thrown(HSD_GObj* gobj) {}
void itGShell_Logic14_Dropped(HSD_GObj* gobj) {}
void itGShell_Logic14_EnteredAir(HSD_GObj* gobj) {}
void itGShell_Logic14_PickedUp(HSD_GObj* gobj) {}
void itGShell_Logic14_Spawned(HSD_GObj* gobj) {}
void itGShell_Logic14_Thrown(HSD_GObj* gobj) {}
void itHeart_Logic8_Destroyed(HSD_GObj* gobj) {}
void itHeart_Logic8_Dropped(HSD_GObj* gobj) {}
void itHeart_Logic8_EnteredAir(HSD_GObj* gobj) {}
void itHeart_Logic8_PickedUp(HSD_GObj* gobj) {}
void itHeart_Logic8_Spawned(HSD_GObj* gobj) {}
void itKusudama_Logic4_Dropped(HSD_GObj* gobj) {}
void itKusudama_Logic4_PickedUp(HSD_GObj* gobj) {}
void itKusudama_Logic4_Spawned(HSD_GObj* gobj) {}
void itKusudama_Logic4_Thrown(HSD_GObj* gobj) {}
void itLipstick_Logic23_Dropped(HSD_GObj* gobj) {}
void itLipstick_Logic23_EnteredAir(HSD_GObj* gobj) {}
void itLipstick_Logic23_PickedUp(HSD_GObj* gobj) {}
void itLipstick_Logic23_Spawned(HSD_GObj* gobj) {}
void itLipstick_Logic23_Thrown(HSD_GObj* gobj) {}
void itRShell_Logic15_PickedUp(HSD_GObj* gobj) {}
void itSScope_Logic21_Dropped(HSD_GObj* gobj) {}
void itSScope_Logic21_EnteredAir(HSD_GObj* gobj) {}
void itSScope_Logic21_PickedUp(HSD_GObj* gobj) {}
void itSScope_Logic21_Spawned(HSD_GObj* gobj) {}
void itSScope_Logic21_Thrown(HSD_GObj* gobj) {}
void itTaruCann_Logic5_PickedUp(HSD_GObj* gobj) {}
void itTaru_Logic2_Dropped(HSD_GObj* gobj) {}
void itTaru_Logic2_PickedUp(HSD_GObj* gobj) {}
void itTaru_Logic2_Thrown(HSD_GObj* gobj) {}
void itTomato_Logic9_Destroyed(HSD_GObj* gobj) {}
void itTomato_Logic9_Dropped(HSD_GObj* gobj) {}
void itTomato_Logic9_EnteredAir(HSD_GObj* gobj) {}
void itTomato_Logic9_PickedUp(HSD_GObj* gobj) {}
void itTomato_Logic9_Spawned(HSD_GObj* gobj) {}
void it_3F14_Logic15_Dropped(HSD_GObj* gobj) {}
void it_3F14_Logic15_EnteredAir(HSD_GObj* gobj) {}
void it_3F14_Logic15_Spawned(HSD_GObj* gobj) {}
void it_3F14_Logic15_Thrown(HSD_GObj* gobj) {}
void it_3F14_Logic17_Spawned(HSD_GObj* gobj) {}
void it_3F14_Logic2_Spawned(HSD_GObj* gobj) {}
void it_3F14_Logic5_Destroyed(HSD_GObj* gobj) {}
void it_3F14_Logic5_Dropped(HSD_GObj* gobj) {}
void it_3F14_Logic5_Spawned(HSD_GObj* gobj) {}
void it_3F14_Logic5_Thrown(HSD_GObj* gobj) {}
void it_3F14_Logic6_Dropped(HSD_GObj* gobj) {}
void it_3F14_Logic6_EnteredAir(HSD_GObj* gobj) {}
void it_3F14_Logic6_Thrown(HSD_GObj* gobj) {}
void it_3F14_Logic7_Dropped(HSD_GObj* gobj) {}
void it_3F14_Logic7_EnteredAir(HSD_GObj* gobj) {}
void it_3F14_Logic7_PickedUp(HSD_GObj* gobj) {}
void it_3F14_Logic7_Spawned(HSD_GObj* gobj) {}
void it_3F14_Logic7_Thrown(HSD_GObj* gobj) {}
bool itBombhei_Logic6_Clanked(HSD_GObj* gobj) { return false; }
bool itBombhei_Logic6_Reflected(HSD_GObj* gobj) { return false; }
bool itBox_Logic1_Clanked(HSD_GObj* gobj) { return false; }
bool itBox_Logic1_DmgDealt(HSD_GObj* gobj) { return false; }
bool itBox_Logic1_DmgReceived(HSD_GObj* gobj) { return false; }
bool itBox_Logic1_HitShield(HSD_GObj* gobj) { return false; }
bool itBox_Logic1_Reflected(HSD_GObj* gobj) { return false; }
bool itDosei_Logic7_Clanked(HSD_GObj* gobj) { return false; }
bool itDosei_Logic7_HitShield(HSD_GObj* gobj) { return false; }
bool itDosei_Logic7_Reflected(HSD_GObj* gobj) { return false; }
bool itDosei_Logic7_ShieldBounced(HSD_GObj* gobj) { return false; }
bool itFlipper_Logic20_Reflected(HSD_GObj* gobj) { return false; }
bool itFlipper_Logic20_ShieldBounced(HSD_GObj* gobj) { return false; }
bool itFreeze_Logic17_Absorbed(HSD_GObj* gobj) { return false; }
bool itFreeze_Logic17_Clanked(HSD_GObj* gobj) { return false; }
bool itFreeze_Logic17_DmgDealt(HSD_GObj* gobj) { return false; }
bool itFreeze_Logic17_DmgReceived(HSD_GObj* gobj) { return false; }
bool itFreeze_Logic17_HitShield(HSD_GObj* gobj) { return false; }
bool itFreeze_Logic17_Reflected(HSD_GObj* gobj) { return false; }
bool itFreeze_Logic17_ShieldBounced(HSD_GObj* gobj) { return false; }
bool itGShell_Logic14_Clanked(HSD_GObj* gobj) { return false; }
bool itGShell_Logic14_DmgDealt(HSD_GObj* gobj) { return false; }
bool itGShell_Logic14_DmgReceived(HSD_GObj* gobj) { return false; }
bool itGShell_Logic14_HitShield(HSD_GObj* gobj) { return false; }
bool itGShell_Logic14_Reflected(HSD_GObj* gobj) { return false; }
bool itGShell_Logic14_ShieldBounced(HSD_GObj* gobj) { return false; }
bool itKusudama_Logic4_Clanked(HSD_GObj* gobj) { return false; }
bool itKusudama_Logic4_DmgDealt(HSD_GObj* gobj) { return false; }
bool itKusudama_Logic4_DmgReceived(HSD_GObj* gobj) { return false; }
bool itKusudama_Logic4_HitShield(HSD_GObj* gobj) { return false; }
bool itKusudama_Logic4_Reflected(HSD_GObj* gobj) { return false; }
bool itLipstick_Logic23_Clanked(HSD_GObj* gobj) { return false; }
bool itLipstick_Logic23_DmgDealt(HSD_GObj* gobj) { return false; }
bool itLipstick_Logic23_Reflected(HSD_GObj* gobj) { return false; }
bool itRShell_Logic15_Clanked(HSD_GObj* gobj) { return false; }
bool itRShell_Logic15_Reflected(HSD_GObj* gobj) { return false; }
bool itRShell_Logic15_ShieldBounced(HSD_GObj* gobj) { return false; }
bool itSScope_Logic21_Clanked(HSD_GObj* gobj) { return false; }
bool itSScope_Logic21_DmgDealt(HSD_GObj* gobj) { return false; }
bool itSScope_Logic21_HitShield(HSD_GObj* gobj) { return false; }
bool itSScope_Logic21_Reflected(HSD_GObj* gobj) { return false; }
bool itSScope_Logic21_ShieldBounced(HSD_GObj* gobj) { return false; }
bool itTaruCann_Logic5_Clanked(HSD_GObj* gobj) { return false; }
bool itTaruCann_Logic5_DmgDealt(HSD_GObj* gobj) { return false; }
bool itTaruCann_Logic5_HitShield(HSD_GObj* gobj) { return false; }
bool itTaruCann_Logic5_Reflected(HSD_GObj* gobj) { return false; }
bool it_3F14_Logic15_DmgDealt(HSD_GObj* gobj) { return false; }
bool it_3F14_Logic15_DmgReceived(HSD_GObj* gobj) { return false; }
bool it_3F14_Logic15_HitShield(HSD_GObj* gobj) { return false; }
bool it_3F14_Logic20_Clanked(HSD_GObj* gobj) { return false; }
bool it_3F14_Logic20_DmgDealt(HSD_GObj* gobj) { return false; }
bool it_3F14_Logic20_DmgReceived(HSD_GObj* gobj) { return false; }
bool it_3F14_Logic20_HitShield(HSD_GObj* gobj) { return false; }
bool it_3F14_Logic2_Clanked(HSD_GObj* gobj) { return false; }
bool it_3F14_Logic2_DmgDealt(HSD_GObj* gobj) { return false; }
bool it_3F14_Logic2_DmgReceived(HSD_GObj* gobj) { return false; }
bool it_3F14_Logic2_HitShield(HSD_GObj* gobj) { return false; }
bool it_3F14_Logic2_Reflected(HSD_GObj* gobj) { return false; }
bool it_3F14_Logic6_DmgDealt(HSD_GObj* gobj) { return false; }
bool it_3F14_Logic6_DmgReceived(HSD_GObj* gobj) { return false; }
bool it_3F14_Logic6_HitShield(HSD_GObj* gobj) { return false; }
bool it_3F14_Logic6_ShieldBounced(HSD_GObj* gobj) { return false; }
bool it_3F14_Logic7_DmgDealt(HSD_GObj* gobj) { return false; }
bool it_3F14_Logic7_DmgReceived(HSD_GObj* gobj) { return false; }
void itBombhei_Logic6_EvtUnk(HSD_GObj* gobj0, HSD_GObj* gobj1) {}
void itBox_Logic1_EvtUnk(HSD_GObj* gobj0, HSD_GObj* gobj1) {}
void itDosei_Logic7_EvtUnk(HSD_GObj* gobj0, HSD_GObj* gobj1) {}
void itFlipper_Logic20_EvtUnk(HSD_GObj* gobj0, HSD_GObj* gobj1) {}
void itFoods_Logic18_EvtUnk(HSD_GObj* gobj0, HSD_GObj* gobj1) {}
void itFreeze_Logic17_EvtUnk(HSD_GObj* gobj0, HSD_GObj* gobj1) {}
void itGShell_Logic14_EvtUnk(HSD_GObj* gobj0, HSD_GObj* gobj1) {}
void itHeart_Logic8_EvtUnk(HSD_GObj* gobj0, HSD_GObj* gobj1) {}
void itKusudama_Logic4_EvtUnk(HSD_GObj* gobj0, HSD_GObj* gobj1) {}
void itRShell_Logic15_EvtUnk(HSD_GObj* gobj0, HSD_GObj* gobj1) {}
void itSScope_Logic21_EvtUnk(HSD_GObj* gobj0, HSD_GObj* gobj1) {}
void itTaruCann_Logic5_EvtUnk(HSD_GObj* gobj0, HSD_GObj* gobj1) {}
void itTaru_Logic2_EvtUnk(HSD_GObj* gobj0, HSD_GObj* gobj1) {}
void itTomato_Logic9_EvtUnk(HSD_GObj* gobj0, HSD_GObj* gobj1) {}

// Fighter / stage stubs for NonMatching files

#include <melee/ft/types.h>
#include <sysdolphin/baselib/mobj.h>

// ftcoll.c (NonMatching)
void ftColl_HurtboxInit(void* fp, void* hurt, void* arg2, void* arg3) {}

// ftmaterial.c (NonMatching)
HSD_MObjInfo ftMObj;

// ftKb_Init.c (NonMatching)
char ftKb_Init_DatFilename[] = "PlKb.dat";
char ftKb_Init_DataName[] = "ftDataKirby";
UNK_T ftKb_Init_UnkMotionStates0[0x2000];

// ftNn_Init.c (NonMatching)
char ftNn_Init_DatFilename[] = "PlNn.dat";
char ftNn_Init_DataName[] = "ftDataNana";

// ftCh_Init.c data stubs
f32 ftCh_Init_804DA070;
f32 ftCh_Init_804DA074;

// ftCh_Init.c function stubs
void ftCh_Init_80156198(HSD_GObj* gobj) {}
void ftCh_Init_80156688(HSD_GObj* gobj) {}
void ftCh_Init_801566B4(HSD_GObj* gobj) {}
void ftCh_Init_801566E0(HSD_GObj* gobj) {}
void ftCh_Init_80156710(HSD_GObj* gobj) {}
void ftCh_Init_80156740(HSD_GObj* gobj) {}
void ftCh_Init_80156770(HSD_GObj* gobj) {}
void ftCh_Init_801567A0(HSD_GObj* gobj) {}
void ftCh_Init_801567AC(HSD_GObj* gobj) {}
void ftCh_Init_801567DC(HSD_GObj* gobj) {}
void ftCh_Init_8015683C(HSD_GObj* gobj) {}
void ftCh_Init_8015686C(HSD_GObj* gobj) {}
void ftCh_Init_80156878(HSD_GObj* gobj) {}
void ftCh_Init_80156884(HSD_GObj* gobj) {}
void ftCh_Init_80156898(HSD_GObj* gobj) {}
void ftCh_Init_801568AC(HSD_GObj* gobj) {}
void ftCh_Init_801568B8(HSD_GObj* gobj) {}
void ftCh_Init_801568E8(HSD_GObj* gobj) {}
void ftCh_Init_80156918(HSD_GObj* gobj) {}
void ftCh_Init_80156948(HSD_GObj* gobj) {}
void ftCh_Init_80156A5C(HSD_GObj* gobj) {}
void fn_801577B4(HSD_GObj* gobj) {}
void fn_8015B548(HSD_GObj* gobj, HSD_GObj* gobj2) {}
void ftCh_GrabUnk1_8015B46C(HSD_GObj* gobj) {}
void ftCh_GrabUnk1_8015B4AC(HSD_GObj* gobj) {}
void ftCh_GrabUnk1_8015B4BC(HSD_GObj* gobj) {}
void ftCh_GrabUnk1_8015B670(HSD_GObj* gobj) {}

// ftdata.c costume data stubs (from NonMatching character init files)
UnkCostumeStruct lbl_804599F0;
UnkCostumeStruct ft_80459A98;
UnkCostumeStruct ft_80459B28;
UnkCostumeStruct ft_80459C10;
UnkCostumeStruct ft_80459CA0;
UnkCostumeStruct ft_80459D18;
UnkCostumeStruct ft_80459D90;
UnkCostumeStruct ft_80459DF0;
UnkCostumeStruct ft_80459E68;
UnkCostumeStruct ft_80459EC8;
UnkCostumeStruct ft_80459F28;
UnkCostumeStruct ft_80459F88;
UnkCostumeStruct ft_8045A000;
UnkCostumeStruct ft_8045A090;
UnkCostumeStruct ft_8045A0F0;
UnkCostumeStruct ft_8045A168;
UnkCostumeStruct ft_8045A1F8;
UnkCostumeStruct ft_8045A270;
UnkCostumeStruct ft_8045A2D0;
UnkCostumeStruct ft_8045A330;
UnkCostumeStruct ft_8045A3A8;
UnkCostumeStruct ft_8045A420;
UnkCostumeStruct ft_8045A480;
UnkCostumeStruct ft_8045A4E0;
UnkCostumeStruct ft_8045A540;
UnkCostumeStruct ft_8045A5B8;
UnkCostumeStruct ft_8045A630;
UnkCostumeStruct ft_8045A648;
UnkCostumeStruct ft_8045A660;
UnkCostumeStruct ft_8045A678;
UnkCostumeStruct ft_8045A690;
UnkCostumeStruct ft_8045A6A8;

// ftCh_Init.c void(void) function stubs
void ftCh_GrabUnk1_8015B2FC(void) {}
void ftCh_GrabUnk1_8015B35C(void) {}
void ftCh_GrabUnk1_8015B390(void) {}
void ftCh_GrabUnk1_8015B3B8(void) {}
void ftCh_GrabUnk1_8015B3EC(void) {}
void ftCh_GrabUnk1_8015B404(void) {}
void ftCh_GrabUnk1_8015B43C(void) {}
void ftCh_Init_80156310(HSD_GObj* gobj) {}

// ftKb_Init.c / ftNn_Init.c additional data
char ftKb_Init_AnimDatFilename[] = "PlKbAJ.dat";
UNK_T ftKb_Init_CostumeStrings[0x100];
UNK_T ftKb_Init_DemoMotionFilenames[0x100];
char ftNn_Init_AnimDatFilename[] = "PlNnAJ.dat";
UNK_T ftNn_Init_CostumeStrings[0x100];
UNK_T ftNn_Init_DemoMotionFilenames[0x100];

// Text/UI stubs
void* devtext_drawlist;
void* devtext_poolhead;
void ifTime_CreateTimers(void) {}
void ifTime_FreeTimers(void) {}
void ifTime_FreeCountdown(void) {}
void ifTime_HideTimers(void) {}
void ifTime_ShowTimers(void) {}
void ifTime_Reset(void) {}
bool ifTime_IsTimerHidden(void) { return false; }
void tyDisplay_8031C2CC(void) {}
void tyDisplay_8031C2EC(void) {}
void vi1202_OnEnter(void) {}
void vi1202_OnFrame(void) {}

// Game data stubs
s32 gm_804D67EC;
s32 gm_804D67F0;
