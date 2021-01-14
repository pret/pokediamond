#ifndef POKEDIAMOND_CTRDG_BACKUP_H
#define POKEDIAMOND_CTRDG_BACKUP_H

#include "nitro/types.h"
#include "CTRDG_flash.h"
#include "CTRDG_task.h"

typedef struct CTRDGiFlashTypePlusTag
{
    u16 (*CTRDGi_WriteAgbFlashSector)(u16 secNo, u8 *src);
    u16 (*CTRDGi_EraseAgbFlashChip)(void);
    u16 (*CTRDGi_EraseAgbFlashSector)(u16 secNo);
    void (*CTRDGi_WriteAgbFlashSectorAsync)(u16 secNo, u8 *src, CTRDG_TASK_FUNC callback);
    void (*CTRDGi_EraseAgbFlashChipAsync)(CTRDG_TASK_FUNC callback);
    void (*CTRDGi_EraseAgbFlashSectorAsync)(u16 secNo, CTRDG_TASK_FUNC callback);
    u16  (*CTRDGi_PollingSR)(u16 phase, u8 *adr, u16 lastData);
    const u16 (*maxtime);
    CTRDGFlashType type;
} CTRDGiFlashTypePlus;

typedef enum
{
    CTRDG_BACKUP_TYPE_FLASH_512K,
    CTRDG_BACKUP_TYPE_FLASH_1M,
    CTRDG_BACKUP_TYPE_SRAM
} CTRDGBackupType;

extern const u16 (*ctrdgi_fl_maxtime);

extern u16 (*CTRDGi_PollingSR)(u16 phase, u8 *adr, u16 lastData);
extern const CTRDGFlashType *AgbFlash;
extern u16 (*CTRDGi_WriteAgbFlashSector)(u16 secNo, u8 *src);
extern u16 (*CTRDGi_EraseAgbFlashChip)(void);
extern u16 (*CTRDGi_EraseAgbFlashSector)(u16 secNo);
extern void (*CTRDGi_WriteAgbFlashSectorAsync)(u16 secNo, u8 *src, CTRDG_TASK_FUNC callback);
extern void (*CTRDGi_EraseAgbFlashChipAsync)(CTRDG_TASK_FUNC callback);
extern void (*CTRDGi_EraseAgbFlashSectorAsync)(u16 secNo, CTRDG_TASK_FUNC callback);

u16 CTRDG_IdentifyAgbBackup(CTRDGBackupType type);

#endif //POKEDIAMOND_CTRDG_BACKUP_H
