#ifndef GUARD_NNS_G3D_H
#define GUARD_NNS_G3D_H

#include "fx.h"

typedef enum
{
    NNS_G3D_GLB_FLAG_FLUSH_WVP              = 0x00000001,
    NNS_G3D_GLB_FLAG_FLUSH_VP               = 0x00000002,
    NNS_G3D_GLB_FLAG_INVBASE_UPTODATE       = 0x00000004,
    NNS_G3D_GLB_FLAG_INVCAMERA_UPTODATE     = 0x00000008,
    NNS_G3D_GLB_FLAG_INVPROJ_UPTODATE       = 0x00000010,
    NNS_G3D_GLB_FLAG_INVBASECAMERA_UPTODATE = 0x00000020,
    NNS_G3D_GLB_FLAG_INVCAMERAPROJ_UPTODATE = 0x00000040,

    NNS_G3D_GLB_FLAG_BASECAMERA_UPTODATE    = 0x00000080,

    NNS_G3D_GLB_FLAG_SRTCAMERA_UPTODATE     = NNS_G3D_GLB_FLAG_BASECAMERA_UPTODATE,
    NNS_G3D_GLB_FLAG_FLUSH_ALT              = NNS_G3D_GLB_FLAG_FLUSH_WVP
}
    NNSG3dGlbFlag;

typedef struct
{
    /*0x000*/ u32     cmd0;
    /*0x004*/ u32     mtxmode_proj;
    /*0x008*/ MtxFx44 projMtx;

    /*0x048*/ u32     mtxmode_posvec;
    /*0x04C*/ MtxFx43 cameraMtx;

    /*0x07C*/ u32     cmd1;
    /*0x080*/ u32     lightVec[4];

    /*0x090*/ u32     cmd2;
    /*0x094*/ u32     prmMatColor0;
    /*0x098*/ u32     prmMatColor1;
    /*0x09C*/ u32     prmPolygonAttr;
    /*0x0A0*/ u32     prmViewPort;

    /*0x0A4*/ u32     cmd3;
    /*0x0A8*/ u32     lightColor[4];

    /*0x0B8*/ u32     cmd4;
    /*0x0BC*/ MtxFx33 prmBaseRot;
    /*0x0E0*/ VecFx32 prmBaseTrans;
    /*0x0EC*/ VecFx32 prmBaseScale;
    /*0x0F8*/ u32     prmTexImageParam;

    /*0x0FC*/ u32 flag;
    /*0x100*/ MtxFx43 invCameraMtx;
    /*0x130*/ MtxFx43 srtCameraMtx;
    /*0x160*/ MtxFx43 invSrtCameraMtx;

    /*0x190*/ MtxFx43 invBaseMtx;

    /*0x1C0*/ MtxFx44 invProjMtx;
    /*0x200*/ MtxFx44 invCameraProjMtx;

    /*0x240*/ VecFx32 camPos;
    /*0x24C*/ VecFx32 camUp;
    /*0x258*/ VecFx32 camTarget;
}
NNSG3dGlb;

extern NNSG3dGlb NNS_G3dGlb;

static inline void NNS_G3dGlbLookAt(const VecFx32 *camPos, const VecFx32 *camUp, const VecFx32 *camTarget) {
    NNS_G3dGlb.camPos = *camPos;
    NNS_G3dGlb.camUp = *camUp;
    NNS_G3dGlb.camTarget = *camTarget;
    MTX_LookAt(camPos, camUp, camTarget, &NNS_G3dGlb.cameraMtx);
    NNS_G3dGlb.flag &= ~(NNS_G3D_GLB_FLAG_INVCAMERA_UPTODATE | NNS_G3D_GLB_FLAG_INVBASECAMERA_UPTODATE | NNS_G3D_GLB_FLAG_INVCAMERAPROJ_UPTODATE | NNS_G3D_GLB_FLAG_BASECAMERA_UPTODATE);
}

static inline void NNS_G3dGlbPerspective(fx32 fovySin, fx32 fovyCos, fx32 aspect, fx32 n, fx32 f) {
    MTX_Perspective(fovySin, fovyCos, aspect, n, f, &NNS_G3dGlb.projMtx);
    NNS_G3dGlb.flag &= ~(NNS_G3D_GLB_FLAG_INVPROJ_UPTODATE | NNS_G3D_GLB_FLAG_INVCAMERAPROJ_UPTODATE);
}

static inline void NNS_G3dGlbOrtho(fx32 t, fx32 b, fx32 l, fx32 r, fx32 n, fx32 f) {
    MTX_Ortho(t, b, l, r, n, f, &NNS_G3dGlb.projMtx);
    NNS_G3dGlb.flag &= ~(NNS_G3D_GLB_FLAG_INVPROJ_UPTODATE | NNS_G3D_GLB_FLAG_INVCAMERAPROJ_UPTODATE);
}

#endif //GUARD_NNS_G3D_H
