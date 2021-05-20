#ifndef POKEDIAMOND_GX_LAYERS_H
#define POKEDIAMOND_GX_LAYERS_H


#include "global.h"

struct GX_LayerData
{
    u32 EngineB_DISPCNT_LayerMask;
    u32 EngineA_DISPCNT_LayerMask;
};


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
    u32 mode1;
    u32 mode2;
    u32 mode3;
    u32 mode4;
};



THUMB_FUNC void GX_SetBanks(const struct GraphicsBanks *banks);
THUMB_FUNC void GX_DisableEngineALayers();
THUMB_FUNC void GX_EngineAToggleLayers(u32 layer_mask, GX_LayerToggle layer_toggle);
THUMB_FUNC void GX_SetEngineALayers(u32 layer_mask);
THUMB_FUNC void GX_DisableEngineBLayers();
THUMB_FUNC void GX_EngineBToggleLayers(u32 layer_mask, GX_LayerToggle layer_toggle);
THUMB_FUNC void GX_BothDispOn();
THUMB_FUNC void GX_SwapDisplay();
THUMB_FUNC u32 GX_GetEngineALayers();

#endif //POKEDIAMOND_GX_LAYERS_H
