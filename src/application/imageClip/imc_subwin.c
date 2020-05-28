//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		imc_subwin.c
 *	@brief		サブ画面の表示データ
 *	@author		
 *	@data		2005.10.24
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#include "system.h"
#include "assert.h"
#include "string.h"
#include "include/application/imageClip/imc_drawdata_define.h"
#include "msg_print.h"
#include "include/system/msgdata.h"
#include "include/system/fontproc.h"
#include "include/system/arc_util.h"
#include "include/application/imageClip/imc_snd_def.h"


#define	__IMC_SUBWIN_H_GLOBAL
#include "include/application/imageClip/imc_subwin.h"

#include "include/system/window.h"


// imc_subwin.hないの"contest.h"をインクルードしている必要があるので
// ここでインクルード
#include "src/contest/comm_command_contest.h"


//-----------------------------------------------------------------------------
/**
 *					定数宣言
*/
//-----------------------------------------------------------------------------
// アクセサリアイコン表示座標定数
#define IMC_SUBWIN_ACCEICON_X_NUM	( 10 )
#define IMC_SUBWIN_ACCEICON_Y_NUM	( IMC_SUBWIN_ACCECOUNT_ICON_MAX / IMC_SUBWIN_ACCEICON_X_NUM )
#define IMC_SUBWIN_ACCEICON_X_DEF	( 38 )
#define IMC_SUBWIN_ACCEICON_Y_DEF	( 104 )
#define IMC_SUBWIN_ACCEICON_X_OFS	( 18 )
#define IMC_SUBWIN_ACCEICON_Y_OFS	( 18 )
#define IMC_SUBWIN_ACCEICON_RES_ID	( 2000 )
#define IMC_SUBWIN_ACCEICON_ANM_ON	(0)		// ONアニメ
#define IMC_SUBWIN_ACCEICON_ANM_OFF	(1)		// OFFアニメ


// テーマ文字列
#define IMC_SUBWIN_THEMA_DEFX ( 0 )
#define IMC_SUBWIN_THEMA_X	( 72 )

//---------------------------------------------------------
//	タイムｶｳﾝﾀ関係
//---------------------------------------------------------
// ｶｳﾝﾀ用
#define IMC_SUBWIN_TIMENUM_RES_ID	( 3000 )
// 数字オブジェシーケンス
enum{
	IMC_SUBWIN_NUM_SEQ_00 = 0,
	IMC_SUBWIN_NUM_SEQ_MAX	= 10,
};
#define IMC_SUBWIN_NUM_DEFX	( 103 )	// X座標
#define IMC_SUBWIN_NUM_DEFY	( 58 )	// Y座標
#define IMC_SUBWIN_NUM_OFSX	( 24 )	// Xオフセット
#define IMC_SUBWIN_NUM_ONE_SYNC	( 30 )	// 1秒のｶｳﾝﾀ変更値
#define IMC_SUBWIN_NUM_PLTT_CHG	( 10 )	// パレット変更のタイミング
#define IMC_SUBWIN_NUM_BMP_DRAW_XDEF	( 0 )
#define IMC_SUBWIN_NUM_BMP_DRWA_YDEF	( 4 )
#define IMC_SUBWIN_NUM_BMP_DRAW_XOFS	( 72 )
// ｶｳﾝﾀｴﾌｪｸﾄ
#define IMC_SUBWIN_NUM_EFFE_SCAL_DEF	( FX32_CONST(1.0f) )
#define IMC_SUBWIN_NUM_EFFE_SCAL_END	( FX32_CONST(1.0f) )
#define IMC_SUBWIN_NUM_EFFE_SCAL_OFS	( FX32_CONST(0.150f) )
#define IMC_SUBWIN_NUM_EFFE_COUNT_MAX	( 16 )
#define IMC_SUBWIN_NUM_SIZE_X			( FX32_CONST(24) )
#define IMC_SUBWIN_NUM_SIZE_Y			( FX32_CONST(24) )



 

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
static void initBG( IMC_BG* bg, GF_BGL_INI* ini );
static void initTalkWinGra( GF_BGL_INI* ini, const CONFIG* cp_config );
static void initBmp( GF_BGL_BMPWIN** bmp, GF_BGL_INI* ini, int x, int y, int scx, int scy, int cofs, BOOL waku_write );
static void deleteBG( IMC_BG* bg );
static void deleteBmp( GF_BGL_BMPWIN* bmp );
static s32 printBmp( GF_BGL_BMPWIN* bmp, int arcID, int dataID, int msgID, int x, int y, u32 wait );
static s32 printBmp_Buff( GF_BGL_BMPWIN* bmp, int arcID, int dataID, int msgID, int x, int y, u32 wait, STRBUF** pp_glb_str );
static s32 printBmp_NoWaku( GF_BGL_BMPWIN* bmp, int arcID, int dataID, int msgID, int x, int y, GF_PRINTCOLOR col, u32 wait );
static s32 printBmp_NoWaku_Buff( GF_BGL_BMPWIN* bmp, int arcID, int dataID, int msgID, int x, int y, GF_PRINTCOLOR col, u32 wait, STRBUF** pp_glb_str );

static void initAcceIconWork( IMC_SUBWIN_ACCEICON* p_data, CLACT_SET_PTR clact_set, CLACT_U_RES_MANAGER_PTR* p_res_man, int acce_max );
static void setAcceIconWork( IMC_SUBWIN_ACCEICON* p_data, int acce_num );
static void deleteAcceIconWork( IMC_SUBWIN_ACCEICON* p_data, CLACT_U_RES_MANAGER_PTR* p_res_man );

static void InitCounterWork( IMC_SUBWIN_TIMECOUNT* p_data, CLACT_SET_PTR clact_set, CLACT_U_RES_MANAGER_PTR* p_res_man, int count_max, GF_BGL_INI* p_bgini,  CON_IMC_LOCAL* p_comm_data);
static void deleteCounterWork( IMC_SUBWIN_TIMECOUNT* p_data, CLACT_U_RES_MANAGER_PTR* p_res_man );
static void mainCounterWork( IMC_SUBWIN_TIMECOUNT* p_data );
static void countDownCounterData( IMC_SUBWIN_TIMECOUNT* p_data );
static void popCounterData( IMC_SUBWIN_TIMECOUNT* p_data );
static void setCounterClactAnm( IMC_SUBWIN_TIMECOUNT* p_data );
static void initCounterEffect( IMC_SUBWIN_TIMECOUNT* p_data, IMC_SUBWIN_TIME_EFFECT* effect_work );
static void mainCounterEffect( IMC_SUBWIN_TIME_EFFECT* effect_work );
static BOOL checkCounterEffectEnd( const IMC_SUBWIN_TIME_EFFECT* cp_effect_work );

static void imcSubWin_DefaultClactResLoad( CLACT_U_RES_OBJ_PTR* p_res_obj, CLACT_U_RES_MANAGER_PTR* pp_res_manager, int heap, int arc_idx, int charidx, int plttidx, int cellidx, int cellanmidx, int plttload_num, int common_res_id );
static void imcSubWin_DefaultClactResDelete( CLACT_U_RES_OBJ_PTR* p_res_obj, CLACT_U_RES_MANAGER_PTR* pp_res_manager );
static void imcSubWin_DefaultClactHeaderMake( CLACT_U_RES_OBJ_PTR* p_res_obj, CLACT_U_RES_MANAGER_PTR* pp_res_manager, CLACT_HEADER* p_head, int bg_pri );

static void imc_UTIL_MoveReq( IMC_SUBWIN_MOVE_WORK* p_work, fx32 s_x, fx32 e_x, int count_max );
static BOOL	imc_UTIL_MoveMain( IMC_SUBWIN_MOVE_WORK* p_work );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	サブウィンドウの初期化
 *
 *	@param	subwin		サブウィンドウ構造体
 *	@param	init		初期化データ
 *	@param	init_mask	初期化マスク
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_SUBWIN_Init( IMC_SUBWIN* subwin, IMC_SUBWIN_INIT* init, int init_mask )
{
	
	if( init_mask & IMC_SUBWIN_INITMASK_CLEAN ){

		memset( subwin, 0, sizeof(IMC_SUBWIN) );
	}
	
	if( init_mask & IMC_SUBWIN_INITMASK_BG ){
		
		initBG( &subwin->bg, init->bg_ini );
	}

	if( init_mask & IMC_SUBWIN_INITMASK_BMP ){

		initBmp( &subwin->bmp, init->bg_ini, 
				IMC_SUBWIN_BMP_X, IMC_SUBWIN_BMP_Y,
				IMC_SUBWIN_BMP_SIZE_X, IMC_SUBWIN_BMP_SIZE_Y,
				TALK_WIN_CGX_SIZ + IMC_SUBWIN_BMP_FRAME_CHAR_OFS,
				TRUE );
	}

	// アイコン数ｶｳﾝﾀ
	if( init_mask & IMC_SUBWIN_INITMASK_ACCE_COUNT ){

		initAcceIconWork( &subwin->acce_icon, init->clactSet, init->p_resMan, init->acce_max );
	}

	// タイムｶｳﾝﾀ
	if( init_mask & IMC_SUBWIN_INITMASK_TIME_COUNT ){
		InitCounterWork( &subwin->counter, init->clactSet, init->p_resMan, init->count_max, init->bg_ini, init->p_comm_data );
	}

	// ランクSTR描画
	if( init_mask & IMC_SUBWIN_INITMASK_RANKBMP ){
		initBmp( &subwin->rankbmp, init->bg_ini, 
				IMC_SUBWIN_RANKBMP_X, IMC_SUBWIN_RANKBMP_Y,
				IMC_SUBWIN_RANKBMP_SIZE_X, IMC_SUBWIN_RANKBMP_SIZE_Y,
				TALK_WIN_CGX_SIZ + IMC_SUBWIN_RANKBMP_FRAME_CHAR_OFS,
				TRUE );

		// ビットマップ初期化
		GF_BGL_BmpWinDataFill( subwin->rankbmp, 15 );

		// 枠以外を書き込む
		printBmp_NoWaku( subwin->rankbmp, ARC_MSG, init->rank_msgid, imgclip_subwin_theme, IMC_SUBWIN_THEMA_DEFX, 0, GF_PRINTCOLOR_MAKE(1,2,15), MSG_NO_PUT );
		printBmp_NoWaku( subwin->rankbmp, ARC_MSG, init->rank_msgid, init->rank_strid, IMC_SUBWIN_THEMA_X, 0, GF_PRINTCOLOR_MAKE(1,2,15), MSG_NO_PUT );

		BmpTalkWinWrite( subwin->rankbmp, WINDOW_TRANS_ON, IMC_SUBWIN_BMP_FRAME_CHAR_OFS, IMC_SUBWIN_BMP_WAKU_PLTT_NO );
	}


	///データ設定
	subwin->clactSet	= init->clactSet;
	subwin->p_resMan	= init->p_resMan;

	// 会話ウィンドウグラフィックデータ読み込み
	initTalkWinGra( init->bg_ini, init->cp_config );
	
	// コンフィグデータ
	subwin->wnd_no = CONFIG_GetWindowType( init->cp_config );
	subwin->wait = CONFIG_GetMsgPrintSpeed( init->cp_config );
	
	subwin->init_flg |= init_mask;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	サブウィンドウ破棄
 *
 *	@param	subwin	サブウィンドウ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_SUBWIN_Delete( IMC_SUBWIN* subwin )
{
	if( subwin->init_flg & IMC_SUBWIN_INITMASK_BG ){
		
		deleteBG( &subwin->bg );
		subwin->init_flg &= ~IMC_SUBWIN_INITMASK_BG;
	}

	if( subwin->init_flg & IMC_SUBWIN_INITMASK_BMP ){

		deleteBmp( subwin->bmp );
		subwin->init_flg &= ~IMC_SUBWIN_INITMASK_BMP;
	}

	// アクセサリｶｳﾝﾀ
	if( subwin->init_flg & IMC_SUBWIN_INITMASK_ACCE_COUNT ){

		deleteAcceIconWork( &subwin->acce_icon, subwin->p_resMan );
		subwin->init_flg &= ~IMC_SUBWIN_INITMASK_ACCE_COUNT;
	}

	// タイムｶｳﾝﾀ
	if( subwin->init_flg & IMC_SUBWIN_INITMASK_TIME_COUNT ){
		deleteCounterWork( &subwin->counter, subwin->p_resMan );
		subwin->init_flg &= ~IMC_SUBWIN_INITMASK_TIME_COUNT;
	}

	// ランクSTR 
	if( subwin->init_flg & IMC_SUBWIN_INITMASK_RANKBMP ){
		deleteBmp( subwin->rankbmp );
		subwin->init_flg &= ~IMC_SUBWIN_INITMASK_RANKBMP;
	}


	memset( subwin, 0, sizeof(IMC_SUBWIN) );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	メイン関数
 *
 *	@param	subwin	サブウィンドウ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_SUBWIN_Main( IMC_SUBWIN* subwin )
{
	// タイムｶｳﾝﾀ
	if( subwin->init_flg & IMC_SUBWIN_INITMASK_TIME_COUNT ){
		mainCounterWork( &subwin->counter );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ビットマップに文字列を表示
 *
 *	@param	subwin	サブウィンドウオブジェ
 *	@param	arcID	アーカイブID
 *	@param	dataID	データID
 *	@param	msgID	表示するメッセージID
 *	
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_SUBWIN_SetBmpWin( IMC_SUBWIN* subwin, int arcID, int dataID, int msgID )
{
	GF_ASSERT_MSG( (subwin->init_flg & IMC_SUBWIN_INITMASK_BMP), "バンプウィンドウが初期化されていません" )
	printBmp( subwin->bmp, arcID, dataID, msgID, 0, 0, MSG_NO_PUT );
}
s32 IMC_SUBWIN_SetBmpWinWait( IMC_SUBWIN* subwin, int arcID, int dataID, int msgID )
{
	GF_ASSERT_MSG( (subwin->init_flg & IMC_SUBWIN_INITMASK_BMP), "バンプウィンドウが初期化されていません" )
	return printBmp_Buff( subwin->bmp, arcID, dataID, msgID, 0, 0, subwin->wait, &subwin->p_glb_str );
}


//----------------------------------------------------------------------------
/**
 *	@brief	Waitバージョンで確保していたバッファをはき
 */
//-----------------------------------------------------------------------------
void IMC_SUBWIN_EndBmpWinWait( IMC_SUBWIN* subwin )
{
	STRBUF_Delete( subwin->p_glb_str );
	subwin->p_glb_str = NULL;
}

//----------------------------------------------------------------------------
/**
 *	@brief	アクセサリカウントアイコン描画設定
 *
 *	@param	subwin		ワーク
 *	@param	acce_num	現在のアクセサリ数
 *
 *	@return	none
 */	
//-----------------------------------------------------------------------------
void IMC_SUBWIN_SetAcceIcon( IMC_SUBWIN* subwin, int acce_num )
{
	setAcceIconWork( &subwin->acce_icon, acce_num );
}

//----------------------------------------------------------------------------
/**
 *	@brief	今のカウンター値取得関数
 *
 *	@param	subwin	サブウィンドウ
 *
 *	@return	カウンターの値
 */
//-----------------------------------------------------------------------------
int IMC_SUBWIN_GetCounterNowNum( const IMC_SUBWIN* subwin )
{
	return subwin->counter.count;
}

//----------------------------------------------------------------------------
/**
 *	@brief	現在カウント値設定
 *
 *	@param	subwin
 *	@param	count 
 *
 *
 * "送信データカウントを設定する関数です
 */
//-----------------------------------------------------------------------------
void IMC_SUBWIN_SetCounterNowNum( IMC_SUBWIN* subwin, int count )
{
	subwin->counter.master_count = count;
}


//----------------------------------------------------------------------------
/**
 *	@brief	カウンターｴﾌｪｸﾄの終了チェック
 *
 *	@param	subwin	サブウィンドウ
 *
 *	@retval	TRUE	終了
 *	@retval	FALSE	途中
 */
//-----------------------------------------------------------------------------
BOOL IMC_SUBWIN_GetCounterEffectEnd( const IMC_SUBWIN* subwin )
{
	return checkCounterEffectEnd( &subwin->counter.counter_eff );
}

//-----------------------------------------------------------------------------
/**
*		プライベート関数
*/
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	BG面の初期化
 *
 *	@param	bg	BGオブジェ
 *	@param	ini	BGシステムワーク
 *
 *	@return	none
 *
 *
 * "送信データカウントを設定する関数です
 *
 *
 */
//-----------------------------------------------------------------------------
static void initBG( IMC_BG* bg, GF_BGL_INI* ini )
{
	IMC_BG_ADD add;

	add.bg_ini		= ini;
	add.arc_file	= ARC_IMAGECLIP_GRA;
	add.char_arc	= IMC_SUBWIN_CG_ARC;
	add.pltt_arc	= IMC_SUBWIN_PL_ARC;
	add.scrn_arc	= IMC_SUBWIN_SC_ARC;
	add.x			= 0;
	add.y			= 0;
	add.frame		= GF_BGL_FRAME0_S;
	add.pltt_num	= IMC_SUBWIN_PL_NUM;
	add.pltt_offs	= 0;
	add.char_offs	= 0;
	add.heap		= HEAPID_IMAGECLIP_DRAW;

	IMC_BG_MakaObj( bg, &add );
}

//----------------------------------------------------------------------------
/**
 *	@brief	会話ウィンドウ用グラフィックデータを読み込む
 *
 *	@param	ini			BGデータ	
 *	@param	cp_config	コンフィグデータ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void initTalkWinGra( GF_BGL_INI* ini, const CONFIG* cp_config )
{
	WINTYPE win_no = CONFIG_GetWindowType( cp_config );
	
	// 枠グラフィック読み込み
	TalkWinGraphicSet( ini, GF_BGL_FRAME1_S, IMC_SUBWIN_BMP_FRAME_CHAR_OFS, IMC_SUBWIN_BMP_WAKU_PLTT_NO, win_no, HEAPID_IMAGECLIP_DRAW );

	// フォント用カラーパレット読み込み
	TalkFontPaletteLoad( PALTYPE_SUB_BG, IMC_SUBWIN_BMP_PLTT_NO*32, HEAPID_IMAGECLIP_DRAW );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ビットマップウィンドウ面の初期化
 *
 *	@param	bmp		ビットマップウィンドウ
 *	@param	ini		BGシステムワーク
 *	@param	x		ｘ座標	キャラクタ単位
 *	@param	x		ｙ座標	キャラクタ単位
 *	@param	scx		ｘサイズ	キャラクタ単位
 *	@param	scy		ｙサイズ	キャラクタ単位
 *	@param	cofs	キャラクタオフセット
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void initBmp( GF_BGL_BMPWIN** bmp, GF_BGL_INI* ini, int x, int y, int scx, int scy, int cofs, BOOL waku_write )
{
	*bmp = GF_BGL_BmpWinAllocGet( HEAPID_IMAGECLIP_DRAW, 1 );
	GF_BGL_BmpWinInit( *bmp );

	GF_BGL_BmpWinAdd(
			ini,
			*bmp,
			GF_BGL_FRAME1_S,
			x,
			y,
			scx,
			scy,
			IMC_SUBWIN_BMP_PLTT_NO,
			cofs );
	
	GF_BGL_BmpWinDataFill( *bmp, 15 );
	
	if( waku_write ){
		// カラのビットマップ書き込み
		BmpTalkWinWrite( *bmp, WINDOW_TRANS_ON, IMC_SUBWIN_BMP_FRAME_CHAR_OFS, IMC_SUBWIN_BMP_WAKU_PLTT_NO );
	}

	GF_BGL_BmpWinOn( *bmp );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	BG面の破棄
 *
 *	@param	bg		BGオブジェ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void deleteBG( IMC_BG* bg )
{
	IMC_BG_DeleteObj( bg );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ビットマップ面の破棄
 *
 *	@param	bmp		ビットマップウィンドウ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void deleteBmp( GF_BGL_BMPWIN* bmp )
{
	// ビットマップウィンドウ破棄
	GF_BGL_BmpWinFree( bmp, 1 );
}

//----------------------------------------------------------------------------
/**
 *	@brief	メッセージ描画関数
 *
 *	@param	bmp		ビットマップ
 *	@param	arcID	アーカイブファイルID
 *	@param	dataID	データID
 *	@param	msgID	メッセージID
 *	@param	x		x座標
 *	@param	y		y座標
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static s32 printBmp( GF_BGL_BMPWIN* bmp, int arcID, int dataID, int msgID, int x, int y, u32 wait )
{
	s32 msg_idx;
	
	// ビットマップ初期化
	GF_BGL_BmpWinDataFill( bmp, 15 );

	// 枠以外を書き込む
	msg_idx = printBmp_NoWaku( bmp, arcID, dataID, msgID, x, y, GF_PRINTCOLOR_MAKE(1,2,15), wait );

	BmpTalkWinWrite( bmp, WINDOW_TRANS_ON, IMC_SUBWIN_BMP_FRAME_CHAR_OFS, IMC_SUBWIN_BMP_WAKU_PLTT_NO );

	return msg_idx;
}

//----------------------------------------------------------------------------
/**
 *	@brief	メッセージ描画関数
 *
 *	@param	bmp		ビットマップ
 *	@param	arcID	アーカイブファイルID
 *	@param	dataID	データID
 *	@param	msgID	メッセージID
 *	@param	x		x座標
 *	@param	y		y座標
 *	@param	wait	ウエイト
 *	@param	pp_glb_str	グローバル文字列
 *
 *	@return	メッセージIDX
 */
//-----------------------------------------------------------------------------
static s32 printBmp_Buff( GF_BGL_BMPWIN* bmp, int arcID, int dataID, int msgID, int x, int y, u32 wait, STRBUF** pp_glb_str )
{
	s32 msg_idx;
	
	// ビットマップ初期化
	GF_BGL_BmpWinDataFill( bmp, 15 );

	// 枠以外を書き込む
	msg_idx = printBmp_NoWaku_Buff( bmp, arcID, dataID, msgID, x, y, GF_PRINTCOLOR_MAKE(1,2,15), wait, pp_glb_str );

	BmpTalkWinWrite( bmp, WINDOW_TRANS_ON, IMC_SUBWIN_BMP_FRAME_CHAR_OFS, IMC_SUBWIN_BMP_WAKU_PLTT_NO );

	return msg_idx;
}

//----------------------------------------------------------------------------
/**
 *	@brief	枠なし文字列描画
 *
 *	@param	bmp		ビットマップ
 *	@param	arcID	あーくID 
 *	@param	dataID	データID
 *	@param	msgID	メッセージID
 *	@param	x		ｘ座標
 *	@param	y		ｙ座標
 *	@param	col		表示カラー
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static s32 printBmp_NoWaku( GF_BGL_BMPWIN* bmp, int arcID, int dataID, int msgID, int x, int y, GF_PRINTCOLOR col, u32 wait )
{
	MSGDATA_MANAGER* msg_data;
	STRBUF* str;
	s32 msg_idx;

	// 文字列取得
	msg_data = MSGMAN_Create( MSGMAN_TYPE_NORMAL, arcID, dataID, HEAPID_IMAGECLIP_DATA );
	GF_ASSERT( msg_data );
	str = MSGMAN_AllocString( msg_data, msgID );

	// 文字列書き込み
	msg_idx = GF_STR_PrintColor( bmp, FONT_TALK, str, x, y, wait, col, NULL );
												// ↑描画位置
	STRBUF_Delete( str );
	MSGMAN_Delete( msg_data );

	return msg_idx;
}

//----------------------------------------------------------------------------
/**
 *	@brief	文字列バッファ保存	文字表示
 *
 *	@param	bmp			ビットマップウィンドウ
 *	@param	arcID		アーカイブ
 *	@param	dataID		データIDX
 *	@param	msgID		メッセージIDX
 *	@param	x			ｘ
 *	@param	y			ｙ
 *	@param	col			カラー
 *	@param	wait		ウエイト
 *	@param	pp_glb_str	グローバル文字列
 *
 *	@return	メッセージインデックス
 */
//-----------------------------------------------------------------------------
static s32 printBmp_NoWaku_Buff( GF_BGL_BMPWIN* bmp, int arcID, int dataID, int msgID, int x, int y, GF_PRINTCOLOR col, u32 wait, STRBUF** pp_glb_str )
{
	MSGDATA_MANAGER* msg_data;
	s32 msg_idx;

	GF_ASSERT( *pp_glb_str == NULL );

	// 文字列取得
	msg_data = MSGMAN_Create( MSGMAN_TYPE_NORMAL, arcID, dataID, HEAPID_IMAGECLIP_DATA );
	GF_ASSERT( msg_data );
	*pp_glb_str = MSGMAN_AllocString( msg_data, msgID );

	// 文字列書き込み
	msg_idx = GF_STR_PrintColor( bmp, FONT_TALK, *pp_glb_str, x, y, wait, col, NULL );
												// ↑描画位置
	MSGMAN_Delete( msg_data );

	return msg_idx;
}

//----------------------------------------------------------------------------
/**
 *	@brief	アクセサリアイコンワーク初期化
 *
 *	@param	p_data		アクセサリアイコンワーク
 *	@param	clact_set	セルアクターセット
 *	@param	p_res_man	リソースマネージャ
 *	@param	acce_max	アクセサリ最大数
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void initAcceIconWork( IMC_SUBWIN_ACCEICON* p_data, CLACT_SET_PTR clact_set, CLACT_U_RES_MANAGER_PTR* p_res_man, int acce_max )
{
	CLACT_HEADER			clact_head;
	CLACT_ADD_SIMPLE		clact_add;
	int i, j;
	
	// リソース読み込み
	imcSubWin_DefaultClactResLoad( p_data->res_obj, p_res_man, HEAPID_IMAGECLIP_DRAW, ARC_IMAGECLIP_GRA, NARC_imageclip_imgclip_access_ma_00_NCGR, NARC_imageclip_imgclip_top_00_NCLR, NARC_imageclip_imgclip_access_ma_00_NCER, NARC_imageclip_imgclip_access_ma_00_NANR, 2, IMC_SUBWIN_ACCEICON_RES_ID );

	// ヘッダー作成
	imcSubWin_DefaultClactHeaderMake( p_data->res_obj, p_res_man, &clact_head, 0 );
	
	// アクター登録
	clact_add.ClActSet		= clact_set;
	clact_add.ClActHeader	= &clact_head;
	clact_add.DrawArea		= NNS_G2D_VRAM_TYPE_2DSUB;
	clact_add.pri			= 0;
	clact_add.heap			= HEAPID_IMAGECLIP_DRAW;


	for( i=0; i<IMC_SUBWIN_ACCEICON_Y_NUM; i++ ){
		clact_add.mat.y = IMC_SUBWIN_ACCEICON_Y_DEF	+ (IMC_SUBWIN_ACCEICON_Y_OFS * i);
		clact_add.mat.y *= FX32_ONE;
		clact_add.mat.y += IMC_CLACT_SUB_SURFACE_Y;

		for( j=0; j<IMC_SUBWIN_ACCEICON_X_NUM; j++ ){
			
			clact_add.mat.x = IMC_SUBWIN_ACCEICON_X_DEF	+ (IMC_SUBWIN_ACCEICON_X_OFS * j);
			clact_add.mat.x *= FX32_ONE;

			p_data->icon[ (i*IMC_SUBWIN_ACCEICON_X_NUM)+j ] = CLACT_AddSimple( &clact_add );
			CLACT_AnmChg( p_data->icon[ (i*IMC_SUBWIN_ACCEICON_X_NUM)+j ], IMC_SUBWIN_ACCEICON_ANM_OFF );

			// 最大数以上の場合はOFF
			if( ((i*IMC_SUBWIN_ACCEICON_X_NUM)+j) >= acce_max ){
				CLACT_SetDrawFlag( p_data->icon[ (i*IMC_SUBWIN_ACCEICON_X_NUM)+j ], FALSE );
			}
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	アイコンワークの描画データ設定
 *
 *	@param	p_data		ワーク
 *	@param	acce_num	アクセサリ保持数
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void setAcceIconWork( IMC_SUBWIN_ACCEICON* p_data, int acce_num )
{
	int i;

	if( p_data->acce_num < acce_num ){
		
		for( i=p_data->acce_num; i<acce_num; i++ ){
			CLACT_AnmChg( p_data->icon[ i ], IMC_SUBWIN_ACCEICON_ANM_ON );
		}

		
	}else if( p_data->acce_num > acce_num ){
		
		for( i=p_data->acce_num-1; i>=acce_num; i-- ){
			CLACT_AnmChg( p_data->icon[ i ], IMC_SUBWIN_ACCEICON_ANM_OFF );
		}
	} 

	p_data->acce_num = acce_num;
}

//----------------------------------------------------------------------------
/**
 *	@brief	アイコンワーク破棄
 *
 *	@param	p_data		描画ワーク
 *	@param	p_res_man	リソースマネージャ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void deleteAcceIconWork( IMC_SUBWIN_ACCEICON* p_data, CLACT_U_RES_MANAGER_PTR* p_res_man )
{
	int i;
	// アクター破棄
	for( i=0; i<IMC_SUBWIN_ACCECOUNT_ICON_MAX; i++ ){
		CLACT_Delete( p_data->icon[i] );
	}

	// リソース破棄
	imcSubWin_DefaultClactResDelete( p_data->res_obj, p_res_man );
}


//----------------------------------------------------------------------------
/**
 *	@brief	基本的なアクターリソース読み込み関数
 *
 *	@param	p_res_obj		リソースオブジェ
 *	@param	pp_res_manager	リソースマネージャ
 *	@param	heap			ヒープ
 *	@param	charidx			キャラクタデータインデックス
 *	@param	plttidx			パレットデータインデックス
 *	@param	cellidx			セルデータインデックス
 *	@param	cellanmidx		セルアニメインデックス
 *	@param	plttload_num	パレット読み込み本数
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void imcSubWin_DefaultClactResLoad( CLACT_U_RES_OBJ_PTR* p_res_obj, CLACT_U_RES_MANAGER_PTR* pp_res_manager, int heap, int arc_idx, int charidx, int plttidx, int cellidx, int cellanmidx, int plttload_num, int common_res_id )
{
	// キャラクタデータ読み込み
	p_res_obj[ CLACT_U_CHAR_RES ] = CLACT_U_ResManagerResAddArcChar( 
			pp_res_manager[ CLACT_U_CHAR_RES ], arc_idx,
			charidx, FALSE,
			common_res_id + charidx,
			NNS_G2D_VRAM_TYPE_2DSUB, heap );
	// 転送
	CLACT_U_CharManagerSetAreaCont( p_res_obj[ CLACT_U_CHAR_RES ] );
	// グラフィックデータだけ破棄
	CLACT_U_ResManagerResOnlyDelete( p_res_obj[ CLACT_U_CHAR_RES ] );

	// パレットデータ読み込み
	p_res_obj[ CLACT_U_PLTT_RES ] = CLACT_U_ResManagerResAddArcPltt( 
			pp_res_manager[ CLACT_U_PLTT_RES ], arc_idx,
			plttidx, FALSE, 
			common_res_id + plttidx,
			NNS_G2D_VRAM_TYPE_2DSUB, 
			plttload_num, heap );
	// 転送
	CLACT_U_PlttManagerSetCleanArea( p_res_obj[ CLACT_U_PLTT_RES ] );	
	// グラフィックデータだけ破棄
	CLACT_U_ResManagerResOnlyDelete( p_res_obj[ CLACT_U_PLTT_RES ] );


	// セルデータ読み込み
	p_res_obj[ CLACT_U_CELL_RES ] = CLACT_U_ResManagerResAddArcKindCell(
			pp_res_manager[ CLACT_U_CELL_RES ], arc_idx,
			cellidx, FALSE,
			common_res_id + cellidx,
			CLACT_U_CELL_RES, heap );

	// セルアニメデータ読み込み
	p_res_obj[ CLACT_U_CELLANM_RES ] = CLACT_U_ResManagerResAddArcKindCell(
			pp_res_manager[ CLACT_U_CELLANM_RES ], arc_idx, 
			cellanmidx, FALSE,
			common_res_id + cellanmidx,
			CLACT_U_CELLANM_RES, heap );
}


//----------------------------------------------------------------------------
/**
 *	@brief	基本的なリソース破棄
 *
 *	@param	p_res_obj		リソースオブジェ	
 *	@param	pp_res_manager	リソースマネージャ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void imcSubWin_DefaultClactResDelete( CLACT_U_RES_OBJ_PTR* p_res_obj, CLACT_U_RES_MANAGER_PTR* pp_res_manager )
{
	CLACT_U_CharManagerDelete( p_res_obj[ CLACT_U_CHAR_RES ] );
	CLACT_U_PlttManagerDelete( p_res_obj[ CLACT_U_PLTT_RES ] );

	// リソース破棄
	CLACT_U_ResManagerResDelete( 
			pp_res_manager[ CLACT_U_CHAR_RES ],
			p_res_obj[ CLACT_U_CHAR_RES ] );
	CLACT_U_ResManagerResDelete( 
			pp_res_manager[ CLACT_U_PLTT_RES ],
			p_res_obj[ CLACT_U_PLTT_RES ] );
	CLACT_U_ResManagerResDelete( 
			pp_res_manager[ CLACT_U_CELL_RES ],
			p_res_obj[ CLACT_U_CELL_RES ] );
	CLACT_U_ResManagerResDelete( 
			pp_res_manager[ CLACT_U_CELLANM_RES ],
			p_res_obj[ CLACT_U_CELLANM_RES ] );
}

//----------------------------------------------------------------------------
/**
 *	@brief	セルアクターヘッダーデータ作成
 *
 *	@param	p_res_obj			リソースオブジェ
 *	@param	pp_res_manager		リソースマネージャ
 *	@param	p_head				ヘッダーワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void imcSubWin_DefaultClactHeaderMake( CLACT_U_RES_OBJ_PTR* p_res_obj, CLACT_U_RES_MANAGER_PTR* pp_res_manager, CLACT_HEADER* p_head, int bg_pri )
{
	
	// 各ボタンを登録
	// アクターヘッダー作成
	CLACT_U_MakeHeader( p_head,
			CLACT_U_ResManagerGetResObjID( p_res_obj[ CLACT_U_CHAR_RES ] ),
			CLACT_U_ResManagerGetResObjID( p_res_obj[ CLACT_U_PLTT_RES ] ),
			CLACT_U_ResManagerGetResObjID( p_res_obj[ CLACT_U_CELL_RES ] ),
			CLACT_U_ResManagerGetResObjID( p_res_obj[ CLACT_U_CELLANM_RES ] ),
			CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE, 0, bg_pri,
			pp_res_manager[ CLACT_U_CHAR_RES ],
			pp_res_manager[ CLACT_U_PLTT_RES ],
			pp_res_manager[ CLACT_U_CELL_RES ],
			pp_res_manager[ CLACT_U_CELLANM_RES ],
			NULL, NULL );
}

//----------------------------------------------------------------------------
/**
 *	@brief	カウンターワークの初期化	作成
 *
 *	@param	p_data		データ格納先
 *	@param	clact_set	セルアクターセット
 *	@param	p_res_man	リソースマネージャ
 *	@param	count_max	カウンター最大値
 *	@param	p_bgini		BGコントロールデータ
 *	@param	p_comm_data	通信データ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void InitCounterWork( IMC_SUBWIN_TIMECOUNT* p_data, CLACT_SET_PTR clact_set, CLACT_U_RES_MANAGER_PTR* p_res_man, int count_max, GF_BGL_INI* p_bgini,  CON_IMC_LOCAL* p_comm_data)
{
	CLACT_HEADER head;
	CLACT_ADD_SIMPLE add;
	int i;
	
	// グラフィックデータ読み込み
	imcSubWin_DefaultClactResLoad( p_data->res_obj, p_res_man, HEAPID_IMAGECLIP_DRAW, ARC_IMAGECLIP_GRA, NARC_imageclip_imgclip_top_num00_NCGR, NARC_imageclip_imgclip_top_num00_NCLR, NARC_imageclip_imgclip_top_num00_NCER, NARC_imageclip_imgclip_top_num00_NANR, 2, IMC_SUBWIN_TIMENUM_RES_ID );

	// ヘッダー作成
	imcSubWin_DefaultClactHeaderMake( p_data->res_obj, p_res_man, &head, 0 );

	// アクター登録
	add.ClActSet	= clact_set;
	add.ClActHeader	= &head;
	add.DrawArea	= NNS_G2D_VRAM_TYPE_2DSUB;
	add.pri			= 0;
	add.heap		= HEAPID_IMAGECLIP_DRAW;

	add.mat.y = IMC_SUBWIN_NUM_DEFY * FX32_ONE;
	add.mat.y += IMC_CLACT_SUB_SURFACE_Y;
	for( i=0; i<IMC_SUBWIN_NUM_KETA; i++ ){
		add.mat.x = IMC_SUBWIN_NUM_DEFX + (i*IMC_SUBWIN_NUM_OFSX);
		add.mat.x *= FX32_ONE;
		p_data->num[ i ] = CLACT_AddSimple( &add );
	}
	
	p_data->count = count_max;
	p_data->master_count = count_max * IMC_SUBWIN_NUM_ONE_SYNC;
	p_data->p_comm_data = p_comm_data;


	p_data->p_comm_data->recieve_sio.counter = count_max;
	p_data->p_comm_data->trans_sio.counter = count_max;

	p_data->pal_chg = FALSE;

	// ｶｳﾝﾀの値のデータをワークに設定
	setCounterClactAnm( p_data );

	// あと　　びゅう　を描画
	initBmp( &p_data->bmp, p_bgini, 
			IMC_SUBWIN_COUNTBMP_X, IMC_SUBWIN_COUNTBMP_Y,
			IMC_SUBWIN_COUNTBMP_SIZE_X, IMC_SUBWIN_COUNTBMP_SIZE_Y,
			TALK_WIN_CGX_SIZ + IMC_SUBWIN_COUNTBMP_FRAME_CHAR_OFS,
			FALSE );

	GF_BGL_BmpWinDataFill( p_data->bmp, 0 );
	printBmp_NoWaku( p_data->bmp, ARC_MSG, NARC_msg_imageclip_dat,imgclip_subwin_count00_01, IMC_SUBWIN_NUM_BMP_DRAW_XDEF, IMC_SUBWIN_NUM_BMP_DRWA_YDEF, GF_PRINTCOLOR_MAKE(1,2,0), MSG_NO_PUT );
	printBmp_NoWaku( p_data->bmp, ARC_MSG, NARC_msg_imageclip_dat, imgclip_subwin_count01, IMC_SUBWIN_NUM_BMP_DRAW_XDEF+IMC_SUBWIN_NUM_BMP_DRAW_XOFS, IMC_SUBWIN_NUM_BMP_DRWA_YDEF, GF_PRINTCOLOR_MAKE(1,2,0), MSG_NO_PUT );
	GF_BGL_BmpWinOn( p_data->bmp );
}

//----------------------------------------------------------------------------
/**
 *	@brief	カウンターデータの破棄
 *
 *	@param	p_data		ワーク
 *	@param	p_res_man	リソースマネージャ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void deleteCounterWork( IMC_SUBWIN_TIMECOUNT* p_data, CLACT_U_RES_MANAGER_PTR* p_res_man )
{
	// タスク破棄
	if( p_data->CountTCB ){
		TCB_Delete( p_data->CountTCB );
	}
	if( p_data->MstTransTCB ){
		TCB_Delete( p_data->MstTransTCB );
	}

	// リソース破棄
	imcSubWin_DefaultClactResDelete( p_data->res_obj, p_res_man );

	// BMP破棄
	deleteBmp( p_data->bmp );

	memset( p_data, 0, sizeof(IMC_SUBWIN_TIMECOUNT) );
}

//----------------------------------------------------------------------------
/**
 *	@brief	カウンターデータのメイン
 *
 *	@param	p_data	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void mainCounterWork( IMC_SUBWIN_TIMECOUNT* p_data )
{
	u32 num;
	
	// カウントダウン
	countDownCounterData( p_data );

	num = p_data->master_count / IMC_SUBWIN_NUM_ONE_SYNC;

	// 転送
	CommContestSendImcLocal( p_data->p_comm_data, num );

	// 受信処理
	popCounterData( p_data );

	// ｶｳﾝﾀの値のデータをワークに設定
	setCounterClactAnm( p_data );

	// カウントｴﾌｪｸﾄメイン処理
	mainCounterEffect( &p_data->counter_eff );
}

//----------------------------------------------------------------------------
/**
 *	@brief	カウンターデータの受信処理
 *
 *	@param	p_data	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void popCounterData( IMC_SUBWIN_TIMECOUNT* p_data )
{
	if( p_data->count != p_data->p_comm_data->recieve_sio.counter ){
		// 受信
		p_data->count = p_data->p_comm_data->recieve_sio.counter;

		if( p_data->count <= IMC_SUBWIN_NUM_PLTT_CHG ){
			//アニメ
			initCounterEffect( p_data, &p_data->counter_eff );

			// 音を鳴らす
			Snd_SePlay( IMC_SE_CON_10COUNT );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	セルアクターの描画を　カウント値にあわせる
 *
 *	@param	p_data	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void setCounterClactAnm( IMC_SUBWIN_TIMECOUNT* p_data )
{
	int i;
	int num;
	int count = p_data->count;
	int keta_num;

	// 桁の値をアクターに設定
	keta_num = 1;
	for( i=1; i<IMC_SUBWIN_NUM_KETA; i++ ){
		keta_num *= 10;
	}
	for( i=0; i<IMC_SUBWIN_NUM_KETA; i++ ){
		num = count / keta_num;
		GF_ASSERT( num <= 10 );

		CLACT_AnmChg( p_data->num[i], IMC_SUBWIN_NUM_SEQ_00 + num );
		count -= num*keta_num;
		keta_num /= 10;

		// 色を変える
		if( p_data->pal_chg == FALSE ){
			if( p_data->count <= IMC_SUBWIN_NUM_PLTT_CHG ){
				CLACT_PaletteNoChgAddTransPlttNo( p_data->num[i], 1 );	

				if( i == IMC_SUBWIN_NUM_KETA - 1 ){
					p_data->pal_chg = TRUE;
				}
			}
		}
	}

}

//----------------------------------------------------------------------------
/**
 *	@brief	ﾏｽﾀｰｶｳﾝﾀ　カウントダウン関数
 *
 *	@param	p_data		ワーク
 *
 *	@retval	TRUE	値が変わった
 *	@retval	FALSE	値が変わらなかった
 */
//-----------------------------------------------------------------------------
static void countDownCounterData( IMC_SUBWIN_TIMECOUNT* p_data )
{
	if( (p_data->master_count - 1) >= 0 ){
		p_data->master_count --;
	}
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
static void imc_UTIL_MoveReq( IMC_SUBWIN_MOVE_WORK* p_work, fx32 s_x, fx32 e_x, int count_max )
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
static BOOL	imc_UTIL_MoveMain( IMC_SUBWIN_MOVE_WORK* p_work )
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
 *	@brief	カウンター用ｴﾌｪｸﾄの初期化
 *
 *	@param	p_data			カウンターワーク
 *	@param	effect_work		ｴﾌｪｸﾄワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void initCounterEffect( IMC_SUBWIN_TIMECOUNT* p_data, IMC_SUBWIN_TIME_EFFECT* effect_work )
{
	int i;
	fx32 scale_start;
	fx32 move_x, move_y;
	VecFx32 get_mat;
	int count;

	get_mat.y = IMC_SUBWIN_NUM_DEFY * FX32_ONE;
	get_mat.y += IMC_CLACT_SUB_SURFACE_Y;
	for( i=0; i<IMC_SUBWIN_NUM_KETA; i++ ){
		effect_work->num[i] = p_data->num[i];
		CLACT_SetAffineParam( effect_work->num[i], CLACT_AFFINE_DOUBLE );
		get_mat.x = IMC_SUBWIN_NUM_DEFX + (i*IMC_SUBWIN_NUM_OFSX);
		get_mat.x *= FX32_ONE;
		effect_work->mat[i] = get_mat;
	}

	// 開始拡縮値を求める
	count = IMC_SUBWIN_NUM_PLTT_CHG - p_data->count;
	
	if( count > 0 ){
		scale_start = IMC_SUBWIN_NUM_EFFE_SCAL_DEF + FX_Mul( count<< FX32_SHIFT, IMC_SUBWIN_NUM_EFFE_SCAL_OFS);
	}else{
		scale_start = IMC_SUBWIN_NUM_EFFE_SCAL_DEF;
	}
	
	imc_UTIL_MoveReq( &effect_work->scale, scale_start, IMC_SUBWIN_NUM_EFFE_SCAL_END, IMC_SUBWIN_NUM_EFFE_COUNT_MAX );

	// 開始拡縮値からX動作値Y動作値を求める
	move_x = FX_Mul( IMC_SUBWIN_NUM_SIZE_X, scale_start );
	move_y = FX_Mul( IMC_SUBWIN_NUM_SIZE_Y, scale_start );
	move_x = move_x - IMC_SUBWIN_NUM_SIZE_X;
	move_y = move_y - IMC_SUBWIN_NUM_SIZE_Y;
	imc_UTIL_MoveReq( &effect_work->x, move_x, 0, IMC_SUBWIN_NUM_EFFE_COUNT_MAX );
	imc_UTIL_MoveReq( &effect_work->y, move_y, 0, IMC_SUBWIN_NUM_EFFE_COUNT_MAX );

	// 初期化済み
	effect_work->init_flg = TRUE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	カウンターｴﾌｪｸﾄメイン動作
 *
 *	@param	effect_work		ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void mainCounterEffect( IMC_SUBWIN_TIME_EFFECT* effect_work )
{
	VecFx32	scale;
	VecFx32 mat;
	BOOL check;
	if( effect_work->init_flg == FALSE ){
		return ;
	}

	// 動作
	check = imc_UTIL_MoveMain( &effect_work->scale );	
	imc_UTIL_MoveMain( &effect_work->x );	
	imc_UTIL_MoveMain( &effect_work->y );	

	// 拡縮値設定
	scale.x = effect_work->scale.x;
	scale.y = effect_work->scale.x;
	scale.z = effect_work->scale.x;
	CLACT_SetScale( effect_work->num[0], &scale );
	CLACT_SetScale( effect_work->num[1], &scale );

	// 座標設定
	mat = effect_work->mat[0];
	mat.x -= effect_work->x.x;
	mat.y -= effect_work->y.x;
	CLACT_SetMatrix( effect_work->num[0], &mat );
	mat = effect_work->mat[1];
	mat.y -= effect_work->y.x;
	CLACT_SetMatrix( effect_work->num[1], &mat );

	// 終了
	if( check ){
		effect_work->init_flg = FALSE;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	カウンターｴﾌｪｸﾄ動作チェック
 *
 *	@param	cp_effect_work	ワーク
 *
 *	@retval	TRUE	終了
 *	@retval	FALSE	途中
 */
//-----------------------------------------------------------------------------
static BOOL checkCounterEffectEnd( const IMC_SUBWIN_TIME_EFFECT* cp_effect_work )
{
	if( cp_effect_work->init_flg == TRUE ){
		return FALSE;
	}
	return TRUE;
}


#ifdef PM_DEBUG
void IMC_SUBWIN_DEBUG_SetBmpWin( IMC_SUBWIN* p_data, int msgID_1, int msgID_2 )
{
	GF_ASSERT_MSG( (p_data->init_flg & IMC_SUBWIN_INITMASK_BMP), "バンプウィンドウが初期化されていません" )

	GF_BGL_BmpWinDataFill( p_data->bmp, 15 );
	printBmp_NoWaku( p_data->bmp, ARC_MSG, NARC_msg_debug_tomoya_dat, msgID_1, 0, 0, GF_PRINTCOLOR_MAKE(1,2,15), MSG_NO_PUT );
	printBmp_NoWaku( p_data->bmp, ARC_MSG, NARC_msg_debug_tomoya_dat, msgID_2, 64, 0, GF_PRINTCOLOR_MAKE(1,2,15), MSG_NO_PUT );
	GF_BGL_BmpWinOn( p_data->bmp );
}
void IMC_SUBWIN_DEBUG_CountTimeSet( IMC_SUBWIN* p_data, int num )
{
	p_data->counter.master_count = num;
}
#endif
