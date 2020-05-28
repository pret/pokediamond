//============================================================================================
/**
 * @file	box_sound_def.h
 * @bfief	ボックス画面サウンドナンバー定義
 * @author	taya
 * @date	06.02.15
 */
//============================================================================================

#ifndef __BOX_SOUND_DEF_H__
#define __BOX_SOUND_DEF_H__

#include "system\snd_tool.h"


#define  SOUND_LOG_IN			(SEQ_SE_DP_PC_LOGIN)	// ボックス画面開始
#define  SOUND_LOG_OFF			(SEQ_SE_DP_PC_LOGOFF)	// ボックス画面終了
#define  SOUND_MOVE_CURSOR		(SEQ_SE_DP_SELECT)		// カーソル移動
#define  SOUND_DECIDE			(SEQ_SE_DP_DECIDE)		// 決定音
//#define  SOUND_DECIDE			(SEQ_SE_DP_BUTTON3)		// 決定音
#define  SOUND_CANCEL			(SEQ_SE_DP_DECIDE)		// キャンセル音
#define  SOUND_CHANGE_TRAY		(SEQ_SE_DP_SELECT)		// トレイ切り替え
//#define  SOUND_CHANGE_TRAY		(SEQ_SE_DP_CLOSE2)		// トレイ切り替え
//#define  SOUND_OPEN_PARTY_TRAY	(SEQ_SE_DP_DECIDE)		// 手持ちウィンドウを開く
//#define  SOUND_OPEN_PARTY_TRAY	(SEQ_SE_DP_OPEN2)		// 手持ちウィンドウを開く
#define  SOUND_OPEN_PARTY_TRAY	(SEQ_SE_DP_OPEN7)		// 手持ちウィンドウを開く
//#define  SOUND_CLOSE_PARTY_TRAY	(SEQ_SE_DP_DECIDE)		// 手持ちウィンドウを閉じる
//#define  SOUND_CLOSE_PARTY_TRAY	(SEQ_SE_DP_CLOSE2)		// 手持ちウィンドウを閉じる
#define  SOUND_CLOSE_PARTY_TRAY	(SEQ_SE_DP_CLOSE7)		// 手持ちウィンドウを閉じる


#define  SOUND_DISP_MENU		(SOUND_DECIDE)			// メニュー項目表示
#define  SOUND_SELECT_MENU		(SOUND_MOVE_CURSOR)		// メニュー選択項目変更

//#define  SOUND_SUB_BUTTON		(SOUND_DECIDE)			// サブ画面ボタン押した
#define  SOUND_SUB_BUTTON		(SEQ_SE_DP_BUTTON9)		// サブ画面ボタン押した

#define  SOUND_SUB_MOVE_ICON	(SOUND_MOVE_CURSOR)		// サブ画面アイコン移動音

//#define  SOUND_POKE_CATCH		(SEQ_SE_DP_SELECT)	// ポケモンつかむ
#define  SOUND_POKE_CATCH		(SEQ_SE_DP_BOX02)	// ポケモンつかむ

//#define  SOUND_POKE_PUT		(SEQ_SE_DP_SELECT)	// ポケモンおく
#define  SOUND_POKE_PUT			(SEQ_SE_DP_BOX01)	// ポケモンおく

#define  SOUND_POKE_SWAP		(SEQ_SE_DP_SELECT)	// ポケモン入れ替える


#define  SOUND_ITEM_WITHDRAW	(SOUND_DECIDE)		// アイテムあずかる
#define  SOUND_ITEM_SET			(SOUND_DECIDE)		// アイテムもたせる
#define  SOUND_ITEM_SWAP		(SOUND_DECIDE)		// アイテムとりかえる

//#define  SOUND_DISABLE_BUTTON	(SOUND_DECIDE)		// 押せないボタンを押したとき
#define  SOUND_DISABLE_BUTTON	(SEQ_SE_DP_BOX03)	// 押せないボタンを押したとき

#define  SOUND_WARNING			(SEQ_SE_DP_BOX03)	// 最後の１体を逃がそうとした時などの警告音



#endif
