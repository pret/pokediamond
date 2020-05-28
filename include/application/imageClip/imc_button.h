//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		imc_button.h
 *	@brief		画面下のボタン制御システム
 *	@author		tomoya takahashi
 *	@data		2005.10.08
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __IMC_BUTTON_H__
#define __IMC_BUTTON_H__

#include "bg_system.h"
#include "clact.h"
#include "button_man.h"
#include "include/application/imageClip/imc_drawsys.h"
#include "touchpanel.h"
#include "include/system/fontoam.h"
#include "char_manager.h"

#undef GLOBAL
#ifdef	__IMC_BUTTON_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

//-----------------------------------------------------------------------------
/**
 *					定数宣言
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	今のボタンの状態
//	動作関数を動かすタイミング
//	
//=====================================
enum{
	IMC_BTTN_PUSH_F		= BMN_EVENT_TOUCH,		// 押された瞬間
	IMC_BTTN_POP		= BMN_EVENT_RELEASE,	// 離された
	IMC_BTTN_PUSH		= BMN_EVENT_HOLD,		// 押されている
	IMC_BTTN_AREA_OVER	= BMN_EVENT_SLIDEOUT,	// ボタンエリア外
};

//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	ボタン構造体	
//	
//=====================================
typedef struct _IMC_BUTTON{
	// 描画部
	CLACT_WORK_PTR clact_w;	// アクターワーク
	
	// 動作部
	int start_flg;		// 動作関数を動かすタイミング
	void*	work;		// 動作関数に渡すワーク
	// 動作関数	ボタンの動作で自動に発動されるもの
	void (*func)(struct _IMC_BUTTON* button, void* work);
} IMC_BUTTON;

// 動作構造体
typedef void (*IMCBUTTON_FUNC)( IMC_BUTTON* button, void* work );

//-------------------------------------
//	
//	ボタン作成構造体
//	
//=====================================
typedef struct {
	CLACT_ADD*		clact;			// セルアクター登録データ

	IMCBUTTON_FUNC	buttonFunc;		// 動作関数
	void*			work;			// 動作に渡すワーク
	int				start_flg;		// どのタイミングに動作関数を実行するか
/*						IMC_BTTN_NOPUSH,		// 押されていない
						IMC_BTTN_PUSH,			// 押されている
						IMC_BTTN_PUSH_F,		// 押された瞬間
						IMC_BTTN_POP,			// 離された	
						IMC_BTTN_AREA_OVER,		// ボタンエリア外 */
} IMC_BUTTON_INIT;

//-------------------------------------
//	
//	フォント付きボタン
//	
//=====================================
typedef struct {
	IMC_BUTTON button;
	FONTOAM_OBJ_PTR font;
	CHAR_MANAGER_ALLOCDATA char_vram;
} IMC_FONT_BUTTON;

//-------------------------------------
//	
//	ボタン作成構造体
//	
//=====================================
typedef struct {
	IMC_BUTTON_INIT bttn_init;		// ボタン初期化データ
	const GF_BGL_BMPWIN* bmp;		// キャラクタデータ
	CONST_FONTOAM_SYS_PTR fntoam_sys;	// OAMフォントシステムデータ
	const NNSG2dImagePaletteProxy* pltt;// パレットプロクシ
	int				fnt_x;			// オフセット位置
	int				fnt_y;			// オフセット位置
	int				char_ofs;		// キャラクタオフセット
} IMC_FONT_BUTTON_INIT;

//-----------------------------------------------------------------------------
/**
*		イメージクリップ用
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	イメージクリップ用ボタン構造体	
//	
//=====================================
typedef struct {
	IMC_BUTTON	bttn[IMC_BTTN_NORM_MAX];
	IMC_FONT_BUTTON bttn_end;
	BOOL bttn_end_do;
	FONTOAM_SYS_PTR fntoam_sys;

	// 当たり判定用テーブル
	BUTTON_MAN* bttn_man;
	TP_HIT_TBL hit[ IMC_BTTN_MAX ];
} IMC_BUTTON_DATA;



//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief
 *
 *	@param	button		ボタンオブジェのポインタ 
 *	@param	init		初期化データ構造体		 
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_BTTN_Init( IMC_BUTTON* button, IMC_BUTTON_INIT* init );
GLOBAL void IMC_BTTN_FontBttnInit( IMC_FONT_BUTTON* button, IMC_FONT_BUTTON_INIT* init );

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
GLOBAL void IMC_BTTN_Delete( IMC_BUTTON* button );
GLOBAL void IMC_BTTN_FontBttnDelete( IMC_FONT_BUTTON* button );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ボタンシステム動作関数実行
 *
 *	@param	button	ボタン構造体
 *	@param	state	今のボタン状態
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_BTTN_DoFunc( IMC_BUTTON* button, int state );

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
		IMC_BTTN_PUSH,			// 押されている
		IMC_BTTN_PUSH_F,		// 押された瞬間
		IMC_BTTN_POP,			// 離された瞬間
		IMC_BTTN_AREA_OVER		// ボタンエリア外
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_BTTN_FuncSet( IMC_BUTTON* button, IMCBUTTON_FUNC func, void* work, int start_flg );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	押されたときの絵にする
 *
 *	@param	bttn	ボタン構造体
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_BTTN_PushGra( IMC_BUTTON* bttn );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	離されたときの絵にする
 *
 *	@param	bttn	ボタン構造体
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_BTTN_PopGra( IMC_BUTTON* bttn );

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
GLOBAL void IMC_BTTN_HalfGra( IMC_BUTTON* bttn );


//-----------------------------------------------------------------------------
/**
*	イメージクリップ用
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
GLOBAL void IMC_IMCBTTN_Init( IMC_BUTTON_DATA* button, IMC_DRAW_DATA* drawData );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	イメージクリップ用ボタンの破棄
 *
 *	@param	button		ボタン構造体
 *	@param	drawData	描画システムデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_IMCBTTN_Delete( IMC_BUTTON_DATA* button, IMC_DRAW_DATA* drawData );

//----------------------------------------------------------------------------
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
GLOBAL void IMC_IMCBTTN_Main( IMC_BUTTON_DATA* button );


//----------------------------------------------------------------------------
/**
 *	@brief	強制終了
 *
 *	@param	button	ボタン
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_IMCBTTN_EndEx( IMC_BUTTON_DATA* button );


//----------------------------------------------------------------------------
/**
 *	@brief	ボタンアニメ状態リセット
 *
 *	@param	button 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_IMCBTTN_Reset( IMC_BUTTON_DATA* button );

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
GLOBAL void IMC_IMCBTTN_Move( IMC_BUTTON_DATA* button, int x, int y );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	アクセサリ　BG　変更ボタンを押した状態にする
 *
 *	@param	button			ボタン構造体
 *	@param	button_no		ボタンナンバー
 *	@param	event			イベントデータ
 *
 *	@return	none
 *
 * button_no
	IMC_BTTN_ACE,		// アクセサリ変更に移る
	IMC_BTTN_BG,		// BG変更に移る
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_IMCBTTN_OnAB( IMC_BUTTON_DATA* button, int button_no, int event );

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
		IMC_BTTN_AREA_OVER		// ボタンエリア外
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_IMCBTTN_FuncSet( IMC_BUTTON_DATA* button, int button_no, IMCBUTTON_FUNC func, void* work, int start_flg );

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
GLOBAL void IMC_IMCBTTN_DrawSet( IMC_BUTTON_DATA* button, int button_no, BOOL flag );


#undef	GLOBAL
#endif		// __IMC_BUTTON_H__

