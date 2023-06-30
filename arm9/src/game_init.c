#include "global.h"
#include "gx.h"
#include "math.h"
#include "main.h"
#include "FS_rom.h"
#include "PAD_pad.h"
#include "string.h"
#include "tp.h"
#include "unk_0201B4E8.h"
#include "unk_02022450.h"
#include "game_init.h"
#include "registers.h"
#include "heap.h"
#include "OS_interrupt.h"

static struct {
    void * contents;
    u32 name_hash;
} sFileCache[128];

struct Main gSystem;

void Main_ToggleHBlankInterrupt(BOOL enableFlag);
void sub_0201B5CC(void *);

void sub_02015EA0(void)
{
    DTCM.intr_check |= 1;
    MI_WaitDma(3);
    sub_0201B5CC(gSystem.unk1C);
    gSystem.unk30++;
}

void sub_02015ED4(void)
{
    DTCM.intr_check |= 1;
    MI_WaitDma(3);
}

void sub_02015EF4(void)
{
    OS_DisableIrqMask(1);
    OS_SetIrqFunction(1, sub_02015ED4);
    OS_EnableIrqMask(1);
}

void Main_SetVBlankIntrCB(void (*a0)(void *), void * a1)
{
    gSystem.vBlankIntr = a0;
    gSystem.vBlankIntrArg = a1;
}

void sub_02015F1C(void)
{
    Main_ToggleHBlankInterrupt(FALSE);
    gSystem.hBlankIntr = NULL;
    gSystem.hBlankIntrArg = NULL;
}

BOOL Main_SetHBlankIntrCB(void (*a0)(void *), void * a1)
{
    if (a0 == 0)
    {
        Main_ToggleHBlankInterrupt(FALSE);
        gSystem.hBlankIntr = NULL;
        gSystem.hBlankIntrArg = NULL;
        return TRUE;
    }
    else if (gSystem.hBlankIntr == NULL)
    {
        gSystem.hBlankIntrArg = a1;
        gSystem.hBlankIntr = a0;
        Main_ToggleHBlankInterrupt(TRUE);
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

void Main_CallHBlankCallback(void)
{
    if (gSystem.hBlankIntr != NULL)
        gSystem.hBlankIntr(gSystem.hBlankIntrArg);
}

void Main_ToggleHBlankInterrupt(BOOL enableFlag)
{
    (void)OS_DisableIrq();
    if (!enableFlag)
    {
        (void)OS_GetIrqMask();
        OS_DisableIrqMask(OS_IE_H_BLANK);
        GX_HBlankIntr(FALSE);
    }
    else
    {
        (void)OS_GetIrqMask();
        OS_SetIrqFunction(OS_IE_H_BLANK, Main_CallHBlankCallback);
        OS_EnableIrqMask(OS_IE_H_BLANK);
        GX_HBlankIntr(TRUE);
    }
    (void)OS_EnableIrq();
}

const struct HeapParam UNK_020EDB10[] = {
    { 0x00D000, OS_ARENA_MAIN },
    { 0x021000, OS_ARENA_MAIN },
    { 0x001000, OS_ARENA_MAIN },
    { 0x10D800, OS_ARENA_MAIN }
};

void sub_02015FC8(void)
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
    InitHeapSystem(UNK_020EDB10, NELEMS(UNK_020EDB10), 92, csum);
}

void InitSystemForTheGame(void)
{
    OS_Init();
    FX_Init();
    reg_GX_POWCNT = (REGType16v)((reg_GX_POWCNT & ~(REG_GX_POWCNT_GE_MASK | REG_GX_POWCNT_RE_MASK | REG_GX_POWCNT_E2DG_MASK | REG_GX_POWCNT_E2DGB_MASK)) | (REG_GX_POWCNT_GE_MASK | REG_GX_POWCNT_RE_MASK | REG_GX_POWCNT_E2DG_MASK | REG_GX_POWCNT_E2DGB_MASK));
    GX_Init();
    OS_InitTick();
    sub_02015FC8();
    gSystem.unk18 = sub_0201B580(0xa0, OS_AllocFromArenaLo(OS_ARENA_MAIN, sub_0201B578(0xa0), 4));
    gSystem.unk1C = sub_0201B580(0x10, OS_AllocFromArenaLo(OS_ARENA_MAIN, sub_0201B578(0x10), 4));
    gSystem.unk20 = sub_0201B580(0x20, OS_AllocFromArenaLo(OS_ARENA_MAIN, sub_0201B578(0x20), 4));
    gSystem.unk24 = sub_0201B580(0x04, OS_AllocFromArenaLo(OS_ARENA_MAIN, sub_0201B578(0x04), 4));
    GX_DispOff();
    reg_GXS_DB_DISPCNT &= ~0x10000;
    reg_GX_POWCNT |= REG_GX_POWCNT_DSEL_MASK;
    OS_SetIrqFunction(1, sub_02015EA0);
    OS_EnableIrqMask(1);
    OS_EnableIrqMask(0x40000);
    (void)OS_EnableIrq();
    GX_VBlankIntr(TRUE);
    FS_Init(1);
    sub_02022450();
    u32 size = FS_TryLoadTable(NULL, 0);
    void * table = OS_AllocFromArenaLo(OS_ARENA_MAIN, size, 4);
    GF_ASSERT(table != NULL);
    FS_TryLoadTable(table, size);
    gSystem.vBlankIntr = NULL;
    gSystem.hBlankIntr = NULL;
    gSystem.unk10 = 0;
    gSystem.unk14 = 0;
    gSystem.unk2C = 0;
    gSystem.screensFlipped = 0;
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

void * AllocAndReadFile(HeapID heapId, const char * path)
{
    void * ret;

    FSFile file;
    FS_InitFile(&file);
    if (FS_OpenFile(&file, path))
    {
        u32 size = file.prop.file.bottom - file.prop.file.top;
        ret = AllocFromHeap(heapId, size);
        if (ret != NULL)
        {
            if (size != FS_ReadFile(&file, ret, (s32)size))
            {
                FreeToHeapExplicit(heapId, ret);
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

void * OpenFileCached(const s8 * str, HeapID heapId)
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
            ret = AllocFromHeap(heapId, size);
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
    gSystem.buttonMode = 0;
    gSystem.heldKeysRaw = 0;
    gSystem.newKeysRaw = 0;
    gSystem.newAndRepeatedKeysRaw = 0;
    gSystem.heldKeys = 0;
    gSystem.newKeys = 0;
    gSystem.newAndRepeatedKeys = 0;
    gSystem.keyRepeatCounter = 0;
    gSystem.keyRepeatContinueDelay = 8;
    gSystem.keyRepeatStartDelay = 15;
    gSystem.touchX = 0;
    gSystem.touchY = 0;
    gSystem.touchNew = 0;
    gSystem.touchHeld = 0;
    gSystem.touchpadReadAuto = 0;
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

void sub_02016438(u8 a0)
{
    gSystem.gbaCartId = a0;
}

void sub_02016444(u8 a0)
{
    gSystem.unk67 |= a0;
}

void sub_02016454(u8 a0)
{
    gSystem.unk67 &= ~a0;
}

void ReadKeypadAndTocuhpad(void)
{
    TPData raw, calib;
    if (PAD_DetectFold())
    {
        // Can't press any buttons while the lid is closed.
        gSystem.newKeys = 0;
        gSystem.heldKeys = 0;
        gSystem.newAndRepeatedKeys = 0;
        gSystem.touchNew = 0;
        gSystem.touchHeld = 0;
        return;
    }

    u32 padRead = PAD_Read();

    // newKeys is all keys that were pressed on this frame but
    // not the last frame.
    gSystem.newAndRepeatedKeysRaw = gSystem.newKeysRaw = (padRead ^ gSystem.heldKeysRaw) & padRead;

    // If you are holding down buttons, indicate them "repeated" every few frames
    // as defined by .keyRepeatStartDelay and .keyRepeatContinueDelay.
    // Same logic as gen3, but fixes the bug where the
    // remapped keys are incorrectly used here.
    // See also: pokeemerald/src/main.c:ReadKeys
    if (padRead != 0 && gSystem.heldKeysRaw == padRead)
    {
        if (--gSystem.keyRepeatCounter == 0)
        {
            gSystem.newAndRepeatedKeysRaw = padRead;
            gSystem.keyRepeatCounter = gSystem.keyRepeatContinueDelay;
        }
    }
    else
    {
        gSystem.keyRepeatCounter = gSystem.keyRepeatStartDelay;
    }
    gSystem.heldKeysRaw = padRead;

    // Apply the button mode option to the read key input
    gSystem.newKeys = gSystem.newKeysRaw;
    gSystem.heldKeys = padRead;
    gSystem.newAndRepeatedKeys = gSystem.newAndRepeatedKeysRaw;
    ApplyButtonModeToInput();

    // Read the touchpad. New to gen 4.
    if (gSystem.touchpadReadAuto == 0)
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
        gSystem.touchX = calib.x;
        gSystem.touchY = calib.y;
    }

    // If the touchpad was used last frame, salvage what we can.
    else if (gSystem.touchHeld)
    {
        switch (calib.validity)
        {
        case TP_VALIDITY_INVALID_X:
            gSystem.touchY = calib.y;
            break;
        case TP_VALIDITY_INVALID_Y:
            gSystem.touchX = calib.x;
            break;
        case TP_VALIDITY_INVALID_XY:
            break;
        }
    }
    // What was read from the touchpad was not salvageable.
    // Ignore touch input.
    else
        calib.touch = 0;
    gSystem.touchNew = (u16)((gSystem.touchHeld ^ calib.touch) & calib.touch);
    gSystem.touchHeld = calib.touch;
}

void ApplyButtonModeToInput(void)
{
    switch (gSystem.buttonMode)
    {
    case 0: // Normal
        break;
    case 1: // Start = X
        if (gSystem.newKeys & PAD_BUTTON_START)
            gSystem.newKeys |= PAD_BUTTON_X;
        if (gSystem.heldKeys & PAD_BUTTON_START)
            gSystem.heldKeys |= PAD_BUTTON_X;
        if (gSystem.newAndRepeatedKeys & PAD_BUTTON_START)
            gSystem.newAndRepeatedKeys |= PAD_BUTTON_X;
        break;
    case 2: // Swap X and Y; unused in the retail game
        {
            u32 swapMask = 0;
            if (gSystem.newKeys & PAD_BUTTON_X)
            {
                swapMask |= PAD_BUTTON_Y;
            }
            if (gSystem.newKeys & PAD_BUTTON_Y)
            {
                swapMask |= PAD_BUTTON_X;
            }
            gSystem.newKeys &= ((PAD_BUTTON_X | PAD_BUTTON_Y) ^ 0xFFFF);;
            gSystem.newKeys |= swapMask;
        }
        {
            u32 swapMask = 0;
            if (gSystem.heldKeys & PAD_BUTTON_X)
            {
                swapMask |= PAD_BUTTON_Y;
            }
            if (gSystem.heldKeys & PAD_BUTTON_Y)
            {
                swapMask |= PAD_BUTTON_X;
            }
            gSystem.heldKeys &= ((PAD_BUTTON_X | PAD_BUTTON_Y) ^ 0xFFFF);
            gSystem.heldKeys |= swapMask;
        }
        {
            u32 swapMask = 0;
            if (gSystem.newAndRepeatedKeys & PAD_BUTTON_X)
            {
                swapMask |= PAD_BUTTON_Y;
            }
            if (gSystem.newAndRepeatedKeys & PAD_BUTTON_Y)
            {
                swapMask |= PAD_BUTTON_X;
            }
            gSystem.newAndRepeatedKeys &= ((PAD_BUTTON_X | PAD_BUTTON_Y) ^ 0xFFFF);
            gSystem.newAndRepeatedKeys |= swapMask;
        }
        break;
    case 3: // L = A
        if (gSystem.newKeys & PAD_BUTTON_L)
            gSystem.newKeys |= PAD_BUTTON_A;
        if (gSystem.heldKeys & PAD_BUTTON_L)
            gSystem.heldKeys |= PAD_BUTTON_A;
        if (gSystem.newAndRepeatedKeys & PAD_BUTTON_L)
            gSystem.newAndRepeatedKeys |= PAD_BUTTON_A;
        gSystem.newKeys &= ((PAD_BUTTON_L | PAD_BUTTON_R) ^ 0xFFFF);
        gSystem.heldKeys &= ((PAD_BUTTON_L | PAD_BUTTON_R) ^ 0xFFFF);
        gSystem.newAndRepeatedKeys &= ((PAD_BUTTON_L | PAD_BUTTON_R) ^ 0xFFFF);
    }
}

void SetKeyRepeatTimers(int continueDelay, int startDelay)
{
    gSystem.keyRepeatContinueDelay = continueDelay;
    gSystem.keyRepeatStartDelay = startDelay;
}

void SetSoftResetDisableMask(u8 a0)
{
    gSystem.softResetDisabled |= a0;
}

void ClearSoftResetDisableMask(u8 a0)
{
    gSystem.softResetDisabled &= ~a0;
}
