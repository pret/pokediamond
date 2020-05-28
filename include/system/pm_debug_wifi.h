/* WIFI用デバック定義
 *	tomoya takahashi
 */

#ifdef PM_DEBUG


#ifndef	_DEUBG_WIFI_H__
#define _DEUBG_WIFI_H__

//-------------------------------------
// このフラグを立てることにより
//　WIFI対戦AUTOﾓｰﾄﾞ
//	L+XとL+Yで2機を起動させると動く
//=====================================
//#define	_WIFI_DEBUG_TUUSHIN

#ifdef _WIFI_DEBUG_TUUSHIN
#define _WIFI_DEBUG_NONE	(0)
#define _WIFI_DEBUG_MODE_X	(1)
#define _WIFI_DEBUG_MODE_Y	(2)
// WIFIデバックワーク
typedef struct{
	u32 DEBUG_WIFI_MODE : 8;		//起動ﾓｰﾄﾞ
	u32 DEBUG_WIFI_SEQ : 8;			//フィールドでの動さシーケンス
	u32 DEBUG_WIFI_MOVE_WAIT : 12;	//動さ待ち
	u32 DEBUG_WIFI_BATTLE : 1;		//対戦中フラグ
	u32 DEBUG_WIFI_A_REQ : 1;		//A連打リクエスト
	u32 DEBUG_WIFI_B_REQ : 1;		//B連打リクエスト
	u32 DEBUG_WIFI_TOUCH_REQ : 1;	//”逃げる”タッチリクエスト
} WIFI_DEBUG_BATTLE_WK;
#endif	// _WIFI_DEBUG_TUUSHIN


#endif	// _DEUBG_WIFI_H__


#endif	// PM_DEBUG
