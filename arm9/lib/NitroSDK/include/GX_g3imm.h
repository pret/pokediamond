#ifndef GUARD_GX_G3IMM_H
#define GUARD_GX_G3IMM_H

#include "GX_g3.h"
#include "fx.h"

void G3_LoadMtx43(struct Mtx43 *mtx);
void G3_MultMtx43(struct Mtx43 *mtx);
void G3_MultMtx33(struct Mtx33 *mtx);


static inline void G3_PushMtx()
{
    reg_G3_MTX_PUSH = 0;
}

static inline void G3_PopMtx(int num)
{
    reg_G3_MTX_POP = (u32)num;
}

static inline void G3_Identity()
{
    reg_G3_MTX_IDENTITY = 0;
}


static inline void G3_Translate(fx32 x, fx32 y, fx32 z)
{
    reg_G3_MTX_TRANS = (u32)x;
    reg_G3_MTX_TRANS = (u32)y;
    reg_G3_MTX_TRANS = (u32)z;
}


static inline void G3_PolygonAttr(int light, GXPolygonMode polyMode, GXCull cullMode, int polygonID, int alpha, int misc) {
    reg_G3_POLYGON_ATTR = GX_PACK_POLYGONATTR_PARAM(light,
                                                    polyMode, cullMode, polygonID, alpha, misc);
}

static inline void G3_TexImageParam(GXTexFmt texFmt,
                                    GXTexGen texGen,
                                    GXTexSizeS s,
                                    GXTexSizeT t,
                                    GXTexRepeat repeat,
                                    GXTexFlip flip, GXTexPlttColor0 pltt0, u32 addr) {
    reg_G3_TEXIMAGE_PARAM = GX_PACK_TEXIMAGE_PARAM(texFmt, texGen, s, t, repeat, flip, pltt0, addr);
}


static inline void G3_TexPlttBase(u32 addr, GXTexFmt texfmt)
{
    u32     param = GX_PACK_TEXPLTTBASE_PARAM(addr, texfmt);
    reg_G3_TEXPLTT_BASE = param;
}


static inline void G3_MaterialColorDiffAmb(GXRgb diffuse, GXRgb ambient, BOOL IsSetVtxColor)
{
    reg_G3_DIF_AMB = GX_PACK_DIFFAMB_PARAM(diffuse, ambient, IsSetVtxColor);
}

static inline void G3_MaterialColorSpecEmi(GXRgb specular, GXRgb emission, BOOL IsShininess)
{
    reg_G3_SPE_EMI = GX_PACK_SPECEMI_PARAM(specular, emission, IsShininess);
}

#endif  //GUARD_GX_G3IMM_H
