#ifndef POKEDIAMOND_CTRDG_FLASH_H
#define POKEDIAMOND_CTRDG_FLASH_H

#include "nitro/types.h"
#include "MI_exMemory.h"

#define CTRDG_AGB_FLASH_ADR  0x0A000000

typedef struct CTRDGiFlashSectorTag
{
    u32 size;
    u16 shift;
    u16 count;
    u16 top;
    u8 reserved[2];
} CTRDGiFlashSector;

typedef struct CTRDGFlashTypeTag
{
    u32 romSize;
    CTRDGiFlashSector sector;
    MICartridgeRamCycle agbWait[2];
    u16 makerID;
    u16 deviceID;
} CTRDGFlashType;

#endif //POKEDIAMOND_CTRDG_FLASH_H
