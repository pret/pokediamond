#ifndef POKEDIAMOND_GF_GX_PLANES_H
#define POKEDIAMOND_GF_GX_PLANES_H


#include "global.h"
#include "gx.h"


typedef enum {
    GX_PLANE_TOGGLE_OFF,
    GX_PLANE_TOGGLE_ON,
} GXPlaneToggle;

typedef struct GraphicsBanks
{
    GXVRamBG bg;
    GXVRamBGExtPltt bgextpltt;
    GXVRamSubBG subbg;
    GXVRamSubBGExtPltt subbgextpltt;
    GXVRamOBJ obj;
    GXVRamOBJExtPltt objextpltt;
    GXVRamSubOBJ subobj;
    GXVRamSubOBJExtPltt subobjextpltt;
    GXVRamTex tex;
    GXVRamTexPltt texpltt;
} GraphicsBanks;

typedef struct GraphicsModes {
    GXDispMode dispMode;
    GXBGMode bgMode;
    GXBGMode subMode;
    GXBG0As _2d3dMode;
} GraphicsModes;

void GfGfx_SetBanks(const struct GraphicsBanks *banks);
void GfGfx_DisableEngineAPlanes(void);
void GfGfx_EngineATogglePlanes(u32 layer_mask, GXPlaneToggle layer_toggle);
void GfGfx_EngineASetPlanes(u32 layer_mask);
void GfGfx_DisableEngineBPlanes(void);
void GfGfx_EngineBTogglePlanes(u32 layer_mask, GXPlaneToggle layer_toggle);
void GfGfx_BothDispOn(void);
void GfGfx_SwapDisplay(void);
u32 GfGfx_EngineAGetPlanes(void);

#endif //POKEDIAMOND_GF_GX_PLANES_H
