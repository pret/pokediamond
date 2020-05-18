#include "global.h"
#include "main.h"
#include "PAD_pad.h"
#include "poke_overlay.h"

FS_EXTERN_OVERLAY(MODULE_52);
FS_EXTERN_OVERLAY(MODULE_63);

#define SOFT_RESET_KEY (PAD_BUTTON_L | PAD_BUTTON_R | PAD_BUTTON_START | PAD_BUTTON_SELECT)

extern struct Unk21C48B8 gUnknown21C48B8;

extern void OS_WaitIrq();
extern void FUN_02016438(s32);
extern void InitSystemForTheGame(void);
extern void InitGraphicMemory(void);
extern void FUN_020163BC(void);
extern void FUN_02022294(void);
extern void FUN_0201259C(void);
extern void FUN_02000DF4(void);
extern void FUN_02002C14(void);
extern void FUN_02002C50(int, int);
extern struct UnkStruct_021C59C8 * FUN_0202254C(void);
extern void FUN_02003B98(int, int);
extern int FUN_02029EF8(struct UnkStruct_021C59C8 *);
extern int LoadPlayerDataAddress(struct UnkStruct_021C59C8 *);
extern void FUN_02020AFC(void);
extern int FUN_020337E8(int);
extern void FUN_02034188(int, int);
extern int FUN_020227FC(struct UnkStruct_021C59C8 *);
extern void FUN_02089D90(int);
extern void FUN_02000E7C(FSOverlayID, struct Unk21DBE18 *);
extern void InitializeMainRNG(void);
extern void FUN_0200A2AC(void);
extern void FUN_02015E30(void);
extern void FUN_02000EE8(void);
void DoSoftReset(u32 parameter);
extern BOOL FUN_0202FB80(void);
extern void FUN_02000E0C(void);
extern void FUN_0201B5CC(int);
extern void FUN_020125D4(void);
extern void FUN_02015E60(void);
extern void FUN_020222C4(void);
extern void FUN_0200A318(void);
extern void FUN_0200E2D8(void);
extern void FUN_02003C10(void);
extern void FUN_02000FE8(void);
extern void FUN_02016464(void);

extern struct Unk21DBE18 MOD63_UNK_021DBE18; 
extern struct Unk21DBE18 MOD52_UNK_021D76C8;


THUMB_FUNC void NitroMain(void)
{
    InitSystemForTheGame();
    InitGraphicMemory();
    FUN_020163BC();
    FUN_02016438(0);

    PM_GetBackLight(&gBacklightTop_2.unk0, NULL);

    FUN_02022294();
    FUN_0201259C();
    FUN_02000DF4();
    FUN_02002C14();
    FUN_02002C50(0, 3);
    FUN_02002C50(1, 3);
    FUN_02002C50(3, 3);
    gBacklightTop.unk18 = -1;
    gBacklightTop.unk20 = FUN_0202254C();
    FUN_02003B98(FUN_02029EF8(gBacklightTop.unk20), LoadPlayerDataAddress(gBacklightTop.unk20));
    FUN_02020AFC();
    if (FUN_020337E8(3) == 3)
        FUN_02034188(3, 0);
    if (FUN_020227FC(gBacklightTop.unk20) == 0)
    {
        FUN_02089D90(0);
    }
    else
    {
        switch (*((s32 *)HW_RESET_PARAMETER_BUF))
        {
        case 0:
            gBacklightTop.unk1C = 0;
            FUN_02000E7C(FS_OVERLAY_ID(MODULE_63), &MOD63_UNK_021DBE18);
            break;
        case 1:
            gBacklightTop.unk1C = 1;
            FUN_02000E7C(FS_OVERLAY_ID(MODULE_52), &MOD52_UNK_021D76C8);
            break;
        default:
            ErrorHandling();
            break;
        }
    }
    gUnknown21C48B8.unk6C = 1;
    gUnknown21C48B8.unk30 = 0;
    InitializeMainRNG();
    FUN_0200A2AC();
    FUN_02015E30();
    gBacklightTop.unk4 = 0;
    for (;;)
    {
        FUN_02000EE8();
        FUN_02000FE8();
        FUN_02016464();
        if ((gUnknown21C48B8.unk38 & SOFT_RESET_KEY) == SOFT_RESET_KEY && !gUnk021C4918.unk8) // soft reset?
        {
            DoSoftReset(0); // soft reset?
        }
        if (FUN_0202FB80())
        {
            FUN_02000E0C();
            FUN_0201B5CC(gUnknown21C48B8.unk18);
            FUN_0201B5CC(gUnknown21C48B8.unk24);
            if (!gUnknown21C48B8.unk30)
            {
                OS_WaitIrq(1, 1);
                gUnknown21C48B8.unk2C++;
            }
        }
        FUN_020125D4();
        FUN_02015E60();
        FUN_020222C4();
        FUN_0201B5CC(gUnknown21C48B8.unk24);
        OS_WaitIrq(1, 1);
        gUnknown21C48B8.unk2C++;
        gUnknown21C48B8.unk30 = 0;
        FUN_0200A318();
        FUN_0200E2D8();
        if (gUnknown21C48B8.unk0)
            gUnknown21C48B8.unk0(gUnknown21C48B8.unk4);
        FUN_02003C10();
        FUN_0201B5CC(gUnknown21C48B8.unk20);
    }
}
