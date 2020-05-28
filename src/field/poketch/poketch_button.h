//============================================================================================
/**
 * @file	poketch_button.h
 * @bfief	ボタン状態管理マネージャ
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#ifndef __BUTTON_MAN_H__
#define __BUTTON_MAN_H__

#include "gflib/touchpanel.h"



enum BMN_EVENT {
	BMN_EVENT_NULL = 0,
	BMN_EVENT_TOUCH,		
	BMN_EVENT_OUT,			
	BMN_EVENT_TAP,			// シングルタップ確定で発生
	BMN_EVENT_DOUBLETAP,	// ダブルタップ確定で発生
	BMN_EVENT_TIMER0,
	BMN_EVENT_TIMER1,
	BMN_EVENT_REPEAT,
};

enum  BMN_TOUCH {
	BMN_TOUCH_OFF,			// 前フレーム触れてない→今フレーム触れた
	BMN_TOUCH_ON,			// 前フレーム触れていた→今フレーム触れてない
	BMN_TOUCH_CONT,			// 前フレームと変わらず
};


//---------------------------------------------------------------------
/**
 *	ボタンマネージャ型宣言
 */
//---------------------------------------------------------------------
typedef struct _POKETCH_BUTTON_MAN	POKETCH_BUTTON_MAN;


//---------------------------------------------------------------------
/**
 *	ボタンマネージャからのコールバック関数型。引数の内容は以下の順。
 *
 *	u32		ボタンのインデックス
 *	u32		発生したイベント（BMN_EVENT）
 *	u32		接触状況の更新（BMN_TOUCH）
*	void*	PBTN_Createで渡したワークポインタ
 *
 */
//---------------------------------------------------------------------
typedef void (*pBmnCallBack)(u32, u32, u32, void*);



extern POKETCH_BUTTON_MAN* PBTN_Create( const TP_HIT_TBL *hit_tbl, u32 btn_cnt, pBmnCallBack callback, void *callback_param, u32 heap_type );
extern void PBTN_Delete( POKETCH_BUTTON_MAN *bmn );
extern void PBTN_Main( POKETCH_BUTTON_MAN *bmn );
extern void PBTN_SetDoubleTapTime( POKETCH_BUTTON_MAN *bmn, u32 idx, u16 time );
extern void PBTN_SetEventTime( POKETCH_BUTTON_MAN *bmn, u32 idx, u32 event_num, u16 time );
extern void PBTN_SetRepeatTime( POKETCH_BUTTON_MAN *bmn, u32 idx, u16 time );
extern void PBTN_ResetState( POKETCH_BUTTON_MAN* bmn, u32 idx );



#endif
