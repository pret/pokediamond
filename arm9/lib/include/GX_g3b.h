#ifndef GUARD_GX_G3B_H
#define GUARD_GX_G3B_H

#include "GX_g3.h"

void G3BS_LoadMtx44(struct GXDLInfo *displaylist, struct Mtx44 *mtx);
void G3B_PushMtx(struct GXDLInfo *displaylist);
void G3B_PopMtx(struct GXDLInfo *displaylist, void *mtx);
void G3B_LoadMtx44(struct GXDLInfo *displaylist, struct Mtx44 *mtx);
void G3B_Color(struct GXDLInfo * displaylist, u32 vtx_col);
void G3B_Normal(struct GXDLInfo * displaylist, fx16 x, fx16 y, fx16 z);
void G3B_Vtx(struct GXDLInfo * displaylist, fx32 x, fx32 y, fx32 z);
void G3B_PolygonAttr(struct GXDLInfo *displaylist, u32 r1, u32 r2, u32 r3, u32 r4, u32 r5, u32 r6);
void G3B_MaterialColorDiffAmb(struct GXDLInfo *displaylist, u32 diffuse_col, u32 ambient_col, u32 replace);
void G3B_MaterialColorSpecEmi(struct GXDLInfo *displaylist, u32 specular_col, u32 emission_col, u32 shiny_table);
void G3B_LightVector(struct GXDLInfo * displaylist, u32 light_num, fx16 x, fx16 y, fx16 z);
void G3B_LightColor(struct GXDLInfo * displaylist, u32 light_num, u32 col);
void G3B_Begin(struct GXDLInfo * displaylist, u32 type);
void G3B_End(struct GXDLInfo * displaylist);

#endif //GUARD_GX_G3B_H
