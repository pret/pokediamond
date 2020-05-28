//============================================================================================
/**
 * @file	ship_demo.c
 * @brief	船デモ
 * @date	2006.05.23
 * @author	Nozomu Saito
 *
 */
//============================================================================================

#include "common.h"
#include "system/procsys.h"
#include "system/arc_util.h"
#include "system/wipe.h"
#include "application/app_tool.h"
#include "system/snd_tool.h"
#include "arc/ship_demo.naix"

#include "ship_demo.h"

#define ANIME_TYPE_NUM	(4)

#define	ANM_ICA	(0)


typedef struct SHIP_DEMO_WORK_tag
{
//	SHIPDEMO_DAT *Dat;				//外部データ
	GF_CAMERA_PTR CameraPtr;//カメラ
	NNSG3dRenderObj			RenderObj;
	NNSG3dResMdl* Model;
	NNSG3dResFileHeader* ResFile;
	void *AnmMem[ANIME_TYPE_NUM];
	NNSFndAllocator AnimeAllocator;
	NNSG3dAnmObj* AnmObj[ANIME_TYPE_NUM];
	VecFx32 Target;	//注視点
	u8 Dir;
	u8 EndFlg;
}SHIP_DEMO_WORK;

typedef struct ARC_TBL_tag
{
	u16 nsbmd;
	u16 anime[ANIME_TYPE_NUM];
}ARC_TBL;

static void InitDisp( void );
static void SetVramBank(void);
static void LoadData(SHIP_DEMO_WORK *wk);

//カメラ設定
static const GF_CAMERA_PARAM CameraData = {
	0x29aec1,
	{
		-0x29fe,0,0
	},
	GF_CAMERA_PERSPECTIV,
	0x05c1,
	0	//dummy
};

//エッジマーキングテーブル
static const GXRgb gEdgeColor[8] = {
    GX_RGB(0, 0, 0),
    GX_RGB(4, 4, 4),
    GX_RGB(4, 4, 4),
    GX_RGB(4, 4, 4),
    GX_RGB(4, 4, 4),
    GX_RGB(4, 4, 4),
    GX_RGB(4, 4, 4),
    GX_RGB(4, 4, 4)
};


//アーカイブインデックステーブル
static ARC_TBL ArcTbl[4] = {
	{
		NARC_ship_demo_c_demo_D_nsbmd,
		{
			NARC_ship_demo_c_demo_D_nsbca,
			NARC_ship_demo_c_demo_D_nsbma,
			NARC_ship_demo_c_demo_D_nsbta,
			NARC_ship_demo_c_demo_D_nsbtp
		}
	},
	{
		NARC_ship_demo_c_demo_L_nsbmd,
		{
			NARC_ship_demo_c_demo_L_nsbca,
			NARC_ship_demo_c_demo_L_nsbma,
			NARC_ship_demo_c_demo_L_nsbta,
			NARC_ship_demo_c_demo_L_nsbtp
		}
	},
	{
		NARC_ship_demo_c_demo_R_nsbmd,
		{
			NARC_ship_demo_c_demo_R_nsbca,
			NARC_ship_demo_c_demo_R_nsbma,
			NARC_ship_demo_c_demo_R_nsbta,
			NARC_ship_demo_c_demo_R_nsbtp
		}
	},
	{
		NARC_ship_demo_c_demo_U_nsbmd,
		{
			NARC_ship_demo_c_demo_U_nsbca,
			NARC_ship_demo_c_demo_U_nsbma,
			NARC_ship_demo_c_demo_U_nsbta,
			NARC_ship_demo_c_demo_U_nsbtp
		}
	}
};

//--------------------------------------------------------------------------------------------
/**
 * プロセス関数：初期化
 *
 * @param	proc	プロセスデータ
 * @param	seq		シーケンス
 *
 * @return	処理状況
 */
//--------------------------------------------------------------------------------------------
PROC_RESULT ShipDemoProc_Init( PROC * proc, int * seq )
{
	u8 i;
	SHIP_DEMO_WORK *wk;
	SHIPDEMO_DAT *dat;
	
	sys_CreateHeap( HEAPID_BASE_APP, HEAPID_SHIPDEMO, 0x20000 );

	wk = PROC_AllocWork( proc, sizeof(SHIP_DEMO_WORK), HEAPID_SHIPDEMO );
	memset( wk, 0, sizeof(SHIP_DEMO_WORK) );
	dat = PROC_GetParentWork( proc );
	
	//進行方向を取得
	wk->Dir = dat->Dir;
	wk->EndFlg = FALSE;
	
	wk->CameraPtr = GFC_AllocCamera(HEAPID_SHIPDEMO);	//カメラ作成
	InitDisp();
		
	//データロード
	LoadData(wk);
	{
		VecFx32 target = {0,0,0};
		//カメラセット
		GFC_InitCameraTDA( &target,
			CameraData.Distance,	// 距離
			&CameraData.Angle,	//
			CameraData.PerspWay,	// 投射影の角度
			CameraData.View,
			FALSE,				//バインドしない
			wk->CameraPtr
			);

		GFC_AttachCamera(wk->CameraPtr);
	}
	for(i=0;i<4;i++){
		//ライトセット
		NNS_G3dGlbLightVector(i,
							dat->LightDataPtr->lightVec[i].x,
							dat->LightDataPtr->lightVec[i].y,
							dat->LightDataPtr->lightVec[i].z);
		NNS_G3dGlbLightColor(i, dat->LightDataPtr->Color[i]);
	}

	//グローバルステート書き換え
	NNS_G3dGlbMaterialColorDiffAmb(
				dat->LightDataPtr->Diff,
				dat->LightDataPtr->Amb,
				dat->LightDataPtr->IsSetVtxColor);
	
	NNS_G3dGlbMaterialColorSpecEmi(
				dat->LightDataPtr->Spec,
				dat->LightDataPtr->Emi,
				dat->LightDataPtr->IsShininess);
	
	// ポリゴンアトリビュート
	NNS_G3dGlbPolygonAttr(
				dat->LightDataPtr->LightFlag,
				dat->LightDataPtr->polyMode,
				dat->LightDataPtr->cullMode,
				dat->LightDataPtr->polygonID,
				dat->LightDataPtr->alpha,
				dat->LightDataPtr->misc);
		
	APP_WipeStart( APP_WIPE_IN, HEAPID_SHIPDEMO );
	return PROC_RES_FINISH;
}

//--------------------------------------------------------------------------------------------
/**
 * プロセス関数：メイン
 *
 * @param	proc	プロセスデータ
 * @param	seq		シーケンス
 *
 * @return	処理状況
 */
//--------------------------------------------------------------------------------------------
PROC_RESULT ShipDemoProc_Main( PROC * proc, int * seq )
{
	u8 i;
	BOOL end_flg;
	MtxFx33 rotate_tmp = {FX32_ONE,0,0,0,FX32_ONE,0,0,0,FX32_ONE};
	VecFx32 scale = {FX32_ONE,FX32_ONE,FX32_ONE};
	VecFx32 trans = {0,0,0};

	SHIP_DEMO_WORK * wk = PROC_GetWork( proc );

	switch(*seq){
	case 0:
		//音開始
		Snd_SePlay( SE_SHIP_RUN );
		(*seq)++;
		break;
	case 1:
		if (!wk->EndFlg){
			//icaアニメ終了を検出
			if (wk->AnmObj[ANM_ICA]->frame+FX32_ONE == NNS_G3dAnmObjGetNumFrame(wk->AnmObj[ANM_ICA])){
				wk->EndFlg = TRUE;
				//ブラックアウトリクエスト
				APP_WipeStart( APP_WIPE_OUT, HEAPID_SHIPDEMO );
			}
		}else{
			//ワイプアウト待ち
			if (WIPE_SYS_EndCheck() ){
				return PROC_RES_FINISH;
			}
		}
	}

	for (i=0;i<ANIME_TYPE_NUM;i++){
		if (wk->AnmObj[i]->frame+FX32_ONE < NNS_G3dAnmObjGetNumFrame(wk->AnmObj[i])){
			//アニメフレーム更新
			wk->AnmObj[i]->frame += (FX32_ONE);
		}
	}
	
	//描画
	GF_G3X_Reset();
	GFC_CameraLookAt();
	simple_3DModelDraw(	&wk->RenderObj,
						&trans,
						&rotate_tmp,
						&scale);
	GF_G3_RequestSwapBuffers(GX_SORTMODE_MANUAL,GX_BUFFERMODE_W);

	return PROC_RES_CONTINUE;

}

//--------------------------------------------------------------------------------------------
/**
 * プロセス関数：終了
 *
 * @param	proc	プロセスデータ
 * @param	seq		シーケンス
 *
 * @return	処理状況
 */
//--------------------------------------------------------------------------------------------
PROC_RESULT ShipDemoProc_End( PROC * proc, int * seq )
{
	u8 i;
	SHIP_DEMO_WORK * wk = PROC_GetWork( proc );
	//アニメ解放
	for(i=0;i<ANIME_TYPE_NUM;i++){
		NNS_G3dFreeAnmObj(	&wk->AnimeAllocator, wk->AnmObj[i]);
		sys_FreeMemoryEz(wk->AnmMem[i]);
	}
	//モデリングデータ解放
	sys_FreeMemoryEz(wk->ResFile);
	//カメラ解放
	GFC_FreeCamera(wk->CameraPtr);
	//ワーク解放
	PROC_FreeWork( proc );
	//3Ｄ関連終了
	simple_3DBGExit();
	//ヒープ解放
	sys_DeleteHeap( HEAPID_SHIPDEMO );
	return PROC_RES_FINISH;
}

//----------------------------------------------------------------------------
/**
 * 画面初期化
 *
 * @return	none
 *
 */
//-----------------------------------------------------------------------------
static void InitDisp( void )
{
	sys_VBlankFuncChange( NULL, NULL );	// VBlankセット
	sys_HBlankIntrStop();				// HBlank停止

	GF_Disp_GX_VisibleControlInit();
	GF_Disp_GXS_VisibleControlInit();
	GX_SetVisiblePlane( 0 );
	GXS_SetVisiblePlane( 0 );

	SetVramBank();				// VRAM設定
	simple_3DBGInit(HEAPID_SHIPDEMO);
	G3X_EdgeMarking( TRUE );
	//エッジマーキングテーブルセット
	G3X_SetEdgeColorTable(gEdgeColor);
	GF_Disp_DispSelect();	//3Ｄ面設定（上にするか、下にするか）
	

}

//===========================================================================
/**
 * 
 * ＶＲＡＭバンク設定
 *
 */
//===========================================================================
static void SetVramBank(void)
{
	GF_BGL_DISPVRAM vramSetTable = {
		GX_VRAM_BG_128_C,				// メイン2DエンジンのBG
		GX_VRAM_BGEXTPLTT_NONE,			// メイン2DエンジンのBG拡張パレット
		GX_VRAM_SUB_BG_32_H,			// サブ2DエンジンのBG
		GX_VRAM_SUB_BGEXTPLTT_NONE,		// サブ2DエンジンのBG拡張パレット
		GX_VRAM_OBJ_16_F,				// メイン2DエンジンのOBJ
		GX_VRAM_OBJEXTPLTT_NONE,		// メイン2DエンジンのOBJ拡張パレット
		GX_VRAM_SUB_OBJ_16_I,			// サブ2DエンジンのOBJ
		GX_VRAM_SUB_OBJEXTPLTT_NONE,	// サブ2DエンジンのOBJ拡張パレット
		GX_VRAM_TEX_01_AB,				// テクスチャイメージスロット
		GX_VRAM_TEXPLTT_0123_E			// テクスチャパレットスロット
	};
	GF_Disp_SetBank( &vramSetTable );
}

//----------------------------------------------------------------------------
/**
 * @brief	船デモデータロード
 *
 * @param	wk		船デモワーク
 *
 * @return	none
 *
 */
//-----------------------------------------------------------------------------
static void LoadData(SHIP_DEMO_WORK *wk)
{
	u8 i;
	NNSG3dResTex *texture;
	void *pAnmRes;
	ARCHANDLE* handle;
	//アーカイブハンドルオープン
	handle = ArchiveDataHandleOpen( ARC_SHIP_DEMO, HEAPID_SHIPDEMO );
	//アニメアロケータ
	sys_InitAllocator(&wk->AnimeAllocator,HEAPID_SHIPDEMO,4);
	
	//モデリングデータをロード
	wk->ResFile = ArchiveDataLoadAllocByHandle( handle, ArcTbl[wk->Dir].nsbmd, HEAPID_SHIPDEMO );
	simple_3DModelSetResFileAlready( &wk->RenderObj, &wk->Model, &wk->ResFile );
	texture = NNS_G3dGetTex(wk->ResFile);	// テクスチャリソース取得
	
	//モデリングデータはグローバルステートを使用する
	NNS_G3dMdlUseGlbDiff(wk->Model);			// ディフューズ
	NNS_G3dMdlUseGlbAmb(wk->Model);				// アンビエント
	NNS_G3dMdlUseGlbSpec(wk->Model);			// スペキュラー
	NNS_G3dMdlUseGlbEmi(wk->Model);				// エミッション	
	
	for(i=0;i<ANIME_TYPE_NUM;i++){
		//アニメーションをロード
		wk->AnmMem[i] = ArchiveDataLoadAllocByHandle( handle, ArcTbl[wk->Dir].anime[i], HEAPID_SHIPDEMO );
		pAnmRes = NNS_G3dGetAnmByIdx(wk->AnmMem[i], 0);
		// 必要量のメモリをアロケートする。
		wk->AnmObj[i] = NNS_G3dAllocAnmObj( &wk->AnimeAllocator, // 使用するアロケータを指定
				                             pAnmRes,    // アニメーションリソースを指定
						                     wk->Model);    // モデルリソースを指定
	
		//イニシャライズ
		NNS_G3dAnmObjInit(wk->AnmObj[i], // アニメーションオブジェクトへのポインタ
		                  pAnmRes, // アニメリソースへのポインタ
			              wk->Model,  // NNSG3dResMdlへのポインタ
				          texture );  // NNSG3dResTexへのポインタ
		//アニメバインド
		NNS_G3dRenderObjAddAnmObj( &wk->RenderObj, wk->AnmObj[i] );
	}
	//ハンドルクローズ
	ArchiveDataHandleClose( handle );
}
