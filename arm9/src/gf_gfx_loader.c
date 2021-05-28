#include "global.h"
#include "filesystem.h"
#include "NNS_g2d.h"
#include "unk_02016B94.h"
#include "GXS_ioreg.h"

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

void FUN_02006948(NarcId narcId, s32 memberNo, u32 r4, u32 r7, u32 r6, u32 r5, u32 heap_id);

THUMB_FUNC void FUN_02006930(NarcId narcId, s32 memberNo, u32 r2, u32 r3, u32 sp10, u32 heap_id)
{
    FUN_02006948(narcId, memberNo, r2, 0, r3, sp10, heap_id);
}

THUMB_FUNC void FUN_02006948(NarcId narcId, s32 memberNo, u32 r4, u32 r7, u32 r6, u32 r5, u32 heap_id)
{
    static void (*const UNK_020ECBB0[])(void *, u32, u32) = {
        GX_LoadBGPltt,
        GX_LoadOBJPltt,
        GX_LoadBGExtPltt,
        GX_LoadOBJExtPltt,
        GXS_LoadBGPltt,
        GXS_LoadOBJPltt,
        GXS_LoadBGExtPltt,
        GXS_LoadOBJExtPltt
    };
    NNSG2dPaletteData * sp8;
    void * sp4 = UncompressFromNarc(narcId, memberNo, FALSE, heap_id, TRUE);
    if (sp4 != NULL)
    {
        if (NNS_G2dGetUnpackedPaletteData(sp4, &sp8))
        {
            sp8->pRawData = (void *)((u32)sp8->pRawData + r7);
            if (r5 == 0)
                r5 = sp8->szByte - r7;
            DC_FlushRange(sp8->pRawData, r5);
            switch (r4)
            {
            case 2:
                GX_BeginLoadBGExtPltt();
                UNK_020ECBB0[r4](sp8->pRawData, r6, r5);
                GX_EndLoadBGExtPltt();
                break;
            case 6:
                GXS_BeginLoadBGExtPltt();
                UNK_020ECBB0[r4](sp8->pRawData, r6, r5);
                GXS_EndLoadBGExtPltt();
                break;
            case 3:
                GX_BeginLoadOBJExtPltt();
                UNK_020ECBB0[r4](sp8->pRawData, r6, r5);
                GX_EndLoadOBJExtPltt();
                break;
            case 7:
                GXS_BeginLoadOBJExtPltt();
                UNK_020ECBB0[r4](sp8->pRawData, r6, r5);
                GXS_EndLoadOBJExtPltt();
                break;
            default:
                UNK_020ECBB0[r4](sp8->pRawData, r6, r5);
                break;
            }
        }
        FreeToHeap(sp4);
    }
}

THUMB_FUNC u32 FUN_02006A34(NarcId narcId, s32 memberId, u32 r5, u32 r6, u32 r4, BOOL isCompressed, u32 heap_id)
{
    static void (*const UNK_020ECBA0[])(void *, u32, u32) = {
        GX_LoadOBJ,
        GXS_LoadOBJ
    };

    NNSG2dCharacterData* sp4;
    void * r7 = UncompressFromNarc(narcId, memberId, isCompressed, heap_id, TRUE);
    if (r7 != NULL)
    {
        if (NNS_G2dGetUnpackedCharacterData(r7, &sp4))
        {
            if (r4 == 0)
                r4 = sp4->szByte;
            DC_FlushRange(sp4->pRawData, r4);
            UNK_020ECBA0[r5](sp4->pRawData, r6, r4);
        }
        FreeToHeap(r7);
    }
    return r4;
}

THUMB_FUNC void FUN_02006A8C(NarcId narcId, s32 memberId, NNS_G2D_VRAM_TYPE r5, u32 r4, u32 heap_id, NNSG2dImagePaletteProxy * sp24)
{
    void * r6 = UncompressFromNarc(narcId, memberId, FALSE, heap_id, TRUE);
    NNSG2dPaletteData* sp8;
    NNSG2dPaletteCompressInfo* sp4;
    if (r6 != NULL)
    {
        BOOL r7 = NNS_G2dGetUnpackedPaletteCompressInfo(r6, &sp4);
        if (NNS_G2dGetUnpackedPaletteData(r6, &sp8))
        {
            if (r7)
            {
                NNS_G2dLoadPaletteEx(sp8, sp4, r4, r5, sp24);
            }
            else
            {
                NNS_G2dLoadPalette(sp8, r4, r5, sp24);
            }
        }
        FreeToHeap(r6);
    }
}

THUMB_FUNC u32 FUN_02006AE4(NarcId narcId, s32 memberId, BOOL isCompressed, u32 whichRoutine, u32 szByte, NNS_G2D_VRAM_TYPE type, u32 baseAddr, u32 heap_id, NNSG2dImageProxy *pImgProxy)
{
    static void (*const UNK_020ECBA8[])(const NNSG2dCharacterData *, u32, NNS_G2D_VRAM_TYPE, NNSG2dImageProxy *) = {
        NNS_G2dLoadImage1DMapping,
        NNS_G2dLoadImage2DMapping
    };

    void * pFile = UncompressFromNarc(narcId, memberId, isCompressed, heap_id, TRUE);
    u32 retSize = 0;
    NNSG2dCharacterData * pSrcData;
    if (pFile != NULL)
    {
        if (NNS_G2dGetUnpackedCharacterData(pFile, &pSrcData))
        {
            if (szByte != 0)
                pSrcData->szByte = szByte;
            UNK_020ECBA8[whichRoutine](pSrcData, baseAddr, type, pImgProxy);
            retSize = pSrcData->szByte;
        }
        FreeToHeap(pFile);
    }
    return retSize;
}

THUMB_FUNC void FUN_02006B38(NarcId narcId, s32 memberId, BOOL isCompressed, u32 r5, u32 sp18, NNS_G2D_VRAM_TYPE sp1C, u32 sp20, u32 heap_id, NNSG2dImageProxy * sp28)
{
    static void (*const UNK_020ECB98[])(const NNSG2dCharacterData *, u32, NNS_G2D_VRAM_TYPE, NNSG2dImageProxy *) = {
        NNS_G2dLoadImage1DMapping,
        NNS_G2dLoadImage2DMapping
    };
    NNSG2dCharacterData * sp4;
    void * r4 = UncompressFromNarc(narcId, memberId, isCompressed, heap_id, TRUE);
    if (r4 != NULL)
    {
        if (NNS_G2dGetUnpackedCharacterData(r4, &sp4))
        {
            if (sp18 != 0)
                sp4->szByte = sp18;
            switch (sp1C)
            {
            case NNS_G2D_VRAM_TYPE_2DMAIN:
                sp4->mapingType = reg_GX_DISPCNT & (REG_GX_DISPCNT_EXOBJ_CH_MASK | REG_GX_DISPCNT_OBJMAP_CH_MASK);
                break;
            case NNS_G2D_VRAM_TYPE_2DSUB:
                sp4->mapingType = reg_GXS_DB_DISPCNT & (REG_GXS_DB_DISPCNT_EXOBJ_MASK | REG_GXS_DB_DISPCNT_OBJMAP_CH_MASK);
                break;
            default:
                ;
            }
            UNK_020ECB98[r5](sp4, sp20, sp1C, sp28);
        }
        FreeToHeap(r4);
    }
}

THUMB_FUNC void * FUN_02006BB0(NarcId narcId, s32 memberId, BOOL isCompressed, NNSG2dCharacterData ** r4, u32 heap_id)
{
    void * r5 = UncompressFromNarc(narcId, memberId, isCompressed, heap_id, FALSE);
    if (r5 != NULL)
    {
        if (!NNS_G2dGetUnpackedBGCharacterData(r5, r4))
        {
            FreeToHeap(r5);
            return NULL;
        }
    }
    return r5;
}

THUMB_FUNC void * FUN_02006BDC(NarcId narcId, s32 memberId, BOOL isCompressed, NNSG2dScreenData ** r4, u32 heap_id)
{
    void * r5 = UncompressFromNarc(narcId, memberId, isCompressed, heap_id, FALSE);
    if (r5 != NULL)
    {
        if (!NNS_G2dGetUnpackedScreenData(r5, r4))
        {
            FreeToHeap(r5);
            return NULL;
        }
    }
    return r5;
}

THUMB_FUNC void * FUN_02006C08(NarcId narcId, s32 memberId, NNSG2dPaletteData ** r4, u32 heap_id)
{
    void * r5 = UncompressFromNarc(narcId, memberId, FALSE, heap_id, FALSE);
    if (r5 != NULL)
    {
        if (!NNS_G2dGetUnpackedPaletteData(r5, r4))
        {
            FreeToHeap(r5);
            return NULL;
        }
    }
    return r5;
}

THUMB_FUNC void * FUN_02006C30(NarcId narcId, s32 memberId, BOOL isCompressed, NNSG2dCellDataBank ** r4, u32 heap_id)
{
    void * r5 = UncompressFromNarc(narcId, memberId, isCompressed, heap_id, FALSE);
    if (r5 != NULL)
    {
        if (!NNS_G2dGetUnpackedCellBank(r5, r4))
        {
            FreeToHeap(r5);
            return NULL;
        }
    }
    return r5;
}

THUMB_FUNC void * FUN_02006C5C(NarcId narcId, s32 memberId, BOOL isCompressed, NNSG2dAnimBankData ** r4, u32 heap_id)
{
    void * r5 = UncompressFromNarc(narcId, memberId, isCompressed, heap_id, FALSE);
    if (r5 != NULL)
    {
        if (!NNS_G2dGetUnpackedAnimBank(r5, r4))
        {
            FreeToHeap(r5);
            return NULL;
        }
    }
    return r5;
}

THUMB_FUNC void * FUN_02006C88(NarcId narcId, s32 memberId, u32 heap_id)
{
    return UncompressFromNarc(narcId, memberId, TRUE, heap_id, FALSE);
}

THUMB_FUNC void * UncompressFromNarc(NarcId narcId, s32 memberNo, BOOL isCompressed, u32 heap_id, BOOL allocAtEnd)
{
    void * dest;
    void * dest2;
    if (isCompressed || allocAtEnd == TRUE)
    {
        u32 size = GetNarcMemberSizeByIdPair(narcId, memberNo);
        dest = AllocFromHeapAtEnd(heap_id, size);
    }
    else
    {
        u32 size = GetNarcMemberSizeByIdPair(narcId, memberNo);
        dest = AllocFromHeap(heap_id, size);
    }
    if (dest != NULL)
    {
        ReadWholeNarcMemberByIdPair(dest, narcId, memberNo);
        if (isCompressed)
        {
            if (allocAtEnd == FALSE)
            {
                dest2 = AllocFromHeap(heap_id, (*(u32 *)dest) >> 8);
            }
            else
            {
                dest2 = AllocFromHeapAtEnd(heap_id, (*(u32 *)dest) >> 8);
            }
            if (dest2 != NULL)
            {
                MI_UncompressLZ8(dest, dest2);
                FreeToHeap(dest);
            }
            dest = dest2; // UB: if dest2 is NULL, dest is never freed
        }
    }
    return dest;
}

THUMB_FUNC void * FUN_02006D18(NarcId narcId, s32 memberNo, BOOL isCompressed, u32 heap_id, BOOL allocAtEnd, u32 *size_p)
{
    void * dest;
    void * dest2;
    *size_p = GetNarcMemberSizeByIdPair(narcId, memberNo);
    if (isCompressed || allocAtEnd == TRUE)
    {
        dest = AllocFromHeapAtEnd(heap_id, *size_p);
    }
    else
    {
        dest = AllocFromHeap(heap_id, *size_p);
    }
    if (dest != NULL)
    {
        ReadWholeNarcMemberByIdPair(dest, narcId, memberNo);
        if (isCompressed)
        {
            *size_p = (*(u32 *)dest) >> 8;
            if (allocAtEnd == FALSE)
            {
                dest2 = AllocFromHeap(heap_id, *size_p);
            }
            else
            {
                dest2 = AllocFromHeapAtEnd(heap_id, *size_p);
            }
            if (dest2 != NULL)
            {
                MI_UncompressLZ8(dest, dest2);
                FreeToHeap(dest);
            }
            dest = dest2; // UB: if dest2 is NULL, dest is never freed
        }
    }
    return dest;
}
