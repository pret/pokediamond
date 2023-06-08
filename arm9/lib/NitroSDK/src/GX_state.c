#include "nitro/types.h"
#include "gx.h"
#include "code32.h"

struct GX_State gGXState;

void GX_InitGXState(){
    gGXState.lcdc = 0x0;
    gGXState.bg = 0x0;
    gGXState.obj = 0x0;
    gGXState.arm7 = 0x0;
    gGXState.tex = 0x0;
    gGXState.texPltt = 0x0;
    gGXState.clrImg = 0x0;
    gGXState.bgExtPltt = 0x0;
    gGXState.objExtPltt = 0x0;
    gGXState.sub_bg = 0x0;
    gGXState.sub_obj = 0x0;
    gGXState.sub_bgExtPltt = 0x0;
    gGXState.sub_objExtPltt = 0x0;
    reg_GX_VRAMCNT = 0x0;
    reg_GX_VRAMCNT_E = 0x0;
    reg_GX_VRAMCNT_F = 0x0;
    reg_GX_VRAMCNT_G = 0x0;
    reg_GX_VRAM_HI_CNT = 0x0;
}
