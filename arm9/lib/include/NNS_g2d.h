#ifndef NNSYS_NNS_G2D_H
#define NNSYS_NNS_G2D_H

#include "gx.h"

typedef struct NNSG2dCharacterData
{
    u16 H;
    u16 W;
    GXTexFmt pixelFmt;
    GXOBJVRamModeChar mapingType;
    u32 characterFmt;
    u32 szByte;
    void * pRawData;
} NNSG2dCharacterData;

typedef struct NNSG2dScreenData
{
    u16 screenWidth;
    u16 screenHeight;
    u16 colorMode;
    u16 screenFormat;
    u32 szByte;
    u32 rawData[1];
} NNSG2dScreenData;

typedef struct NNSG2dPaletteData
{
    GXTexFmt fmt;
    BOOL bExtendedPlt;
    u32 szByte;
    void * pRawData;

} NNSG2dPaletteData;

typedef enum NNS_G2D_VRAM_TYPE
{
    NNS_G2D_VRAM_TYPE_3DMAIN = 0,
    NNS_G2D_VRAM_TYPE_2DMAIN = 1,
    NNS_G2D_VRAM_TYPE_2DSUB = 2,
    NNS_G2D_VRAM_TYPE_MAX = 3
} NNS_G2D_VRAM_TYPE;

typedef enum NNSG2dCharacterDataMapingType
{
    NNS_G2D_CHARACTERMAPING_1D_32,
    NNS_G2D_CHARACTERMAPING_1D_64,
    NNS_G2D_CHARACTERMAPING_1D_128,
    NNS_G2D_CHARACTERMAPING_1D_256,
    NNS_G2D_CHARACTERMAPING_2D,
    NNS_G2D_CHARACTERMAPING_MAX

} NNSG2dCharacterDataMapingType;

typedef struct NNSG2dImageAttr
{
    GXTexSizeS sizeS;
    GXTexSizeT sizeT;
    GXTexFmt fmt;
    BOOL bExtendedPlt;
    GXTexPlttColor0 plttUse;
    GXOBJVRamModeChar mappingType;
} NNSG2dImageAttr;

typedef struct NNSG2dVRamLocation
{
    u32 baseAddrOfVram[ NNS_G2D_VRAM_TYPE_MAX ];
} NNSG2dVRamLocation;

typedef struct NNSG2dImageProxy
{
    NNSG2dVRamLocation vramLocation;
    NNSG2dImageAttr attr;
} NNSG2dImageProxy;

typedef struct NNSG2dPaletteCompressInfo
{
    u16 numPalette;
    u16 pad16;
    void * pPlttIdxTbl;

} NNSG2dPaletteCompressInfo;

void NNS_G2dLoadImage1DMapping
(
    const NNSG2dCharacterData *  pSrcData,
    u32 baseAddr,
    NNS_G2D_VRAM_TYPE type,
    NNSG2dImageProxy * pImgProxy
);

void NNS_G2dLoadImage2DMapping
(
    const NNSG2dCharacterData *  pSrcData,
    u32 baseAddr,
    NNS_G2D_VRAM_TYPE type,
    NNSG2dImageProxy * pImgProxy
);

typedef struct NNSG2dImagePaletteProxy
{
    GXTexFmt fmt;
    BOOL bExtendedPlt;
    NNSG2dVRamLocation vramLocation;
} NNSG2dImagePaletteProxy;

void NNS_G2dLoadPalette
(
    const NNSG2dPaletteData * pSrcData,
    u32 addr,
    NNS_G2D_VRAM_TYPE type,
    NNSG2dImagePaletteProxy * pPltProxy
);

void NNS_G2dLoadPaletteEx
(
    const NNSG2dPaletteData * pSrcData,
    const NNSG2dPaletteCompressInfo * pCmpInfo,
    u32 addr,
    NNS_G2D_VRAM_TYPE type,
    NNSG2dImagePaletteProxy * pPltProxy
);

typedef struct NNSG2dCellVramTransferData
{
    u32 srcDataOffset;
    u32 szByte;
} NNSG2dCellVramTransferData;

typedef struct NNSG2dVramTransferData
{
    u32 szByteMax;
    NNSG2dCellVramTransferData * pCellTransferDataArray;
} NNSG2dVramTransferData;

typedef struct NNSG2dCellOAMAttrData
{
    u16 attr0;
    u16 attr1;
    u16 attr2;
} NNSG2dCellOAMAttrData;

typedef struct NNSG2dCellData
{
    u16 numOAMAttrs;
    u16 cellAttr;
    NNSG2dCellOAMAttrData * pOamAttrArray;

} NNSG2dCellData;

typedef struct NNSG2dCellDataBank
{
    u16 numCells;
    u16 cellBankAttr;
    NNSG2dCellData * pCellDataArrayHead;
    NNSG2dCharacterDataMapingType mappingMode;
    NNSG2dVramTransferData * pVramTransferData;
    void * pStringBank;
    void * pExtendedData;

} NNSG2dCellDataBank;

typedef enum NNSG2dAnimationPlayMode
{
    NNS_G2D_ANIMATIONPLAYMODE_INVALID = 0x0,
    NNS_G2D_ANIMATIONPLAYMODE_FORWARD,
    NNS_G2D_ANIMATIONPLAYMODE_FORWARD_LOOP,
    NNS_G2D_ANIMATIONPLAYMODE_REVERSE,
    NNS_G2D_ANIMATIONPLAYMODE_REVERSE_LOOP,
    NNS_G2D_ANIMATIONPLAYMODE_MAX
} NNSG2dAnimationPlayMode;

typedef struct NNSG2dAnimFrameData
{
    void * pContent;
    u16 frames;
    u16 pad16;
} NNSG2dAnimFrameData;

typedef struct NNSG2dAnimSequenceData
{
    u16 numFrames;
    u16 loopStartFrameIdx;
    u32 animType;
    NNSG2dAnimationPlayMode playMode;
    NNSG2dAnimFrameData * pAnmFrameArray;

} NNSG2dAnimSequenceData;

typedef struct NNSG2dAnimBankData
{

    u16 numSequences;
    u16 numTotalFrames;
    NNSG2dAnimSequenceData * pSequenceArrayHead;
    NNSG2dAnimFrameData * pFrameArrayHead;
    void * pAnimContents;
    void * pStringBank;
    void * pExtendedData;

} NNSG2dAnimBankData;

BOOL NNS_G2dGetUnpackedBGCharacterData(void * pNcgrFile, NNSG2dCharacterData ** ppCharData);
BOOL NNS_G2dGetUnpackedCharacterData(void * pNcgrFile, NNSG2dCharacterData ** ppCharData);
BOOL NNS_G2dGetUnpackedScreenData(void * pNscrFile, NNSG2dScreenData ** ppScrData);
BOOL NNS_G2dGetUnpackedPaletteData(void * pNclrFile, NNSG2dPaletteData ** ppPltData);
BOOL NNS_G2dGetUnpackedPaletteData(void * pNclrFile, NNSG2dPaletteData ** ppPltData);
BOOL NNS_G2dGetUnpackedPaletteCompressInfo(void * pNclrFile, NNSG2dPaletteCompressInfo ** ppPltCmpInfo);
BOOL NNS_G2dGetUnpackedCellBank(void * pNcerFile, NNSG2dCellDataBank ** ppCellBank);
BOOL NNS_G2dGetUnpackedAnimBank(void * pNanrFile, NNSG2dAnimBankData ** ppAnimBank);

#endif //NNSYS_NNS_G2D_H
