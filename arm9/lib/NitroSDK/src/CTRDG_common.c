#include "CTRDG_common.h"
#include "function_target.h"
#include "syscall.h"
#include "OS_cache.h"
#include "OS_protectionRegion.h"
#include "OS_terminate_proc.h"
#include "PXI_fifo.h"
#include "MI_dma.h"
#include "MI_memory.h"
#include "mmap.h"

CTRDGWork CTRDGi_Work;

static BOOL CTRDGi_EnableFlag = FALSE;

ARM_FUNC void CTRDGi_InitCommon(void)
{
    SVC_CpuClear(0, &CTRDGi_Work, sizeof(CTRDGi_Work), 32);

    CTRDGi_Work.lockID = (u16)OS_GetLockID();
}

ARM_FUNC BOOL CTRDG_IsAgbCartridge(void)
{
    return (CTRDG_IsExisting() && CTRDGi_IsAgbCartridgeAtInit());
}

ARM_FUNC BOOL CTRDG_IsOptionCartridge(void)
{
    return (CTRDG_IsExisting() && !CTRDGi_IsAgbCartridgeAtInit());
}

ARM_FUNC BOOL CTRDGi_IsAgbCartridgeAtInit(void)
{
    CTRDGModuleInfo *cip = CTRDGi_GetModuleInfoAddr();

    return cip->isAgbCartridge;
}

ARM_FUNC u32 CTRDG_GetAgbGameCode(void)
{
    u32 ret = 0;

    if (CTRDG_IsExisting())
    {
        ret = CTRDGi_GetAgbGameCodeAtInit();
    }

    return ret;
}

ARM_FUNC u32 CTRDGi_GetAgbGameCodeAtInit(void)
{
    CTRDGModuleInfo *cip = CTRDGi_GetModuleInfoAddr();
    u32 ret = 0;

    if (CTRDGi_IsAgbCartridgeAtInit())
    {
        ret = cip->gameCode;
    }

    return ret;
}

ARM_FUNC u16 CTRDG_GetAgbMakerCode(void)
{
    u16 ret = 0;

    if (CTRDG_IsExisting())
    {
        ret = CTRDGi_GetAgbMakerCodeAtInit();
    }

    return ret;
}

ARM_FUNC u16 CTRDGi_GetAgbMakerCodeAtInit(void)
{
    CTRDGModuleInfo *cip = CTRDGi_GetModuleInfoAddr();
    u16 ret = 0;

    if (CTRDGi_IsAgbCartridgeAtInit())
    {
        ret = cip->makerCode;
    }

    return ret;
}

ARM_FUNC BOOL CTRDG_IsPulledOut(void)
{
    CTRDGModuleInfo *cip = CTRDGi_GetModuleInfoAddr();

    if (cip->moduleID.raw == 0xffff)
    {
        return FALSE;
    }

    if (!cip->detectPullOut)
    {
        (void)CTRDG_IsExisting();
    }

    return cip->detectPullOut;
}

ARM_FUNC BOOL CTRDG_IsExisting(void)
{
    BOOL ret = TRUE;
    CTRDGLockByProc lockInfo;

    CTRDGHeader *chp = CTRDGi_GetHeaderAddr();
    CTRDGModuleInfo *cip = CTRDGi_GetModuleInfoAddr();

    if (cip->moduleID.raw == 0xffff)
    {
        return FALSE;
    }

    if (cip->detectPullOut == TRUE)
    {
        return FALSE;
    }

    CTRDGi_LockByProcessor(CTRDGi_Work.lockID, &lockInfo);

    CTRDGRomCycle rc;

    CTRDGi_ChangeLatestAccessCycle(&rc);
    u8 isRomCode = chp->isRomCode;

    if ((isRomCode == CTRDG_IS_ROM_CODE && cip->moduleID.raw != chp->moduleID)
        || (isRomCode != CTRDG_IS_ROM_CODE && cip->moduleID.raw != *CTRDGi_GetModuleIDImageAddr())
        || ((cip->gameCode != chp->gameCode) && cip->isAgbCartridge))
    {
        cip->detectPullOut = TRUE;
        ret = FALSE;
    }

    CTRDGi_RestoreAccessCycle(&rc);

    CTRDGi_UnlockByProcessor(CTRDGi_Work.lockID, &lockInfo);

    return ret;
}

ARM_FUNC void CTRDGi_ChangeLatestAccessCycle(CTRDGRomCycle *r)
{
    r->c1 = MI_GetCartridgeRomCycle1st();
    r->c2 = MI_GetCartridgeRomCycle2nd();

    MI_SetCartridgeRomCycle1st(MI_CTRDG_ROMCYCLE1_18);
    MI_SetCartridgeRomCycle2nd(MI_CTRDG_ROMCYCLE2_6);
}

ARM_FUNC void CTRDGi_RestoreAccessCycle(CTRDGRomCycle *r)
{
    MI_SetCartridgeRomCycle1st(r->c1);
    MI_SetCartridgeRomCycle2nd(r->c2);
}

ARM_FUNC void CTRDGi_LockByProcessor(u16 lockID, CTRDGLockByProc *info)
{
    while (TRUE)
    {
        info->irq = OS_DisableInterrupts();
        if (((info->locked = OS_ReadOwnerOfLockCartridge() & CTRDG_LOCKED_BY_MYPROC_FLAG) != 0)
            || (OS_TryLockCartridge(lockID) == OS_LOCK_SUCCESS))
        {
            break;
        }
        (void)OS_RestoreInterrupts(info->irq);

        SVC_WaitByLoop(1);
    }
}

ARM_FUNC void CTRDGi_UnlockByProcessor(u16 lockID, CTRDGLockByProc *info)
{
    if (!info->locked)
    {
        (void)OS_UnLockCartridge(lockID);
    }

    (void)OS_RestoreInterrupts(info->irq);
}

ARM_FUNC void CTRDGi_SendtoPxi(u32 data)
{
    while (PXI_SendWordByFifo(PXI_FIFO_TAG_CTRDG, data, FALSE) != PXI_FIFO_SUCCESS)
    {
        SVC_WaitByLoop(1);
    }
}

ARM_FUNC BOOL CTRDG_CpuCopy8(const void *src, void *dest, u32 size)
{
    if (HW_CTRDG_ROM <= (u32)dest && (u32)dest < HW_CTRDG_RAM_END)
    {
        return CTRDGi_CopyCommon(0, (const void *)dest, (void *)src, size, CTRDGi_FORWARD_CPU8);
    }
    else
    {
        return CTRDGi_CopyCommon(0, src, dest, size, CTRDGi_FORWARD_CPU8);
    }
}

ARM_FUNC BOOL CTRDG_CpuCopy16(const void *src, void *dest, u32 size)
{
    return CTRDGi_CopyCommon(0, src, dest, size, CTRDGi_FORWARD_CPU16);
}

ARM_FUNC BOOL CTRDG_CpuCopy32(const void *src, void *dest, u32 size)
{
    return CTRDGi_CopyCommon(0, src, dest, size, CTRDGi_FORWARD_CPU32);
}

ARM_FUNC BOOL CTRDGi_CopyCommon(u32 dmaNo, const void *src, void *dest, u32 size, u32 forwardType)
{
    if (!CTRDG_IsExisting())
    {
        return FALSE;
    }

    CTRDG_CheckEnabled();

    (void)OS_LockCartridge(CTRDGi_Work.lockID);

    if ((forwardType & CTRDGi_FORWARD_TYPE_MASK) == CTRDGi_FORWARD_TYPE_DMA)
    {
        MI_StopDma(dmaNo);
        DC_FlushRange(dest, size);
    }

    switch (forwardType)
    {
        case CTRDGi_FORWARD_DMA16:
            MI_DmaCopy16(dmaNo, src, dest, size);
            break;
        case CTRDGi_FORWARD_DMA32:
            MI_DmaCopy32(dmaNo, src, dest, size);
            break;
        case CTRDGi_FORWARD_CPU16:
            MI_CpuCopy16(src, dest, size);
            break;
        case CTRDGi_FORWARD_CPU32:
            MI_CpuCopy32(src, dest, size);
            break;

        case CTRDGi_FORWARD_CPU8:
            u8 *dest8 = (u8 *)dest;
            u8 *src8 = (u8 *)src;
            for (s32 n = 0; n < size; n++)
            {
                *dest8++ = *src8++;
            }
            break;
    }

    (void)OS_UnLockCartridge(CTRDGi_Work.lockID);

    if (!CTRDG_IsExisting())
    {
        return FALSE;
    }

    return TRUE;
}

ARM_FUNC BOOL CTRDG_Read32(const u32 *address, u32 *rdata)
{
    return CTRDGi_AccessCommon((void *)address, 0, rdata, CTRDGi_ACCESS_READ32);
}

ARM_FUNC BOOL CTRDGi_AccessCommon(void *address, u32 data, void *rdata, u32 accessType)
{
    if (!CTRDG_IsExisting())
    {
        return FALSE;
    }

    CTRDG_CheckEnabled();

    (void)OS_LockCartridge(CTRDGi_Work.lockID);

    switch (accessType)
    {
        case CTRDGi_ACCESS_READ8:
            if (rdata)
            {
                *(u8 *)rdata = *(u8 *)address;
            }
            break;
        case CTRDGi_ACCESS_READ16:
            if (rdata)
            {
                *(u16 *)rdata = *(u16 *)address;
            }
            break;
        case CTRDGi_ACCESS_READ32:
            if (rdata)
            {
                *(u32 *)rdata = *(u32 *)address;
            }
            break;
        case CTRDGi_ACCESS_WRITE8:
            *(u8 *)address = (u8)data;
            break;
        case CTRDGi_ACCESS_WRITE16:
            *(u16 *)address = (u16)data;
            break;
        case CTRDGi_ACCESS_WRITE32:
            *(u32 *)address = (u32)data;
            break;
    }

    (void)OS_UnLockCartridge(CTRDGi_Work.lockID);

    if (!CTRDG_IsExisting())
    {
        return FALSE;
    }

    return TRUE;
}

ARM_FUNC BOOL CTRDG_IsEnabled(void)
{
    return CTRDGi_EnableFlag;
}

ARM_FUNC void CTRDG_Enable(BOOL enable)
{
    OSIntrMode bak_cpsr = OS_DisableInterrupts();
    CTRDGi_EnableFlag = enable;
    if (!CTRDG_IsOptionCartridge())
    {
        u32 acc = (u32)(enable ? OS_PR3_ACCESS_RW : OS_PR3_ACCESS_RO);
        (void)OS_SetDPermissionsForProtectionRegion(OS_PR3_ACCESS_MASK, acc);
    }
    (void)OS_RestoreInterrupts(bak_cpsr);
}

ARM_FUNC void CTRDG_CheckEnabled(void)
{
    if (!CTRDG_IsOptionCartridge() && !CTRDG_IsEnabled())
    {
        OS_Terminate();
    }
}
