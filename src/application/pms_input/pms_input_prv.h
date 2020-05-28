//============================================================================================
/**
 * @file	pms_input_prv.h
 * @bfief	簡易会話入力画面（private ヘッダ）
 * @author	taya
 * @date	06.01.24
 */
//============================================================================================
#ifndef __PMS_INPUT_PRV_H__
#define __PMS_INPUT_PRV_H__

#include "application\pms_input.h"
#include "application\pms_input_data.h"
#include "pms_input_param.h"

//------------------------------------------------------
/**
 * 描画コマンド
 */
//------------------------------------------------------
enum {
	VCMD_INIT,					///< 画面初期構築
	VCMD_QUIT,					///< 描画終了
	VCMD_FADEIN,				///< フェードイン

	VCMD_UPDATE_EDITAREA,		///< 編集領域更新
	VCMD_EDITAREA_TO_BUTTON,	///< 編集領域からコマンドボタンへ
	VCMD_BUTTON_TO_EDITAREA,	///< コマンドボタンから編集領域へ
	VCMD_EDITAREA_TO_CATEGORY,	///< 編集領域からカテゴリ選択へ
	VCMD_CATEGORY_TO_EDITAREA,	///< カテゴリ選択から編集領域へ
	VCMD_CATEGORY_TO_WORDWIN,	///< カテゴリ選択から単語選択へ
	VCMD_WORDWIN_TO_CATEGORY,	///< 単語選択からカテゴリ選択へ（単語選択キャンセル後）
	VCMD_WORDTIN_TO_EDITAREA,	///< 単語選択から編集領域へ（単語決定後）
	VCMD_WORDTIN_TO_BUTTON,		///< 単語選択からコマンドボタンへ（単語決定後）

	VCMD_MOVE_EDITAREA_CURSOR,	///< 編集領域カーソル移動
	VCMD_MOVE_BUTTON_CURSOR,	///< ボタンカーソル移動
	VCMD_MOVE_CATEGORY_CURSOR,	///< カテゴリ選択カーソル移動
	VCMD_MOVE_WORDWIN_CURSOR,	///< 単語選択カーソル移動
	VCMD_SCROLL_WORDWIN,		///< 単語ウィンドウスクロール

	VCMD_DISP_MESSAGE_DEFAULT,	///< 初期メッセージ表示
	VCMD_DISP_MESSAGE_OK,		///< これでいいですか？メッセージ＆メニュー
	VCMD_DISP_MESSAGE_CANCEL,	///< やめますか？メッセージ＆メニュー
	VCMD_DISP_MESSAGE_WARN,		///< なにかことばをいれてください！メッセージ
	VCMD_MOVE_MENU_CURSOR,		///< メニューカーソル移動
	VCMD_ERASE_MENU,			///< メニュー表示消去

	VCMD_CHANGE_CATEGORY_MODE_DISABLE,	///< カテゴリモード切替え、カテゴリ選択状態へ移行しない
	VCMD_CHANGE_CATEGORY_MODE_ENABLE,	///< カテゴリモード切替え、カテゴリ選択状態へ移行する

	VCMD_BUTTON_UP_HOLD,
	VCMD_BUTTON_DOWN_HOLD,
	VCMD_BUTTON_UP_RELEASE,
	VCMD_BUTTON_DOWN_RELEASE,


};


//------------------------------------------------------
/**
 * ボタンアクターレイアウト
 */
//------------------------------------------------------
enum {

	BUTTON_GROUP_SCRN_XPOS = 3,
	BUTTON_GROUP_SCRN_YPOS = 3,
	BUTTON_INITIAL_SCRN_XPOS = 3,
	BUTTON_INITIAL_SCRN_YPOS = 14,

	MODEBUTTON_SCRN_WIDTH = 11,
	MODEBUTTON_SCRN_HEIGHT = 7,

	BUTTON_GROUP_TOUCH_TOP		= BUTTON_GROUP_SCRN_YPOS*8,
	BUTTON_GROUP_TOUCH_BOTTOM	= BUTTON_GROUP_TOUCH_TOP+(MODEBUTTON_SCRN_HEIGHT*8),
	BUTTON_GROUP_TOUCH_LEFT		= BUTTON_GROUP_SCRN_XPOS*8,
	BUTTON_GROUP_TOUCH_RIGHT	= BUTTON_GROUP_TOUCH_LEFT+(MODEBUTTON_SCRN_WIDTH*8),

	BUTTON_INITIAL_TOUCH_TOP	= BUTTON_INITIAL_SCRN_YPOS*8,
	BUTTON_INITIAL_TOUCH_BOTTOM	= BUTTON_INITIAL_TOUCH_TOP+(MODEBUTTON_SCRN_HEIGHT*8),
	BUTTON_INITIAL_TOUCH_LEFT	= BUTTON_INITIAL_SCRN_XPOS*8,
	BUTTON_INITIAL_TOUCH_RIGHT	= BUTTON_INITIAL_TOUCH_LEFT+(MODEBUTTON_SCRN_WIDTH*8),



	BUTTON_UP_XPOS = 192,
	BUTTON_UP_YPOS = 56,
	BUTTON_DOWN_XPOS = 192,
	BUTTON_DOWN_YPOS = 136,

	BUTTON_ARROW_TOUCH_WIDTH = 32,
	BUTTON_ARROW_TOUCH_HEIGHT = 32,

	BUTTON_UP_TOUCH_TOP		= BUTTON_UP_YPOS-(BUTTON_ARROW_TOUCH_HEIGHT/2),
	BUTTON_UP_TOUCH_BOTTOM	= BUTTON_UP_YPOS+(BUTTON_ARROW_TOUCH_HEIGHT/2),
	BUTTON_UP_TOUCH_LEFT	= BUTTON_UP_XPOS-(BUTTON_ARROW_TOUCH_WIDTH/2),
	BUTTON_UP_TOUCH_RIGHT	= BUTTON_UP_XPOS+(BUTTON_ARROW_TOUCH_WIDTH/2),


	BUTTON_DOWN_TOUCH_TOP		= BUTTON_DOWN_YPOS-(BUTTON_ARROW_TOUCH_HEIGHT/2),
	BUTTON_DOWN_TOUCH_BOTTOM	= BUTTON_DOWN_YPOS+(BUTTON_ARROW_TOUCH_HEIGHT/2),
	BUTTON_DOWN_TOUCH_LEFT	= BUTTON_DOWN_XPOS-(BUTTON_ARROW_TOUCH_WIDTH/2),
	BUTTON_DOWN_TOUCH_RIGHT	= BUTTON_DOWN_XPOS+(BUTTON_ARROW_TOUCH_WIDTH/2),



};






//------------------------------------------------------
/**
 * メインワーク型宣言
 */
//------------------------------------------------------
typedef struct _PMS_INPUT_WORK	PMS_INPUT_WORK;

//------------------------------------------------------
/**
 * 描画ワーク型宣言
 */
//------------------------------------------------------
typedef struct _PMS_INPUT_VIEW	PMS_INPUT_VIEW;

//------------------------------------------------------
/**
 * タスクプライオリティ
 */
//------------------------------------------------------
enum {
	TASKPRI_MAIN,
	TASKPRI_VIEW_COMMAND,
	TASKPRI_VIEW_MAIN,
};

enum {
	VTASKPRI_COMMAND,
	VTASKPRI_MAIN,
};

enum {
	PMSIV_MSG_GUIDANCE,
	PMSIV_MSG_WARN_INPUT,
	PMSIV_MSG_CONFIRM_DECIDE,
	PMSIV_MSG_CONFIRM_CANCEL,
};

enum {
	BUTTON_POS_DECIDE,
	BUTTON_POS_CANCEL,
};

enum {
	CATEGORY_MODE_GROUP,
	CATEGORY_MODE_INITIAL,
};

//------------------------------------------------------
/**
 * システム関連関数プロトタイプ
 */
//------------------------------------------------------
extern u32 PMSI_GetInputMode( const PMS_INPUT_WORK* wk );
extern u32 PMSI_GetSentenceType( const PMS_INPUT_WORK* wk );
extern u32 PMSI_GetCategoryMode( const PMS_INPUT_WORK* wk );
extern PMS_WORD  PMSI_GetEditWord( const PMS_INPUT_WORK* wk, int pos );
extern STRBUF* PMSI_GetEditSourceString( const PMS_INPUT_WORK* wk, u32 heapID );
extern u32 PMSI_GetGuidanceType( const PMS_INPUT_WORK* wk );
extern u32 PMSI_GetEditAreaCursorPos( const PMS_INPUT_WORK* wk );
extern u32 PMSI_GetButtonCursorPos( const PMS_INPUT_WORK* wk );
extern u32 PMSI_GetCategoryCursorPos( const PMS_INPUT_WORK* wk );
extern u32 PMSI_GetCategoryWordMax( const PMS_INPUT_WORK* wk );
extern void PMSI_GetCategoryWord( const PMS_INPUT_WORK* wk, u32 word_num, STRBUF* buf );
extern u32 PMSI_GetWordWinCursorPos( const PMS_INPUT_WORK* wk );
extern int PMSI_GetWordWinScrollVector( const PMS_INPUT_WORK* wk );
extern BOOL PMSI_GetWordWinUpArrowVisibleFlag( const PMS_INPUT_WORK* wk );
extern BOOL PMSI_GetWordWinDownArrowVisibleFlag( const PMS_INPUT_WORK* wk );
extern int PMSI_GetTalkWindowType( const PMS_INPUT_WORK* wk );
extern u32 PMSI_GetMenuCursorPos( const PMS_INPUT_WORK* wk );

//------------------------------------------------------
/**
 * 描画関連関数プロトタイプ
 */
//------------------------------------------------------
extern PMS_INPUT_VIEW*  PMSIView_Create(const PMS_INPUT_WORK* wk, const PMS_INPUT_DATA* dwk);
extern void PMSIView_Delete( PMS_INPUT_VIEW* vwk );
extern void PMSIView_SetCommand( PMS_INPUT_VIEW* vwk, int cmd );
extern BOOL PMSIView_WaitCommand( PMS_INPUT_VIEW* vwk, int cmd );
extern BOOL PMSIView_WaitCommandAll( PMS_INPUT_VIEW* vwk );
extern u32 PMSIView_GetSentenceEditPosMax( PMS_INPUT_VIEW* wk );

#endif
