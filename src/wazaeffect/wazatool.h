//==============================================================================
/**
 * @file	wazatool.h
 * @brief	技エフェクト関連の汎用ツールのヘッダ
 * @author	matsuda
 * @date	2005.09.02(金)
 */
//==============================================================================
#ifndef __WAZATOOL_H__
#define __WAZATOOL_H__

#include "we_sys.h"
#include "system/clact_tool.h"
#include "system/laster.h"



//==============================================================================
//	定数定義
//==============================================================================
//--------------------------------------------------------------
//	ヒープ設定
//--------------------------------------------------------------
///技エフェクト動作関数で通常使用するヒープ領域
#define WAZAEFF_HEAP_AREA		(HEAPID_BATTLE)	//(APP_W_HEAP_AREA)

///GetWazaEffPos関数用
enum{
	PM_X,		///<ポケモン個々の中心座標X
	PM_Y,		///<ポケモン個々の中心座標Y
	EFF_X,		///<ポケモンのオフセット関係なしのエフェクト固定中心座標X
	EFF_Y,		///<ポケモンのオフセット関係なしのエフェクト固定中心座標Y
};

///技エフェクトでの一応基準とするアクターソフトウェアプライオリティ
#define WAZAEFF_ACT_SOFTPRI		(100)

///技エフェクトでの一応基準とするアクターBGプライオリティ
#define WAZAEFF_ACT_BGPRI		(1)

//--------------------------------------------------------------
//	旧技エフェクトソースからの引継ぎ(今回も必要かは現時点では不明)
//--------------------------------------------------------------
#define MINE_SIDE_OFFSET_Y	8	//自分側の座標が高いので強制的にｵﾌｾｯﾄで下にずらす

// -----------------------------------------
//
//	オフセット用の定数
//
// -----------------------------------------
enum EOFS_MODE {
	
	WAZAEFF_OFS_MODE_BOTTOM = 0,			///< 下部
	WAZAEFF_OFS_MODE_TOP,					///< 上部

};

//--------------------------------------------------------------
//	残像用定数
//--------------------------------------------------------------
//残像計算データなどの配列参照用
enum{
	WAZATOOL_ZANZOU_0,			// 残像１
	WAZATOOL_ZANZOU_1,			// 残像２
	WAZATOOL_ZANZOU_2,			// 残像３
	WAZATOOL_ZANZOU_3,			// 残像４
	WAZATOOL_ZANZOU_MAX,		// 残像のマックス
};

// 残像反映タイプ
enum{
	WAZATOOL_ZANZOU_TYPE_MATRIX,	// タイプ	座標
	WAZATOOL_ZANZOU_TYPE_SCALE,		// タイプ	拡大縮小
};

//==============================================================================
//	構造体定義
//==============================================================================
///旧アクターを移植しやすいように、
///旧アクターのワーク構成 ＋ 移植を行いやすいようにいくつかワークをプラスしたもの
typedef struct{
	WE_SYS_PTR we_sys;
	CATS_SYS_PTR csp;
	CLACT_WORK_PTR act;
	TCB_PTR tcb;
	
	TCB_FUNC move;		///<TCB動作関数
	TCB_FUNC next_move;	///<SetWorkSeqで関数ポインタを汎用ワークにセットしていたのはここに保存
	s16 x;				///<旧アクターでは座標を直でいじっていたが今回はそれが出来ないので、
	s16 y;				///<こちらに座標をコピーしていじることを想定
	s16 dx;
	s16 dy;
	s16 work[8];		///<アクター個々が持っていた汎用ワーク
}OLDACT_WORK;

//-------------------------------------
//	
//	汎用動作計算用構造体
//	
//	座標計算
//	拡縮計算
//=====================================
typedef struct{
	s16 x;				// ｘ計算結果
	s16 y;				// ｙ計算結果
	s32 work[8];		// 動作ワーク
} WAZATOOL_CALCMOVE;
//==============================================================================
//	型定義
//==============================================================================
// 汎用計算の関数ポインタ型
typedef BOOL (*WAZATOOL_CALCFUNC)( WAZATOOL_CALCMOVE* p_wtc );


//-------------------------------------
//	
//	汎用動作計算用構造体
//	等差計算
//	
//	回転などに使用できます。
//=====================================
typedef struct{
	s32 num;
	s32 work[4];
} WAZATOOL_CALCMOVE_ONE;

//-------------------------------------
//	
//	残像動作システム
//	
//=====================================
typedef struct{
	// 動作データ
	s16	x;	// デフォルト位置
	s16 y;	// デフォルト位置　
	WAZATOOL_CALCMOVE	move_param[ WAZATOOL_ZANZOU_MAX ];
	WAZATOOL_CALCFUNC	move_func;
	// 残像データ
	CATS_ACT_PTR cap[ WAZATOOL_ZANZOU_MAX ];

	u16 wait;		// 各オブジェクトを動かすタイミング
	u16 count;		// 動作タイミングカウンタ
	u8 zanzou_num;	// 残像数
	u8 zanzou_move;	// 今動作している残像の数
	u8 type;		// 座標に反映させるか拡縮に反映させるか
	u8 dummy;
} WAZATOOL_ZANZOU;




//==============================================================================
//	外部関数宣言
//==============================================================================
extern void *WazaTool_AllocClearMemory(int heap_area, u32 size);
extern s16 GetWazaEffPos(WE_SYS_PTR we_sys, int client_no, int get_pos);
extern u32 GetPokeSoftPri(u8 client_no);
extern OLDACT_WORK* OldAct_Init(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, 
	CLACT_WORK_PTR act, TCB_FUNC func);
extern void OldAct_ParamUpdate(OLDACT_WORK *oldact);
extern void OldAct_Delete(OLDACT_WORK *oldact);
extern void OldAct_SetWorkSeq(OLDACT_WORK *oldact, TCB_FUNC func);
extern void OldAct_SetMoveSeq(OLDACT_WORK *oldact);

extern void WazaEffPosGet_Type(int fight_type, int type, s16* x, s16* y);
extern void WazaEffPosGet_ClientType(WE_SYS_PTR wsp, int client_no, s16*x, s16* y);
//-------------------------------------
//	
//	CATS_ACT_PTRのパレットNO取得関数
//	
//=====================================
extern u8 WazaTool_CapPlttNoGet( CATS_ACT_PTR cap );

//-------------------------------------
//	
//	Hブランク関数設定をパックした関数
//
//	後々拡張するとこもあるかも知れないため作成
//	
//=====================================
enum{	// 戻り値
	WAZATOOL_HBLANK_FALSE,
	WAZATOOL_HBLANK_TRUE,
};
extern int WazaTool_HBlankSet( INTR_FUNC func, void * work );




//-------------------------------------
//	●エフェクト方向チェンジ
//	　横と縦のベクトル方向を返します。
//	　戻り値を掛けることで、その方向のベクトルになります。
//	　
//	　回転方向を変える時はWazaTool_VecChangeXを
//	　使ってください。
//=====================================
extern int WazaTool_VecChangeX( WE_SYS_PTR we_sys, int client_no );
extern int WazaTool_VecChangeY( WE_SYS_PTR we_sys, int client_no );

//-------------------------------------
//	汎用計算関数
//=====================================
//等差や距離から必要なシンクすうを取得する
//等差計算
extern fx32 WazaTool_GetDiff( fx32 a, fx32 an, u32 n );
extern u32 WazaTool_GetDiffSync( fx32 a, fx32 an, fx32 diff );


// オブジェクトに値を設定する関数
extern void WazaTool_SetCapMatrix( WAZATOOL_CALCMOVE* p_wtc, CATS_ACT_PTR cap, s16 c_x, s16 c_y );
extern void WazaTool_SetCapScale( WAZATOOL_CALCMOVE* p_wtc, CATS_ACT_PTR cap );
extern void WazaTool_SetSspMatrix( WAZATOOL_CALCMOVE* p_wtc, SOFT_SPRITE* ssp, s16 c_x, s16 c_y );
extern void WazaTool_SetSspScale( WAZATOOL_CALCMOVE* p_wtc, SOFT_SPRITE* ssp );

//WAZATOOL_CALCMOVE構造体用関数郡
//
//回転動作
extern void WazaTool_InitRotaFx( WAZATOOL_CALCMOVE* p_wtc, u16 r_sx, u16 r_ex, u16 r_sy, u16 r_ey, fx32 wx, fx32 wy, int sync );
extern void WazaTool_InitRotaSpeedFx( WAZATOOL_CALCMOVE* p_wtc, u16 r_sx, u16 r_ex, u16 r_sy, u16 r_ey, fx32 wx, fx32 wy, u16 speed_x );
extern BOOL WazaTool_CalcRotaFx( WAZATOOL_CALCMOVE* p_wtc );
extern BOOL WazaTool_CalcAndReflectRotaFxCap( WAZATOOL_CALCMOVE* p_wtc, s16 c_x, s16 c_y, CATS_ACT_PTR cap );
extern BOOL WazaTool_CalcAndReflectRotaFxSsp( WAZATOOL_CALCMOVE* p_wtc, s16 c_x, s16 c_y, SOFT_SPRITE* ssp );

//平行移動
//定数計算
extern void WazaTool_InitStraightSpeed( WAZATOOL_CALCMOVE* p_wtc, s16 sx, s16 ex, s16 sy, s16 ey, u16 speed_x  );
extern void WazaTool_InitStraightSync( WAZATOOL_CALCMOVE* p_wtc, s16 sx, s16 ex, s16 sy, s16 ey, u16 sync  );
extern BOOL WazaTool_CalcStraight( WAZATOOL_CALCMOVE* p_wtc );
//固定少数計算
extern void WazaTool_InitStraightSpeedFx( WAZATOOL_CALCMOVE* p_wtc, s16 sx, s16 ex, s16 sy, s16 ey, u16 speed_x  );
extern void WazaTool_InitStraightSyncFx( WAZATOOL_CALCMOVE* p_wtc, s16 sx, s16 ex, s16 sy, s16 ey, u16 sync );
extern BOOL WazaTool_CalcStraightFx( WAZATOOL_CALCMOVE* p_wtc );
extern BOOL WazaTool_CalcAndReflectStraightFxCap( WAZATOOL_CALCMOVE* p_wtc, CATS_ACT_PTR cap );
extern BOOL WazaTool_CalcAndReflectStraightFxSsp( WAZATOOL_CALCMOVE* p_wtc, SOFT_SPRITE* ssp );

//カーブ動作
extern void WazaTool_InitCurveYFx( WAZATOOL_CALCMOVE* p_wtc_st, WAZATOOL_CALCMOVE* p_wtc_rt, s16 sx, s16 ex, s16 sy, s16 ey, u16 sync, fx32 width );
extern void WazaTool_InitCurveXFx( WAZATOOL_CALCMOVE* p_wtc_st, WAZATOOL_CALCMOVE* p_wtc_rt, s16 sx, s16 ex, s16 sy, s16 ey, u16 sync, fx32 width );
extern BOOL WazaTool_CalcCurveFx( WAZATOOL_CALCMOVE* p_wtc_st, WAZATOOL_CALCMOVE* p_wtc_rt );
extern BOOL WazaTool_CalcAndReflectCurveFxCap( WAZATOOL_CALCMOVE* p_wtc_st, WAZATOOL_CALCMOVE* p_wtc_rt, CATS_ACT_PTR cap );
extern BOOL WazaTool_CalcAndReflectCurveFxSsp( WAZATOOL_CALCMOVE* p_wtc_st, WAZATOOL_CALCMOVE* p_wtc_rt, SOFT_SPRITE* ssp );

//WAZATOOL_CALCMOVE_ONE構造体用関数郡
//実数
extern void WazaTool_InitMoveOneSync( WAZATOOL_CALCMOVE_ONE* p_wtc, s32 a, s32 an, u32 sync );
extern void WazaTool_InitMoveOneSpeed( WAZATOOL_CALCMOVE_ONE* p_wtc, s32 a, s32 an, s16 speed );
extern BOOL WazaTool_CalcMoveOne( WAZATOOL_CALCMOVE_ONE* p_wtc );
//固定少数
extern void WazaTool_InitMoveOneSyncFx( WAZATOOL_CALCMOVE_ONE* p_wtc, s16 a, s16 an, u32 sync );
extern void WazaTool_InitMoveOneSpeedFx( WAZATOOL_CALCMOVE_ONE* p_wtc, s16 a, s16 an, fx32 speed );
extern BOOL WazaTool_CalcMoveOneFx( WAZATOOL_CALCMOVE_ONE* p_wtc );
//sin波cos波
extern void WazaTool_InitSinCosOneSyncFx( WAZATOOL_CALCMOVE_ONE* p_wtc, u16 s_r, u16 e_r, fx32 w, u32 sync );
extern BOOL WazaTool_CalcSinOne( WAZATOOL_CALCMOVE_ONE* p_wtc );
extern BOOL WazaTool_CalcCosOne( WAZATOOL_CALCMOVE_ONE* p_wtc );

// 拡縮
extern void WazaTool_InitScaleRate(WAZATOOL_CALCMOVE* p_wtc, s16 ss, s16 ds, s16 es, u32 sync);
extern BOOL WazaTool_CalcScaleRate(WAZATOOL_CALCMOVE* p_wtc);
extern void WazaTool_InitScaleRateEx(WAZATOOL_CALCMOVE* p_wtc, s16 sx, s16 ex, s16 sy, s16 ey, s16 ds, u32 sync);
extern BOOL WazaTool_CalcScaleRateEx(WAZATOOL_CALCMOVE* p_wtc);
extern void WazaTool_CalcScaleRateToClactScale(WAZATOOL_CALCMOVE* p_wtc, f32* x, f32* y);
extern s16	WazaTool_CalcScaleRateToYPos(s16 def_y, int poke_h, u32 sy);
extern s16	WazaTool_CalcScaleRateToYPosFX(s16 def_y, int poke_h, fx32 sy);
extern void WazaTool_PokeOffsetSet(SOFT_SPRITE* ssp, s16 def_y, s16 poke_height, fx32 scale, int mode);
extern void WazaTool_PokeOffsetSetOAM(CATS_ACT_PTR cap, s16 def_y, s16 poke_height, fx32 scale, int mode);
extern BOOL WazaTool_CalcAndReflectScaleRateCap( WAZATOOL_CALCMOVE* p_wtc, CATS_ACT_PTR cap );
extern BOOL WazaTool_CalcAndReflectScaleRateSsp( WAZATOOL_CALCMOVE* p_wtc, SOFT_SPRITE* ssp );
extern BOOL WazaTool_CalcAndReflectScaleRateExCap( WAZATOOL_CALCMOVE* p_wtc, CATS_ACT_PTR cap );
extern BOOL WazaTool_CalcAndReflectScaleRateExSsp( WAZATOOL_CALCMOVE* p_wtc, SOFT_SPRITE* ssp );

// 揺らし(簡易)
extern void WazaTool_InitShake(WAZATOOL_CALCMOVE* p_wtc, s16 x, s16 y, u32 sync, u32 num);
extern BOOL WazaTool_CalcShake(WAZATOOL_CALCMOVE* p_wtc);
extern BOOL WazaTool_CalcAndReflectShakeCap( WAZATOOL_CALCMOVE* p_wtc, s16 c_x, s16 c_y, CATS_ACT_PTR cap );
extern BOOL WazaTool_CalcAndReflectShakeSsp( WAZATOOL_CALCMOVE* p_wtc, s16 c_x, s16 c_y, SOFT_SPRITE* ssp );

// 残像動作
extern void WazaTool_InitZanzou( WAZATOOL_ZANZOU* p_wtz, WAZATOOL_CALCMOVE* p_wtc, WAZATOOL_CALCFUNC p_func, s16 x, s16 y, u16 wait, u8 zanzou_num, u8 type, CATS_ACT_PTR cap_00, CATS_ACT_PTR cap_01, CATS_ACT_PTR cap_02, CATS_ACT_PTR cap_03 );
extern void WazaTool_ChangeMoveZanzou( WAZATOOL_ZANZOU* p_wtz, WAZATOOL_CALCMOVE* p_wtc, WAZATOOL_CALCFUNC p_func );
extern BOOL WazaTool_CalcZanzou( WAZATOOL_ZANZOU* p_wtz );

//-------------------------------------
//	
//	汎用的に使える動作ワークを
//	作成する関数郡
//
//	回転移動などは共通の動作をすることが多いため作成
//	
//=====================================
extern void WazaTool_MakeDefRota( WAZATOOL_CALCMOVE* p_wtc, int rota_num, int rota_one_sync );
#define WAZATOOL_DEF_ROTA_W_X	(32 * FX32_ONE)	// 回転横幅
#define WAZATOOL_DEF_ROTA_W_Y	(-8 * FX32_ONE)	// 回転縦幅
// FXをintに変更したときの値
#define WAZATOOL_DEF_ROTA_W_X_INT	(32)	// 回転横幅
#define WAZATOOL_DEF_ROTA_W_Y_INT	(-8)	// 回転縦幅

//-------------------------------------
//	
//	alphaフェードタスク
//	
//=====================================
typedef struct _WAZATOOL_ALPHA_FADE{
	WAZATOOL_CALCMOVE wtc;
	int	end_flag;
} WAZATOOL_ALPHA_FADE;
extern void WazaTool_StartAlphaFade( WAZATOOL_ALPHA_FADE* p_alfd, s16 sev1, s16 eev1, s16 sev2, s16 eev2, int sync );
extern BOOL WazaTool_EndCheckAlphaFade( const WAZATOOL_ALPHA_FADE* p_alfd );

//-------------------------------------
//	
//	デフォルトラスターシステム
//
//	３０分の１フレームVar
//
//	このシステムがやること
//		初期化処理		をまとめて行う
//		破棄処理		をまとめて行う
//		VBlank期間処理	をまとめて行う
//
//	使う人がやること
//		バッファへの値の設定
//	
//=====================================
#define WAZATOOL_DEFLASTER_BUFF_SIZE	(192)
typedef struct _WAZATOOL_DEFLASTER*			WAZATOOL_DEFLASTER_PTR;
typedef const struct _WAZATOOL_DEFLASTER*	CONST_WAZATOOL_DEFLASTER_PTR;

extern WAZATOOL_DEFLASTER_PTR WazaTool_InitDefLaster( u32 addr, u32 init_num, int heap );
extern void WazaTool_DeleteDefLaster( WAZATOOL_DEFLASTER_PTR p_lst );
extern void* WazaTool_GetDefLasterWriteBuff( CONST_WAZATOOL_DEFLASTER_PTR cp_lst );
extern const void* WazaTool_GetDefLasterReadBuff( CONST_WAZATOOL_DEFLASTER_PTR cp_lst );
extern void WazaTool_StopDefLaster( WAZATOOL_DEFLASTER_PTR p_lst );
extern void WazaTool_StartDefLaster( WAZATOOL_DEFLASTER_PTR p_lst );
extern void WazaTool_SetDefLasterTransAddr( WAZATOOL_DEFLASTER_PTR p_lst, u32 addr );
extern u32	WazaTool_GetDefLasterTransAddr( WAZATOOL_DEFLASTER_PTR p_lst );

//-------------------------------------
//	
//	1/30フレーム対応
//	
// ラスタースクロールラップ関数
// SINカーブスクロールさせます
//	
//=====================================
typedef struct _WAZATOOL_SCRLASTER*			WAZATOOL_SCRLASTER_PTR;
typedef const struct _WAZATOOL_SCRLASTER*	CONST_WAZATOOL_SCRLASTER_PTR;

extern WAZATOOL_SCRLASTER_PTR WazaTool_InitScrLaster( u8 start, u8 end, u16 add_r, fx32 r_w, s16 scr_sp, u32 bg_no, u32 tsk_pri, u32 init_num, int heap );
extern void WazaTool_DeleteScrLaster( WAZATOOL_SCRLASTER_PTR p_lst );
extern void* WazaTool_GetScrLasterWriteBuff( CONST_WAZATOOL_SCRLASTER_PTR cp_lst );
extern const void* WazaTool_GetScrLasterReadBuff( CONST_WAZATOOL_SCRLASTER_PTR cp_lst );
extern void WazaTool_StopScrLaster( WAZATOOL_SCRLASTER_PTR p_lst );
extern void WazaTool_StartScrLaster( WAZATOOL_SCRLASTER_PTR p_lst );


// ここからはラスターを使用するときに汎用的に使用できるもの
extern u32 WazaTool_GetLasterBuffMatrixData( u16 x, u16 y );
extern u32 WazaTool_GetLasterBGDestAddr( int bg_no );

extern void WazaTool_SetEffectBGPriority( WE_SYS_PTR we_sys, int pri );


// -----------------------------------------
//
//	■ ツールとか
//
// -----------------------------------------
extern void WazaTool_MiddlePointGet(s16 px1, s16 py1, s16 px2, s16 py2, s16* mx, s16* my);
extern void WazaTool_MiddlePointGetFx(s16 px1, s16 py1, s16 px2, s16 py2, fx32* mx, fx32* my);
extern void WazaTool_RangeGetFx(s16 x1, s16 y1, s16 x2, s16 y2, fx32* range);
extern void WazaTool_PointToPointAngleGet(s16 x1, s16 y1, s16 x2, s16 y2, u16* angle);
extern BOOL WazaTool_ParamCalc(int* p, int ep, s32 cp);


// -----------------------------------------
//
//	■ 複数のカラーフェード操作
//
// -----------------------------------------

// -----------------------------------------
//
//	ソフトフェード操作構造体ポインタ
//
// -----------------------------------------
typedef struct _TPAL_SOFT_FADE_SYS * PAL_SFS_PTR;

extern BOOL IsPaletteSoftFade(PAL_SFS_PTR psp);
extern void PaletteSoftFadeDelete(PAL_SFS_PTR psp);
extern PAL_SFS_PTR PaletteSoftFade(PALETTE_FADE_PTR pfd, int heap_area, FADEREQ req,
								   u16 start_pos, u16 col_num, s8 wait, s8 param, 
								   u8 start_evy, u8 end_evy, u16 next_rgb, int tcb_pri);

#define RGBtoY(r,g,b)	(((r)*76 + (g)*151 + (b)*29) >> 8)
extern void WeTool_PalGrayScale(WE_SYS_PTR wsp);
extern void WeTool_PalNormal(WE_SYS_PTR wsp);

#endif	//__WAZATOOL_H__

