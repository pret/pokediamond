#include "global.h"
#include "main.h"
#include "gx.h"


ARM_FUNC void G3_BeginMakeDL(struct DL *displaylist, void *r1, u32 r2){
    displaylist->var0C = r2;
    displaylist->var08 = r1;
    displaylist->var00 = r1;
    displaylist->var04 = (u32 *)r1 + 1;
    displaylist->var10 = 0x0;
}

ARM_FUNC s32 G3_EndMakeDL(struct DL *displaylist){
    if (displaylist->var08 == displaylist->var00)
        return 0;
    //pads the buffer with 0 to 4byte alignment if needed
    switch((u32)displaylist->var00 & 0x3)
    {
    case 0:
        return displaylist->var00 - displaylist->var08;
    case 1:
        *displaylist->var00++ = 0x0;
    case 2:
        *displaylist->var00++ = 0x0;
    case 3:
        *displaylist->var00++ = 0x0;
    }
    if (displaylist->var10)
    {
        *displaylist->var04++ = 0x0;
        displaylist->var10 = 0x0;
    }
    displaylist->var00 = (u8 *)displaylist->var04;
    return displaylist->var00 - displaylist->var08;
}
