#include "global.h"
#include "filesystem.h"
#include "NNS_g2d.h"
#include "unk_02016B94.h"

void * UncompressFromNarc(NarcId narcId, s32 memberNo, BOOL isCompressed, u32 heap_id, BOOL allocAtEnd);

THUMB_FUNC u32 FUN_0200687C(NarcId narcId, s32 memberNo, struct UnkStruct_02016B94_2 * unkStruct02016B94_2, u32 a3, u32 a4, u32 szByte, BOOL isCompressed, u32 heap_id)
{
    NNSG2dCharacterData * pCharData;
    void * r7 = UncompressFromNarc(narcId, memberNo, isCompressed, heap_id, FALSE);
    if (r7 != NULL)
    {
        if (NNS_G2dGetUnpackedBGCharacterData(r7, &pCharData))
        {
            if (szByte == 0)
                szByte = pCharData->szByte;
            FUN_02017E14(unkStruct02016B94_2, (u8)a3, pCharData->pRawData, szByte, a4);
        }
        FreeToHeap(r7);
    }
    return szByte;
}

THUMB_FUNC void FUN_020068C8(NarcId narcId, s32 memberNo, struct UnkStruct_02016B94_2 * unkStruct02016B94_2, u32 a3, u32 a4, u32 szByte, BOOL isCompressed, u32 heap_id)
{
    NNSG2dScreenData * pScreenData;
    void * r7 = UncompressFromNarc(narcId, memberNo, isCompressed, heap_id, TRUE);
    if (r7 != NULL)
    {
        if (NNS_G2dGetUnpackedScreenData(r7, &pScreenData))
        {
            if (szByte == 0)
                szByte = pScreenData->szByte;
            if (FUN_0201886C(unkStruct02016B94_2, a3) != NULL)
                FUN_02017DFC(unkStruct02016B94_2, (u8)a3, pScreenData->rawData, szByte);
            FUN_02017CE8(unkStruct02016B94_2, (u8)a3, pScreenData->rawData, szByte, a4);
        }
        FreeToHeap(r7);
    }
}
