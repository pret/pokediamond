#include "OS_vramExclusive.h"
#include "OS_system.h"
#include "code32.h"

static u32 OSi_vramExclusive;
static u16 OSi_vramLockId[9];

static u32 OsCountZeroBits(register u32 bitmap);

static asm u32 OsCountZeroBits(register u32 bitmap)
{
    clz r0, r0
    bx lr
}

void OSi_InitVramExclusive(void)
{
    OSi_vramExclusive = 0x0000;

    for (s32 i = 0; i < 9; i++)
    {
        OSi_vramLockId[i] = 0;
    }
}

BOOL OSi_TryLockVram(u16 bank, u16 lockId)
{
    u32 workMap;
    s32 zeroBits;
    OSIntrMode enabled = OS_DisableInterrupts();

    workMap = (u32)(bank & OSi_vramExclusive);
    while (TRUE)
    {
        zeroBits = (s32)(31 - OsCountZeroBits(workMap));
        if (zeroBits < 0)
        {
            break;
        }
        workMap &= ~(0x00000001 << zeroBits);
        if (OSi_vramLockId[zeroBits] != lockId)
        {
            (void)OS_RestoreInterrupts(enabled);
            return FALSE;
        }
    }

    workMap = (u32)(bank & 0x01ff);
    while (TRUE)
    {
        zeroBits = (s32)(31 - OsCountZeroBits(workMap));
        if (zeroBits < 0)
        {
            break;
        }
        workMap &= ~(0x00000001 << zeroBits);
        OSi_vramLockId[zeroBits] = lockId;
        OSi_vramExclusive |= (0x00000001 << zeroBits);
    }

    (void)OS_RestoreInterrupts(enabled);
    return TRUE;
}

void OSi_UnlockVram(u16 bank, u16 lockId)
{
    u32 workMap;
    s32 zeroBits;
    OSIntrMode enabled = OS_DisableInterrupts();

    workMap = (u32)(bank & OSi_vramExclusive & 0x01ff);
    while (TRUE)
    {
        zeroBits = (s32)(31- OsCountZeroBits((u32)workMap));
        if (zeroBits < 0)
        {
            break;
        }
        workMap &= ~(0x00000001 << zeroBits);
        if (OSi_vramLockId[zeroBits] == lockId)
        {
            OSi_vramLockId[zeroBits] = 0;
            OSi_vramExclusive &= ~(0x00000001 << zeroBits);
        }
    }

    (void)OS_RestoreInterrupts(enabled);
}
