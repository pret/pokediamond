//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		wsp_status.c
 *	@brief		ステータス異常のエフェクト
 *	@author		tomoya takahashi
 *	@data		2005.12.19
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
#include "wsp.h"			///< xxx.cに対するxxx.hは必須

#include "wazatool.h"			///< 技エフェクト支援関数郡
#include "we_tool.h"			///< 

#include "system/arc_tool.h"				///< アーカイブ用
#include "system/arc_util.h"				///< アーカイブ用

#define __WSP_STATUS_H_GLOBAL

//-----------------------------------------------------------------------------
/**
 *					定数宣言
*/
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
// 眠り
static void SMPTM_NemuriTcb( TCB_PTR tcb, void* work );
static void NemuriObjStart( CATS_ACT_PTR cap, WAZATOOL_CALCMOVE* p_move, WAZATOOL_CALCMOVE* p_scale, int vec_x );
static BOOL NemuriObjMove( CATS_ACT_PTR cap, WAZATOOL_CALCMOVE* p_move, WAZATOOL_CALCMOVE* p_scale );


// 氷
static void SMPTM_KooriTcb( TCB_PTR tcb, void* work );

// やでど
static void SMPTM_YakedoTcb( TCB_PTR tcb, void* work );
static BOOL SMPTM_MoveYakedoObj( CATS_ACT_PTR cap, int* count, int* wait );
static void SMPTM_InitYakedoObj( CATS_ACT_PTR cap, int* count, int* wait, int num, int vec_x);

// こんらん
static void Konran_TCB( TCB_PTR tcb, void* work );

//-----------------------------------------------------------------------------
/**
 *
 *			眠りエフェクト
 * 
 */
//-----------------------------------------------------------------------------

#define NEMURI_SET_NUM	(2)
#define NEMURI_CHAR_NUM	(1)
#define NEMURI_PLTT_NUM	(1)
#define NEMURI_CELL_NUM	(1)
#define NEMURI_CELLANM_NUM	(1)
#define NEMURI_LOAD_PLTT	(1)
#define NEMURI_RES_ID		(0)

#define NEMURI_EFF_SYNC	( 32 )
#define NEMURI_MOVE_H	( -32 )
#define NEMURI_MOVE_W	( 16 )

#define NEMURI_SCALE_S	( 2 )
#define NEMURI_SCALE_D	( 10 )
#define NEMURI_SCALE_E	( 10 )

#define NEMURI_1_WAIT	( 8 )


enum{
	NEMURI_SEQ_0_START,
	NEMURI_SEQ_1_WAIT,
	NEMURI_SEQ_1_START,
	NEMURI_SEQ_END_WAIT,
	NEMURI_SEQ_END,
};

typedef struct{
	WE_SYS_PTR	we_sys;
	int seq;
	int wait;
	CATS_RES_PTR crp;
	int vec_x;

	// 動作データ
	CATS_ACT_PTR		cap[ NEMURI_SET_NUM ];
	WAZATOOL_CALCMOVE	cap_move[ NEMURI_SET_NUM ];
	WAZATOOL_CALCMOVE	cap_scale[ NEMURI_SET_NUM ];
} TWE_ST001_SYS;

//----------------------------------------------------------------------------
/**
 *
 *	@brief	めむりエフェクト
 *
 *	@param	we_sys	技エフェクトシステムワーク
 *	@param	csp		セルアクターツールシステム
 *	@param	crp		セルアクターリソースシステム
 *	@param	cap		セルアクターツールオブジェ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void WestSp_CAT_ST_001(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CATS_ACT_PTR cap)
{
	TCATS_OBJECT_ADD_PARAM_S coap;
	TWE_ST001_SYS* wk;
	int i;
	int client_no;

	
	wk = WET_ALLOC_MEMORY(we_sys, TWE_ST001_SYS);
	wk->we_sys	= we_sys;
	wk->crp		= crp;

	client_no = WeSysATNoGet(we_sys);
	wk->vec_x = WazaTool_VecChangeX( we_sys, client_no );

	// 眠りセルアクターの登録を行う
	coap   = WeSysCoapGet(wk->we_sys);
	coap.x = GetWazaEffPos(we_sys, client_no, PM_X);
	coap.y = GetWazaEffPos(we_sys, client_no, PM_Y);

	for( i=0; i<NEMURI_SET_NUM; i++ ){
		if( i==0 ){
			wk->cap[i] = cap;
			CATS_ObjectPosSetCap( wk->cap[i], coap.x, coap.y );
		}else{
			wk->cap[i] = CATS_ObjectAdd_S( csp, crp, &coap );
		}
		CATS_ObjectEnableCap( wk->cap[i], FALSE );
		CATS_ObjectPriSetCap( wk->cap[i], WAZAEFF_ACT_SOFTPRI );
		CATS_ObjectBGPriSetCap( wk->cap[i], WAZAEFF_ACT_BGPRI );
	}

	// タスク登録
	WEEffect_TCB_AddPriSet( wk->we_sys, SMPTM_NemuriTcb, wk );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	眠りTCB
 *
 *	@param	tcb		タスクワーク
 *	@param	work	ワーク
 *	
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void SMPTM_NemuriTcb( TCB_PTR tcb, void* work )
{
	TWE_ST001_SYS* wk = work;
	int i;

	switch( wk->seq ){
	case NEMURI_SEQ_0_START:
		NemuriObjStart( wk->cap[0], &wk->cap_move[0], &wk->cap_scale[0], wk->vec_x );
		NemuriObjMove( wk->cap[0], &wk->cap_move[0], &wk->cap_scale[0] );
		wk->seq++;
		wk->wait = NEMURI_1_WAIT;
		break;
		
	case NEMURI_SEQ_1_WAIT:
		wk->wait --;
		NemuriObjMove( wk->cap[0], &wk->cap_move[0], &wk->cap_scale[0] );
		if( wk->wait < 0 ){
			wk->seq++;
		}
		break;
		
	case NEMURI_SEQ_1_START:
		NemuriObjStart( wk->cap[1], &wk->cap_move[1], &wk->cap_scale[1], wk->vec_x );
		NemuriObjMove( wk->cap[1], &wk->cap_move[1], &wk->cap_scale[1] );
		NemuriObjMove( wk->cap[0], &wk->cap_move[0], &wk->cap_scale[0] );
		

		wk->seq++;
		break;
		
	case NEMURI_SEQ_END_WAIT:
		NemuriObjMove( wk->cap[0], &wk->cap_move[0], &wk->cap_scale[0] );
		if( NemuriObjMove( wk->cap[1], &wk->cap_move[1], &wk->cap_scale[1] ) ){
			wk->seq++;
		}
		break;
		
	case NEMURI_SEQ_END:
		for( i=0; i<NEMURI_SET_NUM; i++ ){
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
 *
 *	@brief	眠りエフェクト開始
 *
 *	@param	cap			アクター
 *	@param	p_move		移動データ格納先
 *	@param	p_scale		拡縮データ格納先
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void NemuriObjStart( CATS_ACT_PTR cap, WAZATOOL_CALCMOVE* p_move, WAZATOOL_CALCMOVE* p_scale, int vec_x )
{
	s16 cap_x, cap_y;
	
	// 表示＆倍角アフィン
	CATS_ObjectAffineSetCap( cap, CLACT_AFFINE_DOUBLE );
	CATS_ObjectEnableCap( cap, TRUE );

	CATS_ObjectPosGetCap( cap, &cap_x, &cap_y );

	// 直線移動設定
	WazaTool_InitStraightSyncFx( 
			p_move,
			cap_x, cap_x + (NEMURI_MOVE_W * vec_x),
			cap_y, cap_y + (NEMURI_MOVE_H),
			NEMURI_EFF_SYNC
			);

	// 拡縮
	WazaTool_InitScaleRate(
			p_scale,
			NEMURI_SCALE_S,
			NEMURI_SCALE_D,
			NEMURI_SCALE_E,
			NEMURI_EFF_SYNC
			);
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	眠りオブジェクト動作
 *
 *	@param	cap			アクター
 *	@param	p_move		移動動作
 *	@param	p_scale		拡縮
 *
 *	@retval	TRUE	
 *
 *
 */
//-----------------------------------------------------------------------------
static BOOL NemuriObjMove( CATS_ACT_PTR cap, WAZATOOL_CALCMOVE* p_move, WAZATOOL_CALCMOVE* p_scale )
{
	BOOL check;

	// 動作反映部
	WazaTool_CalcAndReflectStraightFxCap( p_move, cap );
	check = WazaTool_CalcAndReflectScaleRateCap( p_scale, cap );

	if( check ){
		return FALSE;
	}

	// 表示OFF
	CATS_ObjectEnableCap( cap, FALSE );
	return TRUE;
}


//-----------------------------------------------------------------------------
/**
 *
 *				こおり
 * 
 */
//-----------------------------------------------------------------------------

#define KOORI_SET_NUM	(1)
#define KOORI_CHAR_NUM	(1)
#define KOORI_PLTT_NUM	(1)
#define KOORI_CELL_NUM	(1)
#define KOORI_CELLANM_NUM	(1)
#define KOORI_LOAD_PLTT		(3)
#define KOORI_RES_ID		(0)

#define KOORI_ALPHA_S	( 0 )
#define KOORI_ALPHA_E	( 16 )
#define KOORI_ALPHA_DEF	( 20 )
#define KOORI_ALPHAIN_SYNC	( 10 )
#define KOORI_ALPHAOUT_SYNC	( 8 )


enum{
	KOORI_SEQ_ALPHAIN_START,
	KOORI_SEQ_ALPHAIN,
	KOORI_SEQ_ANM,
	KOORI_SEQ_ALPHAOUT,
	KOORI_SEQ_END,
};

typedef struct{
	WE_SYS_PTR we_sys;
	int seq;
	int plt_no;
	CATS_RES_PTR crp;

	// 動作データ
	CATS_ACT_PTR		cap;
	WAZATOOL_ALPHA_FADE	cap_alpha;
} TWE_ST004_SYS;

//----------------------------------------------------------------------------
/**
 *
 *	@brief	氷エフェクトタスク登録
 *
 *	@param	we_sys	技エフェクトシステムワーク
 *	@param	csp		セルアクターツールシステム
 *	@param	crp		セルアクターリソースシステム
 *	@param	cap		セルアクターツールオブジェ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void WestSp_CAT_ST_004(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CATS_ACT_PTR cap)
{
	TWE_ST004_SYS* wk;
	int client_no;

	
	wk = WET_ALLOC_MEMORY(we_sys, TWE_ST004_SYS);
	wk->we_sys	= we_sys;
	wk->crp		= crp;

	wk->cap = cap;
	CATS_ObjectEnableCap( wk->cap, FALSE );
	CATS_ObjectObjModeSetCap( wk->cap, GX_OAM_MODE_XLU );
	CATS_ObjectPriSetCap( wk->cap, WAZAEFF_ACT_SOFTPRI );
	CATS_ObjectBGPriSetCap( wk->cap, WAZAEFF_ACT_BGPRI );

	wk->plt_no = CATS_ObjectPaletteOffsetGetCap( wk->cap );

	// タスク登録
	WEEffect_TCB_AddPriSet( wk->we_sys,SMPTM_KooriTcb, wk );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	氷動作タスク
 *
 *	@param	tcb
 *	@param	work 
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void SMPTM_KooriTcb( TCB_PTR tcb, void* work )
{
	TWE_ST004_SYS* wk = work;
	int frame;

	switch( wk->seq ){
	case KOORI_SEQ_ALPHAIN_START:
		WazaTool_StartAlphaFade(
				&wk->cap_alpha,
				KOORI_ALPHA_S, KOORI_ALPHA_E,
				KOORI_ALPHA_DEF - KOORI_ALPHA_S, KOORI_ALPHA_DEF - KOORI_ALPHA_E,
				KOORI_ALPHAIN_SYNC
				);
		CATS_ObjectEnableCap( wk->cap, TRUE );

		WET_DefaultBlendSet(wk->we_sys,
				KOORI_ALPHA_S, KOORI_ALPHA_DEF - KOORI_ALPHA_S);	

		wk->seq++;
		break;
		
	case KOORI_SEQ_ALPHAIN:
		if( WazaTool_EndCheckAlphaFade( &wk->cap_alpha ) ){
			wk->seq++;

			CATS_ObjectAutoAnimeSetCap( wk->cap, CATS_ANM_AUTO_ON );
			CATS_ObjectAutoAnimeSpeedSetCap( wk->cap, FX32_ONE );
		}
		break;
		
	case KOORI_SEQ_ANM:
		// 自分でパレットナンバーを設定する
		frame = CATS_ObjectAnimeFrameGetCap( wk->cap );
		frame %= 3;
		CATS_ObjectPaletteOffsetSetCap( wk->cap, wk->plt_no + frame );
		
		
		if( CATS_ObjectAnimeActiveCheckCap( wk->cap ) == FALSE ){
			wk->seq++;

			WazaTool_StartAlphaFade(
					&wk->cap_alpha,
					KOORI_ALPHA_E, KOORI_ALPHA_S,
					KOORI_ALPHA_DEF - KOORI_ALPHA_E, KOORI_ALPHA_DEF - KOORI_ALPHA_S,
					KOORI_ALPHAOUT_SYNC
					);
		}
		break;
		
	case KOORI_SEQ_ALPHAOUT:
		if( WazaTool_EndCheckAlphaFade( &wk->cap_alpha ) ){
			wk->seq++;

			CATS_ObjectEnableCap( wk->cap, FALSE );
		}
		break;
		
	case KOORI_SEQ_END:
		CATS_ActorPointerDelete_S(wk->cap);
		// 終了
		WEEffect_TCB_Delete(wk->we_sys, tcb);
		sys_FreeMemoryEz(wk);
		return;
	}

	// OAM描画
	CATS_Draw(wk->crp);	
}

//-----------------------------------------------------------------------------
/**
 *
 *			やけど
 * 
 */
//-----------------------------------------------------------------------------
#define YAKEDO_OBJ_NUM			( 6 )		// やどののオブジェクト数
#define YAKEDO_OBJ_ONEGRA_NUM	( 2 )		// 同じ絵のオブジェ数
#define YAKEDO_OBJ_ADD_WAIT		( 2 )		// オブジェ登録待ち
#define YAKEDO_OBJ_DRAW_SYNC	( 16 )		// 表示シンク

#define YAKEDO_OBJ_MAT_OFS_X	( 40 )
#define YAKEDO_OBJ_MAT_DIS_X	( -12 )
#define YAKEDO_OBJ_MAT_OFS_Y	( 40 )

typedef struct{
	WE_SYS_PTR we_sys;
	int seq;
	CATS_RES_PTR crp;

	// 動作データ
	CATS_ACT_PTR		cap[YAKEDO_OBJ_NUM];
	int					cap_count[YAKEDO_OBJ_NUM];
	int					cap_wait[YAKEDO_OBJ_NUM];
} TWE_ST003_SYS;

//----------------------------------------------------------------------------
/**
 *
 *	@brief	やけどエフェクトタスク登録
 *
 *	@param	we_sys	技エフェクトシステムワーク
 *	@param	csp		セルアクターツールシステム
 *	@param	crp		セルアクターリソースシステム
 *	@param	cap		セルアクターツールオブジェ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void WestSp_CAT_ST_003(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CATS_ACT_PTR cap)
{
	TCATS_OBJECT_ADD_PARAM_S coap;
	TWE_ST003_SYS* wk;
	int client_no;
	int i;
	int vec_x;

	
	wk = WET_ALLOC_MEMORY(we_sys, TWE_ST003_SYS);
	wk->we_sys	= we_sys;
	wk->crp		= crp;


	client_no = WeSysATNoGet(wk->we_sys);
	vec_x = WazaTool_VecChangeX( we_sys, client_no );
	coap   = WeSysCoapGet(wk->we_sys);
	coap.x = GetWazaEffPos(we_sys, client_no, PM_X);
	coap.y = GetWazaEffPos(we_sys, client_no, PM_Y);

	// アクターの表示優先順位制御のためカウンタを最終から行う
	for( i=YAKEDO_OBJ_NUM - 1; i>=0; i-- ){
		if( i==YAKEDO_OBJ_NUM - 1 ){
			wk->cap[i] = cap;
			CATS_ObjectPosSetCap( cap, coap.x, coap.y );
		}else{
			wk->cap[i] = CATS_ObjectAdd_S( csp, crp, &coap );
		}
		CATS_ObjectPriSetCap( wk->cap[i], WAZAEFF_ACT_SOFTPRI );
		CATS_ObjectBGPriSetCap( wk->cap[i], WAZAEFF_ACT_BGPRI );
		CATS_ObjectEnableCap( wk->cap[i], FALSE );

		// アニメデータ初期化
		SMPTM_InitYakedoObj( wk->cap[i], &wk->cap_count[i], &wk->cap_wait[i], i, vec_x );
	}

	// タスク登録
	WEEffect_TCB_AddPriSet( wk->we_sys,SMPTM_YakedoTcb, wk );
}

static void SMPTM_InitYakedoObj( CATS_ACT_PTR cap, int* count, int* wait, int num, int vec_x )
{
	s16 x, y;
	
	// 絵を設定
	CATS_ObjectAnimeSeqSetCap( cap, num / YAKEDO_OBJ_ONEGRA_NUM );

	// wait
	*wait = num * YAKEDO_OBJ_ADD_WAIT;

	// count
	*count = YAKEDO_OBJ_DRAW_SYNC;

	// 座標
	CATS_ObjectPosGetCap( cap, &x, &y );
	x += (YAKEDO_OBJ_MAT_OFS_X + (YAKEDO_OBJ_MAT_DIS_X * num)) * vec_x;
	y += YAKEDO_OBJ_MAT_OFS_Y;
	CATS_ObjectPosSetCap( cap, x, y );
}

static BOOL SMPTM_MoveYakedoObj( CATS_ACT_PTR cap, int* count, int* wait )
{
	if( *wait > 0 ){
		(*wait) --;

		if( *wait == 0 ){
			CATS_ObjectEnableCap( cap, TRUE );
		}
		
	}else{

		if( *count > 0 ){
			(*count) --;
		}else{
			CATS_ObjectEnableCap( cap, FALSE );
			return TRUE;
		}
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	やけど動作タスク
 *
 *	@param	tcb
 *	@param	work 
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void SMPTM_YakedoTcb( TCB_PTR tcb, void* work )
{
	TWE_ST003_SYS* wk = work;
	int i;
	BOOL check;

	switch( wk->seq ){
	case 0:
		for( i=0; i<YAKEDO_OBJ_NUM; i++ ){
			check = SMPTM_MoveYakedoObj( wk->cap[i], &wk->cap_count[i], &wk->cap_wait[i] );
		}
		if( check ){
			wk->seq++;
		}
		break;
		
	case 1:
		for( i=0; i<YAKEDO_OBJ_NUM; i++ ){
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


//-----------------------------------------------------------------------------
/**
 *
 *		こんらん
 *
 */
//-----------------------------------------------------------------------------
enum{
	KONRAN_MOVE_START,
	KONRAN_FADE_IN,
	KONRAN_FADE_OUT_WAIT,
	KONRAN_FADE_OUT,
	KONRAN_END,
};


#define KONRAN_CAP_NUM			( 6 )	// ここかえたら288.sもかえる
#define KONRAN_CAP_ROTA_S		( FX_GET_ROTA_NUM( 0 ) )
#define KONRAN_CAP_ROTA_E		( FX_GET_ROTA_NUM( 180 ) )
#define KONRAN_CAP_ROTA_SYNC		( 48 )
#define KONRAN_CAP_ROTA_WIDTH	( FX32_ONE*50 )
#define KONRAN_CAP_ALPHA_S		( 1 )
#define KONRAN_CAP_ALPHA_E		( 16 )
#define KONRAN_CAP_ALPHA_SYNC	( 10 )

#define KONRAN_CAP_ALPHAOUT_WAIT	( KONRAN_CAP_ROTA_SYNC - (KONRAN_CAP_ALPHA_SYNC*2) )
 
typedef struct {
	WE_SYS_PTR	we_sys;
	CATS_SYS_PTR csp;
	CATS_RES_PTR crp;
	int seq;
	int wait;

	int vec_x;

	//こんらん
	CATS_ACT_PTR cap[ KONRAN_CAP_NUM ];
	WAZATOOL_CALCMOVE cap_move[ KONRAN_CAP_NUM ];	// 横移動
	WAZATOOL_ALPHA_FADE cap_alpha;	// アルファ変換
	s16 cap_cx;
	s16 cap_cy;
} TKONRAN_SYS;

static void Konran_CapInit( TKONRAN_SYS* wk, int vec_x )
{
	int i;
	int rota_offs_one;

	rota_offs_one = FX_GET_ROTA_NUM( 360 ) / KONRAN_CAP_NUM;
	
	// 計算データ作成
	for( i=0; i<KONRAN_CAP_NUM; i++ ){
		WazaTool_InitRotaFx(
				&wk->cap_move[ i ],
				KONRAN_CAP_ROTA_S,
				KONRAN_CAP_ROTA_E,
				0,0,
				KONRAN_CAP_ROTA_WIDTH, 0,
				KONRAN_CAP_ROTA_SYNC
				);
		wk->cap_move[i].work[1] += (rota_offs_one*i);
		wk->cap_move[i].work[5] *= vec_x;
	}

}

static void Konran_CapMove( TKONRAN_SYS* wk )
{
	int i;
	u16 rota;

	for( i=0; i<KONRAN_CAP_NUM; i++ ){
		
		// 計算
		WazaTool_CalcRotaFx( &wk->cap_move[ i ] );
		
		// 反映
		CATS_ObjectPosSetCap( wk->cap[ i ],
				wk->cap_cx + wk->cap_move[ i ].x,
				wk->cap_cy );

		// 角度でBG優先順位を変える
		if( (wk->cap_move[ i ].work[ 1 ] >= FX_GET_ROTA_NUM(90)) &&
			(wk->cap_move[ i ].work[ 1 ] <= FX_GET_ROTA_NUM(269)) ){
			
			CATS_ObjectBGPriSetCap( wk->cap[ i ], WAZAEFF_ACT_BGPRI );
		}else{

			CATS_ObjectBGPriSetCap( wk->cap[ i ], BT_3DPriorityGet(wk->we_sys)+1 );
		}//*/
	}
}

static void Konran_TCB( TCB_PTR tcb, void* work )
{
	TKONRAN_SYS* wk = work;
	int i;

	switch( wk->seq ){
	case KONRAN_MOVE_START:
		// アルファ設定
		WET_DefaultBlendSet( wk->we_sys,
				KONRAN_CAP_ALPHA_S, 16 - KONRAN_CAP_ALPHA_S );
		WazaTool_StartAlphaFade(
				&wk->cap_alpha,
				KONRAN_CAP_ALPHA_S, KONRAN_CAP_ALPHA_E,
				16 - KONRAN_CAP_ALPHA_S, 16 - KONRAN_CAP_ALPHA_E,
				KONRAN_CAP_ALPHA_SYNC
				);
		// オブジェ
		Konran_CapInit( wk, wk->vec_x );
		Konran_CapMove( wk );
		wk->seq++;
		break;
		
	case KONRAN_FADE_IN:
		Konran_CapMove( wk );
		if( WazaTool_EndCheckAlphaFade( &wk->cap_alpha ) ){
			wk->seq++;
			wk->wait = KONRAN_CAP_ALPHAOUT_WAIT;
		}
		break;
		
	case KONRAN_FADE_OUT_WAIT:
		Konran_CapMove( wk );
		wk->wait --;
		if( wk->wait < 0 ){
			wk->seq++;
			WazaTool_StartAlphaFade(
					&wk->cap_alpha,
					KONRAN_CAP_ALPHA_E, KONRAN_CAP_ALPHA_S, 
					16 - KONRAN_CAP_ALPHA_E, 16 - KONRAN_CAP_ALPHA_S, 
					KONRAN_CAP_ALPHA_SYNC
					);
		}
		break;
		
	case KONRAN_FADE_OUT:
		Konran_CapMove( wk );
		if( WazaTool_EndCheckAlphaFade( &wk->cap_alpha ) ){
			wk->seq++;
		}
		break;

	case KONRAN_END:
		for( i=0; i<KONRAN_CAP_NUM; i++ ){
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
 * @brief	こんらん用タスク登録
 *
 *	@param	we_sys	技エフェクトシステムワーク
 *	@param	csp		セルアクターツールシステム
 *	@param	crp		セルアクターリソースシステム
 *	@param	cap		セルアクターツールオブジェ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void WestSp_CAT_ST_006(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CATS_ACT_PTR cap)
{
	TKONRAN_SYS* wk;
	int i;
	SOFT_SPRITE* at_ssp;
	TCATS_OBJECT_ADD_PARAM_S coap;

	wk = WET_ALLOC_MEMORY(we_sys, TKONRAN_SYS);
	wk->we_sys	= we_sys;
	wk->csp		= csp;
	wk->crp		= crp;

	// 攻撃側
	at_ssp = WeSysSoftSpritePointerGet( wk->we_sys, WeSysATNoGet(we_sys) );
	wk->cap_cx = SoftSpriteParaGet( at_ssp, SS_PARA_POS_X );
	wk->cap_cy = SoftSpriteParaGet( at_ssp, SS_PARA_POS_Y );
	
	// こんらん
	coap   = WeSysCoapGet(we_sys);
	for( i=0; i<KONRAN_CAP_NUM ; i++ ){
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

	WEEffect_TCB_AddPriSet(wk->we_sys, Konran_TCB, wk);
}
