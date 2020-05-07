#ifndef NITRO_FS_ROM_H_
#define NITRO_FS_ROM_H_

#include "FS_archive.h"
#include "CARD_rom.h"

extern FSArchive fsi_arc_rom;
extern s32 fsi_card_lock_id;
extern CARDRomRegion fsi_ovt7;
extern CARDRomRegion fsi_ovt9;

void FSi_InitRom(u32 default_dma_no);

#endif //NITRO_FS_ROM_H_
