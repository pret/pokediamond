//============================================================================================
/**
 * @file	sdkdef.h
 * @bfief	Nitro SDK で定義されている様々な定数をさらに使いやすく
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#ifndef __SDKDEF_H__
#define __SDKDEF_H__

//---------------------------------------------------------------------------
/**
 * BLEND Plane Mask( <nitro/gx/g2.h> で定義されている定数を拡張）
 */
//---------------------------------------------------------------------------
enum {
	GX_BLEND_BGALL = GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_BG3,
	GX_BLEND_ALL = GX_BLEND_BGALL | GX_BLEND_PLANEMASK_OBJ | GX_BLEND_PLANEMASK_BD,
};

//---------------------------------------------------------------------------
/**
 * WINDOW Plane Mask( <nitro/gx/g2.h> で定義されている定数を拡張）
 */
//---------------------------------------------------------------------------
enum {
	GX_WND_PLANEMASK_BGALL = GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_BG1 | GX_WND_PLANEMASK_BG2 | GX_WND_PLANEMASK_BG3,
	GX_WND_PLANEMASK_ALL = GX_WND_PLANEMASK_BGALL | GX_WND_PLANEMASK_OBJ,
};

#endif
