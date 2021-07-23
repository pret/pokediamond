#ifndef POKEDIAMOND_CTRDG_FLASH_AT29LV512_H
#define POKEDIAMOND_CTRDG_FLASH_AT29LV512_H

#include "nitro/types.h"
#include "CTRDG_task.h"

u32 CTRDGi_EraseFlashChipCoreAT(CTRDGTaskInfo *arg);
u32 CTRDGi_EraseFlashSectorCoreAT(CTRDGTaskInfo *arg);
u32 CTRDGi_EraseFlash4KBCoreAT(CTRDGTaskInfo *arg);
u32 CTRDGi_WriteFlashSectorCoreAT(CTRDGTaskInfo *arg);
u32 CTRDGi_WriteFlash4KBCoreAT(CTRDGTaskInfo *arg);
u16 CTRDGi_EraseFlashChipAT(void);
u16 CTRDGi_EraseFlash4KBAT(u16 l_secNo);
u16 CTRDGi_WriteFlash4KBAT(u16 l_secNo, u8 *src);
void CTRDGi_EraseFlashChipAsyncAT(CTRDG_TASK_FUNC callback);
void CTRDGi_EraseFlash4KBAsyncAT(u16 l_secNo, CTRDG_TASK_FUNC callback);
void CTRDGi_WriteFlash4KBAsyncAT(u16 l_secNo, u8 *src, CTRDG_TASK_FUNC callback);
u16 CTRDGi_EraseFlashSectorAT(u16 p_secNo);
u16 CTRDGi_WriteFlashSectorAT(u16 p_secNo, u8 *src);
void CTRDGi_EraseFlashSectorAsyncAT(u16 p_secNo, CTRDG_TASK_FUNC callback);
void CTRDGi_WriteFlashSectorAsyncAT(u16 p_secNo, u8 *src, CTRDG_TASK_FUNC callback);

#endif //POKEDIAMOND_CTRDG_FLASH_AT29LV512_H
