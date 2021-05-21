#include "global.h"
#include "gx.h"
#include "math.h"
#include "main.h"
#include "FS_rom.h"
#include "PAD_pad.h"
#include "MWC_string.h"
#include "tp.h"
#include "unk_0201B4E8.h"
#include "game_init.h"
#include "registers.h"
#include "heap.h"

#pragma thumb on

extern void FUN_02022450(void);

typedef volatile struct
{
    u8 sys_and_irq_stack[0x3F80];
    u8 svc_stack[0x40];
    u8 reserved[0x38];
    u32 intr_check;
    void * intr_vector;
}
OS_DTCM;

#define DTCM (*(OS_DTCM *)HW_DTCM)

static struct {
    void * contents;
    u32 name_hash;
} UNK_021C4928[128];

struct Main gMain;

void Main_HBlankIntr(BOOL);
void FUN_0201B5CC(void *);

void FUN_02015EA0(void)
{
    DTCM.intr_check |= 1;
    MI_WaitDma(3);
    FUN_0201B5CC(gMain.unk1C);
    gMain.unk30++;
}

void FUN_02015ED4(void)
{
    DTCM.intr_check |= 1;
    MI_WaitDma(3);
}

void FUN_02015EF4(void)
{
    OS_DisableIrqMask(1);
    OS_SetIrqFunction(1, FUN_02015ED4);
    OS_EnableIrqMask(1);
}

void Main_SetVBlankIntrCB(void (*a0)(void *), void * a1)
{
    gMain.vBlankIntr = a0;
    gMain.vBlankIntrArg = a1;
}

void FUN_02015F1C(void)
{
    Main_HBlankIntr(FALSE);
    gMain.hBlankIntr = NULL;
    gMain.hBlankIntrArg = NULL;
}

BOOL FUN_02015F34(void (*a0)(void *), void * a1)
{
    if (a0 == 0)
    {
        Main_HBlankIntr(FALSE);
        gMain.hBlankIntr = NULL;
        gMain.hBlankIntrArg = NULL;
        return TRUE;
    }
    else if (gMain.hBlankIntr == NULL)
    {
        gMain.hBlankIntrArg = a1;
        gMain.hBlankIntr = a0;
        Main_HBlankIntr(TRUE);
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

void FUN_02015F6C(void)
{
    if (gMain.hBlankIntr != NULL)
        gMain.hBlankIntr(gMain.hBlankIntrArg);
}

void Main_HBlankIntr(BOOL a0)
{
    (void)OS_DisableIrq();
    if (!a0)
    {
        (void)OS_GetIrqMask();
        OS_DisableIrqMask(2);
        GX_HBlankIntr(FALSE);
    }
    else
    {
        (void)OS_GetIrqMask();
        OS_SetIrqFunction(2, FUN_02015F6C);
        OS_EnableIrqMask(2);
        GX_HBlankIntr(TRUE);
    }
    (void)OS_EnableIrq();
}

const u32 UNK_020EDB10[][2] = {
    { 0x0000D000, 0x00000000 },
    { 0x00021000, 0x00000000 },
    { 0x00001000, 0x00000000 },
    { 0x0010D800, 0x00000000 }
};

void FUN_02015FC8(void)
{
    u32 data[8];
    u8 digest[16];
    OS_GetLowEntropyData(data);
    MATH_CalcMD5(digest, data, 32);
    u32 csum = 0, i;
    for (i = 0; i < sizeof(digest); i++)
    {
        csum += digest[i];
    }
    csum = (csum << 24) >> 24;
    while (csum & 3)
    {
        csum++;
    }
    FUN_020166C8((u32 *)UNK_020EDB10, 4, 92, (int)csum);
}

void InitSystemForTheGame(void)
{
    OS_Init();
    FX_Init();
    reg_GX_POWCNT = (REGType16v)((reg_GX_POWCNT & ~(REG_GX_POWCNT_GE_MASK | REG_GX_POWCNT_RE_MASK | REG_GX_POWCNT_E2DG_MASK | REG_GX_POWCNT_E2DGB_MASK)) | (REG_GX_POWCNT_GE_MASK | REG_GX_POWCNT_RE_MASK | REG_GX_POWCNT_E2DG_MASK | REG_GX_POWCNT_E2DGB_MASK));
    GX_Init();
    OS_InitTick();
    FUN_02015FC8();
    gMain.unk18 = FUN_0201B580(0xa0, OS_AllocFromArenaLo(OS_ARENA_MAIN, FUN_0201B578(0xa0), 4));
    gMain.unk1C = FUN_0201B580(0x10, OS_AllocFromArenaLo(OS_ARENA_MAIN, FUN_0201B578(0x10), 4));
    gMain.unk20 = FUN_0201B580(0x20, OS_AllocFromArenaLo(OS_ARENA_MAIN, FUN_0201B578(0x20), 4));
    gMain.unk24 = FUN_0201B580(0x04, OS_AllocFromArenaLo(OS_ARENA_MAIN, FUN_0201B578(0x04), 4));
    GX_DispOff();
    reg_GXS_DB_DISPCNT &= ~0x10000;
    reg_GX_POWCNT |= REG_GX_POWCNT_DSEL_MASK;
    OS_SetIrqFunction(1, FUN_02015EA0);
    OS_EnableIrqMask(1);
    OS_EnableIrqMask(0x40000);
    (void)OS_EnableIrq();
    GX_VBlankIntr(TRUE);
    FS_Init(1);
    FUN_02022450();
    u32 size = FS_TryLoadTable(NULL, 0);
    void * table = OS_AllocFromArenaLo(OS_ARENA_MAIN, size, 4);
    GF_ASSERT(table != NULL);
    FS_TryLoadTable(table, size);
    gMain.vBlankIntr = NULL;
    gMain.hBlankIntr = NULL;
    gMain.unk10 = 0;
    gMain.unk14 = 0;
    gMain.unk2C = 0;
    gMain.unk65 = 0;
}

void InitGraphicMemory(void)
{
    GX_SetBankForLCDC(0x1FF);
    MIi_CpuClearFast(0, (void *)HW_LCDC_VRAM, HW_LCDC_VRAM_SIZE);
    GX_DisableBankForLCDC();
    MIi_CpuClearFast(0xC0, (void *)HW_OAM, HW_OAM_SIZE);
    MIi_CpuClearFast(0xC0, (void *)HW_DB_OAM, HW_DB_OAM_SIZE);
    MIi_CpuClearFast(0, (void *)HW_PLTT, HW_PLTT_SIZE);
    MIi_CpuClearFast(0, (void *)HW_DB_PLTT, HW_DB_PLTT_SIZE);
}

void * FUN_020161A4(u32 heap_id, const char * path)
{
    void * ret;

    FSFile file;
    FS_InitFile(&file);
    if (FS_OpenFile(&file, path))
    {
        u32 size = file.prop.file.bottom - file.prop.file.top;
        ret = AllocFromHeap(heap_id, size);
        if (ret != NULL)
        {
            if (size != FS_ReadFile(&file, ret, (s32)size))
            {
                FreeToHeapExplicit(heap_id, ret);
                ret = NULL;
            }
        }
        FS_CloseFile(&file);
    }
    else
        ret = NULL;
    return ret;
}

void FUN_020161F8(const char * path, void ** ptr)
{
    FSFile file;
    FS_InitFile(&file);
    if (FS_OpenFile(&file, path))
    {
        u32 size = file.prop.file.bottom - file.prop.file.top;
        if (*ptr != NULL)
            FS_ReadFile(&file, *ptr, (s32)size);
        FS_CloseFile(&file);
    }
}

u32 FUN_02016230(const s8 * str)
{
    u16 len = (u16)strlen(str);
    u16 sp4;
    if ((len % 4) != 0)
        sp4 = (u16)((len / 4) + 1);
    else
        sp4 = (u16)(len / 4);
    u32 r7 = 0;
    s32 i, j;
    for (i = 0; i < sp4; i++)
    {
        u32 r1 = 0;
        for (j = 0; j < 4; j++)
        {
            int r5 = str[4 * i + j];
            if (r5 == 0)
                break;
            r1 |= r5 << (8 * j);
        }
        r7 ^= r1;
    }
    return r7;
}

int FUN_020162A0(u32 a0)
{
    for (int i = 0; i < 128; i++)
    {
        if (UNK_021C4928[i].name_hash == a0 && UNK_021C4928[i].contents != NULL)
            return i;
    }
    return -1;
}

int FUN_020162C8(void * a0, u32 a1)
{
    for (int i = 0; i < 128; i++)
    {
        if (UNK_021C4928[i].contents == NULL)
        {
            UNK_021C4928[i].contents = a0;
            UNK_021C4928[i].name_hash = a1;
            return i;
        }
    }
    return -1;
}

void FUN_020162FC(void)
{
    for (int i = 127; i > -1; i--)
    {
        if (UNK_021C4928[i].contents != NULL)
        {
            FreeToHeap(UNK_021C4928[i].contents);
            UNK_021C4928[i].contents = NULL;
            UNK_021C4928[i].name_hash = 0;
        }
    }
}

void * FUN_02016324(const s8 * str, u32 heap_id)
{
    s8 sp0[32];
    FSFile file;
    void * ret;
    int r5 = 0;

    if (str[0] == '!')
    {
        strcpy(sp0, str + 1);
        r5 = 1;
    }
    else
    {
        strcpy(sp0, str);
    }
    u32 r7 = FUN_02016230(sp0);
    s32 r0 = FUN_020162A0(r7);
    if (r0 >= 0 && r5 == 0)
    {
        ret = UNK_021C4928[r0].contents;
    }
    else
    {
        FS_InitFile(&file);
        if (FS_OpenFile(&file, (const char *)sp0))
        {
            u32 size = file.prop.file.bottom - file.prop.file.top;
            ret = AllocFromHeap(heap_id, size);
            if (ret != NULL)
            {
                if (size != FS_ReadFile(&file, ret, (s32)size))
                {
                    FreeToHeap(ret);
                    ret = NULL;
                }
            }
            FS_CloseFile(&file);
            if (r5 == 0)
                FUN_020162C8(ret, r7);
        }
        else
            ret = NULL;
    }
    return ret;
}

void FUN_020163BC(void)
{
    TPCalibrateParam tp;
    gMain.unk34 = 0;
    gMain.unk38 = 0;
    gMain.unk3C = 0;
    gMain.unk40 = 0;
    gMain.unk44 = 0;
    gMain.newKeys = 0;
    gMain.newAndRepeatedKeys = 0;
    gMain.unk50 = 0;
    gMain.unk54 = 8;
    gMain.unk58 = 15;
    gMain.unk5C = 0;
    gMain.unk5E = 0;
    gMain.unk60 = 0;
    gMain.unk62 = 0;
    gMain.unk64 = 0;
    TP_Init();
    if (TP_GetUserInfo(&tp) == TRUE)
        TP_SetCalibrateParam(&tp);
    else
    {
        tp.x0 = 686;
        tp.y0 = 1420;
        tp.xDotSize = 3621;
        tp.yDotSize = 4616;
        TP_SetCalibrateParam(&tp);
    }
}

void FUN_02016438(u8 a0)
{
    gMain.unk66 = a0;
}

void FUN_02016444(u8 a0)
{
    gMain.unk67 |= a0;
}

void FUN_02016454(u8 a0)
{
    gMain.unk67 &= ~a0;
}

void FUN_02016464(void)
{
    TPData raw, calib;
    if (PAD_DetectFold())
    {
        gMain.newKeys = 0;
        gMain.unk44 = 0;
        gMain.newAndRepeatedKeys = 0;
        gMain.unk60 = 0;
        gMain.unk62 = 0;
        return;
    }
    u32 r0 = PAD_Read();
    gMain.unk40 = gMain.unk3C = (r0 ^ gMain.unk38) & r0;
    if (r0 != 0 && gMain.unk38 == r0)
    {
        if (--gMain.unk50 == 0)
        {
            gMain.unk40 = r0;
            gMain.unk50 = gMain.unk54;
        }
    }
    else
    {
        gMain.unk50 = gMain.unk58;
    }
    gMain.unk38 = r0;
    gMain.newKeys = gMain.unk3C;
    gMain.unk44 = r0;
    gMain.newAndRepeatedKeys = gMain.unk40;
    FUN_02016568();
    if (gMain.unk64 == 0)
    {
        while (TP_RequestRawSampling(&raw))
            ;
    }
    else
        TP_GetLatestRawPointInAuto(&raw);
    TP_GetCalibratedPoint(&calib, &raw);
    if (calib.validity == 0)
    {
        gMain.unk5C = calib.x;
        gMain.unk5E = calib.y;
    }
    else if (gMain.unk62)
    {
        switch (calib.validity)
        {
        case 1:
            gMain.unk5E = calib.y;
            break;
        case 2:
            gMain.unk5C = calib.x;
            break;
        case 3:
            break;
        }
    }
    else
        calib.touch = 0;
    gMain.unk60 = (u16)((gMain.unk62 ^ calib.touch) & calib.touch);
    gMain.unk62 = calib.touch;
}

void FUN_02016568(void)
{
    switch (gMain.unk34)
    {
    case 0: // Normal
        break;
    case 1: // Start = X
        if (gMain.newKeys & PAD_BUTTON_START)
            gMain.newKeys |= PAD_BUTTON_X;
        if (gMain.unk44 & PAD_BUTTON_START)
            gMain.unk44 |= PAD_BUTTON_X;
        if (gMain.newAndRepeatedKeys & PAD_BUTTON_START)
            gMain.newAndRepeatedKeys |= PAD_BUTTON_X;
        break;
    case 2: // Swap X and Y; unused in the retail game
        {
            u32 r1 = 0;
            if (gMain.newKeys & PAD_BUTTON_X)
            {
                r1 |= PAD_BUTTON_Y;
            }
            if (gMain.newKeys & PAD_BUTTON_Y)
            {
                r1 |= PAD_BUTTON_X;
            }
            gMain.newKeys &= 0xF3FF;
            gMain.newKeys |= r1;
        }
        {
            u32 r1 = 0;
            if (gMain.unk44 & PAD_BUTTON_X)
            {
                r1 |= PAD_BUTTON_Y;
            }
            if (gMain.unk44 & PAD_BUTTON_Y)
            {
                r1 |= PAD_BUTTON_X;
            }
            gMain.unk44 &= 0xF3FF;
            gMain.unk44 |= r1;
        }
        {
            u32 r1 = 0;
            if (gMain.newAndRepeatedKeys & PAD_BUTTON_X)
            {
                r1 |= PAD_BUTTON_Y;
            }
            if (gMain.newAndRepeatedKeys & PAD_BUTTON_Y)
            {
                r1 |= PAD_BUTTON_X;
            }
            gMain.newAndRepeatedKeys &= 0xF3FF;
            gMain.newAndRepeatedKeys |= r1;
        }
        break;
    case 3: // L = A
        if (gMain.newKeys & PAD_BUTTON_L)
            gMain.newKeys |= PAD_BUTTON_A;
        if (gMain.unk44 & PAD_BUTTON_L)
            gMain.unk44 |= PAD_BUTTON_A;
        if (gMain.newAndRepeatedKeys & PAD_BUTTON_L)
            gMain.newAndRepeatedKeys |= PAD_BUTTON_A;
        gMain.newKeys &= 0xFCFF;
        gMain.unk44 &= 0xFCFF;
        gMain.newAndRepeatedKeys &= 0xFCFF;
    }
}

void FUN_0201669C(int x, int y)
{
    gMain.unk54 = x;
    gMain.unk58 = y;
}

void FUN_020166A8(u8 a0)
{
    gMain.unk68 |= a0;
}

void FUN_020166B8(u8 a0)
{
    gMain.unk68 &= ~a0;
}
