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
