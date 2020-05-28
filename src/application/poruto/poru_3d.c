/**
 *	@file	poru_3d.c
 *	@brief	ポルトデモ　3D関連
 *	@author	Miyuki iwasawa
 *	@date	06.03.28
 */

#include "common.h"
#include "system/procsys.h"
#include "system/clact_tool.h"
#include "system/wordset.h"
#include "system/numfont.h"
#include "system/softsprite.h"
#include "poketool/monsno.h"

#define PORU_DEMO_3D_H_GLOBAL
#include "porudemo.h"
#include "poru_3d.h"

//======================================================
//プロトタイプ
//======================================================
static void PoruDemo_CameraInit(PORU3D_WORK* wk,int heapID);
static void PoruDemo_SoftSpriteInit(PORU3D_WORK* wk,PORUDEMO_POKE* poke,int heapID);

/**
 *	@brief	3D関連初期化
 */
void PoruDemo_3DInit(PORU3D_WORK* wk,PORUDEMO_POKE* poke,int heapID)
{
	MI_CpuClear8(wk,sizeof(PORU3D_WORK));

	NNS_G3dInit();		// NitroSystem:３Ｄエンジンの初期化
	G3X_Init();
	G3X_InitMtxStack();
	G3X_SetShading( GX_SHADING_TOON );
	G3X_AlphaTest( FALSE, 0 );
	G3X_AlphaBlend( TRUE );
	G3X_AntiAlias( TRUE );
	G3X_EdgeMarking( FALSE );
	G3X_SetFog( FALSE, 0, 0, 0 );
	G3X_SetClearColor( 0, 0, 0x7fff, 63, FALSE );
	G3_SwapBuffers( GX_SORTMODE_AUTO, GX_BUFFERMODE_W );
	G3_ViewPort( 0, 0, 255, 191 );

	//カメラ初期化
	PoruDemo_CameraInit(wk,heapID);

	//ソフトウェアスプライト初期化
	PoruDemo_SoftSpriteInit(wk,poke,heapID);
	
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_ON );
    G2_SetBG0Priority(1);
}

/**
 *	@brief	ポルトデモ　3Dメイン
 */
void PoruDemo_3DMain(PORU3D_WORK* wk)
{
	GF_G3X_Reset();
	GFC_CameraLookAt();

	G3_MtxMode( GX_MTXMODE_PROJECTION );
	G3_Identity();
	G3_MtxMode( GX_MTXMODE_POSITION_VECTOR );
	G3_Identity();

	NNS_G3dGlbFlush();
	NNS_G2dSetupSoftwareSpriteCamera();
	SoftSpriteMain( wk->ssm );

	G3_SwapBuffers( GX_SORTMODE_MANUAL, GX_BUFFERMODE_Z );
}

/**
 *	@brief	ポルトデモ　3Dリソース解放
 */
void PoruDemo_3DRelease(PORU3D_WORK* wk)
{
	GFC_FreeCamera(wk->camera);
	SoftSpriteEnd(wk->ssm);
}

/**
 *	@brief	ポルトデモ　カメラ設定
 */
static void PoruDemo_CameraInit(PORU3D_WORK* wk,int heapID)		// カメラ
{
	VecFx32	camera_pos = {0,0,0x10000};
	CAMERA_ANGLE angle = {0,0,0};
	fx32	distance   = 0x10000;
	u16		perspway   = 0x05c1;

	wk->camera = GFC_AllocCamera(heapID);

	GFC_InitCameraCDA(&camera_pos,distance,&angle,perspway,GF_CAMERA_ORTHO,wk->camera);
	GFC_SetCameraClip(0,FX32_CONST(100),wk->camera);
	GFC_PurgeCameraTarget(wk->camera);
	GFC_AttachCamera(wk->camera);	
}

/**
 *	@brief	ソフトウェアスプライト初期化
 */
static void PoruDemo_SoftSpriteInit(PORU3D_WORK* wk,PORUDEMO_POKE* poke,int heapID)
{
	SOFT_SPRITE_ARC	ssa;
	SOFT_SPRITE	* ss;

	wk->ssm = SoftSpriteInit(heapID);
	
	PokeGraArcDataGetPP( &ssa,poke->pp,PARA_FRONT);
	
	ss = SoftSpriteAdd( wk->ssm, &ssa,POKEA_INI_PX,POKEA_INI_PY, 0, 0, NULL, NULL );
	SoftSpriteParaSet( ss, SS_PARA_H_FLIP,poke->flip);
	wk->ss = ss;
}

