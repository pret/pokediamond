#include "GX_layers.h"
#include "GX_vramcnt.h"
#include "gx.h"
#include "main.h"

/* TODO: rename - name implies that this is part of the SDK, when it is a GF custom */

static u32 EngineA_DISPCNT_LayerMask;
static u32 EngineB_DISPCNT_LayerMask;

THUMB_FUNC void GX_SetBanks(const struct GraphicsBanks *banks)
{
    GX_ResetBankForBG();
    GX_ResetBankForBGExtPltt();
    GX_ResetBankForSubBG();
    GX_ResetBankForSubBGExtPltt();
    GX_ResetBankForOBJ();
    GX_ResetBankForOBJExtPltt();
    GX_ResetBankForSubOBJ();
    GX_ResetBankForSubOBJExtPltt();
    GX_ResetBankForTex();
    GX_ResetBankForTexPltt();

    GX_SetBankForBG(banks->bg);
    GX_SetBankForBGExtPltt(banks->bgextpltt);
    GX_SetBankForSubBG(banks->subbg);
    GX_SetBankForSubBGExtPltt(banks->subbgextpltt);
    GX_SetBankForOBJ(banks->obj);
    GX_SetBankForOBJExtPltt(banks->objextpltt);
    GX_SetBankForSubOBJ(banks->subobj);
    GX_SetBankForSubOBJExtPltt(banks->subobjextpltt);
    GX_SetBankForTex(banks->tex);
    GX_SetBankForTexPltt(banks->texpltt);
}


THUMB_FUNC void GX_DisableEngineALayers()
{
    EngineA_DISPCNT_LayerMask = 0;
}

THUMB_FUNC void GX_EngineAToggleLayers(u32 layer_mask, GX_LayerToggle layer_toggle)
{
    if (layer_toggle == GX_LAYER_TOGGLE_ON)
    {
        if ((EngineA_DISPCNT_LayerMask & layer_mask) != 0)
        {
            return;
        }
    }
    else
    {
        if ((EngineA_DISPCNT_LayerMask & layer_mask) == 0)
        {
            return;
        }
    }

    GX_SetVisiblePlane(EngineA_DISPCNT_LayerMask ^= layer_mask);
}

THUMB_FUNC void GX_SetEngineALayers(u32 layer_mask)
{
    EngineA_DISPCNT_LayerMask = layer_mask;
    GX_SetVisiblePlane(layer_mask);
}

THUMB_FUNC void GX_DisableEngineBLayers()
{
    EngineB_DISPCNT_LayerMask = 0;
}

THUMB_FUNC void GX_EngineBToggleLayers(u32 layer_mask, GX_LayerToggle layer_toggle)
{
    if (layer_toggle == GX_LAYER_TOGGLE_ON)
    {
        if ((EngineB_DISPCNT_LayerMask & layer_mask) != 0)
        {
            return;
        }
    }
    else
    {
        if ((EngineB_DISPCNT_LayerMask & layer_mask) == 0)
        {
            return;
        }
    }

    GXS_SetVisiblePlane(EngineB_DISPCNT_LayerMask ^= layer_mask);
}

THUMB_FUNC void GX_BothDispOn()
{
    GX_DispOn();
    GXS_DispOn();
}

THUMB_FUNC void GX_SwapDisplay()
{
    if (gSystem.screensFlipped == 0)
    {
        GX_SetDispSelect(GX_DISP_SELECT_MAIN_SUB);
    }
    else
    {
        GX_SetDispSelect(GX_DISP_SELECT_SUB_MAIN);
    }
}

THUMB_FUNC u32 GX_GetEngineALayers()
{
    return EngineA_DISPCNT_LayerMask;
}
