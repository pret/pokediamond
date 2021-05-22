#ifndef POKEDIAMOND_GX_LAYERS_H
#define POKEDIAMOND_GX_LAYERS_H


#include "global.h"
#include "GX_vramcnt.h"
#include "error_message_reset.h"
#include "gx.h"

struct GX_LayerData
{
    u32 EngineB_DISPCNT_LayerMask;
    u32 EngineA_DISPCNT_LayerMask;
};


typedef enum {
    GX_LAYER_TOGGLE_OFF,
    GX_LAYER_TOGGLE_ON,
} GX_LayerToggle;


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
