//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		nmix_game_demo.c
 *	@brief		木の実ミキサー　小さいエフェクト動さなどの処理
 *	@author		tomoya takahashi
 *	@data		2006.05.24
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "common.h"

#include "system/procsys.h"
#include "nutmixer_def.h"
#include "src/application/nuts_tag/ntag_gra.naix"
#include "itemtool/nuts.h"
#include "system/window.h"
#include "system/fontproc.h"
#include "nutmixer.naix"
#include "nmix_game_snd_def.h"

#define __NMIX_GAME_DEMO_H_GLOBAL
#include "nmix_game_demo.h"

//-----------------------------------------------------------------------------
/**
 *					コーディング規約
 *		●関数名
 *				１文字目は大文字それ以降は小文字にする
 *		●変数名
 *				・変数共通
 *						constには c_ を付ける
 *						staticには s_ を付ける
 *						ポインタには p_ を付ける
 *						全て合わさると csp_ となる
 *				・グローバル変数
 *						１文字目は大文字
 *				・関数内変数
 *						小文字と”＿”と数字を使用する 関数の引数もこれと同じ
*/
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
/**
 *		何か汎用的なものをいかに書く
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *	@brief	中心位置とSTRから左端座標を求める
 *
 *	@param	c_x		中心ｘ
 *	@param	str		文字列
 *	@param	font	フォントタイプ
 *
 *	@return	左端座標
 */
//-----------------------------------------------------------------------------
static int NMixDemo_GetStrLeftX_CenterKey( int c_x, const STRBUF* str, FONT_TYPE font )
{
	u32 str_width;
	str_width = FontProc_GetPrintStrWidth( font, str, 0 );
	str_width /= 2;
	c_x -= str_width;
	return c_x;
}


//----------------------------------------------------------------------------
/**
 *	@brief	SWSP　キャラクタリソース読み込み
 */
//-----------------------------------------------------------------------------
static SWSP_CHAR_PTR NMix_Demo_SwspCharLoad( SWSP_SYS_PTR swsp_sys, u32 data_idx, u32 heapid )
{
	SWSP_CHARDATA char_ent;
	void * buff;
	NNSG2dCharacterData* p_chardata;
	SWSP_CHAR_PTR obj;
	
	
	buff = ArcUtil_CharDataGet( 
			ARC_NUTMIXER_GRA, data_idx, FALSE,
			&p_chardata, heapid );

	// キャラクタデータ転送
	char_ent.s_sys		= swsp_sys;
	char_ent.res_file	= p_chardata;
	obj =SWSP_CharLoad( &char_ent );

	sys_FreeMemoryEz( buff );
	return obj;
}

//----------------------------------------------------------------------------
/**
 *	@brief	SWSP　パレットリソース読み込み
 */
//-----------------------------------------------------------------------------
static SWSP_PLTT_PTR NMix_Demo_SwspPlttLoad( SWSP_SYS_PTR swsp_sys, u32 data_idx, u32 heapid )
{
	SWSP_PLTTDATA pltt_ent;
	void * buff;
	NNSG2dPaletteData* p_plttdata;
	SWSP_PLTT_PTR obj;
	
	
	// パレットデータ読み込み
	buff = ArcUtil_PalDataGet( 
			ARC_NUTMIXER_GRA, data_idx,
			&p_plttdata, heapid );
	// キャラクタデータ転送
	pltt_ent.s_sys		= swsp_sys;
	pltt_ent.res_file	= p_plttdata;
	pltt_ent.load_num	= 1;
	obj =SWSP_PlttLoad( &pltt_ent );

	sys_FreeMemoryEz( buff );
	return obj;
}

//----------------------------------------------------------------------------
/**
 *	@brief	オブジェクト登録
 *
 *	@param	swsp_sys	ソフトウェアスプライト
 *	@param	p_char	キャラクタ
 *	@param	p_pltt	パレット
 *	@param	x		ｘ座標
 *	@param	y		ｙ座標	
 *	@param	pri		優先順位
 *
 *	@return	オブジェクト
 */
//-----------------------------------------------------------------------------
static SWSP_OBJ_PTR NMix_Demo_SwspObjAdd( SWSP_SYS_PTR swsp_sys, SWSP_CHAR_PTR p_char, SWSP_PLTT_PTR p_pltt, int x, int y, int pri )
{
	SWSP_ADDDATA add;
	SWSP_OBJ_PTR obj;

	add.s_sys	= swsp_sys;
	add.p_char	= p_char;
	add.p_pltt	= p_pltt;

	// 登録データ格納
	add.m_x = x;
	add.m_y = y;
	add.rota = 0;
	add.alpha = 31;
	add.pri = pri;
	add.pltt_offs = 0; 

	obj = SWSP_Add( &add );

	// 取り合えず非表示
	SWSP_SetSpriteDraw( obj, FALSE );

	return obj;
}



//----------------------------------------------------------------------------
/**
 *	@brief	セルアクターセットなど作成
 *
 *	@param	p_sys		ワーク
 *	@param	work_num	ワーク数
 *	@param	res_num		リソース数
 *	@param	heapID		ヒープID
 */
//-----------------------------------------------------------------------------
void NMIXGAME_CLACT_Init( NMIXGAME_CLACT_SYS* p_sys, int work_num, int res_num, int heapID )
{
	int i;
	
	// セルアクターセット作成
	p_sys->cas = CLACT_U_SetEasyInit( work_num, &p_sys->renddata, heapID );

	// リソースマネージャ作成
	for( i=0; i<4; i++ ){
		p_sys->resMan[i] = CLACT_U_ResManagerInit( res_num, i, heapID );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	システム情報破棄
 *
 *	@param	p_sys	システムワーク
 */
//-----------------------------------------------------------------------------
void NMIXGAME_CLACT_Delete( NMIXGAME_CLACT_SYS* p_sys )
{
	int i;
	
	CLACT_DestSet( p_sys->cas );
	p_sys->cas = NULL;
	
	for( i=0; i<4; i++ ){
		CLACT_U_ResManagerDelete( p_sys->resMan[i] );
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	単純なリソース読み込み
 *
 *	@param	p_sys		管理システム
 *	@param	p_work		データ格納先
 *	@param	arc_file	アーカイブファイル
 *	@param	pltt_idx	パレット
 *	@param	pltt_num	パレット読み込み数
 *	@param	char_idx	キャラクタ
 *	@param	cel_idx		セル
 *	@param	anm_idx		アニメ
 *	@param	cont_id		管理ID
 *	@param	heap		ヒープ
 */
//-----------------------------------------------------------------------------
void NMIXGAME_CLACT_ResLoadEasy( NMIXGAME_CLACT_SYS* p_sys, NMIXGAME_CLACT_RES_WORK* p_work, u32 arc_file, u32 pltt_idx, u32 pltt_num, u32 char_idx, u32 cel_idx, u32 anm_idx, u32 cont_id, u32 heap )
{
	BOOL result;
	
	// キャラクタ
	p_work->resobj[0] = CLACT_U_ResManagerResAddArcChar_AllocType( p_sys->resMan[0],
			arc_file, char_idx, FALSE, cont_id,
			NNS_G2D_VRAM_TYPE_2DMAIN, heap, ALLOC_BOTTOM );

	// パレット
	p_work->resobj[1] = CLACT_U_ResManagerResAddArcPltt_AllocType( p_sys->resMan[1],
			arc_file, pltt_idx, FALSE, cont_id,
			NNS_G2D_VRAM_TYPE_2DMAIN, pltt_num, heap, ALLOC_BOTTOM );
	p_work->pltt_copy = FALSE;

	// セル
	p_work->resobj[2] = CLACT_U_ResManagerResAddArcKindCell( p_sys->resMan[2],
			arc_file, cel_idx, FALSE, cont_id,
			CLACT_U_CELL_RES, heap );

	// アニメ
	p_work->resobj[3] = CLACT_U_ResManagerResAddArcKindCell( p_sys->resMan[3],
			arc_file, anm_idx, FALSE, cont_id,
			CLACT_U_CELLANM_RES, heap );


	// Vram転送
	result = CLACT_U_CharManagerSetCharModeAdjustAreaCont( p_work->resobj[0] );	
	GF_ASSERT( result );
	CLACT_U_ResManagerResOnlyDelete( p_work->resobj[0] );
	result = CLACT_U_PlttManagerSetCleanArea( p_work->resobj[1] );	
	GF_ASSERT( result );
	CLACT_U_ResManagerResOnlyDelete( p_work->resobj[1] );

	// ヘッダー作成
	CLACT_U_MakeHeader( &p_work->head,
			cont_id, cont_id, cont_id, cont_id,
			CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE,
			0, 0,
			p_sys->resMan[0], p_sys->resMan[1], 
			p_sys->resMan[2], p_sys->resMan[3], NULL, NULL );
}

//----------------------------------------------------------------------------
/**
 *	@brief		パレットコピー
 *
 *	@param	p_sys		アクターシステム
 *	@param	p_work		ワーク
 *	@param	arc_file	アーカイブ
 *	@param	pltt_obj	パレットオブジェ
 *	@param	char_idx	キャラ
 *	@param	cel_idx		セル
 *	@param	anm_idx		アニメ
 *	@param	cont_id		管理ID
 *	@param	heap		ヒープ
 */
//-----------------------------------------------------------------------------
void NMIXGAME_CLACT_ResLoadEasy_PlttCopy( NMIXGAME_CLACT_SYS* p_sys, NMIXGAME_CLACT_RES_WORK* p_work, u32 arc_file, CLACT_U_RES_OBJ_PTR pltt_obj, u32 char_idx, u32 cel_idx, u32 anm_idx, u32 cont_id, u32 heap )
{
	BOOL result;
	u32 pltt_contid;
	
	// キャラクタ
	p_work->resobj[0] = CLACT_U_ResManagerResAddArcChar_AllocType( p_sys->resMan[0],
			arc_file, char_idx, FALSE, cont_id,
			NNS_G2D_VRAM_TYPE_2DMAIN, heap, ALLOC_BOTTOM );

	// パレット
	p_work->resobj[1] = pltt_obj;
	p_work->pltt_copy = TRUE;
	pltt_contid = CLACT_U_ResManagerGetResObjID( pltt_obj );

	// セル
	p_work->resobj[2] = CLACT_U_ResManagerResAddArcKindCell( p_sys->resMan[2],
			arc_file, cel_idx, FALSE, cont_id,
			CLACT_U_CELL_RES, heap );

	// アニメ
	p_work->resobj[3] = CLACT_U_ResManagerResAddArcKindCell( p_sys->resMan[3],
			arc_file, anm_idx, FALSE, cont_id,
			CLACT_U_CELLANM_RES, heap );


	// Vram転送
	result = CLACT_U_CharManagerSetCharModeAdjustAreaCont( p_work->resobj[0] );	
	GF_ASSERT( result );
	CLACT_U_ResManagerResOnlyDelete( p_work->resobj[0] );

	// ヘッダー作成
	CLACT_U_MakeHeader( &p_work->head,
			cont_id, pltt_contid, cont_id, cont_id,
			CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE,
			0, 0,
			p_sys->resMan[0], p_sys->resMan[1], 
			p_sys->resMan[2], p_sys->resMan[3], NULL, NULL );
}

//----------------------------------------------------------------------------
/**
 *	@brief	単純リソース破棄
 *
 *	@param	p_sys	システムワーク
 *	@param	p_work	ワーク
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
void NMIXGAME_CLACT_ResDeleteEasy( NMIXGAME_CLACT_SYS* p_sys, NMIXGAME_CLACT_RES_WORK* p_work )
{
	int i;
	CLACT_U_CharManagerDelete( p_work->resobj[0] );

	if( p_work->pltt_copy == FALSE ){
		CLACT_U_PlttManagerDelete( p_work->resobj[1] );
	}

	// リソース完全破棄
	for( i=0; i<4; i++ ){

		if( i != 1 ){
			CLACT_U_ResManagerResDelete( p_sys->resMan[i], p_work->resobj[i] );
		}else{

			// パレットのときだけコピーオブジェチェック
			if( p_work->pltt_copy == FALSE ){
				CLACT_U_ResManagerResDelete( p_sys->resMan[i], p_work->resobj[i] );
			}
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	アクター登録
 *
 *	@param	p_sys		システムワーク
 *	@param	p_work		リソースワーク
 *	@param	x			ｘ座標
 *	@param	y			ｙ座標
 *	@param	z			ｚ座標
 *	@param	pri			優先順位
 *	@param	heap		ヒープ
 *
 *	@return	ワーク
 */
//-----------------------------------------------------------------------------
CLACT_WORK_PTR NMIXGAME_CLACT_Add( NMIXGAME_CLACT_SYS* p_sys, NMIXGAME_CLACT_RES_WORK* p_work, fx32 x, fx32 y, fx32 z, int pri, int heap )
{
	CLACT_ADD_SIMPLE add;
	CLACT_WORK_PTR act;

	add.ClActSet	= p_sys->cas;
	add.ClActHeader	= &p_work->head;
	add.mat.x		= x;
	add.mat.y		= y;
	add.mat.z		= z;
	add.pri			= pri;
	add.DrawArea	= NNS_G2D_VRAM_TYPE_2DMAIN;
	add.heap		= heap;

	act = CLACT_AddSimple( &add );
	GF_ASSERT( act );
	return act;
} 



//-----------------------------------------------------------------------------
/**
 *			汎用計算システム
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *	@brief	動作初期化
 *
 *	@param	p_work			動作ワーク
 *	@param	s_x				開始x座標
 *	@param	e_x				終了x座標
 *	@param	count_max		カウント最大値
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void NMIX_DEMO_MoveReq( NMIX_DEMO_MOVE_WORK* p_work, int s_x, int e_x, int count_max )
{
	p_work->x = s_x;
	p_work->s_x = s_x;
	p_work->dis_x = e_x - s_x;
	p_work->count_max = count_max;
	p_work->count = 0;
}

//----------------------------------------------------------------------------
/**
 *	@brief	動作メイン
 *
 *	@param	p_work	ワーク
 *
 *	@retval	TRUE	終了
 *	@retval FALSE	途中
 */
//-----------------------------------------------------------------------------
BOOL NMIX_DEMO_MoveMain( NMIX_DEMO_MOVE_WORK* p_work )
{
	int w_x;

	// 現在座標取得
	w_x = p_work->dis_x * p_work->count;
	w_x = w_x / p_work->count_max;

	
	p_work->x = w_x + p_work->s_x;

	if( (p_work->count + 1) <= p_work->count_max ){
		p_work->count++;
		return FALSE;
	}

	p_work->count = p_work->count_max;
	return TRUE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	動作初期化
 *
 *	@param	p_work			動作ワーク
 *	@param	s_x				開始x座標
 *	@param	e_x				終了x座標
 *	@param	count_max		カウント最大値
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void NMIX_DEMO_MoveReqFx( NMIX_DEMO_MOVE_WORK_FX* p_work, fx32 s_x, fx32 e_x, int count_max )
{
	p_work->x = s_x;
	p_work->s_x = s_x;
	p_work->dis_x = e_x - s_x;
	p_work->count_max = count_max;
	p_work->count = 0;
}

//----------------------------------------------------------------------------
/**
 *	@brief	動作メイン
 *
 *	@param	p_work	ワーク
 *
 *	@retval	TRUE	終了
 *	@retval FALSE	途中
 */
//-----------------------------------------------------------------------------
BOOL NMIX_DEMO_MoveMainFx( NMIX_DEMO_MOVE_WORK_FX* p_work )
{
	fx32 w_x;

	// 現在座標取得
	w_x = FX_Mul( p_work->dis_x, p_work->count << FX32_SHIFT );
	w_x = FX_Div( w_x, p_work->count_max << FX32_SHIFT );
	
	p_work->x = w_x + p_work->s_x;

	if( (p_work->count + 1) <= p_work->count_max ){
		p_work->count++;
		return FALSE;
	}

	p_work->count = p_work->count_max;
	return TRUE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	加速動作汎用　初期化
 *
 *	@param	p_work	ワーク
 *	@param	s_x		開始座標
 *	@param	e_x		終了座標
 *	@param	s_s		開始速度
 *	@param	count_max ｶｳﾝﾀ値
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void NMIX_DEMO_AddMoveReqFx( NMIX_DEMO_ADDMOVE_WORK_FX* p_work, fx32 s_x, fx32 e_x, fx32 s_s, int count_max )
{
	fx32 t_x_t;	// タイムの２乗
	fx32 vot;	// 初速度＊タイム
	fx32 dis;
	fx32 a;

	dis = e_x - s_x;
	
	// 加速値を求める
	// a = 2(x - vot)/(t*t)
	t_x_t = (count_max * count_max) << FX32_SHIFT;
	vot = FX_Mul( s_s, count_max * FX32_ONE );
	vot = dis - vot;
	vot = FX_Mul( vot, 2*FX32_ONE );
	a = FX_Div( vot, t_x_t );

	p_work->x = s_x;
	p_work->s_x = s_x;
	p_work->s_s = s_s;
	p_work->s_a = a;
	p_work->count = 0;
	p_work->count_max = count_max;
}

//----------------------------------------------------------------------------
/**
 *	@brief	加速動作メイン
 *
 *	@param	p_work	ワーク
 *
 *	@retval	TRUE	終了
 *	@retval	FALSE	途中
 */
//-----------------------------------------------------------------------------
BOOL NMIX_DEMO_AddMoveMainFx( NMIX_DEMO_ADDMOVE_WORK_FX* p_work )
{
	fx32 dis;
	fx32 t_x_t;
	fx32 calc_work;
	fx32 vot;
	
	// 等加速度運動
	// dis = vot + 1/2( a*(t*t) )
	vot = FX_Mul( p_work->s_s, p_work->count << FX32_SHIFT );
	t_x_t = (p_work->count * p_work->count) << FX32_SHIFT;
	calc_work = FX_Mul( p_work->s_a, t_x_t );
	calc_work = FX_Div( calc_work, 2*FX32_ONE );	// 1/2(a*(t*t))
	dis = vot + calc_work;	///<移動距離

	p_work->x = p_work->s_x + dis;


	if( (p_work->count + 1) <= p_work->count_max ){
		p_work->count++;
		return FALSE;
	}

	p_work->count = p_work->count_max;
	return TRUE;
}


//----------------------------------------------------------------------------
/**
 *	@brief	ベクトル作成
 *	@param	x
 *	@param	y
 *	@param	z 
 *	@return	ベクトル
 */
//-----------------------------------------------------------------------------
VecFx32 NMIX_DEMO_MakeVec( fx32 x, fx32 y, fx32 z )
{
	VecFx32 vec;
	vec.x = x;
	vec.y = y;
	vec.z = z;
	return vec;
}






//-----------------------------------------------------------------------------
/**
 *					木の実なべに投げ込み
*/
//-----------------------------------------------------------------------------

#define NMIX_DEMO_NUTS_IN_RESMAN_ID	( 1000 )
// オブジェクトシーケンス
enum{
	NMIX_DEMO_NUTSIN_OBJ_SEQ_WAIT,
	NMIX_DEMO_NUTSIN_OBJ_SEQ_MOVE,
	NMIX_DEMO_NUTSIN_OBJ_SEQ_POCHAN,
	NMIX_DEMO_NUTSIN_OBJ_SEQ_END,
};

// 木の実動さテーブル
typedef struct{
	fx32 eff_ssx;	// 初速度ｘ
	fx32 eff_ssy;	// 初速度ｙ
	s16 eff_sx;		// 開始ｘ座標 
	s16 eff_ex;		// 終了ｘ座標
	
	s16 eff_sy;		// 開始ｙ座標
	s16 eff_ey;		// 終了ｙ座標
	u8 eff_count_max;	// カウント値
	u8 wait;		// 発射ウエイト
} NMIX_DEMO_NUTS_IN_PARAM;

static const NMIX_DEMO_NUTS_IN_PARAM NMIX_DEMO_NutsInMoveParam[ NUTMIXER_MEMBER_MAX ] = {
	{
		FX32_CONST( 0 ),	// 初速度ｘ
		FX32_CONST( 0 ),	// 初速度ｙ
		64,		// 開始ｘ座標 
		96,		// 終了ｘ座標
		-32,	// 開始ｙ座標
		88,		// 終了ｙ座標
		32,	// カウント値
		10,	// 発射ウエイト
	},
	{
		FX32_CONST( 0 ),	// 初速度ｘ
		FX32_CONST( 0 ),	// 初速度ｙ
		280,	// 開始ｘ座標 
		156,	// 終了ｘ座標
		192,	// 開始ｙ座標
		128,	// 終了ｙ座標
		32,	// カウント値
		32,	// 発射ウエイト
	},
	{
		FX32_CONST( 0 ),	// 初速度ｘ
		FX32_CONST( 0 ),	// 初速度ｙ
		-32,	// 開始ｘ座標 
		128,	// 終了ｘ座標
		32,		// 開始ｙ座標
		96,		// 終了ｙ座標
		32,	// カウント値
		32,	// 発射ウエイト
	},
	{
		FX32_CONST( 0 ),	// 初速度ｘ
		FX32_CONST( 0 ),	// 初速度ｙ
		128,	// 開始ｘ座標 
		116,	// 終了ｘ座標
		-32,	// 開始ｙ座標
		96,		// 終了ｙ座標
		32,	// カウント値
		32,	// 発射ウエイト
	},
};

// 木の実グラフィックデータIDX取得マクロ
#define	NMIXGAMEDEMO_NUTSIN_PL_GET(x)		( NARC_ntag_gra_kinomi_001_NCLR + ((x)-NUTS_START_ITEMNUM) )
#define	NMIXGAMEDEMO_NUTSIN_CH_GET(x)		( NARC_ntag_gra_kinomi_001_NCGR + ((x)-NUTS_START_ITEMNUM) )

//----------------------------------------------------------------------------
/**
 *	@brief	ワークの初期化
 *
 *	@param	p_work		ワーク
 *	@param	nuts_num	木の実数
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_NutsIn_Init( NMIX_DEMO_NUTS_IN* p_work, int nuts_num )
{
	memset( p_work, 0, sizeof(NMIX_DEMO_NUTS_IN) );
	p_work->nuts_num = nuts_num;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ワークの破棄
 *
 *	@param	p_work	ワーク
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_NutsIn_Delete( NMIX_DEMO_NUTS_IN* p_work )
{
	// リソース破棄していません。
	GF_ASSERT( p_work->res_load == FALSE );
	memset( p_work, 0, sizeof(NMIX_DEMO_NUTS_IN) );
}

//----------------------------------------------------------------------------
/**
 *	@brief	グラフィックファイル読み込み
 *
 *	@param	p_work					ワーク
 *	@param	p_get_ko_before_data	ゲーム開始前通信データ
 *	@param	p_clact					アクターシステム
 *	@param	p_def_oam_res			デフォルトOAMリソース
 *	@param	heapID					ヒープ
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_NutsIn_GraphicLoad( NMIX_DEMO_NUTS_IN* p_work, NUTMIX_COMM_BEFORE_KO* p_get_ko_before_data, NMIXGAME_CLACT_SYS* p_clact, NMIXGAME_CLACT_RES_WORK* p_def_oam_res, u32 heapID )
{
	int i;
	int load_num;
	
	// 通信相手の木の実データを読み込む	中身はアイテムナンバー
	load_num = 0;
	for( i=0; i<NUTMIXER_MEMBER_MAX; i++ ){
		
		// 0以外なら木の実データ
		if( p_get_ko_before_data->before[i].nut_type != 0 ){
			
//			OS_Printf( "きのみ %d cont_id %d\n", p_get_ko_before_data->before[i].nut_type, NMIX_DEMO_NUTS_IN_RESMAN_ID + i );
			
			// 読み込み処理
			NMIXGAME_CLACT_ResLoadEasy( p_clact, 
					&p_work->res_work[ load_num ], ARC_NTAG_GRA,
					NMIXGAMEDEMO_NUTSIN_PL_GET( p_get_ko_before_data->before[i].nut_type ), 1,
					NMIXGAMEDEMO_NUTSIN_CH_GET( p_get_ko_before_data->before[i].nut_type ),
					NARC_ntag_gra_kinomi_001_NCER, NARC_ntag_gra_kinomi_001_NANR,
					NMIX_DEMO_NUTS_IN_RESMAN_ID + i, heapID );

			// アクターの作成処理
			p_work->clact[ load_num ] = NMIXGAME_CLACT_Add( p_clact,
					&p_work->res_work[ load_num ] ,0,0,0,0, heapID );
			CLACT_SetDrawFlag( p_work->clact[ load_num ], FALSE );
			// 水にポチャンも使う
			p_work->pochan[ load_num ] = NMIXGAME_CLACT_Add( p_clact,
					&p_def_oam_res[ NMIX_GAME_DEF_OAM_RES_START ], 
					0,0,0,0, heapID );
			CLACT_SetDrawFlag( p_work->pochan[ load_num ], FALSE );
			CLACT_AnmChg( p_work->pochan[ load_num ], 1 );
			load_num ++;
		}

		// 全部読み込んだかチェック
		if( p_work->nuts_num == load_num ){
//			OS_Printf( "load_num %d i[%d] \n", load_num, i );
			break;
		}
	}

	p_work->res_load = TRUE;
} 

//----------------------------------------------------------------------------
/**
 *	@brief	グラフィック破棄
 *
 *	@param	p_work	ワーク
 *	@param	p_clact	セルアクターシステム
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_NutsIn_GraphicRelease( NMIX_DEMO_NUTS_IN* p_work, NMIXGAME_CLACT_SYS* p_clact )
{
	int i;

	GF_ASSERT( p_work->res_load == TRUE );

	for( i=0; i<p_work->nuts_num; i++ ){
		CLACT_Delete( p_work->clact[i] );
		CLACT_Delete( p_work->pochan[i] );
		NMIXGAME_CLACT_ResDeleteEasy( p_clact, &p_work->res_work[i] );
	}
	p_work->res_load = FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	木の実投入エフェクト開始
 *
 *	@param	p_work	ワーク
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_NutsIn_Start( NMIX_DEMO_NUTS_IN* p_work )
{
	int i;
	VecFx32 matrix;
	
	GF_ASSERT( p_work->move_flg == FALSE );

	for( i=0; i<p_work->nuts_num; i++ ){
		// 動さパラメータ初期化
		NMIX_DEMO_AddMoveReqFx( &p_work->move_x[i], 
				NMIX_DEMO_NutsInMoveParam[i].eff_sx * FX32_ONE,
				NMIX_DEMO_NutsInMoveParam[i].eff_ex * FX32_ONE,
				NMIX_DEMO_NutsInMoveParam[i].eff_ssx,
				NMIX_DEMO_NutsInMoveParam[i].eff_count_max );	

		NMIX_DEMO_AddMoveReqFx( &p_work->move_y[i], 
				NMIX_DEMO_NutsInMoveParam[i].eff_sy * FX32_ONE,
				NMIX_DEMO_NutsInMoveParam[i].eff_ey * FX32_ONE,
				NMIX_DEMO_NutsInMoveParam[i].eff_ssy,
				NMIX_DEMO_NutsInMoveParam[ i].eff_count_max );	

		// アクターに座標設定
		matrix = NMIX_DEMO_MakeVec( p_work->move_x[i].x,
				p_work->move_y[i].x, 0 );
		CLACT_SetMatrix( p_work->clact[i], &matrix );

		p_work->obj_seq[i] = 0;
		p_work->obj_wait[i] = NMIX_DEMO_NutsInMoveParam[i].wait;
	}

	// 発射総数初期化
	p_work->start_count = 0;
	p_work->move_flg = TRUE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	木の実投入エフェクトメイン
 *
 *	@param	p_work	ワーク
 *
 *	@retval	NMIX_DEMO_NUTS_RET_FALSE,	// 途中
 * 	@retval	NMIX_DEMO_NUTS_RET_TRUE,	// 終了
 *	@retval	NMIX_DEMO_NUTS_RET_NUTS_00,	// 0投入
 *	@retval	NMIX_DEMO_NUTS_RET_NUTS_01,	// 1投入
 *	@retval	NMIX_DEMO_NUTS_RET_NUTS_02,	// 2投入
 *	@retval	NMIX_DEMO_NUTS_RET_NUTS_03,	// 3投入
 */
//-----------------------------------------------------------------------------
u32 NMixGameDemo_NutsIn_Main( NMIX_DEMO_NUTS_IN* p_work )
{
	int i;
	BOOL result;
	VecFx32	matrix;
	u32 ret = NMIX_DEMO_NUTS_RET_FALSE;

	if( p_work->move_flg == FALSE ){
		return NMIX_DEMO_NUTS_RET_TRUE;
	}

	// 発射部分
	if( p_work->start_count < p_work->nuts_num ){

		p_work->obj_wait[ p_work->start_count ]--;
		if( p_work->obj_wait[ p_work->start_count ] <= 0 ){
			// 発射
			p_work->obj_seq[ p_work->start_count ] = NMIX_DEMO_NUTSIN_OBJ_SEQ_MOVE;
			CLACT_SetDrawFlag( p_work->clact[p_work->start_count], TRUE );

			// 戻り値
			ret = NMIX_DEMO_NUTS_RET_NUTS_00 + p_work->start_count;
			p_work->start_count ++;
		}
	}
	
	// 動さ部分
	for( i=0; i<p_work->nuts_num; i++ ){
		switch( p_work->obj_seq[ i ] ){
		case NMIX_DEMO_NUTSIN_OBJ_SEQ_WAIT:
			break;
			
		case NMIX_DEMO_NUTSIN_OBJ_SEQ_MOVE:
			result = NMIX_DEMO_AddMoveMainFx( &p_work->move_x[i] );	
			NMIX_DEMO_AddMoveMainFx( &p_work->move_y[i] );

			matrix = NMIX_DEMO_MakeVec( p_work->move_x[i].x,
					p_work->move_y[i].x, 0 );
			CLACT_SetMatrix( p_work->clact[i], &matrix );
			if( result == TRUE ){
				CLACT_SetMatrix( p_work->pochan[i], &matrix );
				CLACT_SetDrawFlag( p_work->pochan[i], TRUE );
				CLACT_SetAnmFlag( p_work->pochan[i], TRUE );
				CLACT_SetDrawFlag( p_work->clact[i], FALSE );

				// ポチャン音開始
				Snd_SePlay( NMIXGAME_SE_NUTS_SOOP_IN );
				
				p_work->obj_seq[ i ]++;
			}
			break;
			
		case NMIX_DEMO_NUTSIN_OBJ_SEQ_POCHAN:
			// アニメ終了待ち
			if( CLACT_AnmActiveCheck( p_work->pochan[i] ) == FALSE ){
				CLACT_SetDrawFlag( p_work->pochan[i], FALSE );
				p_work->obj_seq[i]++;
			}
			break;
			
		case NMIX_DEMO_NUTSIN_OBJ_SEQ_END:
			break;

		default:
			GF_ASSERT( 0 );
			break;
		}
	}

	// 終了チェック
	if( p_work->obj_seq[ p_work->nuts_num - 1 ] == NMIX_DEMO_NUTSIN_OBJ_SEQ_END ){
		p_work->move_flg = FALSE;
		return NMIX_DEMO_NUTS_RET_TRUE;
	}
	return ret;
}




//-----------------------------------------------------------------------------
/**
 *		上画面制御
 */
//-----------------------------------------------------------------------------
#define NMIX_SUBWIN_FONTBMP_X	( 4 )			// 文字面ビットマップsize
#define NMIX_SUBWIN_FONTBMP_Y	( 19 )			// 文字面ビットマップsize
#define NMIX_SUBWIN_FONTBMP_CX	( 23 )			// 文字面ビットマップsize
#define NMIX_SUBWIN_FONTBMP_CY	( 4 )			// 文字面ビットマップsize
#define NMIX_SUBWIN_FONT_COLOR		( 0 )		// 枠用カラーパレット
#define NMIX_SUBWIN_FONT_CG_OFS		( 1 )
#define NMIX_SUBWIN_FONT_STR_COLOR	( 1 )		// フォント用カラーパレット
#define NMIX_SUBWIN_FONTBMP_PRICOLOR	( GF_PRINTCOLOR_MAKE(1,2,15) )

#define NMIX_SUBWIN_BACK_COLOR		( 2 )	// 背景カラーパレット
#define NMIX_SUBWIN_BACK_COLOR_NUM	( 2 )	// 背景カラーパレット使用数

#define NMIX_SUBWIN_PLNAME_FONTBMP_X	( 6 )		// 文字面ビットマップ位置
#define NMIX_SUBWIN_PLNAME_FONTBMP_Y	( 13 )		// 文字面ビットマップ位置
#define NMIX_SUBWIN_PLNAME_FONTBMP_CX	( 20 )		// 文字面ビットマップsize
#define NMIX_SUBWIN_PLNAME_FONTBMP_CY	( 8 )		// 文字面ビットマップsize
#define NMIX_SUBWIN_BACK_PLNAME_WAKU_DRAW_CX	( 5 )	// 枠　表示開始ｘ
#define NMIX_SUBWIN_BACK_PLNAME_WAKU_DRAW_CY	( 13 )	// 枠　表示開始ｙ
#define NMIX_SUBWIN_BACK_PLNAME_WAKU_DRAW_COX	( 12 )	// 枠　表示　オフセット
#define NMIX_SUBWIN_BACK_PLNAME_WAKU_DRAW_COY	( 5 )	// 枠　表示　オフセット
#define NMIX_SUBWIN_BACK_PLNAME_WAKU_CX		( 10 )		// 枠　サイズ
#define NMIX_SUBWIN_BACK_PLNAME_WAKU_CY		( 4 )		// 枠　サイズ
#define NMIX_SUBWIN_BACK_PLNAME_WAKU_XNUM	( 2 )
#define NMIX_SUBWIN_BACK_PLNAME_FONT_OFSX	( 32 )	// 文字の枠左上から中心までのオフセット
#define NMIX_SUBWIN_BACK_PLNAME_FONT_OFSY	( 8 )	// 文字の枠左上から中心までのオフセット


static void NMixSubWin_BmpInit( NMIX_DEMO_SUB_WIN* p_work, u32 heapID );
static void NMixSubWin_BmpRelease( NMIX_DEMO_SUB_WIN* p_work );
static void NMixSubWin_BackGroundInit( NMIX_DEMO_SUB_WIN* p_work, u32 heapID );
static void NMixSubWin_BackGroundRelease( NMIX_DEMO_SUB_WIN* p_work );
static void NmixSubWIn_BmpTextSet( GF_BGL_BMPWIN* p_bmp, STRBUF* str, int x, int y );



//----------------------------------------------------------------------------
/**
 *	@brief	サブ画面制御ワークの初期化
 *
 *	@param	p_work				ワーク
 *	@param	pp_trainer_name		トレーナー名配列へのポインタ
 *	@param	comm_count			通信相手数
 *	@param	p_msg_data			メッセージデータ
 *	@param	p_comm_data			通信データ
 *	@param	wnd_type			ウィンドウタイプ
 *	@param	heapID				ヒープID
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_SubWin_Init( NMIX_DEMO_SUB_WIN* p_work, int comm_count, NMIXER_MSG* p_msg_data, NUTMIX_GAME_COMM_PACK* p_comm_data, int wnd_type, u32 heapID )
{
	memset( p_work, 0, sizeof(NMIX_DEMO_SUB_WIN) );
	p_work->p_msg_data = p_msg_data;
	p_work->comm_count = comm_count;
	p_work->heapID = heapID;
	p_work->p_comm_data = p_comm_data;
	p_work->wnd_type = wnd_type;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ワークデータ破棄
 *	
 *	@param	p_work	ワーク
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_SubWin_Delete( NMIX_DEMO_SUB_WIN* p_work )
{
	// リソース破棄していません
	GF_ASSERT( p_work->res_load == FALSE );
	memset( p_work, 0, sizeof(NMIX_DEMO_SUB_WIN) );
}

//----------------------------------------------------------------------------
/**
 *	@brief	3Dリソース読み込み処理
 *
 *	@param	p_work		ワーク
 *	@param	p_bgl		BGL
 *	@param	heapID		ヒープID
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_SubWin_GraphicLoad( NMIX_DEMO_SUB_WIN* p_work, GF_BGL_INI* p_bgl, u32 heapID )
{
	GF_ASSERT( p_work->res_load == FALSE );

	// BGL設定
	p_work->p_bgl = p_bgl;
	
	// ビットマップウィンドウ初期化
	NMixSubWin_BmpInit( p_work, heapID );

	// 背景設定
	NMixSubWin_BackGroundInit( p_work, heapID );

	p_work->res_load = TRUE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	
 *
 *	@param	p_work 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_SubWin_GraphicRelease( NMIX_DEMO_SUB_WIN* p_work )
{
	GF_ASSERT( p_work->res_load == TRUE );
	
	// ビットマップウィンドウ破棄
	NMixSubWin_BmpRelease( p_work );

	// 背景破棄
	NMixSubWin_BackGroundRelease( p_work );

	p_work->res_load = FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ウィンドウ付きテキスト登録
 *
 *	@param	p_work	ワーク
 *	@param	msgidx	表示するメッセージ
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_SubWin_WinNutsOn( NMIX_DEMO_SUB_WIN* p_work, int nuts_id )
{
	// 木の実文字列作成
	WORDSET_RegisterItemName( p_work->p_msg_data->wset, 0, nuts_id );
	WORDSET_ExpandStr( p_work->p_msg_data->wset, p_work->p_msg_data->tmp, p_work->p_msg_data->nuts_in );
	
	// ビットマップ初期化
	GF_BGL_BmpWinDataFill( p_work->p_bmp, 15 );
	NmixSubWIn_BmpTextSet( p_work->p_bmp, p_work->p_msg_data->tmp, 0, 0 );
	BmpTalkWinWrite( p_work->p_bmp, WINDOW_TRANS_ON, NMIX_SUBWIN_FONT_CG_OFS, NMIX_SUBWIN_FONT_COLOR );

}

//----------------------------------------------------------------------------
/**
 *	@brief	ビットマップ面表示OFF
 *
 *	@param	p_work	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_SubWin_WinNutsOff( NMIX_DEMO_SUB_WIN* p_work )
{
	GF_BGL_BmpWinOff( p_work->p_bmp );
	// メッセージスクリーンをクリーン
	GF_BGL_ScrClear( p_work->p_bgl, GF_BGL_FRAME0_S );
}

//----------------------------------------------------------------------------
/**
 *	@brief	そのまま　お待ちください描画
 *
 *	@param	p_work	ワーク
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_SubWin_WinWaitMsgOn( NMIX_DEMO_SUB_WIN* p_work )
{
	// ビットマップ初期化
	GF_BGL_BmpWinDataFill( p_work->p_bmp, 15 );
	NmixSubWIn_BmpTextSet( p_work->p_bmp, p_work->p_msg_data->wait, 0, 0 );
	BmpTalkWinWrite( p_work->p_bmp, WINDOW_TRANS_ON, NMIX_SUBWIN_FONT_CG_OFS, NMIX_SUBWIN_FONT_COLOR );
}


//----------------------------------------------------------------------------
/**
 *	@brief	各プレイヤーの名前設定
 *
 *	@param	p_work	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_SubWin_PlayerNameOn( NMIX_DEMO_SUB_WIN* p_work )
{
	int i;
	int x;
	int y;
	int x_draw;
	int y_draw;
	int netid;
	int name_draw_x, name_draw_y;

	// 1人プレイのときは、出さない
	if( p_work->comm_count == 1 ){
		return ;
	}
	
	// 背景スクリーンデータに枠を書く
	for( i=0; i<p_work->comm_count; i++ ){

		x = i % NMIX_SUBWIN_BACK_PLNAME_WAKU_XNUM;
		y = (i / NMIX_SUBWIN_BACK_PLNAME_WAKU_XNUM);

		x_draw = x * NMIX_SUBWIN_BACK_PLNAME_WAKU_DRAW_COX;
		y_draw = y * NMIX_SUBWIN_BACK_PLNAME_WAKU_DRAW_COY;
		x *= NMIX_SUBWIN_BACK_PLNAME_WAKU_CX;
		y *= NMIX_SUBWIN_BACK_PLNAME_WAKU_CY;

		// スクリーンデータ書き込み
		GF_BGL_ScrWriteExpand( p_work->p_bgl, GF_BGL_FRAME1_S,
				NMIX_SUBWIN_BACK_PLNAME_WAKU_DRAW_CX + x_draw,
				NMIX_SUBWIN_BACK_PLNAME_WAKU_DRAW_CY + y_draw,
				NMIX_SUBWIN_BACK_PLNAME_WAKU_CX,
				NMIX_SUBWIN_BACK_PLNAME_WAKU_CY,
				p_work->p_playername_scrn->rawData, 
				x, y,
				NMIX_SUBWIN_BACK_PLNAME_WAKU_CX * 2,
				NMIX_SUBWIN_BACK_PLNAME_WAKU_CY * 2 );

		// パレットをあわせる
		GF_BGL_ScrPalChange( p_work->p_bgl, GF_BGL_FRAME1_S,
				NMIX_SUBWIN_BACK_PLNAME_WAKU_DRAW_CX + x_draw,
				NMIX_SUBWIN_BACK_PLNAME_WAKU_DRAW_CY + y_draw,
				NMIX_SUBWIN_BACK_PLNAME_WAKU_CX,
				NMIX_SUBWIN_BACK_PLNAME_WAKU_CY,
				NMIX_SUBWIN_BACK_COLOR );


		// BMPに名前を書く
		netid = p_work->p_comm_data->playno_netid[ i ];
		WORDSET_RegisterPlayerName( p_work->p_msg_data->wset, 0, p_work->p_comm_data->p_mystate[netid] );
		WORDSET_ExpandStr( p_work->p_msg_data->wset, p_work->p_msg_data->tmp, p_work->p_msg_data->tr_name );


		name_draw_x = NMixDemo_GetStrLeftX_CenterKey( (x_draw*8) + NMIX_SUBWIN_BACK_PLNAME_FONT_OFSX, p_work->p_msg_data->tmp, FONT_TALK );	// 左端座標を求める
		name_draw_y = (y_draw*8) + NMIX_SUBWIN_BACK_PLNAME_FONT_OFSY;
		NmixSubWIn_BmpTextSet( p_work->p_bmp_plname, p_work->p_msg_data->tmp, 
				name_draw_x, name_draw_y );
	}

	GF_BGL_BmpWinOnVReq( p_work->p_bmp_plname );
	// スクリーンデータ転送
	GF_BGL_LoadScreenV_Req( p_work->p_bgl, GF_BGL_FRAME1_S );
}


//----------------------------------------------------------------------------
/**
 *	@brief	ビットマップウィンドウ初期化
 */
//-----------------------------------------------------------------------------
static void NMixSubWin_BmpInit( NMIX_DEMO_SUB_WIN* p_work, u32 heapID )
{
	// 背景の設定とビットマップウィンドウ設定
	p_work->p_bmp = GF_BGL_BmpWinAllocGet( heapID, 1 );
	p_work->p_bmp_plname = GF_BGL_BmpWinAllocGet( heapID, 1 );
	
	// ビットマップウィンドウ登録
	GF_BGL_BmpWinAdd( p_work->p_bgl, p_work->p_bmp,
			GF_BGL_FRAME0_S, 
			NMIX_SUBWIN_FONTBMP_X,
			NMIX_SUBWIN_FONTBMP_Y,
			NMIX_SUBWIN_FONTBMP_CX, 
			NMIX_SUBWIN_FONTBMP_CY, 
			NMIX_SUBWIN_FONT_STR_COLOR,
			TALK_WIN_CGX_SIZ + 1 );

	// ビットマップウィンドウ登録
	GF_BGL_BmpWinAdd( p_work->p_bgl, p_work->p_bmp_plname,
			GF_BGL_FRAME0_S, 
			NMIX_SUBWIN_PLNAME_FONTBMP_X,
			NMIX_SUBWIN_PLNAME_FONTBMP_Y,
			NMIX_SUBWIN_PLNAME_FONTBMP_CX, 
			NMIX_SUBWIN_PLNAME_FONTBMP_CY, 
			NMIX_SUBWIN_FONT_STR_COLOR,
			TALK_WIN_CGX_SIZ + 1 );

	// クリーン
	GF_BGL_BmpWinDataFill( p_work->p_bmp, 15 );
	GF_BGL_BmpWinDataFill( p_work->p_bmp_plname, 0 );

	// 枠を描画
	TalkWinGraphicSet( p_work->p_bgl, GF_BGL_FRAME0_S,
			NMIX_SUBWIN_FONT_CG_OFS,
			NMIX_SUBWIN_FONT_COLOR,
			p_work->wnd_type, heapID );

	// 会話フォントパレット読み込み
	TalkFontPaletteLoad( PALTYPE_SUB_BG, 
			NMIX_SUBWIN_FONT_STR_COLOR * 32, heapID );

	BmpTalkWinWrite( p_work->p_bmp, WINDOW_TRANS_OFF,
			NMIX_SUBWIN_FONT_CG_OFS,
			NMIX_SUBWIN_FONT_COLOR );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ビットマップウィンドウ破棄
 */
//-----------------------------------------------------------------------------
static void NMixSubWin_BmpRelease( NMIX_DEMO_SUB_WIN* p_work )
{
	GF_BGL_BmpWinDel( p_work->p_bmp );
	GF_BGL_BmpWinFree( p_work->p_bmp, 1 );
	GF_BGL_BmpWinDel( p_work->p_bmp_plname );
	GF_BGL_BmpWinFree( p_work->p_bmp_plname, 1 );
}

//----------------------------------------------------------------------------
/**
 *	@brief		背景初期化
 */
//-----------------------------------------------------------------------------
static void NMixSubWin_BackGroundInit( NMIX_DEMO_SUB_WIN* p_work, u32 heapID )
{
	int scrn_idx;
	
	// ベース背景
	ArcUtil_PalSet( ARC_NUTMIXER_GRA, NARC_nutmixer_cook_m_NCLR, 
			PALTYPE_SUB_BG, NMIX_SUBWIN_BACK_COLOR*32,
			NMIX_SUBWIN_BACK_COLOR_NUM*32, heapID );
	ArcUtil_BgCharSet( ARC_NUTMIXER_GRA, NARC_nutmixer_cook_m_NCGR,
			p_work->p_bgl, GF_BGL_FRAME1_S, 0, 0, FALSE, heapID );

	// スクリーンデータ読み込み
	if( p_work->comm_count == 1 ){
		scrn_idx = NARC_nutmixer_cook_m1_NSCR;
	}else{
		scrn_idx = NARC_nutmixer_cook_m2_NSCR;
	}
	p_work->p_bg_scrn_buf = ArcUtil_ScrnDataGet( ARC_NUTMIXER_GRA, 
			scrn_idx, FALSE, &p_work->p_bg_scrn, heapID );
	
	// スクリーンデータ書き込み
	GF_BGL_ScrWrite( p_work->p_bgl, GF_BGL_FRAME1_S,
			p_work->p_bg_scrn->rawData, 0, 0,
			p_work->p_bg_scrn->screenWidth / 8,
			p_work->p_bg_scrn->screenHeight / 8 );

	// パレットをあわせる
	GF_BGL_ScrPalChange( p_work->p_bgl, GF_BGL_FRAME1_S,
			0, 0, 
			p_work->p_bg_scrn->screenWidth / 8,
			p_work->p_bg_scrn->screenHeight / 8,
			NMIX_SUBWIN_BACK_COLOR+1 );


	// プレイヤー名背景を読み込み
	p_work->p_playername_scrn_buf = ArcUtil_ScrnDataGet( ARC_NUTMIXER_GRA, 
			NARC_nutmixer_cook_m2a_NSCR, FALSE, 
			&p_work->p_playername_scrn, heapID );
	
	// スクリーンデータ転送
	GF_BGL_LoadScreenV_Req( p_work->p_bgl, GF_BGL_FRAME1_S );
}

//----------------------------------------------------------------------------
/**
 *	@brief		背景破棄
 */
//-----------------------------------------------------------------------------
static void NMixSubWin_BackGroundRelease( NMIX_DEMO_SUB_WIN* p_work )
{
	sys_FreeMemoryEz( p_work->p_bg_scrn_buf );
	sys_FreeMemoryEz( p_work->p_playername_scrn_buf );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ビットマップウィンドウにテキスト設定
 *
 *	@param	p_bmp		ビットマップ
 *	@param	str			文字列
 *	@param	x			ｘ座標
 *	@param	y			ｙ座標
 */
//-----------------------------------------------------------------------------
static void NmixSubWIn_BmpTextSet( GF_BGL_BMPWIN* p_bmp, STRBUF* str, int x, int y )
{
	// 文字列書き込み
	GF_STR_PrintColor( p_bmp, FONT_TALK, str, x, y, 0, NMIX_SUBWIN_FONTBMP_PRICOLOR, NULL );
}





//-----------------------------------------------------------------------------
/**
 *		カウントダウン
 */
//-----------------------------------------------------------------------------

#define NMIX_GAMEDEMO_COUNTDOWN_X	( 128*FX32_ONE )
#define NMIX_GAMEDEMO_COUNTDOWN_Y	( 96*FX32_ONE )

//----------------------------------------------------------------------------
/**
 *	@brief	カウントダウンワーク初期化
 *
 *	@param	p_work		ワーク
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_CountDown_Init( NMIX_DEMO_COUNTDOWN* p_work )
{
	memset( p_work, 0, sizeof(NMIX_DEMO_COUNTDOWN) );
}

//----------------------------------------------------------------------------
/**
 *	@brief	カウントダウンワーク破棄
 *
 *	@param	p_work	ワーク
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_CountDown_Delete( NMIX_DEMO_COUNTDOWN* p_work )
{
	// リソース破棄していません
	GF_ASSERT( p_work->res_load == FALSE );
	memset( p_work, 0, sizeof(NMIX_DEMO_COUNTDOWN) );
}

//----------------------------------------------------------------------------
/**
 *	@brief	カウントダウンリソース読み込み
 *
 *	@param	p_work			ワーク
 *	@param	p_clact			セルアクター
 *	@param	p_def_oam_res	デフォルトOAMリソース
 *	@param	heapID			ヒープID 
 *	@param	res_no			リソースナンバー
 *	@param	anm_idx			アニメインデックス
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_CountDown_GraphicLoad( NMIX_DEMO_COUNTDOWN* p_work, NMIXGAME_CLACT_SYS* p_clact, NMIXGAME_CLACT_RES_WORK* p_def_oam_res, u32 heapID, u32 res_no, u32 anm_idx )
{
	// 水にポチャンも使う
	p_work->clact = NMIXGAME_CLACT_Add( p_clact,
			&p_def_oam_res[ res_no ], 
			NMIX_GAMEDEMO_COUNTDOWN_X, NMIX_GAMEDEMO_COUNTDOWN_Y,
			0, 0, heapID );
	CLACT_SetDrawFlag( p_work->clact, FALSE );
	CLACT_AnmChg( p_work->clact, anm_idx );

	p_work->res_load = TRUE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	カウントダウンリソース破棄
 *	
 *	@param	p_work	ワーク
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_CountDown_GraphicRelease( NMIX_DEMO_COUNTDOWN* p_work )
{
	GF_ASSERT( p_work->res_load == TRUE );
	CLACT_Delete( p_work->clact );
	p_work->res_load = FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	カウントダウン開始
 *
 *	@param	p_work ワーク
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_CountDown_Start( NMIX_DEMO_COUNTDOWN* p_work )
{
	CLACT_SetDrawFlag( p_work->clact, TRUE );
	CLACT_SetAnmFlag( p_work->clact, TRUE );
}
void NMixGameDemo_CountDown_Start_Pen( NMIX_DEMO_COUNTDOWN* p_work )
{
	VecFx32 matrix;
	
	CLACT_SetDrawFlag( p_work->clact, TRUE );
	CLACT_SetAnmFlag( p_work->clact, TRUE );

	matrix.x = 168 * FX32_ONE;
	matrix.y = 60 * FX32_ONE;

	CLACT_SetMatrix( p_work->clact, &matrix );
}

//----------------------------------------------------------------------------
/**
 *	@brief	カウントダウンメイン
 *
 *	@param	p_work	ワーク
 *
 *	@retval	TRUE	終了
 *	@retval	FALSE	途中
 */
//-----------------------------------------------------------------------------
BOOL NMixGameDemo_CountDown_Main( NMIX_DEMO_COUNTDOWN* p_work )
{
	if( CLACT_AnmActiveCheck( p_work->clact ) == FALSE ){
		return TRUE;
	}
	return FALSE;
}


//-----------------------------------------------------------------------------
/**
 *		鍋グラフィック描画管理システム
 */
//-----------------------------------------------------------------------------
// 炎アニメ
static const u8 FireAnmSync[ NMIX_SOOPTYPE_SOOP_NUM ] = {
	4,
	3,
	2
};
static const fx32 FireScaleMin[ NMIX_SOOPTYPE_SOOP_NUM ] = {
	FX32_CONST(0.98f),
	FX32_CONST(0.95f),
	FX32_CONST(0.92f),
};
static const fx32 FireScaleMax[ NMIX_SOOPTYPE_SOOP_NUM ] = {
	FX32_CONST(1.0f),
	FX32_CONST(1.0f),
	FX32_CONST(1.0f),
};


//----------------------------------------------------------------------------
/**
 *	@brief	ワーク内初期化
 *
 *	@param	p_work	ワーク
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_NabeGra_Init( NMIX_DEMO_NABE_GRA* p_work )
{
	memset( p_work, 0, sizeof(NMIX_DEMO_NABE_GRA) );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ワーク破棄
 *
 *	@param	p_work 
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_NabeGra_Delete( NMIX_DEMO_NABE_GRA* p_work )
{
	GF_ASSERT( p_work->res_load == FALSE );
	memset( p_work, 0, sizeof(NMIX_DEMO_NABE_GRA) );
}

//----------------------------------------------------------------------------
/**
 *	@brief	リソース読み込み
 *
 *	@param	p_work		ワーク
 *	@param	wsp_sys		ソフトウェアスプライトシステム
 *	@param	heapID		ヒープID
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_NabeGra_GraphicLoad( NMIX_DEMO_NABE_GRA* p_work, SWSP_SYS_PTR	swsp_sys, u32 heapID )
{
	int i;
	static const u8 NabeCharTbl[] = {
		NARC_nutmixer_cook_s_fire_NCBR,
		NARC_nutmixer_cook_s_nabe1_NCBR,
		NARC_nutmixer_cook_s_nabe2_NCBR,
		NARC_nutmixer_cook_s_soop1_NCBR,
		NARC_nutmixer_cook_s_soop2_NCBR,
		NARC_nutmixer_cook_s_soop3_NCBR,
	};
	static const u8 NabePlttTbl[] = {
		NARC_nutmixer_cook_s_fire1_NCLR,
		NARC_nutmixer_cook_s_fire2_NCLR,
		NARC_nutmixer_cook_s_fire3_NCLR,
		NARC_nutmixer_cook_s_nabe1_NCLR,
		NARC_nutmixer_cook_s_nabe2_NCLR,
		NARC_nutmixer_cook_s_soop1_NCLR,
		NARC_nutmixer_cook_s_soop2_NCLR,
		NARC_nutmixer_cook_s_soop3_NCLR,
	};
	static const u8 NabeObjCharTbl[] = {
		NMIX_DEMO_NABE_CHAR_FIRE,
		NMIX_DEMO_NABE_CHAR_FIRE,
		NMIX_DEMO_NABE_CHAR_FIRE,
		NMIX_DEMO_NABE_CHAR_NABE_UP,
		NMIX_DEMO_NABE_CHAR_NABE_DOWN,
		NMIX_DEMO_NABE_CHAR_SOOP_0,
		NMIX_DEMO_NABE_CHAR_SOOP_1,
		NMIX_DEMO_NABE_CHAR_SOOP_2,
	};
	static const u8 NabeObjPriTbl[] = {
		3,
		2,
		1,
		7,
		0,
		6,
		5,
		4,
	};
	static const u8 NabeObjMatX[] = {
		0,
		0,
		0,
		0,
		0,
		64,
		64,
		64,
	};
	static const u8 NabeObjMatY[] = {
		0,
		0,
		0,
		0,
		0,
		32,
		32,
		32,
	};
	
	GF_ASSERT( p_work->res_load == FALSE );
	// キャラクタデータ読み込み
	for( i=0; i<NMIX_DEMO_NABE_CHAR_NUM; i++ ){
		p_work->swsp_char[ i ] = NMix_Demo_SwspCharLoad( swsp_sys, NabeCharTbl[i], heapID );
	}
	// パレットデータ読み込み
	for( i=0; i<NMIX_DEMO_NABE_PLTT_NUM; i++ ){
		p_work->swsp_pltt[ i ] = NMix_Demo_SwspPlttLoad( swsp_sys, NabePlttTbl[i], heapID );
	}

	// オブジェクト登録
	for( i=0; i<NMIX_DEMO_NABE_OBJ_NUM; i++ ){
		p_work->swsp_obj[ i ] = NMix_Demo_SwspObjAdd( swsp_sys,
				p_work->swsp_char[ NabeObjCharTbl[ i ] ],
				p_work->swsp_pltt[ i ],
				NabeObjMatX[i], NabeObjMatY[i],
				NabeObjPriTbl[ i ] );
		// 中心座標
		SWSP_SetSpriteCenterPos( p_work->swsp_obj[ i ], 128 - NabeObjMatX[i], 96 - NabeObjMatY[i] );
	}

	p_work->res_load = TRUE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	リソース破棄
 *
 *	@param	p_work	ワーク
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_NabeGra_GraphicRelease( NMIX_DEMO_NABE_GRA* p_work )
{
	int i;

	GF_ASSERT( p_work->res_load == TRUE );

	for( i=0; i<NMIX_DEMO_NABE_OBJ_NUM; i++ ){
		// オブジェクト破棄
		SWSP_Delete( p_work->swsp_obj[ i ] );
	}
	
	// Vramから破棄
	for( i=0; i<NMIX_DEMO_NABE_CHAR_NUM; i++ ){
		SWSP_CharDelete( p_work->swsp_char[ i ] );
	}
	for( i=0; i<NMIX_DEMO_NABE_PLTT_NUM; i++ ){
		SWSP_PlttDelete( p_work->swsp_pltt[ i ] );
	}

	p_work->res_load = FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	オブジェクト表示ONOFF
 *
 *	@param	p_work	ワーク
 *	@param	obj_id	オブジェクトID
 *	@param	flg		フラグ
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_NabeGra_GraphicSetDrawFlg( NMIX_DEMO_NABE_GRA* p_work, u32 obj_id, BOOL flg )
{
	GF_ASSERT( obj_id < NMIX_DEMO_NABE_OBJ_NUM );
	SWSP_SetSpriteDraw( p_work->swsp_obj[ obj_id ], flg );
}

//----------------------------------------------------------------------------
/**
 *	@brief	オブジェクト表示ONOFF	取得
 *
 *	@param	p_work		ワーク
 *	@param	obj_id		オブジェクトID
 *
 *	@retval	TRUE	表示
 *	@retval	FALSE	非表示
 */
//-----------------------------------------------------------------------------
BOOL NMixGameDemo_NabeGra_GraphicGetDrawFlg( NMIX_DEMO_NABE_GRA* p_work, u32 obj_id )
{
	GF_ASSERT( obj_id < NMIX_DEMO_NABE_OBJ_NUM );
	return SWSP_GetSpriteDraw( p_work->swsp_obj[ obj_id ] );
}

//----------------------------------------------------------------------------
/**
 *	@brief	スープ回転角度の設定
 *
 *	@param	p_work		ワーク
 *	@param	rota		回転角度
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_NabeGra_GraphicSetSoopRota( NMIX_DEMO_NABE_GRA* p_work, u16 rota )
{
	int i;
	
	// スープ系全てのOBJに設定
	for( i=NMIX_DEMO_NABE_OBJ_SOOP_0; i<=NMIX_DEMO_NABE_OBJ_SOOP_2; i++ ){
		SWSP_SetSpriteRotZ( p_work->swsp_obj[ i ], rota );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	スープ　拡大率設定
 *
 *	@param	p_work		ワーク
 *	@param	scale		拡大率
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_NabeGra_GraphicSetSoopScale( NMIX_DEMO_NABE_GRA* p_work, fx32 scale )
{
	int i;
	// スープ系全てのOBJに設定
	for( i=NMIX_DEMO_NABE_OBJ_SOOP_0; i<=NMIX_DEMO_NABE_OBJ_SOOP_2; i++ ){
		SWSP_SetSpriteScale( p_work->swsp_obj[ i ], scale, scale );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	鍋グラふぃくα値設定
 *
 *	@param	p_work	ワーク
 *	@param	obj_id	オブジェクトID
 *	@param	alpha	α値
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_NabeGra_GraphicSetAlpha( NMIX_DEMO_NABE_GRA* p_work, u32 obj_id, u32 alpha )
{
	GF_ASSERT( obj_id < NMIX_DEMO_NABE_OBJ_NUM );
	SWSP_SetSpriteAlpha( p_work->swsp_obj[ obj_id ], alpha );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ファイヤーアニメ　開始
 *
 *	@param	p_work	ワーク
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_NabeGra_FireAnmStart( NMIX_DEMO_NABE_GRA* p_work )
{
	p_work->fire_anm_seq = 1;
	p_work->way_switch = 0;

	// 小さい値にする	
	NMIX_DEMO_MoveReqFx( &p_work->fire_anm,
			FX32_ONE,
			FireScaleMin[ 0 ],
			FireAnmSync[ 0 ] );
	
}

//----------------------------------------------------------------------------
/**
 *	@brief	ファイヤーアニメ　メイン
 *	
 *	@param	p_work	ワーク
 */
//-----------------------------------------------------------------------------	
void NMixGameDemo_NabeGra_FireAnm( NMIX_DEMO_NABE_GRA* p_work, int soop_type )
{
	BOOL result;
	int i;
	switch( p_work->fire_anm_seq ){
	case 0:
		// パラメータ初期化
		if( p_work->way_switch == 0 ){
			// 大きくなる
			NMIX_DEMO_MoveReqFx( &p_work->fire_anm,
					FireScaleMin[ soop_type ],
					FireScaleMax[ soop_type ],
					FireAnmSync[ soop_type ] );
		}else{
			// 小さくなる
			NMIX_DEMO_MoveReqFx( &p_work->fire_anm,
					FireScaleMax[ soop_type ],
					FireScaleMin[ soop_type ],
					FireAnmSync[ soop_type ] );
		}
		p_work->fire_anm_seq++;

	case 1:
		// １回動かす
		result = NMIX_DEMO_MoveMainFx( &p_work->fire_anm );
		// 火全てのOBJに設定
		for( i=NMIX_DEMO_NABE_OBJ_FIRE_0; i<=NMIX_DEMO_NABE_OBJ_FIRE_2; i++ ){
			SWSP_SetSpriteScale( p_work->swsp_obj[ i ], p_work->fire_anm.x, p_work->fire_anm.x );
		}
		if( result == TRUE ){
			p_work->fire_anm_seq = 0;
		}
		break;

	default:
		GF_ASSERT( 0 );
		break;
	}
}





//-----------------------------------------------------------------------------
/**
 *		他の人の位置　描画　管理システム
 */
//-----------------------------------------------------------------------------
#define NMIX_DEMO_OTHER_MARK_BG_PRI	( 2 )
//----------------------------------------------------------------------------
/**
 *	@brief	ワーク初期化
 *	@param	p_work 
 *	@param	cp_commdata		通信データ
 *	@param	comm_count		通信人数
 *	@param	p_comm_work		通信ワーク
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_OtherMark_Init( NMIX_DEMO_OTHER_MARK* p_work, const NUTMIX_GAME_COMM_PACK* cp_commdata, u32 comm_count, NUTMIX_COMMPACK_WORK* p_comm_work )
{
	memset( p_work, 0, sizeof(NMIX_DEMO_OTHER_MARK) );
	p_work->cp_commdata = cp_commdata;
	p_work->comm_count = comm_count;
	p_work->p_comm_work	= p_comm_work;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ワーク破棄
 *	
 *	@param	p_work	ワーク
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_OtherMark_Delete( NMIX_DEMO_OTHER_MARK* p_work )	
{
	// リソース破棄していない
	GF_ASSERT( p_work->res_load == FALSE );

	memset( p_work, 0, sizeof(NMIX_DEMO_OTHER_MARK) );
}

//----------------------------------------------------------------------------
/**
 *	@brief	グラフィック読み込み
 *
 *	@param	p_work			ワーク
 *	@param	p_clact			アクターシステム
 *	@param	p_def_oam_res	基本リソース
 *	@param	heapID			ヒープ
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_OtherMark_GraphicLoad( NMIX_DEMO_OTHER_MARK* p_work, NMIXGAME_CLACT_SYS* p_clact, NMIXGAME_CLACT_RES_WORK* p_def_oam_res, u32 heapID )
{
	int i;
	VecFx32 mat;
	
	mat.x = 128 * FX32_ONE;
	mat.y = 96 * FX32_ONE;
	
	for( i=0; i<NUTMIXER_MEMBER_MAX; i++ ){
		p_work->clact[i] = NMIXGAME_CLACT_Add( p_clact,
				&p_def_oam_res[ NMIX_GAME_DEF_OAM_RES_COMMON ], 
				128, 96,
				0, NMIX_DEMO_OTHER_MARK_BG_PRI, heapID );
		CLACT_SetDrawFlag( p_work->clact[i], FALSE );
		CLACT_AnmChg( p_work->clact[i], 4 + i );
		CLACT_SetMatrix( p_work->clact[i], &mat );
	}

	p_work->res_load = TRUE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	グラフィックリソース破棄
 *
 *	@param	p_work	ワーク
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_OtherMark_GraphicRelease( NMIX_DEMO_OTHER_MARK* p_work )
{
	int i;

	for( i=0; i<NUTMIXER_MEMBER_MAX; i++ ){
		CLACT_Delete( p_work->clact[i] );
	}

	p_work->res_load = FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	MARK位置調整
 *
 *	@param	p_work			ワーク
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_OtherMark_Main( NMIX_DEMO_OTHER_MARK* p_work )
{
	int i;
	int net_id;
	VecFx32 matrix;
	const NUTMIX_OYA* p_oya = &p_work->cp_commdata->get_game_data[ COMM_PARENT_ID ].oya;
	
	//	対応する位置に設置
	for( i=0; i<p_work->comm_count; i++ ){
		net_id = p_work->cp_commdata->playno_netid[ i ];
		matrix.x = p_oya->x[ net_id ] * FX32_ONE;
		matrix.y = p_oya->y[ net_id ] * FX32_ONE;
		CLACT_SetMatrix( p_work->clact[i], &matrix );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	描画フラグ設定
 *
 *	@param	p_work
 *	@param	flg 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_OtherMark_DrawFlag( NMIX_DEMO_OTHER_MARK* p_work, BOOL flg )
{
	int i;
	int net_id;
	
	// 自分のID以外のnetid 表示ON
	for( i=0; i<p_work->comm_count; i++ ){
		net_id = p_work->cp_commdata->playno_netid[ i ];
		if( NMIX_CommPack_CommGetCurrentID( p_work->p_comm_work ) != net_id ){
			CLACT_SetDrawFlag( p_work->clact[ i ], flg );
		}
	}
}



//-----------------------------------------------------------------------------
/**
 *		メイン画面　ビットマップウィンドウ
 */
//-----------------------------------------------------------------------------

#define NMIX_MAINWIN_FONT_COLOR		( 0 )		// 枠用カラーパレット
#define NMIX_MAINWIN_MENUFONT_COLOR		( 1 )		// 枠用カラーパレット
#define NMIX_MAINWIN_FONT_CG_OFS	( 1 )
#define NMIX_MAINWIN_SYSTEM_FONT_CG_OFS	( 1+TALK_WIN_CGX_SIZ )
#define NMIX_MAINWIN_STR_COLOR		( 2 )		// フォント用カラーパレット
#define NMIX_MAINWIN_SYSTEMSTR_COLOR		( 3 )		// フォント用カラーパレット
#define NMIX_MAINWIN_BMP_PRICOLOR		( GF_PRINTCOLOR_MAKE(1,2,15) )
#define NMIX_MAINWIN_BMP_SYSTEMPRICOLOR	( GF_PRINTCOLOR_MAKE(1,2,15) )

#define NMIX_MAINWIN_COMMBMP_X	( 10 )			// 文字面ビットマップsize
#define NMIX_MAINWIN_COMMBMP_Y	( 11 )			// 文字面ビットマップsize
#define NMIX_MAINWIN_COMMBMP_CX	( 16 )			// 文字面ビットマップsize
#define NMIX_MAINWIN_COMMBMP_CY	( 4 )			// 文字面ビットマップsize
#define NMIX_MAINWIN_COMMBMP_COFS ( NMIX_MAINWIN_SYSTEM_FONT_CG_OFS+MENU_WIN_CGX_SIZ )			// キャラクタオフセット

#define NMIX_MAINWIN_RESULT0_BMP_X	( 2 )			// 文字面ビットマップsize
#define NMIX_MAINWIN_RESULT0_BMP_Y	( 1 )			// 文字面ビットマップsize
#define NMIX_MAINWIN_RESULT0_BMP_CX	( 28 )			// 文字面ビットマップsize
#define NMIX_MAINWIN_RESULT0_BMP_CY	( 15 )			// 文字面ビットマップsize
#define NMIX_MAINWIN_RESULT0_BMP_COFS ( NMIX_MAINWIN_SYSTEM_FONT_CG_OFS+MENU_WIN_CGX_SIZ )			// キャラクタオフセット

#define NMIX_MAINWIN_RESULT1_BMP_X	( 2 )			// 文字面ビットマップsize
#define NMIX_MAINWIN_RESULT1_BMP_Y	( 18 )			// 文字面ビットマップsize
#define NMIX_MAINWIN_RESULT1_BMP_CX	( 28 )			// 文字面ビットマップsize
#define NMIX_MAINWIN_RESULT1_BMP_CY	( 5 )			// 文字面ビットマップsize
#define NMIX_MAINWIN_RESULT1_BMP_COFS ( NMIX_MAINWIN_RESULT0_BMP_COFS+ (NMIX_MAINWIN_RESULT0_BMP_CX * NMIX_MAINWIN_RESULT0_BMP_CY) )			// キャラクタオフセット


// 結果表示位置
#define NMIX_MAINWIN_RESULT_TITLE_X	( 56 )		// 全体タイトル
#define NMIX_MAINWIN_RESULT_TITLE_Y	( 0 )		// 全体タイトル
#define NMIX_MAINWIN_RESULT_PORUTO_TITLE_X	( 0 )	// ポルトタイトル
#define NMIX_MAINWIN_RESULT_PORUTO_TITLE_Y	( 0 )	// ポルトタイトル
#define NMIX_MAINWIN_RESULT_NEMU_TITLE_X	( 0 )	// メニュータイトル
#define NMIX_MAINWIN_RESULT_NEMU_NUM_X		( 160 )	// メニュー値

#define NMIX_MAINWIN_RESULT_COOKTIME_KETA	( 2 )	// 調理時間桁
#define NMIX_MAINWIN_RESULT_KOBOSI_KETA	( 4 )		// こぼし
#define NMIX_MAINWIN_RESULT_KOGASI_KETA	( 4 )		// こげ
#define NMIX_MAINWIN_RESULT_TEAMWORK_KETA	( 4 )		// チームワーク
#define NMIX_MAINWIN_RESULT_COOKTIME_TITLE_Y	( 24 )	// 調理時間タイトル
#define NMIX_MAINWIN_RESULT_KOBOSI_TITLE_Y	( 48 )	// こぼした回数
#define NMIX_MAINWIN_RESULT_KOGASI_TITLE_Y	( 68 )	// こがした回数
#define NMIX_MAINWIN_RESULT_TEAMWORK_TITLE_Y ( 88 )// TEAMWORK点数

#define NMIX_MAINWIN_RESULT_PORUTO_KETA		( 2 )	//ポルトデータ桁
#define NMIX_MAINWIN_RESULT_PORUTO_NUM_X	( 16 )	// ポルトデータ
#define NMIX_MAINWIN_RESULT_PORUTO_NUM_Y	( 24 )	//ポルトデータ

#define NMIX_MAINWIN_COMMBACK_COLOR	( 4 )

// テキスト表示面処理
#define NMIX_MAINWIN_TEXT_BMP_X		( 2 )
#define NMIX_MAINWIN_TEXT_BMP_Y		( 2 )
#define NMIX_MAINWIN_TEXT_BMP_CX	( 27 )
#define NMIX_MAINWIN_TEXT_BMP_CY	( 5 )
#define NMIX_MAINWIN_TEXT_BMP_COFS ( NMIX_MAINWIN_SYSTEM_FONT_CG_OFS+MENU_WIN_CGX_SIZ )			// キャラクタオフセット


// ここにかいちゃう
// YESNOウィンドウ
#define NMIX_MAINWIN_YESNO_WND_X		( 24 )
#define NMIX_MAINWIN_YESNO_WND_Y		( 8 )
#define NMIX_MAINWIN_YESNO_BMP_COFS ( NMIX_MAINWIN_TEXT_BMP_COFS + (NMIX_MAINWIN_TEXT_BMP_CX * NMIX_MAINWIN_TEXT_BMP_CY) )			// キャラクタオフセット
#define NMIX_MAINWIN_YESNO_PLT			( 5 )
 
// エフェクト
#define NMIX_MAINWIN_COMM_EFF_DRAW_TIME	( 30 )	
#define NMIX_MAINWIN_COMM_EFF_TCB_PRI	( 1024 )


static void NMixMainWin_BmpInit( NMIX_DEMO_MAIN_WIN* p_work, u32 heapID );
static void NMixMainWin_BmpRelease( NMIX_DEMO_MAIN_WIN* p_work );
static void NMixMainWin_BackGroundInit( NMIX_DEMO_MAIN_WIN* p_work, u32 heapID );
//----------------------------------------------------------------------------
/**
 *	@brief	メインウィンドウ　初期化
 *
 *	@param	p_work			ワーク
 *	@param	comm_coun		通信相手数
 *	@param	p_msg_data		メッセージデータ
 *	@param	p_comm_data		通信データ
 *	@param	wnd_type		ウィンドウタイプ
 *	@param	heapID			ヒープ
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_MainWin_Init( NMIX_DEMO_MAIN_WIN* p_work, int comm_count, NMIXER_MSG* p_msg_data, NUTMIX_GAME_COMM_PACK* p_comm_data, int wnd_type, u32 heapID )
{
	memset( p_work, 0, sizeof(NMIX_DEMO_MAIN_WIN) );
	p_work->p_msg_data = p_msg_data;
	p_work->comm_count = comm_count;
	p_work->heapID = heapID;
	p_work->p_comm_data = p_comm_data;
	p_work->wnd_type = wnd_type;
}

//----------------------------------------------------------------------------
/**
 *	@brief	メインウィンドウ破棄
 *
 *	@param	p_work	ワーク
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_MainWin_Delete( NMIX_DEMO_MAIN_WIN* p_work )
{
	// リソース破棄していません
	GF_ASSERT( p_work->res_load == FALSE );

	// タスク破棄
	NMixGameDemo_StopComment( p_work );

	
	memset( p_work, 0, sizeof(NMIX_DEMO_MAIN_WIN) );
}

//----------------------------------------------------------------------------
/**
 *	@brief	メイン画面　BGリソース読み込み
 *	
 *	@param	p_work		ワーク
 *	@param	p_bgl		BGL
 *	@param	heapID		ヒープID
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_MainWin_GraphicLoad( NMIX_DEMO_MAIN_WIN* p_work, GF_BGL_INI* p_bgl, u32 heapID )
{
	GF_ASSERT( p_work->res_load == FALSE );

	// BGL設定
	p_work->p_bgl = p_bgl;
	
	// ビットマップウィンドウ初期化
	NMixMainWin_BmpInit( p_work, heapID );

	// 背景設定
	NMixMainWin_BackGroundInit( p_work, heapID );

	// 非表示にする
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG1, VISIBLE_OFF );
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_OFF );

	p_work->res_load = TRUE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	メイン画面BG　リソース破棄
 *
 *	@param	p_work	ワーク
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_MainWin_GraphicRelease( NMIX_DEMO_MAIN_WIN* p_work )
{
	GF_ASSERT( p_work->res_load == TRUE );
	
	// ビットマップウィンドウ破棄
	NMixMainWin_BmpRelease( p_work );

	p_work->res_load = FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ビットマップウィンドウ初期化
 */
//-----------------------------------------------------------------------------
static void NMixMainWin_BmpInit( NMIX_DEMO_MAIN_WIN* p_work, u32 heapID )
{
	int i;
	static u16 bitmap_param[ NMIX_DEMO_MAINWIN_NUM ][ 6 ] = {
		{ 
			NMIX_MAINWIN_COMMBMP_X,
			NMIX_MAINWIN_COMMBMP_Y,
			NMIX_MAINWIN_COMMBMP_CX,
			NMIX_MAINWIN_COMMBMP_CY,
			NMIX_MAINWIN_STR_COLOR,
			NMIX_MAINWIN_COMMBMP_COFS,
		},
		{
			NMIX_MAINWIN_RESULT0_BMP_X,
			NMIX_MAINWIN_RESULT0_BMP_Y,
			NMIX_MAINWIN_RESULT0_BMP_CX,
			NMIX_MAINWIN_RESULT0_BMP_CY,
			NMIX_MAINWIN_SYSTEMSTR_COLOR,
			NMIX_MAINWIN_RESULT0_BMP_COFS,
		},
		{
			NMIX_MAINWIN_RESULT1_BMP_X,
			NMIX_MAINWIN_RESULT1_BMP_Y,
			NMIX_MAINWIN_RESULT1_BMP_CX,
			NMIX_MAINWIN_RESULT1_BMP_CY,
			NMIX_MAINWIN_SYSTEMSTR_COLOR,
			NMIX_MAINWIN_RESULT1_BMP_COFS,
		},
		{
			NMIX_MAINWIN_TEXT_BMP_X,
			NMIX_MAINWIN_TEXT_BMP_Y,
			NMIX_MAINWIN_TEXT_BMP_CX,
			NMIX_MAINWIN_TEXT_BMP_CY,
			NMIX_MAINWIN_STR_COLOR,
			NMIX_MAINWIN_TEXT_BMP_COFS,
		},
	};

	// 枠の絵など読み込み
	// 会話枠
	TalkWinGraphicSet( p_work->p_bgl, GF_BGL_FRAME2_M,
			NMIX_MAINWIN_FONT_CG_OFS,
			NMIX_MAINWIN_FONT_COLOR,
			p_work->wnd_type, heapID );
	// 会話フォントパレット読み込み
	TalkFontPaletteLoad( PALTYPE_MAIN_BG, 
			NMIX_MAINWIN_STR_COLOR * 32, heapID );

	// メニュー枠
	MenuWinGraphicSet( p_work->p_bgl, GF_BGL_FRAME2_M,
			NMIX_MAINWIN_SYSTEM_FONT_CG_OFS,
			NMIX_MAINWIN_MENUFONT_COLOR,
			MENU_TYPE_SYSTEM, heapID );
	// システムフォントパレット読み込み
	SystemFontPaletteLoad( PALTYPE_MAIN_BG, 
			NMIX_MAINWIN_SYSTEMSTR_COLOR * 32, heapID );
	
	// ビットマップウィンドウメモリ確保
	for( i=0; i<NMIX_DEMO_MAINWIN_NUM; i++ ){
		p_work->p_bmp[i] = GF_BGL_BmpWinAllocGet( heapID, 1 );

		GF_BGL_BmpWinAdd( p_work->p_bgl, p_work->p_bmp[i],
				GF_BGL_FRAME2_M,
				bitmap_param[i][0],
				bitmap_param[i][1],
				bitmap_param[i][2],
				bitmap_param[i][3],
				bitmap_param[i][4],
				bitmap_param[i][5] );

		GF_BGL_BmpWinDataFill( p_work->p_bmp[i], 0 );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	ビットマップウィンドウ破棄
 */
//-----------------------------------------------------------------------------
static void NMixMainWin_BmpRelease( NMIX_DEMO_MAIN_WIN* p_work )
{
	int i;

	for( i=0; i<NMIX_DEMO_MAINWIN_NUM; i++ ){
		GF_BGL_BmpWinDel( p_work->p_bmp[i] );
		GF_BGL_BmpWinFree( p_work->p_bmp[i], 1 );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief		背景初期化
 */
//-----------------------------------------------------------------------------
static void NMixMainWin_BackGroundInit( NMIX_DEMO_MAIN_WIN* p_work, u32 heapID )
{
	void* buff;
	NNSG2dScreenData* p_scrn;
	
	// 背景設定
	ArcUtil_PalSet( ARC_NUTMIXER_GRA, NARC_nutmixer_cook_s_window_NCLR, 
			PALTYPE_MAIN_BG, NMIX_MAINWIN_COMMBACK_COLOR*32,
			1*32, heapID );
	ArcUtil_BgCharSet( ARC_NUTMIXER_GRA, NARC_nutmixer_cook_s_window_NCGR,
			p_work->p_bgl, GF_BGL_FRAME1_M, 0, 0, FALSE, heapID );

	buff = ArcUtil_ScrnDataGet( ARC_NUTMIXER_GRA, 
			NARC_nutmixer_cook_s_window_NSCR, FALSE, &p_scrn, heapID );
	
	// スクリーンデータ書き込み
	GF_BGL_ScrWrite( p_work->p_bgl, GF_BGL_FRAME1_M,
			p_scrn->rawData, 0, 0,
			p_scrn->screenWidth / 8,
			p_scrn->screenHeight / 8 );

	// パレットをあわせる
	GF_BGL_ScrPalChange( p_work->p_bgl, GF_BGL_FRAME1_M,
			0, 0, 
			p_scrn->screenWidth / 8,
			p_scrn->screenHeight / 8,
			NMIX_MAINWIN_COMMBACK_COLOR );

	sys_FreeMemoryEz( buff );

	// スクリーンデータ転送
	GF_BGL_LoadScreenV_Req( p_work->p_bgl, GF_BGL_FRAME1_M );
}



//----------------------------------------------------------------------------
/**
 *	@brief	終了メッセージ表示
 *
 *	@param	p_work	ワーク
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_EndMsgPirntOn( NMIX_DEMO_MAIN_WIN* p_work )
{
	// 文字列描画
	GF_BGL_BmpWinDataFill( p_work->p_bmp[NMIX_DEMO_MAINWIN_COMME], 0 );

	// 文字列描画
	GF_STR_PrintColor( p_work->p_bmp[NMIX_DEMO_MAINWIN_COMME],
			FONT_TALK, p_work->p_msg_data->end, 0, 0, 0,
			NMIX_MAINWIN_BMP_PRICOLOR, NULL );
	// 転送
	GF_BGL_BmpWinOn( p_work->p_bmp[NMIX_DEMO_MAINWIN_COMME] );

	// 表示設定
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG1, VISIBLE_ON );
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_ON );
}

//----------------------------------------------------------------------------
/**
 *	@brief	終了メッセージ非表示
 *
 *	@param	p_work	ワーク
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_EndMsgPrintOff( NMIX_DEMO_MAIN_WIN* p_work )
{
	// 非表示にして終わる
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG1, VISIBLE_OFF );
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_OFF );

	// 転送
	GF_BGL_BmpWinOff( p_work->p_bmp[NMIX_DEMO_MAINWIN_COMME] );
}


//----------------------------------------------------------------------------
/**	
 *	@brief	エフェクトメインタスク
 */
//-----------------------------------------------------------------------------
static void NMixGameDemo_MainComment( TCB_PTR tcb, void* p_work )
{
	NMIX_DEMO_MAIN_WIN* p_demo = p_work;
	
	p_demo->move_count ++;
	
	if( p_demo->move_count >= NMIX_MAINWIN_COMM_EFF_DRAW_TIME ){
		// 非表示にして終わる
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG1, VISIBLE_OFF );
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_OFF );
		TCB_Delete( tcb );
		p_demo->move_tcb = NULL;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	コメント描画エフェクト開始
 *
 *	@param	p_work		ワーク
 *	@param	comm_type	コメントタイプ
 *
 *	comm_type
		NMIX_STMSG_SPEED_KOGERU00,
		NMIX_STMSG_SPEED_HAYAI00,
		NMIX_STMSG_SPEED_KOGERU01,
		NMIX_STMSG_SPEED_HAYAI01,
		NMIX_STMSG_SPEED_KOGERU02,
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_StartComment( NMIX_DEMO_MAIN_WIN* p_work, u32 comm_type )
{
	// 表示中でないかチェック
	GF_ASSERT( p_work->move_tcb == NULL );

	p_work->move_tcb = TCB_Add( NMixGameDemo_MainComment, p_work, NMIX_MAINWIN_COMM_EFF_TCB_PRI );
	p_work->move_count = 0;


	// 文字列描画
	GF_BGL_BmpWinDataFill( p_work->p_bmp[NMIX_DEMO_MAINWIN_COMME], 0 );

	// 文字列描画
	GF_STR_PrintColor( p_work->p_bmp[NMIX_DEMO_MAINWIN_COMME],
			FONT_TALK, p_work->p_msg_data->spd[ comm_type ], 0, 0, 0,
			NMIX_MAINWIN_BMP_PRICOLOR, NULL );
	// 転送
	GF_BGL_BmpWinOn( p_work->p_bmp[NMIX_DEMO_MAINWIN_COMME] );

	// 表示設定
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG1, VISIBLE_ON );
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_ON );
}

//----------------------------------------------------------------------------
/**
 *	@brief	終了チェック
 *	
 *	@param	cp_work 
 *
 *	@retval	TRUE	終了
 *	@retval	FALSE	途中
 */
//-----------------------------------------------------------------------------
BOOL NMixGameDemo_EndCheckComment( const NMIX_DEMO_MAIN_WIN* cp_work )
{
	if( cp_work->move_tcb == NULL ){
		return TRUE;
	}
	return FALSE;
}
	
//----------------------------------------------------------------------------
/**
 *	@brief	コメントエフェクト　停止
 *
 *	@param	p_work	ワーク
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_StopComment( NMIX_DEMO_MAIN_WIN* p_work )
{
	if( p_work->move_tcb == NULL ){
		return ;
	}
	// 非表示にして終わる
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG1, VISIBLE_OFF );
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_OFF );
	
	TCB_Delete( p_work->move_tcb );
	p_work->move_tcb = NULL;
}

// シーン0
static void NMixGameDemo_MainWin_ResultSeen0( NMIX_DEMO_MAIN_WIN* p_work )
{
	// メッセージスクリーンをクリーン
	GF_BGL_ScrClear( p_work->p_bgl, GF_BGL_FRAME2_M );
	
	// 文字列描画
	GF_BGL_BmpWinDataFill( p_work->p_bmp[NMIX_DEMO_MAINWIN_RESULT_MAIN], 15 );

	// 結果発表
	GF_STR_PrintColor( p_work->p_bmp[NMIX_DEMO_MAINWIN_RESULT_MAIN],
			FONT_SYSTEM, p_work->p_msg_data->result, 
			NMIX_MAINWIN_RESULT_TITLE_X, NMIX_MAINWIN_RESULT_TITLE_Y,
			0,
			NMIX_MAINWIN_BMP_SYSTEMPRICOLOR, NULL );

	// 枠の描画
	BmpMenuWinWrite( p_work->p_bmp[NMIX_DEMO_MAINWIN_RESULT_MAIN], WINDOW_TRANS_ON, NMIX_MAINWIN_SYSTEM_FONT_CG_OFS, NMIX_MAINWIN_MENUFONT_COLOR );

	// ちっちゃいウィンドウ
	GF_BGL_BmpWinDataFill( p_work->p_bmp[NMIX_DEMO_MAINWIN_RESULT_SUB], 15 );

	// 出来たポロック
	GF_STR_PrintColor( p_work->p_bmp[NMIX_DEMO_MAINWIN_RESULT_SUB],
			FONT_SYSTEM, p_work->p_msg_data->res[ NMIX_STMSG_RESULT_PORUTO_TI ], 
			NMIX_MAINWIN_RESULT_PORUTO_TITLE_X, NMIX_MAINWIN_RESULT_PORUTO_TITLE_Y,
			0,
			NMIX_MAINWIN_BMP_SYSTEMPRICOLOR, NULL );

	// 枠の描画
	BmpMenuWinWrite( p_work->p_bmp[NMIX_DEMO_MAINWIN_RESULT_SUB], WINDOW_TRANS_ON, NMIX_MAINWIN_SYSTEM_FONT_CG_OFS, NMIX_MAINWIN_MENUFONT_COLOR );

	// 表示
	GF_BGL_BmpWinOnVReq( p_work->p_bmp[NMIX_DEMO_MAINWIN_RESULT_MAIN] );
	GF_BGL_BmpWinOnVReq( p_work->p_bmp[NMIX_DEMO_MAINWIN_RESULT_SUB] );
}

#ifdef PM_DEBUG
extern u32 D_Tomoya_MazeMaze_TeamWork;
#endif

// シーン1
static void NMixGameDemo_MainWin_ResultSeen1( NMIX_DEMO_MAIN_WIN* p_work )
{
	// 調理時間
	GF_STR_PrintColor( p_work->p_bmp[NMIX_DEMO_MAINWIN_RESULT_MAIN],
			FONT_SYSTEM, p_work->p_msg_data->res[ NMIX_STMSG_RESULT_COOK_TIME_TI ], 
			NMIX_MAINWIN_RESULT_NEMU_TITLE_X, NMIX_MAINWIN_RESULT_COOKTIME_TITLE_Y,
			0,
			NMIX_MAINWIN_BMP_SYSTEMPRICOLOR, NULL );

	// 実際の時間
	WORDSET_RegisterNumber( p_work->p_msg_data->wset, 0, 
			p_work->p_comm_data->get_result_data.min,
			NMIX_MAINWIN_RESULT_COOKTIME_KETA, 
			NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT );	// 分
	WORDSET_RegisterNumber( p_work->p_msg_data->wset, 1, 
			p_work->p_comm_data->get_result_data.second,
			NMIX_MAINWIN_RESULT_COOKTIME_KETA, 
			NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT );	// 秒
	WORDSET_RegisterNumber( p_work->p_msg_data->wset, 2,
			p_work->p_comm_data->get_result_data.dec,
			NMIX_MAINWIN_RESULT_COOKTIME_KETA, 
			NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT );	// コンマ
	WORDSET_ExpandStr( p_work->p_msg_data->wset, p_work->p_msg_data->tmp, p_work->p_msg_data->res[NMIX_STMSG_RESULT_COOK_TIME] );	// 展開
	
	GF_STR_PrintColor( p_work->p_bmp[NMIX_DEMO_MAINWIN_RESULT_MAIN],
			FONT_SYSTEM, p_work->p_msg_data->tmp, 
			NMIX_MAINWIN_RESULT_NEMU_NUM_X,
			NMIX_MAINWIN_RESULT_COOKTIME_TITLE_Y,
			0, NMIX_MAINWIN_BMP_SYSTEMPRICOLOR, NULL );

	// こぼした回数
	GF_STR_PrintColor( p_work->p_bmp[NMIX_DEMO_MAINWIN_RESULT_MAIN],
			FONT_SYSTEM, p_work->p_msg_data->res[ NMIX_STMSG_RESULT_KOBOSI_NUM_TI ], 
			NMIX_MAINWIN_RESULT_NEMU_TITLE_X, NMIX_MAINWIN_RESULT_KOBOSI_TITLE_Y,
			0,
			NMIX_MAINWIN_BMP_SYSTEMPRICOLOR, NULL );
	
	// 実際の回数
	WORDSET_RegisterNumber( p_work->p_msg_data->wset, 0, 
			p_work->p_comm_data->get_result_data.kobore_num,
			NMIX_MAINWIN_RESULT_KOBOSI_KETA,
			NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );

	WORDSET_ExpandStr( p_work->p_msg_data->wset, p_work->p_msg_data->tmp, p_work->p_msg_data->res[NMIX_STMSG_RESULT_KOBOSI_NUM] );	// 展開
	
	GF_STR_PrintColor( p_work->p_bmp[NMIX_DEMO_MAINWIN_RESULT_MAIN],
			FONT_SYSTEM, p_work->p_msg_data->tmp, 
			NMIX_MAINWIN_RESULT_NEMU_NUM_X,
			NMIX_MAINWIN_RESULT_KOBOSI_TITLE_Y,
			0, NMIX_MAINWIN_BMP_SYSTEMPRICOLOR, NULL );

	// 焦がした回数
	GF_STR_PrintColor( p_work->p_bmp[NMIX_DEMO_MAINWIN_RESULT_MAIN],
			FONT_SYSTEM, p_work->p_msg_data->res[ NMIX_STMSG_RESULT_KOGASI_NUM_TI ], 
			NMIX_MAINWIN_RESULT_NEMU_TITLE_X, 
			NMIX_MAINWIN_RESULT_KOGASI_TITLE_Y,
			0,
			NMIX_MAINWIN_BMP_SYSTEMPRICOLOR, NULL );
	
	// 実際の回数
	WORDSET_RegisterNumber( p_work->p_msg_data->wset, 0,
			p_work->p_comm_data->get_result_data.kogasi_num, 
			NMIX_MAINWIN_RESULT_KOGASI_KETA,
			NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );

	WORDSET_ExpandStr( p_work->p_msg_data->wset, p_work->p_msg_data->tmp, p_work->p_msg_data->res[NMIX_STMSG_RESULT_KOGASI_NUM] );	// 展開
	
	GF_STR_PrintColor( p_work->p_bmp[NMIX_DEMO_MAINWIN_RESULT_MAIN],
			FONT_SYSTEM, p_work->p_msg_data->tmp, 
			NMIX_MAINWIN_RESULT_NEMU_NUM_X,
			NMIX_MAINWIN_RESULT_KOGASI_TITLE_Y,
			0, NMIX_MAINWIN_BMP_SYSTEMPRICOLOR, NULL );

	// もし複数人数でやっていたらTEAMWORK点を表示
#ifdef PM_DEBUG
	D_Tomoya_MazeMaze_TeamWork = p_work->p_comm_data->get_result_data.match_num;
#endif
/*	if( p_work->comm_count > 1 ){
		// TEAMWORK点数
		GF_STR_PrintColor( p_work->p_bmp[NMIX_DEMO_MAINWIN_RESULT_MAIN],
				FONT_SYSTEM, p_work->p_msg_data->res[ NMIX_STMSG_RESULT_TEAMWORK_TI ], 
				NMIX_MAINWIN_RESULT_NEMU_TITLE_X, 
				NMIX_MAINWIN_RESULT_TEAMWORK_TITLE_Y,
				0,
				NMIX_MAINWIN_BMP_SYSTEMPRICOLOR, NULL );
		
		// 実際の回数
		WORDSET_RegisterNumber( p_work->p_msg_data->wset, 0,
				p_work->p_comm_data->get_result_data.match_num,
				NMIX_MAINWIN_RESULT_TEAMWORK_KETA,
				NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );

		WORDSET_ExpandStr( p_work->p_msg_data->wset, p_work->p_msg_data->tmp, p_work->p_msg_data->res[NMIX_STMSG_RESULT_TEAMWORK] );	// 展開
		
		GF_STR_PrintColor( p_work->p_bmp[NMIX_DEMO_MAINWIN_RESULT_MAIN],
				FONT_SYSTEM, p_work->p_msg_data->tmp, 
				NMIX_MAINWIN_RESULT_NEMU_NUM_X,
				NMIX_MAINWIN_RESULT_TEAMWORK_TITLE_Y,
				0, NMIX_MAINWIN_BMP_SYSTEMPRICOLOR, NULL );
	}//*/
	
	// 表示
	GF_BGL_BmpWinOnVReq( p_work->p_bmp[NMIX_DEMO_MAINWIN_RESULT_MAIN] );
}

// シーン2
static void NMixGameDemo_MainWin_ResultSeen2( NMIX_DEMO_MAIN_WIN* p_work )
{
	// ポロック名	レベル 個数
	WORDSET_RegisterPorutoName( p_work->p_msg_data->wset, 3, 
			p_work->p_comm_data->get_result_data.poruto_type );	
	WORDSET_RegisterNumber( p_work->p_msg_data->wset, 1,
			p_work->p_comm_data->get_result_data.poruto_lv,
			NMIX_MAINWIN_RESULT_PORUTO_KETA,
			NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT );

	WORDSET_RegisterNumber( p_work->p_msg_data->wset, 2,
			p_work->comm_count,
			NMIX_MAINWIN_RESULT_PORUTO_KETA,
			NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT );

#ifdef NMIX_DEBUG_DUMMY_RESULT_ON
	if( sys.cont & PAD_BUTTON_A ){
		WORDSET_RegisterNumber( p_work->p_msg_data->wset, 2,
				99,
				NMIX_MAINWIN_RESULT_PORUTO_KETA,
				NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT );
	}
#endif

	WORDSET_ExpandStr( p_work->p_msg_data->wset, p_work->p_msg_data->tmp, p_work->p_msg_data->res[NMIX_STMSG_RESULT_PORUTO] );	// 展開

	GF_STR_PrintColor( p_work->p_bmp[NMIX_DEMO_MAINWIN_RESULT_SUB],
			FONT_SYSTEM, p_work->p_msg_data->tmp, 
			NMIX_MAINWIN_RESULT_PORUTO_NUM_X, 
			NMIX_MAINWIN_RESULT_PORUTO_NUM_Y,
			0,
			NMIX_MAINWIN_BMP_SYSTEMPRICOLOR, NULL );
	
	// 表示
	GF_BGL_BmpWinOnVReq( p_work->p_bmp[NMIX_DEMO_MAINWIN_RESULT_SUB] );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ゲーム結果表示
 *
 *	@param	p_work		ワーク
 *	@param	seen		シーン
		NMIX_DEMO_MINWIN_RESULT_SEEN0,
		NMIX_DEMO_MINWIN_RESULT_SEEN1,
		NMIX_DEMO_MINWIN_RESULT_SEEN2,
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_ResultOn( NMIX_DEMO_MAIN_WIN* p_work, u32 seen )
{

	switch( seen ){
	case NMIX_DEMO_MINWIN_RESULT_SEEN0:
		NMixGameDemo_MainWin_ResultSeen0( p_work );
		break;
		
	case NMIX_DEMO_MINWIN_RESULT_SEEN1:
		NMixGameDemo_MainWin_ResultSeen1( p_work );
		break;
		
	case NMIX_DEMO_MINWIN_RESULT_SEEN2:
		NMixGameDemo_MainWin_ResultSeen2( p_work );
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	結果表示をoff
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_ResultOff( NMIX_DEMO_MAIN_WIN* p_work )
{
	// メッセージスクリーンをクリーン
	GF_BGL_ScrClear( p_work->p_bgl, GF_BGL_FRAME2_M );
	
	// 表示
	GF_BGL_BmpWinOff( p_work->p_bmp[NMIX_DEMO_MAINWIN_RESULT_MAIN] );
	GF_BGL_BmpWinOff( p_work->p_bmp[NMIX_DEMO_MAINWIN_RESULT_SUB] );
}


//----------------------------------------------------------------------------
/**
 *	@brief	テキスト表示
 *
 *	@param	p_work		ワーク
 *	@param	text_no		テキストタイプ
			NMIX_DEMO_MAINWIN_TEXT_SAVE_PORUTO,
			NMIX_DEMO_MAINWIN_TEXT_HIKITUDUKI,
			NMIX_DEMO_MAINWIN_TEXT_PORUTO_IPPAI,
			NMIX_DEMO_MAINWIN_TEXT_BAG,
			NMIX_DEMO_MAINWIN_TEXT_TUGOUWARU,
			NMIX_DEMO_MAINWIN_TEXT_NUTS_NONE,
			NMIX_DEMO_MAINWIN_TEXT_TUUSHIN_TAIKI
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_TextOn( NMIX_DEMO_MAIN_WIN* p_work, u32 text_no )
{
	STRBUF* str;
	int my_netid;
	
	GF_BGL_BmpWinDataFill( p_work->p_bmp[NMIX_DEMO_MAINWIN_TEXT], 15 );

	switch( text_no ){
	case NMIX_DEMO_MAINWIN_TEXT_SAVE_PORUTO:
		WORDSET_RegisterPlayerName( p_work->p_msg_data->wset, 0,
				 p_work->p_comm_data->p_mystate[ p_work->p_comm_data->my_netid ] );
		WORDSET_ExpandStr( p_work->p_msg_data->wset, p_work->p_msg_data->tmp, p_work->p_msg_data->casein );	// 展開
		str = p_work->p_msg_data->tmp;
		break;
		
	case NMIX_DEMO_MAINWIN_TEXT_HIKITUDUKI:
		str = p_work->p_msg_data->replay;
		break;
		
	case NMIX_DEMO_MAINWIN_TEXT_PORUTO_IPPAI:
		str = p_work->p_msg_data->poruto_ippai;
		break;
		
	case NMIX_DEMO_MAINWIN_TEXT_BAG:
		str = p_work->p_msg_data->bag_erabu;
		break;
		
	case NMIX_DEMO_MAINWIN_TEXT_TUGOUWARU:
		str = p_work->p_msg_data->exit;
		break;
		
	case NMIX_DEMO_MAINWIN_TEXT_NUTS_NONE:
		str = p_work->p_msg_data->nuts_none;
		break;

	case NMIX_DEMO_MAINWIN_TEXT_TUUSHIN_TAIKI:
		str = p_work->p_msg_data->wait;
		break;
	}
	
	// 文字の表示
	GF_STR_PrintColor( p_work->p_bmp[NMIX_DEMO_MAINWIN_TEXT],
			FONT_TALK, str, 
			0, 0, 0,
			NMIX_MAINWIN_BMP_PRICOLOR, NULL );

	// 枠の描画
	BmpTalkWinWrite( p_work->p_bmp[NMIX_DEMO_MAINWIN_TEXT], WINDOW_TRANS_ON, NMIX_MAINWIN_FONT_CG_OFS, NMIX_MAINWIN_FONT_COLOR );
	
	// 表示
	GF_BGL_BmpWinOnVReq( p_work->p_bmp[NMIX_DEMO_MAINWIN_TEXT] );
}



//-----------------------------------------------------------------------------
/**
 *		スープエフェクト管理
 */
//-----------------------------------------------------------------------------
enum{
	NMIX_DEMO_SOOP_EFF_MOVETYPE_ANM_END,	// アニメが終わり次第消える
	NMIX_DEMO_SOOP_EFF_MOVETYPE_ENDREQ,		// 終了リクエストをもらって消える
	NMIX_DEMO_SOOP_EFF_MOVETYPE_NUM
};

//-------------------------------------
//	動さパラメータ
//=====================================
typedef struct {
	fx32 rnd_scale_min;	// 拡縮最小
	fx32 rnd_scale_max;	// 拡縮最大
	fx32 rnd_scale_ss;	// 拡縮初速度
	fx32 move_ss;		// 初速度
	u8 rnd_dis_s_min;	// 動さ開始最小
	u8 rnd_dis_s_max;	// 動さ開始最大
	u8 rnd_dis_min;		// 動さ距離最小
	u8 rnd_dis_max;		// 動さ距離最大
	u8 move_sync;		// 動さシンク数
	u8 res_id;			// デフォルトリソース何番目か
	u8 res_anm;			// アニメーション何番目か
	u8 move_type;		// 動さタイプ

	u8 scale_use;		// 拡縮使用フラグ
	u8 soop_move;		// スープ動さ
	u8 pri;				// priority
} NMIX_DEMO_SOOP_EFF_PARAM;

// 動さパラメータ
// 最後のスープタイプには、こぼれるがないので-1しています
#define EFF_SOOP_DATA_NUM	( (NMIX_SOOPTYPE_SOOP_NUM*3) - 1 )	// データすう
static const NMIX_DEMO_SOOP_EFF_PARAM EffSoopMoveParam[ EFF_SOOP_DATA_NUM ] = {
	{	// スープ形態0	煙
		FX32_CONST(0.50f),	// 乱数で求める拡大値最小
		FX32_CONST(1.50f),	// 乱数で求める拡大値最大
		FX32_CONST(0.0f),	// 拡大初速度
		FX32_CONST(0.0f),	// 動さ初速度
		32,					// 開始距離最小
		64,					// 開始距離最大
		0,					// 動さ距離最小
		0,					// 動さ距離最大
		32,					// 動さシンク
		NMIX_GAME_DEF_OAM_RES_SOUP,	// リソース何番目か
		1,						// アニメナンバー
		NMIX_DEMO_SOOP_EFF_MOVETYPE_ANM_END,// 動さタイプ
		FALSE,				// 拡縮使用フラグ
		FALSE,				// スープと同期して動くか
		5,					// ソフト優先順位
	},
	{	// スープ形態0	こげる
		FX32_CONST(0.50f),	// 乱数で求める拡大値最小
		FX32_CONST(1.0f),	// 乱数で求める拡大値最大
		FX32_CONST(0.0f),	// 拡大初速度
		FX32_CONST(0.0f),	// 動さ初速度
		0,					// 開始距離最小
		8,					// 開始距離最大
		0,					// 動さ距離最小
		24,					// 動さ距離最大
		16,					// 動さシンク
		NMIX_GAME_DEF_OAM_RES_SOUP,	// リソース何番目か
		2,					// アニメナンバー
		NMIX_DEMO_SOOP_EFF_MOVETYPE_ENDREQ,	// 動さタイプ
		TRUE,				// 拡縮使用フラグ
		TRUE,				// スープと同期して動くか
		10,					// ソフト優先順位
	},
	{	// スープ形態0	こぼれる
		FX32_CONST(0.50f),	// 乱数で求める拡大値最小
		FX32_CONST(1.50f),	// 乱数で求める拡大値最大
		FX32_CONST(0.0f),	// 拡大初速度
		FX32_CONST(2.0f),	// 動さ初速度
		32,					// 開始距離最小
		64,					// 開始距離最大
		32,					// 動さ距離最小
		64,					// 動さ距離最大
		16,					// 動さシンク
		NMIX_GAME_DEF_OAM_RES_SOUP,	// リソース何番目か
		0,						// アニメナンバー
		NMIX_DEMO_SOOP_EFF_MOVETYPE_ANM_END,// 動さタイプ
		FALSE,				// 拡縮使用フラグ
		FALSE,				// スープと同期して動くか
		5,					// ソフト優先順位
	},

	{	// スープ形態1	煙
		FX32_CONST(0.50f),	// 乱数で求める拡大値最小
		FX32_CONST(1.50f),	// 乱数で求める拡大値最大
		FX32_CONST(0.0f),	// 拡大初速度
		FX32_CONST(0.0f),	// 動さ初速度
		32,					// 開始距離最小
		64,					// 開始距離最大
		0,					// 動さ距離最小
		0,					// 動さ距離最大
		32,					// 動さシンク
		NMIX_GAME_DEF_OAM_RES_CREAM,	// リソース何番目か
		1,						// アニメナンバー
		NMIX_DEMO_SOOP_EFF_MOVETYPE_ANM_END,// 動さタイプ
		FALSE,				// 拡縮使用フラグ
		FALSE,				// スープと同期して動くか
		5,					// ソフト優先順位
	},
	{	// スープ形態1	こげる
		FX32_CONST(0.50f),	// 乱数で求める拡大値最小
		FX32_CONST(1.0f),	// 乱数で求める拡大値最大
		FX32_CONST(0.0f),	// 拡大初速度
		FX32_CONST(0.0f),	// 動さ初速度
		0,					// 開始距離最小
		8,					// 開始距離最大
		0,					// 動さ距離最小
		24,					// 動さ距離最大
		16,					// 動さシンク
		NMIX_GAME_DEF_OAM_RES_CREAM,	// リソース何番目か
		2,					// アニメナンバー
		NMIX_DEMO_SOOP_EFF_MOVETYPE_ENDREQ,	// 動さタイプ
		TRUE,				// 拡縮使用フラグ
		TRUE,				// スープと同期して動くか
		10,					// ソフト優先順位
	},
	{	// スープ形態1	こぼれる
		FX32_CONST(0.50f),	// 乱数で求める拡大値最小
		FX32_CONST(1.50f),	// 乱数で求める拡大値最大
		FX32_CONST(0.0f),	// 拡大初速度
		FX32_CONST(4.0f),	// 動さ初速度
		32,					// 開始距離最小
		64,					// 開始距離最大
		32,					// 動さ距離最小
		64,					// 動さ距離最大
		16,					// 動さシンク
		NMIX_GAME_DEF_OAM_RES_CREAM,	// リソース何番目か
		0,						// アニメナンバー
		NMIX_DEMO_SOOP_EFF_MOVETYPE_ANM_END,// 動さタイプ
		FALSE,				// 拡縮使用フラグ
		FALSE,				// スープと同期して動くか
		5,					// ソフト優先順位
	},
	

	{	// スープ形態2	煙
		FX32_CONST(0.50f),	// 乱数で求める拡大値最小
		FX32_CONST(1.50f),	// 乱数で求める拡大値最大
		FX32_CONST(0.0f),	// 拡大初速度
		FX32_CONST(0.0f),	// 動さ初速度
		32,					// 開始距離最小
		64,					// 開始距離最大
		0,					// 動さ距離最小
		0,					// 動さ距離最大
		32,					// 動さシンク
		NMIX_GAME_DEF_OAM_RES_SOBORO,	// リソース何番目か
		0,						// アニメナンバー
		NMIX_DEMO_SOOP_EFF_MOVETYPE_ANM_END,// 動さタイプ
		FALSE,				// 拡縮使用フラグ
		FALSE,				// スープと同期して動くか
		5,					// ソフト優先順位
	},
	{	// スープ形態2	こげ
		FX32_CONST(0.50f),	// 乱数で求める拡大値最小
		FX32_CONST(1.50f),	// 乱数で求める拡大値最大
		FX32_CONST(0.0f),	// 拡大初速度
		FX32_CONST(0.0f),	// 動さ初速度
		32,					// 開始距離最小
		64,					// 開始距離最大
		0,					// 動さ距離最小
		0,					// 動さ距離最大
		32,					// 動さシンク
		NMIX_GAME_DEF_OAM_RES_SOBORO,	// リソース何番目か
		1,						// アニメナンバー
		NMIX_DEMO_SOOP_EFF_MOVETYPE_ANM_END,// 動さタイプ
		FALSE,				// 拡縮使用フラグ
		FALSE,				// スープと同期して動くか
		5,					// ソフト優先順位
	},
};

#define NMIX_DEMO_SOOP_EFFECT_PRI	( 100 )		// ソフトpriority
#define NMIX_DEMO_SOOP_EFFECT_BG_PRI	( 2 )	// ハードpri
#define NMIX_DEMO_SOOP_END_EFF_SYNC	( 8 )	// こげ終了エフェクトシンク数



static NMIX_DEMO_SOOP_EFF_OBJ* NmixGameDemo_SoopEffect_GetClaenObj( NMIX_DEMO_SOOP_EFFECT* p_work );
static NMIX_DEMO_SOOP_EFF_OBJ* NmixGameDemo_SoopEffect_GetOldObj( NMIX_DEMO_SOOP_EFFECT* p_work );
static void NmixGameDemo_SoopEffect_DeleteObj( NMIX_DEMO_SOOP_EFF_OBJ* p_obj );
static void NmixGameDemo_SoopEffect_MainObj( NMIX_DEMO_SOOP_EFF_OBJ* p_obj );
static void NmixGameDemo_SoopEffect_MoveSoopObj( NMIX_DEMO_SOOP_EFF_OBJ* p_obj, NUTMIX_GAME_COMM_PACK* p_comm_pack );
static void NmixGameDemo_SoopEffect_AddObj( NMIX_DEMO_SOOP_EFF_OBJ* p_obj, int move_type, fx32 s_x, fx32 e_x, fx32 ss_x, fx32 s_y, fx32 e_y, fx32 ss_y, fx32 scale_x, fx32 scale_e, fx32 scale_ss, BOOL scale_use, int move_sync, NMIXGAME_CLACT_RES_WORK* p_res, int anm_idx, NMIXGAME_CLACT_SYS* p_clact, u32 heapID, BOOL soop_move, u8 pri );
static void NmixGameDemo_SoopEffect_EndEffectObj( NMIX_DEMO_SOOP_EFF_OBJ* p_obj );


//----------------------------------------------------------------------------
/**
 *	@brief	エフェクト初期化
 *	
 *	@param	p_work	ワーク
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_SoopEffect_Init( NMIX_DEMO_SOOP_EFFECT* p_work )
{
	memset( p_work, 0, sizeof(NMIX_DEMO_SOOP_EFFECT) );
}

//----------------------------------------------------------------------------
/**
 *	@brief	エフェクトワーク破棄
 *
 *	@param	p_work	ワーク
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_SoopEffect_Delete( NMIX_DEMO_SOOP_EFFECT* p_work )
{
	GF_ASSERT( p_work->res_load == FALSE );

	memset( p_work, 0, sizeof(NMIX_DEMO_SOOP_EFFECT) );
}

//----------------------------------------------------------------------------
/**
 *	@brief	リソース読み込み
 *
 *	@param	p_work				ワーク
 *	@param	p_clact				セルアクター
 *	@param	p_def_oam_res		デフォルトリソース
 *	@param	heapID				ヒープID
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_SoopEffect_GraphicLoad( NMIX_DEMO_SOOP_EFFECT* p_work, NMIXGAME_CLACT_SYS* p_clact, NMIXGAME_CLACT_RES_WORK* p_def_oam_res, u32 heapID )
{
	p_work->p_clact = p_clact;
	p_work->p_def_oam_res = p_def_oam_res;
	p_work->heapID	= heapID;

	p_work->res_load = TRUE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	リソース破棄
 *
 *	@param	p_work	ワーク
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_SoopEffect_GraphicRelease( NMIX_DEMO_SOOP_EFFECT* p_work )
{
	int i;
	
	// 登録されているOAMを破棄する
	for(  i=0; i<NMIX_DEMO_SOOP_EFF_NUM; i++ ){
		if( p_work->eff_obj[i].clact != NULL ){
			NmixGameDemo_SoopEffect_DeleteObj( &p_work->eff_obj[i] );
		}
	}
	p_work->res_load = FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	メイン関数
 *
 *	@param	p_work	ワーク
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_SoopEffect_Main( NMIX_DEMO_SOOP_EFFECT* p_work, NUTMIX_GAME_COMM_PACK* p_comm_pack )
{
	int i;

	for( i=0; i<NMIX_DEMO_SOOP_EFF_NUM; i++ ){
		if( p_work->eff_obj[i].clact ){
			NmixGameDemo_SoopEffect_MainObj( &p_work->eff_obj[i] );

			// スープと一緒に移動する
			if( p_work->eff_obj[i].soop_move ){
				NmixGameDemo_SoopEffect_MoveSoopObj( &p_work->eff_obj[i], p_comm_pack );
			}
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	エフェクト登録
 *
 *	@param	p_work			ワーク
 *	@param	soop_type		スープタイプ
 *	@param	eff_type		エフェクトタイプ
 *
 *	eff_type
		NMIX_DEMO_SOOP_EFF_TYPE_KOGE,
		NMIX_DMEO_SOOP_EFF_TYPE_KOBORE,
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_SoopEffect_Add( NMIX_DEMO_SOOP_EFFECT* p_work, int soop_type, int eff_type )
{
	NMIX_DEMO_SOOP_EFF_OBJ* p_obj;
	u16 rnd_rota;
	fx32 s_x, e_x, s_y, e_y, e_scale, ss_x, ss_y;
	NMIX_DEMO_SOOP_EFF_PARAM move_param = EffSoopMoveParam[ soop_type*3+eff_type ];
	int move_s_dis, move_dis;


	// 空いているオブジェ確保
	p_obj = NmixGameDemo_SoopEffect_GetClaenObj( p_work );
	if( p_obj == NULL ){
		// 一番昔に登録されたオブジェクトを取得
		p_obj = NmixGameDemo_SoopEffect_GetOldObj( p_work );
		GF_ASSERT( p_obj );
		NmixGameDemo_SoopEffect_DeleteObj( p_obj );	// オブジェクト破棄
	}
	
	// 乱数を使用してパラメータを作成する
	// 動さ方向を求める
	rnd_rota = gf_mtRand();

	// 開始動さ距離
	move_s_dis = move_param.rnd_dis_s_min + (gf_mtRand() % move_param.rnd_dis_s_max);
	move_dis = move_param.rnd_dis_min + (gf_mtRand() % move_param.rnd_dis_max);

	move_dis += move_s_dis;	// 開始位置を足す
	
	// 方向から開始ｘｙ座標を求める
	s_x = FX_Mul( FX_SinIdx( rnd_rota ),  move_s_dis*FX32_ONE );
	s_y = FX_Mul( FX_CosIdx( rnd_rota ),  move_s_dis*FX32_ONE );
	// 方向から終了ｘｙ座標を求める
	e_x = FX_Mul( FX_SinIdx( rnd_rota ),  move_dis*FX32_ONE );
	e_y = FX_Mul( FX_CosIdx( rnd_rota ),  move_dis*FX32_ONE );
	// 方向から初速度ｘｙを求める
	ss_x = FX_Mul( FX_SinIdx( rnd_rota ), move_param.move_ss );
	ss_y = FX_Mul( FX_CosIdx( rnd_rota ), move_param.move_ss );

	// 開始終了座標を中心からの距離にする
	s_x += 128 * FX32_ONE;
	e_x += 128 * FX32_ONE;
	s_y += 96 * FX32_ONE;
	e_y += 96 * FX32_ONE;

	// 拡縮を求める
	e_scale = move_param.rnd_scale_min + (gf_mtRand() % move_param.rnd_scale_max);
	
	// 動さデータ登録
	NmixGameDemo_SoopEffect_AddObj(
			p_obj, move_param.move_type,
			s_x, e_x, ss_x, s_y, e_y, ss_y,
			FX32_CONST( 0.10f ), e_scale, move_param.rnd_scale_ss, move_param.scale_use,
			move_param.move_sync,
			&p_work->p_def_oam_res[ move_param.res_id ],
			move_param.res_anm, p_work->p_clact, p_work->heapID,
			move_param.soop_move,
			move_param.pri );

	// 登録ｶｳﾝﾀ
	p_obj->add_time = p_work->add_count;
	p_work->add_count ++;
}

//----------------------------------------------------------------------------
/**
 *	@brief	終了リクエストを出し、終了待ちエフェクトを消す
 *
 *	@param	p_work	ワーク
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_SoopEffect_DelReq( NMIX_DEMO_SOOP_EFFECT* p_work )
{
	int i;	
	
	// 終了リクエストを出し、終了エフェクト設定
	for( i=0; i<NMIX_DEMO_SOOP_EFF_NUM; i++ ){
		
		if( p_work->eff_obj[i].clact != NULL ){
			NmixGameDemo_SoopEffect_EndEffectObj( &p_work->eff_obj[i] );
		}
	}
}



//----------------------------------------------------------------------------
/**
 *	@brief	クリーンオブジェクト取得
 *
 *	@param	p_work	ワーク
 *
 *	@return	オブジェPTR		NULL：なし
 */
//-----------------------------------------------------------------------------
static NMIX_DEMO_SOOP_EFF_OBJ* NmixGameDemo_SoopEffect_GetClaenObj( NMIX_DEMO_SOOP_EFFECT* p_work )
{
	int i;

	for( i=0; i<NMIX_DEMO_SOOP_EFF_NUM; i++ ){
		if( p_work->eff_obj[i].clact == NULL ){
			return &p_work->eff_obj[i];
		}
	}
	return NULL;
}

//----------------------------------------------------------------------------
/**
 *	@brief	一番昔に登録されたオブジェクトを取得
 *
 *	@param	p_work	ワーク
 *
 *	@return	オブジェクト
 */
//-----------------------------------------------------------------------------
static NMIX_DEMO_SOOP_EFF_OBJ* NmixGameDemo_SoopEffect_GetOldObj( NMIX_DEMO_SOOP_EFFECT* p_work )
{
	int i;
	NMIX_DEMO_SOOP_EFF_OBJ* p_obj = NULL;

	for( i=0; i<NMIX_DEMO_SOOP_EFF_NUM; i++ ){
		if( p_work->eff_obj[i].clact != NULL ){

			if( p_obj == NULL ){
				p_obj = &p_work->eff_obj[i];
			}else{
				if( p_obj->add_time > p_work->eff_obj[i].add_time ){
					p_obj = &p_work->eff_obj[i];
				}
			}
		}
	}
	return p_obj;
}

//----------------------------------------------------------------------------
/**
 *	@brief	オブジェクト破棄処理
 *
 *	@param	p_obj	ワーク
 */
//-----------------------------------------------------------------------------
static void NmixGameDemo_SoopEffect_DeleteObj( NMIX_DEMO_SOOP_EFF_OBJ* p_obj )
{
	GF_ASSERT( p_obj->clact );

	CLACT_Delete( p_obj->clact );
	memset( p_obj, 0, sizeof(NMIX_DEMO_SOOP_EFF_OBJ) );
}

//----------------------------------------------------------------------------
/**
 *	@brief	オブジェクトメイン処理
 *
 *	@param	p_obj	オブジェクト
 */
//-----------------------------------------------------------------------------
static void NmixGameDemo_SoopEffect_MainObj( NMIX_DEMO_SOOP_EFF_OBJ* p_obj )
{
	BOOL result;
	
	if( p_obj->move_end == FALSE ){
		// 動さ処理
		p_obj->move_end = NMIX_DEMO_AddMoveMainFx( &p_obj->move_x );
		NMIX_DEMO_AddMoveMainFx( &p_obj->move_y );
		NMIX_DEMO_AddMoveMainFx( &p_obj->move_scale );

		// 座標設定
		p_obj->matrix.x = p_obj->move_x.x;
		p_obj->matrix.y = p_obj->move_y.x;
		CLACT_SetMatrix( p_obj->clact, &p_obj->matrix );

		if( p_obj->scale_use ){
			p_obj->scale.x = p_obj->move_scale.x;
			p_obj->scale.y = p_obj->move_scale.x;
			p_obj->scale.z = p_obj->move_scale.x;
			CLACT_SetScale( p_obj->clact, &p_obj->scale );
		}
	}

	if( p_obj->anm_end == FALSE ){
		// アニメ終了と動さ終了を検知
		if( CLACT_AnmActiveCheck( p_obj->clact ) == FALSE ){
			p_obj->anm_end = TRUE;
		}
	}

	if( p_obj->move_type == NMIX_DEMO_SOOP_EFF_MOVETYPE_ANM_END ){
		
		if( (p_obj->move_end == TRUE) && (p_obj->anm_end == TRUE) ){
			// 破棄
			NmixGameDemo_SoopEffect_DeleteObj( p_obj );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	スープ一緒にオブジェクトを回転させる
 *
 *	@param	p_obj		オブジェクト
 *	@param	p_comm_pack	通信パック
 */
//-----------------------------------------------------------------------------
static void NmixGameDemo_SoopEffect_MoveSoopObj( NMIX_DEMO_SOOP_EFF_OBJ* p_obj, NUTMIX_GAME_COMM_PACK* p_comm_pack )
{
	VecFx32 matrix;
	u32 dist;
	u16 def_rota;
	u16 calc_rota;
	fx32 calc_x, calc_y;
	
	// 全アニメ終了後動く
	if( (p_obj->move_end == TRUE) && (p_obj->anm_end == TRUE) ){
		if( p_comm_pack->get_game_data[ COMM_PARENT_ID ].oya.rota_way == 0 ){
			p_obj->obj_rota += p_comm_pack->get_game_data[ COMM_PARENT_ID ].oya.rota_sp;
		}else{
			p_obj->obj_rota -= p_comm_pack->get_game_data[ COMM_PARENT_ID ].oya.rota_sp;
		}

		calc_x = p_obj->matrix.x - (NMIX_SOOP_ROTA_CX * FX32_ONE);
		calc_y = p_obj->matrix.y - (NMIX_SOOP_ROTA_CY * FX32_ONE);

		dist = GetVectorDistance( 	
				calc_x >> FX32_SHIFT,
				calc_y >> FX32_SHIFT,
				0, 0 );

		def_rota = FX_Atan2Idx(
				calc_y,
				calc_x );

		calc_rota = def_rota + p_obj->obj_rota;

		// アクター座標を設定
		matrix.x = FX_Mul( FX_CosIdx( calc_rota ), dist * FX32_ONE );
		matrix.y = FX_Mul( FX_SinIdx( calc_rota ), dist * FX32_ONE );

		matrix.x += (NMIX_SOOP_ROTA_CX*FX32_ONE);
		matrix.y += (NMIX_SOOP_ROTA_CY*FX32_ONE);

		// 回転後座標を設定
		CLACT_SetMatrix( p_obj->clact, &matrix );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	オブジェクト登録
 *
 *	@param	p_obj			オブジェクト
 *	@param	move_type		タイプ
 *	@param	s_x				開始ｘ座標
 *	@param	e_x				終了ｘ座標
 *	@param	ss_x			初速度ｘ
 *	@param	s_y				開始ｙ座標
 *	@param	e_y				終了ｙ座標
 *	@param	ss_y			初速度ｙ
 *	@param	scale_x			拡縮開始
 *	@param	scale_e			拡縮最後
 *	@param	scale_ss		拡縮初速度
 *	@param	scale_use		拡縮を使用するか
 *	@param	move_sync		動さシンク数
 *	@param	p_res			リソース
 *	@param	anm_idx			アニメナンバー
 *	@param	p_clact			アクター
 *	@param	heapID			ヒープID
 *	@param	soop_move		スープ動さ
 *	@param	pri				ソフトpriority
 */
//-----------------------------------------------------------------------------
static void NmixGameDemo_SoopEffect_AddObj( NMIX_DEMO_SOOP_EFF_OBJ* p_obj, int move_type, fx32 s_x, fx32 e_x, fx32 ss_x, fx32 s_y, fx32 e_y, fx32 ss_y, fx32 scale_x, fx32 scale_e, fx32 scale_ss, BOOL scale_use, int move_sync, NMIXGAME_CLACT_RES_WORK* p_res, int anm_idx, NMIXGAME_CLACT_SYS* p_clact, u32 heapID, BOOL soop_move, u8 pri )
{
	p_obj->move_type = move_type;
	NMIX_DEMO_AddMoveReqFx( &p_obj->move_x,
			s_x, e_x, ss_x, move_sync );
	NMIX_DEMO_AddMoveReqFx( &p_obj->move_y,
			s_y, e_y, ss_y, move_sync );
	NMIX_DEMO_AddMoveReqFx( &p_obj->move_scale,
			scale_x, scale_e, scale_ss, move_sync );

	p_obj->matrix.x = s_x;
	p_obj->matrix.y = s_y;
	p_obj->scale.x = scale_x;
	p_obj->scale.y = scale_x;
	p_obj->scale.z = scale_x;
	p_obj->scale_use = scale_use;
	p_obj->soop_move = soop_move;

	// アクター登録
	p_obj->clact = NMIXGAME_CLACT_Add( p_clact, p_res, s_x, s_y, 0, pri, heapID );
	GF_ASSERT( p_obj->clact );	// 登録失敗
	if( p_obj->scale_use ){
		// 拡縮
		CLACT_SetScaleAffine( p_obj->clact, &p_obj->scale, CLACT_AFFINE_DOUBLE );
	}
	// アニメ
	CLACT_AnmChg( p_obj->clact, anm_idx );
	// AUTOアニメ
	CLACT_SetAnmFlag( p_obj->clact, TRUE );
	// BG優先順位
	CLACT_BGPriorityChg( p_obj->clact, NMIX_DEMO_SOOP_EFFECT_BG_PRI );
}

//----------------------------------------------------------------------------
/**
 *	@brief	終了エフェクト設定
 *
 *	@param	p_obj	オブジェ
 */
//-----------------------------------------------------------------------------
static void NmixGameDemo_SoopEffect_EndEffectObj( NMIX_DEMO_SOOP_EFF_OBJ* p_obj )
{
	// アニメタイプチェック
	// 終了リクエスト形式かチェック
	if( p_obj->move_type != NMIX_DEMO_SOOP_EFF_MOVETYPE_ENDREQ ){
		return ;
	}
	
	// 拡縮アニメして終わる
	NMIX_DEMO_AddMoveReqFx( &p_obj->move_scale,
			p_obj->move_scale.x, FX32_CONST(0.050f), 0, NMIX_DEMO_SOOP_END_EFF_SYNC );

	// アニメ終了後自滅
	p_obj->move_type = NMIX_DEMO_SOOP_EFF_MOVETYPE_ANM_END;
	p_obj->scale_use = TRUE;

	CLACT_SetAffineParam( p_obj->clact, CLACT_AFFINE_DOUBLE );

}


//-----------------------------------------------------------------------------
/**
 *		矢印エフェクト管理
 */
//-----------------------------------------------------------------------------

#define NMIX_DEMO_YAZIRUSI_OAM_CONT_ID	( 7000 )	// 管理ID
#define NMIX_DEMO_YAZIRUSI_OAM_CL_NUM	( 2 )		// カラー本数
#define NMIX_DEMO_YAZIRUSI_OAM_SET_X	( 128 * FX32_ONE )
#define NMIX_DEMO_YAZIRUSI_OAM_SET_Y	( 96 * FX32_ONE )

#define NMIX_DEMO_YAZIRUSI_NORMAL_ANMNUM	( 3 )	// 点滅回数
#define NMIX_DEMO_YAZIRUSI_NORMAL_TIMING	( 8 )	// 点滅タイミング


static void NmixGameDemo_Yazirusi_NormalAnmStart( NMIX_DEMO_YAZIRUSI_OBJ* p_obj );
static void NmixGameDemo_Yazirusi_NormalAnm( NMIX_DEMO_YAZIRUSI_OBJ* p_obj );
static void NmixGameDemo_Yazirusi_ReverseAnmStart( NMIX_DEMO_YAZIRUSI_OBJ* p_obj );
static void NmixGameDemo_Yazirusi_ReverseAnm( NMIX_DEMO_YAZIRUSI_OBJ* p_obj );


//----------------------------------------------------------------------------
/**
 *	@brief	矢印エフェクト初期化
 *
 *	@param	p_work	ワーク
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_Yazirusi_Init( NMIX_DEMO_YAZIRUSI* p_work )
{
	memset( p_work, 0, sizeof(NMIX_DEMO_YAZIRUSI) );
}

//----------------------------------------------------------------------------
/**
 *	@brief	矢印エフェクト破棄
 *
 *	@param	p_work	ワーク
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_Yazirusi_Delete( NMIX_DEMO_YAZIRUSI* p_work )
{
	GF_ASSERT( p_work->res_load == FALSE );
	memset( p_work, 0, sizeof(NMIX_DEMO_YAZIRUSI) );
}

//----------------------------------------------------------------------------
/**
 *	@brief	リソース読み込み
 *
 *	@param	p_work		ワーク
 *	@param	p_clact		セルアクター
 *	@param	heapID		ヒープ
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_Yazirusi_GraphicLoad( NMIX_DEMO_YAZIRUSI* p_work, NMIXGAME_CLACT_SYS* p_clact, u32 heapID )
{
	int i;
	
	GF_ASSERT( p_work->res_load == FALSE );


	p_work->p_clact = p_clact;
	
	// リソース読み込み
	NMIXGAME_CLACT_ResLoadEasy( p_clact,
			&p_work->oam_res, ARC_NUTMIXER_GRA,
			NARC_nutmixer_cook_s_yazi_NCLR,
			NMIX_DEMO_YAZIRUSI_OAM_CL_NUM,
			NARC_nutmixer_cook_s_yazi_NCGR, 
			NARC_nutmixer_cook_s_yaj_NCER, 
			NARC_nutmixer_cook_s_yaj_NANR, 
			NMIX_DEMO_YAZIRUSI_OAM_CONT_ID, heapID );

	// オブジェクト登録
	for( i=0; i<NMIX_DEMO_YAZIRUSI_OBJ_NUM; i++ ){
		p_work->yazirusi[i].clact = NMIXGAME_CLACT_Add( p_clact,
				&p_work->oam_res,
				NMIX_DEMO_YAZIRUSI_OAM_SET_X,
				NMIX_DEMO_YAZIRUSI_OAM_SET_Y, 0,
				0, heapID );

		// アニメチェンジ
		if( i >= NMIX_DEMO_YAZIRUSI_LEFT ){

			CLACT_AnmChg( p_work->yazirusi[i].clact, 1 );
		}

		CLACT_SetDrawFlag( p_work->yazirusi[i].clact, FALSE );
	}

	p_work->res_load = TRUE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	リソース破棄
 *
 *	@param	p_work		ワーク
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_Yazirusi_GraphicRelease( NMIX_DEMO_YAZIRUSI* p_work )
{
	int i;

	GF_ASSERT( p_work->res_load == TRUE );

	for( i=0; i<NMIX_DEMO_YAZIRUSI_OBJ_NUM; i++ ){
		// オブジェクト破棄
		CLACT_Delete( p_work->yazirusi[i].clact );
	}
	
	// リソース破棄
	NMIXGAME_CLACT_ResDeleteEasy( p_work->p_clact, &p_work->oam_res );

	p_work->res_load = FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	矢印メイン動さ
 *
 *	@param	p_work	ワーク
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_Yazirusi_Main( NMIX_DEMO_YAZIRUSI* p_work )
{
	int i;
	
	// 各々の動さをする
	// 右左は、３回点滅して終わる
	// 逆回転は、終わりがクルまで、点滅する
	for( i=0; i<NMIX_DEMO_YAZIRUSI_OBJ_NUM; i++ ){
		if( (i == NMIX_DEMO_YAZIRUSI_LEFT) || (i == NMIX_DEMO_YAZIRUSI_RIGHT) ){
			NmixGameDemo_Yazirusi_NormalAnm( &p_work->yazirusi[i] );
		}else{
			NmixGameDemo_Yazirusi_ReverseAnm( &p_work->yazirusi[i] );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	動さリクエスト
 *
 *	@param	p_work		ワーク
 *	@param	eff_type	エフェクトタイプ
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_Yazirusi_Add( NMIX_DEMO_YAZIRUSI* p_work, int eff_type )
{
	GF_ASSERT( eff_type < NMIX_DEMO_YAZIRUSI_OBJ_NUM );

	// 動さ開始
	if( (eff_type == NMIX_DEMO_YAZIRUSI_LEFT) || (eff_type == NMIX_DEMO_YAZIRUSI_RIGHT) ){
		NmixGameDemo_Yazirusi_NormalAnmStart( &p_work->yazirusi[eff_type] );
	}else{
		NmixGameDemo_Yazirusi_ReverseAnmStart( &p_work->yazirusi[eff_type] );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	動さ強制終了
 *
 *	@param	p_work		ワーク
 *	@param	eff_type	エフェクトタイプ
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_Yazirusi_Stop( NMIX_DEMO_YAZIRUSI* p_work, int eff_type )
{
	GF_ASSERT( eff_type < NMIX_DEMO_YAZIRUSI_OBJ_NUM );
	
	// 動さ終了
	p_work->yazirusi[ eff_type ].move = FALSE;

	// 非表示に
	CLACT_SetDrawFlag( p_work->yazirusi[ eff_type ].clact, FALSE );
}

//----------------------------------------------------------------------------
/**
 *	@brief	矢印エフェクトが終わっているかチェック
 *
 *	@param	cp_work		ワーク
 *	@param	eff_type	タイプ
 *
 *	@retval	TRUE	終了
 *	@retval	FALSE	途中
 */
//-----------------------------------------------------------------------------
BOOL NMixGameDemo_Yazirusi_EndCheck( const NMIX_DEMO_YAZIRUSI* cp_work, int eff_type )
{
	GF_ASSERT( eff_type < NMIX_DEMO_YAZIRUSI_OBJ_NUM );
	
	// 動さ終了
	if( cp_work->yazirusi[ eff_type ].move == FALSE ){
		return TRUE;
	}
	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	通常アニメ開始
 *
 *	@param	p_obj	オブジェ
 */
//-----------------------------------------------------------------------------
static void NmixGameDemo_Yazirusi_NormalAnmStart( NMIX_DEMO_YAZIRUSI_OBJ* p_obj )
{
	p_obj->count = 0;
	p_obj->count_num = NMIX_DEMO_YAZIRUSI_NORMAL_ANMNUM;
	p_obj->move = TRUE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ノーマルアニメ
 *
 *	@param	p_obj	オブジェ
 */
//-----------------------------------------------------------------------------
static void NmixGameDemo_Yazirusi_NormalAnm( NMIX_DEMO_YAZIRUSI_OBJ* p_obj )
{
	if( p_obj->move == FALSE ){
		return ;
	}
	
	NmixGameDemo_Yazirusi_ReverseAnm( p_obj );

	// 0になった回数を数える
	if( p_obj->count == 0 ){
		p_obj->count_num --;
		if( p_obj->count_num <= 0 ){

			// 動さ終了
			p_obj->move = FALSE;
			// 描画OFF
			CLACT_SetDrawFlag( p_obj->clact, FALSE );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	逆回転用動さ開始
 *
 *	@param	p_obj	オブジェ
 */
//-----------------------------------------------------------------------------
static void NmixGameDemo_Yazirusi_ReverseAnmStart( NMIX_DEMO_YAZIRUSI_OBJ* p_obj )
{
	p_obj->count = 0;
	p_obj->move = TRUE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	逆回転　用アニメメイン
 *
 *	@param	p_obj	オブジェ
 */
//-----------------------------------------------------------------------------
static void NmixGameDemo_Yazirusi_ReverseAnm( NMIX_DEMO_YAZIRUSI_OBJ* p_obj )
{
	if( p_obj->move == FALSE ){
		return ;
	}
	
	if( p_obj->count == 0 ){
		// 表示
		CLACT_SetDrawFlag( p_obj->clact, TRUE );
	}else if( p_obj->count == NMIX_DEMO_YAZIRUSI_NORMAL_TIMING ){
		// 非表示
		CLACT_SetDrawFlag( p_obj->clact, FALSE );
	}else if( p_obj->count == (NMIX_DEMO_YAZIRUSI_NORMAL_TIMING * 2) ){
		p_obj->count = 0;
		return ;
	}
	p_obj->count ++;
}



//-----------------------------------------------------------------------------
/**
 *		星キラキラ　
 */
//-----------------------------------------------------------------------------
#define NMIX_DEMO_HOSI_SOFT_PRI	( 5 )
#define NMIX_DEMO_HOSI_BG_PRI	( 2 )

#define NMIX_DEMO_HOSI_MOVE_SYNC	( 16 )	// 動さシンク数
#define NMIX_DEMO_HOSI_MOVE_DIST	( FX32_CONST( 16 ) )	// 移動距離
#define NMIX_DEMO_HOSI_MOVE_SS		( FX32_CONST( 1 ) )		// 初速度
#define NMIX_DEMO_HOSI_MOVE_ADDNUM	( 2 )	// 1回の登録数



static NMIX_DEMO_HOSI_KIRAKIRA_OBJ* NMixGameDemo_HosiKirakiraCleanObj_Get( NMIX_DEMO_HOSI_KIRAKIRA* p_work );

static void NMixGameDemo_HosiKiraKiraObjMain( NMIX_DEMO_HOSI_KIRAKIRA_OBJ* p_obj );
static void NMixGameDemo_HosiKiraKiraObjDel( NMIX_DEMO_HOSI_KIRAKIRA_OBJ* p_obj );
static void NMixGameDemo_HosiKirakiraObjAdd( NMIX_DEMO_HOSI_KIRAKIRA_OBJ* p_obj, int anm_idx, fx32 x, fx32 y, fx32 e_x, fx32 e_y, fx32 ss_x, fx32 ss_y );



//----------------------------------------------------------------------------
/**
 *	@brief	キラキラ初期化
 *
 *	@param	p_work		ワーク
 *	@param	comm_count	通信相手数
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_HosiKiraKira_Init( NMIX_DEMO_HOSI_KIRAKIRA* p_work, int comm_count )
{
	memset( p_work, 0, sizeof(NMIX_DEMO_HOSI_KIRAKIRA) );
	p_work->comm_count = comm_count;
}

//----------------------------------------------------------------------------
/**
 *	@brief	キラキラ　破棄
 *
 *	@param	p_work	ワーク
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_HosiKiraKira_Delete( NMIX_DEMO_HOSI_KIRAKIRA* p_work )
{
	// リソース破棄していません。
	GF_ASSERT( p_work->res_load == FALSE );
	memset( p_work, 0, sizeof(NMIX_DEMO_HOSI_KIRAKIRA) );
}

//----------------------------------------------------------------------------
/**
 *	@brief	リソース読み込み処理
 *
 *	@param	p_work				ワーク
 *	@param	p_clact				アクターシステム
 *	@param	p_def_oam_res		デフォルトりそーす
 *	@param	heapID				ヒープID
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_HosiKiraKira_GraphicLoad( NMIX_DEMO_HOSI_KIRAKIRA* p_work, NMIXGAME_CLACT_SYS* p_clact, NMIXGAME_CLACT_RES_WORK* p_def_oam_res, u32 heapID )
{
	int i;
	
	for( i=0; i<KIRAKIRA_OBJ_MAX; i++ ){
		p_work->eff_obj[i].clact = NMIXGAME_CLACT_Add( p_clact,
				&p_def_oam_res[ NMIX_GAME_DEF_OAM_RES_COMMON ], 
				0, 0,
				0, NMIX_DEMO_HOSI_SOFT_PRI, heapID );
		CLACT_SetDrawFlag( p_work->eff_obj[i].clact, FALSE );
	}

	p_work->res_load = TRUE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	リソース破棄
 *
 *	@param	p_work	ワーク
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_HosiKiraKira_GraphicRelease( NMIX_DEMO_HOSI_KIRAKIRA* p_work )
{
	int i;

	for( i=0; i<KIRAKIRA_OBJ_MAX; i++ ){
		CLACT_Delete( p_work->eff_obj[i].clact );
	}

	p_work->res_load = FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	キラキラメイン処理
 *
 *	@param	p_work ワーク
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_HosiKiraKira_Main( NMIX_DEMO_HOSI_KIRAKIRA* p_work )
{
	int i;

	for( i=0; i<KIRAKIRA_OBJ_MAX; i++ ){
		NMixGameDemo_HosiKiraKiraObjMain( &p_work->eff_obj[i] );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	キラキラオブジェクトを出す
 *
 *	@param	p_work	ワーク
 *	@param	x		ｘ座標
 *	@param	y		ｙ座標
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_HosiKiraKira_Add( NMIX_DEMO_HOSI_KIRAKIRA* p_work, int x, int y )
{
	NMIX_DEMO_HOSI_KIRAKIRA_OBJ* p_obj;
	u32 rota;
	fx32 e_x, e_y;
	fx32 ss_x, ss_y;
	int i;


	// 登録座標などを求める
	rota = FX_Atan2Idx( x - NMIX_SOOP_ROTA_CX, y - NMIX_SOOP_ROTA_CY );

	// 回転位置から移動方向を求める
	e_x = FX_Mul( FX_CosIdx( rota ), NMIX_DEMO_HOSI_MOVE_DIST );
	e_y = FX_Mul( FX_SinIdx( rota ), NMIX_DEMO_HOSI_MOVE_DIST );
	ss_x = FX_Mul( FX_CosIdx( rota ), NMIX_DEMO_HOSI_MOVE_SS );
	ss_y = FX_Mul( FX_SinIdx( rota ), NMIX_DEMO_HOSI_MOVE_SS );

	// 空いているオブジェ取得
	p_obj = NMixGameDemo_HosiKirakiraCleanObj_Get( p_work );
	if( p_obj ){
		NMixGameDemo_HosiKirakiraObjAdd( p_obj, p_work->eff_count,
				x*FX32_ONE, y*FX32_ONE,
				(NMIX_SOOP_ROTA_CX*FX32_ONE) + e_x, 
				(NMIX_SOOP_ROTA_CY*FX32_ONE) + e_y, 
				ss_x, ss_y );
	}
	p_obj = NMixGameDemo_HosiKirakiraCleanObj_Get( p_work );
	if( p_obj ){
		NMixGameDemo_HosiKirakiraObjAdd( p_obj, p_work->eff_count,
				x*FX32_ONE, y*FX32_ONE,
				(NMIX_SOOP_ROTA_CX*FX32_ONE) - e_x, 
				(NMIX_SOOP_ROTA_CY*FX32_ONE) - e_y, 
				-ss_x, -ss_y );
	}

	// エフェクトカウント
	p_work->eff_count = (p_work->eff_count + 1) % p_work->comm_count;
}


//----------------------------------------------------------------------------
/**
 *	@brief	空いているオブジェクト取得
 *
 *	@param	p_work	ワーク
 *
 *	@return	オブジェクト
 */
//-----------------------------------------------------------------------------
static NMIX_DEMO_HOSI_KIRAKIRA_OBJ* NMixGameDemo_HosiKirakiraCleanObj_Get( NMIX_DEMO_HOSI_KIRAKIRA* p_work )
{
	int i;

	for( i=0; i<KIRAKIRA_OBJ_MAX; i++ ){

		if( p_work->eff_obj[i].move_flg == FALSE ){
			return &p_work->eff_obj[i];
		}
	}
	return NULL;
}

//----------------------------------------------------------------------------
/**
 *	@brief	オブジェクト動さメイン
 *
 *	@param	p_obj	オブジェクト
 */
//-----------------------------------------------------------------------------
static void NMixGameDemo_HosiKiraKiraObjMain( NMIX_DEMO_HOSI_KIRAKIRA_OBJ* p_obj )
{
	BOOL result;

	if( p_obj->move_flg == FALSE  ){
		return ;
	}
	
	if( p_obj->move_end == FALSE ){
		// 動さ処理
		p_obj->move_end = NMIX_DEMO_AddMoveMainFx( &p_obj->move_x );
		NMIX_DEMO_AddMoveMainFx( &p_obj->move_y );

		// 座標設定
		p_obj->matrix.x = p_obj->move_x.x;
		p_obj->matrix.y = p_obj->move_y.x;
		CLACT_SetMatrix( p_obj->clact, &p_obj->matrix );
	}

	if( p_obj->move_end == TRUE ){
		// 破棄
		NMixGameDemo_HosiKiraKiraObjDel( p_obj );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	オブジェクト動さ破棄
 *
 *	@param	p_obj	オブジェクト
 */
//-----------------------------------------------------------------------------
static void NMixGameDemo_HosiKiraKiraObjDel( NMIX_DEMO_HOSI_KIRAKIRA_OBJ* p_obj )
{
	if( p_obj->move_flg == FALSE  ){
		return ;
	}
	// アクターを非表示に
	CLACT_SetDrawFlag( p_obj->clact, FALSE );
	p_obj->move_flg = FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	オブジェクト登録
 *
 *	@param	p_obj		オブジェクト
 *	@param	anm_idx		アニメインデックス
 *	@param	x			開始ｘ座標
 *	@param	y			開始ｙ座標
 *	@param	e_x			終了ｘ座標
 *	@param	e_y			終了ｙ座標
 *	@param	ss_x		初速度ｘ
 *	@param	ss_y		初速度ｙ
 */
//-----------------------------------------------------------------------------
static void NMixGameDemo_HosiKirakiraObjAdd( NMIX_DEMO_HOSI_KIRAKIRA_OBJ* p_obj, int anm_idx, fx32 x, fx32 y, fx32 e_x, fx32 e_y, fx32 ss_x, fx32 ss_y )
{
	NMIX_DEMO_AddMoveReqFx( &p_obj->move_x,
			x, e_x, ss_x, NMIX_DEMO_HOSI_MOVE_SYNC );
	NMIX_DEMO_AddMoveReqFx( &p_obj->move_y,
			y, e_y, ss_y, NMIX_DEMO_HOSI_MOVE_SYNC );
	p_obj->matrix.x = x;
	p_obj->matrix.y = y;

	// 表示
	CLACT_SetDrawFlag( p_obj->clact, TRUE );
	// アニメ
	CLACT_AnmChg( p_obj->clact, anm_idx );
	CLACT_AnmReStart( p_obj->clact );
	// AUTOアニメ
	CLACT_SetAnmFlag( p_obj->clact, TRUE );
	// BG優先順位
	CLACT_BGPriorityChg( p_obj->clact, NMIX_DEMO_HOSI_BG_PRI );

	// 動さ開始
	p_obj->move_flg = TRUE;
	p_obj->move_end = FALSE;
}


//-----------------------------------------------------------------------------
/**
 *			ポルト表示
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *	@brief	ポルト表示初期化
 *
 *	@param	p_work		ワーク
 *	@param	x			ｘ座標
 *	@param	y			ｙ座標
 *	@param	poruto_type	ポルトタイプ
 *	@param	heapID		ヒープ
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_PorutoDraw_Init( NMIX_DEMO_PORUTO_DRAW* p_work, int x, int y, int poruto_type, int heapID )
{
	p_work->poruto_man = PoruOam_SysInit( heapID, 1, 1, PORUOAM_DRAW_MAIN, PORUOAM_CGXOFS_ADJUST );

	// ポルト登録
	p_work->p_obj = PoruOam_Add( p_work->poruto_man, poruto_type, x, y, 0, 0, 0, PORUOAM_VT_MAIN );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポルト破棄
 *
 *	@param	p_work	ワーク
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_PorutoDraw_Delete( NMIX_DEMO_PORUTO_DRAW* p_work )
{
	PoruOam_Del( p_work->poruto_man, p_work->p_obj );
	PoruOam_SysRelease( p_work->poruto_man );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポルト描画処理
 *
 *	@param	p_work ワーク
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_PorutoDraw_Draw( NMIX_DEMO_PORUTO_DRAW* p_work )
{
	PoruOam_DrawMain( p_work->poruto_man );
}


//-----------------------------------------------------------------------------
/**
 *			YES　NO　ウィンドウ
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *	@brief	YESNOウィンドウ　初期化
 *
 *	@param	p_work			ワーク
 *	@param	comm_count		通信ｶｳﾝﾀ
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_YesNoWnd_Init( NMIX_DEMO_YESNO_WND* p_work, int heap, GF_BGL_INI* p_bgl )
{
	p_work->yes_no = TOUCH_SW_AllocWork( heap );
	p_work->p_bgl = p_bgl;
}

//----------------------------------------------------------------------------
/**
 *	@brief	YESNOウィンドウ破棄
 *
 *	@param	p_work	ワーク
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_YesNoWnd_Delete( NMIX_DEMO_YESNO_WND* p_work )
{
	TOUCH_SW_FreeWork( p_work->yes_no );
}

//----------------------------------------------------------------------------
/**
 *	@brief	YESNOウィンドウ開始
 *
 *	@param	p_work ワーク
 */
//-----------------------------------------------------------------------------
void NMixGameDemo_YesNoWnd_Start( NMIX_DEMO_YESNO_WND* p_work )
{
	TOUCH_SW_PARAM param;

	param.p_bgl  = p_work->p_bgl;
	param.bg_frame = GF_BGL_FRAME2_M;
	param.char_offs = NMIX_MAINWIN_YESNO_BMP_COFS;
	param.pltt_offs = NMIX_MAINWIN_YESNO_PLT;
	param.x		= NMIX_MAINWIN_YESNO_WND_X;
	param.y		= NMIX_MAINWIN_YESNO_WND_Y;
	
	TOUCH_SW_Init( p_work->yes_no, &param );
}

//----------------------------------------------------------------------------
/**
 *	@brief	YESNOウィンドウメイン
 *
 *	@param	p_work	ワーク
 *
 *	@retval	TOUCH_SW_RET_NORMAL	// 何もなし
 *	@retval	TOUCH_SW_RET_YES	// はい
 *	@retval	TOUCH_SW_RET_NO		// いいえ
 */
//-----------------------------------------------------------------------------
u32 NMixGameDemo_YesNoWnd_Main( NMIX_DEMO_YESNO_WND* p_work )
{
	u32 ret;
	ret = TOUCH_SW_Main( p_work->yes_no );

	if( ret != TOUCH_SW_RET_NORMAL ){
		TOUCH_SW_Reset( p_work->yes_no );
	}
	return ret;
}

