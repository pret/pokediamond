#ifndef GUARD_GX_STATE_H
#define GUARD_GX_STATE_H

struct GX_State
{
    u16     lcdc;
    u16     bg;
    u16     obj;
    u16     arm7;
    u16     tex;
    u16     texPltt;
    u16     clrImg;
    u16     bgExtPltt;
    u16     objExtPltt;

    u16     sub_bg;
    u16     sub_obj;
    u16     sub_bgExtPltt;
    u16     sub_objExtPltt;
};

void GX_InitGXState();

#endif //GUARD_GX_STATE_H
