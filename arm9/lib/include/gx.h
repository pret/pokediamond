#ifndef GUARD_GX_H
#define GUARD_GX_H

struct DL
{
    u8 *var00; //end pointer
    u32 *var04; //aligned end pointer
    u8 *var08; //start pointer
    u32 var0C;
    u32 var10; //pad end with zero bool
};

//GX_g3
void G3_BeginMakeDL(struct DL *displaylist, void *r1, u32 r2);
s32 G3_EndMakeDL(struct DL *displaylist);


//GX_asm
void GX_SendFifo48B(void *src, void *dst);


//GXi_NopClearFifo128_ probably asm

#endif //GUARD_GX_H
