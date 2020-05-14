#include "global.h"
#include "main.h"
#include "gx.h"

extern u32 gUnk02106814;

extern u32 gUnk021D3410;
extern u32 gUnk021D3400;
extern u32 gUnk021D3414;
extern u32 gUnk021D3418;

//probably structs of length 0x6
extern u16 gUnk02103B4C[];
extern u16 gUnk02103B4E[];
extern u16 gUnk02103B50[];

extern u32 gUnk021D3408;
extern u32 gUnk021D3404;
extern u16 gUnk02103B3C[];

extern s32 gUnk021D33FC;
extern u32 gUnk021D340C;

static inline void _GX_Load_16(void *src, void *dst, u32 size){
    if (gUnk02106814 != -1 && size > 0x1C)
    {
        MI_DmaCopy16(gUnk02106814, src, dst, size);
    }
    else
    {
        MIi_CpuCopy16(src, dst, size);
    }
}

static inline void _GX_Load_32(void *src, void *dst, u32 size){
    if (gUnk02106814 != -1 && size > 0x30)
    {
        MI_DmaCopy32(gUnk02106814, src, dst, size);
    }
    else
    {
        MIi_CpuCopy32(src, dst, size);
    }
}

static inline void _GX_Load_32_Async(void *src, void *dst, u32 size, void *func, void *ptr){
    if (gUnk02106814 != -1)
    {
        MI_DmaCopy32Async(gUnk02106814, src, dst, size, func, ptr);
    }
    else
    {
        MIi_CpuCopy32(src, dst, size);
    }
}

void GX_BeginLoadTex(){
    u32 temp = GX_ResetBankForTex();
    gUnk021D3410 = temp;
    gUnk021D3400 = gUnk02103B4C[temp * 3] << 0xC;
    gUnk021D3414 = gUnk02103B4E[temp * 3] << 0xC;
    gUnk021D3418 = gUnk02103B50[temp * 3] << 0xC;
}

void GX_LoadTex(void *src, u32 offset, u32 size){
    void *temp;
    if (!gUnk021D3414)
    {
        temp = (void *)(gUnk021D3400 + offset);
    }
    else
    {
        if ((offset + size) < gUnk021D3418)
        {
            temp = (void *)(gUnk021D3400 + offset);
        }
        else if (offset >= gUnk021D3418)
        {
            temp = (void *)(gUnk021D3414 + offset - gUnk021D3418);
        }
        else
        {
            void *temp2 = (void *)gUnk021D3414;
            u32 temp1 = gUnk021D3418 - offset;
            temp = (void *)(gUnk021D3400 + offset);
            _GX_Load_32(src, temp, temp1);
            _GX_Load_32_Async((void *)((u8 *)src + temp1), temp2, (size - temp1), NULL, NULL);
            return;
        }
    }
    _GX_Load_32_Async(src, temp, size, NULL, NULL);
}

void GX_EndLoadTex(){
    if (gUnk02106814 != -1)
        MI_WaitDma(gUnk02106814);
    GX_SetBankForTex(gUnk021D3410);
    gUnk021D3418 = 0x0;
    gUnk021D3414 = 0x0;
    gUnk021D3400 = 0x0;
    gUnk021D3410 = 0x0;
}

void GX_BeginLoadTexPltt(){
    s32 temp = GX_ResetBankForTexPltt();
    gUnk021D3408 = temp;
    gUnk021D3404 = gUnk02103B3C[temp >> 4] << 0xC;
}

void GX_LoadTexPltt(void *src, u32 offset, u32 size){
    _GX_Load_32_Async(src, (void *)(gUnk021D3404 + offset), size, NULL, NULL);
}

void GX_EndLoadTexPltt(){
    if (gUnk02106814 != -1)
        MI_WaitDma(gUnk02106814);
    GX_SetBankForTexPltt(gUnk021D3408);
    gUnk021D3408 = 0x0;
    gUnk021D3404 = 0x0;
}

void GX_BeginLoadClearImage(){
    s32 temp = GX_ResetBankForClearImage();
    gUnk021D33FC = temp;
    switch (temp)
    {
    case 2:
    case 3:
        gUnk021D340C = 0x6800000;
        return;
    case 8:
    case 12:
        gUnk021D340C = 0x6840000;
        return;
    case 1:
        gUnk021D340C = 0x67E0000;
        return;
    case 4:
        gUnk021D340C = 0x6820000;
    }
}

void GX_LoadClearImageColor(void *src, u32 size){
    _GX_Load_32_Async(src, (void *)(gUnk021D340C), size, NULL, NULL);
}

void GX_LoadClearImageDepth(void *src, u32 size){
    _GX_Load_32_Async(src, (void *)(gUnk021D340C + 0x20000), size, NULL, NULL);
}

void GX_EndLoadClearImage(){
    if (gUnk02106814 != -1)
        MI_WaitDma(gUnk02106814);
    GX_SetBankForClearImage(gUnk021D33FC);
    gUnk021D33FC = 0x0;
    gUnk021D340C = 0x0;
}
