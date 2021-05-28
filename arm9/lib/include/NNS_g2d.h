#ifndef NNSYS_NNS_G2D_H
#define NNSYS_NNS_G2D_H
#include "gx.h"

typedef struct NNSG2dCharacterData
{

    u16                             H;
    u16                             W;

    GXTexFmt                        pixelFmt;    // GXTexFmt

    GXOBJVRamModeChar               mapingType;  // GXOBJVRamModeChar
    u32                             characterFmt;// 31 ..... 10 ...........9 8 ................ 0
    //     Reserved  VramTransfer   NNSG2dCharacterFmt
    u32                             szByte;
    void*                           pRawData;  // offset addr of the content.

}
NNSG2dCharacterData;

typedef struct NNSG2dScreenData
{

    u16     screenWidth;    // screen width (pixels) of rawData
    u16     screenHeight;   // screen height (pixels) of rawData
    u16     colorMode;      // character data color mode
    u16     screenFormat;   // screen data format
    u32     szByte;         // size of rawData
    u32     rawData[1];     // screen data (variable length)

}
NNSG2dScreenData;

typedef struct NNSG2dPaletteData
{

    GXTexFmt            fmt;
    BOOL                bExtendedPlt;

    u32                 szByte;
    void*               pRawData;          // offset addr of the content.

}
NNSG2dPaletteData;

typedef enum NNS_G2D_VRAM_TYPE
{
    NNS_G2D_VRAM_TYPE_3DMAIN = 0,
    NNS_G2D_VRAM_TYPE_2DMAIN = 1,
    NNS_G2D_VRAM_TYPE_2DSUB  = 2,
    NNS_G2D_VRAM_TYPE_MAX    = 3

} NNS_G2D_VRAM_TYPE;

typedef struct NNSG2dImageAttr
{
    GXTexSizeS                      sizeS;          // Image size (Invalid data is set during 1D mapping.)
    GXTexSizeT                      sizeT;          // Image size (Invalid data is set during 1D mapping.)

    GXTexFmt                        fmt;            // Image format
    BOOL                            bExtendedPlt;   // Whether or not to use the extended palette

    GXTexPlttColor0                 plttUse;        // How to use palette number 0
    GXOBJVRamModeChar               mappingType;    // Mapping mode
}
NNSG2dImageAttr;

typedef struct NNSG2dVRamLocation
{
    u32                 baseAddrOfVram[ NNS_G2D_VRAM_TYPE_MAX ];
}
NNSG2dVRamLocation;

typedef struct NNSG2dImageProxy
{
    NNSG2dVRamLocation        vramLocation;
    NNSG2dImageAttr           attr;
}
NNSG2dImageProxy;

typedef struct NNSG2dPaletteCompressInfo
{
    u16               numPalette;
    u16               pad16;
    void*             pPlttIdxTbl;        // offset addr.

}
    NNSG2dPaletteCompressInfo;

void NNS_G2dLoadImage1DMapping
(
    const NNSG2dCharacterData*  pSrcData,
    u32                         baseAddr,
    NNS_G2D_VRAM_TYPE           type,
    NNSG2dImageProxy*           pImgProxy
);

void NNS_G2dLoadImage2DMapping
(
    const NNSG2dCharacterData*  pSrcData,
    u32                         baseAddr,
    NNS_G2D_VRAM_TYPE           type,
    NNSG2dImageProxy*           pImgProxy
);

typedef struct NNSG2dImagePaletteProxy
{

    GXTexFmt                  fmt;          // palette format
    // (Obtainable values are limited to GX_TEXFMT_PLTT16 and GX_TEXFMT_PLTT256)

    BOOL                      bExtendedPlt; // Use expanded palette?

    NNSG2dVRamLocation        vramLocation;
}
    NNSG2dImagePaletteProxy;

void NNS_G2dLoadPalette
(
    const NNSG2dPaletteData*    pSrcData,
    u32                         addr,
    NNS_G2D_VRAM_TYPE           type,
    NNSG2dImagePaletteProxy*    pPltProxy
);

void NNS_G2dLoadPaletteEx
(
    const NNSG2dPaletteData*            pSrcData,
    const NNSG2dPaletteCompressInfo*    pCmpInfo,
    u32                                 addr,
    NNS_G2D_VRAM_TYPE                   type,
    NNSG2dImagePaletteProxy*            pPltProxy
);

BOOL NNS_G2dGetUnpackedBGCharacterData( void* pNcgrFile, NNSG2dCharacterData** ppCharData );
BOOL NNS_G2dGetUnpackedCharacterData( void* pNcgrFile, NNSG2dCharacterData** ppCharData );
BOOL NNS_G2dGetUnpackedScreenData( void* pNscrFile, NNSG2dScreenData** ppScrData );
BOOL NNS_G2dGetUnpackedPaletteData( void* pNclrFile, NNSG2dPaletteData** ppPltData );
BOOL NNS_G2dGetUnpackedPaletteData( void* pNclrFile, NNSG2dPaletteData** ppPltData );
BOOL NNS_G2dGetUnpackedPaletteCompressInfo( void* pNclrFile, NNSG2dPaletteCompressInfo** ppPltCmpInfo );

#endif //NNSYS_NNS_G2D_H
