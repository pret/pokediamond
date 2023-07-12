#ifndef POKEDIAMOND_GX_LAYERS_H
#define POKEDIAMOND_GX_LAYERS_H


#include "global.h"
#include "gx.h"


typedef enum {
    GX_LAYER_TOGGLE_OFF,
    GX_LAYER_TOGGLE_ON,
} GXLayerToggle;

typedef struct GraphicsBanks
{
    s32 bg;
    s32 bgextpltt;
    s32 subbg;
    s32 subbgextpltt;
    s32 obj;
    s32 objextpltt;
    s32 subobj;
    s32 subobjextpltt;
    s32 tex;
    s32 texpltt;
} GraphicsBanks;

typedef struct GraphicsModes {
    GXDispMode dispMode;
    GXBGMode bgMode;
    GXBGMode subMode;
    GXBG0As _2d3dMode;
} GraphicsModes;

void GX_SetBanks(const struct GraphicsBanks *banks);
void GX_DisableEngineALayers(void);
void GX_EngineAToggleLayers(u32 layer_mask, GXLayerToggle layer_toggle);
void GX_SetEngineALayers(u32 layer_mask);
void GX_DisableEngineBLayers(void);
void GX_EngineBToggleLayers(u32 layer_mask, GXLayerToggle layer_toggle);
void GX_BothDispOn(void);
void GX_SwapDisplay(void);
u32 GX_GetEngineALayers(void);

#endif //POKEDIAMOND_GX_LAYERS_H
