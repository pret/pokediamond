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
} sFileCache[128];

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
    csum %= 256;
    while (csum & 3)
    {
        csum++;
    }
    FUN_020166C8((u32 *)UNK_020EDB10, 4, 92, csum);
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
    MI_CpuClearFast((void *)HW_LCDC_VRAM, HW_LCDC_VRAM_SIZE);
    GX_DisableBankForLCDC();
    MI_CpuFillFast((void *)HW_OAM, 0xC0, HW_OAM_SIZE);
    MI_CpuFillFast((void *)HW_DB_OAM, 0xC0, HW_DB_OAM_SIZE);
    MI_CpuClearFast((void *)HW_PLTT, HW_PLTT_SIZE);
    MI_CpuClearFast((void *)HW_DB_PLTT, HW_DB_PLTT_SIZE);
}

void * AllocAndReadFile(u32 heap_id, const char * path)
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

void OpenAndReadWholeFile(const char * path, void ** ptr)
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

u32 GetFilenameHash(const s8 * str)
{
    u16 len = (u16)strlen(str);
    u16 numWords;
    if ((len % 4) != 0)
        numWords = (u16)((len / 4) + 1);
    else
        numWords = (u16)(len / 4);
    u32 hash = 0;
    s32 i, j;
    for (i = 0; i < numWords; i++)
    {
        u32 curWord = 0;
        for (j = 0; j < 4; j++)
        {
            int curChar = str[4 * i + j];
            if (curChar == 0)
                break;
            curWord |= curChar << (8 * j);
        }
        hash ^= curWord;
    }
    return hash;
}

int GetFileCacheId(u32 hash)
{
    for (int i = 0; i < 128; i++)
    {
        if (sFileCache[i].name_hash == hash && sFileCache[i].contents != NULL)
            return i;
    }
    return -1;
}

int AddFileToCache(void * contents, u32 hash)
{
    for (int i = 0; i < 128; i++)
    {
        if (sFileCache[i].contents == NULL)
        {
            sFileCache[i].contents = contents;
            sFileCache[i].name_hash = hash;
            return i;
        }
    }
    return -1;
}

void ClearFileCache(void)
{
    for (int i = 127; i > -1; i--)
    {
        if (sFileCache[i].contents != NULL)
        {
            FreeToHeap(sFileCache[i].contents);
            sFileCache[i].contents = NULL;
            sFileCache[i].name_hash = 0;
        }
    }
}

void * OpenFileCached(const s8 * str, u32 heap_id)
{
    s8 filenameBuf[32];
    FSFile file;
    void * ret;
    int skipCache = 0;

    if (str[0] == '!')
    {
        strcpy(filenameBuf, str + 1);
        skipCache = 1;
    }
    else
    {
        strcpy(filenameBuf, str);
    }
    u32 hash = GetFilenameHash(filenameBuf);
    s32 cacheId = GetFileCacheId(hash);
    if (cacheId >= 0 && skipCache == 0)
    {
        ret = sFileCache[cacheId].contents;
    }
    else
    {
        FS_InitFile(&file);
        if (FS_OpenFile(&file, (const char *)filenameBuf))
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
            if (skipCache == 0)
                AddFileToCache(ret, hash);
        }
        else
            ret = NULL;
    }
    return ret;
}

void InitKeypadAndTouchpad(void)
{
    TPCalibrateParam tp;
    gMain.buttonMode = 0;
    gMain.heldKeysRaw = 0;
    gMain.newKeysRaw = 0;
    gMain.newAndRepeatedKeysRaw = 0;
    gMain.heldKeys = 0;
    gMain.newKeys = 0;
    gMain.newAndRepeatedKeys = 0;
    gMain.keyRepeatCounter = 0;
    gMain.keyRepeatContinueDelay = 8;
    gMain.keyRepeatStartDelay = 15;
    gMain.touchX = 0;
    gMain.touchY = 0;
    gMain.touchNew = 0;
    gMain.touchHeld = 0;
    gMain.touchpadReadAuto = 0;
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

void ReadKeypadAndTocuhpad(void)
{
    TPData raw, calib;
    if (PAD_DetectFold())
    {
        // Can't press any buttons while the lid is closed.
        gMain.newKeys = 0;
        gMain.heldKeys = 0;
        gMain.newAndRepeatedKeys = 0;
        gMain.touchNew = 0;
        gMain.touchHeld = 0;
        return;
    }

    u32 padRead = PAD_Read();

    // newKeys is all keys that were pressed on this frame but
    // not the last frame.
    gMain.newAndRepeatedKeysRaw = gMain.newKeysRaw = (padRead ^ gMain.heldKeysRaw) & padRead;

    // If you are holding down buttons, indicate them "repeated" every few frames
    // as defined by .keyRepeatStartDelay and .keyRepeatContinueDelay.
    // Same logic as gen3, but fixes the bug where the
    // remapped keys are incorrectly used here.
    // See also: pokeemerald/src/main.c:ReadKeys
    if (padRead != 0 && gMain.heldKeysRaw == padRead)
    {
        if (--gMain.keyRepeatCounter == 0)
        {
            gMain.newAndRepeatedKeysRaw = padRead;
            gMain.keyRepeatCounter = gMain.keyRepeatContinueDelay;
        }
    }
    else
    {
        gMain.keyRepeatCounter = gMain.keyRepeatStartDelay;
    }
    gMain.heldKeysRaw = padRead;

    // Apply the button mode option to the read key input
    gMain.newKeys = gMain.newKeysRaw;
    gMain.heldKeys = padRead;
    gMain.newAndRepeatedKeys = gMain.newAndRepeatedKeysRaw;
    ApplyButtonModeToInput();

    // Read the touchpad. New to gen 4.
    if (gMain.touchpadReadAuto == 0)
    {
        while (TP_RequestRawSampling(&raw))
            ;
    }
    else
        TP_GetLatestRawPointInAuto(&raw);
    TP_GetCalibratedPoint(&calib, &raw);

    // If the touchpad is valid, we gucci.
    if (calib.validity == TP_VALIDITY_VALID)
    {
        gMain.touchX = calib.x;
        gMain.touchY = calib.y;
    }

    // If the touchpad was used last frame, salvage what we can.
    else if (gMain.touchHeld)
    {
        switch (calib.validity)
        {
        case TP_VALIDITY_INVALID_X:
            gMain.touchY = calib.y;
            break;
        case TP_VALIDITY_INVALID_Y:
            gMain.touchX = calib.x;
            break;
        case TP_VALIDITY_INVALID_XY:
            break;
        }
    }
    // What was read from the touchpad was not salvageable.
    // Ignore touch input.
    else
        calib.touch = 0;
    gMain.touchNew = (u16)((gMain.touchHeld ^ calib.touch) & calib.touch);
    gMain.touchHeld = calib.touch;
}

void ApplyButtonModeToInput(void)
{
    switch (gMain.buttonMode)
    {
    case 0: // Normal
        break;
    case 1: // Start = X
        if (gMain.newKeys & PAD_BUTTON_START)
            gMain.newKeys |= PAD_BUTTON_X;
        if (gMain.heldKeys & PAD_BUTTON_START)
            gMain.heldKeys |= PAD_BUTTON_X;
        if (gMain.newAndRepeatedKeys & PAD_BUTTON_START)
            gMain.newAndRepeatedKeys |= PAD_BUTTON_X;
        break;
    case 2: // Swap X and Y; unused in the retail game
        {
            u32 swapMask = 0;
            if (gMain.newKeys & PAD_BUTTON_X)
            {
                swapMask |= PAD_BUTTON_Y;
            }
            if (gMain.newKeys & PAD_BUTTON_Y)
            {
                swapMask |= PAD_BUTTON_X;
            }
            gMain.newKeys &= ((PAD_BUTTON_X | PAD_BUTTON_Y) ^ 0xFFFF);;
            gMain.newKeys |= swapMask;
        }
        {
            u32 swapMask = 0;
            if (gMain.heldKeys & PAD_BUTTON_X)
            {
                swapMask |= PAD_BUTTON_Y;
            }
            if (gMain.heldKeys & PAD_BUTTON_Y)
            {
                swapMask |= PAD_BUTTON_X;
            }
            gMain.heldKeys &= ((PAD_BUTTON_X | PAD_BUTTON_Y) ^ 0xFFFF);
            gMain.heldKeys |= swapMask;
        }
        {
            u32 swapMask = 0;
            if (gMain.newAndRepeatedKeys & PAD_BUTTON_X)
            {
                swapMask |= PAD_BUTTON_Y;
            }
            if (gMain.newAndRepeatedKeys & PAD_BUTTON_Y)
            {
                swapMask |= PAD_BUTTON_X;
            }
            gMain.newAndRepeatedKeys &= ((PAD_BUTTON_X | PAD_BUTTON_Y) ^ 0xFFFF);
            gMain.newAndRepeatedKeys |= swapMask;
        }
        break;
    case 3: // L = A
        if (gMain.newKeys & PAD_BUTTON_L)
            gMain.newKeys |= PAD_BUTTON_A;
        if (gMain.heldKeys & PAD_BUTTON_L)
            gMain.heldKeys |= PAD_BUTTON_A;
        if (gMain.newAndRepeatedKeys & PAD_BUTTON_L)
            gMain.newAndRepeatedKeys |= PAD_BUTTON_A;
        gMain.newKeys &= ((PAD_BUTTON_L | PAD_BUTTON_R) ^ 0xFFFF);
        gMain.heldKeys &= ((PAD_BUTTON_L | PAD_BUTTON_R) ^ 0xFFFF);
        gMain.newAndRepeatedKeys &= ((PAD_BUTTON_L | PAD_BUTTON_R) ^ 0xFFFF);
    }
}

void SetKeyRepeatTimers(int x, int y)
{
    gMain.keyRepeatContinueDelay = x;
    gMain.keyRepeatStartDelay = y;
}

void SetSoftResetDisableMask(u8 a0)
{
    gMain.softResetDisabled |= a0;
}

void ClearSoftResetDisableMask(u8 a0)
{
    gMain.softResetDisabled &= ~a0;
}
