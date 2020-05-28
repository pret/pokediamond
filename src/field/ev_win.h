//==============================================================================================
/**
 * @file	ev_win.h
 * @brief	イベントウィンドウ
 * @author	Satoshi Nohara
 * @date	2005.07.29
 */
//==============================================================================================
#ifndef EV_WIN_H
#define EV_WIN_H


//==============================================================================================
//
//	定義
//
//==============================================================================================
#define EV_WIN_B_CANCEL			(0xfffe)		//Bキャンセル
//#define EV_WIN_LIST_END		(0xfffd)		//項目の終了コード
#define EV_WIN_NOTHING			(0xeeee)		//初期化の値
#define	EV_WIN_LIST_LABEL		(0xfa)			//リスト使用時にラベルを指定する定義(スクリプト用)
#define	EV_WIN_TALK_MSG_NONE	(0xff)			//リスト使用時の会話メッセージなし

//----------------------------------------------------------------------------------------------
//	フロア定義
//
//	・WK_ELEVATOR_FLOORに代入される値
//	・カーソル位置に対応しているので注意
//	・階ナンバーの文字列はスクリプトでセットする
//----------------------------------------------------------------------------------------------
#define FLOOR_NOTHING			(0xffff)		//TCB削除する値

#define FLOOR_C05R0103_2F		(0)
#define FLOOR_C05R0103_1F		(1)

#define FLOOR_C05R0803_2F		(0)
#define FLOOR_C05R0803_1F		(1)

#define FLOOR_C07FS0101_8F		(0)
#define FLOOR_C07FS0101_4F		(1)
#define FLOOR_C07FS0101_3F		(2)
#define FLOOR_C07FS0101_2F		(3)

#define FLOOR_T07R0103_2F		(0)
#define FLOOR_T07R0103_1F		(1)

#define FLOOR_C08R0802_2F		(0)
#define FLOOR_C08R0802_1F		(1)

#define FLOOR_C07R0206_5F		(0)
#define FLOOR_C07R0206_4F		(1)
#define FLOOR_C07R0206_3F		(2)
#define FLOOR_C07R0206_2F		(3)
#define FLOOR_C07R0206_1F		(4)

#define FLOOR_C01R0208_4F		(0)
#define FLOOR_C01R0208_3F		(1)
#define FLOOR_C01R0208_2F		(2)
#define FLOOR_C01R0208_1F		(3)

//アセンブラでincludeされている場合は、下の宣言を無視できるようにifndefで囲んである
#ifndef	__ASM_NO_DEF_


#include "common.h"
#include "gflib/msg_print.h"					//STRCODE
#include "system/msgdata.h"						//MSGDATA_MANAGER


//==============================================================================================
//
//	イベントウィンドウワークへの不完全型ポインタ
//
//==============================================================================================
typedef	struct _EV_WIN_WORK EV_WIN_WORK;


//==============================================================================================
//
//	extern宣言
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	BMPメニュー　初期化
 *
 * @param	x			ウィンドウ表示X座標
 * @param	y			ウィンドウ表示X座標
 * @param	cursor		カーソル位置
 * @param	cancel		Bキャンセルフラグ(TRUE=有効、FALSE=無効)
 * @param	work		結果を代入するワークのポインタ
 * @param	wordset		WORDSET型のポインタ
 *
 * @retval	"EV_WIN_WORK型のアドレス、NULLは失敗"
 */
//--------------------------------------------------------------
extern EV_WIN_WORK* CmdEvBmpMenu_Init(FIELDSYS_WORK* fsys, u8 x, u8 y, u8 cursor, u8 cancel, u16* work, WORDSET* wordset, GF_BGL_BMPWIN* talk_bmpwin, MSGDATA_MANAGER* msgman );

//--------------------------------------------------------------
/**
 * @brief	BMPメニュー　リスト作成
 *
 * @param	wk			EV_WIN_WORK型のポインタ
 * @param	msg_id		メッセージID
 * @param	param		BMPMENUパラメータ
 *
 * @retval	none
 */
//--------------------------------------------------------------
extern void CmdEvBmpMenu_MakeList( EV_WIN_WORK* wk, u32 msg_id, u32 param  );

//--------------------------------------------------------------
/**
 * @brief	BMPメニュー　開始
 *
 * @param	wk			EV_WIN_WORK型のポインタ
 * @param	msg_id		メッセージID
 * @param	param		BMPMENUパラメータ
 *
 * @retval	none
 */
//--------------------------------------------------------------
extern void CmdEvBmpMenu_Start( EV_WIN_WORK* wk );

//--------------------------------------------------------------
/**
 * @brief	BMPメニュー縦横　開始
 *
 * @param	wk			EV_WIN_WORK型のポインタ
 * @param	x_max		横方向項目最大数(必ず1以上)
 *
 * @retval	none
 */
//--------------------------------------------------------------
extern void CmdEvBmpMenuHV_Start( EV_WIN_WORK* wk, u8 x_max );

//--------------------------------------------------------------
/**
 * @brief	BMPリスト　初期化
 *
 * @param	x			ウィンドウ表示X座標
 * @param	y			ウィンドウ表示X座標
 * @param	cursor		カーソル位置
 * @param	cancel		Bキャンセルフラグ(TRUE=有効、FALSE=無効)
 * @param	work		結果を代入するワークのポインタ
 * @param	wordset		WORDSET型のポインタ
 *
 * @retval	"EV_WIN_WORK型のアドレス、NULLは失敗"
 */
//--------------------------------------------------------------
extern EV_WIN_WORK* CmdEvBmpList_Init( FIELDSYS_WORK* fsys, u8 x, u8 y, u8 cursor, u8 cancel, u16* work, WORDSET* wordset, GF_BGL_BMPWIN* talk_bmpwin, MSGDATA_MANAGER* msgman );

//--------------------------------------------------------------
/**
 * @brief	BMPリスト　リスト作成
 *
 * @param	wk			EV_WIN_WORK型のポインタ
 * @param	msg_id		メッセージID
 * @param	param		BMPLISTパラメータ
 *
 * @retval	none
 */
//--------------------------------------------------------------
extern void CmdEvBmpList_MakeList( EV_WIN_WORK* wk, u32 msg_id, u32 talk_msg_id, u32 param  );

//--------------------------------------------------------------
/**
 * @brief	BMPリスト　開始
 *
 * @param	wk			EV_WIN_WORK型のポインタ
 *
 * @retval	none
 */
//--------------------------------------------------------------
extern void CmdEvBmpList_Start( EV_WIN_WORK* wk );

//--------------------------------------------------------------
/**
 * @brief	BMPリスト　強制終了
 *
 * @param	wk			EV_WIN_WORK型のポインタ
 *
 * @retval	none
 */
//--------------------------------------------------------------
extern void EvBmpMenu_Del( EV_WIN_WORK* wk );

//--------------------------------------------------------------
/**
 * @brief	BMPメニュー　フロア表示
 *
 * @param	fsys		FIELDSYS_WORK型のポインタ
 * @param	x			ウィンドウ表示X座標
 * @param	y			ウィンドウ表示X座標
 * @param	work		結果を代入するワークのポインタ
 * @param	wordset		WORDSET型のポインタ
 *
 * @retval	none
 */
//--------------------------------------------------------------
extern void ElevatorFloorWrite(FIELDSYS_WORK* fsys, u8 x, u8 y, u16* work, WORDSET* wordset);

//--------------------------------------------------------------
/**
 * 特殊接続先から、現在のフロアナンバーを取得
 *
 * @param   zone_id		ゾーンID
 *
 * @retval  "フロアナンバー"
 */
//--------------------------------------------------------------
extern u16 ElevatorNowFloorGet( int zone_id );




//--------------------------------------------------------------------------------------------
/**
 * 所持金ウィンドウ表示
 *
 * @param	fsys
 * @param	wk
 * @param	x		表示X座標
 * @param	y		表示Y座標
 *
 * @return	確保したBMPウィンドウ
 *
 *	EvWin_GoldWinDelで削除すること！
 */
//--------------------------------------------------------------------------------------------
extern GF_BGL_BMPWIN * EvWin_GoldWinPut( FIELDSYS_WORK * fsys, u8 x, u8 y );

//--------------------------------------------------------------------------------------------
/**
 * 所持金ウィンドウ削除
 *
 * @param	wk
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
extern void EvWin_GoldWinDel( GF_BGL_BMPWIN * win );

//--------------------------------------------------------------------------------------------
/**
 * 所持金描画
 *
 * @param	fsys
 * @param	wk
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
extern void EvWin_GoldWrite( FIELDSYS_WORK * fsys, GF_BGL_BMPWIN * win );

//--------------------------------------------------------------------------------------------
/**
 * 所持コインウィンドウ表示
 *
 * @param	fsys
 * @param	wk
 * @param	x		表示X座標
 * @param	y		表示Y座標
 *
 * @return	確保したBMPウィンドウ
 *
 *	EvWin_CoinWinDelで削除すること！
 */
//--------------------------------------------------------------------------------------------
extern GF_BGL_BMPWIN * EvWin_CoinWinPut( FIELDSYS_WORK * fsys, u8 x, u8 y );

//--------------------------------------------------------------------------------------------
/**
 * 所持コインウィンドウ削除
 *
 * @param	wk
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
extern void EvWin_CoinWinDel( GF_BGL_BMPWIN * win );

//--------------------------------------------------------------------------------------------
/**
 * 所持コイン描画
 *
 * @param	fsys
 * @param	wk
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
extern void EvWin_CoinWrite( FIELDSYS_WORK * fsys, GF_BGL_BMPWIN * win );

//--------------------------------------------------------------------------------------------
/**
 * 所持バトルポイントウィンドウ表示
 *
 * @param	fsys
 * @param	wk
 * @param	x		表示X座標
 * @param	y		表示Y座標
 *
 * @return	確保したBMPウィンドウ
 *
 *	EvWin_CoinWinDel(共有で使える)で削除すること！
 */
//--------------------------------------------------------------------------------------------
extern GF_BGL_BMPWIN * EvWin_BtlPointWinPut( FIELDSYS_WORK * fsys, u8 x, u8 y );

//--------------------------------------------------------------------------------------------
/**
 * 所持バトルポイント描画
 *
 * @param	fsys
 * @param	wk
 */
//--------------------------------------------------------------------------------------------
extern void EvWin_BtlPointWrite( FIELDSYS_WORK * fsys, GF_BGL_BMPWIN * win );


#endif	__ASM_NO_DEF_


#endif	/* EV_WIN_H */


