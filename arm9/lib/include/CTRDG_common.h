#ifndef POKEDIAMOND_CTRDG_COMMON_H
#define POKEDIAMOND_CTRDG_COMMON_H

#include "consts.h"
#include "OS_spinLock.h"
#include "OS_system.h"
#include "MI_exMemory.h"

typedef struct CTRDGWork
{
    vu16    subpInitialized;
    u16     lockID;

} CTRDGWork;

typedef struct CTRDGModuleID
{
    union
    {
        struct
        {
            u8 bitID;
            u8 numberID:5;
            u8 :2;
            u8 disableExLsiID:1;
        };
        u16 raw;
    };
} CTRDGModuleID;

typedef struct CTRDGModuleInfo
{
    CTRDGModuleID moduleID;
    u8 exLsiID[3];
    u8 isAgbCartridge:1;
    u8 detectPullOut:1;
    u8 :0; //??
    u16 makerCode;
    u32 gameCode;
} CTRDGModuleInfo;

typedef struct CTRDGLockByProc
{
    BOOL locked;
    OSIntrMode irq;
} CTRDGLockByProc;

typedef struct CTRDGHeader
{
    u32 startAddress;
    u8 nintendoLogo[0x9c];

    u8 titleName[12];
    u32 gameCode;
    u16 makerCode;

    u8 isRomCode;

    u8 machineCode;
    u8 deviceType;

    u8 exLsiID[3];

    u8 reserved[4];
    u8 softVersion;
    u8 complement;

    u16 moduleID;
} CTRDGHeader;

typedef struct CTRDGRomCycle
{
    MICartridgeRomCycle1st c1;
    MICartridgeRomCycle2nd c2;
} CTRDGRomCycle;

#define CTRDGi_GetModuleInfoAddr()      ((CTRDGModuleInfo *)HW_CTRDG_MODULE_INFO_BUF)
#define CTRDGi_GetHeaderAddr()          ((CTRDGHeader *)HW_CTRDG_ROM)
#define CTRDGi_GetModuleIDImageAddr()   ((u16 *)(HW_CTRDG_ROM + 0x0001fffe))

#define CTRDG_IS_ROM_CODE               0x96
#define CTRDG_LOCKED_BY_MYPROC_FLAG     OS_MAINP_LOCKED_FLAG

#define CTRDGi_FORWARD_TYPE_DMA         0x00000000
#define CTRDGi_FORWARD_TYPE_CPU         0x00000001
#define CTRDGi_FORWARD_TYPE_MASK        0x00000001

#define CTRDGi_FORWARD_WIDTH_8          0x00000000
#define CTRDGi_FORWARD_WIDTH_16         0x00000010
#define CTRDGi_FORWARD_WIDTH_32         0x00000020

#define CTRDGi_FORWARD_DMA16            (CTRDGi_FORWARD_TYPE_DMA | CTRDGi_FORWARD_WIDTH_16)
#define CTRDGi_FORWARD_DMA32            (CTRDGi_FORWARD_TYPE_DMA | CTRDGi_FORWARD_WIDTH_32)
#define CTRDGi_FORWARD_CPU8             (CTRDGi_FORWARD_TYPE_CPU | CTRDGi_FORWARD_WIDTH_8)
#define CTRDGi_FORWARD_CPU16            (CTRDGi_FORWARD_TYPE_CPU | CTRDGi_FORWARD_WIDTH_16)
#define CTRDGi_FORWARD_CPU32            (CTRDGi_FORWARD_TYPE_CPU | CTRDGi_FORWARD_WIDTH_32)

#define CTRDGi_ACCESS_DIR_WRITE         0x00000000
#define CTRDGi_ACCESS_DIR_READ          0x00000001

#define CTRDGi_ACCESS_WIDTH_8           0x00000010
#define CTRDGi_ACCESS_WIDTH_16          0x00000020
#define CTRDGi_ACCESS_WIDTH_32          0x00000040

#define CTRDGi_ACCESS_WRITE8            (CTRDGi_ACCESS_DIR_WRITE | CTRDGi_ACCESS_WIDTH_8)
#define CTRDGi_ACCESS_WRITE16           (CTRDGi_ACCESS_DIR_WRITE | CTRDGi_ACCESS_WIDTH_16)
#define CTRDGi_ACCESS_WRITE32           (CTRDGi_ACCESS_DIR_WRITE | CTRDGi_ACCESS_WIDTH_32)
#define CTRDGi_ACCESS_READ8             (CTRDGi_ACCESS_DIR_READ | CTRDGi_ACCESS_WIDTH_8)
#define CTRDGi_ACCESS_READ16            (CTRDGi_ACCESS_DIR_READ | CTRDGi_ACCESS_WIDTH_16)
#define CTRDGi_ACCESS_READ32            (CTRDGi_ACCESS_DIR_READ | CTRDGi_ACCESS_WIDTH_32)

void CTRDGi_InitCommon(void);
BOOL CTRDG_IsAgbCartridge(void);
BOOL CTRDG_IsOptionCartridge(void);
BOOL CTRDGi_IsAgbCartridgeAtInit(void);
u32 CTRDG_GetAgbGameCode(void);
u32 CTRDGi_GetAgbGameCodeAtInit(void);
u16 CTRDG_GetAgbMakerCode(void);
u16 CTRDGi_GetAgbMakerCodeAtInit(void);
BOOL CTRDG_IsPulledOut(void);
BOOL CTRDG_IsExisting(void);
void CTRDGi_ChangeLatestAccessCycle(CTRDGRomCycle *r);
void CTRDGi_RestoreAccessCycle(CTRDGRomCycle *r);
void CTRDGi_LockByProcessor(u16 lockID, CTRDGLockByProc *info);
void CTRDGi_UnlockByProcessor(u16 lockID, CTRDGLockByProc *info);
void CTRDGi_SendtoPxi(u32 data);
BOOL CTRDG_CpuCopy8(const void *src, void *dest, u32 size);
BOOL CTRDG_CpuCopy16(const void *src, void *dest, u32 size);
BOOL CTRDG_CpuCopy32(const void *src, void *dest, u32 size);
BOOL CTRDGi_CopyCommon(u32 dmaNo, const void *src, void *dest, u32 size, u32 forwardType);
BOOL CTRDG_Read32(const u32 *address, u32 *rdata);
BOOL CTRDGi_AccessCommon(void *address, u32 data, void *rdata, u32 accessType);
BOOL CTRDG_IsEnabled(void);
void CTRDG_Enable(BOOL enable);
void CTRDG_CheckEnabled(void);

#endif //POKEDIAMOND_CTRDG_COMMON_H
