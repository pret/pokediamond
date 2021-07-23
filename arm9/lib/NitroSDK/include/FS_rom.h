#ifndef NITRO_FS_ROM_H_
#define NITRO_FS_ROM_H_

#include "FS_archive.h"
#include "FS_file.h"
#include "CARD_rom.h"
#include "nitro/types.h"

extern FSArchive fsi_arc_rom;
extern s32 fsi_card_lock_id;
extern CARDRomRegion fsi_ovt7;
extern CARDRomRegion fsi_ovt9;

void FSi_OnRomReadDone(void * p_arc);
FSResult FSi_ReadRomCallback(FSArchive * p_arc, void * dst, u32 src, u32 len);
FSResult FSi_WriteDummyCallback(FSArchive * p_arc, const void *src, u32 dst, u32 len);
FSResult FSi_RomArchiveProc(FSFile * p_arc, FSCommandType cmd);
FSResult FSi_ReadDummyCallback(FSArchive *p_arc, void *dst, u32 src, u32 len);
FSResult FSi_EmptyArchiveProc(FSFile *p_file, FSCommandType cmd);
void FSi_InitRom(u32 default_dma_no);
u32 FS_SetDefaultDMA(u32 dma_no);
u32 FS_TryLoadTable(void * p_mem, u32 size);

#endif //NITRO_FS_ROM_H_
