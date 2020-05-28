//============================================================================================
/**
 * @file	pst_3d.c
 * @brief	ポケモンステータス画面3D処理
 * @author	Hiroyuki Nakamura
 * @date	2006.01.24
 */
//============================================================================================
#include "common.h"
#include "system/procsys.h"
#include "system/clact_tool.h"
#include "system/wordset.h"
#include "system/numfont.h"
#include "system/softsprite.h"
#include "poketool/monsno.h"

#define	PST_3D_H_GLOBAL
#include "application/p_status.h"
#include "pst_sys.h"
#include "pst_obj.h"
#include "pst_3d.h"
#include "pst_snd_def.h"


//============================================================================================
//	定数定義
//============================================================================================
#define	POKE_SS_PX	( 52 )		// ポケモン表示X座標
#define	POKE_SS_PY	( 104 )		// ポケモン表示Y座標

/*
	コンディションゲージは４つの四角ポリゴンで表示されている。
	四角ポリゴンの並びは
			２　１
			３　４
	となっている。
	頂点のＩＤは左上を１として時計回り。
*/

// ゲージ１
// 頂点の最大座標
/*
#define	COND_P1_X1_MAX	( 5122 )
#define	COND_P1_Y1_MAX	( 3712 )
#define	COND_P1_X2_MAX	( 8344 )
#define	COND_P1_Y2_MAX	( 965 )
#define	COND_P1_X3_MAX	( 6989 )
#define	COND_P1_Y3_MAX	( -3003 )
#define	COND_P1_X4_MAX	( 5120 )
#define	COND_P1_Y4_MAX	( 128 )
*/
#define	COND_P1_X1_MAX	( 5138 )
#define	COND_P1_Y1_MAX	( 3784 )
//#define	COND_P1_X2_MAX	( 8346 )
//#define	COND_P1_Y2_MAX	( 879 )
#define	COND_P1_X2_MAX	( 8344 )
#define	COND_P1_Y2_MAX	( 965 )
#define	COND_P1_X3_MAX	( 7079 )
#define	COND_P1_Y3_MAX	( -2955 )
#define	COND_P1_X4_MAX	( 5138 )
#define	COND_P1_Y4_MAX	( 300 )
// 頂点の最小座標
#define	COND_P1_X1_MIN	( COND_P1_X1_MAX )
#define	COND_P1_Y1_MIN	( COND_P1_Y4_MAX+(COND_P1_Y1_MAX-COND_P1_Y4_MAX)/8 )
#define	COND_P1_X2_MIN	( COND_P1_X4_MAX+(COND_P1_X2_MAX-COND_P1_X4_MAX)/8 )
#define	COND_P1_Y2_MIN	( COND_P1_Y4_MAX+(COND_P1_Y2_MAX-COND_P1_Y4_MAX)/8 )
#define	COND_P1_X3_MIN	( COND_P1_X4_MAX+(COND_P1_X3_MAX-COND_P1_X4_MAX)/8 )
#define	COND_P1_Y3_MIN	( COND_P1_Y4_MAX+(COND_P1_Y3_MAX-COND_P1_Y4_MAX)/8 )
#define	COND_P1_X4_MIN	( COND_P1_X4_MAX )
#define	COND_P1_Y4_MIN	( COND_P1_Y4_MAX )

// ゲージ２
// 頂点の最大座標
/*
#define	COND_P2_X1_MAX	( 1843 )
#define	COND_P2_Y1_MAX	( 965 )
#define	COND_P2_X2_MAX	( 5120 )
#define	COND_P2_Y2_MAX	( 3712 )
#define	COND_P2_X3_MAX	( 5120 )
#define	COND_P2_Y3_MAX	( 128 )
#define	COND_P2_X4_MAX	( 3200 )
#define	COND_P2_Y4_MAX	( -3003 )
*/
//#define	COND_P2_X1_MAX	( 1748 )
//#define	COND_P2_Y1_MAX	( 879 )
#define	COND_P2_X1_MAX	( 1843 )
#define	COND_P2_Y1_MAX	( 965 )
#define	COND_P2_X2_MAX	( 5045 )
#define	COND_P2_Y2_MAX	( 3784 )
#define	COND_P2_X3_MAX	( 5045 )
#define	COND_P2_Y3_MAX	( 300 )
#define	COND_P2_X4_MAX	( 3106 )
#define	COND_P2_Y4_MAX	( -2955 )
// 頂点の最小座標
#define	COND_P2_X1_MIN	( COND_P2_X3_MAX+(COND_P2_X1_MAX-COND_P2_X3_MAX)/8 )
#define	COND_P2_Y1_MIN	( COND_P2_Y3_MAX+(COND_P2_Y1_MAX-COND_P2_Y3_MAX)/8 )
#define	COND_P2_X2_MIN	( COND_P2_X2_MAX )
#define	COND_P2_Y2_MIN	( COND_P2_Y3_MAX+(COND_P2_Y2_MAX-COND_P2_Y3_MAX)/8 )
#define	COND_P2_X3_MIN	( COND_P2_X3_MAX )
#define	COND_P2_Y3_MIN	( COND_P2_Y3_MAX )
#define	COND_P2_X4_MIN	( COND_P2_X3_MAX+(COND_P2_X4_MAX-COND_P2_X3_MAX)/8 )
#define	COND_P2_Y4_MIN	( COND_P2_Y3_MAX+(COND_P2_Y4_MAX-COND_P2_Y3_MAX)/8 )

// ゲージ３
// 頂点の最大座標
#define	COND_P3_X1_MAX	( COND_P2_X1_MAX )
#define	COND_P3_Y1_MAX	( COND_P2_Y1_MAX )
#define	COND_P3_X2_MAX	( COND_P2_X3_MAX )
#define	COND_P3_Y2_MAX	( COND_P2_Y3_MAX )
#define	COND_P3_X3_MAX	( COND_P1_X3_MAX )
#define	COND_P3_Y3_MAX	( COND_P1_Y3_MAX )
#define	COND_P3_X4_MAX	( COND_P2_X4_MAX )
#define	COND_P3_Y4_MAX	( COND_P2_Y4_MAX )
// 頂点の最小座標
#define	COND_P3_X1_MIN	( COND_P3_X2_MAX+(COND_P3_X1_MAX-COND_P3_X2_MAX)/8 )
#define	COND_P3_Y1_MIN	( COND_P3_Y2_MAX+(COND_P3_Y1_MAX-COND_P3_Y2_MAX)/8 )
#define	COND_P3_X2_MIN	( COND_P3_X2_MAX )
#define	COND_P3_Y2_MIN	( COND_P3_Y2_MAX )
#define	COND_P3_X3_MIN	( COND_P3_X2_MAX+(COND_P3_X3_MAX-COND_P3_X2_MAX)/8 )
#define	COND_P3_Y3_MIN	( COND_P3_Y2_MAX+(COND_P3_Y3_MAX-COND_P3_Y2_MAX)/8 )
#define	COND_P3_X4_MIN	( COND_P3_X2_MAX+(COND_P3_X4_MAX-COND_P3_X2_MAX)/8 )
#define	COND_P3_Y4_MIN	( COND_P3_Y2_MAX+(COND_P3_Y4_MAX-COND_P3_Y2_MAX)/8 )

// ゲージ４
// 頂点の最大座標
#define	COND_P4_X1_MAX	( COND_P1_X4_MAX )
#define	COND_P4_Y1_MAX	( COND_P1_Y4_MAX )
#define	COND_P4_X2_MAX	( COND_P1_X2_MAX )
#define	COND_P4_Y2_MAX	( COND_P1_Y2_MAX )
#define	COND_P4_X3_MAX	( COND_P1_X3_MAX )
#define	COND_P4_Y3_MAX	( COND_P1_Y3_MAX )
#define	COND_P4_X4_MAX	( COND_P2_X4_MAX )
#define	COND_P4_Y4_MAX	( COND_P2_Y4_MAX )
// 頂点の最小座標
#define	COND_P4_X1_MIN	( COND_P4_X1_MAX )
#define	COND_P4_Y1_MIN	( COND_P4_Y1_MAX )
#define	COND_P4_X2_MIN	( COND_P4_X1_MAX+(COND_P4_X2_MAX-COND_P4_X1_MAX)/8 )
#define	COND_P4_Y2_MIN	( COND_P4_Y1_MAX+(COND_P4_Y2_MAX-COND_P4_Y1_MAX)/8 )
#define	COND_P4_X3_MIN	( COND_P4_X1_MAX+(COND_P4_X3_MAX-COND_P4_X1_MAX)/8 )
#define	COND_P4_Y3_MIN	( COND_P4_Y1_MAX+(COND_P4_Y3_MAX-COND_P4_Y1_MAX)/8 )
#define	COND_P4_X4_MIN	( COND_P4_X1_MAX+(COND_P4_X4_MAX-COND_P4_X1_MAX)/8 )
#define	COND_P4_Y4_MIN	( COND_P4_Y1_MAX+(COND_P4_Y4_MAX-COND_P4_Y1_MAX)/8 )

// １パラメータあたりのサイズ計算マクロ
#define	PRM_SIZ(max,min)	( FX_F32_TO_FX16( FX_FX16_TO_F32(max-min)/0xff ) )

// 表示座標計算用パラメータ
typedef struct {
	VecFx16	max;	// 最大座標
	VecFx16	min;	// 最小座標
	VecFx16	siz;	// １あたりのサイズ
}CONDITION_VTX_CALC;


//============================================================================================
//	プロトタイプ宣言
//============================================================================================
static void ConditionGagePut( PST_CONDISION_VTX * vtx );
static void ConditionParamPlus( VecFx16 * p, VecFx16 * m );
static void PokeStatus_ConditionPlus( PST_WORK * wk );
static void ConditionMaxMake( const CONDITION_VTX_CALC * cnst, VecFx16 * make, u8 prm );
static void ConditionMoveMake( VecFx16 * now, VecFx16 * max, VecFx16 * move );


//============================================================================================
//	グローバル変数
//============================================================================================
static const CONDITION_VTX_CALC	ConPrm[][4] =
{
	{	// ゲージ１
		{	// 左上
			{ COND_P1_X1_MAX, COND_P1_Y1_MAX, 0 },
			{ COND_P1_X1_MIN, COND_P1_Y1_MIN, 0 },
			{ PRM_SIZ(COND_P1_X1_MAX,COND_P1_X1_MIN),PRM_SIZ(COND_P1_Y1_MAX,COND_P1_Y1_MIN),0 }
		},
		{	// 右上
			{ COND_P1_X2_MAX, COND_P1_Y2_MAX, 0 },
			{ COND_P1_X2_MIN, COND_P1_Y2_MIN, 0 },
			{ PRM_SIZ(COND_P1_X2_MAX,COND_P1_X2_MIN),PRM_SIZ(COND_P1_Y2_MAX,COND_P1_Y2_MIN),0 }
		},
		{	// 右下
			{ COND_P1_X3_MAX, COND_P1_Y3_MAX, 0 },
			{ COND_P1_X3_MIN, COND_P1_Y3_MIN, 0 },
			{ PRM_SIZ(COND_P1_X3_MAX,COND_P1_X3_MIN),PRM_SIZ(COND_P1_Y3_MAX,COND_P1_Y3_MIN),0 }
		},
		{	// 左下
			{ COND_P1_X4_MAX, COND_P1_Y4_MAX, 0 },
			{ COND_P1_X4_MIN, COND_P1_Y4_MIN, 0 },
			{ PRM_SIZ(COND_P1_X4_MAX,COND_P1_X4_MIN),PRM_SIZ(COND_P1_Y4_MAX,COND_P1_Y4_MIN),0 }
		}
	},
	{	// ゲージ２
		{	// 左上
			{ COND_P2_X1_MAX, COND_P2_Y1_MAX, 0 },
			{ COND_P2_X1_MIN, COND_P2_Y1_MIN, 0 },
			{ PRM_SIZ(COND_P2_X1_MAX,COND_P2_X1_MIN),PRM_SIZ(COND_P2_Y1_MAX,COND_P2_Y1_MIN),0 }
		},
		{	// 右上
			{ COND_P2_X2_MAX, COND_P2_Y2_MAX, 0 },
			{ COND_P2_X2_MIN, COND_P2_Y2_MIN, 0 },
			{ PRM_SIZ(COND_P2_X2_MAX,COND_P2_X2_MIN),PRM_SIZ(COND_P2_Y2_MAX,COND_P2_Y2_MIN),0 }
		},
		{	// 右下
			{ COND_P2_X3_MAX, COND_P2_Y3_MAX, 0 },
			{ COND_P2_X3_MIN, COND_P2_Y3_MIN, 0 },
			{ PRM_SIZ(COND_P2_X3_MAX,COND_P2_X3_MIN),PRM_SIZ(COND_P2_Y3_MAX,COND_P2_Y3_MIN),0 }
		},
		{	// 左下
			{ COND_P2_X4_MAX, COND_P2_Y4_MAX, 0 },
			{ COND_P2_X4_MIN, COND_P2_Y4_MIN, 0 },
			{ PRM_SIZ(COND_P2_X4_MAX,COND_P2_X4_MIN),PRM_SIZ(COND_P2_Y4_MAX,COND_P2_Y4_MIN),0 }
		}
	},
	{	// ゲージ３
		{	// 左上
			{ COND_P3_X1_MAX, COND_P3_Y1_MAX, 0 },
			{ COND_P3_X1_MIN, COND_P3_Y1_MIN, 0 },
			{ PRM_SIZ(COND_P3_X1_MAX,COND_P3_X1_MIN),PRM_SIZ(COND_P3_Y1_MAX,COND_P3_Y1_MIN),0 }
		},
		{	// 右上
			{ COND_P3_X2_MAX, COND_P3_Y2_MAX, 0 },
			{ COND_P3_X2_MIN, COND_P3_Y2_MIN, 0 },
			{ PRM_SIZ(COND_P3_X2_MAX,COND_P3_X2_MIN),PRM_SIZ(COND_P3_Y2_MAX,COND_P3_Y2_MIN),0 }
		},
		{	// 右下
			{ COND_P3_X3_MAX, COND_P3_Y3_MAX, 0 },
			{ COND_P3_X3_MIN, COND_P3_Y3_MIN, 0 },
			{ PRM_SIZ(COND_P3_X3_MAX,COND_P3_X3_MIN),PRM_SIZ(COND_P3_Y3_MAX,COND_P3_Y3_MIN),0 }
		},
		{	// 左下
			{ COND_P3_X4_MAX, COND_P3_Y4_MAX, 0 },
			{ COND_P3_X4_MIN, COND_P3_Y4_MIN, 0 },
			{ PRM_SIZ(COND_P3_X4_MAX,COND_P3_X4_MIN),PRM_SIZ(COND_P3_Y4_MAX,COND_P3_Y4_MIN),0 }
		}
	},
	{	// ゲージ４
		{	// 左上
			{ COND_P4_X1_MAX, COND_P4_Y1_MAX, 0 },
			{ COND_P4_X1_MIN, COND_P4_Y1_MIN, 0 },
			{ PRM_SIZ(COND_P4_X1_MAX,COND_P4_X1_MIN),PRM_SIZ(COND_P4_Y1_MAX,COND_P4_Y1_MIN),0 }
		},
		{	// 右上
			{ COND_P4_X2_MAX, COND_P4_Y2_MAX, 0 },
			{ COND_P4_X2_MIN, COND_P4_Y2_MIN, 0 },
			{ PRM_SIZ(COND_P4_X2_MAX,COND_P4_X2_MIN),PRM_SIZ(COND_P4_Y2_MAX,COND_P4_Y2_MIN),0 }
		},
		{	// 右下
			{ COND_P4_X3_MAX, COND_P4_Y3_MAX, 0 },
			{ COND_P4_X3_MIN, COND_P4_Y3_MIN, 0 },
			{ PRM_SIZ(COND_P4_X3_MAX,COND_P4_X3_MIN),PRM_SIZ(COND_P4_Y3_MAX,COND_P4_Y3_MIN),0 }
		},
		{	// 左下
			{ COND_P4_X4_MAX, COND_P4_Y4_MAX, 0 },
			{ COND_P4_X4_MIN, COND_P4_Y4_MIN, 0 },
			{ PRM_SIZ(COND_P4_X4_MAX,COND_P4_X4_MIN),PRM_SIZ(COND_P4_Y4_MAX,COND_P4_Y4_MIN),0 }
		}
	}
};



//--------------------------------------------------------------------------------------------
/**
 * 3D関連初期化
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void PokeStatus_3DInit( PST_WORK * wk )
{
	// 初期化（NITRO-SDKのサンプルから）
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
	G3_SwapBuffers( GX_SORTMODE_AUTO, GX_BUFFERMODE_Z );
	G3_ViewPort( 0, 0, 255, 191 );

	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_ON );
    G2_SetBG0Priority( 2 );
}

//--------------------------------------------------------------------------------------------
/**
 * 3D関連メイン
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void PokeStatus_3DMain( PST_WORK * wk )
{
	if( wk->page == PST_PAGE_CONDITION ){
		GF_G3X_Reset();
		GFC_CameraLookAt();

		G3_MtxMode( GX_MTXMODE_PROJECTION );
		G3_Identity();
		G3_MtxMode( GX_MTXMODE_POSITION_VECTOR );
		G3_Identity();

		NNS_G3dGlbFlush();
		ConditionGagePut( wk->cvtx );
		NNS_G3dGlbFlush();

		PokeStatus_ConditionPlus( wk );
	}

	NNS_G2dSetupSoftwareSpriteCamera();
	SoftSpriteMain( wk->p3d.ssm );

	G3_SwapBuffers( GX_SORTMODE_MANUAL, GX_BUFFERMODE_Z );
}

//--------------------------------------------------------------------------------------------
/**
 * 3D関連削除
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void PokeStatus_3DRelease( PST_WORK * wk )
{
	GFC_FreeCamera( wk->p3d.camera );	// カメラ削除
	PokeAnm_EndAnimeForce( wk->p3d.poke_anm_sys, 0 );
	PokeAnm_FreeMemory( wk->p3d.poke_anm_sys );
	SoftSpriteEnd( wk->p3d.ssm );	// ソフトウェアスプライト削除
}


//============================================================================================
//	コンディション
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * カメラ設定
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void PokeStatus_CameraInit( PST_WORK * wk )
{
	VecFx32	camera_pos = {0,0,0x10000};
	CAMERA_ANGLE angle = {0,0,0};
	fx32	distance   = 0x10000;
	u16		perspway   = 0x05c1;

	wk->p3d.camera = GFC_AllocCamera( HEAPID_POKESTATUS );

	GFC_InitCameraCDA( &camera_pos, distance, &angle, perspway, GF_CAMERA_ORTHO, wk->p3d.camera );
	GFC_SetCameraClip( 0, FX32_CONST(100), wk->p3d.camera );	// クリップ設定(near-far)
	GFC_PurgeCameraTarget( wk->p3d.camera );
	GFC_AttachCamera( wk->p3d.camera );
}

//--------------------------------------------------------------------------------------------
/**
 * コンディションゲージ表示
 *
 * @param	vtx		ポリゴン表示座標
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
//static u8 d_vtx_flg;
//static u8 d_vtx_pos;
static void ConditionGagePut( PST_CONDISION_VTX * vtx )
{
	G3_PolygonAttr(
		GX_LIGHTMASK_NONE,			// no lights
		GX_POLYGONMODE_MODULATE,	// modulation mode
		GX_CULL_NONE,				// cull none
		18,							// polygon ID(0 - 63)
		20,							// alpha(0 - 31)
		0 );						// OR of GXPolygonAttrMisc's value

    G3_Begin( GX_BEGIN_QUADS );
    {
		u32	i;

		for( i=0; i<4; i++ ){
			G3_Color( GX_RGB(8,31,15) );
			G3_Vtx( vtx[i].lt.x, vtx[i].lt.y, vtx[i].lt.z );
			G3_Color( GX_RGB(8,31,15) );
			G3_Vtx( vtx[i].rt.x, vtx[i].rt.y, vtx[i].rt.z );
			G3_Color( GX_RGB(8,31,15) );
			G3_Vtx( vtx[i].ru.x, vtx[i].ru.y, vtx[i].ru.z );
			G3_Color( GX_RGB(8,31,15) );
			G3_Vtx( vtx[i].lu.x, vtx[i].lu.y, vtx[i].lu.z );
		}
	}
    G3_End();

/*
	G3_PolygonAttr(
		GX_LIGHTMASK_NONE,			// no lights
		GX_POLYGONMODE_MODULATE,	// modulation mode
		GX_CULL_NONE,				// cull none
		18,							// polygon ID(0 - 63)
		20,							// alpha(0 - 31)
		0 );						// OR of GXPolygonAttrMisc's value

	if( sys.trg & PAD_BUTTON_SELECT ){
		d_vtx_flg = (d_vtx_flg+1)&3;
		OS_Printf( "VTX ID : %d\n", d_vtx_flg );
		return;
	}

	if( sys.trg & PAD_BUTTON_A ){
		d_vtx_pos = (d_vtx_pos+1)&3;
		OS_Printf( "POL ID : %d\n", d_vtx_pos );
		return;
	}

	if( sys.trg & PAD_BUTTON_START ){
		OS_Printf( "LT : x = %d, y = %d, z = %d\n", vtx[d_vtx_pos].lt.x, vtx[d_vtx_pos].lt.y, vtx[d_vtx_pos].lt.z );
		OS_Printf( "RT : x = %d, y = %d, z = %d\n", vtx[d_vtx_pos].rt.x, vtx[d_vtx_pos].rt.y, vtx[d_vtx_pos].rt.z );
		OS_Printf( "RU : x = %d, y = %d, z = %d\n", vtx[d_vtx_pos].ru.x, vtx[d_vtx_pos].ru.y, vtx[d_vtx_pos].ru.z );
		OS_Printf( "LU : x = %d, y = %d, z = %d\n", vtx[d_vtx_pos].lu.x, vtx[d_vtx_pos].lu.y, vtx[d_vtx_pos].lu.z );
		d_vtx_flg = (d_vtx_flg+1)&3;
		return;
	}

	if( sys.cont & PAD_BUTTON_L ){
		if( d_vtx_flg == 0 ){
			vtx[d_vtx_pos].lt.x -= 1;
		}else if( d_vtx_flg == 1 ){
			vtx[d_vtx_pos].rt.x -= 1;
		}else if( d_vtx_flg == 2 ){
			vtx[d_vtx_pos].ru.x -= 1;
		}else if( d_vtx_flg == 3 ){
			vtx[d_vtx_pos].lu.x -= 1;
		}
		return;
	}

	if( sys.cont & PAD_BUTTON_R ){
		if( d_vtx_flg == 0 ){
			vtx[d_vtx_pos].lt.x += 1;
		}else if( d_vtx_flg == 1 ){
			vtx[d_vtx_pos].rt.x += 1;
		}else if( d_vtx_flg == 2 ){
			vtx[d_vtx_pos].ru.x += 1;
		}else if( d_vtx_flg == 3 ){
			vtx[d_vtx_pos].lu.x += 1;
		}
		return;
	}

	if( sys.cont & PAD_BUTTON_X ){
		if( d_vtx_flg == 0 ){
			vtx[d_vtx_pos].lt.y -= 1;
		}else if( d_vtx_flg == 1 ){
			vtx[d_vtx_pos].rt.y -= 1;
		}else if( d_vtx_flg == 2 ){
			vtx[d_vtx_pos].ru.y -= 1;
		}else if( d_vtx_flg == 3 ){
			vtx[d_vtx_pos].lu.y -= 1;
		}
		return;
	}

	if( sys.cont & PAD_BUTTON_Y ){
		if( d_vtx_flg == 0 ){
			vtx[d_vtx_pos].lt.y += 1;
		}else if( d_vtx_flg == 1 ){
			vtx[d_vtx_pos].rt.y += 1;
		}else if( d_vtx_flg == 2 ){
			vtx[d_vtx_pos].ru.y += 1;
		}else if( d_vtx_flg == 3 ){
			vtx[d_vtx_pos].lu.y += 1;
		}
		return;
	}

    G3_Begin( GX_BEGIN_QUADS );
    {
		u32	i;

		for( i=d_vtx_pos; i<d_vtx_pos+1; i++ ){
			if( d_vtx_flg == 0 ){
				G3_Color( GX_RGB(0,0,0) );
			}else{
				G3_Color( GX_RGB(8,31,15) );
			}
			G3_Vtx( vtx[i].lt.x, vtx[i].lt.y, vtx[i].lt.z );
			if( d_vtx_flg == 1 ){
				G3_Color( GX_RGB(0,0,0) );
			}else{
				G3_Color( GX_RGB(8,31,15) );
			}
			G3_Vtx( vtx[i].rt.x, vtx[i].rt.y, vtx[i].rt.z );
			if( d_vtx_flg == 2 ){
				G3_Color( GX_RGB(0,0,0) );
			}else{
				G3_Color( GX_RGB(8,31,15) );
			}
			G3_Vtx( vtx[i].ru.x, vtx[i].ru.y, vtx[i].ru.z );
			if( d_vtx_flg == 3 ){
				G3_Color( GX_RGB(0,0,0) );
			}else{
				G3_Color( GX_RGB(8,31,15) );
			}
			G3_Vtx( vtx[i].lu.x, vtx[i].lu.y, vtx[i].lu.z );
		}
	}
    G3_End();
*/

}

//--------------------------------------------------------------------------------------------
/**
 * 表示座標変更
 *
 * @param	p		表示座標
 * @param	m		変更値
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void ConditionParamPlus( VecFx16 * p, VecFx16 * m )
{
	p->x += m->x;
	p->y += m->y;
	p->z += m->z;
}

//--------------------------------------------------------------------------------------------
/**
 * コンディションゲージ動作
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void PokeStatus_ConditionPlus( PST_WORK * wk )
{
	u32	i;

	if( wk->con_mv_cnt == 4 ){
		PokeStatus_ConditionFlashAnm( wk );
		return;
	}

	if( wk->con_mv_cnt == 3 ){
		for( i=0; i<4; i++ ){
			wk->cvtx[i] = wk->mvtx[i];
		}
	}else{
		for( i=0; i<4; i++ ){
			ConditionParamPlus( &wk->cvtx[i].lt, &wk->pvtx[i].lt );
			ConditionParamPlus( &wk->cvtx[i].rt, &wk->pvtx[i].rt );
			ConditionParamPlus( &wk->cvtx[i].lu, &wk->pvtx[i].lu );
			ConditionParamPlus( &wk->cvtx[i].ru, &wk->pvtx[i].ru );
		}
	}

	wk->con_mv_cnt++;

	if( wk->con_mv_cnt == 4 ){
		PokeStatus_ConditionFlash( wk, 1 );
	}else{
		PokeStatus_ConditionFlash( wk, 0 );
	}
}

//--------------------------------------------------------------------------------------------
/**
 * コンディションゲージ初期化
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void PokeStatus_ConditionParamInit( PST_WORK * wk )
{
	u32	i;

	if( wk->page != PST_PAGE_CONDITION ){ return; }

	wk->cvtx[0].lt = ConPrm[0][3].min;
	wk->cvtx[0].rt = ConPrm[0][3].min;
	wk->cvtx[0].lu = ConPrm[0][3].min;
	wk->cvtx[0].ru = ConPrm[0][3].min;

	wk->cvtx[1].lt = ConPrm[1][2].min;
	wk->cvtx[1].rt = ConPrm[1][2].min;
	wk->cvtx[1].lu = ConPrm[1][2].min;
	wk->cvtx[1].ru = ConPrm[1][2].min;

	wk->cvtx[2].lt = ConPrm[2][1].min;
	wk->cvtx[2].rt = ConPrm[2][1].min;
	wk->cvtx[2].lu = ConPrm[2][1].min;
	wk->cvtx[2].ru = ConPrm[2][1].min;

	wk->cvtx[3].lt = ConPrm[3][0].min;
	wk->cvtx[3].rt = ConPrm[3][0].min;
	wk->cvtx[3].lu = ConPrm[3][0].min;
	wk->cvtx[3].ru = ConPrm[3][0].min;

	PokeStatus_ConditionParamMake( wk );
}

//--------------------------------------------------------------------------------------------
/**
 * コンディションゲージ最大値セット
 *
 * @param	cnst	座標データ
 * @param	make	作成場所
 * @param	prm		パラメー
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void ConditionMaxMake( const CONDITION_VTX_CALC * cnst, VecFx16 * make, u8 prm )
{
	if( prm == 0xff ){
		*make = cnst->max;
	}else if( prm == 0 ){
		*make = cnst->min;
	}else{
		make->x = cnst->min.x + cnst->siz.x * prm;
		make->y = cnst->min.y + cnst->siz.y * prm;
		make->z = cnst->min.z + cnst->siz.z * prm;
	}
}

//--------------------------------------------------------------------------------------------
/**
 * コンディションゲージ動作値セット
 *
 * @param	now		現在の座標
 * @param	max		最大座標
 * @param	move	１あたりの動作値
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void ConditionMoveMake( VecFx16 * now, VecFx16 * max, VecFx16 * move )
{
	move->x = FX_F32_TO_FX16( FX_FX16_TO_F32(max->x-now->x)/4 );
	move->y = FX_F32_TO_FX16( FX_FX16_TO_F32(max->y-now->y)/4 );
	move->z = FX_F32_TO_FX16( FX_FX16_TO_F32(max->z-now->z)/4 );
}

//--------------------------------------------------------------------------------------------
/**
 * コンディションゲージ動作パラメータ作成
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void PokeStatus_ConditionParamMake( PST_WORK * wk )
{
	u32	i;

	// 最大値をセット
	ConditionMaxMake( &ConPrm[0][0], &wk->mvtx[0].lt, wk->pp.style );
	ConditionMaxMake( &ConPrm[0][1], &wk->mvtx[0].rt, wk->pp.beautiful );
	ConditionMaxMake( &ConPrm[0][2], &wk->mvtx[0].ru, wk->pp.cute );
	ConditionMaxMake( &ConPrm[0][3], &wk->mvtx[0].lu, 0 );

	ConditionMaxMake( &ConPrm[1][0], &wk->mvtx[1].lt, wk->pp.strong );
	ConditionMaxMake( &ConPrm[1][1], &wk->mvtx[1].rt, wk->pp.style );
	ConditionMaxMake( &ConPrm[1][2], &wk->mvtx[1].ru, 0 );
	ConditionMaxMake( &ConPrm[1][3], &wk->mvtx[1].lu, wk->pp.clever );

	ConditionMaxMake( &ConPrm[2][0], &wk->mvtx[2].lt, wk->pp.strong );
	ConditionMaxMake( &ConPrm[2][1], &wk->mvtx[2].rt, 0 );
	ConditionMaxMake( &ConPrm[2][2], &wk->mvtx[2].ru, wk->pp.cute );
	ConditionMaxMake( &ConPrm[2][3], &wk->mvtx[2].lu, wk->pp.clever );

	ConditionMaxMake( &ConPrm[3][0], &wk->mvtx[3].lt, 0 );
	ConditionMaxMake( &ConPrm[3][1], &wk->mvtx[3].rt, wk->pp.beautiful );
	ConditionMaxMake( &ConPrm[3][2], &wk->mvtx[3].ru, wk->pp.cute );
	ConditionMaxMake( &ConPrm[3][3], &wk->mvtx[3].lu, wk->pp.clever );

	// プラス値を計算
	for( i=0; i<4; i++ ){
		ConditionMoveMake( &wk->cvtx[i].lt, &wk->mvtx[i].lt, &wk->pvtx[i].lt );
		ConditionMoveMake( &wk->cvtx[i].rt, &wk->mvtx[i].rt, &wk->pvtx[i].rt );
		ConditionMoveMake( &wk->cvtx[i].lu, &wk->mvtx[i].lu, &wk->pvtx[i].lu );
		ConditionMoveMake( &wk->cvtx[i].ru, &wk->mvtx[i].ru, &wk->pvtx[i].ru );
	}

	wk->con_mv_cnt = 0;
}


//============================================================================================
//	ソフトウェアスプライト
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * ソフトウェアスプライトセット
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void PokeStatus_SoftSpriteSet( PST_WORK * wk )
{
	SOFT_SPRITE_ARC	ssa;
	void * pp;

	wk->p3d.ssm = SoftSpriteInit( HEAPID_POKESTATUS );

	pp = PokeStatusPokeParamGet( wk );

	if( wk->dat->ppt == PST_PP_TYPE_POKEPASO ){
		PokeGraArcDataGetPPP( &ssa, pp, PARA_FRONT );
	}else{
		PokeGraArcDataGetPP( &ssa, pp, PARA_FRONT );
	}


	PokeAnmDataSet( wk->p3d.ssanm, wk->pp.mons );

	wk->p3d.flip = PokePersonalParaGet( wk->pp.mons, ID_PER_reverse ) ^ 1;
	wk->p3d.ss = SoftSpriteAdd( wk->p3d.ssm, &ssa, POKE_SS_PX, POKE_SS_PY, 0, 0, wk->p3d.ssanm, NULL );

	SoftSpriteParaSet( wk->p3d.ss, SS_PARA_H_FLIP, wk->p3d.flip );
//	SoftSpriteAnimeSet( wk->p3d.ss, 1 );

//	PokePrgAnmDataSet( wk->p3d.poke_anm_sys, wk->p3d.ss, wk->pp.mons, PARA_FRONT, 0, (wk->p3d.flip^1), 0 );
}

void PokeStatus_SoftSpriteAnmSet( PST_WORK * wk )
{
//	PokeAnmDataSet( wk->p3d.ssanm, wk->pp.mons );
	if( wk->pp.tamago != 0 ){
//		SoftSpriteAnimeSet( wk->p3d.ss, 0 );
		PokePrgAnmDataSet( wk->p3d.poke_anm_sys, wk->p3d.ss, 0, PARA_FRONT, 0, wk->p3d.flip, 0 );
	}else{
		SoftSpriteAnimeSet( wk->p3d.ss, 1 );
		PokePrgAnmDataSet(
			wk->p3d.poke_anm_sys, wk->p3d.ss, wk->pp.mons, PARA_FRONT, 0, wk->p3d.flip, 0 );
	}
}


//--------------------------------------------------------------------------------------------
/**
 * ソフトウェアスプライト再セット
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void PokeStatus_SoftSpriteReset( PST_WORK * wk )
{
	PokeAnm_EndAnimeForce( wk->p3d.poke_anm_sys, 0 );

	SoftSpriteEnd( wk->p3d.ssm );	// ソフトウェアスプライト削除
	PokeStatus_SoftSpriteSet( wk );
	PokeStatus_SoftSpriteAnmSet( wk );
}
