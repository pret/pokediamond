#include "GX_layers.h"
#include "GX_vramcnt.h"
#include "gx.h"
#include "main.h"


struct GX_LayerData layer_data;

THUMB_FUNC void GX_SetBanks(const struct GraphicsBanks *banks)
{
    GX_ResetBankForBG();
    GX_ResetBankForBGExtPltt();
    GX_ResetBankForSubBG();
    FUN_020C6034();
    GX_ResetBankForOBJ();
    GX_ResetBankForOBJExtPltt();
    FUN_020C605C();
    GX_ResetBankForSubOBJ();
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
    layer_data.EngineA_DISPCNT_LayerMask = 0;
}

THUMB_FUNC void GX_EngineAToggleLayers(u32 layer_mask, GX_LayerToggle layer_toggle)
{
    if (layer_toggle == GX_LAYER_TOGGLE_ON)
    {
        if ((layer_data.EngineA_DISPCNT_LayerMask & layer_mask) != 0)
        {
            return;
        }
    }
    else
    {
        if ((layer_data.EngineA_DISPCNT_LayerMask & layer_mask) == 0)
        {
            return;
        }
    }

    reg_GX_DISPCNT = (reg_GX_DISPCNT & 0xFFFFE0FF) | (layer_data.EngineA_DISPCNT_LayerMask ^= layer_mask) << 8;
}

THUMB_FUNC void GX_SetEngineALayers(u32 layer_mask)
{
    layer_data.EngineA_DISPCNT_LayerMask = layer_mask;
    reg_GX_DISPCNT = (reg_GX_DISPCNT & 0xFFFFE0FF) | layer_mask << 8;
}

THUMB_FUNC void GX_DisableEngineBLayers()
{
    layer_data.EngineB_DISPCNT_LayerMask = 0;
}

THUMB_FUNC void GX_EngineBToggleLayers(u32 layer_mask, GX_LayerToggle layer_toggle)
{
    if (layer_toggle == GX_LAYER_TOGGLE_ON)
    {
        if ((layer_data.EngineB_DISPCNT_LayerMask & layer_mask) != 0)
        {
            return;
        }
    }
    else
    {
        if ((layer_data.EngineB_DISPCNT_LayerMask & layer_mask) == 0)
        {
            return;
        }
    }

    reg_GXS_DB_DISPCNT = (reg_GXS_DB_DISPCNT & 0xFFFFE0FF) | (layer_data.EngineB_DISPCNT_LayerMask ^= layer_mask) << 8;
}

THUMB_FUNC void GX_BothDispOn()
{
    GX_DispOn();

    reg_GXS_DB_DISPCNT |= 0x10000;
}

THUMB_FUNC void GX_SwapDisplay()
{
    if (gMain.unk65 == 0)
    {
        reg_GX_POWCNT |= 0x8000; //send display A to lower screen
    }
    else
    {
        reg_GX_POWCNT &= 0xFFFF7FFF; // sned display A to upper screen
    }
}

THUMB_FUNC u32 GX_GetEngineALayers()
{
    return layer_data.EngineA_DISPCNT_LayerMask;
}
