//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		wsp_tomoya.c
 *	@brief		tomoya の作成した技エフェクト
 *	@author		tomoya takahashi
 *	@data		2005.12.15
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
// -----------------------------------------
//
//	include
//
// -----------------------------------------
#include "common.h"				///< 必須
#include "system/lib_pack.h"	///< 必須
#include "we_def.h"
#include "west_sp.h"			///< 必須
#include "wsp_sample.h"			///< xxx.cに対するxxx.hは必須
#include "wsp.h"			///< xxx.cに対するxxx.hは必須

#include "wazatool.h"			///< 技エフェクト支援関数郡
#include "we_tool.h"			///< 

#include "ball_effect.h"
#include "system/arc_tool.h"				///< アーカイブ用
#include "system/arc_util.h"				///< アーカイブ用
#include "system/brightness.h"				///< ブライトネス
#include "system/wipe.h"

//-------------------------------------
//	
//	でんこうせっか
//	
//=====================================
#define WE098_OAM_MAX	(2)
#define WE098_ROTA_NUM	(1)		// 回転数
#define WE098_SYNC		(8)		// シンク数
#define WE098_SYNC_ZAN	(10)	// 残像のシンク数
#define WE098_DO_WAIT	(2)		// 残像実行待ち
#define WE098_ALPHA_OAM	(26)	// OAMに掛けるα値
#define WE098_ALPHA_BG	(5)		// BGに掛けるα値
typedef struct{

	WE_SYS_PTR		we_sys;
	CATS_RES_PTR	crp;
	
	SOFT_SPRITE*		at_ssp;		// 攻撃ポケモン
	WAZATOOL_CALCMOVE	at_wtc;		// ポケモン動作データ
	CATS_ACT_PTR		at_cap[ WE098_OAM_MAX ];	// 残像OAMのアクターデータ
	WAZATOOL_ZANZOU		at_wtz;		// 残像動作データ
	s16					at_pos_x;	// ポケモンデフォルト座標
	s16					at_pos_y;	// ポケモンデフォルト座標
	s16					cap_ofs_y;	// OAMオフセットY

/*
	SOFT_SPRITE*		df_ssp;		// 守備ポケモン
	WAZATOOL_CALCMOVE	df_wtc;		// ポケモン動作データ
	s16					df_pos_x;	// ポケモンデフォルト座標
	s16					df_pos_y;	// ポケモンデフォルト座標
*/
} TWE_098_SYS;


//----------------------------------------------------------------------------
/**
 *	@brief	でんこうせっか	動作TCB
 *
 *	@param	tcb		TCBワーク
 *	@param	work	でんこうせっか動作ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void We098_TCB(TCB_PTR tcb, void* work)
{
	TWE_098_SYS* wk = work;
	BOOL check[3];
	int i;		// ループ用


	// 動作が完全に終わるまで待って終了
	// 動作部
	check[0] = WazaTool_CalcAndReflectRotaFxSsp( &wk->at_wtc, wk->at_pos_x, wk->at_pos_y, wk->at_ssp );
	check[1] = WazaTool_CalcZanzou( &wk->at_wtz );
//	check[2] = WazaTool_CalcAndReflectShakeSsp( &wk->df_wtc, wk->df_pos_x, wk->df_pos_y, wk->df_ssp );
	check[2] = FALSE;

	// 残像OAM描画
	CATS_Draw(wk->crp);	

	// 終了チェック部
	for( i=0; i<3; i++ ){
		// 計算途中があるかチェック
		if( check[i] == TRUE ){
			// 続行
			return ;
		}
	}

	// 元座標を設定
	SoftSpriteParaSet( wk->at_ssp, SS_PARA_POS_X, wk->at_pos_x );
	SoftSpriteParaSet( wk->at_ssp, SS_PARA_POS_Y, wk->at_pos_y + (WAZATOOL_DEF_ROTA_W_Y >> FX32_SHIFT) );
//	SoftSpriteParaSet( wk->df_ssp, SS_PARA_POS_X, wk->df_pos_x );
//	SoftSpriteParaSet( wk->df_ssp, SS_PARA_POS_Y, wk->df_pos_y );


	// 終了
	WEEffect_TCB_Delete(wk->we_sys, tcb);
	sys_FreeMemoryEz(wk);
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	でんこうせっかの実行
 *
 *	@param	we_sys	技エフェクトシステムワーク
 *
 *	@return	none
 *
 * poke_oamにポケモンの絵をドロップしておく必要があります　WE098_OAM_MAX
 *
 * we_sysから受け取る引数なし
 *
 * OBJ	背景、３ｄ面のアルファブレンディングを行います。
 *
 */
//-----------------------------------------------------------------------------
void WestSp_WE_098( WE_SYS_PTR we_sys )
{
	TWE_098_SYS* wk;
	int i;		// ループ用
	int vec_x;
	WAZATOOL_CALCMOVE	at_zan_wtc;	// 残像ポケモン動作データ
	
	wk = sys_AllocMemory(WeSysHeapAreaGet(we_sys), sizeof(TWE_098_SYS));

	wk->we_sys	= we_sys;
	wk->crp		= WeSysPokeCrpGet(wk->we_sys);
	
	// ポケモン　ソフトウェアスプライトデータ取得
	wk->at_ssp = WeSysSoftSpritePointerGet( wk->we_sys, WeSysATNoGet(wk->we_sys) );
	wk->at_pos_x = SoftSpriteParaGet( wk->at_ssp, SS_PARA_POS_X );
	wk->at_pos_y = SoftSpriteParaGet( wk->at_ssp, SS_PARA_POS_Y );
	wk->cap_ofs_y = SoftSpriteParaGet( wk->at_ssp, SS_PARA_SHADOW_HEIGHT );

/*	wk->df_ssp = WeSysSoftSpritePointerGet( wk->we_sys, WeSysDFNoGet(wk->we_sys) );
	wk->df_pos_x = SoftSpriteParaGet( wk->df_ssp, SS_PARA_POS_X );
	wk->df_pos_y = SoftSpriteParaGet( wk->df_ssp, SS_PARA_POS_Y );//*/
	// 座標を回転のY幅分上に補正
	wk->at_pos_y -= WAZATOOL_DEF_ROTA_W_Y >> FX32_SHIFT;

	// ポケモン　動作データ作成
	WazaTool_MakeDefRota( 
			&wk->at_wtc,
			WE098_ROTA_NUM, WE098_SYNC );

/*	WazaTool_InitShake( &wk->df_wtc,
			WE098_SHAKE_W_X,
			0,
			WE098_SHAKE_SYNC / WE098_SHAKE_NUM,
			WE098_SHAKE_NUM );//*/

	// 残像動作データ作成
	WazaTool_MakeDefRota(
			&at_zan_wtc,
			WE098_ROTA_NUM, WE098_SYNC_ZAN );

	// ベクトルをあわせる
	// 攻撃側
	vec_x = WazaTool_VecChangeX( wk->we_sys, WeSysATNoGet(wk->we_sys) );
	wk->at_wtc.work[2] *= vec_x;
	at_zan_wtc.work[2] *= vec_x;
	
	// 防御側
//	vec_x = WazaTool_VecChangeX( wk->we_sys, WeSysDFNoGet(wk->we_sys) );
//	wk->df_wtc.x *= vec_x;

	// 残像データ取得
	for( i=0; i<WE098_OAM_MAX; i++ ){
		wk->at_cap[ i ] = WeSysPokeCapGet(wk->we_sys, i);
		CATS_ObjectPriSetCap( wk->at_cap[ i ], WAZAEFF_ACT_SOFTPRI );
		CATS_ObjectBGPriSetCap( wk->at_cap[ i ], WAZAEFF_ACT_BGPRI );
		CATS_ObjectObjModeSetCap(wk->at_cap[i], GX_OAM_MODE_XLU);
	}

	WazaTool_InitZanzou( &wk->at_wtz, &at_zan_wtc, WazaTool_CalcRotaFx,
			wk->at_pos_x, wk->at_pos_y - wk->cap_ofs_y,
			WE098_DO_WAIT,WE098_OAM_MAX, WAZATOOL_ZANZOU_TYPE_MATRIX, 
			wk->at_cap[0], wk->at_cap[1], NULL, NULL );


	// 残像の色を設定
	// アルファを掛ける
	WET_DefaultBlendSet(wk->we_sys, WET_DEFAULT_BLEND, WET_DEFAULT_BLEND);
	
	
	WEEffect_TCB_AddPriSet(wk->we_sys, We098_TCB, wk);
}


//-------------------------------------
//	
//	ドリルくちばし
//	
//=====================================
enum{
	WE065_AT_MOVE1,
	WE065_AT_ROTA1,
	WE065_AT_WAIT,
	WE065_AT_MOVE2,
	WE065_DF_MOVE,
	WE065_AT_ROTA2,
	WE065_END,
};
#define WE065_MOVE_WIDTH	(-32)
#define WE065_MOVE_SYNC		(3)
#define WE065_MOVE2_SYNC	(2)
#define WE065_SHAKE_WAIT	( 32 )
#define WE065_ROTA_DIS		(20)
#define WE065_ROTA1_SYNC	(8)
#define WE065_ROTA2_SYNC	(4)
#define WE065_MOVE_WAIT		(2)
typedef struct{

	WE_SYS_PTR		we_sys;
	
	int						seq;		// シーケンス
	s16						wait;		// ウェイト
	SOFT_SPRITE*			at_ssp;		// 攻撃ポケモン
	WAZATOOL_CALCMOVE		at_wtc;		// ポケモン動作データ
	WAZATOOL_CALCMOVE_ONE	at_wtc_r;	// ポケモン動作データ回転
	s16						at_pos_x;	// ポケモンデフォルト座標
	s16						at_pos_y;	// ポケモンデフォルト座標

/*	
	SOFT_SPRITE*		df_ssp;		// 守備ポケモン
	WAZATOOL_CALCMOVE	df_wtc;		// ポケモン動作データ
	s16					df_pos_x;	// ポケモンデフォルト座標
	s16					df_pos_y;	// ポケモンデフォルト座標
*/
} TWE_065_SYS;

//----------------------------------------------------------------------------
/**
 *	@brief	ドリルくちばし	動作TCB
 *
 *	@param	tcb		TCBワーク
 *	@param	work	ドリルくちばし動作ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void We065_TCB(TCB_PTR tcb, void* work)
{
	TWE_065_SYS* wk = work;
	
	switch( wk->seq ){
	case WE065_AT_MOVE1:
		if( WazaTool_CalcStraightFx( &wk->at_wtc ) ){
			WazaTool_SetSspMatrix( &wk->at_wtc, wk->at_ssp, wk->at_pos_x, wk->at_pos_y );
		}else{
			WazaTool_InitStraightSyncFx( &wk->at_wtc, wk->at_wtc.x, 0, 0, 0, WE065_MOVE2_SYNC );
			wk->seq ++;
		}
		break;

	case WE065_AT_ROTA1:
		if( WazaTool_CalcMoveOne( &wk->at_wtc_r ) ){
			SoftSpriteParaSet( wk->at_ssp, SS_PARA_ROT_Z, wk->at_wtc_r.num );
		}else{
			WazaTool_InitMoveOneSync( &wk->at_wtc_r, wk->at_wtc_r.num, 0, WE065_ROTA2_SYNC );
			wk->seq ++;
			wk->wait = WE065_MOVE_WAIT;
		}
		break;

	case WE065_AT_WAIT:
		wk->wait --;
		if( wk->wait < 0 ){
			wk->seq++;
		}
		break;

	case WE065_AT_MOVE2:
		if( WazaTool_CalcStraightFx( &wk->at_wtc ) ){
			WazaTool_SetSspMatrix( &wk->at_wtc, wk->at_ssp, wk->at_pos_x, wk->at_pos_y );
		}else{
			wk->seq ++;
			wk->wait = WE065_SHAKE_WAIT;
		}
		break;
		
	case WE065_DF_MOVE:
/*		if( WazaTool_CalcAndReflectShakeSsp( &wk->df_wtc, wk->df_pos_x, wk->df_pos_y, wk->df_ssp ) == FALSE ){
			wk->seq ++;
		}//*/

		wk->wait --;
		if( wk->wait < 0 ){
			wk->seq++;
		}
		break;
		
	case WE065_AT_ROTA2:
		if( WazaTool_CalcMoveOne( &wk->at_wtc_r ) ){
			SoftSpriteParaSet( wk->at_ssp, SS_PARA_ROT_Z, wk->at_wtc_r.num );
		}else{
			wk->seq ++;
		}
		break;

	case WE065_END:			// 終了
		// 元座標を設定
		SoftSpriteParaSet( wk->at_ssp, SS_PARA_POS_X, wk->at_pos_x );
		SoftSpriteParaSet( wk->at_ssp, SS_PARA_POS_Y, wk->at_pos_y );

		SoftSpriteParaSet( wk->at_ssp, SS_PARA_ROT_Z, 0 );
/*		SoftSpriteParaSet( wk->df_ssp, SS_PARA_POS_X, wk->df_pos_x );
		SoftSpriteParaSet( wk->df_ssp, SS_PARA_POS_Y, wk->df_pos_y );//*/

		// 終了
		WEEffect_TCB_Delete(wk->we_sys, tcb);
		sys_FreeMemoryEz(wk);
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ドリルくちばしの実行
 *
 *	@param	we_sys	技エフェクトシステムワーク
 *
 *	@return	none
 *
 * we_sysから受け取る引数なし
 *
 */
//-----------------------------------------------------------------------------
void WestSp_WE_065( WE_SYS_PTR we_sys )
{
	TWE_065_SYS* wk;
	int i;		// ループ用
	int vec_x;
	int vec_x_df;
	
	
	wk = sys_AllocMemory(WeSysHeapAreaGet(we_sys), sizeof(TWE_098_SYS));

	wk->we_sys	= we_sys;
	wk->seq = 0;	

	// ポケモン　ソフトウェアスプライトデータ取得
	wk->at_ssp = WeSysSoftSpritePointerGet( wk->we_sys, WeSysATNoGet(wk->we_sys) );
	wk->at_pos_x = SoftSpriteParaGet( wk->at_ssp, SS_PARA_POS_X );
	wk->at_pos_y = SoftSpriteParaGet( wk->at_ssp, SS_PARA_POS_Y );

/*	wk->df_ssp = WeSysSoftSpritePointerGet( wk->we_sys, WeSysDFNoGet(wk->we_sys) );
	wk->df_pos_x = SoftSpriteParaGet( wk->df_ssp, SS_PARA_POS_X );
	wk->df_pos_y = SoftSpriteParaGet( wk->df_ssp, SS_PARA_POS_Y );//*/

	// ポケモン　動作データ作成
	WazaTool_InitStraightSyncFx( &wk->at_wtc, 0, WE065_MOVE_WIDTH, 0, 0, WE065_MOVE_SYNC );
	WazaTool_InitMoveOneSync( &wk->at_wtc_r, 0, FX_GET_ROTA_NUM(WE065_ROTA_DIS), WE065_ROTA1_SYNC );
	
//	WazaTool_InitShake( &wk->df_wtc, WE065_SHAKE_WIDTH, 0, WE065_SHAKE_SYNC, WE065_SHAKE_NUM );
	

	// ベクトルをあわせる
	// 攻撃側
	vec_x = WazaTool_VecChangeX( wk->we_sys, WeSysATNoGet(wk->we_sys) );
	wk->at_wtc.work[1] *= vec_x;
	wk->at_wtc_r.work[1] *= vec_x;

/*	// 防御側
	wk->df_wtc.x *= vec_x;//*/

	vec_x_df = WazaTool_VecChangeX( wk->we_sys, WeSysDFNoGet(wk->we_sys) );

	// 攻撃回転位置設定
	{
		int ats = WET_SideCheck(we_sys, WeSysATNoGet(wk->we_sys));
		int dfs = WET_SideCheck(we_sys, WeSysDFNoGet(wk->we_sys));
		
		if (ats == SIDE_MINE &&	dfs == SIDE_MINE){
			SoftSpriteParaSet( wk->at_ssp, SS_PARA_ROT_CX, (SOFT_SPRITE_SIZE_X / 2) * -1);
			SoftSpriteParaSet( wk->at_ssp, SS_PARA_ROT_CY, SOFT_SPRITE_SIZE_Y / 2 );
		}
		else if (ats == SIDE_ENEMY && dfs == SIDE_ENEMY){
			SoftSpriteParaSet( wk->at_ssp, SS_PARA_ROT_CX, (SOFT_SPRITE_SIZE_X / 2) * +1);
			SoftSpriteParaSet( wk->at_ssp, SS_PARA_ROT_CY, SOFT_SPRITE_SIZE_Y / 2 );
		}
		else {		
			SoftSpriteParaSet( wk->at_ssp, SS_PARA_ROT_CX, (SOFT_SPRITE_SIZE_X / 2) * vec_x_df);
			SoftSpriteParaSet( wk->at_ssp, SS_PARA_ROT_CY, SOFT_SPRITE_SIZE_Y / 2 );
		}
	}

	WEEffect_TCB_AddPriSet(wk->we_sys, We065_TCB, wk);
}

//-------------------------------------
//	
//	スプーンまげ
//	
//=====================================
//個々のスプーンオブジェクトの動作シーケンス
enum{
	WE134_SPOON_OBJ_MOVE1,
	WE134_SPOON_OBJ_MOVE2,
	WE134_SPOOP_OBJ_END
};
//全体の流れ
enum{
	WE134_MATRIX_INIT,
	WE134_FADE_IN,
	WE134_FADE_IN_END,
	WE134_OBJ_MOVE,
	WE134_SPOON_CURVE,
	WE134_FADE_OUT,
	WE134_END
};

#define WE134_SPOON_NUM		(3)		// 残像＋本物
#define WE134_ZANZOU_NUM	(2)
#define WE134_ROTA1_S		( FX_GET_ROTA_NUM(90) )
#define WE134_ROTA1_E		( FX_GET_ROTA_NUM(270) )
#define WE134_ROTA2_E		( FX_GET_ROTA_NUM(180) )
#define WE134_ROTA_SP		( FX_GET_ROTA_NUM(10) )
#define WE134_ROTA_WIDHT	( -32 * FX32_ONE )
#define WE134_ROTA_HEIGHT	( -8 * FX32_ONE )
#define WE134_DO_WAIT		( 8 )
#define WE134_FADE_COUNT	( 10 )

#define WE134_ROTA_SP_S		( FX_GET_ROTA_NUM(0) )
#define WE134_ROTA_SP_E		( FX_GET_ROTA_NUM(360) )
#define WE134_ROTA_SP_W		( -1 * FX32_ONE )


// 個々のスプーン構造体
typedef struct {
	CATS_ACT_PTR	cap;
	WAZATOOL_CALCMOVE wtc;
	WAZATOOL_CALCMOVE_ONE add_sp;		// 回転スピード加速度
	s16 def_sp_x;	// X方向回転のデフォルトスピード
	s16	pos_x;
	s16 pos_y;
	int seq;
	BOOL do_flag;	// 実行開始フラグ
} TWE_134_SPOON;
// スプーンまげ全体データ
typedef struct {
	WE_SYS_PTR	we_sys;
	CATS_SYS_PTR csp;
	CATS_RES_PTR crp;

	// spoon_obj
	TWE_134_SPOON	main;
	TWE_134_SPOON	sub[ WE134_ZANZOU_NUM ];
	int	seq;
	int wait;
	int count;
	int fade_count;
} TWE_134_SYS;

//----------------------------------------------------------------------------
/**
 *	@brief	スプーンまげ　残像オブジェの作成
 *
 *	@param	spoon		スプーン残像オブジェデータ格納先
 *	@param	csp			clact_toolシステムワーク
 *	@param	crp			clact_toolリソースワーク
 *	@param	cp_coap		セルアクター情報
 *	@param	cp_parent	親スプーン
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void We_CAT_WE_134_ZanzouInit( TWE_134_SPOON* spoon, CATS_SYS_PTR csp, CATS_RES_PTR crp, const TCATS_OBJECT_ADD_PARAM_S* cp_coap, const TWE_134_SPOON* cp_parent )
{
	//スプーンアッド
	spoon->cap		= CATS_ObjectAdd_S(csp, crp, cp_coap);
	spoon->wtc		= cp_parent->wtc;
	spoon->add_sp	= cp_parent->add_sp;
	spoon->def_sp_x = cp_parent->def_sp_x;
	spoon->pos_x	= cp_parent->pos_x;
	spoon->pos_y	= cp_parent->pos_y;
	spoon->seq		= cp_parent->seq;
	spoon->do_flag	= FALSE;

	// 表示OFF
	CATS_ObjectEnableCap( spoon->cap, FALSE );

	CATS_ObjectPriSetCap( spoon->cap, WAZAEFF_ACT_SOFTPRI );
	CATS_ObjectBGPriSetCap( spoon->cap, WAZAEFF_ACT_BGPRI );
}

static void We_CAT_WE_134_ZanzouDelete( TWE_134_SPOON* spoon )
{
	//スプーン破棄
	CATS_ActorPointerDelete_S(spoon->cap);
}

//----------------------------------------------------------------------------
/**
 *	@brief	描画ON/OFF　設定
 *
 *	@param	spoon	スプーンデータ
 *	@param	flag	描画ON/OFF
 *
 *	@return	none
 *
 *	flag
 *		TRUE	表示
 *		FALSE	非表示
 */
//-----------------------------------------------------------------------------
static void We_CAT_WE_134_SpoonDrawFlag( TWE_134_SPOON* spoon, BOOL flag )
{
	CATS_ObjectEnableCap( spoon->cap, flag );
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	スプーン動作
 *
 *	@param	spoon	スプーンワーク
 *
 *	@retval	TRUE	途中
 *	@retval	FALSE	完了
 *
 *
 */
//-----------------------------------------------------------------------------
static BOOL We134_SpoonMove( TWE_134_SPOON* spoon )
{
	if( spoon->do_flag == FALSE ){
		return TRUE;
	}
	
	switch( spoon->seq ){
	case WE134_SPOON_OBJ_MOVE1:
	case WE134_SPOON_OBJ_MOVE2:
		if( WazaTool_CalcRotaFx( &spoon->wtc ) ){
			// 加速
			WazaTool_CalcCosOne( &spoon->add_sp );
			spoon->wtc.work[5] = spoon->def_sp_x + spoon->add_sp.num;

			CATS_ObjectPosSetCap( spoon->cap, 
					spoon->pos_x + spoon->wtc.x,
					spoon->pos_y + spoon->wtc.y	);
		}else{
			// MOVE2以外は次の動作の初期化を行う
			if( spoon->seq < WE134_SPOON_OBJ_MOVE2 ){
				// 回転移動
				if( spoon->seq == WE134_SPOON_OBJ_MOVE1 ){
					WazaTool_InitRotaSpeedFx( &spoon->wtc,
							spoon->wtc.work[1], WE134_ROTA2_E,
							spoon->wtc.work[1], WE134_ROTA2_E,
							spoon->wtc.work[2], spoon->wtc.work[4],
							WE134_ROTA_SP );
				}
				// 移動加速度
				WazaTool_InitSinCosOneSyncFx( &spoon->add_sp,
						WE134_ROTA_SP_S, WE134_ROTA_SP_E,
						WE134_ROTA_SP_W, spoon->wtc.work[0]);
			}
			spoon->seq++;
		}
		break;

	case WE134_SPOOP_OBJ_END:
		return FALSE;
	}
	
	return TRUE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	スプーンまげ	動作TCB
 *
 *	@param	tcb		TCBワーク
 *	@param	work	スプーンまげ動作ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void We134_TCB(TCB_PTR tcb, void* work)
{
	TWE_134_SYS* wk = work;
	int i;	// ループ用
	BOOL check = FALSE;
	BOOL check_sub;
	
	switch( wk->seq ){
	case WE134_MATRIX_INIT:
		We134_SpoonMove( &wk->main );
		wk->seq++;
		break;
	case WE134_FADE_IN:
		wk->fade_count += WE134_FADE_COUNT;
		G2_ChangeBlendAlpha( (wk->fade_count / 10), 31 - (wk->fade_count / 10) );
		
		if( wk->fade_count >= 310 ){
			// メインオブジェのオブジェモードを普通にする
			CATS_ObjectObjModeSetCap(wk->main.cap, GX_OAM_MODE_NORMAL);

			wk->seq++;
		}
		break;

	case WE134_FADE_IN_END:
		// 残像のα値に変更
		G2_ChangeBlendAlpha( WET_DEFAULT_BLEND, WET_DEFAULT_BLEND );
		wk->seq++;
		break;

	case WE134_OBJ_MOVE:
		// 実行開始チェック部
		if( wk->wait <= 0 ){
			wk->sub[ wk->count ].do_flag = TRUE;
			// 表示ON
			CATS_ObjectEnableCap( wk->sub[ wk->count ].cap, TRUE );
			
			wk->count ++;
			wk->wait = WE134_DO_WAIT;
		}
		if( wk->count < WE134_ZANZOU_NUM ){
			wk->wait --;
		}

		// 動作部
		check = We134_SpoonMove( &wk->main );
		for( i=0; i<WE134_ZANZOU_NUM; i++ ){
			check_sub = We134_SpoonMove( &wk->sub[ i ] );

			// 残像は動作が終わったら表示OFF
			if( check_sub == FALSE ){
				We_CAT_WE_134_SpoonDrawFlag( &wk->sub[ i ], FALSE );
			}
			check |= check_sub;
		}

		// 全動作終了したら終わり
		if( check == FALSE ){
			wk->seq++;
		}
		break;

	case WE134_SPOON_CURVE:
		// アニメーションさせる
		CATS_ObjectUpdateCap( wk->main.cap );

		// アニメ終了待ち
		if( CLACT_AnmActiveCheck( wk->main.cap->act ) == FALSE ){
			// メインオブジェを半透明オブジェモードに変更
			CATS_ObjectObjModeSetCap(wk->main.cap, GX_OAM_MODE_XLU);
			wk->seq ++;
		}
		break;

	case WE134_FADE_OUT:
		wk->fade_count -= WE134_FADE_COUNT;
		G2_ChangeBlendAlpha( (wk->fade_count / 10), 31 - (wk->fade_count / 10) );
		
		if( wk->fade_count <= 0 ){
			wk->seq++;
		}
		break;

	case WE134_END:
		// 残像データ破棄
		for( i=0; i<WE134_ZANZOU_NUM; i++ ){
			We_CAT_WE_134_ZanzouDelete( &wk->sub[ i ] );			
		}

		// mainOAM破棄
		CATS_ActorPointerDelete_S(wk->main.cap);
		
		// 終了
		WEEffect_TCB_Delete(wk->we_sys, tcb);
		sys_FreeMemoryEz(wk);
		return;
	}

	// OAM描画
	CATS_Draw(wk->crp);	
}

//----------------------------------------------------------------------------
/**
 * @brief	スプーンまげ用タスク
 *
 *	@param	we_sys	技エフェクトシステムワーク
 *	@param	csp		セルアクターツールシステム
 *	@param	crp		セルアクターリソースシステム
 *	@param	cap		セルアクターツールオブジェ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void WestSp_CAT_WE_134(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CATS_ACT_PTR cap)
{
	TWE_134_SYS* wk;
	TCATS_OBJECT_ADD_PARAM_S coap;
	int i;		// ループ用
	int at_client;
	int width;

	wk = sys_AllocMemory(WeSysHeapAreaGet(we_sys), sizeof(TWE_134_SYS));

	wk->we_sys	= we_sys;
	wk->csp		= csp;
	wk->crp		= crp;
	wk->wait	= WE134_DO_WAIT;
	wk->count	= 0;
	wk->seq		= 0;

	// ポケモンの配置からゆれる横方向を決定
	at_client = WeSysATNoGet(we_sys); 
	width = WazaTool_VecChangeX( we_sys, at_client );
	width *= WE134_ROTA_WIDHT;

	// メインスプーンデータ作成
	wk->main.cap	= cap;
	wk->main.seq	= WE134_SPOON_OBJ_MOVE1;
	WazaTool_InitRotaSpeedFx( &wk->main.wtc, 
			WE134_ROTA1_S, WE134_ROTA1_E,
			WE134_ROTA1_S, WE134_ROTA1_E,
			width, WE134_ROTA_HEIGHT,
			WE134_ROTA_SP );
	WazaTool_InitSinCosOneSyncFx( &wk->main.add_sp,
			WE134_ROTA_SP_S, WE134_ROTA_SP_E,
			WE134_ROTA_SP_W, wk->main.wtc.work[0]);

	wk->main.def_sp_x = wk->main.wtc.work[5];
	wk->main.do_flag = TRUE;	// メインはいきなり移動
	// 座標は攻撃側を設定
	wk->main.pos_x	= GetWazaEffPos(we_sys, at_client, PM_X);
	wk->main.pos_y	= GetWazaEffPos(we_sys, at_client, PM_Y);
	CATS_ObjectPosSetCap( wk->main.cap, wk->main.pos_x, wk->main.pos_y );
	CATS_ObjectPriSetCap( wk->main.cap, WAZAEFF_ACT_SOFTPRI );
	CATS_ObjectBGPriSetCap( wk->main.cap, WAZAEFF_ACT_BGPRI );
	
	// サブスプーンデータ作成
	coap   = WeSysCoapGet(wk->we_sys);
	coap.x = wk->main.pos_x;
	coap.y = wk->main.pos_y;
	for( i=0; i<WE134_ZANZOU_NUM; i++ ){

		We_CAT_WE_134_ZanzouInit( 
				&wk->sub[ i ],			// データ格納先
				wk->csp, wk->crp,		// セルアクターシステム
				&coap,					// セルアクター登録データ
				&wk->main );			// 親オブジェ
	}

	// フェード設定
	wk->fade_count = 0;
	WET_DefaultBlendSet(wk->we_sys, 0, 31);
	CATS_ObjectObjModeSetCap(wk->main.cap, GX_OAM_MODE_XLU);
	for( i=0; i<WE134_ZANZOU_NUM; i++ ){
		CATS_ObjectObjModeSetCap(wk->sub[ i ].cap, GX_OAM_MODE_XLU);
	}

	WEEffect_TCB_AddPriSet(wk->we_sys, We134_TCB, wk);
}


//-------------------------------------
//	
//	ねんりき
//	
//=====================================
enum{
/*	WE093_AT_MOVE,
	WE093_WAIT,//*/
	WE093_DF_MOVE1,
	WE093_DF_MOVE2,
	WE093_END,
};
#define WE093_SHAKE_MOVE	(2)	// 横揺れ幅
#define WE093_SHAKE_SYNC	(1)	
#define WE093_SHAKE_DFNUM	(6)

/*#define WE093_SHAKE_ATNUM	(2)
#define WE093_WAIT_NUM		(6)//*/

/*#define WE093_SCALE_WIDTH	(0.150f)
#define WE093_SCALE_HEIGHT	(0.30f)
#define WE093_Z_SCALE_MAX	(10.0f)//*/

#define WE093_Z_SCALE_D		( 10 )
#define WE093_Z_SCALE_XS	( 10 )
#define WE093_Z_SCALE_XE	( 12 )
#define WE093_Z_SCALE_YS	( 10 )
#define WE093_Z_SCALE_YE	( 15 )
#define WE093_Z_SCALE_OFS	( 0.10f )


#define WE093_Z_SCALE_ADD_SYNC	( 7 )
#define WE093_Z_SCALE_SUB_SYNC	( 4 )
//#define WE093_Z_ALPHA		(1)
//#define WE093_Z_BG_ALPHA	(16 - WE093_Z_ALPHA)//*/
#define WE093_Z_ALPHA		(28)
#define WE093_Z_BG_ALPHA	(15)
typedef struct {
	WE_SYS_PTR	we_sys;
	CATS_RES_PTR crp;

	int seq;
	int wait;

/*	// 攻撃
	WAZATOOL_CALCMOVE at_wtc;
	SOFT_SPRITE*	at_ssp;
	s16	at_x;
	s16 at_y;//*/

	// 防御
	WAZATOOL_CALCMOVE df_wtc;
	WAZATOOL_CALCMOVE df_scale;
	CATS_ACT_PTR	df_cap;	// 残像OAMのアクターデータ
	SOFT_SPRITE*	df_ssp;
	s16 df_x;
	s16 df_y;
	s16 s_ofs_switch;
	
	s16 cap_ofs_y;

} TWE_093_SYS;

//----------------------------------------------------------------------------
/**
 *	@brief	防御ポケモンの座標　拡大値設定
 *
 *	@param	TWE_093_SYS* wk 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void We093_DFPokeParamSet( TWE_093_SYS* wk )
{
	f32 scale_x, scale_y;

	SoftSpriteParaSet( wk->df_ssp, SS_PARA_POS_X, wk->df_x + wk->df_wtc.x );
	SoftSpriteParaSet( wk->df_ssp, SS_PARA_POS_Y, wk->df_y + wk->df_wtc.y );
	CATS_ObjectPosSetCap( wk->df_cap, wk->df_x + wk->df_wtc.x, wk->df_y + wk->df_wtc.y - wk->cap_ofs_y );
	
	WazaTool_CalcScaleRateToClactScale( &wk->df_scale, &scale_x, &scale_y );
	scale_x += (f32)(wk->s_ofs_switch * WE093_Z_SCALE_OFS);
	CATS_ObjectScaleSetCap( wk->df_cap, scale_x, scale_y );

	wk->s_ofs_switch *= -1;
}

//----------------------------------------------------------------------------
/**
 *	@brief	念力TCB
 *
 *	@param	tcb
 *	@param	work
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void We093_TCB(TCB_PTR tcb, void* work)
{
	TWE_093_SYS* wk = work;
	BOOL check;
	
	switch( wk->seq ){
/*	case WE093_AT_MOVE:
		
		// poke動作部
		if( WazaTool_CalcAndReflectShakeSsp( &wk->at_wtc, wk->at_x, wk->at_y, wk->at_ssp ) == FALSE ){
			SoftSpriteParaSet( wk->at_ssp, SS_PARA_POS_X, wk->at_x );
			SoftSpriteParaSet( wk->at_ssp, SS_PARA_POS_Y, wk->at_y );

			wk->seq++;
		}
		break;

	case WE093_WAIT:
		wk->wait++;
		if( wk->wait > WE093_WAIT_NUM ){
			wk->seq ++;
		}
		break;//*/

	case WE093_DF_MOVE1:	// 拡大MAXまで
		WazaTool_CalcShake( &wk->df_wtc );
		check = WazaTool_CalcScaleRateEx( &wk->df_scale );

		// 座標　拡大値設定
		We093_DFPokeParamSet( wk );
		
		if( check == FALSE ){
			// 拡大計算
			WazaTool_InitScaleRateEx( &wk->df_scale,
					WE093_Z_SCALE_XE,WE093_Z_SCALE_XS, 
					WE093_Z_SCALE_YE,WE093_Z_SCALE_YS,
					WE093_Z_SCALE_D,
					WE093_Z_SCALE_SUB_SYNC);

			wk->seq++;
		}
		break;

	case WE093_DF_MOVE2:	// 縮小おわりまで
		WazaTool_CalcShake( &wk->df_wtc );
		check = WazaTool_CalcScaleRateEx( &wk->df_scale );

		// 座標　拡大値設定
		We093_DFPokeParamSet( wk );
		
		if( check == FALSE ){
			SoftSpriteParaSet( wk->df_ssp, SS_PARA_POS_X, wk->df_x );
			SoftSpriteParaSet( wk->df_ssp, SS_PARA_POS_Y, wk->df_y );
			wk->seq++;
		}
		break;
		
	case WE093_END:

		// 終了
		WEEffect_TCB_Delete(wk->we_sys, tcb);
		sys_FreeMemoryEz(wk);
		return;	
	}

	// 残像OAM描画
	CATS_Draw(wk->crp);	
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ねんりき
 *
 *	@param	we_sys	技エフェクトシステムワーク
 *
 *	@return	none
 *
 * we_sysから受け取る引数なし
 *
 */
//-----------------------------------------------------------------------------
void WestSp_WE_093( WE_SYS_PTR we_sys )
{
	TWE_093_SYS* wk;

	
	wk = sys_AllocMemory(WeSysHeapAreaGet(we_sys), sizeof(TWE_093_SYS));

	wk->we_sys	= we_sys;
	wk->crp		= WeSysPokeCrpGet(wk->we_sys);
	wk->seq		= 0;
	wk->wait	= 0;
	
	// ポケモン　ソフトウェアスプライトデータ取得
/*	wk->at_ssp = WeSysSoftSpritePointerGet( wk->we_sys, WeSysATNoGet(wk->we_sys) );
	wk->at_x = SoftSpriteParaGet( wk->at_ssp, SS_PARA_POS_X );
	wk->at_y = SoftSpriteParaGet( wk->at_ssp, SS_PARA_POS_Y );//*/
	
	wk->df_ssp = WeSysSoftSpritePointerGet( wk->we_sys, WeSysDFNoGet(wk->we_sys) );
	wk->df_x = SoftSpriteParaGet( wk->df_ssp, SS_PARA_POS_X );
	wk->df_y = SoftSpriteParaGet( wk->df_ssp, SS_PARA_POS_Y );

	wk->cap_ofs_y = SoftSpriteParaGet( wk->df_ssp, SS_PARA_SHADOW_HEIGHT );

	// パレットフェード
//	PaletteFadeReq();

	// ポケモン　動作データ作成
//	WazaTool_InitShake( &wk->at_wtc, WE093_SHAKE_MOVE, 0, WE093_SHAKE_SYNC, WE093_SHAKE_ATNUM );
	WazaTool_InitShake( &wk->df_wtc, WE093_SHAKE_MOVE, 0, WE093_SHAKE_SYNC, WE093_SHAKE_DFNUM );

	// 残像データ作成
	// 残像データ取得
	wk->df_cap = WeSysPokeCapGet(wk->we_sys, 0);
	CATS_ObjectObjModeSetCap(wk->df_cap, GX_OAM_MODE_XLU);
	CATS_ObjectAffineSetCap(wk->df_cap, CLACT_AFFINE_DOUBLE);
	CATS_ObjectPriSetCap( wk->df_cap, WAZAEFF_ACT_SOFTPRI );
	CATS_ObjectBGPriSetCap( wk->df_cap, WAZAEFF_ACT_BGPRI );

	// 拡大計算
	WazaTool_InitScaleRateEx( &wk->df_scale,
			WE093_Z_SCALE_XS, WE093_Z_SCALE_XE,
			WE093_Z_SCALE_YS, WE093_Z_SCALE_YE,
			WE093_Z_SCALE_D,
			WE093_Z_SCALE_ADD_SYNC);

	// 拡縮振るえ動作のスイッチ
	wk->s_ofs_switch = 1;

	// 半透明掛ける
	WET_DefaultBlendSet(wk->we_sys,
			WE093_Z_ALPHA, WE093_Z_BG_ALPHA);

	WEEffect_TCB_AddPriSet(wk->we_sys, We093_TCB, wk);
}


//-------------------------------------
//	
//	とける
//	
//=====================================
enum{
	WE151_RASTER,
	WE151_FADE_OUT,
	WE151_FADE_WAIT,
	WE151_FADE_IN,
	WE151_END,
};
#define WE151_SIN_BUFF	(72)
#define WE151_ROTA_ADD	( FX_GET_ROTA_NUM(5) )
#define WE151_ROTA_WIDTH	(8*FX32_ONE)	// 半径

#define WE151_SCROLL_SP	(80)		// 単位は整数*100

#define WE151_MOVEY_END	(40)
#define WE151_MOVEX_END	(80)
#define WE151_MOVE_SYNC	(24)

#define WE151_ALPHA_FADE_SYNC	( 16 )

#define WE151_HEIGHT_ERR	(-8)	// このサイズ分ポケモンの絵の上と下をカット

#define WE151_FADE_WAIT_NUM	(8)
typedef struct{
	WE_SYS_PTR	we_sys;
	int			seq;
	int			count;

	SOFT_SPRITE* at_ssp;
	s16			at_x;
	s16			at_y;

	s16		start;
	s16		end;
	
	// ラスターデータ
	WAZATOOL_SCRLASTER_PTR	lst;

	// 縦横伸縮比計算
	WAZATOOL_CALCMOVE	move_param;

	// アルファフェード
	WAZATOOL_ALPHA_FADE	alpha_fade;
} TWE_151_SYS;


static void We151_BuffClean( TWE_151_SYS* wk, void* buff )
{
	u32 num;
	
	// バッファ内を初期値で初期化
	num = ((-wk->at_y & 0xffff) << 16) | (-wk->at_x & 0xffff);
	MI_CpuFill32( buff, num, sizeof(u32) * LASTER_SCROLL_BUFF_SIZE );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ラスター動作部分
 *
 *	@param	wk	ワーク
 *
 *	@retval	TRUE	途中
 *	@retval	FALSE	終了
 *
 *
 */
//-----------------------------------------------------------------------------
static BOOL We151_RasterMove( TWE_151_SYS* wk )
{
	u32* buff;
	int i;
	BOOL ret;
	s16 set_x, set_y;
	int in_buff;

	buff = WazaTool_GetScrLasterWriteBuff( wk->lst );
	// バッファ初期化
	We151_BuffClean( wk, buff );

	// 計算部
	// 縦横伸縮
	ret = WazaTool_CalcStraightFx( &wk->move_param );
	
	// 値設定部
	// 縦伸縮
	// 横平行移動
	for( i=wk->start; i<=wk->end; i++ ){
		set_x = buff[i] & 0xffff;
		set_y = buff[i] >> 16;

		// 縦伸縮設定
		set_y -= ( (wk->end - i) * (wk->move_param.y) ) / 100;
		set_x -= ( ((wk->start + (SOFT_SPRITE_SIZE_Y/2)) - i) * (wk->move_param.x) ) / 100;

		// 1つ前のバッファに入れておく
		in_buff = i - 1;
		if( in_buff < 0 ){
			in_buff += 192;
		}
		// 設定
		buff[in_buff] = WazaTool_GetLasterBuffMatrixData( set_x, set_y );
	}
	
	return ret;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	とける
 *
 *	@param	tcb		TCBワーク
 *	@param	work	ワーク
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void We151_TCB(TCB_PTR tcb, void* work)
{
	TWE_151_SYS* wk = work;

	switch( wk->seq ){
	case WE151_RASTER:
		if( We151_RasterMove( wk ) == FALSE ){
			wk->seq++;
			WET_DefaultBGEffectBlendSet( wk->we_sys, 31, 0 );
			// アルファフェード登録
			WazaTool_StartAlphaFade( &wk->alpha_fade,
					31, 0, 0, 31, WE151_ALPHA_FADE_SYNC);
		}
		break;
	
	case WE151_FADE_OUT:
		We151_RasterMove( wk );
		
		// アルファフェード終了待ち
		if( WazaTool_EndCheckAlphaFade( &wk->alpha_fade ) ){
			wk->seq ++;
			
			// ラスターシステムストップ
			WazaTool_StopScrLaster( wk->lst );
			wk->count = 0;
		}
		break;

	case WE151_FADE_WAIT:

		GF_BGL_ScrollSet(WeSysBGLPointerGet( wk->we_sys ), BATTLE_FRAME_EFFECT, GF_BGL_SCROLL_X_SET, -wk->at_x);
		GF_BGL_ScrollSet(WeSysBGLPointerGet( wk->we_sys ), BATTLE_FRAME_EFFECT, GF_BGL_SCROLL_Y_SET, -wk->at_y);

		wk->count ++;
		if( wk->count > WE151_FADE_WAIT_NUM ){
			// フェードイン開始
			WazaTool_StartAlphaFade( &wk->alpha_fade,
					0, 31, 31, 0, WE151_ALPHA_FADE_SYNC);
			wk->seq++;
		}
		break;

	case WE151_FADE_IN:
		// アルファフェード終了待ち
		if( WazaTool_EndCheckAlphaFade( &wk->alpha_fade ) ){
			// ポケモン表示
			SoftSpriteParaSet( wk->at_ssp, SS_PARA_VANISH, 0 );
		
			wk->seq++;
		}
		break;

	case WE151_END:

		// ラスターシステム破棄
		WazaTool_DeleteScrLaster( wk->lst );

		GF_BGL_PrioritySet( BT_BGL_FrameGet(wk->we_sys, WES_BF_EFFECT), BT_BGPriorityGet( wk->we_sys, WES_BF_EFFECT ) );
		GF_BGL_PrioritySet( GF_BGL_FRAME0_M, BT_3DPriorityGet(wk->we_sys) );
		
		// キャラクタデータクリア
		GF_BGL_ClearCharSet( BT_BGL_FrameGet(wk->we_sys, WES_BF_EFFECT), 0x4000, 0, WeSysHeapAreaGet(wk->we_sys) );
		GF_BGL_ScrClear( WeSysBGLPointerGet(wk->we_sys) ,BT_BGL_FrameGet(wk->we_sys, WES_BF_EFFECT) );
		
		// 終了
		WEEffect_TCB_Delete(wk->we_sys, tcb);
		sys_FreeMemoryEz(wk);
		break;

	default:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	とける
 *
 *	@param	we_sys	技エフェクトシステムワーク
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void WestSp_WE_151( WE_SYS_PTR we_sys )
{
	TWE_151_SYS* wk;
	int vec_x;
	TCB_PTR tcb;
	int client_type;

	wk = sys_AllocMemory(WeSysHeapAreaGet(we_sys), sizeof(TWE_151_SYS));
	memset( wk, 0, sizeof(TWE_151_SYS) );

	wk->we_sys	= we_sys;

	// WE151タスク登録
	tcb = WEEffect_TCB_AddPriSet(wk->we_sys, We151_TCB, wk);

	// 攻撃側ポケモンデータ取得
	wk->at_ssp = WeSysSoftSpritePointerGet( wk->we_sys, WeSysATNoGet(wk->we_sys) );
	wk->at_x = SoftSpriteParaGet( wk->at_ssp, SS_PARA_POS_X );
	wk->at_y = SoftSpriteParaGet( wk->at_ssp, SS_PARA_POS_Y );
	wk->at_y -= SoftSpriteParaGet(wk->at_ssp, SS_PARA_SHADOW_HEIGHT);

	// 左上座標に変更
	wk->at_x -= SOFT_SPRITE_SIZE_X / 2;
	wk->at_y -= SOFT_SPRITE_SIZE_Y / 2;

	// ポケモン非表示
	SoftSpriteParaSet( wk->at_ssp, SS_PARA_VANISH, 1 );

	// ベクトルを整える
	vec_x = WazaTool_VecChangeX( wk->we_sys, WeSysATNoGet(wk->we_sys) );

	wk->start	= wk->at_y + WE151_HEIGHT_ERR;
	wk->end		= wk->at_y + SOFT_SPRITE_SIZE_Y - WE151_HEIGHT_ERR;

	if( wk->start < 0 ){
		wk->start = 0;
	}
	if( wk->end > 192 ){
		wk->end = 192;
	}
	
	// ラスター初期化
	wk->lst = WazaTool_InitScrLaster( 
			wk->start,					// 開始
			wk->end,					// 終了
			WE151_ROTA_ADD,				// 回転角変更値
			WE151_ROTA_WIDTH * vec_x,	// 半径
			WE151_SCROLL_SP,			// スクロールスピード
			BT_BGL_BGNoGet(we_sys, WES_BF_EFFECT),	// BGNO
			TCB_GetPriority(tcb)+ 1,		// タスク優先順位
			WazaTool_GetLasterBuffMatrixData( wk->at_x, wk->at_y ),
			WeSysHeapAreaGet(we_sys) );
	
	// 縦横伸縮比
	WazaTool_InitStraightSyncFx( &wk->move_param,
			0, WE151_MOVEX_END,
			0, WE151_MOVEY_END,
			WE151_MOVE_SYNC );

	// 縦横伸縮比
	wk->move_param.work[1] *= vec_x;	// 横方向のベクトル

	// 当てるOBJの位置によりBGpriorityを変更する
	client_type = WET_ClientTypeGet( wk->we_sys, WeSysATNoGet(we_sys) );
	if( (client_type == CLIENT_TYPE_B) || (client_type == CLIENT_TYPE_C) ){
		GF_BGL_PrioritySet( BT_BGL_FrameGet(wk->we_sys, WES_BF_EFFECT), BT_3DPriorityGet(wk->we_sys) );
		GF_BGL_PrioritySet( GF_BGL_FRAME0_M, BT_3DPriorityGet(wk->we_sys) + 1 );
	}

	// 1回呼ぶ
	We151_TCB( tcb, wk );
}

//-------------------------------------
//	
//	ナイトヘッド
//	
//=====================================
enum{
	WE101_AT_POKE_SCALE_FADEIN,
	WE101_ATWAIT,
	WE101_AT_POKE_SCALE_DOWN,
	WE101_ATEND,
};

enum{
	WE101_DF_POKEBLACKOUT,
	WE101_DF_POKEBLACKIN,
	WE101_DF_END,
};

#define WE101_AT_SCALE_START	(14)
#define WE101_AT_SCALE_END		(10)
#define WE101_AT_SCALE_START_F	(WE101_AT_SCALE_START / (f32)WE101_AT_SCALE_END)
#define WE101_AT_SCALE_SYNC		(8)

#define WE101_AT_ALPHA_START	(0)
#define WE101_AT_ALPHA_END		(16)
#define WE101_AT_ALPHA_SYNC		(8)

#define WE101_AT_WAIT	( 32 )

#define WE101_DF_SHAKE_WIDTH	(4)
#define WE101_DF_SHAKE_SYNC		(1)
#define WE101_DF_SHAKE_NUM		(4)
#define WE101_DF_BLACK_FADE_WAIT	(0)
#define WE101_DF_BLACK_FADE_S		(0)
#define WE101_DF_BLACK_FADE_E		(16)
#define WE101_DF_BLACK_FADE_COL		(0)

typedef struct {
	WE_SYS_PTR	we_sys;
	CATS_RES_PTR crp;
	int			seq;
	int			count;
	
	// 攻撃側CAT
	CATS_ACT_PTR			at_cap;
	WAZATOOL_CALCMOVE		at_scale;
	WAZATOOL_CALCMOVE_ONE	at_alpha;
	BOOL contest_x_flip;		// コンテストのときTRUE
} TWE_101AT_SYS;

typedef struct {
	WE_SYS_PTR	we_sys;
	int			seq;
	
	// 防御側
	SOFT_SPRITE*		df_ssp;
	CATS_ACT_PTR		df_cap;
	BOOL				cap_move;
	WAZATOOL_CALCMOVE	df_shake;
	s16					df_x;
	s16					df_y;

	int					oam_y;
} TWE_101DF_SYS;



//----------------------------------------------------------------------------
/**
 *
 *	@brief	ナイトヘッド
 *
 *	@param	tcb		TCBワーク
 *	@param	work	ワーク
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void We101AT_TCB(TCB_PTR tcb, void* work)
{
	TWE_101AT_SYS* wk = work;
	BOOL check;
	f32 s_x, s_y;

	switch( wk->seq ){
	case WE101_AT_POKE_SCALE_FADEIN:
		check = WazaTool_CalcMoveOneFx( &wk->at_alpha );
		G2_ChangeBlendAlpha( wk->at_alpha.num, 31 - wk->at_alpha.num );
		if( check == FALSE ){
			wk->seq++;
			wk->count = 0;
		}
		break;

	case WE101_ATWAIT:

		wk->count ++;
		if( wk->count > WE101_AT_WAIT ){
			wk->seq++;
		}
		break;
		
	case WE101_AT_POKE_SCALE_DOWN:
		check = WazaTool_CalcScaleRate( &wk->at_scale );

		WazaTool_CalcScaleRateToClactScale( &wk->at_scale, &s_x, &s_y );
		if( wk->contest_x_flip == TRUE ){
			s_x = -s_x;
		}
		CATS_ObjectScaleSetCap( wk->at_cap, s_x, s_y );
//		check = WazaTool_CalcAndReflectScaleRateCap( &wk->at_scale, wk->at_cap );
		if( check == FALSE ){
			// オブジェウィンドウOAM非表示
			CATS_ObjectEnableCap( wk->at_cap, FALSE );
			wk->seq++;
		}
		break;
		
	case WE101_ATEND:

		// 終了
		WEEffect_TCB_Delete(wk->we_sys, tcb);
		sys_FreeMemoryEz(wk);
		return ;
	}

	// 残像OAM描画
	CATS_Draw(wk->crp);	
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ナイトヘッド
 *
 *	@param	tcb		TCBワーク
 *	@param	work	ワーク
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void We101DF_TCB(TCB_PTR tcb, void* work)
{
	TWE_101DF_SYS* wk = work;
	BOOL check;

	switch( wk->seq ){
	case WE101_DF_POKEBLACKOUT:
		WazaTool_CalcShake( &wk->df_shake );
		WazaTool_SetSspMatrix( &wk->df_shake, wk->df_ssp, wk->df_x, wk->df_y );
		// ２vs２ポケモンかぶり問題のため
		if( wk->cap_move == TRUE ){
			WazaTool_SetCapMatrix( &wk->df_shake, wk->df_cap, wk->df_x, wk->df_y - wk->oam_y );
		}
		if( SoftSpritePalFadeExist( wk->df_ssp ) == FALSE ){
			// palフェード
			SoftSpritePalFadeSet( wk->df_ssp, WE101_DF_BLACK_FADE_E, WE101_DF_BLACK_FADE_S, WE101_DF_BLACK_FADE_WAIT, WE101_DF_BLACK_FADE_COL );

			// ２vs２ポケモンかぶり問題のため
			if( wk->cap_move == TRUE ){
				int plt_bit;

				// パレットフェード
				plt_bit = 1 << WazaTool_CapPlttNoGet( wk->df_cap );

				PaletteFadeReq(WeSysPFDGet(wk->we_sys), PF_BIT_MAIN_OBJ, plt_bit, WE101_DF_BLACK_FADE_WAIT, WE101_DF_BLACK_FADE_E, WE101_DF_BLACK_FADE_S, WE101_DF_BLACK_FADE_COL);
			}

			wk->seq++;
		}
		break;

	case WE101_DF_POKEBLACKIN:
		check = WazaTool_CalcShake( &wk->df_shake );
		WazaTool_SetSspMatrix( &wk->df_shake, wk->df_ssp, wk->df_x, wk->df_y );
		// ２vs２ポケモンかぶり問題のため
		if( wk->cap_move == TRUE ){
			WazaTool_SetCapMatrix( &wk->df_shake, wk->df_cap, wk->df_x, wk->df_y - wk->oam_y );
		}
		if( SoftSpritePalFadeExist( wk->df_ssp ) == FALSE ){

			SoftSpriteParaSet( wk->df_ssp, SS_PARA_POS_X, wk->df_x );
			SoftSpriteParaSet( wk->df_ssp, SS_PARA_POS_Y, wk->df_y );

			// ２VS２ポケモンかぶり問題のため
			if( wk->cap_move == TRUE ){
				SoftSpriteParaSet( wk->df_ssp, SS_PARA_VANISH, 0 );	// ssp非表示
				CATS_ObjectPosSetCap( wk->df_cap, wk->df_x, wk->df_y - wk->oam_y );
			}

			wk->seq++;
		}
		break;
		
	case WE101_DF_END:
		// 終了
		WEEffect_TCB_Delete(wk->we_sys, tcb);
		sys_FreeMemoryEz(wk);
		return ;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ナイトヘッド
 
 *	@param	we_sys	技エフェクトシステムワーク
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void WestSp_WE_101AT( WE_SYS_PTR we_sys )
{
	TWE_101AT_SYS* wk;
	int vec_x;

	wk = sys_AllocMemory(WeSysHeapAreaGet(we_sys), sizeof(TWE_101AT_SYS));
	memset( wk, 0, sizeof(TWE_101AT_SYS) );

	wk->we_sys	= we_sys;
	wk->crp		= WeSysPokeCrpGet(wk->we_sys);

	// コンテストかチェック
	wk->contest_x_flip = WES_ContestFlag_Get(we_sys);


	// 攻撃側データ作成
	wk->at_cap = WeSysPokeCapGet(wk->we_sys, 0);
	// 拡縮動作
	WazaTool_InitScaleRate( &wk->at_scale, WE101_AT_SCALE_START, WE101_AT_SCALE_END, WE101_AT_SCALE_END, WE101_AT_SCALE_SYNC );
	// アルファ
	WazaTool_InitMoveOneSyncFx( &wk->at_alpha, WE101_AT_ALPHA_START, WE101_AT_ALPHA_END, WE101_AT_ALPHA_SYNC );
	// アルファ設定
	CATS_ObjectObjModeSetCap( wk->at_cap, GX_OAM_MODE_XLU );
	WET_DefaultBlendSet( wk->we_sys, 0, 31 );
	// 拡縮設定
	CATS_ObjectAffineSetCap( wk->at_cap, CLACT_AFFINE_DOUBLE );
	
	if(wk->contest_x_flip == TRUE){
		CATS_ObjectScaleSetCap( wk->at_cap, -WE101_AT_SCALE_START_F, WE101_AT_SCALE_START_F );
	}else{
		CATS_ObjectScaleSetCap( wk->at_cap, WE101_AT_SCALE_START_F, WE101_AT_SCALE_START_F );
	}
	
	CATS_ObjectPriSetCap( wk->at_cap, WAZAEFF_ACT_SOFTPRI );
	CATS_ObjectBGPriSetCap( wk->at_cap, WAZAEFF_ACT_BGPRI );

	// タスク登録
	WEEffect_TCB_AddPriSet(wk->we_sys, We101AT_TCB, wk);
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ナイトヘッド
 *
 *	@param	we_sys	技エフェクトシステムワーク
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void WestSp_WE_101DF( WE_SYS_PTR we_sys )
{
	TWE_101DF_SYS* wk;
	int vec_x;
	int at_client;
	int df_client;

	wk = sys_AllocMemory(WeSysHeapAreaGet(we_sys), sizeof(TWE_101DF_SYS));
	memset( wk, 0, sizeof(TWE_101DF_SYS) );

	wk->we_sys	= we_sys;

	// 防御側データ作成
	wk->df_ssp = WeSysSoftSpritePointerGet( wk->we_sys, WeSysDFNoGet(wk->we_sys) );
	wk->df_x = SoftSpriteParaGet( wk->df_ssp, SS_PARA_POS_X );
	wk->df_y = SoftSpriteParaGet( wk->df_ssp, SS_PARA_POS_Y );
	wk->oam_y = SoftSpriteParaGet(wk->df_ssp, SS_PARA_SHADOW_HEIGHT);
	// 横揺れ
	WazaTool_InitShake( &wk->df_shake, WE101_DF_SHAKE_WIDTH,0,WE101_DF_SHAKE_SYNC,WE101_DF_SHAKE_NUM );
		
	// ベクトルをあわせる
	vec_x = WazaTool_VecChangeX( wk->we_sys, WeSysDFNoGet( wk->we_sys ) );
	wk->df_shake.x += vec_x;

	// palフェード
	SoftSpritePalFadeSet( wk->df_ssp, WE101_DF_BLACK_FADE_S, WE101_DF_BLACK_FADE_E, WE101_DF_BLACK_FADE_WAIT, WE101_DF_BLACK_FADE_COL );

	// Defenseマスク用セル
	wk->df_cap = WeSysPokeCapGet(wk->we_sys, 1);

	at_client = WET_ClientTypeGet( wk->we_sys, WeSysATNoGet(wk->we_sys) );
	df_client = WET_ClientTypeGet( wk->we_sys, WeSysDFNoGet(wk->we_sys) );

	// 攻撃がAで守備がC
	// 攻撃がDで守備がB
	// の時だけSSPを消しCAPだけで動さする
	// ２VS２ポケモンかぶり問題のため
	if( ((at_client == CLIENT_TYPE_A) && (df_client == CLIENT_TYPE_C)) ||
		((at_client == CLIENT_TYPE_D) && (df_client == CLIENT_TYPE_B)) ){
		int plt_bit;
		// パレットフェード
		plt_bit = 1 << WazaTool_CapPlttNoGet( wk->df_cap );
		PaletteFadeReq(WeSysPFDGet(wk->we_sys), PF_BIT_MAIN_OBJ, plt_bit, WE101_DF_BLACK_FADE_WAIT, WE101_DF_BLACK_FADE_S, WE101_DF_BLACK_FADE_E, WE101_DF_BLACK_FADE_COL);
		wk->cap_move = TRUE;
		SoftSpriteParaSet( wk->df_ssp, SS_PARA_VANISH, 1 );	// ssp非表示
	}

	// タスク登録
	WEEffect_TCB_AddPriSet(wk->we_sys, We101DF_TCB, wk);
}

//-------------------------------------
//	
//	うらみ
//	
//=====================================
// 光るポケモンの方
enum{
	WE180_INIT,
	WE180_MAIN,
	WE180_END,
};

// ラスターポケモンの方
enum{
	WE180_L_FADEIN,
	WE180_L_MAIN,
	WE180_L_FADE_OUT,
	WE180_L_END,
};

/*// パレットフェード
enum{
	WE180_P_FADEOUT_INIT,
	WE180_P_FADEOUT_MAIN,
	WE180_P_FADEIN_INIT,
	WE180_P_FADEIN_MAIN,
	WE180_P_FADE_END,
};//*/

#define WE180_ROTA_ADD		( FX_GET_ROTA_NUM(5) )
#define WE180_ROTA_WIDTH	( 5*FX32_ONE )
#define WE180_SCR_SP		(100)

#define WE180_FADEIN_ALPHA1_ST		( 0 )
#define WE180_FADEIN_ALPHA1_ED		( 8 )
#define WE180_FADEIN_ALPHA2_ST		( 16 )
#define WE180_FADEIN_ALPHA2_ED		( 8 )
#define WE180_FADEIN_ALPHA_SYNC		( 24 )
#define WE180_FADEOUT_ALPHA_SYNC	( 24 )//*/

#define WE180_LASTER_COUNT		(32)

/*#define WE180_PL_FADE_S			(0)
#define WE180_PL_FADE_E			(8)
#define WE180_PL_COLOR			( GX_RGB( 31,31,31 ) )
#define WE180_PL_WAIT			( 0 )
#define WE180_PL_COUNT			( 4 )//*/

typedef struct {
	WE_SYS_PTR	we_sys;
	int			seq;
	int			sub_seq;
	int			pl_fade_seq;

/*	// 攻撃用
	SOFT_SPRITE* at_ssp;	// 光らせるスプライト
	int at_pl_count;//*/
	
	// 防御用
	SOFT_SPRITE* df_ssp;
	WAZATOOL_SCRLASTER_PTR	lst;
	PALETTE_FADE_PTR	pfd;	// BGのパレットフェード
	WAZATOOL_ALPHA_FADE alpha;	// アルファフェード
	int df_count;

	CATS_ACT_PTR		df_cap;
	
} TWE_180_SYS;

/*
static BOOL We180_PlFadeObj( TWE_180_SYS* wk )
{
	BOOL ret = FALSE;
	
	switch( wk->pl_fade_seq ){
	case WE180_P_FADEOUT_INIT:
		SoftSpritePalFadeSet( wk->at_ssp, 
				WE180_PL_FADE_S, WE180_PL_FADE_E,
				WE180_PL_WAIT, WE180_PL_COLOR );
		wk->pl_fade_seq++;
		break;
		
	case WE180_P_FADEOUT_MAIN:
		if( SoftSpritePalFadeExist( wk->at_ssp ) == FALSE ){
			wk->pl_fade_seq++;
		}
		break;
		
	case WE180_P_FADEIN_INIT:
		SoftSpritePalFadeSet( wk->at_ssp, 
				WE180_PL_FADE_E, WE180_PL_FADE_S,
				WE180_PL_WAIT, WE180_PL_COLOR );
		wk->pl_fade_seq++;
		break;
		
	case WE180_P_FADEIN_MAIN:
		if( SoftSpritePalFadeExist( wk->at_ssp ) == FALSE ){
			wk->at_pl_count++;
			if( wk->at_pl_count > WE180_PL_COUNT ){
				wk->pl_fade_seq++;
			}else{
				wk->pl_fade_seq = WE180_P_FADEOUT_INIT;
			}
		}
		break;
		
	case WE180_P_FADE_END:
		ret = TRUE;
		break;
	}

	return ret;
}
//*/
static BOOL We180_LasterObj( TWE_180_SYS* wk )
{
	BOOL ret = FALSE;
	
	switch( wk->sub_seq ){
	case WE180_L_FADEIN:
		if( WazaTool_EndCheckAlphaFade( &wk->alpha ) == TRUE ){
			wk->sub_seq ++;
			wk->df_count = WE180_LASTER_COUNT;
		}
		break;
		
	case WE180_L_MAIN:
		wk->df_count --;
		if( wk->df_count < 0 ){
			wk->sub_seq++;

			// フェードアウト準備
			WazaTool_StartAlphaFade( &wk->alpha,
					WE180_FADEIN_ALPHA1_ED, WE180_FADEIN_ALPHA1_ST, 
					 WE180_FADEIN_ALPHA2_ED, WE180_FADEIN_ALPHA2_ST,
					WE180_FADEOUT_ALPHA_SYNC );
		}
		break;
		
	case WE180_L_FADE_OUT:
		if( WazaTool_EndCheckAlphaFade( &wk->alpha ) == TRUE ){
			wk->sub_seq ++;

			// ラスター破棄
			WazaTool_DeleteScrLaster( wk->lst );
		}
		break;
		
	case WE180_L_END:
		ret = TRUE;
		break;
	}

	return ret;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	うらみ
 *
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void We180_TCB( TCB_PTR tcb, void* work )
{
	TWE_180_SYS* wk = work;
	BOOL check;
	
	
	switch( wk->seq ){
	case WE180_INIT:
		if( CATS_ObjectEnableGetCap( wk->df_cap ) == 1 ){
			SoftSpriteParaSet( wk->df_ssp, SS_PARA_VANISH, 1 );
		}
		
		We180_LasterObj( wk );
		wk->seq ++;
		break;

	case WE180_MAIN:

		// 光らせる
		check = We180_LasterObj( wk );
		
		// ラスターの方が終わるのを待つ
		if( check ){
			wk->seq ++;
		}
		break;
		
	case WE180_END:

		// エフェクトBG優先順位変更
		GF_BGL_PrioritySet( BT_BGL_FrameGet(wk->we_sys, WES_BF_EFFECT), BT_BGPriorityGet( wk->we_sys, WES_BF_EFFECT ) );
		GF_BGL_PrioritySet( GF_BGL_FRAME0_M, BT_3DPriorityGet(wk->we_sys) );
		
		SoftSpriteParaSet( wk->df_ssp, SS_PARA_VANISH, 0 );

		// キャラクタデータクリア
		GF_BGL_ClearCharSet( BT_BGL_FrameGet(wk->we_sys, WES_BF_EFFECT), 0x4000, 0, WeSysHeapAreaGet(wk->we_sys) );
		GF_BGL_ScrClear( WeSysBGLPointerGet(wk->we_sys) ,BT_BGL_FrameGet(wk->we_sys, WES_BF_EFFECT) );
		
		// 終了
		WEEffect_TCB_Delete(wk->we_sys, tcb);
		sys_FreeMemoryEz(wk);
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	うらみ
 *
 *	@param	we_sys	技エフェクトシステムワーク
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void WestSp_WE_180( WE_SYS_PTR we_sys )
{
	TWE_180_SYS* wk;
	int vec_x;
	s16 e_x, e_y;
	int plt_bit;
	int client_type;
	
	wk = WET_ALLOC_MEMORY(we_sys, TWE_180_SYS);
	wk->we_sys	= we_sys;
	wk->pfd		= WeSysPFDGet(wk->we_sys);

	// アルファフェード
	WET_DefaultBGEffectBlendSet( wk->we_sys, WE180_FADEIN_ALPHA1_ST, WE180_FADEIN_ALPHA2_ST );
	WazaTool_StartAlphaFade( &wk->alpha,
			WE180_FADEIN_ALPHA1_ST, WE180_FADEIN_ALPHA1_ED,
			WE180_FADEIN_ALPHA2_ST, WE180_FADEIN_ALPHA2_ED,
			WE180_FADEIN_ALPHA_SYNC );


/*	// 攻撃側
	wk->at_ssp = WeSysSoftSpritePointerGet( wk->we_sys, WeSysATNoGet(wk->we_sys) );
//*/

	// 防御側
	// 
	wk->df_ssp = WeSysSoftSpritePointerGet( wk->we_sys, WeSysDFNoGet(wk->we_sys) );
	e_x = SoftSpriteParaGet( wk->df_ssp, SS_PARA_POS_X );
	e_y = SoftSpriteParaGet( wk->df_ssp, SS_PARA_POS_Y );
	e_y -= SoftSpriteParaGet(wk->df_ssp, SS_PARA_SHADOW_HEIGHT);
	e_x -= (SOFT_SPRITE_SIZE_X / 2);
	e_y -= (SOFT_SPRITE_SIZE_Y / 2);

	// 中のレイヤーにBGを入れるための処理
	wk->df_cap = WeSysPokeCapGet(wk->we_sys, 0);
	client_type = WET_ClientTypeGet( wk->we_sys, WeSysDFNoGet(wk->we_sys) );
	if( (client_type == CLIENT_TYPE_D) ||
		(client_type == CLIENT_TYPE_A) ){
		CATS_ObjectEnableCap( wk->df_cap, TRUE );
		CATS_ObjectBGPriSetCap( wk->df_cap, 2 );
	}else{

		// エフェクトBGを３D面の上にする
		GF_BGL_PrioritySet( BT_BGL_FrameGet(wk->we_sys, WES_BF_EFFECT), BT_3DPriorityGet(wk->we_sys) );
		GF_BGL_PrioritySet( GF_BGL_FRAME0_M, BT_3DPriorityGet(wk->we_sys) + 1 );
		CATS_ObjectEnableCap( wk->df_cap, FALSE );
	}

	
	// ラスター
	wk->lst = WazaTool_InitScrLaster( 
			e_y,
			e_y + SOFT_SPRITE_SIZE_Y,
			WE180_ROTA_ADD,
			WE180_ROTA_WIDTH,
			WE180_SCR_SP,
			BT_BGL_BGNoGet(we_sys, WES_BF_EFFECT),
			0,
			WazaTool_GetLasterBuffMatrixData( -e_x, -e_y ),
			WeSysHeapAreaGet(we_sys) );

	// パレットフェード
	plt_bit = 1 << (BATTLE_PAL_EFF_0);
	ColorConceChangePfd( wk->pfd, FADE_MAIN_BG, plt_bit, 8, 0x0 );

	// タスク登録
	WEEffect_TCB_AddPriSet(wk->we_sys, We180_TCB, wk);
}

//-------------------------------------
//	
//	ゆびをふる
//	
//=====================================
enum{
	WE118_FADEIN,
	WE118_MAIN,
	WE118_FADEOUT,
	WE118_END,
};

#define WE118_FADE_SCALE_S	(1)
#define WE118_FADE_SCALE_D	(10)
#define WE118_FADE_SCALE_E	(10)
#define WE118_FADE_SYNC		(8)

#define WE118_ROTA_S	( FX_GET_ROTA_NUM( 359 ) )
#define WE118_ROTA_E	( FX_GET_ROTA_NUM( 320 ) )
#define WE118_ROTA_S_E	( FX_GET_ROTA_NUM( 0 ) )
#define WE118_ROTA_E_E	( FX_GET_ROTA_NUM( 40 ) )
#define WE118_ROTA_NUM	( 5 )
#define WE118_ROTA_ONE_SYNC	(4)
#define WE118_ROTA_OFS_X	( -12 )
#define WE118_ROTA_OFS_Y	( 12 )

// 座標補正
#define WE118_MATRIX_OFSX	( 40 )
#define WE118_MATRIX_OFSY	( 0 )

typedef struct {
	WE_SYS_PTR	we_sys;
	CATS_SYS_PTR csp;
	CATS_RES_PTR crp;
	int	seq;

	//　手
	CATS_ACT_PTR			hand_cap;
	WAZATOOL_CALCMOVE		hand_scale;
	WAZATOOL_CALCMOVE_ONE	hand_rota;
	int hand_rota_count;
	int hand_rota_end;

	int sum_flip;
	
	// 後々は後ろの絵
} TWE_118_SYS;

//----------------------------------------------------------------------------
/**
 *	@brief	ゆびをふる	動作TCB
 *
 *	@param	tcb		TCBワーク
 *	@param	work	スプーンまげ動作ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void We118_TCB(TCB_PTR tcb, void* work)
{
	TWE_118_SYS* wk = work;
	BOOL check;
	f32	s_x, s_y;
	int rota_s, rota_e;

	switch( wk->seq ){
	case WE118_FADEIN:
		// 計算
		check = WazaTool_CalcScaleRate( &wk->hand_scale );
		
		// 値設定
		if( check == TRUE ){
			WazaTool_CalcScaleRateToClactScale( &wk->hand_scale, &s_x, &s_y );
			CATS_ObjectScaleSetCap( wk->hand_cap, s_x * wk->sum_flip, s_y );
		}else{
			wk->seq++;
			wk->hand_rota_count = WE118_ROTA_NUM;
				
			// フェードアウトの設定を行う
			WazaTool_InitScaleRate(		// 拡縮
					&wk->hand_scale,
					WE118_FADE_SCALE_E,
					WE118_FADE_SCALE_D,
					WE118_FADE_SCALE_S,		
					WE118_FADE_SYNC	);
			
		}
		break;
		
	case WE118_MAIN:
		check = WazaTool_CalcMoveOne( &wk->hand_rota );
		// 回転各設定
		CATS_ObjectRotationSetCap( wk->hand_cap, wk->hand_rota.num );
		
		if( check == FALSE ){
			if( wk->hand_rota_count > 0 ){
				wk->hand_rota_count --;
		
				rota_s = wk->hand_rota.num;
				rota_e = wk->hand_rota_end;
				wk->hand_rota_end = wk->hand_rota.num;
				
				// 回転初期化
				WazaTool_InitMoveOneSync( 
						&wk->hand_rota,
						rota_s,
						rota_e,
						WE118_ROTA_ONE_SYNC
						);
			}else{
				
				wk->seq ++;
			}
		}
		break;
		
	case WE118_FADEOUT:
		// 計算
		check = WazaTool_CalcScaleRate( &wk->hand_scale );
		
		// 値設定
		if( check == TRUE ){
			WazaTool_CalcScaleRateToClactScale( &wk->hand_scale, &s_x, &s_y );
			CATS_ObjectScaleSetCap( wk->hand_cap, s_x * wk->sum_flip, s_y );

		}else{
		
			wk->seq++;
		}
		break;
		
	case WE118_END:
		// 終了
		// OAM破棄
		CATS_ActorPointerDelete_S(wk->hand_cap);

		// 終了
		WEEffect_TCB_Delete(wk->we_sys, tcb);
		sys_FreeMemoryEz(wk);
		return ;
	}

	// OAM描画
	CATS_Draw(wk->crp);	
}

//----------------------------------------------------------------------------
/**
 * @brief	指をふる用タスク
 *
 *	@param	we_sys	技エフェクトシステムワーク
 *	@param	csp		セルアクターツールシステム
 *	@param	crp		セルアクターリソースシステム
 *	@param	cap		セルアクターツールオブジェ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void WestSp_CAT_WE_118(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CATS_ACT_PTR cap)
{
	TWE_118_SYS* wk;
	int vec_x;
	int con_chg_x;
	s16 at_x, at_y;
	
	wk = WET_ALLOC_MEMORY(we_sys, TWE_118_SYS);
	wk->we_sys	= we_sys;
	wk->csp		= csp;
	wk->crp		= crp;

	vec_x = WazaTool_VecChangeX( wk->we_sys, WeSysATNoGet(wk->we_sys) );

	// コンテストのときフリップ
	if( ContestFlipCheck(wk->we_sys, WEDEF_DROP_M1 ) == TRUE ){
		wk->sum_flip = -1;
		con_chg_x = vec_x * -1;
	}else{
		wk->sum_flip = 1;
		con_chg_x = vec_x;
	}
	

	// 座標は攻撃側を設定
	at_x	= GetWazaEffPos(we_sys, WeSysATNoGet(wk->we_sys), PM_X);
	at_y	= GetWazaEffPos(we_sys, WeSysATNoGet(wk->we_sys), PM_Y);
	
	// 手動作パラメータ設定
	wk->hand_cap		= cap;
	CATS_ObjectAffineSetCap( wk->hand_cap, CLACT_AFFINE_DOUBLE );
	CATS_ObjectScaleSetCap( wk->hand_cap, WE118_FADE_SCALE_S, WE118_FADE_SCALE_S );
	CATS_ObjectPosSetCap( wk->hand_cap, at_x, at_y );
	CATS_ObjectPosMoveCap( wk->hand_cap, WE118_MATRIX_OFSX * vec_x, WE118_MATRIX_OFSY );
	CATS_ObjectPriSetCap( wk->hand_cap, WAZAEFF_ACT_SOFTPRI );
	CATS_ObjectBGPriSetCap( wk->hand_cap, WAZAEFF_ACT_BGPRI );
	CATS_ObjectAffinePosSetCap( wk->hand_cap, WE118_ROTA_OFS_X * con_chg_x, WE118_ROTA_OFS_Y );

	if (WET_SideCheck(we_sys, WeSysATNoGet(we_sys)) == SIDE_ENEMY){
		CATS_ObjectAnimeSeqSetCap(wk->hand_cap, 1);
	}
	else {
		CATS_ObjectAnimeSeqSetCap(wk->hand_cap, 0);
	}

		
	WazaTool_InitScaleRate(		// 拡縮
			&wk->hand_scale,
			WE118_FADE_SCALE_S,		
			WE118_FADE_SCALE_D,
			WE118_FADE_SCALE_E,
			WE118_FADE_SYNC	);

	if( con_chg_x >= 0 ){
		WazaTool_InitMoveOneSync( 
				&wk->hand_rota,
				WE118_ROTA_S,
				WE118_ROTA_E,
				WE118_ROTA_ONE_SYNC
				);
		wk->hand_rota_end = WE118_ROTA_S;
	}else{

		WazaTool_InitMoveOneSync( 
				&wk->hand_rota,
				WE118_ROTA_S_E,
				WE118_ROTA_E_E,
				WE118_ROTA_ONE_SYNC
				);
		wk->hand_rota_end = WE118_ROTA_S_E;

	}

	// タスク登録
	WEEffect_TCB_AddPriSet(wk->we_sys, We118_TCB, wk);
}

//-------------------------------------
//	
//	からみつく
//	
//=====================================
enum{
	WE132_OAM_MOVE,
	WE132_SHAKE,
	WE132_SCALE,
	WE132_END,
};
#define WE132_OAM_NUM	(4)

#define WE132_SCALE_S	( 10 )
#define WE132_SCALE_E	( 8 )
#define WE132_SCALE_D	( 10 )
#define WE132_SCALE_NUM	( 3 )
#define WE132_SCALE_SYNC	( 8 )
#define WE132_FLIP_ROTA	( FX_GET_ROTA_NUM(45) )
#define WE132_UNDER_MAT_OFS	(16)
#define WE132_GRASS_MAT_OFS	(10)		// この座標づつ上に表示してく

#define WE132_SHAKE_WIDTH	( 4 )
#define WE132_SHAKE_NUM		( 1 )
#define WE132_SHAKE_SYNC	( 1 )

#define WE132_GRASS_ADD_WAIT	( 4 )

// 草オブジェ
typedef struct{
	
	CATS_ACT_PTR cap;
	
	// 回転と拡大パラメータ
	WAZATOOL_CALCMOVE		scale;
	BOOL	flip;
	int		scale_num;
	int		next_scale_s;
	int		next_scale_e;
} TWE_132_GRASS;

// 132のオブジェ
typedef struct {
	WE_SYS_PTR	we_sys;
	CATS_SYS_PTR csp;
	CATS_RES_PTR crp;
	
	int	seq;
	int wait;
	int count;

	// 防御側
	SOFT_SPRITE*	df_ssp;
	s16				df_x;
	s16				df_y;
	WAZATOOL_CALCMOVE shake;
	

	// 草データ
	TWE_132_GRASS	grass[ WE132_OAM_NUM ];
	int grass_count;
} TWE_132_SYS;

static void TWE_132_GrassInit( TWE_132_GRASS* wk, CATS_ACT_PTR cap, s16 x, s16 y, BOOL flip )
{
	// 初期カ
	wk->cap = cap;
	WazaTool_InitScaleRate(
			&wk->scale,
			WE132_SCALE_S,
			WE132_SCALE_D,
			WE132_SCALE_E,
			WE132_SCALE_SYNC
			);
	wk->scale_num = WE132_SCALE_NUM;
	wk->next_scale_s = WE132_SCALE_E;
	wk->next_scale_e = WE132_SCALE_S;
	wk->flip		= flip;
	
	CATS_ObjectPosSetCap( wk->cap, x, y );
	CATS_ObjectPosSetCap( wk->cap, x, y );

	// ダブルアフィン
	CATS_ObjectAffineSetCap( wk->cap, CLACT_AFFINE_DOUBLE );
	
	CATS_ObjectPriSetCap( wk->cap, WAZAEFF_ACT_SOFTPRI );
	CATS_ObjectBGPriSetCap( wk->cap, WAZAEFF_ACT_BGPRI );

	if( flip ){
		// フリップさせる
		CATS_ObjectScaleSetCap( wk->cap, -1, 1 );
	}

	// 描画オフ
	CATS_ObjectEnableCap( wk->cap, FALSE );
}

static void TWE_132_GrassDelete( TWE_132_GRASS* wk )
{
	// OAM破棄
	CATS_ActorPointerDelete_S(wk->cap);
}

static void TWE_132_GrassDrawOn( TWE_132_GRASS* wk )
{
	// 描画オフ
	CATS_ObjectEnableCap( wk->cap, TRUE );
		
	// オートアニメさせる
	CATS_ObjectAutoAnimeSetCap( wk->cap, TRUE );
}

static BOOL TWE_132_GrassMove( TWE_132_GRASS* wk )
{
	BOOL check;
	f32	s_x, s_y;
	int tmp;

	// 計算部
	check = WazaTool_CalcScaleRate( &wk->scale );

	// 拡縮をscale_num回続ける
	if( check == TRUE ){

		WazaTool_CalcScaleRateToClactScale( &wk->scale, &s_x, &s_y );
		if( wk->flip ){
			CATS_ObjectScaleSetCap( wk->cap, -s_x, 1 );
		}else{
			CATS_ObjectScaleSetCap( wk->cap, s_x, 1 );
		}
	}else{
		if( wk->scale_num > 0 ){
			wk->scale_num --;

			WazaTool_InitScaleRate(
					&wk->scale,
					wk->next_scale_s,
					WE132_SCALE_D,
					wk->next_scale_e,
					WE132_SCALE_SYNC
					);
			tmp = wk->next_scale_s;
			wk->next_scale_s	= wk->next_scale_e;
			wk->next_scale_e	= tmp;
		}else{
			
			return FALSE;
		}
	}

	return TRUE;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	からみつく　TCB
 *
 *	@param	tcb
 *	@param	work 
 *
 *	@return
 *
 *
 */
//-----------------------------------------------------------------------------
static void We132_TCB( TCB_PTR tcb, void* work )
{
	TWE_132_SYS* wk = work;
	int i;
	BOOL check;
	
	switch( wk->seq ){
	case WE132_OAM_MOVE:
		if( wk->wait >= WE132_GRASS_ADD_WAIT ){
			// １つ登録
			wk->wait = 0;
			TWE_132_GrassDrawOn( &wk->grass[ wk->count ] );
			wk->count++;

			if( wk->count >= WE132_OAM_NUM ){
				wk->seq ++;
			}
		}
		wk->wait ++;
		break;
		
	case WE132_SHAKE:
		// ポケモンをシェイク
		if( WazaTool_CalcAndReflectShakeSsp( &wk->shake, wk->df_x, wk->df_y, wk->df_ssp ) == FALSE ){
			wk->seq++;
		}
		break;
		
	case WE132_SCALE:
		for( i = 0; i < WE132_OAM_NUM; i++ ){

			check = TWE_132_GrassMove( wk->grass + i );
		}
		if( check == FALSE ){
			wk->seq++;
		}
		break;

	case WE132_END:
		SoftSpriteParaSet( wk->df_ssp, SS_PARA_POS_X, wk->df_x );
		SoftSpriteParaSet( wk->df_ssp, SS_PARA_POS_Y, wk->df_y );

		for( i = 0; i < WE132_OAM_NUM; i++ ){
			TWE_132_GrassDelete( wk->grass + i );
		}

		// 終了
		WEEffect_TCB_Delete(wk->we_sys, tcb);
		sys_FreeMemoryEz(wk);
		return ;
	}

	// OAM描画
	CATS_Draw(wk->crp);	
}

//----------------------------------------------------------------------------
/**
 * @brief	からみつく用タスク
 *
 *	@param	we_sys	技エフェクトシステムワーク
 *	@param	csp		セルアクターツールシステム
 *	@param	crp		セルアクターリソースシステム
 *	@param	cap		セルアクターツールオブジェ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void WestSp_CAT_WE_132(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CATS_ACT_PTR cap)
{
	TWE_132_SYS* wk;
	int i;		// ループ用
	int df_client;
	int set_y;
	int flip_flg;
	TCATS_OBJECT_ADD_PARAM_S coap;
	
	wk = WET_ALLOC_MEMORY(we_sys, TWE_132_SYS);
	wk->we_sys	= we_sys;
	wk->csp		= csp;
	wk->crp		= crp;

	// ポケモンの配置からゆれる横方向を決定
	df_client = WeSysDFNoGet(we_sys); 

	// 座標は防御側を設定
	wk->df_ssp = WeSysSoftSpritePointerGet( wk->we_sys, df_client );
	wk->df_x	= SoftSpriteParaGet( wk->df_ssp, SS_PARA_POS_X );
	wk->df_y	= SoftSpriteParaGet( wk->df_ssp, SS_PARA_POS_Y );
	WazaTool_InitShake( 
			&wk->shake,
			WE132_SHAKE_WIDTH,
			0,
			WE132_SHAKE_SYNC,
			WE132_SHAKE_NUM
			);

	// 草オブジェ作成
	set_y = wk->df_y + WE132_UNDER_MAT_OFS;	// ポケモンの底辺の座標にする
	flip_flg = 0;
	coap   = WeSysCoapGet(wk->we_sys);
	for( i=0; i<WE132_OAM_NUM; i++ ){
		// ０個めは引数のcapを使用
		if( i == 0 ){
			
			TWE_132_GrassInit( &wk->grass[ i ], cap, wk->df_x, set_y, flip_flg );
		}else{
			
			TWE_132_GrassInit( &wk->grass[ i ], CATS_ObjectAdd_S(csp, crp, &coap), wk->df_x, set_y, flip_flg );
		}

		set_y -= WE132_GRASS_MAT_OFS;
		flip_flg ^= 1;
	}

	WEEffect_TCB_AddPriSet(wk->we_sys, We132_TCB, wk);
}


//-------------------------------------
//	
//	ほねブーメラン
//	
//=====================================
enum{
	WE155_AT_MOVE0,
	WE155_AT_MOVE0_1,
	WE155_BONE_AT_DF,
	WE155_BONE_DF_AT,
	WE155_AT_MOVE1,
	WE155_AT_MOVE2,
	WE155_END,
};

#define WE155_AT_MOVE_X		( -32 )
#define WE155_AT_MOVE_X_0	( -16 )
#define WE155_AT_MOVE_SYNC	( 4 )
#define WE155_AT_MOVE_SYNC_0	( 2 )

/*#define WE155_SHAKE_WIDTH	( 4 )
#define WE155_SHAKE_NUM		( 1 )
#define WE155_SHAKE_SYNC	( 1 )//*/

#define WE155_BONE_MOVE_ONE_SYNC	( 10 )
#define	WE155_BONE_MOVE_HEIGHT		( 32*FX32_ONE )

typedef struct{
	WE_SYS_PTR	we_sys;
	CATS_SYS_PTR csp;
	CATS_RES_PTR crp;
	int seq;
	
	// 攻撃側
	SOFT_SPRITE* at_ssp;
	s16	at_x;
	s16	at_y;
	WAZATOOL_CALCMOVE at_move;
	s32 vec_x;

/*	// 防御側
	WAZATOOL_CALCMOVE df_move;//*/
	SOFT_SPRITE* df_ssp;
	s16	df_x;
	s16	df_y;
	
	// 骨
	CATS_ACT_PTR	bone_obj;
	WAZATOOL_CALCMOVE bone_param1;
	WAZATOOL_CALCMOVE bone_param2;
} TWE155_SYS;

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ほねぶーめらん
 *
 *	@param	TCB_PTR tcb
 *	@param	work 
 *
 *	@return
 *
 *
 */
//-----------------------------------------------------------------------------
static void We155_TCB( TCB_PTR tcb, void* work )
{
	TWE155_SYS* wk = work;

	switch( wk->seq ){
	case WE155_AT_MOVE0:
		if( WazaTool_CalcStraightFx( &wk->at_move ) ){
			WazaTool_SetSspMatrix( &wk->at_move, wk->at_ssp, wk->at_x, wk->at_y );
		}else{
			WazaTool_InitStraightSyncFx( 
					&wk->at_move,
					wk->at_move.x, 0,
					0, 0,
					WE155_AT_MOVE_SYNC_0 );
			wk->seq++;
		}
		return;	// OAM描画しないため
		
	case WE155_AT_MOVE0_1:
		if( WazaTool_CalcStraightFx( &wk->at_move ) ){
			WazaTool_SetSspMatrix( &wk->at_move, wk->at_ssp, wk->at_x, wk->at_y );
		}else{
			SoftSpriteParaSet( wk->at_ssp, SS_PARA_POS_X, wk->at_x );
			SoftSpriteParaSet( wk->at_ssp, SS_PARA_POS_Y, wk->at_y );

			WazaTool_InitStraightSyncFx( 
					&wk->at_move,
					0, WE155_AT_MOVE_X * wk->vec_x,
					0, 0,
					WE155_AT_MOVE_SYNC );
			wk->seq++;
		}
		return;	// OAM描画しないため

	case WE155_BONE_AT_DF:
		// 骨動かす
		if( WazaTool_CalcAndReflectCurveFxCap( &wk->bone_param1, &wk->bone_param2, wk->bone_obj ) == FALSE ){

			WazaTool_InitCurveYFx( 
					&wk->bone_param1, &wk->bone_param2,
					wk->df_x, wk->at_x, 
					wk->df_y, wk->at_y,
					WE155_BONE_MOVE_ONE_SYNC,
					-WE155_BONE_MOVE_HEIGHT
					);
			wk->seq++;
		}
		break;
		
	case WE155_BONE_DF_AT:
		// ポケモンを動かす
//		WazaTool_CalcAndReflectShakeSsp( &wk->df_move, wk->df_x, wk->df_y, wk->df_ssp );

		// 骨を動かす
		if( WazaTool_CalcAndReflectCurveFxCap( &wk->bone_param1, &wk->bone_param2, wk->bone_obj ) == FALSE ){
/*			SoftSpriteParaSet( wk->df_ssp, SS_PARA_POS_X, wk->df_x );
			SoftSpriteParaSet( wk->df_ssp, SS_PARA_POS_Y, wk->df_y );//*/

			// 骨表示OFF
			CATS_ObjectEnableCap( wk->bone_obj, FALSE );
			wk->seq++;
		}
		
		break;
		
	case WE155_AT_MOVE1:
		if( WazaTool_CalcStraightFx( &wk->at_move ) ){
			WazaTool_SetSspMatrix( &wk->at_move, wk->at_ssp, wk->at_x, wk->at_y );
		}else{
			WazaTool_InitStraightSyncFx( 
					&wk->at_move,
					wk->at_move.x, 0,
					0, 0,
					WE155_AT_MOVE_SYNC );
			wk->seq++;
		}
		break;

	case WE155_AT_MOVE2:
		if( WazaTool_CalcStraightFx( &wk->at_move ) ){
			WazaTool_SetSspMatrix( &wk->at_move, wk->at_ssp, wk->at_x, wk->at_y );
		}else{
			SoftSpriteParaSet( wk->at_ssp, SS_PARA_POS_X, wk->at_x );
			SoftSpriteParaSet( wk->at_ssp, SS_PARA_POS_Y, wk->at_y );

			wk->seq++;
		}
		break;
		
	case WE155_END:
		CATS_ActorPointerDelete_S(wk->bone_obj);

		// 終了
		WEEffect_TCB_Delete(wk->we_sys, tcb);
		sys_FreeMemoryEz(wk);
		return ;
	}

	// OAM描画
	CATS_Draw(wk->crp);	
}

//----------------------------------------------------------------------------
/**
 * @brief	骨用タスク登録
 *
 *	@param	we_sys	技エフェクトシステムワーク
 *	@param	csp		セルアクターツールシステム
 *	@param	crp		セルアクターリソースシステム
 *	@param	cap		セルアクターツールオブジェ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void WestSp_CAT_WE_155(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CATS_ACT_PTR cap)
{
	TWE155_SYS* wk;

	wk = WET_ALLOC_MEMORY(we_sys, TWE155_SYS);
	wk->we_sys	= we_sys;
	wk->csp		= csp;
	wk->crp		= crp;

	wk->vec_x = WazaTool_VecChangeX( wk->we_sys, WeSysATNoGet(wk->we_sys) );

	// 攻撃側
	wk->at_ssp = WeSysSoftSpritePointerGet( wk->we_sys, WeSysATNoGet(we_sys) );
	wk->at_x	= SoftSpriteParaGet( wk->at_ssp, SS_PARA_POS_X );
	wk->at_y	= SoftSpriteParaGet( wk->at_ssp, SS_PARA_POS_Y );
	WazaTool_InitStraightSyncFx( 
			&wk->at_move,
			0, WE155_AT_MOVE_X_0 * wk->vec_x,
			0, 0,
			WE155_AT_MOVE_SYNC );

	// 防御側
	wk->df_ssp = WeSysSoftSpritePointerGet( wk->we_sys, WeSysDFNoGet(we_sys) );
	wk->df_x	= SoftSpriteParaGet( wk->df_ssp, SS_PARA_POS_X );
	wk->df_y	= SoftSpriteParaGet( wk->df_ssp, SS_PARA_POS_Y );
/*	WazaTool_InitShake( 
			&wk->df_move,
			WE155_SHAKE_WIDTH, 0,
			WE155_SHAKE_SYNC,
			WE155_SHAKE_NUM );//*/

	// 骨
	wk->bone_obj = cap;
	CATS_ObjectAutoAnimeSetCap( wk->bone_obj, TRUE );
	CATS_ObjectPriSetCap( wk->bone_obj, WAZAEFF_ACT_SOFTPRI );
	CATS_ObjectBGPriSetCap( wk->bone_obj, WAZAEFF_ACT_BGPRI );
	WazaTool_InitCurveYFx( 
			&wk->bone_param1, &wk->bone_param2,
			wk->at_x, wk->df_x, 
			wk->at_y, wk->df_y,
			WE155_BONE_MOVE_ONE_SYNC,
			WE155_BONE_MOVE_HEIGHT
			);

	WEEffect_TCB_AddPriSet(wk->we_sys, We155_TCB, wk);
}

//-------------------------------------
//	
//	だましうち
//	
//=====================================
enum{
	WE185_AT_FADE_OUT,
	WE185_DF_DAMAGE,
	WE185_AT_FADE_IN,
	WE185_END,
};
#define WE185_ROTA_NUM	( 2 )
#define WE185_ROTA_SYNC	( 16 )
#define WE185_FADE_ALPHA_S	(16)
#define WE185_FADE_ALPHA_E	(0)
#define WE185_FADE_ALPHA_SYNC	( 32 )

#define WE185_DF_SHAKE_WAIT	( 16 )

/*#define WE185_SHAKE_WIDTH	( 4 )
#define WE185_SHAKE_NUM		( 1 )
#define WE185_SHAKE_SYNC	( 1 )//*/

typedef struct {
	WE_SYS_PTR	we_sys;
	CATS_RES_PTR crp;
	int seq;
	int wait;

	// 攻撃側
	SOFT_SPRITE* at_ssp;
	CATS_ACT_PTR at_cap;
	s16	at_x;
	s16	at_y;
	WAZATOOL_CALCMOVE at_move;
	WAZATOOL_ALPHA_FADE	at_alpha;

	s16 cap_ofs_y;

/*	// 防御側
	SOFT_SPRITE* df_ssp;
	s16	df_x;
	s16	df_y;
	WAZATOOL_CALCMOVE df_move;//*/

} TWE185_SYS;

//----------------------------------------------------------------------------
/**
 *
 *	@brief	だまし討ち
 *
 *	@param	tcb
 *	@param	work 
 *
 *	@return
 *
 *
 */
//-----------------------------------------------------------------------------
static void We185_TCB( TCB_PTR tcb, void* work )
{
	TWE185_SYS* wk = work;
	
	switch( wk->seq ){
	case WE185_AT_FADE_OUT:
		// アルファは勝手におわる
		
		// 回転計算
		if( WazaTool_CalcAndReflectRotaFxCap( &wk->at_move, wk->at_x, wk->at_y - wk->cap_ofs_y, wk->at_cap ) == FALSE ){
			wk->seq++;
			wk->wait = WE185_DF_SHAKE_WAIT;
		}
		break;
		
	case WE185_DF_DAMAGE:
		wk->wait --;
		if( wk->wait < 0 ){
			wk->seq++;

			// フェードイン準備
			WazaTool_StartAlphaFade(
					&wk->at_alpha,
					WE185_FADE_ALPHA_E, WE185_FADE_ALPHA_S,
					16 - WE185_FADE_ALPHA_E, 16 - WE185_FADE_ALPHA_S,  
					WE185_FADE_ALPHA_SYNC
					);
		}
		break;

	case WE185_AT_FADE_IN:
		// alpah
		if( WazaTool_EndCheckAlphaFade( &wk->at_alpha ) ){
			CATS_ObjectEnableCap( wk->at_cap, TRUE );
			SoftSpriteParaSet( wk->at_ssp, SS_PARA_VANISH, FALSE );
			wk->seq++;
		}
		break;

	case WE185_END:
		// 終了
		WEEffect_TCB_Delete(wk->we_sys, tcb);
		sys_FreeMemoryEz(wk);
		return ;
	}
	// OAM描画
	CATS_Draw(wk->crp);	
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	だましうち
 *
 *	@param	we_sys 
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void WestSp_WE_185( WE_SYS_PTR we_sys )
{
	TWE185_SYS* wk;
	int vec_x;

	wk = WET_ALLOC_MEMORY(we_sys, TWE185_SYS);
	wk->we_sys	= we_sys;
	wk->crp		= WeSysPokeCrpGet(wk->we_sys);

	vec_x = WazaTool_VecChangeX( wk->we_sys, WeSysATNoGet(wk->we_sys) );

	// 攻撃側
	wk->at_ssp = WeSysSoftSpritePointerGet( wk->we_sys, WeSysATNoGet(we_sys) );
	wk->at_x	= SoftSpriteParaGet( wk->at_ssp, SS_PARA_POS_X );
	wk->at_y	= SoftSpriteParaGet( wk->at_ssp, SS_PARA_POS_Y );
	wk->cap_ofs_y = SoftSpriteParaGet( wk->at_ssp, SS_PARA_SHADOW_HEIGHT );
	wk->at_y	-= WAZATOOL_DEF_ROTA_W_Y_INT;
	wk->at_cap	= WeSysPokeCapGet(wk->we_sys, 0);
	CATS_ObjectObjModeSetCap( wk->at_cap, GX_OAM_MODE_XLU );
	SoftSpriteParaSet( wk->at_ssp, SS_PARA_VANISH, TRUE );
	WazaTool_MakeDefRota( 
			&wk->at_move,
			WE185_ROTA_NUM,
			WE185_ROTA_SYNC	);
	WET_DefaultBlendSet( wk->we_sys,
			WE185_FADE_ALPHA_S, 16 - WE185_FADE_ALPHA_S );
	WazaTool_StartAlphaFade(
			&wk->at_alpha,
			WE185_FADE_ALPHA_S, WE185_FADE_ALPHA_E,
			16 - WE185_FADE_ALPHA_S, 16 - WE185_FADE_ALPHA_E, 
			WE185_FADE_ALPHA_SYNC
			);
	wk->at_move.work[2] *= vec_x;

/*	// 防御側
	wk->df_ssp = WeSysSoftSpritePointerGet( wk->we_sys, WeSysDFNoGet(we_sys) );
	wk->df_x	= SoftSpriteParaGet( wk->df_ssp, SS_PARA_POS_X );
	wk->df_y	= SoftSpriteParaGet( wk->df_ssp, SS_PARA_POS_Y );
	WazaTool_InitShake( 
			&wk->df_move,
			WE185_SHAKE_WIDTH, 0,
			WE185_SHAKE_SYNC,
			WE185_SHAKE_NUM );//*/

	WEEffect_TCB_AddPriSet(wk->we_sys, We185_TCB, wk);

	// OAM描画
	CATS_Draw(wk->crp);	
}

//-------------------------------------
//	
//	怖い顔
//	
//=====================================
enum{
	WE184_FACE_MOVE,
	WE184_FACE_FADEOUT,
	WE184_FACE_END,
};

enum{
	WE184_MOVE,
	WE184_END,
};

enum{
	WE184_POKE_SCALE_UP,
	WE184_POKE_SCALE_DOWN,
	WE184_POKE_END,
};

/*#define WE184_SCALE_RATE_S	( 10 )
#define WE184_SCALE_RATE_E	( 15 )
#define WE184_SCALE_RATE_D	( 10 )
#define WE184_SCALE_SYNC	( 12 )
#define WE184_MOVE_WIDTH	( 64 )
#define WE184_MOVE_HEIGH	( -16 )
#define WE184_MOVE_HEIGH_MY	( -48 )
#define WE184_MOVE_SYNC		( 32 )		// 顔が動くしんく
#define WE184_MOVE_X_OFS	( 32 )	//*/

#define WE184_SCALE_RATE_S	( 10 )
#define WE184_SCALE_RATE_E	( 15 )
#define WE184_SCALE_RATE_D	( 10 )
#define WE184_SCALE_SYNC	( 12 )

#define WE184_MOVE_WIDTH	( 0 )
#define WE184_MOVE_HEIGH	( -8 )
#define WE184_MOVE_HEIGH_MY	( -24 )
#define WE184_MOVE_SYNC		( 32 )		// 顔が動くしんく
#define WE184_MOVE_X_OFS	( 32 )	//*/

#define WE184_FACE_SCALE_RATE_S	( 5 )
#define WE184_FACE_SCALE_RATE_E	( 12 )
#define WE184_FACE_SCALE_RATE_D	( 10 )

#define WE184_FADE_OUT_SYNC	( 8 )

typedef struct {
	WE_SYS_PTR	we_sys;
	CATS_SYS_PTR csp;
	CATS_RES_PTR crp;
	int seq;
	
	// 攻撃側
	SOFT_SPRITE* at_ssp;
	WAZATOOL_CALCMOVE at_scale;
	int poke_seq;
	
	// 怖い顔
	CATS_ACT_PTR face_obj;
	int face_seq;
	WAZATOOL_CALCMOVE face_scale;
	WAZATOOL_CALCMOVE face_move;
	WAZATOOL_ALPHA_FADE face_alpha;
	s16	face_x;
	s16	face_y;
	
} TWE184_SYS;

static BOOL We184_PokeMove( TWE184_SYS* wk )
{
	BOOL ret = FALSE;
	
	switch( wk->poke_seq ){
	case WE184_POKE_SCALE_UP:
		if( WazaTool_CalcScaleRate( &wk->at_scale ) ){
			// 拡縮
			SoftSpriteParaSet( wk->at_ssp, SS_PARA_AFF_Y, wk->at_scale.y );
		}else{
			wk->poke_seq++;
			WazaTool_InitScaleRate( 
					&wk->at_scale,
					WE184_SCALE_RATE_E,
					WE184_SCALE_RATE_D,
					WE184_SCALE_RATE_S,
					WE184_SCALE_SYNC );
		}
		break;
		
	case WE184_POKE_SCALE_DOWN:
		if( WazaTool_CalcScaleRate( &wk->at_scale ) ){
			// 拡縮
			SoftSpriteParaSet( wk->at_ssp, SS_PARA_AFF_Y, wk->at_scale.y );
		}else{
			SoftSpriteParaSet( wk->at_ssp, SS_PARA_AFF_Y, 0x100 );
			wk->poke_seq++;
		}
		break;

	case WE184_POKE_END:
		ret = TRUE;		
		break;
	}

	return ret;
}

static BOOL We184_FaceMove( TWE184_SYS* wk )
{
	BOOL ret = FALSE;
	BOOL check;
	
	switch( wk->face_seq ){
	case WE184_FACE_MOVE:
		// 計算部
		// 全て同じフレームで動く
		WazaTool_CalcAndReflectScaleRateCap( &wk->face_scale, wk->face_obj );
		check = WazaTool_CalcStraightFx( &wk->face_move );

		if( check ){

			// 座標移動
			WazaTool_SetCapMatrix( &wk->face_move, wk->face_obj, wk->face_x, wk->face_y );
		}else{
			wk->face_seq++;
			WazaTool_StartAlphaFade( 
					&wk->face_alpha,
					16, 0,
					14,16,
					WE184_FADE_OUT_SYNC	);
		}
		break;

	case WE184_FACE_FADEOUT:
		if( WazaTool_EndCheckAlphaFade( &wk->face_alpha ) ){
			CATS_ObjectEnableCap( wk->face_obj, FALSE );
			wk->face_seq++;
		}
		break;

	case WE184_FACE_END:
		ret = TRUE;
		break;
	}

	return ret;
}

static void We184_TCB( TCB_PTR tcb, void* work )
{
	TWE184_SYS* wk = work;
	
	switch( wk->seq ){
	case WE184_MOVE:
		We184_PokeMove( wk );
		if( We184_FaceMove( wk ) ){
			wk->seq++;
		}
		break;
		
	case WE184_END:
		CATS_ActorPointerDelete_S(wk->face_obj);
		// 終了
		WEEffect_TCB_Delete(wk->we_sys, tcb);
		sys_FreeMemoryEz(wk);
		return;
	}

	// OAM描画
	CATS_Draw(wk->crp);	
}

//----------------------------------------------------------------------------
/**
 * @brief	怖い顔用タスク登録
 *
 *	@param	we_sys	技エフェクトシステムワーク
 *	@param	csp		セルアクターツールシステム
 *	@param	crp		セルアクターリソースシステム
 *	@param	cap		セルアクターツールオブジェ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void WestSp_CAT_WE_184(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CATS_ACT_PTR cap)
{
	TWE184_SYS* wk;
	int vec_x;
	int vec_y;
	s16	at_x;
	s16	at_y;
	int move_y;

	wk = WET_ALLOC_MEMORY(we_sys, TWE184_SYS);
	wk->we_sys	= we_sys;
	wk->csp		= csp;
	wk->crp		= crp;

	vec_x = WazaTool_VecChangeX( wk->we_sys, WeSysATNoGet(wk->we_sys) );
	vec_y = WazaTool_VecChangeY( wk->we_sys, WeSysATNoGet(wk->we_sys) );

	// 攻撃側
	wk->at_ssp = WeSysSoftSpritePointerGet( wk->we_sys, WeSysATNoGet(we_sys) );
	at_x	= SoftSpriteParaGet( wk->at_ssp, SS_PARA_POS_X );
	at_y	= SoftSpriteParaGet( wk->at_ssp, SS_PARA_POS_Y );
	WazaTool_InitScaleRate( 
			&wk->at_scale,
			WE184_SCALE_RATE_S,
			WE184_SCALE_RATE_D,
			WE184_SCALE_RATE_E,
			WE184_SCALE_SYNC );


	// かお
	wk->face_obj = cap;
	CATS_ObjectAutoAnimeSetCap( wk->face_obj, TRUE );
	CATS_ObjectAffineSetCap( wk->face_obj, CLACT_AFFINE_DOUBLE );
	CATS_ObjectObjModeSetCap( wk->face_obj, GX_OAM_MODE_XLU );
	CATS_ObjectPriSetCap( wk->face_obj, WAZAEFF_ACT_SOFTPRI );
	CATS_ObjectBGPriSetCap( wk->face_obj, WAZAEFF_ACT_BGPRI );
	wk->face_x	= at_x + (WE184_MOVE_X_OFS * vec_x);
	wk->face_y	= at_y;

	if( vec_y < 0 ){
		move_y = WE184_MOVE_HEIGH;
	}else{
		move_y = WE184_MOVE_HEIGH_MY;
	}

	
	WazaTool_InitStraightSyncFx( 
			&wk->face_move,
			0, WE184_MOVE_WIDTH * vec_x, 
			0, move_y * vec_y,
			WE184_MOVE_SYNC );
	WazaTool_InitScaleRate( 
			&wk->face_scale,
			WE184_FACE_SCALE_RATE_S,
			WE184_FACE_SCALE_RATE_D,
			WE184_FACE_SCALE_RATE_E,
			WE184_MOVE_SYNC );
//	WET_DefaultBlendSet(wk->we_sys, 31, 26 );

	G2_SetBlendAlpha( GX_BLEND_PLANEMASK_NONE,
			GX_BLEND_ALL, 31, 26 );	

	WEEffect_TCB_AddPriSet(wk->we_sys, We184_TCB, wk);
}



//-------------------------------------
//	
//	みやぶる
//	
//=====================================
enum{
	WE193_MOVE_INIT,
	WE193_MOVE_MAIN,
	WE193_POKE_FADE_OUT,
	WE193_POKE_FADE_IN,
	WE193_END,
};

#define WE193_MOVE_WIDTH	( 80 )
#define WE193_MOVE_HEIGHT	( 80 )
#define WE193_MOVE_SYNC		( 8 )
#define WE193_MOVE_COUNT	( 6 )
#define WE193_MOVE_WAIT		( 4 )

#define WE193_FADEOUT_ALPHA_SYNC	( 16 )
#define WE193_POKE_FADE_S	( 0 )
#define WE193_POKE_FADE_E	( 10 )
#define WE193_POKE_FADE_COLOR	( GX_RGB( 31,31,31 ) )
#define WE193_POKE_FADE_WAIT	(0)

typedef struct {
	WE_SYS_PTR	we_sys;
	CATS_SYS_PTR csp;
	CATS_RES_PTR crp;
	int seq;
	
	// 防御側
	SOFT_SPRITE* df_ssp;
	
	// むしめがね
	CATS_ACT_PTR cap;
	WAZATOOL_CALCMOVE cap_move;
	WAZATOOL_ALPHA_FADE cap_alpha;
	s16	cap_x;
	s16	cap_y;
	int cap_count;
	int cap_wait;
	
} TWE193_SYS;

static void We193_InitCap( TWE193_SYS* wk )
{
	switch( wk->cap_count ){
	case 0:
		WazaTool_InitStraightSyncFx( 
				&wk->cap_move, 
				0, WE193_MOVE_WIDTH / 2,
				0, WE193_MOVE_HEIGHT / 2,
				WE193_MOVE_SYNC );
		break;
	case 1:
		WazaTool_InitStraightSyncFx( 
				&wk->cap_move, 
				0, 0,
				0, -WE193_MOVE_HEIGHT,
				WE193_MOVE_SYNC );
		break;
	case 2:
		WazaTool_InitStraightSyncFx( 
				&wk->cap_move, 
				0, -WE193_MOVE_WIDTH,
				0, WE193_MOVE_HEIGHT,
				WE193_MOVE_SYNC );
		break;
	case 3:
		WazaTool_InitStraightSyncFx( 
				&wk->cap_move, 
				0, 0,
				0, -WE193_MOVE_HEIGHT,
				WE193_MOVE_SYNC );
		break;
	case 4:
		WazaTool_InitStraightSyncFx( 
				&wk->cap_move, 
				0, WE193_MOVE_WIDTH,
				0, WE193_MOVE_HEIGHT,
				WE193_MOVE_SYNC );
		break;
	case 5:
		WazaTool_InitStraightSyncFx( 
				&wk->cap_move, 
				0, -WE193_MOVE_WIDTH / 2,
				0, -WE193_MOVE_HEIGHT / 2,
				WE193_MOVE_SYNC );
		break;
	default:
		GF_ASSERT(0);
		break;
	}
}

static void We193_TCB( TCB_PTR tcb, void* work )
{
	TWE193_SYS* wk = work;

	switch( wk->seq ){
	case WE193_MOVE_INIT:
		// 初期化処理
		wk->cap_wait ++;
		if( wk->cap_wait > WE193_MOVE_WAIT ){
			We193_InitCap( wk );
			wk->seq ++;
			wk->cap_wait = 0;
		}
		break;
		
	case WE193_MOVE_MAIN:
		// 計算部
		if( WazaTool_CalcStraightFx( &wk->cap_move ) ){
			WazaTool_SetCapMatrix( &wk->cap_move, wk->cap, wk->cap_x, wk->cap_y );
		}else{

			wk->cap_count ++;
			if( wk->cap_count < WE193_MOVE_COUNT ){
				wk->seq = WE193_MOVE_INIT;

				// 現在位置を保存
				wk->cap_x += wk->cap_move.x;
				wk->cap_y += wk->cap_move.y;
			}else{
				
				wk->seq ++;
				// フェードアウト設定
				CATS_ObjectObjModeSetCap( wk->cap, GX_OAM_MODE_XLU );
				WazaTool_StartAlphaFade( 
						&wk->cap_alpha,
						16, 0,
						0, 16,
						WE193_FADEOUT_ALPHA_SYNC );
				
				// パレットフェード
				SoftSpritePalFadeSet( wk->df_ssp,
						WE193_POKE_FADE_S, WE193_POKE_FADE_E,
						WE193_POKE_FADE_WAIT,
						WE193_POKE_FADE_COLOR );
			}
		}
		break;
		
	case WE193_POKE_FADE_OUT:
		if( WazaTool_EndCheckAlphaFade( &wk->cap_alpha ) ){
			CATS_ObjectEnableCap( wk->cap, FALSE );
		}
		if( SoftSpritePalFadeExist( wk->df_ssp ) == FALSE ){
			wk->seq++;
			// パレットフェード
			SoftSpritePalFadeSet( wk->df_ssp,
					WE193_POKE_FADE_E, WE193_POKE_FADE_S,
					WE193_POKE_FADE_WAIT,
					WE193_POKE_FADE_COLOR );
		}
		break;
		
	case WE193_POKE_FADE_IN:
		if( SoftSpritePalFadeExist( wk->df_ssp ) == FALSE ){
			wk->seq++;
		}
		break;
		
	case WE193_END:
		CATS_ActorPointerDelete_S(wk->cap);
		// 終了
		WEEffect_TCB_Delete(wk->we_sys, tcb);
		sys_FreeMemoryEz(wk);
		return;
	}

	// OAM描画
	CATS_Draw(wk->crp);	
}

//----------------------------------------------------------------------------
/**
 * @brief	みやぶる用タスク登録
 *
 *	@param	we_sys	技エフェクトシステムワーク
 *	@param	csp		セルアクターツールシステム
 *	@param	crp		セルアクターリソースシステム
 *	@param	cap		セルアクターツールオブジェ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void WestSp_CAT_WE_193(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CATS_ACT_PTR cap)
{
	TWE193_SYS* wk;

	wk = WET_ALLOC_MEMORY(we_sys, TWE193_SYS);
	wk->we_sys	= we_sys;
	wk->csp		= csp;
	wk->crp		= crp;

	// 防御側
	wk->df_ssp = WeSysSoftSpritePointerGet( wk->we_sys, WeSysDFNoGet(we_sys) );


	// 虫眼鏡
	wk->cap = cap;
	CATS_ObjectPriSetCap( wk->cap, WAZAEFF_ACT_SOFTPRI );
	CATS_ObjectBGPriSetCap( wk->cap, WAZAEFF_ACT_BGPRI );
	CATS_ObjectPosGetCap( wk->cap, &wk->cap_x, &wk->cap_y );


	WEEffect_TCB_AddPriSet(wk->we_sys, We193_TCB, wk);
}

//-------------------------------------
//	
//	ロックオン
//	
//=====================================
enum{
	WE199_MOVE_INIT,
	WE199_MOVE_MAIN,
	WE199_ANIME_ACT,
	WE199_FLASH_IN,
	WE199_FLASH_OUT,
	WE199_SWITCH_ACT,
	WE199_END,
};

#define WE199_MOVE_WAIT_INIT	( -16 )
#define WE199_MOVE_WIDTH	( 80 )
#define WE199_MOVE_HEIGHT	( 80 )
#define WE199_MOVE_SYNC		( 4 )
#define WE199_MOVE_COUNT	( 4 )
#define WE199_MOVE_WAIT		( 1 )

#define WE199_FLASH_SYNC	( -8 )

#define WE199_FLASH_WAIT	( 8 )

#define WE199_SWITCH_WAIT	( 4 )
#define WE199_SWITCH_COUNT	( 4 )


typedef struct {
	WE_SYS_PTR	we_sys;
	CATS_SYS_PTR csp;
	CATS_RES_PTR crp;
	int seq;
	
	// 防御側
	SOFT_SPRITE* df_ssp;

	// ポケモンフェード用
	SOFT_SPRITE* fade_ssp[4];
	
	// ロックオン
	CATS_ACT_PTR cap;
	WAZATOOL_CALCMOVE cap_move;
	s16	cap_x;
	s16	cap_y;
	int cap_count;
	int cap_wait;
	int cap_vanish;
} TWE199_SYS;

static void We199_InitCap( TWE199_SYS* wk )
{
	switch( wk->cap_count ){
	case 0:
		WazaTool_InitStraightSyncFx( 
				&wk->cap_move, 
				0, WE199_MOVE_WIDTH,
				0, WE199_MOVE_HEIGHT,
				WE199_MOVE_SYNC );
		break;
	case 1:
		WazaTool_InitStraightSyncFx( 
				&wk->cap_move, 
				0, 0,
				0, -WE199_MOVE_HEIGHT,
				WE199_MOVE_SYNC );
		break;
	case 2:
		WazaTool_InitStraightSyncFx( 
				&wk->cap_move, 
				0, -WE199_MOVE_WIDTH,
				0, WE199_MOVE_HEIGHT,
				WE199_MOVE_SYNC );
		break;
	case 3:
		WazaTool_InitStraightSyncFx( 
				&wk->cap_move, 
				0, WE199_MOVE_WIDTH/2,
				0, -WE199_MOVE_HEIGHT/2,
				WE199_MOVE_SYNC );
		break;
	default:
		GF_ASSERT(0);
		break;
	}
}

static void We199_TCB( TCB_PTR tcb, void* work )
{
	TWE199_SYS* wk = work;
	int i;

	switch( wk->seq ){
	case WE199_MOVE_INIT:
		// 初期化処理
		wk->cap_wait ++;
		if( wk->cap_wait > WE199_MOVE_WAIT ){
			We199_InitCap( wk );
			wk->seq ++;
			wk->cap_wait = 0;
		}
		break;
		
	case WE199_MOVE_MAIN:
		// 計算部
		if( WazaTool_CalcStraightFx( &wk->cap_move ) ){
			WazaTool_SetCapMatrix( &wk->cap_move, wk->cap, wk->cap_x, wk->cap_y );
		}else{

			wk->cap_count ++;
			if( wk->cap_count < WE199_MOVE_COUNT ){
				wk->seq = WE199_MOVE_INIT;

				// 現在位置を保存
				wk->cap_x += wk->cap_move.x;
				wk->cap_y += wk->cap_move.y;
			}else{
				
				wk->seq ++;
				wk->cap_wait = WE199_FLASH_WAIT;

				// オートアニメ
				// アニメシーケンス変更
				CATS_ObjectAnimeSeqSetCap( wk->cap, 1 );
				CATS_ObjectAutoAnimeSetCap( wk->cap, TRUE );
			}
		}
		break;

	case WE199_ANIME_ACT:
		wk->cap_wait --;
		if( wk->cap_wait < 0 ){
			wk->seq++;

			PaletteFadeReq(WeSysPFDGet(wk->we_sys), PF_BIT_MAIN_BG, BT_HaikeiFadeBit( wk->we_sys ), WE199_FLASH_SYNC, 0, 16, 0xffff);
			for( i=0; i<4; i++ ){
				if( wk->fade_ssp[i] ){
					SoftSpritePalFadeSet( wk->fade_ssp[i], 14, 16, 0, 0xffff );
				}
			}
/*			// ブライトネス開始
			WIPE_SYS_Start( 
					WIPE_PATTERN_M,
					WIPE_TYPE_FADEOUT,
					WIPE_TYPE_FADEOUT,
					WIPE_FADE_WHITE,
					WE199_FLASH_SYNC,
					1, WeSysHeapAreaGet(wk->we_sys) );
//*/
		}
		break;
		
	case WE199_FLASH_IN:
		if( PaletteFadeCheck(WeSysPFDGet(wk->we_sys)) == 0 ){
			wk->seq++;
/*
			// ブライトネス開始
			WIPE_SYS_Start( 
					WIPE_PATTERN_M,
					WIPE_TYPE_FADEIN,
					WIPE_TYPE_FADEIN,
					WIPE_FADE_WHITE,
					WE199_FLASH_SYNC,
					1, WeSysHeapAreaGet(wk->we_sys) );
//*/
			
			PaletteFadeReq(WeSysPFDGet(wk->we_sys), PF_BIT_MAIN_BG, BT_HaikeiFadeBit( wk->we_sys ), WE199_FLASH_SYNC, 16, 0, 0xffff);
			for( i=0; i<4; i++ ){
				if( wk->fade_ssp[i] ){
					SoftSpritePalFadeSet( wk->fade_ssp[i], 2, 0, 0, 0xffff );
					
				}
			}
		}
		break;
		
	case WE199_FLASH_OUT:
		if( PaletteFadeCheck(WeSysPFDGet(wk->we_sys)) == 0 ){
			wk->seq++;

			wk->cap_wait = WE199_SWITCH_WAIT;
			wk->cap_count = WE199_SWITCH_COUNT;
			wk->cap_vanish = 0;
		}
		break;

	case WE199_SWITCH_ACT:
		wk->cap_wait --;
		if( wk->cap_wait < 0 ){
			wk->cap_wait = WE199_SWITCH_WAIT;
			wk->cap_count --;
			if( wk->cap_count < 0 ){	// 回数点滅したら終了
				wk->seq ++;
			}else{
				CATS_ObjectEnableCap( wk->cap, wk->cap_vanish );
				wk->cap_vanish ^= 1;
			}
		}
		break;
		
	case WE199_END:
		CATS_ActorPointerDelete_S(wk->cap);
		// 終了
		WEEffect_TCB_Delete(wk->we_sys, tcb);
		sys_FreeMemoryEz(wk);
		return;
	}

	// OAM描画
	CATS_Draw(wk->crp);	
}

//----------------------------------------------------------------------------
/**
 * @brief	ロックオン用タスク登録
 *
 *	@param	we_sys	技エフェクトシステムワーク
 *	@param	csp		セルアクターツールシステム
 *	@param	crp		セルアクターリソースシステム
 *	@param	cap		セルアクターツールオブジェ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void WestSp_CAT_WE_199(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CATS_ACT_PTR cap)
{
	TWE199_SYS* wk;
	int i;

	wk = WET_ALLOC_MEMORY(we_sys, TWE199_SYS);
	wk->we_sys	= we_sys;
	wk->csp		= csp;
	wk->crp		= crp;

	// 防御側
	wk->df_ssp = WeSysSoftSpritePointerGet( wk->we_sys, WeSysDFNoGet(we_sys) );

	for( i=0; i<4; i++ ){
		wk->fade_ssp[i] = WeSysSoftSpritePointerGet( wk->we_sys, i );
	}

	// 虫眼鏡
	wk->cap = cap;
	CATS_ObjectPriSetCap( wk->cap, WAZAEFF_ACT_SOFTPRI );
	CATS_ObjectBGPriSetCap( wk->cap, WAZAEFF_ACT_BGPRI );
	CATS_ObjectPosGetCap( wk->cap, &wk->cap_x, &wk->cap_y );
	wk->cap_x -= WE199_MOVE_WIDTH / 2;
	wk->cap_y -= WE199_MOVE_HEIGHT / 2;
	CATS_ObjectPosSetCap( wk->cap, wk->cap_x, wk->cap_y );
	CATS_ObjectObjModeSetCap( wk->cap, GX_OAM_MODE_XLU );
	wk->cap_wait = WE199_MOVE_WAIT_INIT;

	// α設定
//	WET_DefaultBlendSet(wk->we_sys, 31, 26 );

	G2_SetBlendAlpha( GX_BLEND_PLANEMASK_NONE,
			GX_BLEND_ALL, 31, 26 );	
	


	WEEffect_TCB_AddPriSet(wk->we_sys, We199_TCB, wk);
}

//-------------------------------------
//	
//	あまえる
//	
//=====================================
enum{
	WE204_ROTA_OUT,
	WE204_ROTA_DOWN,
	WE204_ROTA_IN,
	WE204_ROTA_END,
};
enum{
	WE204_MOVE,
	WE204_END,
};
#define WE204_ROTA_E		( FX_GET_ROTA_NUM( 15 ) )
#define WE204_ROTA_SYNC		( 3 )
#define WE204_ROTA_C_Y		( 50 )
#define WE204_DOWN_HEIGHT	( 2 )
#define WE204_DOWN_SYNC		( 2 )
#define WE204_DOWN_WAIT		( 0 )

#define WE204_MOVE_NUM		(4)

#define WE204_MATRIX_Y		( 40 )
#define WE204_MATRIXOFS_Y	( -40 )

#define WE204_ROTA_OFS_X	( 16 )

// ワーク
typedef struct{
	int	seq;
	WE_SYS_PTR	we_sys;			
	
	// ソフトスプライトデータ
	SOFT_SPRITE* at_ssp;
	s16 at_x;
	s16 at_y;

	// 回転計算用ワーク
	WAZATOOL_CALCMOVE_ONE	calc_rota;
	WAZATOOL_CALCMOVE		calc_move;
	int count;
	int rota_seq;
	int wait;
	int flip_flg;

} TWE204_SYS;

static void TWe204_RotaInit( TWE204_SYS* wk, BOOL flip )
{
	fx32 width;

	WazaTool_InitMoveOneSyncFx( 
			&wk->calc_rota,
			0,
			WE204_ROTA_E,
			WE204_ROTA_SYNC	);

	// 回転方向
	// 回転軸設定
	if( flip ){
		wk->calc_rota.work[1] *= -1;
		SoftSpriteParaSet( wk->at_ssp, SS_PARA_ROT_CX, WE204_ROTA_OFS_X );
	}else{
		SoftSpriteParaSet( wk->at_ssp, SS_PARA_ROT_CX, -WE204_ROTA_OFS_X );
	}
	
	wk->rota_seq = 0;
	wk->wait = WE204_DOWN_WAIT;
}

static BOOL TWe204_RotaMove( TWE204_SYS* wk )
{
	BOOL ret = FALSE;
	
	switch( wk->rota_seq ){
	case WE204_ROTA_OUT:

		WazaTool_CalcMoveOneFx( &wk->calc_rota );
		SoftSpriteParaSet( wk->at_ssp, SS_PARA_ROT_Z, wk->calc_rota.num );

		wk->wait --;
		if( wk->wait < 0 ){
			wk->rota_seq++;

			WazaTool_InitStraightSyncFx(
					&wk->calc_move,
					wk->at_x, wk->at_x,
					wk->at_y, wk->at_y + WE204_DOWN_HEIGHT,
					WE204_DOWN_SYNC
					);
		}
		break;

	case WE204_ROTA_DOWN:
		if( WazaTool_CalcMoveOneFx( &wk->calc_rota ) ){
			SoftSpriteParaSet( wk->at_ssp, SS_PARA_ROT_Z, wk->calc_rota.num );
		}
		
		if( WazaTool_CalcAndReflectStraightFxSsp( &wk->calc_move, wk->at_ssp ) == FALSE ){
			wk->rota_seq++;
			WazaTool_InitMoveOneSyncFx( 
					&wk->calc_rota,
					wk->calc_rota.num,
					0,
					WE204_ROTA_SYNC	);

			WazaTool_InitStraightSyncFx(
					&wk->calc_move,
					wk->at_x, wk->at_x,
					wk->at_y + WE204_DOWN_HEIGHT, wk->at_y,
					WE204_DOWN_SYNC
					);
		}
		break;

	case WE204_ROTA_IN:

		WazaTool_CalcAndReflectStraightFxSsp( &wk->calc_move, wk->at_ssp );
		
		if( WazaTool_CalcMoveOneFx( &wk->calc_rota ) ){
			SoftSpriteParaSet( wk->at_ssp, SS_PARA_ROT_Z, wk->calc_rota.num );
		}else{
			SoftSpriteParaSet( wk->at_ssp, SS_PARA_POS_X, wk->at_x );
			SoftSpriteParaSet( wk->at_ssp, SS_PARA_POS_Y, wk->at_y );
			SoftSpriteParaSet( wk->at_ssp, SS_PARA_ROT_Z, 0 );
			wk->rota_seq++;
		}
		break;
	case WE204_ROTA_END:
		ret = TRUE;
		break;
	}

	return ret;
}

static void We204_TCB( TCB_PTR tcb, void* work )
{
	TWE204_SYS* wk = work;

	switch( wk->seq ){
	case WE204_MOVE:
		if( TWe204_RotaMove( wk ) ){

			wk->count ++;
			if( wk->count < WE204_MOVE_NUM ){
				wk->flip_flg ^= 1;
				TWe204_RotaInit( wk, wk->flip_flg );
				TWe204_RotaMove( wk );
			}else{
				wk->seq++;
			}
		}
		break;

	case WE204_END:
		// 終了
		WEEffect_TCB_Delete(wk->we_sys, tcb);
		sys_FreeMemoryEz(wk);
		return;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	あまえる
 *
 *	@param	we_sys 
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void WestSp_WE_204( WE_SYS_PTR we_sys )
{
	TWE204_SYS* wk;
	int vec_x;

	wk = WET_ALLOC_MEMORY(we_sys, TWE204_SYS);
	wk->we_sys	= we_sys;

	vec_x = WazaTool_VecChangeX( wk->we_sys, WeSysATNoGet(wk->we_sys) );

	// 攻撃側
	if (WeSysGPWorkGet(we_sys, 0) == 0){
		wk->at_ssp = WeSysSoftSpritePointerGet( wk->we_sys, WeSysATNoGet(we_sys) );
		wk->at_x = SoftSpriteParaGet( wk->at_ssp, SS_PARA_POS_X );
		wk->at_y = SoftSpriteParaGet( wk->at_ssp, SS_PARA_POS_Y );
	}
	else {
		wk->at_ssp = WeSysSoftSpritePointerGet( wk->we_sys, WeSysDFNoGet(we_sys) );
		wk->at_x = SoftSpriteParaGet( wk->at_ssp, SS_PARA_POS_X );
		wk->at_y = SoftSpriteParaGet( wk->at_ssp, SS_PARA_POS_Y );
	}

	// 回転中心角度設定
	SoftSpriteParaSet( wk->at_ssp, SS_PARA_ROT_CY, WE204_ROTA_C_Y );

	// 回転データ初期化
	if( vec_x == 1 ){
		wk->flip_flg = 0;
	}else{
		wk->flip_flg = 1;
	}
	TWe204_RotaInit( wk, wk->flip_flg );

	WEEffect_TCB_AddPriSet(wk->we_sys, We204_TCB, wk);
}


//-------------------------------------
//	
//	いばる
//	
//=====================================
enum{
	WE207_POKE_SCALE,
	WE207_WAIT,
	WE207_END,
};
enum{
	WE207_AT_SCALE_UP,
	WE207_AT_WAIT,
	WE207_AT_SCALE_DOWN,
	WE207_AT_END,
};

#define WE207_SCALE_POKE_S		( 10 )
#define WE207_SCALE_POKE_D		( 10 )
#define WE207_SCALE_POKE_E		( 15 )
#define WE207_SCALE_POKE_SYNC	( 8 )
#define WE207_SCALE_POKE_WAIT	( 4 )



#define WE207_WAIT_NUM	( 16 )

typedef struct {
	WE_SYS_PTR	we_sys;
	int seq;
	int wait;
	
	// 攻撃側
	SOFT_SPRITE* at_ssp;
	WAZATOOL_CALCMOVE at_scale;
	int at_wait;
	int at_seq;
	int at_y;
	int at_h;
	
} TWE207_SYS;


static BOOL We207_MoveAtPoke( TWE207_SYS* wk )
{
	BOOL ret = FALSE;
	
	switch( wk->at_seq ){
	case WE207_AT_SCALE_UP:
		if( WazaTool_CalcAndReflectScaleRateSsp( &wk->at_scale, wk->at_ssp ) ){
			// 足にあわせる
			WazaTool_PokeOffsetSet( wk->at_ssp, wk->at_y, wk->at_h, wk->at_scale.work[4], WAZAEFF_OFS_MODE_BOTTOM);
		}else{
			wk->at_seq++;
		}
		break;

	case WE207_AT_WAIT:
		wk->at_wait --;
		if( wk->at_wait < 0 ){
			wk->at_seq++;
			WazaTool_InitScaleRate(
					&wk->at_scale,
					WE207_SCALE_POKE_E,
					WE207_SCALE_POKE_D,
					WE207_SCALE_POKE_S,
					WE207_SCALE_POKE_SYNC
					);
		}
		break;

	case WE207_AT_SCALE_DOWN:
		if( WazaTool_CalcAndReflectScaleRateSsp( &wk->at_scale, wk->at_ssp ) ){
			// 足にあわせる
			WazaTool_PokeOffsetSet( wk->at_ssp, wk->at_y, wk->at_h, wk->at_scale.work[4], WAZAEFF_OFS_MODE_BOTTOM);
		}else{
			wk->at_seq++;
		}
		break;

	case WE207_AT_END:
		SoftSpriteParaSet( wk->at_ssp, SS_PARA_AFF_X, 0x100 );
		SoftSpriteParaSet( wk->at_ssp, SS_PARA_AFF_Y, 0x100 );
		ret = TRUE;
		break;
	}

	return ret;
}

static void We207_TCB( TCB_PTR tcb, void* work )
{
	TWE207_SYS* wk = work;
	
	switch( wk->seq ){
	case WE207_POKE_SCALE:
		if( We207_MoveAtPoke( wk ) ){
			wk->seq++;
			wk->wait = WE207_WAIT_NUM;
		}
		break;

	case WE207_WAIT:
		wk->wait --;
		if( wk->wait < 0 ){
			wk->seq++;
		}
		break;
		

	case WE207_END:
		// 終了
		WEEffect_TCB_Delete(wk->we_sys, tcb);
		sys_FreeMemoryEz(wk);
		return;
	}

}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	あまえる
 *
 *	@param	we_sys 
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void WestSp_WE_207_MAIN( WE_SYS_PTR we_sys )
{
	TWE207_SYS* wk;
	SOFT_SPRITE* df_ssp;

	wk = WET_ALLOC_MEMORY(we_sys, TWE207_SYS);
	wk->we_sys	= we_sys;

	// 攻撃側
	wk->at_ssp = WeSysSoftSpritePointerGet( wk->we_sys, WeSysATNoGet(we_sys) );
	WazaTool_InitScaleRate(
			&wk->at_scale,
			WE207_SCALE_POKE_S,
			WE207_SCALE_POKE_D,
			WE207_SCALE_POKE_E,
			WE207_SCALE_POKE_SYNC
			);
	wk->at_wait = WE207_SCALE_POKE_WAIT;	

	wk->at_h	= WeSysPokeOfsGet(wk->we_sys, WeSysATNoGet(wk->we_sys));
	wk->at_y	= SoftSpriteParaGet( wk->at_ssp, SS_PARA_POS_Y );

	WEEffect_TCB_AddPriSet(wk->we_sys, We207_TCB, wk);
}


//-------------------------------------
//	
//	くろいまなざし
//	
//=====================================
enum{
	WE212_CAP_SCALE_OUT,
	WE212_CAP_SCALE_IN,
	WE212_CAP_ALPHA_WAIT,
	WE212_CAP_END
};

enum{
	WE212_CAP_OBJ_SCALE_OUT,
	WE212_CAP_ANIME,
	WE212_CAP_FLASH_IN,
	WE212_CAP_OBJ_ALPHA_OUT,
	WE212_END
};

enum{
	WE212_CAP_SCALE_OUT_INIT,
	WE212_CAP_SCALE_OUT_MOVE,
	WE212_CAP_SCALE_OUT_END,
};

#define WE212_SCALE_OUT_KETA	( 100 )
#define WE212_SCALE_S	( 15 * WE212_SCALE_OUT_KETA )
#define WE212_SCALE_D	( 10 )
#define WE212_SCALE_E	( 10 * WE212_SCALE_OUT_KETA )
#define WE212_SYNC_S	( 4 * WE212_SCALE_OUT_KETA )
#define WE212_SCALE_OUT_DIV	( 3 )	// 1/WE212_SCALE_OUT_DIVづつ減らしていく
#define WE212_SCALDE_NUM	(2)
 
#define WE212_ALPHA_S	( 16 )
#define WE212_ALPHA_E	( 10 )

#define WE212_FADE_OUT_NUM	( 3 )

#define WE212_FLASH_WAIT	( 30 )
//#define WE212_FLASH_SYNC	( -2 )
#define WE212_FLASH_SYNC	( 8 )
#define WE212_FLASH_OUT_FLG	( -1 )
#define WE212_FLASH_IN_FLG	( -2 )
#define WE212_FLASH_MSK		( PLANEMASK_BG0|PLANEMASK_BG2|PLANEMASK_BG3 )

#define WE212_CAP_ALPHA_IN_SYNC	( 4 )
#define WE212_CAP_ALPHA_OUT_SYNC	( 8 )
#define WE212_CAP_OBJ_END_FRAME	( 4 )


typedef struct {
	WE_SYS_PTR	we_sys;
	CATS_SYS_PTR csp;
	CATS_RES_PTR crp;
	int seq;
	int flash_wait;
	
	// くろいまなざし
	CATS_ACT_PTR cap;
	WAZATOOL_CALCMOVE		cap_scale;
	WAZATOOL_ALPHA_FADE		cap_alpha;
	int cap_seq;
	int cap_scalenum;

	int cap_count;
	int cap_sync;
	int cap_scale_s;
	int cap_scale_e;
	int cap_scale_out_seq;
} TWE212_SYS;

static void We212_InitCapObj( TWE212_SYS* wk )
{
	WazaTool_InitScaleRate(
			&wk->cap_scale,
			wk->cap_scale_s / WE212_SCALE_OUT_KETA,
			WE212_SCALE_D,
			wk->cap_scale_e / WE212_SCALE_OUT_KETA,
			wk->cap_sync / WE212_SCALE_OUT_KETA
			);
	WET_DefaultBlendSet(wk->we_sys, WE212_ALPHA_S, 16 - WE212_ALPHA_S );
	WazaTool_StartAlphaFade(
			&wk->cap_alpha,
			WE212_ALPHA_S,
			WE212_ALPHA_E,
			16 - WE212_ALPHA_S,
			16 - WE212_ALPHA_E,
			(wk->cap_sync / WE212_SCALE_OUT_KETA) * WE212_SCALDE_NUM	
			);
	wk->cap_seq = 0;
	wk->cap_scalenum = 0;
}

static BOOL We212_CalcCapObj( TWE212_SYS* wk )
{
	BOOL ret = FALSE;
	
	switch( wk->cap_seq ){
	case WE212_CAP_SCALE_OUT:
		if( WazaTool_CalcAndReflectScaleRateCap( &wk->cap_scale, wk->cap ) == FALSE ){
			WazaTool_InitScaleRate(
					&wk->cap_scale,
					wk->cap_scale_e / WE212_SCALE_OUT_KETA,
					WE212_SCALE_D,
					wk->cap_scale_s / WE212_SCALE_OUT_KETA,
					wk->cap_sync / WE212_SCALE_OUT_KETA
					);
			wk->cap_seq++;
		}
		break;
		
	case WE212_CAP_SCALE_IN:
		if( WazaTool_CalcAndReflectScaleRateCap( &wk->cap_scale, wk->cap ) == FALSE ){
			wk->cap_scalenum++;
			if( wk->cap_scalenum < WE212_SCALDE_NUM ){
				wk->cap_seq = WE212_CAP_SCALE_OUT;
				WazaTool_InitScaleRate(
						&wk->cap_scale,
						wk->cap_scale_s / WE212_SCALE_OUT_KETA,
						WE212_SCALE_D,
						wk->cap_scale_e / WE212_SCALE_OUT_KETA,
						wk->cap_sync / WE212_SCALE_OUT_KETA
						);
			}else{
				wk->cap_seq++;
			}
		}
		break;
		
	case WE212_CAP_ALPHA_WAIT:
		if( WazaTool_EndCheckAlphaFade( &wk->cap_alpha ) ){
			wk->cap_seq++;
			ret = TRUE;
		}
		break;
		
	case WE212_CAP_END:
		ret = TRUE;
		break;
	}

	return ret;
}

static BOOL We212_ScaleOut( TWE212_SYS* wk )
{
	BOOL ret = FALSE;
	
	switch( wk->cap_scale_out_seq ){
	case WE212_CAP_SCALE_OUT_INIT:
		We212_InitCapObj( wk );
		We212_CalcCapObj( wk );
		wk->cap_scale_out_seq++;
		break;
		
	case WE212_CAP_SCALE_OUT_MOVE:
		if( We212_CalcCapObj( wk ) ){
			wk->cap_count --;
			if( wk->cap_count >= 0 ){
				wk->cap_sync -= wk->cap_sync / WE212_SCALE_OUT_DIV;
				wk->cap_scale_s -= wk->cap_scale_s / WE212_SCALE_OUT_DIV;
				wk->cap_scale_e -= wk->cap_scale_e / WE212_SCALE_OUT_DIV;
				wk->cap_scale_out_seq = WE212_CAP_SCALE_OUT_INIT;
			}else{
				wk->cap_scale_out_seq++;
				ret = TRUE;
			}
		}
		break;
		
	case WE212_CAP_SCALE_OUT_END:
		ret = TRUE;
		break;
	}

	return ret;
}


static void We212_TCB( TCB_PTR tcb, void* work )
{
	TWE212_SYS* wk = work;
	BOOL check1, check2;
	
	switch( wk->seq ){
	case WE212_CAP_OBJ_SCALE_OUT:
		if( We212_ScaleOut( wk ) ){
			wk->seq ++;
			wk->flash_wait = WE212_FLASH_WAIT;

			CATS_ObjectAnimeSeqSetCap( wk->cap, 0 );
			CATS_ObjectAutoAnimeSetCap( wk->cap, TRUE );
//			G2_ChangeBlendAlpha( 16, 0 );
			CATS_ObjectScaleSetCap( wk->cap, 1,1 );
			WazaTool_StartAlphaFade(
					&wk->cap_alpha,
					0,
					16,
					16,
					0,
					WE212_CAP_ALPHA_IN_SYNC
					);
		}
		break;

	case WE212_CAP_ANIME:
		
		// フラッシュタスク設定
		if( wk->flash_wait == 0 ){

//			PaletteFadeReq(WeSysPFDGet(wk->we_sys), PF_BIT_MAIN_BG, BT_HaikeiFadeBit( wk->we_sys ), WE212_FLASH_SYNC, 0, 16, 0xffff);
			
			// ブライトネス開始	フラッシュアウト
			ChangeBrightnessRequest( 
					WE212_FLASH_SYNC,
					BRIGHTNESS_WHITE,
					BRIGHTNESS_NORMAL,
					WE212_FLASH_MSK,
					MASK_MAIN_DISPLAY );//*/

			wk->flash_wait = WE212_FLASH_OUT_FLG;
		}else{
			
			if( wk->flash_wait > 0 ){
				wk->flash_wait --;
			}
		}

		if( wk->flash_wait == WE212_FLASH_OUT_FLG ){
//			if( PaletteFadeCheck(WeSysPFDGet(wk->we_sys)) == 0 ){
			if( IsFinishedBrightnessChg( MASK_MAIN_DISPLAY ) ){
				
//				PaletteFadeReq(WeSysPFDGet(wk->we_sys), PF_BIT_MAIN_BG, BT_HaikeiFadeBit( wk->we_sys ), WE212_FLASH_SYNC, 16, 0, 0xffff);
				
				// ブライトネス開始	フラッシュイン
				ChangeBrightnessRequest( 
						WE212_FLASH_SYNC,
						BRIGHTNESS_NORMAL,
						BRIGHTNESS_WHITE,
						WE212_FLASH_MSK,
						MASK_MAIN_DISPLAY );//*/
				wk->flash_wait = WE212_FLASH_IN_FLG;	
			}
		}
		
		// アニメ終了待ち
		if( CATS_ObjectAnimeActiveCheckCap( wk->cap ) == FALSE ){
			wk->seq ++;
		}
		break;

	case WE212_CAP_FLASH_IN:
//		if( PaletteFadeCheck(WeSysPFDGet(wk->we_sys)) == 0 ){
		if( IsFinishedBrightnessChg( MASK_MAIN_DISPLAY ) ){
			wk->seq ++;
			WET_DefaultBlendSet(wk->we_sys, 16, 0 );
			WazaTool_StartAlphaFade(
					&wk->cap_alpha,
					16,
					0,
					0,
					16,
					WE212_CAP_ALPHA_OUT_SYNC
					);
		}
		break;

	case WE212_CAP_OBJ_ALPHA_OUT:
		if( WazaTool_EndCheckAlphaFade( &wk->cap_alpha ) ){
			CATS_ObjectEnableCap( wk->cap, FALSE );
			wk->seq++;
		}
		break;
		
	case WE212_END:
		CATS_ActorPointerDelete_S(wk->cap);
		// 終了
		WEEffect_TCB_Delete(wk->we_sys, tcb);
		sys_FreeMemoryEz(wk);
		return;
	}

	// OAM描画
	CATS_Draw(wk->crp);	
}

//----------------------------------------------------------------------------
/**
 * @brief	くろいまなざし用タスク登録
 *
 *	@param	we_sys	技エフェクトシステムワーク
 *	@param	csp		セルアクターツールシステム
 *	@param	crp		セルアクターリソースシステム
 *	@param	cap		セルアクターツールオブジェ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void WestSp_CAT_WE_212(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CATS_ACT_PTR cap)
{
	TWE212_SYS* wk;
	SOFT_SPRITE* df_ssp;

	wk = WET_ALLOC_MEMORY(we_sys, TWE212_SYS);
	wk->we_sys	= we_sys;
	wk->csp		= csp;
	wk->crp		= crp;

	// くろいまなざし
	wk->cap = cap;
	CATS_ObjectPriSetCap( wk->cap, WAZAEFF_ACT_SOFTPRI );
	CATS_ObjectBGPriSetCap( wk->cap, WAZAEFF_ACT_BGPRI );
	CATS_ObjectAffineSetCap( wk->cap, CLACT_AFFINE_DOUBLE );
	CATS_ObjectObjModeSetCap( wk->cap, GX_OAM_MODE_XLU );
	CATS_ObjectAnimeFrameSetCap( wk->cap, WE212_CAP_OBJ_END_FRAME );
	wk->cap_count = WE212_FADE_OUT_NUM;
	wk->cap_sync = WE212_SYNC_S;
	wk->cap_scale_s	= WE212_SCALE_S;
	wk->cap_scale_e	= WE212_SCALE_E;

	WEEffect_TCB_AddPriSet(wk->we_sys, We212_TCB, wk);
}


//-------------------------------------
//	
//	おんがえし
//	
//=====================================
enum{
	WE216_SHAKE_INIT,
	WE216_SHAKE_MOVE,
	WE216_SHAKE_END,
};
#define WE216_SHAKE_Y			( 32 )
#define WE216_SHAKE_ONE_SYNC	( 6 )
#define WE216_SHAKE_NUM			( 4 )
typedef struct {
	int	seq;
	WE_SYS_PTR	we_sys;			
	
	// ソフトスプライトデータ
	SOFT_SPRITE* at_ssp;
	s16	at_x;
	s16 at_y;
	WAZATOOL_CALCMOVE	at_move;
	int at_move_count;

} TWE216_SYS;

static void We216_ShakeInit( TWE216_SYS* wk )
{
	switch( wk->at_move_count ){
	case 0:
	case 2:
		WazaTool_InitStraightSyncFx(
				&wk->at_move,
				0,0,
				0, WE216_SHAKE_Y,
				WE216_SHAKE_ONE_SYNC
				);
		break;

	case 1:
	case 3:
		WazaTool_InitStraightSyncFx(
				&wk->at_move,
				0,0,
				WE216_SHAKE_Y, 0,
				WE216_SHAKE_ONE_SYNC
				);
		break;
	}
}

static void We216_TCB( TCB_PTR tcb, void* work )
{
	TWE216_SYS* wk = work;
	
	switch( wk->seq ){
	case WE216_SHAKE_INIT:
		We216_ShakeInit( wk );
		wk->seq++;
		break;
		
	case WE216_SHAKE_MOVE:
		if( WazaTool_CalcStraightFx( &wk->at_move ) ){
			WazaTool_SetSspMatrix( &wk->at_move, wk->at_ssp, wk->at_x, wk->at_y );
		}else{
			wk->at_move_count++;
			if( wk->at_move_count < WE216_SHAKE_NUM ){
				wk->seq = WE216_SHAKE_INIT;
			}else{
				wk->seq++;
			}
		}
		break;
		
	case WE216_SHAKE_END:
		// 終了
		WEEffect_TCB_Delete(wk->we_sys, tcb);
		sys_FreeMemoryEz(wk);
		break;
	}
}

//----------------------------------------------------------------------------
/**
 * @brief	おんがえし用タスク登録
 *
 *	@param	we_sys	技エフェクトシステムワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void WestSp_WE_216( WE_SYS_PTR we_sys )
{
	TWE216_SYS* wk;

	wk = WET_ALLOC_MEMORY(we_sys, TWE216_SYS);
	wk->we_sys	= we_sys;

	// 攻撃側
	wk->at_ssp = WeSysSoftSpritePointerGet( wk->we_sys, WeSysATNoGet(we_sys) );
	wk->at_x = SoftSpriteParaGet( wk->at_ssp, SS_PARA_POS_X );
	wk->at_y = SoftSpriteParaGet( wk->at_ssp, SS_PARA_POS_Y );

	// 上下運動
	wk->at_move_count = 0;

	WEEffect_TCB_AddPriSet(wk->we_sys, We216_TCB, wk);
}


//-------------------------------------
//	
//	あてみなげ
//	
//=====================================
enum{
	WE233_AT_ROTA_INIT,
	WE233_AT_ROTA_CALC,
	WE233_AT_MOVE_1,
	WE233_DF_MOVE_1,
	WE233_AT_MOVE_2,
	WE233_DF_MOVE_2,
	WE233_END,
};

#define WE233_ROTA_NUM	( 1 )
#define WE233_ROTA_SYNC	( 64 )
#define WE233_STRAIGHT_MOVE_X		( 32 )
#define WE233_STRAIGHT_MOVE_SYNC	( 2 )
#define WE233_STRAIGHT_MOVE1_SYNC	( 8 )

typedef struct {
	int	seq;
	WE_SYS_PTR	we_sys;			
	int vec_x;
	
	// 攻撃用
	SOFT_SPRITE* at_ssp;
	s16	at_x;
	s16 at_y;
	WAZATOOL_CALCMOVE	at_move;

	// 防御用
	SOFT_SPRITE* df_ssp;
	s16	df_x;
	s16 df_y;
	WAZATOOL_CALCMOVE	df_move;
} TWE233_SYS;

static void We233_TCB( TCB_PTR tcb, void* work )
{
	TWE233_SYS* wk = work;

	switch( wk->seq ){
	case WE233_AT_ROTA_INIT:
		// 回転動作初期化
		WazaTool_MakeDefRota( 
				&wk->at_move,
				WE233_ROTA_NUM,
				WE233_ROTA_SYNC
				);
		wk->at_move.work[2] *= wk->vec_x;
		wk->seq++;
		break;
		
	case WE233_AT_ROTA_CALC:
		if( WazaTool_CalcAndReflectRotaFxSsp( &wk->at_move, wk->at_x, wk->at_y - WAZATOOL_DEF_ROTA_W_Y_INT, wk->at_ssp ) == FALSE ){

			SoftSpriteParaSet( wk->at_ssp, SS_PARA_POS_X, wk->at_x );
			SoftSpriteParaSet( wk->at_ssp, SS_PARA_POS_Y, wk->at_y );

			// 平行移動処理
			WazaTool_InitStraightSyncFx( 
					&wk->at_move,
					wk->at_x, wk->at_x + WE233_STRAIGHT_MOVE_X,
					0, 0,
					WE233_STRAIGHT_MOVE_SYNC
					);
			wk->at_move.work[1] *= wk->vec_x;
			wk->seq++;

			// 滑らかにするため
			WazaTool_CalcStraightFx( &wk->at_move );
			SoftSpriteParaSet( wk->at_ssp, SS_PARA_POS_X, wk->at_move.x );
		}
		break;
		
	case WE233_AT_MOVE_1:
		if( WazaTool_CalcStraightFx( &wk->at_move ) ){

			SoftSpriteParaSet( wk->at_ssp, SS_PARA_POS_X, wk->at_move.x );
		}else{

			// 敵平行移動処理
			WazaTool_InitStraightSyncFx( 
					&wk->df_move,
					wk->df_x, wk->df_x + (WE233_STRAIGHT_MOVE_X * wk->vec_x),
					0, 0,
					WE233_STRAIGHT_MOVE_SYNC
					);
			wk->seq++;
		}
		break;
		
	case WE233_DF_MOVE_1:
		if( WazaTool_CalcStraightFx( &wk->df_move ) ){

			SoftSpriteParaSet( wk->df_ssp, SS_PARA_POS_X, wk->df_move.x );
		}else{

			// 平行移動処理
			WazaTool_InitStraightSyncFx( 
					&wk->at_move,
					wk->at_move.x, wk->at_x,
					0, 0,
					WE233_STRAIGHT_MOVE1_SYNC
					);
			wk->seq++;
		}
		break;

	case WE233_AT_MOVE_2:
		if( WazaTool_CalcStraightFx( &wk->at_move ) ){

			SoftSpriteParaSet( wk->at_ssp, SS_PARA_POS_X, wk->at_move.x );
		}else{
			SoftSpriteParaSet( wk->at_ssp, SS_PARA_POS_X, wk->at_x );

			// 敵平行移動処理
			WazaTool_InitStraightSyncFx( 
					&wk->df_move,
					wk->df_move.x, wk->df_x,
					0, 0,
					WE233_STRAIGHT_MOVE1_SYNC
					);
			wk->seq++;
		}
		break;
		
	case WE233_DF_MOVE_2:
		if( WazaTool_CalcStraightFx( &wk->df_move ) ){

			SoftSpriteParaSet( wk->df_ssp, SS_PARA_POS_X, wk->df_move.x );
		}else{
			SoftSpriteParaSet( wk->df_ssp, SS_PARA_POS_X, wk->df_x );

			wk->seq++;
		}
		break;
		
	case WE233_END:
		// 終了
		WEEffect_TCB_Delete(wk->we_sys, tcb);
		sys_FreeMemoryEz(wk);
		break;
	}
}

//----------------------------------------------------------------------------
/**
 * @brief	あてみなげ用タスク登録
 *
 *	@param	we_sys	技エフェクトシステムワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void WestSp_WE_233( WE_SYS_PTR we_sys )
{
	TWE233_SYS* wk;

	wk = WET_ALLOC_MEMORY(we_sys, TWE233_SYS);
	wk->we_sys	= we_sys;

	wk->vec_x = WazaTool_VecChangeX( wk->we_sys, WeSysATNoGet(wk->we_sys) );

	// 攻撃側
	wk->at_ssp = WeSysSoftSpritePointerGet( wk->we_sys, WeSysATNoGet(we_sys) );
	wk->at_x = SoftSpriteParaGet( wk->at_ssp, SS_PARA_POS_X );
	wk->at_y = SoftSpriteParaGet( wk->at_ssp, SS_PARA_POS_Y );

	// 防御側
	wk->df_ssp = WeSysSoftSpritePointerGet( wk->we_sys, WeSysDFNoGet(we_sys) );
	wk->df_x = SoftSpriteParaGet( wk->df_ssp, SS_PARA_POS_X );
	wk->df_y = SoftSpriteParaGet( wk->df_ssp, SS_PARA_POS_Y );

	WEEffect_TCB_AddPriSet(wk->we_sys, We233_TCB, wk);
}


//-------------------------------------
//	
//	いちゃもん
//	
//=====================================
enum{
	WE259_INIT_MOVE,
	WE259_MOVE_OBJ,
	WE259_WAIT,
	WE259_INIT_REMOVE,
	WE259_REMOVE_OBJ,
	WE259_END,
};

enum{
	WE259_SSP_SCALE_1,
	WE259_SSP_SCALE_2,
	WE259_SSP_SCALE_3,
	WE259_SSP_END,
};

#define WE259_CAP_OBJ_NUM	( 6 )

#define WE259_OBJ_SCALE_D	( 10 )
#define WE259_OBJ_SCALE_SYNC	( 2 )
#define WE259_OBJ_SCALE1_S	( 10 )
#define WE259_OBJ_SCALE1_E	( 8 )
#define WE259_OBJ_SCALE2_S	( 8 )
#define WE259_OBJ_SCALE2_E	( 15 )
#define WE259_OBJ_SCALE3_S	( 15 )
#define WE259_OBJ_SCALE3_E	( 10 )

#define WE259_OBJ_SCALE1_SX	( 10 )
#define WE259_OBJ_SCALE1_EX	( 9 )
#define WE259_OBJ_SCALE2_SX	( 9 )
#define WE259_OBJ_SCALE2_EX	( 11 )
#define WE259_OBJ_SCALE3_SX	( 11 )
#define WE259_OBJ_SCALE3_EX	( 10 )

/*#define WE259_CAP_MAT_XOFS		( 48 )
#define WE259_CAP_MAT_XOFS_SUB	( 4 )
#define WE259_CAP_MAT_YOFS_SUB	( 24 )//*/

#define WE259_CAP_MAT_R			( 48*FX32_ONE )	// 半径サイズ
#define WE259_CAP_MAT_ROTA		( FX_GET_ROTA_NUM( 90 ) / (WE259_CAP_OBJ_NUM/2) )

#define WE259_CAP_WAIT_MAX	( 8 )
#define WE256_CAP_ANIME_SPEED	( FX32_ONE*2 )

typedef struct {
	WE_SYS_PTR	we_sys;
	CATS_SYS_PTR csp;
	CATS_RES_PTR crp;
	int seq;
	int count;
	int wait;

	// 攻撃オブジェクト
	SOFT_SPRITE* at_ssp;
	WAZATOOL_CALCMOVE	at_scale;
	int ssp_seq;

	s16 ssp_y;
	s16 poke_h;
	
	// いちゃもんオブジェクト
	CATS_ACT_PTR	cap[ WE259_CAP_OBJ_NUM ];
	int cap_seq[ WE259_CAP_OBJ_NUM  ];
	int cap_wait[ WE259_CAP_OBJ_NUM ];
	
} TWE259_SYS;

// ポケモン動作準備
static void We259_SSP_Init( TWE259_SYS* wk )
{
	wk->ssp_seq = 0;

	WazaTool_InitScaleRateEx(
			&wk->at_scale,
			WE259_OBJ_SCALE1_SX,
			WE259_OBJ_SCALE1_EX,
			WE259_OBJ_SCALE1_S,
			WE259_OBJ_SCALE1_E,
			WE259_OBJ_SCALE_D,
			WE259_OBJ_SCALE_SYNC
			);
}

static BOOL We259_SSP_Move( TWE259_SYS* wk )
{
	BOOL ret = FALSE;
	
	switch( wk->ssp_seq ){
	case WE259_SSP_SCALE_1:
		if( WazaTool_CalcAndReflectScaleRateExSsp( &wk->at_scale, wk->at_ssp ) ){

			WazaTool_PokeOffsetSet(
					wk->at_ssp,
					wk->ssp_y, wk->poke_h,
					wk->at_scale.work[4], WAZAEFF_OFS_MODE_BOTTOM);//*/
		}else{
			wk->ssp_seq++;
			WazaTool_InitScaleRateEx(
					&wk->at_scale,
					WE259_OBJ_SCALE2_SX,
					WE259_OBJ_SCALE2_EX,
					WE259_OBJ_SCALE2_S,
					WE259_OBJ_SCALE2_E,
					WE259_OBJ_SCALE_D,
					WE259_OBJ_SCALE_SYNC
					);
		}
		break;
		
	case WE259_SSP_SCALE_2:
		if( WazaTool_CalcAndReflectScaleRateExSsp( &wk->at_scale, wk->at_ssp ) ){
			WazaTool_PokeOffsetSet(
					wk->at_ssp,
					wk->ssp_y, wk->poke_h,
					wk->at_scale.work[4], WAZAEFF_OFS_MODE_BOTTOM);//*/
		}else{
			wk->ssp_seq++;
			WazaTool_InitScaleRateEx(
					&wk->at_scale,
					WE259_OBJ_SCALE3_SX,
					WE259_OBJ_SCALE3_EX,
					WE259_OBJ_SCALE3_S,
					WE259_OBJ_SCALE3_E,
					WE259_OBJ_SCALE_D,
					WE259_OBJ_SCALE_SYNC
					);
		}
		break;
		
	case WE259_SSP_SCALE_3:
		if( WazaTool_CalcAndReflectScaleRateExSsp( &wk->at_scale, wk->at_ssp ) ){
			WazaTool_PokeOffsetSet(
					wk->at_ssp,
					wk->ssp_y, wk->poke_h,
					wk->at_scale.work[4], WAZAEFF_OFS_MODE_BOTTOM);//*/
		}else{
			SoftSpriteParaSet( wk->at_ssp, SS_PARA_AFF_X, 0x100 );
			SoftSpriteParaSet( wk->at_ssp, SS_PARA_AFF_Y, 0x100 );
			wk->ssp_seq++;
			ret = TRUE;
		}
		break;
		
	case WE259_SSP_END:
		ret = TRUE;
		break;
	}

	return ret;
}


static void We259_CAP_Init( CATS_ACT_PTR cap, int* p_cap_seq, fx32 frame )
{
	*p_cap_seq = 0;
	CATS_ObjectPriSetCap( cap, WAZAEFF_ACT_SOFTPRI );
	CATS_ObjectBGPriSetCap( cap, WAZAEFF_ACT_BGPRI );
	CATS_ObjectEnableCap( cap, TRUE );
	CATS_ObjectAutoAnimeSetCap( cap, TRUE );
	CATS_ObjectAutoAnimeSpeedSetCap( cap, frame );
	// アニメシーケンスチェンジ
	CATS_ObjectAnimeSeqSetCap( cap, 0 );		
	CATS_ObjectAnimeFrameSetCap(cap, 0 );


	// 55フレーム先にするめる
	CATS_ObjectUpdateNumCap( cap, 55*FX32_ONE );
}

// アニメーションさせる
static BOOL We259_CAP_Move( CATS_ACT_PTR cap, int* p_cap_seq )
{
	BOOL ret = FALSE;
	
	switch( *p_cap_seq ){
	case 0:		// 終了チェック
		if( CATS_ObjectAnimeActiveCheckCap( cap ) == FALSE ){
			(*p_cap_seq)++;
			ret = TRUE;
		}
		break;

	case 1:		// 終了
		ret = TRUE;
		break;
	
	default:
		ret = TRUE;
		break;
	}

	return ret;
}


static void We259_TCB( TCB_PTR tcb, void* work )
{
	TWE259_SYS* wk = work;
	BOOL check1, check2;
	int i;

	switch( wk->seq ){
	case WE259_INIT_MOVE:
		We259_SSP_Init( wk );
		We259_CAP_Init( wk->cap[ wk->count ], &wk->cap_seq[ wk->count ], WE256_CAP_ANIME_SPEED );
		wk->seq++;
		break;
		
	case WE259_MOVE_OBJ:
		check1 = We259_SSP_Move( wk );
		check2 = We259_CAP_Move( wk->cap[ wk->count ], &wk->cap_seq[ wk->count ] );
		if( (check1 == check2) && (check1 == TRUE) ){
			// アニメシーケンスチェンジ
			CATS_ObjectAnimeSeqSetCap( wk->cap[ wk->count ], 1 );		
			wk->seq++;
		}
		break;

	case WE259_WAIT:
		wk->cap_wait[ wk->count ] --;
		if( wk->cap_wait[ wk->count ] < 0 ){
			wk->count ++;
			if( wk->count < WE259_CAP_OBJ_NUM ){
				wk->seq = WE259_INIT_MOVE;
			}else{
				wk->seq ++;
			}
		}
		break;

	case WE259_INIT_REMOVE:
		for( i=0; i<WE259_CAP_OBJ_NUM; i++ ){
			We259_CAP_Init( wk->cap[ i ], &wk->cap_seq[ i ], WE256_CAP_ANIME_SPEED );
		}
		wk->seq++;
		break;
			
	case WE259_REMOVE_OBJ:
		for( i=0; i<WE259_CAP_OBJ_NUM; i++ ){
			check1 = We259_CAP_Move( wk->cap[ i ], &wk->cap_seq[ i ] );
		}
		if( check1 == TRUE ){
			wk->seq++;
		}
		break;
		
	case WE259_END:
		for( i=0; i<WE259_CAP_OBJ_NUM; i++ ){
			CATS_ActorPointerDelete_S(wk->cap[i]);
		}
		
		// 終了
		WEEffect_TCB_Delete(wk->we_sys, tcb);
		sys_FreeMemoryEz(wk);
		return;
	}

	// OAM描画
	CATS_Draw(wk->crp);	
}


//----------------------------------------------------------------------------
/**
 * @brief	いちゃもん用タスク登録
 *
 *	@param	we_sys	技エフェクトシステムワーク
 *	@param	csp		セルアクターツールシステム
 *	@param	crp		セルアクターリソースシステム
 *	@param	cap		セルアクターツールオブジェ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void WestSp_CAT_WE_259(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CATS_ACT_PTR cap)
{
	TWE259_SYS* wk;
	TCATS_OBJECT_ADD_PARAM_S coap;
	int i;
	s16 at_x;
	s16 at_y;
	s16 cap_x;
	s16 cap_y;

	wk = WET_ALLOC_MEMORY(we_sys, TWE259_SYS);
	wk->we_sys	= we_sys;
	wk->csp		= csp;
	wk->crp		= crp;

	// 攻撃側
	wk->at_ssp = WeSysSoftSpritePointerGet( wk->we_sys, WeSysATNoGet(wk->we_sys) );
	at_x = SoftSpriteParaGet( wk->at_ssp, SS_PARA_POS_X );
	at_y = SoftSpriteParaGet( wk->at_ssp, SS_PARA_POS_Y );

	
	// ポケモンの高さ　と　位置を取得
	wk->ssp_y = at_y;
	wk->poke_h	= WeSysPokeOfsGet(wk->we_sys, WeSysATNoGet(wk->we_sys));
	

	// いちゃもん
	coap   = WeSysCoapGet(wk->we_sys);
	// 残り分のオブジェクトも作成
	for( i=0; i<WE259_CAP_OBJ_NUM; i++ ){
		if( i==0 ){
			wk->cap[ i ] = cap;
		}else{
			wk->cap[ i ] = CATS_ObjectAdd_S(csp, crp, &coap);
		}
		CATS_ObjectEnableCap( wk->cap[i], FALSE );

		// 配置位置設定
		//     5 4
		//    3   2
		//   1     0
/*		cap_x = WE259_CAP_MAT_XOFS - (WE259_CAP_MAT_XOFS_SUB * (WE259_CAP_MAT_XOFS_SUB * (i / 2)) );
		cap_y = WE259_CAP_MAT_YOFS_SUB * (i / 2);//*/

		cap_x = FX_Mul( FX_CosIdx( WE259_CAP_MAT_ROTA*(i/2) ), WE259_CAP_MAT_R ) >> FX32_SHIFT;
		cap_y = FX_Mul( FX_SinIdx( WE259_CAP_MAT_ROTA*(i/2) ), WE259_CAP_MAT_R ) >> FX32_SHIFT;
		if( (i % 2) == 0 ){
			// 偶数=右側
			cap_x = at_x + cap_x;
			CATS_ObjectFlipSetCap( wk->cap[i], TRUE );
		}else{
			// 奇数＝左側
			cap_x = at_x - cap_x;
		}
		cap_y = at_y - cap_y;
		CATS_ObjectPosSetCap( wk->cap[i], cap_x, cap_y );

		// wait設定
		if( i < 2 ){
			wk->cap_wait[ i ] = WE259_CAP_WAIT_MAX;
		}else{
			wk->cap_wait[ i ] = 0;
		}
	}

	WEEffect_TCB_AddPriSet(wk->we_sys, We259_TCB, wk);
}


//-------------------------------------
//	
//	バトンタッチ
//	
//=====================================
enum{
	WE226_OPEN_BALL_INIT,
	WE226_OPEN_BALL,
	WE266_POKE_IN_BALL,
	WE266_CLOSE_BALL,
	WE266_MOVE_BALL,
	WE226_END,
};

#define WE226_SCALE_S	( 10 )
#define WE226_SCALE_E	( 0 )
#define WE226_SCALE_D	( 10 )
#define WE226_SCALE_SYNC	( 8 )

#define WE226_MOVE_SYNC	( 8 )

typedef struct {
	WE_SYS_PTR	we_sys;
	CATS_SYS_PTR csp;
	CATS_RES_PTR crp;
	int seq;

	// 攻撃オブジェクト
	SOFT_SPRITE* at_ssp;
	WAZATOOL_CALCMOVE	at_scale;
	WAZATOOL_CALCMOVE	at_move;
	
	// ボールオブジェクト
	CATS_ACT_PTR	cap;
	WAZATOOL_CALCMOVE	cap_move;
	int cap_seq;
	s16 cap_x;
	s16 cap_y;

} TWE226_SYS;

static void We226_TCB( TCB_PTR tcb, void* work )
{
	TWE226_SYS* wk = work;
	int ofs_x, ofs_y;

	switch( wk->seq ){
	case WE226_OPEN_BALL_INIT:	// ボールおーぷん初期化
		CATS_ObjectAutoAnimeSetCap( wk->cap, TRUE );
		wk->seq++;
		break;
		
	case WE226_OPEN_BALL:	// ボールオープン
		if( CATS_ObjectAnimeActiveCheckCap( wk->cap ) == FALSE ){
			CATS_ObjectAutoAnimeSetCap( wk->cap, FALSE );
			wk->seq++;
			WazaTool_InitScaleRate(
					&wk->at_scale,
					WE226_SCALE_S,
					WE226_SCALE_D,
					WE226_SCALE_E,
					WE226_SCALE_SYNC
					);
			ofs_x = SoftSpriteParaGet( wk->at_ssp, SS_PARA_POS_X );
			ofs_y = SoftSpriteParaGet( wk->at_ssp, SS_PARA_POS_Y );
			WazaTool_InitStraightSyncFx(
					&wk->at_move,
					ofs_x, wk->cap_x,
					ofs_y, wk->cap_y,
					WE226_SCALE_SYNC
					);

		}
		break;
		
	case WE266_POKE_IN_BALL:	// ポケモンをぼーるのなかへ
		WazaTool_CalcAndReflectStraightFxSsp( &wk->at_move, wk->at_ssp );
		if( WazaTool_CalcAndReflectScaleRateSsp( &wk->at_scale, wk->at_ssp ) == FALSE ){
			SoftSpriteParaSet( wk->at_ssp, SS_PARA_VANISH, TRUE );
			SoftSpriteParaSet( wk->at_ssp, SS_PARA_AFF_X, 0x100 );
			SoftSpriteParaSet( wk->at_ssp, SS_PARA_AFF_Y, 0x100 );

			CATS_ObjectAnimeSeqSetCap( wk->cap, 1 );
			CATS_ObjectAutoAnimeSpeedSetCap( wk->cap, FX32_ONE );
			CATS_ObjectAutoAnimeSetCap( wk->cap, TRUE );
			wk->seq++;
		}
		break;
		
	case WE266_CLOSE_BALL:		// ボールをとじる
		if( CATS_ObjectAnimeActiveCheckCap( wk->cap ) == FALSE ){

			CATS_ObjectAutoAnimeSetCap( wk->cap, FALSE );
			wk->seq++;
			WazaTool_InitStraightSyncFx(
					&wk->cap_move,
					0, 0,
					wk->cap_y, 0,
					WE226_MOVE_SYNC
					);
		}
		break;
		
	case WE266_MOVE_BALL:
		if( WazaTool_CalcStraightFx( &wk->cap_move ) ){

			CATS_ObjectPosSetCap( wk->cap, wk->cap_x, wk->cap_move.y );
		}else{

			wk->seq++;
		}
		break;
		
	case WE226_END:
		CATS_ActorPointerDelete_S(wk->cap);
		
		// 終了
		WEEffect_TCB_Delete(wk->we_sys, tcb);
		sys_FreeMemoryEz(wk);
		return;
	}

	// OAM描画
	CATS_Draw(wk->crp);	
}

//----------------------------------------------------------------------------
/**
 * @brief	バトンタッチ用タスク登録
 *
 *	@param	we_sys	技エフェクトシステムワーク
 *	@param	csp		セルアクターツールシステム
 *	@param	crp		セルアクターリソースシステム
 *	@param	cap		セルアクターツールオブジェ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void WestSp_CAT_WE_226(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CATS_ACT_PTR cap)
{
	TWE226_SYS* wk;
	s16 at_x, at_y;

	wk = WET_ALLOC_MEMORY(we_sys, TWE226_SYS);
	wk->we_sys	= we_sys;
	wk->csp		= csp;
	wk->crp		= crp;


	// 攻撃側
	wk->at_ssp = WeSysSoftSpritePointerGet( wk->we_sys, WeSysATNoGet(we_sys) );
	SoftSpriteParaSet( wk->at_ssp, SS_PARA_VANISH, FALSE );
//	wk->cap_x = SoftSpriteParaGet( wk->at_ssp, SS_PARA_POS_X );
//	wk->cap_y = SoftSpriteParaGet( wk->at_ssp, SS_PARA_POS_Y );
	wk->cap_x = GetWazaEffPos(we_sys, WeSysATNoGet(we_sys), PM_X);
	wk->cap_y = GetWazaEffPos(we_sys, WeSysATNoGet(we_sys), PM_Y);
	
	//ボールオブジェ
	wk->cap = cap;
	CATS_ObjectPriSetCap( wk->cap, WAZAEFF_ACT_SOFTPRI );
	CATS_ObjectBGPriSetCap( wk->cap, WAZAEFF_ACT_BGPRI );
	CATS_ObjectPosSetCap( wk->cap, wk->cap_x, wk->cap_y );


	WEEffect_TCB_AddPriSet(wk->we_sys, We226_TCB, wk);
}


//-------------------------------------
//	
//	おきみやげ
//	
//=====================================
enum{
	WE262_FADEIN_INIT,
	WE262_FADEIN,
	WE262_SCALE_OUT,
	WE262_SCALE_WAIT,
	WE262_SCALE_IN,
	WE262_FADEOUT,
	WE262_END,
};

enum{
	WE262_SCALEOUT_Y,
	WE262_SCALEOUT_YX,
	WE262_SCALEOUT_END,
};

enum{
	WE262_SCALEIN_MOVE,
	WE262_SCALEIN_XY_MOVE,
	WE262_SCALEIN_END,
};

#define WE262_ALPHA_IN_S	( 0 )
#define WE262_ALPHA_IN_E	( 8 )
#define WE262_ALPHA_SYNC	( 8 )

#define WE262_SCALE_D		( 10 )

#define WE262_SCALEOUT_SY		( 10 )
#define WE262_SCALEOUT_EY		( 20 )
#define WE262_SCALEOUT_SX		( 10 )
#define WE262_SCALEOUT_EX		( 1 )
#define WE262_SCALEOUT_YSYNC	( 8 )
#define WE262_SCALEOUT_XSYNC	( 4 )
#define WE262_SCALEOUT_WAIT		( 6 )

#define WE262_SCALEIN_SY		( 20 )
#define WE262_SCALEIN_EY		( 10 )
#define WE262_SCALEIN_SX		( 2 )
#define WE262_SCALEIN_EX		( 10 )
#define WE262_SCALEIN_SYNC	( 8 )

#define WE262_SCALEIN_MOVE_DIS	( 64 )
#define WE262_SCALEIN_MOVE_SYNC	( 8 )
#define WE262_SCALEIN_WAIT	( 6 )

#define WE262_SCALE_WAIT_NUM	( 2 )
 
typedef struct {
	WE_SYS_PTR	we_sys;
	CATS_RES_PTR crp;
	int seq;
	int wait;

	int poke_h;
	int dy;

	// ポケモンかげ
	CATS_ACT_PTR	poke_cap_at;
	CATS_ACT_PTR	poke_cap_df;

	CATS_ACT_PTR	poke_cap_at_msk;
	CATS_ACT_PTR	poke_cap_df_msk;
	
	WAZATOOL_CALCMOVE	cap_scale1;
	WAZATOOL_CALCMOVE	cap_scale2;
	WAZATOOL_CALCMOVE	cap_move;
	int cap_seq;
	int cap_wait;
	
	WAZATOOL_ALPHA_FADE	cap_alpha;
	PALETTE_FADE_PTR	pfd;	// パレットフェード

	BOOL contest_at;
	BOOL contest_df;
} TWE262_SYS;

#define CLIENT_MAX_NUM	( CLIENT_TYPE_D + 1 )
static const u16 We262_MskOnOff[ CLIENT_MAX_NUM ] = {
	0, 0, 
	1, 0, 0, 1,
};

static void We262_SetPlttColorCap( TWE262_SYS* wk, CATS_ACT_PTR cap )
{
	int plt_bit;

	// パレットフェード
	plt_bit = 1 << WazaTool_CapPlttNoGet( cap );
	
	ColorConceChangePfd( wk->pfd, FADE_MAIN_OBJ, plt_bit, 8, 0x0 );
}

static void We262_ScaleOutInit( TWE262_SYS* wk )
{
	int client_type;
	f32 s_x, s_y;
	
	WazaTool_InitScaleRateEx(
			&wk->cap_scale1,
			WE262_SCALE_D,
			WE262_SCALE_D,
			WE262_SCALEOUT_SY,
			WE262_SCALEOUT_EY,
			WE262_SCALE_D,
			WE262_SCALEOUT_YSYNC
			);
	WazaTool_InitScaleRate(
			&wk->cap_scale2,
			WE262_SCALEOUT_SX,
			WE262_SCALE_D,
			WE262_SCALEOUT_EX,
			WE262_SCALEOUT_XSYNC
			);

	wk->cap_seq = 0;
	wk->cap_wait= WE262_SCALEOUT_WAIT;
	
	client_type = WET_ClientTypeGet(wk->we_sys, WeSysATNoGet(wk->we_sys));
	CATS_ObjectEnableCap( wk->poke_cap_at_msk, We262_MskOnOff[ client_type ] );
	CATS_ObjectEnableCap( wk->poke_cap_at, TRUE );

	// 拡大縮小はコンテストがあるので左右反転も考える
	WazaTool_CalcScaleRateToClactScale( &wk->cap_scale1, &s_x, &s_y );
	if( wk->contest_at == TRUE ){
		s_x = -s_x;
	}
	CATS_ObjectScaleSetCap( wk->poke_cap_at, s_x, s_y );
	
	We262_SetPlttColorCap( wk, wk->poke_cap_at );
}

static BOOL We262_ScaleOutMove( TWE262_SYS* wk )
{
	BOOL ret = FALSE;
	f32 s_x, s_y;
	
	switch( wk->cap_seq ){
	case WE262_SCALEOUT_Y:

		WazaTool_CalcScaleRateEx( &wk->cap_scale1 );
		// 拡大縮小はコンテストがあるので左右反転も考える
		WazaTool_CalcScaleRateToClactScale( &wk->cap_scale1, &s_x, &s_y );
		if( wk->contest_at == TRUE ){
			s_x = -s_x;
		}
		CATS_ObjectScaleSetCap( wk->poke_cap_at, s_x, s_y );

		WazaTool_PokeOffsetSetOAM(
				wk->poke_cap_at,
				wk->dy, wk->poke_h,
				wk->cap_scale1.work[4], WAZAEFF_OFS_MODE_BOTTOM);//*/
		wk->cap_wait --;
		if( wk->cap_wait < 0 ){
			wk->cap_seq++;
			WazaTool_InitScaleRateEx(
					&wk->cap_scale1,
					WE262_SCALEOUT_SX,
					WE262_SCALEOUT_EX,
					WE262_SCALEOUT_EY,
					WE262_SCALEOUT_EY,
					WE262_SCALE_D,
					WE262_SCALEOUT_XSYNC
					);
		}
		break;
		
	case WE262_SCALEOUT_YX:
		WazaTool_CalcScaleRateEx( &wk->cap_scale1 );
		if( WazaTool_CalcScaleRate( &wk->cap_scale2 ) ){
			
			// 値設定
			wk->cap_scale1.x = wk->cap_scale2.x;

			// 拡大縮小はコンテストがあるので左右反転も考える
			WazaTool_CalcScaleRateToClactScale( &wk->cap_scale1, &s_x, &s_y );
			if( wk->contest_at == TRUE ){
				s_x = -s_x;
			}
			CATS_ObjectScaleSetCap( wk->poke_cap_at, s_x, s_y );

			WazaTool_PokeOffsetSetOAM(
					wk->poke_cap_at,
					wk->dy, wk->poke_h,
					wk->cap_scale1.work[4], WAZAEFF_OFS_MODE_BOTTOM);//*/
		}else{
			wk->cap_seq++;
			// 表示OFF
			CATS_ObjectEnableCap( wk->poke_cap_at_msk, FALSE );
			CATS_ObjectEnableCap( wk->poke_cap_at, FALSE );
			ret = TRUE;
		}
		break;
		
	case WE262_SCALEOUT_END:
		ret = TRUE;
		break;
	}

	return ret;
}

static void We262_ScaleInInit( TWE262_SYS* wk )
{
	s16 mat_x, mat_y;
	f32 s_x, s_y;
	int client_type;
	
	CATS_ObjectPosGetCap( wk->poke_cap_df, &mat_x, &mat_y );
	
	WazaTool_InitStraightSyncFx( 
			&wk->cap_move,
			mat_x, mat_x,
			mat_y - WE262_SCALEIN_MOVE_DIS, mat_y,
			WE262_SCALEIN_MOVE_SYNC
			);

	WazaTool_InitScaleRateEx(
			&wk->cap_scale1,
			WE262_SCALEIN_SX,
			WE262_SCALEIN_EX,
			WE262_SCALEIN_SY,
			WE262_SCALEIN_EY,
			WE262_SCALE_D,
			WE262_SCALEIN_SYNC
			);

	// １回値を設定
	WazaTool_CalcScaleRateToClactScale( &wk->cap_scale1, &s_x, &s_y );
	if( wk->contest_df == TRUE ){
		s_x = -s_x;
	}
	CATS_ObjectScaleSetCap( wk->poke_cap_df, s_x, s_y );
	WazaTool_CalcAndReflectStraightFxCap( &wk->cap_move, wk->poke_cap_df );

	wk->cap_seq = 0;
	wk->cap_wait = WE262_SCALEIN_WAIT;

	client_type = WET_ClientTypeGet(wk->we_sys, WeSysDFNoGet(wk->we_sys));
	CATS_ObjectEnableCap( wk->poke_cap_df_msk, We262_MskOnOff[ client_type ] );
	CATS_ObjectEnableCap( wk->poke_cap_df, TRUE );

	We262_SetPlttColorCap( wk, wk->poke_cap_df );
}

static BOOL We262_ScaleInMove( TWE262_SYS* wk )
{
	f32 s_x, s_y;
	BOOL ret = FALSE;
	BOOL check;
	
	switch( wk->cap_seq ){
	case WE262_SCALEIN_MOVE:
		wk->cap_wait--;
		WazaTool_CalcAndReflectStraightFxCap( &wk->cap_move, wk->poke_cap_df );
		if( wk->cap_wait < 0 ){
			wk->cap_seq++;
		}
		break;
		
	case WE262_SCALEIN_XY_MOVE:
		WazaTool_CalcAndReflectStraightFxCap( &wk->cap_move, wk->poke_cap_df );
		
		// 拡大縮小はコンテストがあるので左右反転も考える
		check = WazaTool_CalcScaleRateEx( &wk->cap_scale1 );
		WazaTool_CalcScaleRateToClactScale( &wk->cap_scale1, &s_x, &s_y );

		if( wk->contest_df == TRUE ){
			s_x = -s_x;
		}
		CATS_ObjectScaleSetCap( wk->poke_cap_df, s_x, s_y );
		if( check == FALSE ){
			wk->cap_seq++;
			ret = TRUE;
		}
		break;
		
	case WE262_SCALEIN_END:
		ret = TRUE;
		break;
	}

	return ret;
}

static void We262_TCB( TCB_PTR tcb, void* work )
{
	TWE262_SYS* wk = work;

	switch( wk->seq ){
	case WE262_FADEIN_INIT:
		WET_DefaultBlendSet( wk->we_sys, WE262_ALPHA_IN_S, 16 - WE262_ALPHA_IN_S );
		WazaTool_StartAlphaFade( 
				&wk->cap_alpha, 
				WE262_ALPHA_IN_S,
				WE262_ALPHA_IN_E,
				16 - WE262_ALPHA_IN_S,
				16 - WE262_ALPHA_IN_E,
				WE262_ALPHA_SYNC);
		wk->seq++;
		break;
		
	case WE262_FADEIN:
		if( WazaTool_EndCheckAlphaFade( &wk->cap_alpha ) ){
			wk->seq++;
			We262_ScaleOutInit( wk );
		}
		break;
		
	case WE262_SCALE_OUT:
		if( We262_ScaleOutMove( wk ) ){
			wk->seq++;

			wk->wait = WE262_SCALE_WAIT_NUM;
		}
		break;

	case WE262_SCALE_WAIT:
		wk->wait --;
		if( wk->wait < 0 ){
			We262_ScaleInInit( wk );
			wk->seq++;
		}
		break;
		
	case WE262_SCALE_IN:
		if( We262_ScaleInMove( wk ) ){
			wk->seq++;
			WazaTool_StartAlphaFade( 
					&wk->cap_alpha, 
					WE262_ALPHA_IN_E,
					WE262_ALPHA_IN_S,
					16 - WE262_ALPHA_IN_E,
					16 - WE262_ALPHA_IN_S,
					WE262_ALPHA_SYNC);
		}
		break;
		
	case WE262_FADEOUT:
		if( WazaTool_EndCheckAlphaFade( &wk->cap_alpha ) ){
			wk->seq++;
		}
		break;
		
	case WE262_END:
		// 終了
		WEEffect_TCB_Delete(wk->we_sys, tcb);
		sys_FreeMemoryEz(wk);
		break;
	}

	// 残像OAM描画
	CATS_Draw(wk->crp);	
}


//----------------------------------------------------------------------------
/**
 * @brief	おきみやげ用タスク登録
 *
 *	@param	we_sys	技エフェクトシステムワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void WestSp_WE_262( WE_SYS_PTR we_sys )
{
	TWE262_SYS* wk;
	SOFT_SPRITE* ssp;
	s16 at_x, at_y;
	s16 df_x, df_y;

	wk = WET_ALLOC_MEMORY(we_sys, TWE262_SYS);
	wk->we_sys	= we_sys;
	wk->crp		= WeSysPokeCrpGet(wk->we_sys);
	wk->pfd		= WeSysPFDGet(wk->we_sys);


	// 攻撃側
	ssp = WeSysSoftSpritePointerGet( wk->we_sys, WeSysATNoGet(we_sys) );
	at_x = SoftSpriteParaGet( ssp, SS_PARA_POS_X );
	at_y = SoftSpriteParaGet( ssp, SS_PARA_POS_Y );
	at_y -= SoftSpriteParaGet( ssp, SS_PARA_SHADOW_HEIGHT );

	// 防御側
	ssp = WeSysSoftSpritePointerGet( wk->we_sys, WeSysDFNoGet(we_sys) );
	df_x = SoftSpriteParaGet( ssp, SS_PARA_POS_X );
	df_y = SoftSpriteParaGet( ssp, SS_PARA_POS_Y );
	df_y -= SoftSpriteParaGet( ssp, SS_PARA_SHADOW_HEIGHT );

	// 攻撃側　高さ　位置を取得
	wk->dy = at_y;
	wk->poke_h = WeSysPokeOfsGet(wk->we_sys, WeSysATNoGet(wk->we_sys));
	
	//かげ
	// 自分の影
	wk->poke_cap_at = WeSysPokeCapGet(wk->we_sys, 0);
	CATS_ObjectPriSetCap( wk->poke_cap_at, WAZAEFF_ACT_SOFTPRI );
	CATS_ObjectBGPriSetCap( wk->poke_cap_at, WAZAEFF_ACT_BGPRI );
	CATS_ObjectPosSetCap( wk->poke_cap_at, at_x, at_y );
	CATS_ObjectEnableCap( wk->poke_cap_at, FALSE );
	CATS_ObjectObjModeSetCap(wk->poke_cap_at, GX_OAM_MODE_XLU);
	CATS_ObjectAffineSetCap( wk->poke_cap_at, CLACT_AFFINE_DOUBLE );

	// 相手の影
	wk->poke_cap_df = WeSysPokeCapGet(wk->we_sys, 1);
	CATS_ObjectPriSetCap( wk->poke_cap_df, WAZAEFF_ACT_SOFTPRI );
	CATS_ObjectBGPriSetCap( wk->poke_cap_df, WAZAEFF_ACT_BGPRI );
	CATS_ObjectPosSetCap( wk->poke_cap_df, df_x, df_y );
	CATS_ObjectEnableCap( wk->poke_cap_df, FALSE );
	CATS_ObjectObjModeSetCap(wk->poke_cap_df, GX_OAM_MODE_XLU);
	CATS_ObjectAffineSetCap( wk->poke_cap_df, CLACT_AFFINE_DOUBLE );
	CATS_ObjectAffinePosSetCap( wk->poke_cap_df, 0, SOFT_SPRITE_SIZE_Y / 2 );

	// コンテストチェック
	wk->contest_at = ContestFlipCheck(wk->we_sys, WEDEF_DROP_M1 ); 
	wk->contest_df = ContestFlipCheck(wk->we_sys, WEDEF_DROP_E1 ); 

	// マスク用
	wk->poke_cap_at_msk = WeSysPokeCapGet(wk->we_sys, 2);
	wk->poke_cap_df_msk = WeSysPokeCapGet(wk->we_sys, 3);

	CATS_ObjectEnableCap( wk->poke_cap_at_msk, FALSE );
	CATS_ObjectEnableCap( wk->poke_cap_df_msk, FALSE );


	WEEffect_TCB_AddPriSet(wk->we_sys, We262_TCB, wk);
}


//-------------------------------------
//	
//	ふういん
//	
//=====================================
enum{
	WE286_SCALEIN_INIT,
	WE286_SCALEIN,
	WE286_MOVE_POKE,
	WE286_SCALEOUT,
	WE286_END,
};

#define WE286_ZANZOU_NUM		( 3 )
#define WE286_ZANZOU_FUU_OAM	( 0 )	// 封OAMの要素数
#define WE286_ZANZOU_SCALE_S	( 25 )
#define WE286_ZANZOU_SCALE_E	( 10 )
#define WE286_ZANZOU_SCALE_D	( 10 )
#define WE286_ZANZOU_SCALE_SYNC	( 10 )
#define WE286_ZANZOU_SCALEOUT_SYNC	( 6 )

#define WE286_ZANZOU_WAIT		( 9 )
#define WE286_ZANZOU_OUT_WAIT	( 5 )
#define WE286_SHAKE_X			( 4 )
#define WE286_SHAKE_SYNC		( 1 )
#define WE286_SHAKE_NUM			( 6 )

typedef struct {
	WE_SYS_PTR	we_sys;
	CATS_SYS_PTR csp;
	CATS_RES_PTR crp;
	int seq;

	// 防御側
	SOFT_SPRITE* df_ssp;
	WAZATOOL_CALCMOVE	df_move;
	s16 df_x;
	s16 df_y;
	
	// 封印残像オブジェクト
	CATS_ACT_PTR zz_cap[ WE286_ZANZOU_NUM ];
	WAZATOOL_ZANZOU zz_sys;
	WAZATOOL_CALCMOVE	zz_move;
} TWE286_SYS;

static void We286_ZZScaleInInit( TWE286_SYS* wk )
{
	WazaTool_InitScaleRate( 
			&wk->zz_move,
			WE286_ZANZOU_SCALE_S,
            WE286_ZANZOU_SCALE_D,   
			WE286_ZANZOU_SCALE_E,
            WE286_ZANZOU_SCALE_SYNC
			);

	WazaTool_InitZanzou( 
			&wk->zz_sys,
			&wk->zz_move,
			WazaTool_CalcScaleRate,
			wk->df_x, wk->df_y,
			WE286_ZANZOU_WAIT,
			WE286_ZANZOU_NUM,
			WAZATOOL_ZANZOU_TYPE_SCALE,
			wk->zz_cap[ 2 ],		// その他
			wk->zz_cap[ 1 ],		// その他
			wk->zz_cap[ WE286_ZANZOU_FUU_OAM ],		// 封
			NULL
			);
}

static void We286_ZZScaleOutInit( TWE286_SYS* wk )
{
	WazaTool_InitScaleRate( 
			&wk->zz_move,
			WE286_ZANZOU_SCALE_E,
            WE286_ZANZOU_SCALE_D,   
			WE286_ZANZOU_SCALE_S,
            WE286_ZANZOU_SCALEOUT_SYNC
			);

	WazaTool_InitZanzou( 
			&wk->zz_sys,
			&wk->zz_move,
			WazaTool_CalcScaleRate,
			wk->df_x, wk->df_y,
			WE286_ZANZOU_OUT_WAIT,
			WE286_ZANZOU_NUM,
			WAZATOOL_ZANZOU_TYPE_SCALE,
			wk->zz_cap[ WE286_ZANZOU_FUU_OAM ],		// 封
			wk->zz_cap[ 1 ],		// その他
			wk->zz_cap[ 2 ],		// その他
			NULL
			);

	CATS_ObjectEnableCap( wk->zz_cap[ WE286_ZANZOU_FUU_OAM ], TRUE );
}

static void We286_TCB( TCB_PTR tcb, void* work )
{
	TWE286_SYS* wk = work;
	int i;

	switch( wk->seq ){
	case WE286_SCALEIN_INIT:
		We286_ZZScaleInInit( wk );
		wk->seq++;
		break;

	case WE286_SCALEIN:
		if( WazaTool_CalcZanzou( &wk->zz_sys ) == FALSE ){
			CATS_ObjectEnableCap( wk->zz_cap[ WE286_ZANZOU_FUU_OAM ], TRUE );
			wk->seq++;

			// ポケモンシェイク
			WazaTool_InitShake( 
					&wk->df_move,
					WE286_SHAKE_X,
					0,
					WE286_SHAKE_SYNC,
					WE286_SHAKE_NUM
					);
		}
		break;
		
	case WE286_MOVE_POKE:
		if( WazaTool_CalcAndReflectShakeSsp( &wk->df_move, wk->df_x, wk->df_y, wk->df_ssp ) == FALSE ){
			wk->seq++;

			We286_ZZScaleOutInit( wk );
		}
		break;
		
	case WE286_SCALEOUT:
		if( WazaTool_CalcZanzou( &wk->zz_sys ) == FALSE ){
			wk->seq++;
		}
		break;
		
	case WE286_END:
		for( i=0; i<WE286_ZANZOU_NUM; i++ ){
			CATS_ActorPointerDelete_S(wk->zz_cap[ i ]);
		}
		sys_FreeMemoryEz(wk);
		WEEffect_TCB_Delete(wk->we_sys, tcb);
		return ;
	}

	CATS_Draw(wk->crp);
}

//----------------------------------------------------------------------------
/**
 * @brief	ふういん用タスク登録
 *
 *	@param	we_sys	技エフェクトシステムワーク
 *	@param	csp		セルアクターツールシステム
 *	@param	crp		セルアクターリソースシステム
 *	@param	cap		セルアクターツールオブジェ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void WestSp_CAT_WE_286(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CATS_ACT_PTR cap)
{
	TWE286_SYS* wk;
	int i;
	TCATS_OBJECT_ADD_PARAM_S coap;

	wk = WET_ALLOC_MEMORY(we_sys, TWE286_SYS);
	wk->we_sys	= we_sys;
	wk->csp		= csp;
	wk->crp		= crp;

	// 防御側
	wk->df_ssp = WeSysSoftSpritePointerGet( wk->we_sys, WeSysDFNoGet(we_sys) );
	wk->df_x = SoftSpriteParaGet( wk->df_ssp, SS_PARA_POS_X );
	wk->df_y = SoftSpriteParaGet( wk->df_ssp, SS_PARA_POS_Y );
	wk->df_y -= SoftSpriteParaGet( wk->df_ssp, SS_PARA_SHADOW_HEIGHT );
	
	// 残像
	coap   = WeSysCoapGet(we_sys);
	for( i=0; i<WE286_ZANZOU_NUM; i++ ){
		if( i == WE286_ZANZOU_FUU_OAM ){
			wk->zz_cap[ i ] = cap;
			// 最初のアクターは違う絵になる
			CATS_ObjectAnimeSeqSetCap( wk->zz_cap[ i ], 1 );
		}else{
			wk->zz_cap[ i ] = CATS_ObjectAdd_S(wk->csp, wk->crp, &coap);
			// ほかは半透明
			CATS_ObjectObjModeSetCap( wk->zz_cap[ i ], GX_OAM_MODE_XLU );
		}
		CATS_ObjectPriSetCap( wk->zz_cap[ i ], WAZAEFF_ACT_SOFTPRI );
		CATS_ObjectBGPriSetCap( wk->zz_cap[ i ], WAZAEFF_ACT_BGPRI );
		CATS_ObjectPosSetCap( wk->zz_cap[ i ], wk->df_x, wk->df_y );
		CATS_ObjectEnableCap( wk->zz_cap[ i ], FALSE );
		CATS_ObjectAffineSetCap( wk->zz_cap[ i ], CLACT_AFFINE_DOUBLE );
	}

	WEEffect_TCB_AddPriSet(wk->we_sys, We286_TCB, wk);
}


//-------------------------------------
//	
//	おんねん
//	
//=====================================
enum{
	WE288_MOVE_START,
	WE288_FADE_IN,
	WE288_FADE_OUT_WAIT,
	WE288_FADE_OUT,
	WE288_END,
};


#define WE288_CAP_NUM			( 6 )	// ここかえたら288.sもかえる
#define WE288_CAP_H_SUM			( 5 )	// 上下は何倍速で動かすか
#define WE288_CAP_H_DIS			( FX32_ONE*10 )
#define WE288_CAP_ROTA_S		( FX_GET_ROTA_NUM( 0 ) )
#define WE288_CAP_ROTA_E		( FX_GET_ROTA_NUM( 180 ) )
#define WE288_CAP_ROTA_SYNC		( 48 )
#define WE288_CAP_ROTA_WIDTH	( FX32_ONE*50 )
#define WE288_CAP_ALPHA_S		( 1 )
#define WE288_CAP_ALPHA_E		( 16 )
#define WE288_CAP_ALPHA_SYNC	( 10 )

#define WE288_CAP_ALPHAOUT_WAIT	( WE288_CAP_ROTA_SYNC - (WE288_CAP_ALPHA_SYNC*2) )
 
typedef struct {
	WE_SYS_PTR	we_sys;
	CATS_SYS_PTR csp;
	CATS_RES_PTR crp;
	int seq;
	int wait;

	int vec_x;

	//おんねん
	CATS_ACT_PTR cap[ WE288_CAP_NUM ];
	WAZATOOL_CALCMOVE cap_move[ WE288_CAP_NUM ];	// 横移動
	WAZATOOL_ALPHA_FADE cap_alpha;	// アルファ変換
	s16 cap_cx;
	s16 cap_cy;
} TWE288_SYS;

static void We288_CapInit( TWE288_SYS* wk, int vec_x )
{
	int i;
	int rota_offs_one;

	rota_offs_one = FX_GET_ROTA_NUM( 360 ) / WE288_CAP_NUM;
	
	// 計算データ作成
	for( i=0; i<WE288_CAP_NUM; i++ ){
		WazaTool_InitRotaFx(
				&wk->cap_move[ i ],
				WE288_CAP_ROTA_S,
				WE288_CAP_ROTA_E,
				0,0,
				WE288_CAP_ROTA_WIDTH, 0,
				WE288_CAP_ROTA_SYNC
				);
		wk->cap_move[i].work[1] += (rota_offs_one*i);
		wk->cap_move[i].work[5] *= vec_x;
	}

}

static void We288_CapMove( TWE288_SYS* wk )
{
	int i;
	s16 ofs_y;
	u16 rota;

	for( i=0; i<WE288_CAP_NUM; i++ ){
		
		// 計算
		WazaTool_CalcRotaFx( &wk->cap_move[ i ] );
		
		// yオフセット座標を求める
		rota = wk->cap_move[ i ].work[ 1 ] * WE288_CAP_H_SUM;
		ofs_y = FX_Mul( FX_SinIdx( rota ), WE288_CAP_H_DIS*wk->vec_x ) >> FX32_SHIFT;

		// 反映
		CATS_ObjectPosSetCap( wk->cap[ i ],
				wk->cap_cx + wk->cap_move[ i ].x,
				wk->cap_cy + ofs_y );

		// 角度でBG優先順位を変える
		if( (wk->cap_move[ i ].work[ 1 ] >= FX_GET_ROTA_NUM(90)) &&
			(wk->cap_move[ i ].work[ 1 ] <= FX_GET_ROTA_NUM(269)) ){
			
			CATS_ObjectBGPriSetCap( wk->cap[ i ], WAZAEFF_ACT_BGPRI );
		}else{

			CATS_ObjectBGPriSetCap( wk->cap[ i ], BT_3DPriorityGet(wk->we_sys)+1 );
		}//*/
	}
}

static void We288_TCB( TCB_PTR tcb, void* work )
{
	TWE288_SYS* wk = work;
	int i;

	switch( wk->seq ){
	case WE288_MOVE_START:
		// アルファ設定
		WET_DefaultBlendSet( wk->we_sys,
				WE288_CAP_ALPHA_S, 16 - WE288_CAP_ALPHA_S );
		WazaTool_StartAlphaFade(
				&wk->cap_alpha,
				WE288_CAP_ALPHA_S, WE288_CAP_ALPHA_E,
				16 - WE288_CAP_ALPHA_S, 16 - WE288_CAP_ALPHA_E,
				WE288_CAP_ALPHA_SYNC
				);
		// オブジェ
		We288_CapInit( wk, wk->vec_x );
		We288_CapMove( wk );
		wk->seq++;
		break;
		
	case WE288_FADE_IN:
		We288_CapMove( wk );
		if( WazaTool_EndCheckAlphaFade( &wk->cap_alpha ) ){
			wk->seq++;
			wk->wait = WE288_CAP_ALPHAOUT_WAIT;
		}
		break;
		
	case WE288_FADE_OUT_WAIT:
		We288_CapMove( wk );
		wk->wait --;
		if( wk->wait < 0 ){
			wk->seq++;
			WazaTool_StartAlphaFade(
					&wk->cap_alpha,
					WE288_CAP_ALPHA_E, WE288_CAP_ALPHA_S, 
					16 - WE288_CAP_ALPHA_E, 16 - WE288_CAP_ALPHA_S, 
					WE288_CAP_ALPHA_SYNC
					);
		}
		break;
		
	case WE288_FADE_OUT:
		We288_CapMove( wk );
		if( WazaTool_EndCheckAlphaFade( &wk->cap_alpha ) ){
			wk->seq++;
		}
		break;

	case WE288_END:
		for( i=0; i<WE288_CAP_NUM; i++ ){
			CATS_ActorPointerDelete_S(wk->cap[ i ]);
		}
		sys_FreeMemoryEz(wk);
		WEEffect_TCB_Delete(wk->we_sys, tcb);
		return ;
	}

	CATS_Draw(wk->crp);
}

//----------------------------------------------------------------------------
/**
 * @brief	おんねん用タスク登録
 *
 *	@param	we_sys	技エフェクトシステムワーク
 *	@param	csp		セルアクターツールシステム
 *	@param	crp		セルアクターリソースシステム
 *	@param	cap		セルアクターツールオブジェ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void WestSp_CAT_WE_288(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CATS_ACT_PTR cap)
{
	TWE288_SYS* wk;
	int i;
	SOFT_SPRITE* at_ssp;
	TCATS_OBJECT_ADD_PARAM_S coap;

	wk = WET_ALLOC_MEMORY(we_sys, TWE288_SYS);
	wk->we_sys	= we_sys;
	wk->csp		= csp;
	wk->crp		= crp;

	// 攻撃側
	at_ssp = WeSysSoftSpritePointerGet( wk->we_sys, WeSysATNoGet(we_sys) );
	wk->cap_cx = SoftSpriteParaGet( at_ssp, SS_PARA_POS_X );
	wk->cap_cy = SoftSpriteParaGet( at_ssp, SS_PARA_POS_Y );
	
	// おんねん
	coap   = WeSysCoapGet(we_sys);
	for( i=0; i<WE288_CAP_NUM ; i++ ){
		if( i == 0 ){
			wk->cap[ i ] =  cap;
		}else{
			wk->cap[ i ] = CATS_ObjectAdd_S(wk->csp, wk->crp, &coap);
		}
		CATS_ObjectPriSetCap( wk->cap[ i ], WAZAEFF_ACT_SOFTPRI );
		CATS_ObjectObjModeSetCap( wk->cap[ i ], GX_OAM_MODE_XLU );
		CATS_ObjectAutoAnimeSetCap( wk->cap[ i ], TRUE );
	}
	
	wk->vec_x = WazaTool_VecChangeX( wk->we_sys, WeSysATNoGet(wk->we_sys) );

	WEEffect_TCB_AddPriSet(wk->we_sys, We288_TCB, wk);
}


//-------------------------------------
//	
//	くさぶえ
//	
//=====================================
#define WE320_CAP_NUM	( 15 )		// ここかえたらwe_320.sも変える
#define WE320_CAP_GRA_NUM	( 3 )	// 絵の種類
#define WE320_CAP_STR_SX	( 0 )
#define WE320_CAP_STR_EX	( 256 )
#define WE320_CAP_STR_SY	( 0 )
#define WE320_CAP_STR_EY	( -128 )
#define WE320_CAP_STR_SYNC	( 59 )

#define WE320_CAP_Y_OFS_ROTA	( FX_GET_ROTA_NUM( 2 ) )
#define WE320_CAP_Y_HEIGHT		( FX32_ONE*14 )
#define WE320_CAP_SCALE_DEF		( 1.0f )
#define WE320_CAP_SCALE_NUM		( FX32_CONST(0.17f) )

#define WE320_CAP_START_WAIT	( 6 )

typedef struct {
	WE_SYS_PTR	we_sys;
	CATS_SYS_PTR csp;
	CATS_RES_PTR crp;
	int seq;
	int vec_x;
	int vec_y;

	//音符
	CATS_ACT_PTR cap[ WE320_CAP_NUM ];
	WAZATOOL_CALCMOVE cap_move[ WE320_CAP_NUM ];	// 斜め移動
	int cap_wait;
	int cap_count;
} TWE320_SYS;

static void We320_CapObjStart( CATS_ACT_PTR cap, WAZATOOL_CALCMOVE* p_wtc, int vec_x, int vec_y )
{
	s16 n_x, n_y;

	CATS_ObjectPosGetCap( cap, &n_x, &n_y );
	
	WazaTool_InitStraightSyncFx( 
			p_wtc,
			n_x + (WE320_CAP_STR_SX * vec_x),
			n_x + (WE320_CAP_STR_EX * vec_x),
			n_y + (WE320_CAP_STR_SY * vec_y),
			n_y + (WE320_CAP_STR_EY * vec_y),
			WE320_CAP_STR_SYNC
			);

	CATS_ObjectEnableCap( cap, TRUE );
}

static BOOL We320_CapObjMove( CATS_ACT_PTR cap, WAZATOOL_CALCMOVE* p_wtc )
{
	s16 cap_x, cap_y;
	s16 ofs_y;
	fx32 scale_work;
	f32 scale;
	u16 rota;
	
	if( WazaTool_CalcAndReflectStraightFxCap( p_wtc, cap ) ){
		
		CATS_ObjectPosGetCap( cap, &cap_x, &cap_y );

		rota = cap_x * WE320_CAP_Y_OFS_ROTA;
		
		// x座標によりY座標の波と拡大縮小値を決める
		// Y座標
		ofs_y = FX_Mul( FX_SinIdx( rota ), WE320_CAP_Y_HEIGHT ) >> FX32_SHIFT;
		CATS_ObjectPosSetCap( cap, cap_x, cap_y + ofs_y );

		// 拡縮値
		scale_work = FX_Mul( FX_SinIdx( rota ), WE320_CAP_SCALE_NUM );
		scale_work *= -1;
		scale = WE320_CAP_SCALE_DEF + FX_FX32_TO_F32( scale_work );
		CATS_ObjectScaleSetCap( cap, scale, scale );
		return FALSE;
	}

	return TRUE;
}

static BOOL We320_CapObjManager( TWE320_SYS* wk )
{
	int i;
	BOOL check;
	
	// 発射管理
	if( wk->cap_count < WE320_CAP_NUM ){
		wk->cap_wait++;
		if( wk->cap_wait > WE320_CAP_START_WAIT ){
			wk->cap_wait = 0;
			
			We320_CapObjStart(
					wk->cap[ wk->cap_count ], 
					&wk->cap_move[ wk->cap_count ],
					wk->vec_x, wk->vec_y );
			wk->cap_count++;
		}
	}

	// 動作管理
	for( i = 0; i < wk->cap_count; i++ ){

		check = We320_CapObjMove( wk->cap[ i ], &wk->cap_move[ i ] );
	}

	// 終了チェック部
	if( wk->cap_count >= WE320_CAP_NUM ){
		if( check == TRUE ){
			return TRUE;
		}
	}

	return FALSE;
}

static void We320_TCB( TCB_PTR tcb, void* work )
{
	TWE320_SYS* wk = work;
	int i;

	if( We320_CapObjManager(wk) ){

		// 終了
		for( i=0; i<WE320_CAP_NUM; i++ ){
			CATS_ActorPointerDelete_S(wk->cap[ i ]);
		}
		sys_FreeMemoryEz(wk);
		WEEffect_TCB_Delete(wk->we_sys, tcb);
	}else{

		CATS_Draw(wk->crp);
	}
}

//----------------------------------------------------------------------------
/**
 * @brief	草笛用タスク登録
 *
 *	@param	we_sys	技エフェクトシステムワーク
 *	@param	csp		セルアクターツールシステム
 *	@param	crp		セルアクターリソースシステム
 *	@param	cap		セルアクターツールオブジェ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void WestSp_CAT_WE_320(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CATS_ACT_PTR cap)
{
	TWE320_SYS* wk;
	int i;
	s16 at_x, at_y;
	SOFT_SPRITE* at_ssp;
	TCATS_OBJECT_ADD_PARAM_S coap;

	wk = WET_ALLOC_MEMORY(we_sys, TWE320_SYS);
	wk->we_sys	= we_sys;
	wk->csp		= csp;
	wk->crp		= crp;

	// 攻撃側
	at_ssp = WeSysSoftSpritePointerGet( wk->we_sys, WeSysATNoGet(we_sys) );
	at_x = SoftSpriteParaGet( at_ssp, SS_PARA_POS_X );
	at_y = SoftSpriteParaGet( at_ssp, SS_PARA_POS_Y );
	
	// 音符
	coap   = WeSysCoapGet(we_sys);
	for( i=0; i<WE320_CAP_NUM ; i++ ){
		if( i == 0 ){
			wk->cap[ i ] =  cap;
		}else{
			wk->cap[ i ] = CATS_ObjectAdd_S(wk->csp, wk->crp, &coap);
		}
		CATS_ObjectPriSetCap( wk->cap[ i ], WAZAEFF_ACT_SOFTPRI );
		CATS_ObjectBGPriSetCap( wk->cap[ i ], WAZAEFF_ACT_BGPRI );
		CATS_ObjectAffineSetCap(wk->cap[ i ], CLACT_AFFINE_DOUBLE);
		CATS_ObjectEnableCap(wk->cap[ i ], FALSE);
		CATS_ObjectPosSetCap( wk->cap[ i ], at_x, at_y );

		// 絵を変更
		CATS_ObjectAnimeSeqSetCap( wk->cap[ i ], i % WE320_CAP_GRA_NUM );
	}
	
	wk->vec_x = WazaTool_VecChangeX( wk->we_sys, WeSysATNoGet(wk->we_sys) );
	wk->vec_y = WazaTool_VecChangeY( wk->we_sys, WeSysATNoGet(wk->we_sys) );

	WEEffect_TCB_AddPriSet(wk->we_sys, We320_TCB, wk);
}


//-------------------------------------
//	
//	じんつうりき
//	
//=====================================

// じんつうりき　防御側動作
enum{
	WE326_DF_SWITCH,
	WE326_DF_WAIT,
	WE326_DF_END,
};

#define WE326_ROTA_ADD_NUM	( FX_GET_ROTA_NUM(180) / SOFT_SPRITE_SIZE_Y )
#define WE326_ROTA_NUM_0	( FX_GET_ROTA_NUM(180) )
#define WE326_ROTA_NUM_1	( FX_GET_ROTA_NUM(180) )
#define WE326_WIDTH0_NUM		( 5 )
#define WE326_WIDTH1_NUM		( -5 )
#define WE326_WIDTH2_NUM		( 10 )
#define WE326_CHANGE_NUM	( 3 )
#define WE326_CHANGE_WAIT	( 16 )
#define WE326_ROTA0_WIDTH	( 16*FX32_ONE )
#define WE326_ROTA1_WIDTH	( -16*FX32_ONE )
#define WE326_ROTA2_WIDTH	( 20*FX32_ONE )
#define WE326_WIDTH_OFS	( 1*FX32_ONE )
#define WE326_MAT_OFS	(-8)
typedef struct {
	WE_SYS_PTR we_sys;
	WAZATOOL_DEFLASTER_PTR p_laster;
	int seq;

	SOFT_SPRITE* ssp;

	int effect_y;
	int center_y;
	int rota_num;
	fx32 rota_width;
	int rota_width_ofs_flg;
	int width_a;
	int wait;
	int count;
	u32 init_num;
} TWE326_DF_SYS;

static void We326DF_ParamSet( TWE326_DF_SYS* wk )
{
	switch( wk->count ){
	case 0:
		wk->rota_num	= WE326_ROTA_NUM_0;
		wk->width_a		= WE326_WIDTH0_NUM;
		wk->rota_width	= WE326_ROTA0_WIDTH;
		wk->wait		= WE326_CHANGE_WAIT;
		break;

	case 1:
		wk->rota_num = WE326_ROTA_NUM_1;
		wk->width_a = WE326_WIDTH1_NUM;
		wk->rota_width	= WE326_ROTA1_WIDTH;
		wk->wait	= WE326_CHANGE_WAIT;
		break;

	case 2:
		wk->rota_num = WE326_ROTA_NUM_0;
		wk->width_a = WE326_WIDTH2_NUM;
		wk->rota_width	= WE326_ROTA2_WIDTH;
		wk->wait	= WE326_CHANGE_WAIT;
		wk->wait	= WE326_CHANGE_WAIT;
		break;
	}
}

static void We326DF_BuffSet( TWE326_DF_SYS* wk )
{
	u32* buff = WazaTool_GetDefLasterWriteBuff( wk->p_laster );
	int i;
	s16 ofs_x;
	s16 now_x;
	s16 now_y;
	u16 rota_num;
	int width;
	int start = wk->effect_y + WE326_MAT_OFS;
	int end = wk->effect_y + SOFT_SPRITE_SIZE_Y - WE326_MAT_OFS;
	int in_buff;

	if( start < 0 ){
		start = 0;
	}
	if( end > 192 ){
		end = 192;
	}
	
	// 震わせるため回転半径の幅を補正するタイミングを
	// 交互に変える
	wk->rota_width_ofs_flg *= -1;
	
	// sinカーブを作成＆wodth_aと座標ｙを使用して横移動値を求める
	for( i= start; i< end; i++ ){

		if( i & 2 ){
			width = wk->rota_width + (WE326_WIDTH_OFS * wk->rota_width_ofs_flg);
		}else{
			width = wk->rota_width - (WE326_WIDTH_OFS * wk->rota_width_ofs_flg);
		}
		
		rota_num = wk->rota_num + WE326_ROTA_ADD_NUM * (i - start);
		ofs_x = FX_Mul( FX_SinIdx( rota_num ), width ) >> FX32_SHIFT;
		ofs_x += ((i - wk->center_y) * wk->width_a) / 10;

		// 値設定
		now_x = wk->init_num & 0xffff;
		now_y = wk->init_num >> 16;

		// 1つ前のバッファに入れておく
		in_buff = i - 1;
		if( in_buff < 0 ){
			in_buff += 192;
		}
		buff[ in_buff ] = WazaTool_GetLasterBuffMatrixData( now_x + ofs_x, now_y );
	}
}

static void We326DF_TCB( TCB_PTR tcb, void* work )
{
	TWE326_DF_SYS* wk = work;

	switch( wk->seq ){
	case WE326_DF_SWITCH:
		We326DF_ParamSet( wk );
		We326DF_BuffSet( wk );
		wk->seq++;
		break;
		
	case WE326_DF_WAIT:
		wk->wait --;
		We326DF_BuffSet( wk );
		if( wk->wait < 0 ){
			wk->count++;
			if( wk->count < WE326_CHANGE_NUM ){
				wk->seq = WE326_DF_SWITCH;
			}else{
				wk->seq++;
			}
		}
		break;
		
	case WE326_DF_END:
		SoftSpriteParaSet( wk->ssp, SS_PARA_VANISH, FALSE );
		WazaTool_StopDefLaster( wk->p_laster );
		WazaTool_DeleteDefLaster( wk->p_laster );

		GF_BGL_PrioritySet( BT_BGL_FrameGet(wk->we_sys, WES_BF_EFFECT), BT_BGPriorityGet( wk->we_sys, WES_BF_EFFECT ) );
		GF_BGL_PrioritySet( GF_BGL_FRAME0_M, BT_3DPriorityGet(wk->we_sys) );

		// キャラクタデータクリア
		GF_BGL_ClearCharSet( BT_BGL_FrameGet(wk->we_sys, WES_BF_EFFECT), 0x4000, 0, WeSysHeapAreaGet(wk->we_sys) );
		GF_BGL_ScrClear( WeSysBGLPointerGet(wk->we_sys) ,BT_BGL_FrameGet(wk->we_sys, WES_BF_EFFECT) );
		
		sys_FreeMemoryEz(wk);
		WEEffect_TCB_Delete(wk->we_sys, tcb);
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	神通力をうけたエフェクト
 *
 *	@param	we_sys		技エフェクトシステム
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void WestSp_WE_326DF(WE_SYS_PTR we_sys)
{
	TWE326_DF_SYS* wk;
	SOFT_SPRITE* ssp;
	s16 ssp_x, ssp_y;
	int client_type;

	wk = WET_ALLOC_MEMORY(we_sys, TWE326_DF_SYS);
	wk->we_sys	= we_sys;
	
	// 防御側座標を取得
	wk->ssp = WeSysSoftSpritePointerGet( wk->we_sys, WeSysDFNoGet(we_sys) );
	ssp_x = SoftSpriteParaGet( wk->ssp, SS_PARA_POS_X );
	ssp_y = SoftSpriteParaGet( wk->ssp, SS_PARA_POS_Y );
	ssp_y -= SoftSpriteParaGet(wk->ssp, SS_PARA_SHADOW_HEIGHT);

	SoftSpriteParaSet( wk->ssp, SS_PARA_VANISH, TRUE );
	
	wk->center_y = ssp_y;
	
	ssp_x = ssp_x - (SOFT_SPRITE_SIZE_X/2);
	wk->effect_y = ssp_y - (SOFT_SPRITE_SIZE_Y/2);
	
	wk->init_num = WazaTool_GetLasterBuffMatrixData( -ssp_x, -wk->effect_y );

	// ラスターシステム作成
	wk->p_laster = WazaTool_InitDefLaster( 
			WazaTool_GetLasterBGDestAddr( BT_BGL_BGNoGet(wk->we_sys, WES_BF_EFFECT) ),
			wk->init_num,
			WeSysHeapAreaGet(wk->we_sys)
			);

	wk->rota_width_ofs_flg = 1;


	// 当てるOBJの位置によりBGpriorityを変更する
	client_type = WET_ClientTypeGet( wk->we_sys, WeSysDFNoGet(we_sys) );
	if( (client_type == CLIENT_TYPE_B) || (client_type == CLIENT_TYPE_C) ){
		GF_BGL_PrioritySet( BT_BGL_FrameGet(wk->we_sys, WES_BF_EFFECT), BT_3DPriorityGet(wk->we_sys) );
		GF_BGL_PrioritySet( GF_BGL_FRAME0_M, BT_3DPriorityGet(wk->we_sys) + 1 );
	}

	WEEffect_TCB_AddPriSet(wk->we_sys, We326DF_TCB, wk);
}


//-------------------------------------
//	
//	ねこだまし
//	
//=====================================
// wndマスク～ブライトネスフェード
enum{
	WE252_BACK_MASKFADE_START,
	WE252_BACK_MASKFADE,
	WE252_BACK_MASKFADE_AND_BRFADEOUT,
	WE252_BACK_BRIGHTNESS_FADEOUT,
	WE252_BACK_BRIGHTNESS_FADEIN,
	WE252_BACK_END,
};

#define WE252_BACK_MSKFADE_SX	( 127 )
#define WE252_BACK_MSKFADE_EX	( 0 )
#define WE252_BACK_MSKFADE_SYNC	( 8 )

#define WE252_BACK_BROUT_SYNC	( 8 )
//#define WE252_BACK_BRIN_SYNC	( 20 )
#define WE252_BACK_BRIN_SYNC	( 0 )

#define WE252_BACK_BR_WAIT		( 7 )

typedef struct {
	WE_SYS_PTR we_sys;
	int seq;
	int wait;
	WAZATOOL_CALCMOVE wnd_move;
}TWE252_BACK_SYS;


//----------------------------------------------------------------------------
/**
 *
 *	@brief	ねこだましの背景エフェクト
 *
 *	@param	tcb		TCBワーク
 *	@param	work	ワーク
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void We252Back_TCB( TCB_PTR tcb, void* work )
{
	TWE252_BACK_SYS* wk = work;

	switch( wk->seq ){
	case WE252_BACK_MASKFADE_START:
		WazaTool_InitStraightSyncFx(  
				&wk->wnd_move,
				WE252_BACK_MSKFADE_SX,
				WE252_BACK_MSKFADE_EX,
				0,0,
				WE252_BACK_MSKFADE_SYNC
				);
		// マスク設定
		GX_SetVisibleWnd( GX_WNDMASK_W0 );
		WET_DefaultWndMskSet( 
				wk->we_sys,
				WET_WNDMSK_0,
				FALSE );
		G2_SetWnd0Position( 0, 0, 255, 191 );
		wk->wait = WE252_BACK_BR_WAIT;
		wk->seq++;
		break;
		
	case WE252_BACK_MASKFADE:
		wk->wait --;
		if( wk->wait < 0 ){

			PaletteFadeReq(WeSysPFDGet(wk->we_sys), PF_BIT_MAIN_BG, BT_HaikeiFadeBit( wk->we_sys ), WE252_BACK_BRIN_SYNC, 0, 16, 0xffff);
/*			// ブライトネスフェード
			ChangeBrightnessRequest(
					WE252_BACK_BROUT_SYNC,
					BRIGHTNESS_WHITE,
					BRIGHTNESS_NORMAL,
					(1 << BT_BGL_BGNoGet(wk->we_sys, WES_BF_WINDOW )) | (1 << BT_BGL_BGNoGet(wk->we_sys, WES_BF_BACKGROUND)),
					MASK_MAIN_DISPLAY
					);//*/

			wk->seq++;
		}
		break;

	case WE252_BACK_MASKFADE_AND_BRFADEOUT:
		if( WazaTool_CalcStraightFx( &wk->wnd_move ) ){
			G2_SetWnd0Position( 
					127 - wk->wnd_move.x,
					0,
					128 + wk->wnd_move.x,
					191 );
		}else{
			wk->seq++;
		}
		break;
		
	case WE252_BACK_BRIGHTNESS_FADEOUT:
		if( PaletteFadeCheck(WeSysPFDGet(wk->we_sys)) == 0 ){
			wk->seq++;

			// ウィンドウマスクOFF
			GX_SetVisibleWnd( GX_WNDMASK_NONE );

			PaletteFadeReq(WeSysPFDGet(wk->we_sys), PF_BIT_MAIN_BG, BT_HaikeiFadeBit( wk->we_sys ), WE252_BACK_BRIN_SYNC, 16, 0, 0xffff);
			
			// ブライトネスフェード
/*			ChangeBrightnessRequest(
					WE252_BACK_BRIN_SYNC,
					BRIGHTNESS_NORMAL,
					BRIGHTNESS_WHITE,
					(1 << BT_BGL_BGNoGet(wk->we_sys, WES_BF_WINDOW )) | (1 << BT_BGL_BGNoGet(wk->we_sys, WES_BF_BACKGROUND)),
					MASK_MAIN_DISPLAY
					);//*/
		}
		break;
		
	case WE252_BACK_BRIGHTNESS_FADEIN:
		if( PaletteFadeCheck(WeSysPFDGet(wk->we_sys)) == 0 ){
			wk->seq++;
		}
		break;
			
	case WE252_BACK_END:
		sys_FreeMemoryEz(wk);
		WEEffect_TCB_Delete(wk->we_sys, tcb);
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ねこだましをうけたエフェクト
 *
 *	@param	we_sys		技エフェクトシステム
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void WestSp_WE_252Back(WE_SYS_PTR we_sys)
{
	TWE252_BACK_SYS* wk;

	wk = WET_ALLOC_MEMORY(we_sys, TWE326_DF_SYS);
	wk->we_sys	= we_sys;

	WEEffect_TCB_AddPriSet(wk->we_sys, We252Back_TCB, wk);
}

enum{
	WE252_CAP_START,
	WE252_CAP_ALPHAIN,
	WE252_CAP_ANM,
	WE252_CAP_ALPHAOUT,
	WE252_CAP_END,
};
#define WE252_CAP_ALPHA_S	( 0 )
#define WE252_CAP_ALPHA_E	( 16 )
#define WE252_CAP_SYNC		( 8 )
typedef struct {
	WE_SYS_PTR we_sys;
	CATS_SYS_PTR csp;
	CATS_RES_PTR crp;
	int seq;

	CATS_ACT_PTR cap;
	
	WAZATOOL_ALPHA_FADE alpha;
} TWE252_CAP_DRAW;


static void WeCat252_DrawCapTcb( TCB_PTR tcb, void* work )
{
	TWE252_CAP_DRAW* wk = work;
	
	switch( wk->seq ){
	case WE252_CAP_START:
		WET_DefaultBlendSet( wk->we_sys, WE252_CAP_ALPHA_S, 16 - WE252_CAP_ALPHA_S );			
		WazaTool_StartAlphaFade(
				&wk->alpha,
				WE252_CAP_ALPHA_S, WE252_CAP_ALPHA_E,
				16 - WE252_CAP_ALPHA_S, 16 - WE252_CAP_ALPHA_E,
				WE252_CAP_SYNC
				);
		wk->seq++;
		break;
		
	case WE252_CAP_ALPHAIN:
		if( WazaTool_EndCheckAlphaFade( &wk->alpha ) ){
			wk->seq++;
		}
		break;
		
	case WE252_CAP_ANM:
		if( CATS_ObjectAnimeActiveCheckCap( wk->cap ) == FALSE ){
			wk->seq++;
			WazaTool_StartAlphaFade(
					&wk->alpha,
					WE252_CAP_ALPHA_E, WE252_CAP_ALPHA_S,
					16 - WE252_CAP_ALPHA_E, 16 - WE252_CAP_ALPHA_S,
					WE252_CAP_SYNC
					);
		}
		break;
		
	case WE252_CAP_ALPHAOUT:
		if( WazaTool_EndCheckAlphaFade( &wk->alpha ) ){
			wk->seq++;
		}
		break;
		
	case WE252_CAP_END:
		CATS_ActorPointerDelete_S(wk->cap);
		// 終了
		WEEffect_TCB_Delete(wk->we_sys, tcb);
		sys_FreeMemoryEz(wk);
		return;
	}

	// OAM描画
	CATS_Draw(wk->crp);	
}

//----------------------------------------------------------------------------
/**
 * @brief	オートアニメが終わるまで描画
 *
 *	@param	we_sys	技エフェクトシステムワーク
 *	@param	csp		セルアクターツールシステム
 *	@param	crp		セルアクターリソースシステム
 *	@param	cap		セルアクターツールオブジェ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void WestSp_CAT_WE_252_DrawCap(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CATS_ACT_PTR cap)
{
	TWE252_CAP_DRAW* wk;

	wk = WET_ALLOC_MEMORY(we_sys, TWE252_CAP_DRAW);
	wk->we_sys	= we_sys;
	wk->csp		= csp;
	wk->crp		= crp;
	wk->cap		= cap;

	CATS_ObjectAutoAnimeSetCap( wk->cap, TRUE );
	CATS_ObjectObjModeSetCap( wk->cap, GX_OAM_MODE_XLU );

	WEEffect_TCB_AddPriSet(wk->we_sys, WeCat252_DrawCapTcb, wk);
}


//-------------------------------------
//	
//	ポケモンを震えさせながら拡縮
//	
//=====================================
enum{
	WE252_POKE_SSP_SCALEUP_INIT,
	WE252_POKE_SSP_SCALEUP,
	WE252_POKE_SSP_SCALEDOWN_INIT,
	WE252_POKE_SSP_SCALEDOWN,
	WE252_POKE_SSP_SCALEEND,
};

#define NEKODAMASI_SC_SX		(10)
#define NEKODAMASI_SC_EX		(7)
#define NEKODAMASI_SC_SY		(10)
#define NEKODAMASI_SC_EY		(30)
#define NEKODAMASI_SC_D			(10)
#define NEKODAMASI_SC_NUM		(1)
#define NEKODAMASI_SC_SYNC		((4 << 16) | 3)

#define WE252_SHAKE_WIDTH	( 2 )
#define WE252_SHAKE_NUM		( 2 )
#define WE252_SHAKE_SYNC	( 1 )


typedef struct {
	WE_SYS_PTR we_sys;
	int seq;

	s16 dy;			// 今のポジション
	s16 dx;			// 今のポジション
	s16 poke_h;		// ポケモンの高さ

	// ポケモン
	SOFT_SPRITE*	ssp;
	WAZATOOL_CALCMOVE	ssp_scale;
	WAZATOOL_CALCMOVE	ssp_shak;

	int scale_sx;
	int scale_ex;
	int scale_sy;
	int scale_ey;
	int scale_d;
	int scale_num;		// 伸びて縮むを１とした回数
	int scale_sync;		// 伸びて縮むに１回のしんく数
} TWE252_POKE_SSP_SCALE_UPDOWN;

static void We252SSPPokeScaleUpDownTCB( TCB_PTR tcb, void* work )
{
	TWE252_POKE_SSP_SCALE_UPDOWN* wk = work;
	BOOL check;

	switch( wk->seq ){
	case WE252_POKE_SSP_SCALEUP_INIT:
		WazaTool_InitScaleRateEx(
				&wk->ssp_scale,
				wk->scale_sx,
				wk->scale_ex,
				wk->scale_sy,
				wk->scale_ey,
				wk->scale_d,
				wk->scale_sync >> 16
				);
		WazaTool_CalcAndReflectShakeSsp( &wk->ssp_shak, wk->dx, wk->dy, wk->ssp );
		WazaTool_CalcAndReflectScaleRateExSsp( &wk->ssp_scale, wk->ssp );

		WazaTool_PokeOffsetSet(
				wk->ssp,
				wk->dy, wk->poke_h,
				wk->ssp_scale.work[4], WAZAEFF_OFS_MODE_BOTTOM);//*/
		wk->seq++;
		break;
		
	case WE252_POKE_SSP_SCALEUP:
		WazaTool_CalcAndReflectShakeSsp( &wk->ssp_shak, wk->dx, wk->dy, wk->ssp );
		check = WazaTool_CalcAndReflectScaleRateExSsp( &wk->ssp_scale, wk->ssp );
		WazaTool_PokeOffsetSet(
				wk->ssp,
				wk->dy, wk->poke_h,
				wk->ssp_scale.work[4], WAZAEFF_OFS_MODE_BOTTOM);//*/
		
		if( check == FALSE ){
			wk->seq++;
		}
		break;
		
	case WE252_POKE_SSP_SCALEDOWN_INIT:
		WazaTool_InitScaleRateEx(
				&wk->ssp_scale,
				wk->scale_ex,
				wk->scale_sx,
				wk->scale_ey,
				wk->scale_sy,
				wk->scale_d,
				wk->scale_sync & 0xffff
				);
		WazaTool_CalcAndReflectShakeSsp( &wk->ssp_shak, wk->dx, wk->dy, wk->ssp );
		WazaTool_CalcAndReflectScaleRateExSsp( &wk->ssp_scale, wk->ssp );
		WazaTool_PokeOffsetSet(
				wk->ssp,
				wk->dy, wk->poke_h,
				wk->ssp_scale.work[4], WAZAEFF_OFS_MODE_BOTTOM);//*/
		wk->seq++;
		break;
		
	case WE252_POKE_SSP_SCALEDOWN:
		WazaTool_CalcAndReflectShakeSsp( &wk->ssp_shak, wk->dx, wk->dy, wk->ssp );
		check = WazaTool_CalcAndReflectScaleRateExSsp( &wk->ssp_scale, wk->ssp );
		WazaTool_PokeOffsetSet(
				wk->ssp,
				wk->dy, wk->poke_h,
				wk->ssp_scale.work[4], WAZAEFF_OFS_MODE_BOTTOM);//*/
		// 拡縮値を設定
		if( check == FALSE ){
			wk->scale_num --;
			if( wk->scale_num <= 0 ){
				// 終了
				wk->seq++;
			}else{
				wk->seq = WE252_POKE_SSP_SCALEUP_INIT;
			}
		}
		break;
		
	case WE252_POKE_SSP_SCALEEND:
		SoftSpriteParaSet( wk->ssp, SS_PARA_POS_X, wk->dx );
		SoftSpriteParaSet( wk->ssp, SS_PARA_POS_Y, wk->dy );

		SoftSpriteParaSet( wk->ssp, SS_PARA_AFF_X, 0x100 );
		SoftSpriteParaSet( wk->ssp, SS_PARA_AFF_Y, 0x100 );
		
		sys_FreeMemoryEz(wk);
		WEEffect_TCB_Delete(wk->we_sys, tcb);
		return;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	POKE_SSP を伸び縮みさせる	
 *
 *	@param	we_sys		技エフェクトシステム
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void WestSp_WE_252SSPPoke(WE_SYS_PTR we_sys)
{
	TWE252_POKE_SSP_SCALE_UPDOWN* wk;

	wk = WET_ALLOC_MEMORY(we_sys, TWE252_POKE_SSP_SCALE_UPDOWN);
	wk->we_sys	= we_sys;

	wk->poke_h	= WeSysPokeOfsGet(wk->we_sys, WeSysDFNoGet(wk->we_sys));

	// ポケモン取得
	wk->ssp = WeSysSoftSpritePointerGet(wk->we_sys, WeSysDFNoGet(wk->we_sys));
	wk->dy = SoftSpriteParaGet( wk->ssp, SS_PARA_POS_Y );
	wk->dx = SoftSpriteParaGet( wk->ssp, SS_PARA_POS_X );
	
	wk->scale_sx	= NEKODAMASI_SC_SX;
	wk->scale_ex	= NEKODAMASI_SC_EX;
	wk->scale_sy	= NEKODAMASI_SC_SY;
	wk->scale_ey	= NEKODAMASI_SC_EY;
	wk->scale_d		= NEKODAMASI_SC_D;
	wk->scale_num	= NEKODAMASI_SC_NUM;
	wk->scale_sync	= NEKODAMASI_SC_SYNC;


	WazaTool_InitShake(
			&wk->ssp_shak,
			WE252_SHAKE_WIDTH, 0,
			WE252_SHAKE_SYNC,
			WE252_SHAKE_NUM
			);


	WEEffect_TCB_AddPriSet(wk->we_sys, We252SSPPokeScaleUpDownTCB, wk);
}



//-------------------------------------
//	
//	メガホーン
//	
//=====================================

#define MEGAHOON_POS_X_OFS	( 64 )
#define MEGAHOON_POS_Y_OFS	( -16 )
#define MEGAHOON_MOVE_X		( 48 )
#define MEGAHOON_MOVE_Y		( -16 )
#define MEGAHOON_MOVE_SYNC	( 6 )

typedef struct {
	WE_SYS_PTR we_sys;
	CATS_RES_PTR crp;

	WAZATOOL_CALCMOVE	cap_move;
	CATS_ACT_PTR cap;
} TWE224_SYS;

static void We_224TCB( TCB_PTR tcb, void* work )
{
	TWE224_SYS* wk = work;
	
	if( WazaTool_CalcAndReflectStraightFxCap( &wk->cap_move, wk->cap ) == FALSE ){
		CATS_ActorPointerDelete_S(wk->cap);
		sys_FreeMemoryEz(wk);
		WEEffect_TCB_Delete(wk->we_sys, tcb);
		return ;
	}
	CATS_Draw(wk->crp);
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	メガホーン動作タスク登録
 *
 *	@param	we_sys		技エフェクトシステム
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void WestSp_WE_224(WE_SYS_PTR we_sys)
{
	TWE224_SYS* wk;
	int at_client;
	int vec_x, vec_y;
	int cap_x, cap_y;

	wk = WET_ALLOC_MEMORY(we_sys, TWE224_SYS);
	wk->we_sys	= we_sys;
	wk->crp		= WeSysCrpGet( we_sys );

	// cap取得
	at_client = WeSysATNoGet( we_sys );
	if( WET_SideCheck( we_sys, at_client ) == SIDE_MINE ){
		wk->cap = WeSysOamCapGet( we_sys, 0 );

		CATS_ActorPointerDelete_S( WeSysOamCapGet( we_sys, 1 ) );
	}else{
		wk->cap = WeSysOamCapGet( we_sys, 1 );

		CATS_ActorPointerDelete_S( WeSysOamCapGet( we_sys, 0 ) );
	}

	// 方向ベクトル取得
	vec_x = WazaTool_VecChangeX( we_sys, at_client );
	vec_y = WazaTool_VecChangeY( we_sys, at_client );

	// メガホーン座標設定
	cap_x = GetWazaEffPos( we_sys, at_client, PM_X );
	cap_y = GetWazaEffPos( we_sys, at_client, PM_Y );
	cap_x += MEGAHOON_POS_X_OFS * vec_x;
	cap_y += MEGAHOON_POS_Y_OFS * vec_y;
	CATS_ObjectPosSetCap( wk->cap, cap_x, cap_y );

	// メガホーン動作設定
	WazaTool_InitStraightSyncFx(
			&wk->cap_move,
			cap_x, cap_x + (MEGAHOON_MOVE_X * vec_x),
			cap_y, cap_y + (MEGAHOON_MOVE_Y * vec_y),
			MEGAHOON_MOVE_SYNC
			);
	

	WEEffect_TCB_AddPriSet(wk->we_sys, We_224TCB, wk);
}


// 攻撃側動作
enum{
	WE224AT_SHAKE_INIT,
	WE224AT_SHAKE,
	WE224AT_MOVE1,		// 敵のほうに移動
	WE224AT_WAIT,		// 待機
	WE224AT_MOVE2,		// 戻る
	WE224AT_END,		// 終了
};
#define WE224AT_SHAKE_X		( 4 )
#define WE224AT_SHAKE_NUM	( 4 )
#define WE224AT_SHAKE_SYNC	( 1 )

#define WE224AT_MOVE_X		( 40 )
#define WE224AT_MOVE_Y		( -7 )
#define WE224AT_SYNC		( 4 )

#define WE224AT_WAIT_NUM		( 8 )

typedef struct{
	WE_SYS_PTR we_sys;
	int seq;
	int wait;
	int vec_x;
	int vec_y;

	// ポケモン
	SOFT_SPRITE*	ssp;
	s16				ssp_x;
	s16				ssp_y;
	WAZATOOL_CALCMOVE	ssp_move;
	WAZATOOL_CALCMOVE	ssp_shake;
}TWE224AT_SYS;


//----------------------------------------------------------------------------
/**
 *
 *	@brief	攻撃側動作
 *
 *	@param	tcb		
 *	@param	work 
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void We_224ATTCB( TCB_PTR tcb, void* work )
{
	TWE224AT_SYS* wk = work;

	switch( wk->seq ){
	case WE224AT_SHAKE_INIT:
		WazaTool_InitShake(
				&wk->ssp_shake,
				WE224AT_SHAKE_X,
				0,
				WE224AT_SHAKE_SYNC,
				WE224AT_SHAKE_NUM
				);
		wk->seq++;
		break;
		
	case WE224AT_SHAKE:
		if( WazaTool_CalcAndReflectShakeSsp( &wk->ssp_shake, wk->ssp_x, wk->ssp_y, wk->ssp ) == FALSE ){
			wk->seq++;

			// 直線移動設定
			WazaTool_InitStraightSyncFx(
					&wk->ssp_move,
					wk->ssp_x, wk->ssp_x + (WE224AT_MOVE_X * wk->vec_x),
					wk->ssp_y, wk->ssp_y + (WE224AT_MOVE_Y * wk->vec_y),
					WE224AT_SYNC
					);
		}
		break;
		
	case WE224AT_MOVE1:		// 敵のほうに移動
		if( WazaTool_CalcAndReflectStraightFxSsp( &wk->ssp_move, wk->ssp ) == FALSE ){
			wk->seq++;
			wk->wait = WE224AT_WAIT_NUM;
		}
		break;
		
	case WE224AT_WAIT:		// 待機
		wk->wait --;
		if( wk->wait < 0 ){
			wk->seq++;

			// 直線移動設定
			WazaTool_InitStraightSyncFx(
					&wk->ssp_move,
					wk->ssp_x + (WE224AT_MOVE_X * wk->vec_x), wk->ssp_x, 
					wk->ssp_y + (WE224AT_MOVE_Y * wk->vec_y), wk->ssp_y, 
					WE224AT_SYNC
					);
		}
		break;
		
	case WE224AT_MOVE2:		// 戻る
		if( WazaTool_CalcAndReflectStraightFxSsp( &wk->ssp_move, wk->ssp ) == FALSE ){
			wk->seq++;
		}
		break;
		
	case WE224AT_END:		// 終了
		SoftSpriteParaSet( wk->ssp, SS_PARA_POS_X, wk->ssp_x );
		SoftSpriteParaSet( wk->ssp, SS_PARA_POS_Y, wk->ssp_y );
		
		sys_FreeMemoryEz(wk);
		WEEffect_TCB_Delete(wk->we_sys, tcb);
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	メガホーン攻撃側動作タスク登録
 *
 *	@param	we_sys		技エフェクトシステム
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void WestSp_WE_224AT(WE_SYS_PTR we_sys)
{
	TWE224AT_SYS* wk;
	int at_client;

	wk = WET_ALLOC_MEMORY(we_sys, TWE224AT_SYS);
	wk->we_sys	= we_sys;

	// ポケモンデータ作成
	at_client = WeSysATNoGet( we_sys );
	wk->ssp = WeSysSoftSpritePointerGet( we_sys, at_client );
	wk->ssp_x = SoftSpriteParaGet( wk->ssp, SS_PARA_POS_X );
	wk->ssp_y = SoftSpriteParaGet( wk->ssp, SS_PARA_POS_Y );

	// 方向ベクトル取得
	wk->vec_x = WazaTool_VecChangeX( we_sys, at_client );
	wk->vec_y = WazaTool_VecChangeY( we_sys, at_client );


	WEEffect_TCB_AddPriSet(wk->we_sys, We_224ATTCB, wk);
}


// 防御側動作
enum{
	WE224DF_MOVE1_INIT,
	WE224DF_MOVE1,
	WE224DF_SHAKE,
	WE224DF_MOVE2,
	WE224DF_END,
};
#define WE224DF_SHAKE_X		( 4 )
#define WE224DF_SHAKE_NUM	( 4 )
#define WE224DF_SHAKE_SYNC	( 1 )

#define WE224DF_MOVE_X		( -40 )
#define WE224DF_MOVE_Y		( 16 )
#define WE224DF_SYNC		( 4 )

typedef struct{
	WE_SYS_PTR we_sys;
	int seq;
	int vec_x;
	int vec_y;

	// ポケモン
	SOFT_SPRITE*	ssp;
	s16				ssp_x;
	s16				ssp_y;
	WAZATOOL_CALCMOVE	ssp_move;
	WAZATOOL_CALCMOVE	ssp_shake;
}TWE224DF_SYS;


//----------------------------------------------------------------------------
/**
 *
 *	@brief	攻撃側動作
 *
 *	@param	tcb		
 *	@param	work 
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void We_224DFTCB( TCB_PTR tcb, void* work )
{
	TWE224DF_SYS* wk = work;
	s16 x, y;

	switch( wk->seq ){
	case WE224DF_MOVE1_INIT:
		// 直線移動設定
		WazaTool_InitStraightSyncFx(
				&wk->ssp_move,
				wk->ssp_x, wk->ssp_x + (WE224DF_MOVE_X * wk->vec_x),
				wk->ssp_y, wk->ssp_y + (WE224DF_MOVE_Y * wk->vec_y),
				WE224DF_SYNC
				);
		wk->seq++;
		break;
		
		
	case WE224DF_MOVE1:		// 敵のほうに移動
		if( WazaTool_CalcAndReflectStraightFxSsp( &wk->ssp_move, wk->ssp ) == FALSE ){
			wk->seq++;
			WazaTool_InitShake(
					&wk->ssp_shake,
					WE224DF_SHAKE_X,
					0,
					WE224DF_SHAKE_SYNC,
					WE224DF_SHAKE_NUM
					);
		}
		break;
		
	case WE224DF_SHAKE:
		x = SoftSpriteParaGet( wk->ssp, SS_PARA_POS_X );
		y = SoftSpriteParaGet( wk->ssp, SS_PARA_POS_Y );
		if( WazaTool_CalcAndReflectShakeSsp( &wk->ssp_shake, x, y, wk->ssp ) == FALSE ){
			wk->seq++;

			// 直線移動設定
			WazaTool_InitStraightSyncFx(
					&wk->ssp_move,
					wk->ssp_x + (WE224DF_MOVE_X * wk->vec_x), wk->ssp_x, 
					wk->ssp_y + (WE224DF_MOVE_Y * wk->vec_y), wk->ssp_y, 
					WE224DF_SYNC
					);

		}
		break;
		
	case WE224DF_MOVE2:		// 戻る
		if( WazaTool_CalcAndReflectStraightFxSsp( &wk->ssp_move, wk->ssp ) == FALSE ){
			wk->seq++;
		}
		break;
		
	case WE224DF_END:		// 終了
		SoftSpriteParaSet( wk->ssp, SS_PARA_POS_X, wk->ssp_x );
		SoftSpriteParaSet( wk->ssp, SS_PARA_POS_Y, wk->ssp_y );
		
		sys_FreeMemoryEz(wk);
		WEEffect_TCB_Delete(wk->we_sys, tcb);
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	メガホーン攻撃側動作タスク登録
 *
 *	@param	we_sys		技エフェクトシステム
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void WestSp_WE_224DF(WE_SYS_PTR we_sys)
{
	TWE224DF_SYS* wk;
	int at_client;

	wk = WET_ALLOC_MEMORY(we_sys, TWE224DF_SYS);
	wk->we_sys	= we_sys;

	// ポケモンデータ作成
	at_client = WeSysDFNoGet( we_sys );
	wk->ssp = WeSysSoftSpritePointerGet( we_sys, at_client );
	wk->ssp_x = SoftSpriteParaGet( wk->ssp, SS_PARA_POS_X );
	wk->ssp_y = SoftSpriteParaGet( wk->ssp, SS_PARA_POS_Y );

	// 方向ベクトル取得
	wk->vec_x = WazaTool_VecChangeX( we_sys, at_client );
	wk->vec_y = WazaTool_VecChangeY( we_sys, at_client );


	WEEffect_TCB_AddPriSet(wk->we_sys, We_224DFTCB, wk);
}
