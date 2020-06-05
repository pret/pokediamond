#include "global.h"
#include "gx.h"


ARM_FUNC void G3_BeginMakeDL(struct GXDLInfo *displaylist, void *r1, u32 r2){
    displaylist->length = r2;
    displaylist->bottom = r1;
    displaylist->curr_cmd = r1;
    displaylist->curr_param = (u32 *)r1 + 1;
    displaylist->param0_cmd_flg = 0x0;
}

ARM_FUNC s32 G3_EndMakeDL(struct GXDLInfo *displaylist){
    if (displaylist->bottom == (u32 *)displaylist->curr_cmd)
        return 0;
    //pads the buffer with 0 to 4byte alignment if needed
    switch((u32)displaylist->curr_cmd & 0x3)
    {
    case 0:
        return displaylist->curr_cmd - (u8 *)displaylist->bottom;
    case 1:
        *displaylist->curr_cmd++ = 0x0;
    case 2:
        *displaylist->curr_cmd++ = 0x0;
    case 3:
        *displaylist->curr_cmd++ = 0x0;
    }
    if (displaylist->param0_cmd_flg)
    {
        *displaylist->curr_param++ = 0x0;
        displaylist->param0_cmd_flg = 0x0;
    }
    displaylist->curr_cmd = (u8 *)displaylist->curr_param;
    return displaylist->curr_cmd - (u8 *)displaylist->bottom;
}
