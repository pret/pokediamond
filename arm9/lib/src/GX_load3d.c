#include "global.h"
#include "main.h"
#include "gx.h"

extern u32 UNK_02106814;

extern u32 UNK_021D3410;
extern u32 UNK_021D3400;
extern u32 UNK_021D3414;
extern u32 UNK_021D3418;

//probably structs of length 0x6
extern u16 UNK_02103B4C[];
extern u16 UNK_02103B4E[];
extern u16 UNK_02103B50[];

extern u32 UNK_021D3408;
extern u32 UNK_021D3404;
extern u16 UNK_02103B3C[];

extern s32 UNK_021D33FC;
extern u32 UNK_021D340C;

ARM_FUNC void GX_BeginLoadTex(){
    u32 temp = GX_ResetBankForTex();
    UNK_021D3410 = temp;
    UNK_021D3400 = UNK_02103B4C[temp * 3] << 0xC;
    UNK_021D3414 = UNK_02103B4E[temp * 3] << 0xC;
    UNK_021D3418 = UNK_02103B50[temp * 3] << 0xC;
}

ARM_FUNC void GX_LoadTex(void *src, u32 offset, u32 size){
    void *temp;
    if (!UNK_021D3414)
    {
        temp = (void *)(UNK_021D3400 + offset);
    }
    else
    {
        if ((offset + size) < UNK_021D3418)
        {
            temp = (void *)(UNK_021D3400 + offset);
        }
        else if (offset >= UNK_021D3418)
        {
            temp = (void *)(UNK_021D3414 + offset - UNK_021D3418);
        }
        else
        {
            void *temp2 = (void *)UNK_021D3414;
            u32 temp1 = UNK_021D3418 - offset;
            temp = (void *)(UNK_021D3400 + offset);
            _GX_Load_32(UNK_02106814, src, temp, temp1);
            _GX_Load_32_Async(UNK_02106814, (void *)((u8 *)src + temp1), temp2, (size - temp1), NULL, NULL);
            return;
        }
    }
    _GX_Load_32_Async(UNK_02106814, src, temp, size, NULL, NULL);
}

ARM_FUNC void GX_EndLoadTex(){
    if (UNK_02106814 != -1)
        MI_WaitDma(UNK_02106814);
    GX_SetBankForTex(UNK_021D3410);
    UNK_021D3418 = 0x0;
    UNK_021D3414 = 0x0;
    UNK_021D3400 = 0x0;
    UNK_021D3410 = 0x0;
}

ARM_FUNC void GX_BeginLoadTexPltt(){
    s32 temp = GX_ResetBankForTexPltt();
    UNK_021D3408 = temp;
    UNK_021D3404 = UNK_02103B3C[temp >> 4] << 0xC;
}

ARM_FUNC void GX_LoadTexPltt(void *src, u32 offset, u32 size){
    _GX_Load_32_Async(UNK_02106814, src, (void *)(UNK_021D3404 + offset), size, NULL, NULL);
}

ARM_FUNC void GX_EndLoadTexPltt(){
    if (UNK_02106814 != -1)
        MI_WaitDma(UNK_02106814);
    GX_SetBankForTexPltt(UNK_021D3408);
    UNK_021D3408 = 0x0;
    UNK_021D3404 = 0x0;
}

ARM_FUNC void GX_BeginLoadClearImage(){
    s32 temp = GX_ResetBankForClearImage();
    UNK_021D33FC = temp;
    switch (temp)
    {
    case 2:
    case 3:
        UNK_021D340C = 0x6800000;
        return;
    case 8:
    case 12:
        UNK_021D340C = 0x6840000;
        return;
    case 1:
        UNK_021D340C = 0x67E0000;
        return;
    case 4:
        UNK_021D340C = 0x6820000;
    }
}

ARM_FUNC void GX_LoadClearImageColor(void *src, u32 size){
    _GX_Load_32_Async(UNK_02106814, src, (void *)(UNK_021D340C), size, NULL, NULL);
}

ARM_FUNC void GX_LoadClearImageDepth(void *src, u32 size){
    _GX_Load_32_Async(UNK_02106814, src, (void *)(UNK_021D340C + 0x20000), size, NULL, NULL);
}

ARM_FUNC void GX_EndLoadClearImage(){
    if (UNK_02106814 != -1)
        MI_WaitDma(UNK_02106814);
    GX_SetBankForClearImage(UNK_021D33FC);
    UNK_021D33FC = 0x0;
    UNK_021D340C = 0x0;
}
