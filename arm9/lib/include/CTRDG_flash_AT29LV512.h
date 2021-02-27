#ifndef POKEDIAMOND_CTRDG_FLASH_AT29LV512_H
#define POKEDIAMOND_CTRDG_FLASH_AT29LV512_H

#include "nitro/types.h"
#include "CTRDG_task.h"

u32 CTRDGi_EraseFlashChipCoreAT(CTRDGTaskInfo *arg);
u32 CTRDGi_EraseFlashSectorCoreAT(CTRDGTaskInfo *arg);

#endif //POKEDIAMOND_CTRDG_FLASH_AT29LV512_H
