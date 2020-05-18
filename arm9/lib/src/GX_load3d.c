#include "global.h"
#include "main.h"
#include "GX.h"

extern u32 GXi_DmaId;

extern u32 sTex;
extern u32 sTexLCDCBlk1;
extern u32 sTexLCDCBlk2;
extern u32 sSzTexBlk1;

static const struct _TexStartAddrTable
{
    u16     blk1;                      // 12 bit shift
    u16     blk2;                      // 12 bit shift
    u16     szBlk1;                    // 12 bit shift
};
extern struct _TexStartAddrTable sTexStartAddrTable[16];


extern u32 sTexPltt;
extern u32 sTexPlttLCDCBlk;
extern u16 sTexPlttStartAddrTable[8];

extern s32 sClrImg;
extern u32 sClrImgLCDCBlk;

ARM_FUNC void GX_BeginLoadTex(){
    u32 temp = GX_ResetBankForTex();
    sTex = temp;
    sTexLCDCBlk1 = sTexStartAddrTable[temp].blk1 << 0xC;
    sTexLCDCBlk2 = sTexStartAddrTable[temp].blk2 << 0xC;
    sSzTexBlk1 = sTexStartAddrTable[temp].szBlk1 << 0xC;
}

ARM_FUNC void GX_LoadTex(void *src, u32 offset, u32 size){
    void *temp;
    if (!sTexLCDCBlk2)
    {
        temp = (void *)(sTexLCDCBlk1 + offset);
    }
    else
    {
        if ((offset + size) < sSzTexBlk1)
        {
            temp = (void *)(sTexLCDCBlk1 + offset);
        }
        else if (offset >= sSzTexBlk1)
        {
            temp = (void *)(sTexLCDCBlk2 + offset - sSzTexBlk1);
        }
        else
        {
            void *temp2 = (void *)sTexLCDCBlk2;
            u32 temp1 = sSzTexBlk1 - offset;
            temp = (void *)(sTexLCDCBlk1 + offset);
            GXi_DmaCopy32(GXi_DmaId, src, temp, temp1);
            GXi_DmaCopy32Async(GXi_DmaId, (void *)((u8 *)src + temp1), temp2, (size - temp1), NULL, NULL);
            return;
        }
    }
    GXi_DmaCopy32Async(GXi_DmaId, src, temp, size, NULL, NULL);
}

ARM_FUNC void GX_EndLoadTex(){
    GXi_WaitDma(GXi_DmaId);
    GX_SetBankForTex(sTex);
    sSzTexBlk1 = 0x0;
    sTexLCDCBlk2 = 0x0;
    sTexLCDCBlk1 = 0x0;
    sTex = 0x0;
}

ARM_FUNC void GX_BeginLoadTexPltt(){
    s32 temp = GX_ResetBankForTexPltt();
    sTexPltt = temp;
    sTexPlttLCDCBlk = sTexPlttStartAddrTable[temp >> 4] << 0xC;
}

ARM_FUNC void GX_LoadTexPltt(void *src, u32 offset, u32 size){
    GXi_DmaCopy32Async(GXi_DmaId, src, (void *)(sTexPlttLCDCBlk + offset), size, NULL, NULL);
}

ARM_FUNC void GX_EndLoadTexPltt(){
    GXi_WaitDma(GXi_DmaId);
    GX_SetBankForTexPltt(sTexPltt);
    sTexPltt = 0x0;
    sTexPlttLCDCBlk = 0x0;
}

ARM_FUNC void GX_BeginLoadClearImage(){
    s32 temp = GX_ResetBankForClearImage();
    sClrImg = temp;
    switch (temp)
    {
    case 2:
    case 3:
        sClrImgLCDCBlk = 0x6800000;
        return;
    case 8:
    case 12:
        sClrImgLCDCBlk = 0x6840000;
        return;
    case 1:
        sClrImgLCDCBlk = 0x67E0000;
        return;
    case 4:
        sClrImgLCDCBlk = 0x6820000;
    }
}

ARM_FUNC void GX_LoadClearImageColor(void *src, u32 size){
    GXi_DmaCopy32Async(GXi_DmaId, src, (void *)(sClrImgLCDCBlk), size, NULL, NULL);
}

ARM_FUNC void GX_LoadClearImageDepth(void *src, u32 size){
    GXi_DmaCopy32Async(GXi_DmaId, src, (void *)(sClrImgLCDCBlk + 0x20000), size, NULL, NULL);
}

ARM_FUNC void GX_EndLoadClearImage(){
    GXi_WaitDma(GXi_DmaId);
    GX_SetBankForClearImage(sClrImg);
    sClrImg = 0x0;
    sClrImgLCDCBlk = 0x0;
}
