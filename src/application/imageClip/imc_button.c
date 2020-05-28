//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		imc_button.c
 *	@brief		画面下のボタン制御システム
 *	@author		tomoya takahashi 
 *	@data		2005.10.08
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "include/system/clact_util.h"
#include "include/application/imageClip/imc_drawdata_define.h"
#include "msg_print.h"
#include "include/system/msgdata.h"
#include "include/system/fontproc.h"
#include "assert.h"
#include "system.h"
#include "string.h"
#include "pltt_manager.h"
#include "include/application/imageClip/imc_snd_def.h"

#define __IMC_BUTTON_H_GLOBAL
#include "include/application/imageClip/imc_button.h"

//-----------------------------------------------------------------------------
/**
 *					定数宣言
*/
//-----------------------------------------------------------------------------
#define IMC_BTTN_PRI	(2)

//-------------------------------------
//	
//	絵のON	OFFフレーム数
//	
//=====================================
#define	IMC_BTTN_DRAW_OFF	(0)
#define	IMC_BTTN_DRAW_HALF	(1)
#define	IMC_BTTN_DRAW_ON	(2)
#define	IMC_BTTN_DRAW_HALF2	(3)


//-------------------------------------
//	
//	フォントボタンの文字列オフセット位置
//	
//=====================================
#define IMC_FONTBTTN_DRAW_X		(16)
#define IMC_FONTBTTN_DRAW_Y_OFF	(19)
#define IMC_FONTBTTN_DRAW_Y_ON	(15)
#define IMC_FONTBTTN_PLTT_OFS_OFF	(3)
#define IMC_FONTBTTN_PLTT_OFS_ON	(4)

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

static void imcBttnNoFunc( IMC_BUTTON* bttn, void* work );


//-----------------------------------------------------------------------------
/**
*		イメージクリップ用
*/
//-----------------------------------------------------------------------------
static void makeBttn( IMC_BUTTON* bttn, int bttn_no, IMC_DRAW_DATA* drawData, int x, int y, int sx, int sy );
static void makeFontBttn( IMC_FONT_BUTTON* bttn, int bttn_no, IMC_DRAW_DATA* drawData, CONST_FONTOAM_SYS_PTR fnt_sys, const GF_BGL_BMPWIN* bmp, int x, int y, int sx, int sy );
static void makeHitTbl( TP_HIT_TBL* p_hit, int bttn_no, int x, int y, int sx, int sy );

static void loadBttnRes( IMC_DRAW_DATA* drawData );
static void loadBttnEndCkRes( IMC_DRAW_DATA* drawData );
static void deleteBttnCharPltt( IMC_DRAW_DATA* drawData );

static GF_BGL_BMPWIN* getBttnStr( IMC_DRAW_DATA* drawData, u32 arcID, u32 dataID, u32 msgID, int bmp_x, int bmp_y );
static void deleteBttnStr( GF_BGL_BMPWIN* win );

static void IMCBTTN_normalAnm( IMC_BUTTON* bttn, int state );
static void IMCBTTN_sndStart( IMC_BUTTON* bttn, int se, int timing, int state );
static void IMC_BTTN_FontAnm( IMC_FONT_BUTTON* bttn, int state );

static void IMC_BTTN_Move( IMC_BUTTON* bttn, int x, int y );
static void IMC_FONTBTTN_Move( IMC_FONT_BUTTON* bttn, int x, int y );

// コールバック関数
static void IMC_IMCBTTN_Call( u32 button, u32 event, void* work );

// static void IMCBTTN_ace_bg_snd_anm( IMC_BUTTON_DATA* data, int flg );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ボタンの初期化
 *
 *	@param	button		ボタンオブジェのポインタ 
 *	@param	init		初期化データ構造体		 
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_BTTN_Init( IMC_BUTTON* button, IMC_BUTTON_INIT* init )
{

	GF_ASSERT( button );
	GF_ASSERT( init );

	button->clact_w = CLACT_Add( init->clact );
	GF_ASSERT( button->clact_w );

	// データ格納
	button->start_flg	= init->start_flg;
	button->work		= init->work;
	if(init->buttonFunc){
		button->func		= init->buttonFunc;
	}else{
		button->func		= imcBttnNoFunc;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	文字列貼り付けボタン作成
 *
 *	@param	button	文字列ボタン
 *	@param	init	初期化データ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_BTTN_FontBttnInit( IMC_FONT_BUTTON* button, IMC_FONT_BUTTON_INIT* init )
{
	FONTOAM_INIT fontoam_init;
	
	IMC_BTTN_Init( &button->button, &init->bttn_init );

	fontoam_init.fontoam_sys	= init->fntoam_sys;
	fontoam_init.bmp			= init->bmp;
	fontoam_init.clact_set		= init->bttn_init.clact->ClActSet;
	fontoam_init.pltt			= init->pltt;
	fontoam_init.parent			= button->button.clact_w;
	fontoam_init.char_ofs		= init->char_ofs;
	fontoam_init.x				= init->fnt_x;
	fontoam_init.y				= init->fnt_y;
	fontoam_init.bg_pri			= 0;
	fontoam_init.soft_pri		= 0;
	fontoam_init.draw_area		= init->bttn_init.clact->DrawArea;
	fontoam_init.heap			= init->bttn_init.clact->heap;

	button->font = FONTOAM_Init( &fontoam_init );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ボタンの破棄
 *
 *	@param	button	ボタンオブジェクト
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_BTTN_Delete( IMC_BUTTON* button )
{
	// アクター破棄
	CLACT_Delete( button->clact_w );

	// 初期化
	memset( button, 0, sizeof(IMC_BUTTON) );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	フォント張り付きボタン破棄
 *
 *	@param	button	ボタンデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_BTTN_FontBttnDelete( IMC_FONT_BUTTON* button )
{
	IMC_BTTN_Delete( &button->button );

	FONTOAM_Delete( button->font );

	memset( button, 0, sizeof(IMC_FONT_BUTTON) );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ボタンシステムメイン関数
 *
 *	@param	button	ボタン構造体
 *	@param	state	今のボタン状態
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_BTTN_DoFunc( IMC_BUTTON* button, int state )
{
	// 動作関数を実行するかチェック
	if( state == button->start_flg ){

		button->func( button, button->work );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	アクセサリ　BG　変更ボタンを押した状態にする
 *
 *	@param	button			ボタン構造体
 *	@param	button_no		ボタンナンバー
 *
 *	@return	none
 *
 * button_no
	IMC_BTTN_ACE,		// アクセサリ変更に移る
	IMC_BTTN_BG,		// BG変更に移る
 *
 */
//-----------------------------------------------------------------------------
void IMC_IMCBTTN_OnAB( IMC_BUTTON_DATA* button, int button_no, int event )
{
	int i;		// ループ用
	IMC_BUTTON* bttn;	
	
	// flgのオブジェクトは押された絵に
	// その他のオブジェクトのボタンを離した状態にする
	for( i=IMC_BTTN_ACE; i<=IMC_BTTN_BG; i++ ){

		bttn = button->bttn + i;
		
		if( i != button_no ){
			// 離した絵にする
			IMC_BTTN_PopGra( bttn );
		}else{
			if( event == IMC_BTTN_PUSH_F ){
				// 押した絵にする
				IMC_BTTN_HalfGra( bttn );
				// ボタンを押した音
				Snd_SePlay( IMC_SE_BUTTON_ON );
			}else if( event == IMC_BTTN_PUSH ){

				// 深く押した
				IMC_BTTN_PushGra( bttn );
			}else{

				// 押した絵にする
				IMC_BTTN_HalfGra( bttn );
			}
		}
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	動作関数をボタンに設定
 *
 *	@param	button		ボタン構造体
 *	@param	func		動作関数
 *	@param	work		ワーク
 *	@param	start_flg	動作関数実行タイミング
 *
 *	@return	none
 *
 *	start_flg
		IMC_BTTN_NOPUSH,		// 押されていない
		IMC_BTTN_PUSH,			// 押されている
		IMC_BTTN_PUSH_F,		// 押された瞬間
		IMC_BTTN_POP,			// 離された瞬間
 *
 */
//-----------------------------------------------------------------------------
void IMC_BTTN_FuncSet( IMC_BUTTON* button, IMCBUTTON_FUNC func, void* work, int start_flg )
{
	GF_ASSERT( button );
	
	button->start_flg	= start_flg;
	button->work		= work;
	button->func		= func;
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	何もしない関数
 *
 *	@param	bttn
 *	@param	work 
 *
 *	@return
 *
 *
 */
//-----------------------------------------------------------------------------
static void imcBttnNoFunc( IMC_BUTTON* bttn, void* work )
{
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	押されたときのエフェクト
 *
 *	@param	bttn	ボタン構造体
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_BTTN_PushGra( IMC_BUTTON* bttn )
{
	// 絵を押し状態にする
	CLACT_AnmFrameSet( bttn->clact_w, IMC_BTTN_DRAW_ON );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	離されたときのエフェクト
 *
 *	@param	bttn	ボタン構造体
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_BTTN_PopGra( IMC_BUTTON* bttn )
{
	// 絵を離し状態にする
	CLACT_AnmFrameSet( bttn->clact_w, IMC_BTTN_DRAW_OFF );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	中間のときの絵にする
 *
 *	@param	bttn	ボタン構造体
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_BTTN_HalfGra( IMC_BUTTON* bttn )
{
	// 絵を中間状態にする
	CLACT_AnmFrameSet( bttn->clact_w, IMC_BTTN_DRAW_HALF );
}



//-----------------------------------------------------------------------------
/**
*			イメージクリップ用関数郡
*	jump
*/
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *	
 *	@brief	イメージクリップ用ボタンの作成
 *
 *	@param	button		ボタン構造体
 *	@param	drawData	描画システムデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_IMCBTTN_Init( IMC_BUTTON_DATA* button, IMC_DRAW_DATA* drawData )
{
	GF_BGL_BMPWIN* bmp;
	
	// OAMフォントシステム作成
	button->fntoam_sys = FONTOAM_SysInit( 1, HEAPID_IMAGECLIP_DATA );

	// リソース読み込み
	loadBttnRes( drawData );

	
	// パレットをめくるボタン
	// 描画データと当たり判定テーブルの作成
	makeBttn( &button->bttn[ IMC_BTTN_RET ], IMC_BTTN_RET, drawData,
			IMC_BTTN_RET_X, IMC_BTTN_RET_Y,
			IMC_BTTN_RET_SIZE_X, IMC_BTTN_RET_SIZE_Y);
	makeHitTbl( button->hit, IMC_BTTN_RET,
			IMC_BTTN_RET_X, IMC_BTTN_RET_Y + IMC_BTTN_HIT_Y_OFS,
			IMC_BTTN_RET_SIZE_X, IMC_BTTN_RET_SIZE_Y - IMC_BTTN_HIT_Y_OFS);
	
	// パレットをめくって前に戻すボタン
	// 描画データと当たり判定テーブルの作成
	makeBttn( &button->bttn[ IMC_BTTN_RETB ], IMC_BTTN_RETB, drawData,
			IMC_BTTN_RETB_X, IMC_BTTN_RET_Y,
			IMC_BTTN_RET_SIZE_X, IMC_BTTN_RET_SIZE_Y);
	makeHitTbl( button->hit, IMC_BTTN_RETB,
			IMC_BTTN_RETB_X, IMC_BTTN_RET_Y + IMC_BTTN_HIT_Y_OFS,
			IMC_BTTN_RET_SIZE_X, IMC_BTTN_RET_SIZE_Y - IMC_BTTN_HIT_Y_OFS);
	
	// アクセサリ変更に移るボタン
	// 描画データと当たり判定テーブルの作成
	makeBttn( &button->bttn[ IMC_BTTN_ACE ], IMC_BTTN_ACE, drawData,
			IMC_BTTN_ACE_X, IMC_BTTN_Y,
			IMC_BTTN_NOR_SIZE_X, IMC_BTTN_NOR_SIZE_Y);
	makeHitTbl( button->hit, IMC_BTTN_ACE,
			IMC_BTTN_ACE_X, IMC_BTTN_Y + IMC_BTTN_HIT_Y_OFS_NOR_END,
			IMC_BTTN_NOR_SIZE_X, IMC_BTTN_NOR_SIZE_Y - IMC_BTTN_HIT_Y_OFS);
	
	// BG変更に移るボタン
	// 描画データと当たり判定テーブルの作成
	makeBttn( &button->bttn[ IMC_BTTN_BG ], IMC_BTTN_BG, drawData,
			IMC_BTTN_BG_X, IMC_BTTN_Y,
			IMC_BTTN_NOR_SIZE_X, IMC_BTTN_NOR_SIZE_Y);
	makeHitTbl( button->hit, IMC_BTTN_BG,
			IMC_BTTN_BG_X, IMC_BTTN_Y + IMC_BTTN_HIT_Y_OFS_NOR_END,
			IMC_BTTN_NOR_SIZE_X, IMC_BTTN_NOR_SIZE_Y - IMC_BTTN_HIT_Y_OFS);
	
	
	// END変更に移るボタン
	// 描画データと当たり判定テーブルの作成
	// フォントデータ読み込み
	FontProc_LoadFont( FONT_BUTTON, HEAPID_IMAGECLIP_DRAW );
	// 文字列の
	// ビットマップウィンドウ作成
	bmp = getBttnStr( drawData, ARC_MSG, NARC_msg_imageclip_dat,
			imgclip_end,
			IMC_BTTN_END_SIZE_X / 8,
			IMC_BTTN_END_SIZE_Y / 8);
	// 文字列つきボタン作成
	makeFontBttn( &button->bttn_end, IMC_BTTN_END, drawData, 
			button->fntoam_sys, bmp,
			IMC_BTTN_END_X, IMC_BTTN_Y,
			IMC_BTTN_END_SIZE_X, IMC_BTTN_END_SIZE_Y );
	makeHitTbl( button->hit, IMC_BTTN_END,
			IMC_BTTN_END_X, IMC_BTTN_Y + IMC_BTTN_HIT_Y_OFS_NOR_END,
			IMC_BTTN_END_SIZE_X, IMC_BTTN_END_SIZE_Y - IMC_BTTN_HIT_Y_OFS );
	// 文字列の
	// ビットマップウィンドウ破棄
	deleteBttnStr( bmp );
	// 文字列フォント破棄
	FontProc_UnloadFont( FONT_BUTTON );

	// 終了ボタン有効
	button->bttn_end_do = TRUE;
	
	// リソース破棄
	deleteBttnCharPltt( drawData );


	// デフォルトでアクセサリ変更に移るボタンを変更
	IMC_BTTN_PushGra( &button->bttn[ IMC_BTTN_ACE ] );

	// ボタンマネージャに登録
	button->bttn_man = BMN_Create( button->hit, IMC_BTTN_MAX, IMC_IMCBTTN_Call, button, HEAPID_IMAGECLIP_DATA );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	イメージクリップ用ボタンの破棄
 *
 *	@param	button		ボタン構造体
 *	@param	drawData	描画データ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_IMCBTTN_Delete( IMC_BUTTON_DATA* button, IMC_DRAW_DATA* drawData )
{
	int i;

	// セル、セルアニメ、キャラクタVramエリア　パレットVramエリア解放
	for( i=0;i<IMC_BTTN_MAX;i++ ){
		IMC_DRAW_CLACT_DeleteCellRes( drawData, i );
		IMC_DRAW_CLACT_DeleteCellAnmRes( drawData, i );
		DelChar( i );
	}
	DelPltt( IMC_BTTN_RES_MAN_PLTT );
	DelPltt( IMC_BTTN_RES_MAN_PLTT_FONT );

	for( i=0; i<IMC_BTTN_NORM_MAX; i++ ){
		IMC_BTTN_Delete( &button->bttn[ i ] );
	}

	// フォントデータが使用していたキャラクタ領域破棄
	CharVramAreaFree( &button->bttn_end.char_vram );
	
	IMC_BTTN_FontBttnDelete( &button->bttn_end );

	FONTOAM_SysDelete( button->fntoam_sys );

	// ボタンマネージャ破棄
	BMN_Delete( button->bttn_man );
	button->bttn_man = NULL;
}

//----------------------------------------------------------------------------
//
/**
 *
 *	@brief	イメージクリップボタンメイン
 *
 *	@param	button	ボタン情報
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_IMCBTTN_Main( IMC_BUTTON_DATA* button )
{
	GF_ASSERT( button->bttn_man );
	
	BMN_Main( button->bttn_man );
}

//----------------------------------------------------------------------------
/**
 *	@brief	強制終了
 *
 *	@param	button	ボタン
 */
//-----------------------------------------------------------------------------
void IMC_IMCBTTN_EndEx( IMC_BUTTON_DATA* button )
{
	if( button->bttn_end_do == TRUE ){
		// アニメ
		IMCBTTN_normalAnm( &button->bttn_end.button, IMC_BTTN_PUSH );
		// 終了ボタンの場合はフォントデータの座標も動かす
		IMC_BTTN_FontAnm( &button->bttn_end, IMC_BTTN_PUSH_F );
		// 音を鳴らす
		IMCBTTN_sndStart( &button->bttn_end.button, IMC_SE_BUTTON_ENDON, IMC_BTTN_PUSH_F, IMC_BTTN_PUSH );
		// 動作
		IMC_BTTN_DoFunc( &button->bttn_end.button, button->bttn_end.button.start_flg );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	ボタンアニメ状態リセット
 *
 *	@param	button 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
void IMC_IMCBTTN_Reset( IMC_BUTTON_DATA* button )
{
	IMCBTTN_normalAnm( &button->bttn_end.button, IMC_BTTN_AREA_OVER );
	IMC_BTTN_FontAnm( &button->bttn_end, IMC_BTTN_AREA_OVER );

	// ボタン状態設定
	IMC_IMCBTTN_OnAB( button, IMC_BTTN_ACE, IMC_BTTN_AREA_OVER );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	全ボタンを足し算移動させる
 *
 *	@param	button		ボタン構造体
 *	@param	x			足すｘ値
 *	@param	y			足すｙ値
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_IMCBTTN_Move( IMC_BUTTON_DATA* button, int x, int y )
{
	int i;			// ループ用

	for(i=0; i<IMC_BTTN_NORM_MAX; i++ ){
		IMC_BTTN_Move( button->bttn + i, x, y );
	}
	IMC_FONTBTTN_Move( &button->bttn_end, x, y );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	動作関数を設定
 *
 *	@param	button		ボタンデータ
 *	@param	button_no	ボタンナンバー
 *	@param	func		動作関数
 *	@param	work		ワーク
 *	@param	start_flg	関数を実行するタイミング
 *
 *	@return	none
 *
 *	start_flg
		IMC_BTTN_NOPUSH,		// 押されていない
		IMC_BTTN_PUSH,			// 押されている
		IMC_BTTN_PUSH_F,		// 押された瞬間
		IMC_BTTN_POP,			// 離された瞬間
 *
 */
//-----------------------------------------------------------------------------
void IMC_IMCBTTN_FuncSet( IMC_BUTTON_DATA* button, int button_no, IMCBUTTON_FUNC func, void* work, int start_flg )
{
	GF_ASSERT( button );

	if( button_no < IMC_BTTN_NORM_MAX ){
		IMC_BTTN_FuncSet( 
				&button->bttn[ button_no ],
				func, work, 
				start_flg);
	}else{
		IMC_BTTN_FuncSet( 
				&button->bttn_end.button,
				func, work, 
				start_flg);
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	ボタンの表示非表示設定
 *
 *	@param	button		ボタンワーク
 *	@param	button_no	ボタンナンバー
 *	@param	flag		フラグ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void IMC_IMCBTTN_DrawSet( IMC_BUTTON_DATA* button, int button_no, BOOL flag )
{
	GF_ASSERT( button );

	if( button_no < IMC_BTTN_NORM_MAX ){
		CLACT_SetDrawFlag( 
				button->bttn[ button_no ].clact_w, flag );
	}else{
		CLACT_SetDrawFlag( 
				button->bttn_end.button.clact_w, flag );
		FONTOAM_SetDrawFlag( 
				button->bttn_end.font, flag );

		if( flag == TRUE ){
			button->bttn_end_do = TRUE;
		}else{
			button->bttn_end_do = FALSE;
		}
	}
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	イメージクリップ用ボタンコールバック関数
 *
 *	@param	button		ボタンID
 *	@param	event		イベント
 *	@param	work		ワーク
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void IMC_IMCBTTN_Call( u32 button, u32 event, void* work )
{
	IMC_BUTTON_DATA* data = work;
	
	switch( button ){
	case IMC_BTTN_RET:
		// アニメ
		IMCBTTN_normalAnm( &data->bttn[ IMC_BTTN_RET ], event );
		// 音を鳴らす
		IMCBTTN_sndStart( &data->bttn[ IMC_BTTN_RET ], IMC_SE_RET_BUTTON_ON, IMC_BTTN_PUSH_F, event );
		// 動作
		IMC_BTTN_DoFunc( &data->bttn[ IMC_BTTN_RET ], event );
		break;

	case IMC_BTTN_RETB:
		// アニメ
		IMCBTTN_normalAnm( &data->bttn[ IMC_BTTN_RETB ], event );
		// 音を鳴らす
		IMCBTTN_sndStart( &data->bttn[ IMC_BTTN_RETB ], IMC_SE_RET_BUTTON_ON, IMC_BTTN_PUSH_F, event );
		// 動作
		IMC_BTTN_DoFunc( &data->bttn[ IMC_BTTN_RETB ], event );
		break;
		
	case IMC_BTTN_ACE:
	case IMC_BTTN_BG:
		// ボタン状態設定
		IMC_IMCBTTN_OnAB( data, button, event );
		// 動作
		IMC_BTTN_DoFunc( &data->bttn[ button ], event );
		break;
		
	case IMC_BTTN_END:
		if( data->bttn_end_do == TRUE ){
			// アニメ
			IMCBTTN_normalAnm( &data->bttn_end.button, event );
			// 終了ボタンの場合はフォントデータの座標も動かす
			IMC_BTTN_FontAnm( &data->bttn_end, event );
			// 音を鳴らす
			IMCBTTN_sndStart( &data->bttn_end.button, IMC_SE_BUTTON_ENDON, IMC_BTTN_PUSH_F, event );
			// 動作
			IMC_BTTN_DoFunc( &data->bttn_end.button, event );
		}
		break;

	default:
		GF_ASSERT_MSG( 0, "ここにくるのはおかしい\n" );
		break;
	}
}



//----------------------------------------------------------------------------
/**
 *
 *	@brief	ボタンナンバーのボタン作成
 *
 *	@param	bttn		ボタンデータ
 *	@param	bttn_no		ボタンナンバー
 *	@param	drawData	描画システムデータ
 *	@param	x			ｘ座標
 *	@param	y			ｙ座標
 *	@param	sx			ｘサイズ
 *	@param	sy			ｙサイズ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void makeBttn( IMC_BUTTON* bttn, int bttn_no, IMC_DRAW_DATA* drawData, int x, int y, int sx, int sy )
{
	IMC_BUTTON_INIT init;
	CLACT_HEADER head;
	CLACT_ADD	add;
	
	// ヘッダー作成
	CLACT_U_MakeHeader( 
			&head, 
			bttn_no, IMC_BTTN_RES_MAN_PLTT, 
			bttn_no, bttn_no,
			CLACT_U_HEADER_DATA_NONE,CLACT_U_HEADER_DATA_NONE,
			0, 0,
			drawData->resMan[ CLACT_U_CHAR_RES ],
			drawData->resMan[ CLACT_U_PLTT_RES ],
			drawData->resMan[ CLACT_U_CELL_RES ],
			drawData->resMan[ CLACT_U_CELLANM_RES ],
			NULL, NULL );

	// 登録データ作成
	add.ClActSet	= drawData->clactSet;
	add.ClActHeader = &head;
	add.mat.x		= x << FX32_SHIFT;
	add.mat.y		= y << FX32_SHIFT;
	add.mat.z		= 0;
	add.pri			= IMC_BTTN_PRI;
	add.DrawArea	= NNS_G2D_VRAM_TYPE_2DMAIN;
	add.heap		= HEAPID_IMAGECLIP_DRAW;

	init.clact	= &add;
	init.buttonFunc = NULL;
	init.work		= NULL;
	init.start_flg	= IMC_BTTN_POP;
	
	IMC_BTTN_Init( bttn, &init );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	フォントボタン
 *
 *	@param	bttn		フォントボタンデータ
 *	@param	bttn_no		ボタンナンバー	
 *	@param	drawData	描画システムデータ
 *	@param	fnt_sys		フォントシステム
 *	@param	pltt		パレットプロクシ
 *	@param	bmp			ビットマップウィンドウ
 *	@param	x			ｘ座標
 *	@param	y			ｙ座標
 *	@param	sx			ｘサイズ
 *	@param	sy			ｙサイズ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void makeFontBttn( IMC_FONT_BUTTON* bttn, int bttn_no, IMC_DRAW_DATA* drawData, CONST_FONTOAM_SYS_PTR fnt_sys, const GF_BGL_BMPWIN* bmp, int x, int y, int sx, int sy )
{
	IMC_FONT_BUTTON_INIT init;
	CLACT_HEADER head;
	CLACT_ADD	add;
	CLACT_U_RES_OBJ_PTR pltt_obj;
	int char_size;
	BOOL check;

	
	// セルアクターヘッダー作成
	CLACT_U_MakeHeader( 
			&head, 
			bttn_no, IMC_BTTN_RES_MAN_PLTT, 
			bttn_no, bttn_no,
			CLACT_U_HEADER_DATA_NONE,CLACT_U_HEADER_DATA_NONE,
			0, 0,
			drawData->resMan[ CLACT_U_CHAR_RES ],
			drawData->resMan[ CLACT_U_PLTT_RES ],
			drawData->resMan[ CLACT_U_CELL_RES ],
			drawData->resMan[ CLACT_U_CELLANM_RES ],
			NULL, NULL );


	// セルアクター登録データ作成
	add.ClActSet	= drawData->clactSet;
	add.ClActHeader = &head;
	add.mat.x		= x << FX32_SHIFT;
	add.mat.y		= y << FX32_SHIFT;
	add.mat.z		= 0;
	add.pri			= IMC_BTTN_PRI;
	add.DrawArea	= NNS_G2D_VRAM_TYPE_2DMAIN;
	add.heap		= HEAPID_IMAGECLIP_DRAW;

	// 文字列つきボタン作成データ
	init.bttn_init.clact	= &add;
	init.bttn_init.buttonFunc = NULL;
	init.bttn_init.work		= NULL;
	init.bttn_init.start_flg= IMC_BTTN_POP;
	init.fntoam_sys			= fnt_sys;
	init.bmp				= bmp;
	init.fnt_x				= IMC_FONTBTTN_DRAW_X;
	init.fnt_y				= IMC_FONTBTTN_DRAW_Y_OFF;

	// パレットプロクシ取得
	pltt_obj = CLACT_U_ResManagerGetIDResObjPtr( drawData->resMan[ CLACT_U_PLTT_RES ], IMC_BTTN_RES_MAN_PLTT_FONT );
	init.pltt				= CLACT_U_PlttManagerGetProxy( pltt_obj, NULL );

	// キャラクタオフセットを調べる
	char_size = FONTOAM_NeedCharSize( bmp, NNS_G2D_VRAM_TYPE_2DMAIN, HEAPID_IMAGECLIP_DATA );

	// キャラクタデータのVRAM領域確保
	check = CharVramAreaAlloc( char_size, CHARM_CONT_AREACONT, NNS_G2D_VRAM_TYPE_2DMAIN, &bttn->char_vram );
	GF_ASSERT_MSG( check, "ボタン文字用キャラクタデータ領域確保失敗" );
	init.char_ofs			= bttn->char_vram.alloc_ofs;
	
	// 文字列つきボタン作成
	IMC_BTTN_FontBttnInit( bttn, &init );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	当たり判定テーブルにデータを設定
 *
 *	@param	p_hit		当たり判定テーブル
 *	@param	bttn_no		ボタンナンバー
 *	@param	x			左上ｘ座標
 *	@param	y			左上ｙ座標
 *	@param	sx			幅
 *	@param	sy			高さ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void makeHitTbl( TP_HIT_TBL* p_hit, int bttn_no, int x, int y, int sx, int sy )
{
	p_hit[ bttn_no ].rect.top		= y;
	p_hit[ bttn_no ].rect.left		= x;
	p_hit[ bttn_no ].rect.bottom	= y + sy;
	p_hit[ bttn_no ].rect.right		= x + sx;
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	イメージクリップボタンデータ読み込み
 *
 *	@param	drawData	描画システムデータ 
 *
 *	@return	none
 *	
 *
 */
//-----------------------------------------------------------------------------
static void loadBttnRes( IMC_DRAW_DATA* drawData )
{
	int i;		// ループ用
	
	for( i=0; i<IMC_BTTN_MAX; i++ ){
		// キャラクタ
		IMC_DRAW_CLACT_LoadCharData( 
				drawData, ARC_IMAGECLIP_GRA,
				IMC_BTTN_ARC_CHAR_GET( i ),
				FALSE, NNS_G2D_VRAM_TYPE_2DMAIN, i);
		// セル
		IMC_DRAW_CLACT_LoadCellData( 
				drawData, ARC_IMAGECLIP_GRA,
				IMC_BTTN_ARC_CELL_GET( i ),
				FALSE, i);
		// セルアニメ
		IMC_DRAW_CLACT_LoadCellAnmData( 
				drawData, ARC_IMAGECLIP_GRA,
				IMC_BTTN_ARC_CANM_GET( i ),
				FALSE, i);
	}

	// パレット
	IMC_DRAW_CLACT_LoadPlttData( 
				drawData, ARC_IMAGECLIP_GRA,
				IMC_BTTN_ARC_FILE_PLTT,
				FALSE, NNS_G2D_VRAM_TYPE_2DMAIN, 
				IMC_BTTN_PLTT_LOAD_NUM, IMC_BTTN_RES_MAN_PLTT);

	// フォント用パレット
	IMC_DRAW_CLACT_LoadPlttData( 
				drawData, ARC_IMAGECLIP_GRA,
				IMC_BTTN_ARC_FILE_PLTT_FONT,
				FALSE, NNS_G2D_VRAM_TYPE_2DMAIN, 
				IMC_BTTN_PLTT_LOAD_NUM_FONT, IMC_BTTN_RES_MAN_PLTT_FONT);
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	終了チェックボタン用
 *
 *	@param	drawData	描画システムデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void loadBttnEndCkRes( IMC_DRAW_DATA* drawData )
{
	int i;		// ループ用
	
	for( i=0; i<IMC_BTTN_ENDCK_MAX; i++ ){
		// キャラクタ
		IMC_DRAW_CLACT_LoadCharData( 
				drawData, ARC_IMAGECLIP_GRA,
				IMC_BTTN_ENDCK_ARC_CHAR,
				FALSE, NNS_G2D_VRAM_TYPE_2DMAIN, i);
		// セル
		IMC_DRAW_CLACT_LoadCellData( 
				drawData, ARC_IMAGECLIP_GRA,
				IMC_BTTN_ENDCK_ARC_CELL,
				FALSE, i);
		// セルアニメ
		IMC_DRAW_CLACT_LoadCellAnmData( 
				drawData, ARC_IMAGECLIP_GRA,
				IMC_BTTN_ENDCK_ARC_CANM,
				FALSE, i);
	}

	// パレット
	IMC_DRAW_CLACT_LoadPlttData( 
				drawData, ARC_IMAGECLIP_GRA,
				IMC_BTTN_ARC_FILE_PLTT,
				FALSE, NNS_G2D_VRAM_TYPE_2DMAIN, 
				IMC_BTTN_PLTT_LOAD_NUM, IMC_BTTN_RES_MAN_PLTT);

	// フォント用パレット
	IMC_DRAW_CLACT_LoadPlttData( 
				drawData, ARC_IMAGECLIP_GRA,
				IMC_BTTN_ARC_FILE_PLTT_FONT,
				FALSE, NNS_G2D_VRAM_TYPE_2DMAIN, 
				IMC_BTTN_PLTT_LOAD_NUM_FONT, IMC_BTTN_RES_MAN_PLTT_FONT);
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ボタンとキャラクタは破棄
 *
 *	@param	drawData	描画データ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void deleteBttnCharPltt( IMC_DRAW_DATA* drawData )
{
	int i;		//ループ用

	for(i=0;i<IMC_BTTN_MAX;i++){
		IMC_DRAW_CLACT_DeleteCharRes( drawData, i );
	}

	IMC_DRAW_CLACT_DeletePlttRes( drawData, IMC_BTTN_RES_MAN_PLTT );
	IMC_DRAW_CLACT_DeletePlttRes( drawData, IMC_BTTN_RES_MAN_PLTT_FONT );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	普通のアニメ
 *
 *	@param	bttn	ボタン構造体
 *	@param	state	今の状態
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void IMCBTTN_normalAnm( IMC_BUTTON* bttn, int state )
{
	if( state == IMC_BTTN_PUSH_F ){

		// 中間の絵
		IMC_BTTN_HalfGra( bttn );

	}else if( state == IMC_BTTN_PUSH ){

		// 押した絵にする
		IMC_BTTN_PushGra( bttn );

	}else if( (state == IMC_BTTN_POP) ||
			(state == IMC_BTTN_AREA_OVER) ){
		
		// 離した絵にする
		IMC_BTTN_PopGra( bttn );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	終了ボタン用アニメ
 *
 *	@param	bttn	ボタンワワーク
 *	@param	state	ステータス
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void IMCBTTN_EndButtonAnm( IMC_BUTTON* bttn, int state )
{
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	フォントボタンのフォントデータのアニメーションを管理
 *
 *	@param	bttn	フォントボタン構造体
 *	@param	state	今の状態
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void IMC_BTTN_FontAnm( IMC_FONT_BUTTON* bttn, int state )
{
	if( state == IMC_BTTN_PUSH_F ){

		// 押した絵にする
		FONTOAM_SetMat( bttn->font, IMC_FONTBTTN_DRAW_X, IMC_FONTBTTN_DRAW_Y_ON );

		// パレットオフセットを変更
		FONTOAM_SetPaletteNo( bttn->font, IMC_FONTBTTN_PLTT_OFS_ON );
	}else{
		
		if( state == IMC_BTTN_POP ){

			// 離した絵にする
			FONTOAM_SetMat( bttn->font, IMC_FONTBTTN_DRAW_X, IMC_FONTBTTN_DRAW_Y_OFF );
		}
		
		if( state == IMC_BTTN_AREA_OVER ){
			// 離した絵にする
			FONTOAM_SetMat( bttn->font, IMC_FONTBTTN_DRAW_X, IMC_FONTBTTN_DRAW_Y_OFF );
			// パレットオフセットを変更
			FONTOAM_SetPaletteNo( bttn->font, IMC_FONTBTTN_PLTT_OFS_OFF );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	効果音開始
 *
 *	@param	bttn		ボタンオブジェ
 *	@param	se			鳴らすSE
 *	@param	state		今の状態
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void IMCBTTN_sndStart( IMC_BUTTON* bttn, int se, int timing, int state )
{
	if( state == timing ){

		// ボタンを押した音
		Snd_SePlay( se );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ボタン用文字列作成
 *
 *	@param	drawData	描画システムデータ
 *	@param	arcID		アーカイブID
 *	@param	dataID		データID
 *	@param	msgID		メッセージID
 *	@param	bmp_x		作成するビットマップの大きさ
 *	@param	bmp_y		作成するビットマップの大きさ
 *
 *	@return	作成したビットマップ
 *
 *
 */
//-----------------------------------------------------------------------------
static GF_BGL_BMPWIN* getBttnStr( IMC_DRAW_DATA* drawData, u32 arcID, u32 dataID, u32 msgID, int bmp_x, int bmp_y )
{
	MSGDATA_MANAGER* msg_data;
	STRBUF* str;
	GF_BGL_BMPWIN* bmp;

	msg_data = MSGMAN_Create( MSGMAN_TYPE_NORMAL, arcID, dataID, HEAPID_IMAGECLIP_DATA );
	GF_ASSERT( msg_data );
	str = MSGMAN_AllocString( msg_data, msgID );


	bmp = GF_BGL_BmpWinAllocGet( HEAPID_IMAGECLIP_DRAW, 1 );
	GF_BGL_BmpWinInit( bmp );
	GF_BGL_BmpWinObjAdd( drawData->BG_Ini, bmp, bmp_x, bmp_y, 0, 0 );

	// 文字列書き込み
	GF_STR_PrintColor( bmp, FONT_BUTTON, str, 0, 0, MSG_NO_PUT, GF_PRINTCOLOR_MAKE(1,2,3), NULL );

	STRBUF_Delete( str );
	MSGMAN_Delete( msg_data );

	return bmp;
	
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	文字列破棄
 *
 *	@param	win 
 *
 *	@return
 *
 *
 */
//-----------------------------------------------------------------------------
static void deleteBttnStr( GF_BGL_BMPWIN* win )
{
	GF_BGL_BmpWinFree( win, 1 );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ボタンを動かす
 *
 *	@param	bttn		ボタンデータ
 *	@param	x			ｘ座標
 *	@param	y			ｙ座標
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void IMC_BTTN_Move( IMC_BUTTON* bttn, int x, int y )
{
	const VecFx32* get_mat;
	VecFx32	mat;	

	get_mat = CLACT_GetMatrix( bttn->clact_w );
	mat = *get_mat;
	mat.x += x << FX32_SHIFT;
	mat.y += y << FX32_SHIFT;
	CLACT_SetMatrix( bttn->clact_w, &mat );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	フォントボタンを動かす
 *
 *	@param	bttn		フォントボタン
 *	@param	x			足すｘ値
 *	@param	y			足すｙ値
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void IMC_FONTBTTN_Move( IMC_FONT_BUTTON* bttn, int x, int y )
{
	IMC_BTTN_Move( &bttn->button, x, y );
	FONTOAM_ReflectParentMat( bttn->font );
}

#if 0
// アクセサリ　BG　サウンド変更ボタンはエフェクト中には押せないため、
// 押していないことになるときもあるので、
// ボタンシステム内で行うことができない。
//----------------------------------------------------------------------------
/**
 *
 *	@brief	アクセサリ　BG　サウンド	のアニメーション
 *
 *	@param	data	イメージクリップボタンデータ
 *	@param	flg		フラグ	
 *
 *	@return	none
 *
 * flg
	IMC_BTTN_ACE,		// アクセサリ変更
	IMC_BTTN_BG,		// BG変更
 *
 */
//-----------------------------------------------------------------------------
static void IMCBTTN_ace_bg_snd_anm( IMC_BUTTON_DATA* data, int flg )
{
	IMC_BUTTON* bttn;
	int state;
	int i;		// ループ用
	
	bttn = &data->bttn[ flg ];

	state = IMC_BTTN_GetState( bttn );
	if( state == IMC_BTTN_PUSH_F ){

		// flgのオブジェクトは押された絵に
		// その他のオブジェクトのボタンを離した状態にする
		for( i=IMC_BTTN_ACE; i<=IMC_BTTN_SND; i++ ){

			bttn = data->bttn + i;
			
			if( i != flg ){
				// 離した絵にする
				IMC_BTTN_PopGra( bttn );
			}else{
				// 押した絵にする
				IMC_BTTN_PushGra( bttn );
			}
		}
	}
}
#endif

