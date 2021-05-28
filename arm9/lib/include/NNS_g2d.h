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

typedef struct NNSG2dCellVramTransferData
{
    u32        srcDataOffset;
    u32        szByte;

}
NNSG2dCellVramTransferData;

typedef struct NNSG2dVramTransferData
{
    u32                                 szByteMax;             // Maximum byte count during all VRAM transfers
    NNSG2dCellVramTransferData*         pCellTransferDataArray;// This is the length of the numCells amount of the maintained NNSG2dCellDataBank.
    //

}
NNSG2dVramTransferData;

typedef struct NNSG2dCellOAMAttrData
{
    u16         attr0;
    u16         attr1;
    u16         attr2;

}
NNSG2dCellOAMAttrData;

typedef struct NNSG2dCellData
{
    u16                       numOAMAttrs;      // Number of OAM attributes
    u16                       cellAttr;         // Information related to cell type
    // Information related to flips (upper 8 bits)
    // Information related to bounding information
    //
    // Information related to rendering optimization (lower 8 bits)
    //      (6bit => Radius of bounding sphere  >> 2 )


    NNSG2dCellOAMAttrData*    pOamAttrArray;    // Pointer to the NNSG2dCellOAMAttrData array

}
NNSG2dCellData;

typedef struct NNSG2dCellDataBank
{
    u16                              numCells;               // Total number of cells
    u16                              cellBankAttr;           // Attribute
    NNSG2dCellData*                  pCellDataArrayHead;     // offset address
    NNSG2dCharacterDataMapingType    mappingMode;            // Mapping mode of the referenced character

    NNSG2dVramTransferData*          pVramTransferData;      // Information related to Vram transfer animation

    void*                            pStringBank;            // Character string bank
    void*                            pExtendedData;          // offset addr (if it exists)


}
NNSG2dCellDataBank;

typedef enum NNSG2dAnimationPlayMode
{
    NNS_G2D_ANIMATIONPLAYMODE_INVALID = 0x0,    // Disabled
    NNS_G2D_ANIMATIONPLAYMODE_FORWARD,          // one-time playback (forward)
    NNS_G2D_ANIMATIONPLAYMODE_FORWARD_LOOP,     // repeat playback (forward loop)
    NNS_G2D_ANIMATIONPLAYMODE_REVERSE,          // reverse playback (reverse (forward + backward))
    NNS_G2D_ANIMATIONPLAYMODE_REVERSE_LOOP,     // reverse playback repeat (reverse (forward + backward) loop)
    NNS_G2D_ANIMATIONPLAYMODE_MAX
}
NNSG2dAnimationPlayMode;

typedef struct NNSG2dAnimFrameData
{
    void*           pContent;   // pointer to animation result
    u16             frames;     // animation frame continuation time (units: video frames)
    u16             pad16;      // padding

}
NNSG2dAnimFrameData;

typedef struct NNSG2dAnimSequenceData
{
    u16                     numFrames;         // number of animation frames forming the sequence
    u16                     loopStartFrameIdx; // loop start animation frame number

    u32                     animType;          // animation type (upper 16 bits)
    //  animation elements (lower 16 bits)
    // (What's referenced by NNSG2dAnimFrameData.pContent is changed)

    NNSG2dAnimationPlayMode playMode;          // animation sequence playback method
    NNSG2dAnimFrameData*    pAnmFrameArray;    // offset from the head of pFrameArray.

}
NNSG2dAnimSequenceData;

typedef struct NNSG2dAnimBankData
{

    u16                       numSequences;         // number of animation sequences
    u16                       numTotalFrames;       // total number of animation frames
    NNSG2dAnimSequenceData*   pSequenceArrayHead;   // pointer to animation sequence array
    NNSG2dAnimFrameData*      pFrameArrayHead;      // pointer to animation frame array
    void*                     pAnimContents;        // pointer to animation result array
    void*                     pStringBank;          // pointer to string bank (set during execution)
    void*                     pExtendedData;        // pointer to library expansion area (not used)

}
NNSG2dAnimBankData;


BOOL NNS_G2dGetUnpackedBGCharacterData( void* pNcgrFile, NNSG2dCharacterData** ppCharData );
BOOL NNS_G2dGetUnpackedCharacterData( void* pNcgrFile, NNSG2dCharacterData** ppCharData );
BOOL NNS_G2dGetUnpackedScreenData( void* pNscrFile, NNSG2dScreenData** ppScrData );
BOOL NNS_G2dGetUnpackedPaletteData( void* pNclrFile, NNSG2dPaletteData** ppPltData );
BOOL NNS_G2dGetUnpackedPaletteData( void* pNclrFile, NNSG2dPaletteData** ppPltData );
BOOL NNS_G2dGetUnpackedPaletteCompressInfo( void* pNclrFile, NNSG2dPaletteCompressInfo** ppPltCmpInfo );
BOOL NNS_G2dGetUnpackedCellBank( void* pNcerFile, NNSG2dCellDataBank** ppCellBank );
BOOL NNS_G2dGetUnpackedAnimBank( void* pNanrFile, NNSG2dAnimBankData** ppAnimBank );

#endif //NNSYS_NNS_G2D_H
