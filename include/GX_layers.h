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
