#include "error_message_reset.h"
#include "GX_layers.h"
#include "unk_02031734.h"
#include "unk_0202F150.h"
#include "unk_02016B94.h"



const struct UnkStruct4 UNK_020FF49C = { 0, 3, 3, 0x1a, 0x12, 1, 0x23 };

const u32 UNK_020FF4A4[2] = { 0x00020000, 0x00000000 };

const struct GraphicsModes UNK_020FF4AC = { mode1 : 1 };

const struct UnkStruct1 UNK_020FF4BC = { 0, 0, 0x800, 0, 1, 0, 0, 6, 0, 1, 0, 0, 0 };

const struct GraphicsBanks UNK_020FF4D8 = { bg : 3 };

u32 sErrorMessagePrinterLock;

extern void FUN_0200E3A0(PMLCDTarget, int);
extern void FUN_0200CB00(struct UnkStruct2 *param0, u32 param1, u32 param2, u32 param3, u8 param4, u32 param5);
extern void FUN_02002ED0(u32 param0, u32 param1, u32 param2);
extern void FUN_0200CCA4(struct Window *param0, u32 param1, u32 param2, u32 param3);
extern void FUN_0200E394(u32 param0);
extern void FUN_0200A274(u32 param0, u32 param1, u32 param2);

THUMB_FUNC void VBlankHandler()
{
    *(vu32 *)HW_INTR_CHECK_BUF |= 1;

    MI_WaitDma(3);
}

THUMB_FUNC void PrintErrorMessageAndReset()
{

    struct UnkStruct2 *ptr;
    struct Window buf;

    if (sErrorMessagePrinterLock != 1)
    {
        sErrorMessagePrinterLock = 1;
        OS_SetArenaHi(OS_ARENA_MAIN, OS_GetInitArenaHi(OS_ARENA_MAIN));
        OS_SetArenaLo(OS_ARENA_MAIN, OS_GetInitArenaLo(OS_ARENA_MAIN));

        FUN_020166C8((u32 *)UNK_020FF4A4, 1, 1, 0);
        FUN_0200E3A0(PM_LCD_TOP, 0);
        FUN_0200E3A0(PM_LCD_BOTTOM, 0);

        OS_DisableIrqMask(1);
        OS_SetIrqFunction(1, &VBlankHandler);
        OS_EnableIrqMask(1);

        Main_SetVBlankIntrCB(NULL, NULL);

        FUN_02015F34(NULL, NULL);
        GX_DisableEngineALayers();
        GX_DisableEngineBLayers();

        reg_GX_DISPCNT &= 0xFFFFE0FF;
        reg_GXS_DB_DISPCNT &= 0xFFFFE0FF;

        FUN_0201669C(4, 8);

        gMain.unk65 = 0;
        GX_SwapDisplay();

        reg_G2_BLDCNT = 0;
        reg_G2S_DB_BLDCNT = 0;
        reg_GX_DISPCNT &= 0xFFFF1FFF;
        reg_GXS_DB_DISPCNT &= 0xFFFF1FFF;

        GX_SetBanks(&UNK_020FF4D8);
        ptr = FUN_02016B94(0);
        FUN_02016BBC(&UNK_020FF4AC);

        FUN_02016C18(ptr, 0, &UNK_020FF4BC, 0);
        FUN_02018744(ptr, 0);

        FUN_0200CB00(ptr, 0, 503, 2, 0, 0);

        FUN_02002ED0(0, 0x20, 0);
        FUN_02017F18(0, 0x20, 0, 0);
        FUN_02017FE4(0, 0x6C21);
        FUN_02017FE4(4, 0x6C21);

        struct MsgData *msg_data = NewMsgDataFromNarc(1, NARC_MSGDATA_MSG, 0xc8, 0);
        struct String *str = String_ctor(6 << 6, 0);

        FUN_0201BD5C();
        FUN_02019150(ptr, &buf, &UNK_020FF49C);
        FUN_020196F4(&buf, 15, 0, 0, 0xd0, 0x90);
        FUN_0200CCA4(&buf, 0, 0x1f7, 2);

        ReadMsgDataIntoString(msg_data, 3, str);

        AddTextPrinterParameterized((u32)(&buf), 0, (const u16 *)str, 0, 0, 0, NULL); // wtf

        String_dtor(str);
        GX_BothDispOn();
        FUN_0200E394(0);
        FUN_0200E394(1);
        FUN_0200A274(0, 0x3f, 3);
        FUN_02032DAC();

    lid:
        HandleDSLidAction();
        FUN_0202FB80();
        if (!FUN_02033678())
        {
            OS_WaitIrq(1, 1);
            goto lid;
        }


    lid2:
        HandleDSLidAction();
        if (!((u16)(((reg_PAD_KEYINPUT | *(vu16 *)HW_BUTTON_XY_BUF) ^ 0x2FFF) & 0x2FFF) & 1))
        {
            OS_WaitIrq(1, 1);
            goto lid2;
        }

        FUN_0200E3A0(PM_LCD_TOP, 0x7FFF);
        FUN_0200E3A0(PM_LCD_BOTTOM, 0x7FFF);

        FUN_02019178(&buf);

        DestroyMsgData(msg_data);
        FreeToHeap(ptr);

        OS_ResetSystem(0);
    }
}
