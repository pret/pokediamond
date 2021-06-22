#ifndef POKEDIAMOND_GX_LAYERS_H
#define POKEDIAMOND_GX_LAYERS_H


#include "global.h"
#include "gx.h"


typedef enum {
    GX_LAYER_TOGGLE_OFF,
    GX_LAYER_TOGGLE_ON,
} GX_LayerToggle;


struct GraphicsBanks
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
};


struct GraphicsModes {
    GXDispMode dispMode;
    GXBGMode bgMode;
    GXBGMode subMode;
    GXBG0As _2d3dMode;
};



void GX_SetBanks(const struct GraphicsBanks *banks);
void GX_DisableEngineALayers();
void GX_EngineAToggleLayers(u32 layer_mask, GX_LayerToggle layer_toggle);
void GX_SetEngineALayers(u32 layer_mask);
void GX_DisableEngineBLayers();
void GX_EngineBToggleLayers(u32 layer_mask, GX_LayerToggle layer_toggle);
void GX_BothDispOn();
void GX_SwapDisplay();
u32 GX_GetEngineALayers();

#endif //POKEDIAMOND_GX_LAYERS_H
