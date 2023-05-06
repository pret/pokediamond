#ifndef POKEDIAMOND_GF_GFX_LOADER_H
#define POKEDIAMOND_GF_GFX_LOADER_H

#include "bg_window.h"
#include "filesystem.h"

u32 GfGfxLoader_LoadCharData(NarcId narcId, s32 memberNo, struct BgConfig * unkStruct02016B94_2, u32 layer, u32 numTiles, u32 szByte, BOOL isCompressed, u32 heap_id);
void GfGfxLoader_LoadScrnData(NarcId narcId, s32 memberNo, struct BgConfig * unkStruct02016B94_2, u32 layer, u32 tileOffset, u32 szByte, BOOL isCompressed, u32 heap_id);
void GfGfxLoader_GXLoadPal(NarcId narcId, s32 memberNo, enum GFPalLoadLocation location, enum GFPalSlotOffset palSlotOffset, u32 szByte, u32 heap_id);
void GfGfxLoader_GXLoadPalWithSrcOffset(NarcId narcId, s32 memberNo, enum GFPalLoadLocation location, u32 srcOffset, enum GFPalSlotOffset palSlotOffset, u32 szByte, u32 heap_id);
u32 GfGfxLoader_LoadWholePalette(NarcId narcId, s32 memberId, u32 layer, u32 baseAddr, u32 szByte, BOOL isCompressed, u32 heap_id);
void GfGfxLoader_PartiallyLoadPalette(NarcId narcId, s32 memberId, NNS_G2D_VRAM_TYPE vramType, u32 baseAddr, u32 heap_id, NNSG2dImagePaletteProxy * pPltProxy);
u32 GfGfxLoader_LoadImageMapping(NarcId narcId, s32 memberId, BOOL isCompressed, u32 layer, u32 szByte, NNS_G2D_VRAM_TYPE type, u32 baseAddr, u32 heap_id, NNSG2dImageProxy *pImgProxy);
void GfGfxLoader_SetObjCntFlagsAndLoadImageMapping(NarcId narcId, s32 memberId, BOOL isCompressed, u32 layer, u32 szByte, NNS_G2D_VRAM_TYPE type, u32 baseAddr, u32 heap_id, NNSG2dImageProxy * pImageProxy);
void * GfGfxLoader_GetCharData(NarcId narcId, s32 memberId, BOOL isCompressed, NNSG2dCharacterData ** ppCharData, u32 heap_id);
void * GfGfxLoader_GetScrnData(NarcId narcId, s32 memberId, BOOL isCompressed, NNSG2dScreenData ** ppScrData, u32 heap_id);
void * GfGfxLoader_GetPlttData(NarcId narcId, s32 memberId, NNSG2dPaletteData ** ppPltData, u32 heap_id);
void * GfGfxLoader_GetCellBank(NarcId narcId, s32 memberId, BOOL isCompressed, NNSG2dCellDataBank ** ppCellBank, u32 heap_id);
void * GfGfxLoader_GetAnimBank(NarcId narcId, s32 memberId, BOOL isCompressed, NNSG2dAnimBankData ** ppAnimBank, u32 heap_id);
void * GfGfxLoader_UncompressFromNarc(NarcId narcId, s32 memberId, u32 heap_id);
void * GfGfxLoader_LoadFromNarc(NarcId narcId, s32 memberNo, BOOL isCompressed, u32 heap_id, BOOL allocAtEnd);
void * GfGfxLoader_LoadFromNarc_GetSizeOut(NarcId narcId, s32 memberNo, BOOL isCompressed, u32 heap_id, BOOL allocAtEnd, u32 *size_p);

#endif //POKEDIAMOND_GF_GFX_LOADER_H
