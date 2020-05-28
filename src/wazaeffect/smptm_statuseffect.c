//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		smptm_statuseffect.c
 *	@brief		サンプル　ステータス　エフェクト
 *	@author		tomoya takahashi
 *	@data		2005.12.16
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "common.h"
#include "system/lib_pack.h"
#include "battle/battle_common.h"

#include "wazatool.h"
#include "we_tool.h"

#define __SMPTM_STATUSEFFECT_H_GLOBAL
#include "smptm_statuseffect.h"

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
 *					定数宣言
*/
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	ステータスエフェクトシステム
//	
//=====================================
typedef struct {
	CATS_SYS_PTR	csp;	///< セルアクター管理
	CATS_RES_PTR	crp;	///< リソースデータ
	PALETTE_FADE_PTR pfd;	///< パレットフェードワーク
	
	int				heap;
	int				status;			///< 実行ステータスエフェクト
	SOFT_SPRITE*	ssp;	//< ソフトウェアスプライト
	u8				client_type;///< クライアントタイプ
	BOOL*			p_end;			///< 終了検出フラグ

	BOOL			sub_call_flg;	///< サブコールの終了チェックフラグ
} SMPTM_SYS;
typedef void (*pSMPTM_Func)( SMPTM_SYS* p_smptm );


//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
static void SMPTM_SysTcb( TCB_PTR tcb, void* work );

static void SMPTM_ClactInit( SMPTM_SYS* p_smptm, int set_num, int char_num, int pltt_num, int cell_num, int cellanm_num );
static void SMPTM_ClactDelete( SMPTM_SYS* p_smptm );

static void SMPTM_ClactResLoad( SMPTM_SYS* p_smptm, const char** cpp_path, int pltt_num, int id );


static void SMPTM_None( SMPTM_SYS* p_smptm );

// 眠り
static void SMPTM_NemuriMove( SMPTM_SYS* p_smptm );
static void SMPTM_NemuriGraphicInit( SMPTM_SYS* p_smptm );
static void SMPTM_NemuriGraphicDelete( SMPTM_SYS* p_smptm );
static void SMPTM_NemuriTcb( TCB_PTR tcb, void* work );
static void NemuriObjStart( CATS_ACT_PTR cap, WAZATOOL_CALCMOVE* p_move, WAZATOOL_CALCMOVE* p_scale, int client_type );
static BOOL NemuriObjMove( CATS_ACT_PTR cap, WAZATOOL_CALCMOVE* p_move, WAZATOOL_CALCMOVE* p_scale );

// 氷
static void SMPTM_KooriMove( SMPTM_SYS* p_smptm );
static void SMPTM_KooriGraphicInit( SMPTM_SYS* p_smptm );
static void SMPTM_KooriGraphicDelete( SMPTM_SYS* p_smptm );
static void SMPTM_KooriTcb( TCB_PTR tcb, void* work );

//-------------------------------------
//	
//	関数テーブル
//	
//=====================================
const static pSMPTM_Func pSMPTM_SubCallFunc[] = {
	SMPTM_None,
	SMPTM_NemuriMove,
	SMPTM_None,
	SMPTM_NemuriMove,
	SMPTM_KooriMove,
	SMPTM_NemuriMove,
};

const static pSMPTM_Func pSMPTM_GraphicInitFunc[] = {
	SMPTM_None,
	SMPTM_NemuriGraphicInit,
	SMPTM_None,
	SMPTM_NemuriGraphicInit,
	SMPTM_KooriGraphicInit,
	SMPTM_NemuriGraphicInit,
};

const static pSMPTM_Func pSMPTM_GraphicDeleteFunc[] = {
	SMPTM_None,
	SMPTM_NemuriGraphicDelete,
	SMPTM_None,
	SMPTM_NemuriGraphicDelete,
	SMPTM_KooriGraphicDelete,
	SMPTM_NemuriGraphicDelete,
};

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ステータス　エフェクト　開始
 *
 *	@param	status			ステータス
 *	@param	client_type		クライアントタイプ
 *	@param	p_end			終了チェックフラグ
 *	@param	gra				グラフィックパラメータ
 *	@param	heap			使用ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void STATUSEFF_SampStart( int status, int client_type, BOOL* p_end, const SMPTM_GRAPHIC_PARAM* cp_gra, int heap )
{
	SMPTM_SYS* wk;
//	GF_ASSERT( status <= STATUS_MAHI );

	wk = sys_AllocMemory( heap, sizeof(SMPTM_SYS) );	
	memset( wk, 0, sizeof(SMPTM_SYS) );

	wk->status		= status;
	wk->client_type	= client_type;
	wk->p_end		= p_end;
	*wk->p_end		= FALSE;
	wk->heap		= heap;
	wk->csp			= cp_gra->csp;
	wk->ssp			= cp_gra->ss;
	wk->pfd			= cp_gra->pfd;

	// グラフィックデータ初期化関数コール
	pSMPTM_GraphicInitFunc[ wk->status ]( wk );

	// エフェクト開始コール
	wk->sub_call_flg = TRUE;
	pSMPTM_SubCallFunc[ wk->status ]( wk );
	

	// 終了検知タスク登録
	TCB_Add( SMPTM_SysTcb, wk, 64 );
}

static void SMPTM_SysTcb( TCB_PTR tcb, void* work )
{
	SMPTM_SYS* wk = work;

	if( wk->sub_call_flg == FALSE ){

		// グラフィックデータ破棄
		pSMPTM_GraphicDeleteFunc[ wk->status ]( wk );

		*wk->p_end = TRUE;
		sys_FreeMemoryEz( wk );
		TCB_Delete( tcb );
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	セルアクター初期化
 *
 *	@param	p_smptm			システムワーク
 *	@param	set_num			アクター最大数
 *	@param	char_num		キャラクタ数
 *	@param	pltt_num		パレット数
 *	@param	cell_num		セル数
 *	@param	cellanm_num		セルアニメ数
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void SMPTM_ClactInit( SMPTM_SYS* p_smptm, int set_num, int char_num, int pltt_num, int cell_num, int cellanm_num )
{
	TCATS_RESOURCE_NUM_LIST res_man_ini;
	
	// システムワーク作成
	p_smptm->crp = CATS_ResourceCreate( p_smptm->csp );
	// セルアクターセット作成
	CATS_ClactSetInit( p_smptm->csp, p_smptm->crp, set_num );
		
	// リソースマネージャ作成
	res_man_ini.resource_num.char_num = char_num;
	res_man_ini.resource_num.pltt_num = pltt_num;
	res_man_ini.resource_num.cell_num = cell_num;
	res_man_ini.resource_num.cell_anm_num = cellanm_num;
	res_man_ini.resource_num.mcell_num = 0;
	res_man_ini.resource_num.mcell_anm_num = 0;
	CATS_ResourceManagerInit( p_smptm->csp, p_smptm->crp, &res_man_ini );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	セルアクターリソース読み込み
 *
 *	@param	p_smptm			ワーク
 *	@param	cpp_path		パスのテーブル	(char pltt cell cellanm)
 *	@param	pltt_num		パレット数	読み込みすう
 *	@param	id				管理ID
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void SMPTM_ClactResLoad( SMPTM_SYS* p_smptm, const char** cpp_path, int pltt_num, int id )
{
	// キャラクタ読み込み
	CATS_LoadResourceChar(
			p_smptm->csp,
			p_smptm->crp,
			cpp_path[0],
			NNS_G2D_VRAM_TYPE_2DMAIN,
			id
			);

	// パレット読み込み
	CATS_LoadResourcePlttWork(
			p_smptm->pfd,
			FADE_MAIN_OBJ,
			p_smptm->csp,
			p_smptm->crp,
			cpp_path[1],
			pltt_num,
			NNS_G2D_VRAM_TYPE_2DMAIN,
			id
			);

	// セル読み込み
	CATS_LoadResourceCell(
			p_smptm->csp,
			p_smptm->crp,
			cpp_path[2],
			id
			);

	// セルアニメ読み込み
	CATS_LoadResourceCellAnm(
			p_smptm->csp,
			p_smptm->crp,
			cpp_path[3],
			id
			);
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	セルアクター破棄
 *
 *	@param	p_smptm		エフェクトワーク
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void SMPTM_ClactDelete( SMPTM_SYS* p_smptm )
{
	CATS_ResourceDestructor_S(p_smptm->csp, p_smptm->crp);
	p_smptm->crp = NULL;
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	何もなしエフェクト
 *
 *	@param	p_smptm	ステータスエフェクトワーク
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void SMPTM_None( SMPTM_SYS* p_smptm )
{
	p_smptm->sub_call_flg = FALSE;
}


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


const static char* pNemuriPath[] = {
	"data/smptm_nemuri.NCGR",
	"data/smptm_nemuri.NCLR",
	"data/smptm_nemuri.NCER",
	"data/smptm_nemuri.NANR",
};


enum{
	NEMURI_SEQ_0_START,
	NEMURI_SEQ_1_WAIT,
	NEMURI_SEQ_1_START,
	NEMURI_SEQ_END_WAIT,
	NEMURI_SEQ_END,
};

typedef struct{
	SMPTM_SYS* p_smptm;
	int seq;
	int wait;

	// 動作データ
	CATS_ACT_PTR		cap[ NEMURI_SET_NUM ];
	WAZATOOL_CALCMOVE	cap_move[ NEMURI_SET_NUM ];
	WAZATOOL_CALCMOVE	cap_scale[ NEMURI_SET_NUM ];
} SMPTM_NEMURI_SYS;

//----------------------------------------------------------------------------
/**
 *
 *	@brief	めむりエフェクト
 *
 *	@param	p_smptm	ステータスエフェクトワーク
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void SMPTM_NemuriMove( SMPTM_SYS* p_smptm )
{
	TCATS_OBJECT_ADD_PARAM_S coap;
	SMPTM_NEMURI_SYS* wk;
	int i;

	
	wk = sys_AllocMemory( p_smptm->heap, sizeof(SMPTM_NEMURI_SYS) );
	memset( wk, 0, sizeof(SMPTM_NEMURI_SYS) );
	memset( &coap, 0, sizeof(TCATS_OBJECT_ADD_PARAM_S) );

	wk->p_smptm = p_smptm;

	// 眠りセルアクターの登録を行う
	coap.x = SoftSpriteParaGet( p_smptm->ssp, SS_PARA_POS_X );
	coap.y = SoftSpriteParaGet( p_smptm->ssp, SS_PARA_POS_Y );
	coap.z = 0;
	coap.d_area = NNS_G2D_VRAM_TYPE_2DMAIN;
	coap.id[ 4 ] = CLACT_U_HEADER_DATA_NONE;
	coap.id[ 5 ] = CLACT_U_HEADER_DATA_NONE;

	for( i=0; i<NEMURI_SET_NUM; i++ ){
		wk->cap[i] = CATS_ObjectAdd_S( p_smptm->csp, p_smptm->crp, &coap );
		CATS_ObjectEnableCap( wk->cap[i], FALSE );
	}

	// タスク登録
	TCB_Add( SMPTM_NemuriTcb, wk, 0 );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	眠りグラフィックデータ作成
 *	
 *	@param	p_smptm	ワーク
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void SMPTM_NemuriGraphicInit( SMPTM_SYS* p_smptm )
{
	SMPTM_ClactInit( p_smptm, NEMURI_SET_NUM, NEMURI_CHAR_NUM, NEMURI_PLTT_NUM, NEMURI_CELL_NUM, NEMURI_CELLANM_NUM );

	SMPTM_ClactResLoad( p_smptm, pNemuriPath, NEMURI_LOAD_PLTT, NEMURI_RES_ID );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	眠りグラフィックデータ破棄
 *
 *	@param	p_smptm 
 *
 *	@return
 *
 *
 */
//-----------------------------------------------------------------------------
static void SMPTM_NemuriGraphicDelete( SMPTM_SYS* p_smptm )
{
	SMPTM_ClactDelete( p_smptm );
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
	SMPTM_NEMURI_SYS* wk = work;
	int i;

	switch( wk->seq ){
	case NEMURI_SEQ_0_START:
		NemuriObjStart( wk->cap[0], &wk->cap_move[0], &wk->cap_scale[0], wk->p_smptm->client_type );
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
		NemuriObjStart( wk->cap[1], &wk->cap_move[1], &wk->cap_scale[1], wk->p_smptm->client_type );
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
		wk->p_smptm->sub_call_flg = FALSE;
		sys_FreeMemoryEz( wk );
		TCB_Delete( tcb );
		return;
	}

	CATS_Draw(wk->p_smptm->crp);
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
static void NemuriObjStart( CATS_ACT_PTR cap, WAZATOOL_CALCMOVE* p_move, WAZATOOL_CALCMOVE* p_scale, int client_type )
{
	int vec_x;
	s16 cap_x, cap_y;
	
	// 表示＆倍角アフィン
	CATS_ObjectAffineSetCap( cap, CLACT_AFFINE_DOUBLE );
	CATS_ObjectEnableCap( cap, TRUE );

	CATS_ObjectPosGetCap( cap, &cap_x, &cap_y );

	
	switch(client_type){
	case CLIENT_TYPE_AA:
	case CLIENT_TYPE_A:
	case CLIENT_TYPE_C:
		vec_x = 1;
		break;
	
	case CLIENT_TYPE_BB:
	case CLIENT_TYPE_B:
	case CLIENT_TYPE_D:
		vec_x = -1;
		break;
	}

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

const static char* pKooriPath[] = {
	"data/smptm_koori.NCGR",
	"data/smptm_koori.NCLR",
	"data/smptm_koori.NCER",
	"data/smptm_koori.NANR",
};


enum{
	KOORI_SEQ_ALPHAIN_START,
	KOORI_SEQ_ALPHAIN,
	KOORI_SEQ_ANM,
	KOORI_SEQ_ALPHAOUT,
	KOORI_SEQ_END,
};

typedef struct{
	SMPTM_SYS* p_smptm;
	int seq;
	int plt_no;

	// 動作データ
	CATS_ACT_PTR		cap;
	WAZATOOL_ALPHA_FADE	cap_alpha;
} SMPTM_KOORI_SYS;

//----------------------------------------------------------------------------
/**
 *
 *	@brief	氷エフェクトタスク登録
 *
 *	@param	p_smptm 
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void SMPTM_KooriMove( SMPTM_SYS* p_smptm )
{
	TCATS_OBJECT_ADD_PARAM_S coap;
	SMPTM_KOORI_SYS* wk;

	
	wk = sys_AllocMemory( p_smptm->heap, sizeof(SMPTM_KOORI_SYS) );
	memset( wk, 0, sizeof(SMPTM_KOORI_SYS) );
	memset( &coap, 0, sizeof(TCATS_OBJECT_ADD_PARAM_S) );

	wk->p_smptm = p_smptm;

	// 眠りセルアクターの登録を行う
	coap.x = SoftSpriteParaGet( p_smptm->ssp, SS_PARA_POS_X );
	coap.y = SoftSpriteParaGet( p_smptm->ssp, SS_PARA_POS_Y );
	coap.z = 0;
	coap.d_area = NNS_G2D_VRAM_TYPE_2DMAIN;
	coap.id[ 4 ] = CLACT_U_HEADER_DATA_NONE;
	coap.id[ 5 ] = CLACT_U_HEADER_DATA_NONE;

	wk->cap = CATS_ObjectAdd_S( p_smptm->csp, p_smptm->crp, &coap );
	CATS_ObjectEnableCap( wk->cap, FALSE );
	CATS_ObjectObjModeSetCap( wk->cap, GX_OAM_MODE_XLU );

	wk->plt_no = CATS_ObjectPaletteOffsetGetCap( wk->cap );

	// タスク登録
	TCB_Add( SMPTM_KooriTcb, wk, 0 );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	氷グラフィックデータ初期化
 *
 *	@param	p_smptm		ワーク
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void SMPTM_KooriGraphicInit( SMPTM_SYS* p_smptm )
{
	SMPTM_ClactInit( p_smptm, KOORI_SET_NUM, KOORI_CHAR_NUM, KOORI_PLTT_NUM, KOORI_CELL_NUM, KOORI_CELLANM_NUM );

	SMPTM_ClactResLoad( p_smptm, pKooriPath, KOORI_LOAD_PLTT, KOORI_RES_ID );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	氷グラフィックデータ破棄
 *
 *	@param	p_smptm		ワーク
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void SMPTM_KooriGraphicDelete( SMPTM_SYS* p_smptm )
{
	SMPTM_ClactDelete( p_smptm );
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
	SMPTM_KOORI_SYS* wk = work;
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

		// ここは後でコンテスト用にする必要がある
		G2_SetBlendAlpha( GX_BLEND_PLANEMASK_NONE,
				( 1 << BATTLE_BGNO_BACKGROUND ) | GX_BLEND_PLANEMASK_BG0,
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
		wk->p_smptm->sub_call_flg = FALSE;
		sys_FreeMemoryEz( wk );
		TCB_Delete( tcb );
		return;
	}

	CATS_Draw(wk->p_smptm->crp);
}


//-----------------------------------------------------------------------------
/**
 *
 *				毒
 * 
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	毒動作開始関数
 *
 *	@param	p_smptm		ワーク
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void SMPTM_DokuMove( SMPTM_SYS* p_smptm )
{
	
}


#if 0
// デバッグ
typedef struct{
	WE_SYS_PTR we_sys;
	BOOL end;
} DEBUG_SMPTM_SYS;

static void Debug_smptmTcb( TCB_PTR tcb, void* work )
{
	DEBUG_SMPTM_SYS* wk = work;

	if( wk->end ){
		sys_FreeMemoryEz(wk);
		WEEffect_TCB_Delete(wk->we_sys, tcb);
	}
}

void Debug_SmpTm( WE_SYS_PTR we_sys )
{
	DEBUG_SMPTM_SYS* wk;
	SMPTM_GRAPHIC_PARAM gra;
	int i;
	
	wk = WET_ALLOC_MEMORY(we_sys, DEBUG_SMPTM_SYS);
	wk->we_sys = we_sys;
	
	gra.csp = WeSysCspGet(we_sys);
	gra.ss = WeSysSoftSpritePointerGet( we_sys, WeSysATNoGet(we_sys) );
	gra.pfd = WeSysPFDGet( we_sys );
	
	STATUSEFF_SampStart( STATUS_KOORI, 
			WeSysClientTypeGet(we_sys, WeSysATNoGet(we_sys)),
			&wk->end,
			&gra,
			WeSysHeapAreaGet(we_sys) );


	WEEffect_TCB_AddPriSet(wk->we_sys, Debug_smptmTcb, wk);
}
#endif

