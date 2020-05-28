//==============================================================================================
/**
 * @file	guinness_win.h
 * @brief	ギネスウィンドウ
 * @author	Satoshi Nohara
 * @date	2006.03.01
 */
//==============================================================================================
#ifndef GUINNESS_WIN_H
#define GUINNESS_WIN_H


//==============================================================================================
//
//	定義
//
//==============================================================================================
#define GUINNESS_WIN_B_CANCEL			(0xfffe)		//Bキャンセル
//#define GUINNESS_WIN_LIST_END		(0xfffd)		//項目の終了コード
#define GUINNESS_WIN_NOTHING			(0xeeee)		//初期化の値
#define	GUINNESS_WIN_LIST_LABEL		(0xfa)			//リスト使用時にラベルを指定する定義(スクリプト用)


//アセンブラでincludeされている場合は、下の宣言を無視できるようにifndefで囲んである
#ifndef	__ASM_NO_DEF_


#include "common.h"
#include "gflib/msg_print.h"					//STRCODE
#include "system/msgdata.h"						//MSGDATA_MANAGER


//#define	SE_GUINNESS_WIN_START		(SEQ_SE_DP_CALL01)	//開始音	//違う
//#define	SE_GUINNESS_WIN_START		(SEQ_SE_DP_PIKO2)	//開始音	//bank違う？
#define	SE_GUINNESS_WIN_START		(SEQ_SE_DP_UP)	//開始音


//==============================================================================================
//
//	イベントウィンドウワークへの不完全型ポインタ
//
//==============================================================================================
typedef	struct _GUINNESS_WIN_WORK GUINNESS_WIN_WORK;


//==============================================================================================
//
//	extern宣言
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	イベント擬似コマンド：ギネスウィンドウ呼び出し
 *
 * @param	x			ウィンドウ表示X座標
 * @param	y			ウィンドウ表示X座標
 * @param	cursor		カーソル位置
 * @param	cancel		Bキャンセルフラグ(TRUE=有効、FALSE=無効)
 * @param	wordset		WORDSET型のポインタ
 *
 * @retval	none
 */
//--------------------------------------------------------------
extern void EventCmd_GuinnessWin( GMEVENT_CONTROL* event, u8 x, u8 y, u8 cursor, u8 cancel, WORDSET* wordset );


#endif	__ASM_NO_DEF_


#endif	/* GUINNESS_WIN_H */



