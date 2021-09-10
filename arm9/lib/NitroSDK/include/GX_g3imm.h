#ifndef GUARD_GX_G3IMM_H
#define GUARD_GX_G3IMM_H

#include "GX_g3.h"
#include "fx.h"

void G3_LoadMtx43(struct Mtx43 *mtx);
void G3_MultMtx43(struct Mtx43 *mtx);
void G3_MultMtx33(struct Mtx33 *mtx);

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


#endif  //GUARD_GX_G3IMM_H
