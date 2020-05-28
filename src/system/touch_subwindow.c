//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		touch_subwindow.c
 *	@brief		サブ画面　触れるウィンドウボタンシステム
 *	@author		tomoya takahashi
 *	@data		2006.03.23
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "system.h"
#include "assert.h"
#include <string.h>

#include "include/gflib/button_man.h"

#include "include/system/arc_tool.dat"
#include "include/system/arc_util.h"
#include "include/system/touch_subwindow.naix"

#include "include/system/snd_tool.h"

#define __TOUCH_SUBWINDOW_H_GLOBAL 
#include "include/system/touch_subwindow.h"

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
// 各バッファ・ワークの数
enum{		
	TOUCH_SW_BUF_YES,
	TOUCH_SW_BUF_NO,
	TOUCH_SW_BUF_NUM,


	TOUCH_SW_BUF_NO_TOUCH,	// タッチされたかチェック時の触っていない定数
};
#define TOUCH_SW_Y_OFS	( 32 )	// NOの方のオフセット

// アニメーション関係
#define TOUCH_SW_ANIME_NUM		( 4 )		// アニメーション数
#define TOUCH_SW_ANIME_SP		( FX32_ONE )// アニメスピード
#define TOUCH_SW_ANIME_TIMING	( FX32_ONE * 1 )

// 今のワーク内の状態
enum{
	TOUCH_SW_PARAM_NODATA,	// 空
	TOUCH_SW_PARAM_DO,		// 実行データ格納
};

// VRAM転送タスク
#define TOUCH_SW_VRAM_TRANS_TSK_PRI	( 128 )

#define TOUCH_FLG_INIT	( 0x8 )


//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	アニメデータ
//=====================================
typedef struct {
	const fx32* cp_anime_tbl;
	u32 tbl_num;
	fx32 frame;
} TOUCH_SW_ANIME;


//-------------------------------------
//	ボタンデータ初期化データ
//=====================================
typedef struct {
	GF_BGL_INI* ini;
	u32 bg_frame;			// BGナンバー
	u32 fileidx;	// アーカイブファイル
	u32 scrn_arcidx[ TOUCH_SW_ANIME_NUM ];	// スクリーンデータ
	u32 char_offs;	// キャラクタオフセット
	u32 pltt_offs;	// パレットオフセット
	const fx32* cp_anime_tbl;	// アニメテーブル
	u32 tbl_num;				// テーブル数
	u8 ofs_x;		// ｘ
	u8 ofs_y;		// ｙ
} TOUCH_SW_BUTTON_PARAM;

//-------------------------------------
//	1ボタンデータ
//=====================================
typedef struct {
	GF_BGL_INI* ini;
	u32 bg_frame;			// BGナンバー
	void* p_scrn_buff[ TOUCH_SW_ANIME_NUM ];		// スクリーンバッファ
	NNSG2dScreenData* p_scrn[ TOUCH_SW_ANIME_NUM ];	// スクリーンデータ
	TOUCH_SW_ANIME anime;
	u8 ofs_x;	// ｘ座標
	u8 ofs_y;	// ｙ座標
	u8 anm_idx;	// 今の反映されているスクリーンIDX
	u8 dummy1;
} TOUCH_SW_BUTTON;

//-------------------------------------
//	キャラクタデータ転送タスク
//=====================================
typedef struct {
	GF_BGL_INI* ini;
	NNSG2dCharacterData* p_char;
	void* p_buff;	
	int bg_frame;
	int char_ofs;
} TOUCH_SW_CHARACTER_TRANS;

//-------------------------------------
//	Vブランク　パレットデータ転送タスク
//=====================================
typedef struct {
	NNSG2dPaletteData* p_pltt;
	void* p_buff;	
	int pltype;	// パレット転送先
	int ofs;
	int size;
} TOUCH_SW_PALETTE_TRANS;


//-------------------------------------
//	システムワーク
//=====================================
typedef struct _TOUCH_SW_SYS{
	BUTTON_MAN* p_button_man;// ボタンマネージャ
	TP_HIT_TBL hit_tbl[ TOUCH_SW_BUF_NUM ];		// ボタンデータ
	TOUCH_SW_BUTTON button[ TOUCH_SW_BUF_NUM ];	// ボタンデータ
	GF_BGL_INI* p_bgl;		// BGLシステムワーク
	u32 bg_frame;			// BGナンバー
	u32 heapid;				// 使用ヒープID
	fx32 anime_tbl[ TOUCH_SW_ANIME_NUM ];	// アニメテーブル
	u8 x;					// x座標（ｷｬﾗｸﾀ単位）
	u8 y;					// y座標（ｷｬﾗｸﾀ単位）
	u8 button_move_flag;	// ボタン動作フラグ
	u8 now_work_param : 4;	// 現在のワーク内の状態
	u8 touch_flg: 4;		// タッチした瞬間感知
};


//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
static void TouchSW_CleanWork( TOUCH_SW_SYS* p_touch_sw, u32 heapid );

//-------------------------------------
//	ある程度処理をまとめた関数
//=====================================
static void TouchSW_SYS_CharTrans( TOUCH_SW_SYS* p_touch_sw, const TOUCH_SW_PARAM* cp_param );
static void TouchSW_SYS_PlttTrans( TOUCH_SW_SYS* p_touch_sw, const TOUCH_SW_PARAM* cp_param );
static void TouchSW_SYS_ButtonInit( TOUCH_SW_SYS* p_touch_sw, const TOUCH_SW_PARAM* cp_param );
static void TouchSW_SYS_ButtonManaInit( TOUCH_SW_SYS* p_touch_sw, const TOUCH_SW_PARAM* cp_param );

//-------------------------------------
//	ボタン動作システム
//=====================================
static void TouchSW_ButtonCallBack( u32 button_no, u32 event, void* p_work );

//-------------------------------------
//	ボタンワーク操作関数郡
//=====================================
static void TouchSW_ButtonInit( TOUCH_SW_BUTTON* p_bttn, const TOUCH_SW_BUTTON_PARAM* cp_param, u32 heapid );
static BOOL TouchSW_ButtonMain( TOUCH_SW_BUTTON* p_bttn );
static void TouchSW_ButtonDelete( TOUCH_SW_BUTTON* p_bttn );
static void TouchSW_FrameScrnSet( TOUCH_SW_BUTTON* p_bttn );


//-------------------------------------
//	アニメデータ操作関数
//=====================================
static void TouchSW_AnimeInit( TOUCH_SW_ANIME* p_anime, const fx32* cp_anime_tbl, u32 tbl_num );
static void TouchSW_AnimeAdd( TOUCH_SW_ANIME* p_anime, fx32 frame );
static void TouchSW_AnimeSet( TOUCH_SW_ANIME* p_anime, fx32 frame );
static fx32 TouchSW_AnimeGet( const TOUCH_SW_ANIME* cp_anime );
static u32 TouchSW_AnimeIdxGet( const TOUCH_SW_ANIME* cp_anime );

//-------------------------------------
//	キャラクタデータ　パレットデータ転送
//=====================================
static void TouchSW_CharTransReq( u32 fileIdx, u32 dataIdx, GF_BGL_INI* bgl, u32 frm, u32 offs, u32 heapID );
static void TouchSW_PlttTransReq( u32 fileIdx, u32 dataIdx, PALTYPE palType, u32 offs, u32 transSize, u32 heapID );
static void TouchSW_CharTransTsk( TCB_PTR tcb, void* p_work );
static void TouchSW_PlttTransTsk( TCB_PTR tcb, void* p_work );


//-------------------------------------
//	スクリーンの反映を行う
//=====================================
static void TouchSW_ScrnSet( GF_BGL_INI* bg_ini, int frame, const NNSG2dScreenData* scrn, int x, int y );
static void TouchSW_ScrnCharOfsSet( const NNSG2dScreenData* scrn, int char_offs );
static void TouchSW_ScrnPlttOfsSet( const NNSG2dScreenData* scrn, int pltt_offs );

//----------------------------------------------------------------------------
/**
 *	@brief	システムワーク作成
 *	
 *	@param	heapid	使用ヒープID 
 *	
 *	@return	ワークポインタ
 */
//-----------------------------------------------------------------------------
TOUCH_SW_SYS* TOUCH_SW_AllocWork( u32 heapid )
{
	TOUCH_SW_SYS* p_touch_sw;
	p_touch_sw = sys_AllocMemory( heapid, sizeof(TOUCH_SW_SYS) );

	// ワーク初期化
	TouchSW_CleanWork( p_touch_sw, heapid );

	return p_touch_sw;
}

//----------------------------------------------------------------------------
/**
 *	@brief	システムワーク破棄
 *	
 *	@param	p_touch_sw	システムワーク
 */
//-----------------------------------------------------------------------------
void TOUCH_SW_FreeWork( TOUCH_SW_SYS* p_touch_sw )
{
	// 実行データ格納済みならリセット
	if( p_touch_sw->now_work_param == TOUCH_SW_PARAM_DO ){
		TOUCH_SW_Reset( p_touch_sw );
	}
	sys_FreeMemoryEz( p_touch_sw );
}

//----------------------------------------------------------------------------
/**
 *	@brief	システム初期化
 *
 *	@param	p_touch_sw	システムワーク
 *	@param	cp_param	システム動作データ
 */
//-----------------------------------------------------------------------------
void TOUCH_SW_Init( TOUCH_SW_SYS* p_touch_sw, const TOUCH_SW_PARAM* cp_param )
{
	
	// データ格納
	p_touch_sw->p_bgl		= cp_param->p_bgl;
	p_touch_sw->bg_frame	= cp_param->bg_frame;
	p_touch_sw->x			= cp_param->x;
	p_touch_sw->y			= cp_param->y;

	// キャラクタデータ転送
	TouchSW_SYS_CharTrans( p_touch_sw, cp_param );

	// パレットデータ転送
	TouchSW_SYS_PlttTrans( p_touch_sw, cp_param );
	
	// ボタンデータ初期化
	TouchSW_SYS_ButtonInit( p_touch_sw, cp_param );

	// ボタンマネージャ初期化
	TouchSW_SYS_ButtonManaInit( p_touch_sw, cp_param );

	// 実行データ保持
	p_touch_sw->now_work_param = TOUCH_SW_PARAM_DO;

	// タッチフラグ
	p_touch_sw->touch_flg = TOUCH_FLG_INIT;
}

//----------------------------------------------------------------------------
/**
 *	@brief	システムメイン動作
 *
 *	@param	p_touch_sw	システムワーク
 *
 *	@retval	TOUCH_SW_RET_NORMAL	// 何もなし
 *	@retval	TOUCH_SW_RET_YES	// はい
 *	@retval	TOUCH_SW_RET_NO	// いいえ
 *	@retval	TOUCH_SW_RET_YES_TOUCH	// はい押した瞬間
 *	@retval	TOUCH_SW_RET_NO_TOUCH	// いいえ押した瞬間
 */
//-----------------------------------------------------------------------------
u32 TOUCH_SW_MainMC( TOUCH_SW_SYS* p_touch_sw )
{
	u32 ret;

	// タッチフラグ初期化
	p_touch_sw->touch_flg = TOUCH_FLG_INIT;

	ret = TOUCH_SW_Main( p_touch_sw );

	// 押された瞬間も返す
	if( ret == TOUCH_SW_RET_NORMAL ){
		if( p_touch_sw->touch_flg == BMN_EVENT_TOUCH ){
			if( p_touch_sw->button_move_flag == TOUCH_SW_BUF_YES ){
				return TOUCH_SW_RET_YES_TOUCH;
			}else{
				return TOUCH_SW_RET_NO_TOUCH;
			}
		}
	}
	return ret;
}

//----------------------------------------------------------------------------
/**
 *	@brief	システムメイン動作
 *
 *	@param	p_touch_sw	システムワーク
 *
 *	@retval	TOUCH_SW_RET_NORMAL	// 何もなし
 *	@retval	TOUCH_SW_RET_YES	// はい
 *	@retval	TOUCH_SW_RET_NO		// いいえ
 */
//-----------------------------------------------------------------------------
u32 TOUCH_SW_Main( TOUCH_SW_SYS* p_touch_sw )
{
	BOOL check;
	
	// 実行データ設定済み
	GF_ASSERT( p_touch_sw->now_work_param == TOUCH_SW_PARAM_DO );
	
	// 触ったボタンが無いときはボタンマネージャを実行
	if( p_touch_sw->button_move_flag == TOUCH_SW_BUF_NO_TOUCH ){
		BMN_Main( p_touch_sw->p_button_man );
	}

	// ボタンを触っていたら触ったボタンを動作
	check = FALSE;
	if( p_touch_sw->button_move_flag != TOUCH_SW_BUF_NO_TOUCH ){

		check = TouchSW_ButtonMain( &p_touch_sw->button[ p_touch_sw->button_move_flag ] );
	}

	// アニメ終了のときははいかいいえがきまった
	if( check == TRUE ){
		if( p_touch_sw->button_move_flag == TOUCH_SW_BUF_YES ){
			return TOUCH_SW_RET_YES;
		}else{
			return TOUCH_SW_RET_NO;
		}
	}

	return TOUCH_SW_RET_NORMAL;
}

//----------------------------------------------------------------------------
/**
 *	@brief	システムデータリセット	(Initの前の状態にする　いらないかもしれない)
 *
 *	@param	p_touch_sw	システムワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void TOUCH_SW_Reset( TOUCH_SW_SYS* p_touch_sw )
{
	int i;
	
	// ボタンマネージャ破棄
	BMN_Delete( p_touch_sw->p_button_man );

	// ボタンデータ破棄
	for( i=0; i<TOUCH_SW_BUF_NUM; i++ ){
		TouchSW_ButtonDelete( &p_touch_sw->button[ i ] );
	}

	// ワーク初期化
	TouchSW_CleanWork( p_touch_sw, p_touch_sw->heapid );
}



//-----------------------------------------------------------------------------
/**
 *		static 関数
 */
//-----------------------------------------------------------------------------

//----------------------------------------------------------------------------
/**
 *	@brief	ワークの初期化
 *
 *	@param	p_touch_sw 
 *	@param	heapid
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void TouchSW_CleanWork( TOUCH_SW_SYS* p_touch_sw, u32 heapid )
{
	memset( p_touch_sw, 0, sizeof(TOUCH_SW_SYS) );

	p_touch_sw->now_work_param = TOUCH_SW_PARAM_NODATA;	// 空ID
	p_touch_sw->heapid = heapid;
	p_touch_sw->button_move_flag = TOUCH_SW_BUF_NO_TOUCH;
	p_touch_sw->touch_flg = TOUCH_FLG_INIT;
}


//----------------------------------------------------------------------------
/**
 *	@brief	キャラクタデータ転送処理
 *
 *	@param	p_touch_sw
 *	@param	cp_param 
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void TouchSW_SYS_CharTrans( TOUCH_SW_SYS* p_touch_sw, const TOUCH_SW_PARAM* cp_param )
{
	// キャラクタデータ転送
	TouchSW_CharTransReq( ARC_TOUCH_SUBWINDOW_GRA, NARC_touch_subwindow_yes_no_dutton_lzh_NCGR, 
			p_touch_sw->p_bgl, p_touch_sw->bg_frame, cp_param->char_offs,
			p_touch_sw->heapid );
	
}

//----------------------------------------------------------------------------
/**
 *	@brief	パレットデータ転送
 *
 *	@param	p_touch_sw
 *	@param	cp_param 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void TouchSW_SYS_PlttTrans( TOUCH_SW_SYS* p_touch_sw, const TOUCH_SW_PARAM* cp_param )
{
	u32 pal_type;
	if( p_touch_sw->bg_frame < GF_BGL_FRAME0_S ){
		pal_type = PALTYPE_MAIN_BG;
	}else{
		pal_type = PALTYPE_SUB_BG;
	}
	TouchSW_PlttTransReq( ARC_TOUCH_SUBWINDOW_GRA, NARC_touch_subwindow_yes_no_button_NCLR,
			pal_type,
			cp_param->pltt_offs * 32, TOUCH_SW_USE_PLTT_NUM * 32,
			p_touch_sw->heapid );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ボタンデータ初期化
 *
 *	@param	p_touch_sw
 *	@param	cp_param 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void TouchSW_SYS_ButtonInit( TOUCH_SW_SYS* p_touch_sw, const TOUCH_SW_PARAM* cp_param )
{
	int i,j;
	TOUCH_SW_BUTTON_PARAM bt_pr;

	// ボタンアニメデータ作成
	for( i=0; i<TOUCH_SW_ANIME_NUM; i++ ){
		p_touch_sw->anime_tbl[ i ] = TOUCH_SW_ANIME_TIMING * (i+1);
	}

	// ボタンデータ作成
	bt_pr.ini		= p_touch_sw->p_bgl;
	bt_pr.bg_frame	= p_touch_sw->bg_frame;
	bt_pr.fileidx	= ARC_TOUCH_SUBWINDOW_GRA;
	bt_pr.char_offs = cp_param->char_offs;
	bt_pr.pltt_offs	= cp_param->pltt_offs;
	bt_pr.cp_anime_tbl = p_touch_sw->anime_tbl;
	bt_pr.tbl_num	= TOUCH_SW_ANIME_NUM;
	bt_pr.ofs_x		= p_touch_sw->x;
	for( i=0; i<TOUCH_SW_BUF_NUM; i++ ){

		// スクリーンデータインデックスバッファ作成
		for( j=0; j<TOUCH_SW_ANIME_NUM; j++ ){
			bt_pr.scrn_arcidx[ j ] = NARC_touch_subwindow_yes_button01_lzh_NSCR + (j * TOUCH_SW_BUF_NUM) + i;
		}

		// Yオフセット値
		bt_pr.ofs_y = (i*(TOUCH_SW_Y_OFS/8)) + p_touch_sw->y;

		// パレットオフセット
		bt_pr.pltt_offs += i;

		// ボタン初期化
		TouchSW_ButtonInit( &p_touch_sw->button[i], &bt_pr, p_touch_sw->heapid );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	ボタンマネージャ初期化
 *
 *	@param	p_touch_sw
 *	@param	cp_param 
 *
 *	@return	
 */
//-----------------------------------------------------------------------------
static void TouchSW_SYS_ButtonManaInit( TOUCH_SW_SYS* p_touch_sw, const TOUCH_SW_PARAM* cp_param )
{
	int i;
	
	// ボタンあたり判定データ作成
	for( i=0; i<TOUCH_SW_BUF_NUM; i++ ){
		p_touch_sw->hit_tbl[ i ].rect.top	= (p_touch_sw->y*8) + (i*TOUCH_SW_Y_OFS);
		p_touch_sw->hit_tbl[ i ].rect.bottom = (p_touch_sw->y*8) + (i*TOUCH_SW_Y_OFS) + (TOUCH_SW_USE_SCRN_Y*8);
		p_touch_sw->hit_tbl[ i ].rect.left	= (p_touch_sw->x*8);
		p_touch_sw->hit_tbl[ i ].rect.right	= (p_touch_sw->x*8) + (TOUCH_SW_USE_SCRN_X*8);
	}
	
	p_touch_sw->p_button_man = BMN_Create( p_touch_sw->hit_tbl, TOUCH_SW_BUF_NUM, 
							TouchSW_ButtonCallBack, p_touch_sw, p_touch_sw->heapid );
}


//----------------------------------------------------------------------------
/**
 *	@brief	ボタンマネージャコールバック
 *
 *	@param	button_no
 *	@param	event
 *	@param	p_work 
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void TouchSW_ButtonCallBack( u32 button_no, u32 event, void* p_work )
{
	TOUCH_SW_SYS* p_touch_sw = p_work;

	p_touch_sw->touch_flg = event;

	if( event == BMN_EVENT_TOUCH ){	
		// 触ったボタン保存
		p_touch_sw->button_move_flag = button_no;

		Snd_SePlay( SE_TOUCH_SUB_WIN );
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	ボタンワーク初期化
 *
 *	@param	p_bttn		ボタンワーク
 *	@param	cp_param	ボタン初期化データ
 *	@param	heapid		ヒープID
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void TouchSW_ButtonInit( TOUCH_SW_BUTTON* p_bttn, const TOUCH_SW_BUTTON_PARAM* cp_param, u32 heapid )
{
	int i;
	
	// アニメデータ登録
	TouchSW_AnimeInit( &p_bttn->anime, cp_param->cp_anime_tbl, cp_param->tbl_num );

	// データ代入
	p_bttn->ini		= cp_param->ini;
	p_bttn->bg_frame= cp_param->bg_frame;
	p_bttn->ofs_x	= cp_param->ofs_x;
	p_bttn->ofs_y	= cp_param->ofs_y;

	// スクリーンワーク読み込み
	for( i=0; i<TOUCH_SW_ANIME_NUM; i++ ){
		p_bttn->p_scrn_buff[i] = ArcUtil_ScrnDataGet( cp_param->fileidx, cp_param->scrn_arcidx[i], 
				TRUE, &p_bttn->p_scrn[ i ], heapid );

		// キャラクタオフセットを設定
		TouchSW_ScrnCharOfsSet( p_bttn->p_scrn[ i ], cp_param->char_offs );
		// パレットオフセットを設定
		TouchSW_ScrnPlttOfsSet( p_bttn->p_scrn[ i ], cp_param->pltt_offs );
	}
	
	// スクリーンの反映を行う
	TouchSW_FrameScrnSet( p_bttn );
	p_bttn->anm_idx = 0;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ボタンワーク　動作	（アニメ）
 *
 *	@param	p_bttn		ボタンワーク
 *
 *	@retval	TRUE	ボタンのアニメが終了した	
 *	@retval	FALSE	ボタンのアニメ途中
 */
//-----------------------------------------------------------------------------
static BOOL TouchSW_ButtonMain( TOUCH_SW_BUTTON* p_bttn )
{
	u32 new_anime = TouchSW_AnimeIdxGet( &p_bttn->anime );
	
	// アニメを進め　最終アニメフレームに行ったら終わり
	if( p_bttn->anm_idx != new_anime ){
		TouchSW_FrameScrnSet( p_bttn );
		p_bttn->anm_idx = new_anime;

	}

	// アニメ終了検知
	if( new_anime == (p_bttn->anime.tbl_num - 1) ){
		return TRUE;
	}

	// アニメを進める
	TouchSW_AnimeAdd( &p_bttn->anime, TOUCH_SW_ANIME_SP );


	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ボタンデータ破棄
 *
 *	@param	p_bttn		ボタンワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void TouchSW_ButtonDelete( TOUCH_SW_BUTTON* p_bttn )
{
	int i;
	
	// スクリーン領域を初期化
	GF_BGL_ScrFill( p_bttn->ini, p_bttn->bg_frame, 0, 
			p_bttn->ofs_x, p_bttn->ofs_y,
			p_bttn->p_scrn[0]->screenWidth/8, p_bttn->p_scrn[0]->screenHeight/8, 0 );
	GF_BGL_LoadScreenV_Req( p_bttn->ini, p_bttn->bg_frame );

	// ワーク破棄
	for( i=0; i<TOUCH_SW_ANIME_NUM; i++ ){
		sys_FreeMemoryEz( p_bttn->p_scrn_buff[ i ] );
	}

	memset( p_bttn, 0, sizeof( TOUCH_SW_BUTTON ) );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ボタンのフレーム数のスクリーンを設定
 *
 *	@param	p_bttn		ボタンワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void TouchSW_FrameScrnSet( TOUCH_SW_BUTTON* p_bttn )
{
	u32 idx = TouchSW_AnimeIdxGet( &p_bttn->anime );

	TouchSW_ScrnSet( p_bttn->ini, p_bttn->bg_frame,
			p_bttn->p_scrn[ idx ], p_bttn->ofs_x, p_bttn->ofs_y );

}

//----------------------------------------------------------------------------
/**
 *	@brief	アニメデータ初期化
 *	
 *	@param	p_anime			アニメワーク
 *	@param	cp_anime_tbl	アニメテーブル
 *	@param	tbl_num			アニメテーブル数
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void TouchSW_AnimeInit( TOUCH_SW_ANIME* p_anime, const fx32* cp_anime_tbl, u32 tbl_num )
{
	p_anime->cp_anime_tbl	= cp_anime_tbl;
	p_anime->tbl_num		= tbl_num;
	p_anime->frame			= 0;
}

//----------------------------------------------------------------------------
/**
 *	@brief	アニメフレームを進める
 *
 *	@param	p_anime		アニメワーク
 *	@param	frame		フレーム数
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void TouchSW_AnimeAdd( TOUCH_SW_ANIME* p_anime, fx32 frame )
{
	p_anime->frame += frame;
}

//----------------------------------------------------------------------------
/**
 *	@brief	アニメフレームを設定する
 *
 *	@param	p_anime		アニメワーク
 *	@param	frame		フレーム数
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void TouchSW_AnimeSet( TOUCH_SW_ANIME* p_anime, fx32 frame )
{
	p_anime->frame = frame;
}

//----------------------------------------------------------------------------
/**
 *	@brief	アニメフレームを取得
 *
 *	@param	cp_anime	アニメワーク
 *
 *	@return	フレーム数	
 */
//-----------------------------------------------------------------------------
static fx32 TouchSW_AnimeGet( const TOUCH_SW_ANIME* cp_anime )
{
	return cp_anime->frame;
}

//----------------------------------------------------------------------------
/**
 *	@brief	現在のアニメインデックス数を取得
 *
 *	@param	cp_anime	アニメワーク
 *
 *	@return	アニメインデックス数	（何番目のスクリーンを表示するか）
 */
//-----------------------------------------------------------------------------
static u32 TouchSW_AnimeIdxGet( const TOUCH_SW_ANIME* cp_anime )
{
	int i;

	for( i=0; i<cp_anime->tbl_num; i++ ){

		//　そのインデックスの最後の値以下のときはそのインデックス
		if( cp_anime->cp_anime_tbl[ i ] >= cp_anime->frame ){
			return i;
		}
	}
	return cp_anime->tbl_num - 1;
}



//----------------------------------------------------------------------------
/**
 *	@brief	キャラクタデータ転送リクエスト
 *
 *	@param	fileIdx		アーカイブファイルインデックス
 *	@param	dataIdx		データインデックス
 *	@param	bgl			BGデータ
 *	@param	frm			ﾌﾚｰﾑナンバー
 *	@param	offs		オフセット
 *	@param	heapID		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void TouchSW_CharTransReq( u32 fileIdx, u32 dataIdx, GF_BGL_INI* bgl, u32 frm, u32 offs, u32 heapID )
{
	TOUCH_SW_CHARACTER_TRANS* p_tw;

	p_tw = sys_AllocMemory( heapID, sizeof(TOUCH_SW_CHARACTER_TRANS) );
	memset( p_tw, 0, sizeof(TOUCH_SW_CHARACTER_TRANS) );

	// キャラクタデータ読み込み
	p_tw->p_buff = ArcUtil_CharDataGet( fileIdx, dataIdx, TRUE, &p_tw->p_char, heapID );

	// 転送データ格納
	p_tw->ini = bgl;
	p_tw->bg_frame = frm;
	p_tw->char_ofs = offs;

	// タスク登録
	VWaitTCB_Add( TouchSW_CharTransTsk, p_tw, TOUCH_SW_VRAM_TRANS_TSK_PRI );
}

//----------------------------------------------------------------------------
/**
 *	@brief	パレットデータ転送リクエスト
 *
 *	@param	fileIdx		アーカイブファイルインデックス
 *	@param	dataIdx		データインデックス
 *	@param	palType		パレット転送先
 *	@param	offs		オフセット
 *	@param	transSize	転送size
 *	@param	heapID		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void TouchSW_PlttTransReq( u32 fileIdx, u32 dataIdx, PALTYPE palType, u32 offs, u32 transSize, u32 heapID )
{
	TOUCH_SW_PALETTE_TRANS* p_tw;

	p_tw = sys_AllocMemory( heapID, sizeof(TOUCH_SW_PALETTE_TRANS) );
	memset( p_tw, 0, sizeof(TOUCH_SW_PALETTE_TRANS) );

	// キャラクタデータ読み込み
	p_tw->p_buff = ArcUtil_PalDataGet( fileIdx, dataIdx, &p_tw->p_pltt, heapID );

	// 転送データ格納
	p_tw->pltype = palType;
	p_tw->ofs = offs;
	p_tw->size = transSize;

	// タスク登録
	VWaitTCB_Add( TouchSW_PlttTransTsk, p_tw, TOUCH_SW_VRAM_TRANS_TSK_PRI );
}

//----------------------------------------------------------------------------
/**
 *	@brief	キャラクタデータ転送タスク
 *
 *	@param	tcb
 *	@param	p_work 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void TouchSW_CharTransTsk( TCB_PTR tcb, void* p_work )
{
	TOUCH_SW_CHARACTER_TRANS* p_tw = p_work;


	DC_FlushRange( p_tw->p_char->pRawData, p_tw->p_char->szByte );
	GF_BGL_LoadCharacter( p_tw->ini, p_tw->bg_frame, 
			p_tw->p_char->pRawData, p_tw->p_char->szByte, p_tw->char_ofs );

	// メモリ解放
	TCB_Delete( tcb );
	sys_FreeMemoryEz( p_tw->p_buff );
	sys_FreeMemoryEz( p_tw );
}

//----------------------------------------------------------------------------
/**
 *	@brief	パレットデータ転送タスク
 *
 *	@param	tcb
 *	@param	p_work 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void TouchSW_PlttTransTsk( TCB_PTR tcb, void* p_work )
{
	TOUCH_SW_PALETTE_TRANS* p_tw = p_work;


	DC_FlushRange( p_tw->p_pltt->pRawData, p_tw->size );

	if( p_tw->pltype == PALTYPE_MAIN_BG ){
		GX_LoadBGPltt( p_tw->p_pltt->pRawData, p_tw->ofs, p_tw->size );
	}else if( p_tw->pltype == PALTYPE_SUB_BG ){
		GXS_LoadBGPltt( p_tw->p_pltt->pRawData, p_tw->ofs, p_tw->size );
	}

	// メモリ解放
	TCB_Delete( tcb );
	sys_FreeMemoryEz( p_tw->p_buff );
	sys_FreeMemoryEz( p_tw );
}

//----------------------------------------------------------------------------
/**
 *	@brief	スクリーンデータ転送
 *
 *	@param	bg_ini		BGシステムワーク
 *	@param	frame		BGナンバー
 *	@param	scrn		スクリーンワーク
 *	@param	x			ｘ座標
 *	@param	y			ｙ座標
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void TouchSW_ScrnSet( GF_BGL_INI* bg_ini, int frame, const NNSG2dScreenData* scrn, int x, int y )
{
	// 書きだし
	GF_BGL_ScrWriteExpand(
				bg_ini, frame,
				x, y,
				scrn->screenWidth / 8, scrn->screenHeight / 8,
				scrn->rawData,
				0, 0,
				scrn->screenWidth / 8, scrn->screenHeight / 8 );
	
	GF_BGL_LoadScreenV_Req(bg_ini, frame );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	スクリーンデータのキャラクタネームの値をオフセット分ずらす
 *
 *	@param	scrn			スクリーンデータ
 *	@param	char_offs		キャラクタオフセット	キャラクタ単位
 *
 *	@return	none
 *
 * キャラクタネーム最大値チェックをしていないので注意してください
 *
 */
//-----------------------------------------------------------------------------
static void TouchSW_ScrnCharOfsSet( const NNSG2dScreenData* scrn, int char_offs )
{
	int i;							// ループ用
	u16* scrndata;					// スクリーンデータ
	int size = scrn->szByte / 2;	// ループ回数	２=2byte
	
	// スクリーンデータ代入
	scrndata = (u16*)scrn->rawData;
	for(i=0; i<size; i++){

		scrndata[ i ] += char_offs;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	パレットオフセットをスクリーンバッファに設定
 *
 *	@param	scrn		スクリーンバッファ
 *	@param	pltt_offs	パレットオフセット	(パレット本数単位)
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void TouchSW_ScrnPlttOfsSet( const NNSG2dScreenData* scrn, int pltt_offs )
{
	int i;							// ループ用
	u16* scrndata;					// スクリーンデータ
	int size = scrn->szByte / 2;	// ループ回数	２=2byte
	
	// スクリーンデータ代入
	scrndata = (u16*)scrn->rawData;
	for(i=0; i<size; i++){

		scrndata[ i ] &= 0x0fff;
		scrndata[ i ] |= pltt_offs << 12;
	}
}
