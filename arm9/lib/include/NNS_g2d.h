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


extern BOOL NNS_G2dGetUnpackedBGCharacterData( void* pNcgrFile, NNSG2dCharacterData** ppCharData );
extern BOOL NNS_G2dGetUnpackedScreenData( void* pNscrFile, NNSG2dScreenData** ppScrData );

#endif //NNSYS_NNS_G2D_H
