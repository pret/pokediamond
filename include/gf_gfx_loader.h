#ifndef POKEDIAMOND_GF_GFX_LOADER_H
#define POKEDIAMOND_GF_GFX_LOADER_H

#include "bg_window.h"
#include "filesystem.h"
#include "heap.h"

u32 GfGfxLoader_LoadCharData(NarcId narcId, s32 memberNo, struct BgConfig *unkStruct02016B94_2, u32 layer, u32 numTiles, u32 szByte, BOOL isCompressed, HeapID heapId);
void GfGfxLoader_LoadScrnData(NarcId narcId, s32 memberNo, struct BgConfig *unkStruct02016B94_2, u32 layer, u32 tileOffset, u32 szByte, BOOL isCompressed, HeapID heapId);
void GfGfxLoader_GXLoadPal(NarcId narcId, s32 memberNo, enum GFPalLoadLocation location, enum GFPalSlotOffset palSlotOffset, u32 szByte, HeapID heapId);
void GfGfxLoader_GXLoadPalWithSrcOffset(NarcId narcId, s32 memberNo, enum GFPalLoadLocation location, u32 srcOffset, enum GFPalSlotOffset palSlotOffset, u32 szByte, HeapID heapId);
u32 GfGfxLoader_LoadWholePalette(NarcId narcId, s32 memberId, u32 layer, u32 baseAddr, u32 szByte, BOOL isCompressed, HeapID heapId);
void GfGfxLoader_PartiallyLoadPalette(NarcId narcId, s32 memberId, NNS_G2D_VRAM_TYPE vramType, u32 baseAddr, HeapID heapId, NNSG2dImagePaletteProxy *pPltProxy);
u32 GfGfxLoader_LoadImageMapping(NarcId narcId, s32 memberId, BOOL isCompressed, u32 layer, u32 szByte, NNS_G2D_VRAM_TYPE type, u32 baseAddr, HeapID heapId, NNSG2dImageProxy *pImgProxy);
void GfGfxLoader_SetObjCntFlagsAndLoadImageMapping(NarcId narcId, s32 memberId, BOOL isCompressed, u32 layer, u32 szByte, NNS_G2D_VRAM_TYPE type, u32 baseAddr, HeapID heapId, NNSG2dImageProxy *pImageProxy);
void *GfGfxLoader_GetCharData(NarcId narcId, s32 memberId, BOOL isCompressed, NNSG2dCharacterData **ppCharData, HeapID heapId);
void *GfGfxLoader_GetScrnData(NarcId narcId, s32 memberId, BOOL isCompressed, NNSG2dScreenData **ppScrData, HeapID heapId);
void *GfGfxLoader_GetPlttData(NarcId narcId, s32 memberId, NNSG2dPaletteData **ppPltData, HeapID heapId);
void *GfGfxLoader_GetCellBank(NarcId narcId, s32 memberId, BOOL isCompressed, NNSG2dCellDataBank **ppCellBank, HeapID heapId);
void *GfGfxLoader_GetAnimBank(NarcId narcId, s32 memberId, BOOL isCompressed, NNSG2dAnimBankData **ppAnimBank, HeapID heapId);
void *GfGfxLoader_UncompressFromNarc(NarcId narcId, s32 memberId, HeapID heapId);
void *GfGfxLoader_LoadFromNarc(NarcId narcId, s32 memberNo, BOOL isCompressed, HeapID heapId, BOOL allocAtEnd);
void *GfGfxLoader_LoadFromNarc_GetSizeOut(NarcId narcId, s32 memberNo, BOOL isCompressed, HeapID heapId, BOOL allocAtEnd, u32 *size_p);

#endif // POKEDIAMOND_GF_GFX_LOADER_H
