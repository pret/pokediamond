#include "gf_gfx_planes.h"

#include "global.h"

#include "GX_vramcnt.h"
#include "gx.h"
#include "main.h"

/* TODO: cleanup this file, it changed a lot in HG, so needs to be reflected here */

static u32 sEngineAPlanes;
static u32 sEngineBPlanes;

void GfGfx_SetBanks(const struct GraphicsBanks *banks) {
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

void GfGfx_DisableEngineAPlanes() {
    sEngineAPlanes = 0;
}

void GfGfx_EngineATogglePlanes(u32 layer_mask, GXPlaneToggle layer_toggle) {
    if (layer_toggle == GX_PLANE_TOGGLE_ON) {
        if ((sEngineAPlanes & layer_mask) != 0) {
            return;
        }
    } else {
        if ((sEngineAPlanes & layer_mask) == 0) {
            return;
        }
    }

    GX_SetVisiblePlane(sEngineAPlanes ^= layer_mask);
}

void GfGfx_EngineASetPlanes(u32 layer_mask) {
    sEngineAPlanes = layer_mask;
    GX_SetVisiblePlane(layer_mask);
}

void GfGfx_DisableEngineBPlanes() {
    sEngineBPlanes = 0;
}

void GfGfx_EngineBTogglePlanes(u32 layer_mask, GXPlaneToggle layer_toggle) {
    if (layer_toggle == GX_PLANE_TOGGLE_ON) {
        if ((sEngineBPlanes & layer_mask) != 0) {
            return;
        }
    } else {
        if ((sEngineBPlanes & layer_mask) == 0) {
            return;
        }
    }

    GXS_SetVisiblePlane(sEngineBPlanes ^= layer_mask);
}

void GfGfx_BothDispOn() {
    GX_DispOn();
    GXS_DispOn();
}

void GfGfx_SwapDisplay() {
    if (gSystem.screensFlipped == 0) {
        GX_SetDispSelect(GX_DISP_SELECT_MAIN_SUB);
    } else {
        GX_SetDispSelect(GX_DISP_SELECT_SUB_MAIN);
    }
}

u32 GfGfx_EngineAGetPlanes() {
    return sEngineAPlanes;
}
