//============================================================================================
/**
 * @file	button_man.c
 * @bfief	ボタン状態管理マネージャ
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#include "common.h"
#include "gflib\touchpanel.h"

#define __POKETCH_BUTTON_MAN_GLOBAL__
#include "poketch_button.h"



//====================================================
// 定数
//====================================================
#define EVENT_TIME_MAX	(2)			// １つのボタンが発生させる時間イベントの最大数

//====================================================
// 個別ボタン状態管理構造体
//====================================================
typedef struct {
	u8  state;
	u8  touch_flag;
	u8  prev_touch_flag;
	u8  action_event;

	u16 timer;
	u16 doubletap_time;

	u16 event_time[ EVENT_TIME_MAX ];
	u16 repeat_time;

}BUTTON;

//====================================================
// ボタン全体管理
//====================================================
struct _POKETCH_BUTTON_MAN {
	const TP_HIT_TBL*	hit_tbl;
	pBmnCallBack		callback;
	u32					heap_type;
	u32					btn_cnt;
	void*				callback_param;

	BUTTON *btn;

};

//====================================================
// ボタン状態
//====================================================
enum {
	STATE_FREE = 0,
	STATE_HOLD,
	STATE_DOUBLETAP_CHECK,
	STATE_DOUBLETAP,
	STATE_RESET,
};

//====================================================
// 定数
//====================================================
#define TIMER_MAX	(0xffff)		// ホールド状態のタイマー最大値

//==============================================================
// Prototype
//==============================================================
static void ButtonStateInit( BUTTON* btn );
static void ButtonStateChange( BUTTON *btn, u32 state );
static void ButtonStateChange( BUTTON *btn, u32 state );
static void ButtonTimerInc( BUTTON *btn );
static u32 TimeEventCheck( BUTTON* btn );
static u32 StateFree( BUTTON *btn, BOOL tp_cont, BOOL tp_trg );
static u32 StateHold( BUTTON *btn, BOOL tp_cont, BOOL tp_trg );
static u32 StateDoubleTapCheck( BUTTON *btn, BOOL tp_cont, BOOL tp_trg );
static u32 StateDoubleTap( BUTTON *btn, BOOL tp_cont, BOOL tp_trg );
static u32 StateReset( BUTTON *btn, BOOL tp_cont,  BOOL tp_trg );


//------------------------------------------------------------------
/**
 * ボタン管理マネージャ作成
 *
 * @param   hit_tbl			当たり判定に使うTP_HIT_TBLテーブル
 * @param   btn_cnt			RECT_HITテーブルの要素数（NELEMSで）
 * @param   callback		ボタンの状態更新時に呼び出されるコールバック関数
 * @param   callback_param	コールバック関数に渡す任意ポインタ
 * @param   heap_type		モジュールのワーク確保に使うヒープタイプ
 *
 * @retval  BOOL		正常終了なら確保したマネージャのアドレス，
 *						確保失敗したらNULL
 */
//------------------------------------------------------------------
POKETCH_BUTTON_MAN* PBTN_Create( const TP_HIT_TBL *hit_tbl, u32 btn_cnt, pBmnCallBack callback, void *callback_param, u32 heap_type )
{
	POKETCH_BUTTON_MAN *bmn;

	GF_ASSERT( btn_cnt > 0 );

	bmn = sys_AllocMemory( heap_type, sizeof(POKETCH_BUTTON_MAN) );
	if(bmn)
	{
		bmn->heap_type = heap_type;
		bmn->callback = callback;
		bmn->hit_tbl = hit_tbl;
		bmn->btn_cnt = btn_cnt;
		bmn->callback_param = callback_param;

		bmn->btn = sys_AllocMemory( heap_type, sizeof(BUTTON) * btn_cnt );
		if(bmn->btn)
		{
			u32 i;

			for(i = 0; i < btn_cnt; i++)
			{
				ButtonStateInit( &bmn->btn[i] );
			}
		}
		else
		{
			sys_FreeMemory( heap_type, bmn );
			bmn = NULL;
		}
	}
	return bmn;
}
//------------------------------------------------------------------
/**
 * ボタン管理マネージャ消去
 *
* @param   bmn		PBTN_Createで確保したマネージャのアドレス
 *
 */
//------------------------------------------------------------------
void PBTN_Delete( POKETCH_BUTTON_MAN *bmn )
{
	GF_ASSERT( bmn );
	sys_FreeMemory( bmn->heap_type, bmn->btn );
	sys_FreeMemory( bmn->heap_type, bmn );
}

//------------------------------------------------------------------
/**
 * ボタン管理マネージャメイン（毎フレーム呼び出し）
 *
 * @param   bmn		
 *
 */
//------------------------------------------------------------------
void PBTN_Main( POKETCH_BUTTON_MAN *bmn )
{
	static u32 (* const ButtonProc[])(BUTTON*, BOOL, BOOL ) = {
		StateFree,
		StateHold,
		StateDoubleTapCheck,
		StateDoubleTap,
		StateReset,
	};

	BOOL tp_cont, tp_trg;
	u32 i, ev, touch_ev;

	tp_cont = GF_TP_GetCont();
	if( tp_cont )
	{
		tp_trg = GF_TP_GetTrg();

		for(i = 0; i < bmn->btn_cnt; i++)
		{
			bmn->btn[i].prev_touch_flag = bmn->btn[i].touch_flag;
			if(bmn->btn[i].touch_flag){
				bmn->btn[i].touch_flag = GF_TP_SingleHitCont( &bmn->hit_tbl[i] );
			}else{
				bmn->btn[i].touch_flag = GF_TP_SingleHitTrg( &bmn->hit_tbl[i] );
			}
		}
	}
	else
	{
		tp_trg = FALSE;

		for(i = 0; i < bmn->btn_cnt; i++)
		{
			bmn->btn[i].prev_touch_flag = bmn->btn[i].touch_flag;
			bmn->btn[i].touch_flag = FALSE;
		}
	}


	for(i = 0; i < bmn->btn_cnt; i++)
	{
		ev = ButtonProc[bmn->btn[i].state]( &bmn->btn[i], tp_cont, tp_trg );
		if(bmn->btn[i].touch_flag != bmn->btn[i].prev_touch_flag){
			touch_ev = bmn->btn[i].touch_flag;
		}else{
			touch_ev = BMN_TOUCH_CONT;
		}
		if(	(ev != BMN_EVENT_NULL)
		||	(touch_ev != BMN_TOUCH_CONT)
		){
			bmn->callback( i, ev, touch_ev, bmn->callback_param );
			break;
		}
	}

	for(i++ ; i < bmn->btn_cnt; i++)
	{
		ButtonProc[bmn->btn[i].state]( &bmn->btn[i], tp_cont, tp_trg );
	}
}


//------------------------------------------------------------------
/**
 * 特定ボタンにダブルタップ検知の機能を持たせる
 *
 * @param   bmn		マネージャワーク
 * @param   idx		ボタンインデックス
 * @param   time	ダブルタップ検知フレーム数
 *
 */
//------------------------------------------------------------------
void PBTN_SetDoubleTapTime( POKETCH_BUTTON_MAN *bmn, u32 idx, u16 time )
{
	bmn->btn[idx].doubletap_time = time;
}
//------------------------------------------------------------------
/**
 * 特定ボタンに一定時間ホールドでイベント発生の機能を持たせる
 *
 * @param   bmn		マネージャワーク
 * @param   idx		ボタンインデックス
 * @param   event_num		イベントナンバー
 * @param   time		イベント発生するホールド時間（フレーム）
 *
 */
//------------------------------------------------------------------
void PBTN_SetEventTime( POKETCH_BUTTON_MAN *bmn, u32 idx, u32 event_num, u16 time )
{
	bmn->btn[idx].event_time[event_num] = time;
}
//------------------------------------------------------------------
/**
 * 特定ボタンにリピート間隔をセット
 *
 * @param   bmn		
 * @param   idx		
 * @param   time		
 *
 */
//------------------------------------------------------------------
void PBTN_SetRepeatTime( POKETCH_BUTTON_MAN *bmn, u32 idx, u16 time )
{
	bmn->btn[idx].repeat_time = time;
}

//------------------------------------------------------------------
/**
 * ボタン状態を強制リセット
 *
 * @param   bmn		マネージャワーク
 * @param   idx		ボタンインデックス
 *
 */
//------------------------------------------------------------------
void PBTN_ResetState( POKETCH_BUTTON_MAN* bmn, u32 idx )
{
	bmn->btn[idx].timer = 0;
	bmn->btn[idx].state = STATE_RESET;
}

//------------------------------------------------------------------
/**
 * ボタンワーク初期化
 *
 * @param   btn		ボタンワーク
 *
 */
//------------------------------------------------------------------
static void ButtonStateInit( BUTTON* btn )
{
	u32 i;

	btn->state = STATE_FREE;
	btn->touch_flag = FALSE;
	btn->prev_touch_flag = FALSE;
	btn->timer = 0;
	btn->doubletap_time = 0;	// デフォルトでは０（ダブルタップなし）

	for(i = 0; i < EVENT_TIME_MAX; i++)
	{
		btn->event_time[i] = 0;
	}

	btn->repeat_time = 0;
}
//------------------------------------------------------------------
/**
 * ボタンステータス変更
 *
 * @param   btn			ボタンワーク
 * @param   state		ステータス
 *
 */
//------------------------------------------------------------------
static void ButtonStateChange( BUTTON *btn, u32 state )
{
	btn->state = state;
	btn->timer = 0;
}
//------------------------------------------------------------------
/**
 * タイマー保持したままステータス変更
 *
 * @param   btn		
 * @param   state		
 *
 */
//------------------------------------------------------------------
static void ButtonStateChangeNoReset( BUTTON *btn, u32 state )
{
	btn->state = state;
}
//------------------------------------------------------------------
/**
 * ボタン個別タイマーインクリメント。
 *
 * @param   btn		ボタンワーク
 *
 * @retval	BOOL	TRUEでイベント発生
 */
//------------------------------------------------------------------
static void ButtonTimerInc( BUTTON *btn )
{
	if( btn->timer < TIMER_MAX ){
		btn->timer++;
	}
}

//------------------------------------------------------------------
/**
 * タイマーイベント発生ならIDを渡す
 *
 * @param   btn		ボタンワーク
 *
 * @retval  u32		イベントID（発生しなければ BUTTON_EVENT_NULL）
 */
//------------------------------------------------------------------
static u32 TimeEventCheck( BUTTON* btn )
{
	u32 i;

	for(i = 0; i < EVENT_TIME_MAX; i++)
	{
		if(btn->event_time[i] == btn->timer)
		{
			return BMN_EVENT_TIMER0 + i;
		}
	}


	return BMN_EVENT_NULL;
}


//------------------------------------------------------------------
/**
 * ボタン状態：初期状態
 *
 * @param   btn			ボタンワーク
 * @param   tp_cont		タッチパネルContフラグ
 * @param   tp_trg		タッチパネルTrgフラグ
 *
 * @retval  u32		発生したイベントタイプ
 */
//------------------------------------------------------------------
static u32 StateFree( BUTTON *btn, BOOL tp_cont, BOOL tp_trg )
{
	if(btn->touch_flag){
		if(tp_trg){
			ButtonStateChange( btn, STATE_HOLD );
			return BMN_EVENT_TOUCH;
		}
	}
	return BMN_EVENT_NULL;
}
//------------------------------------------------------------------
/**
 * ボタン状態：押されている
 *
 * @param   btn			ボタンワーク
 * @param   tp_cont		タッチパネルContフラグ
 * @param   tp_trg		タッチパネルTrgフラグ
 *
 * @retval  u32		発生したイベントタイプ
 */
//------------------------------------------------------------------
static u32 StateHold( BUTTON *btn, BOOL tp_cont, BOOL tp_trg )
{
	ButtonTimerInc( btn );

	// ボタン押しっぱ
	if( btn->touch_flag ){
		u32 event_idx;

		event_idx = TimeEventCheck( btn );

		if( event_idx != BMN_EVENT_NULL )
		{
			return event_idx;
		}

		if( btn->repeat_time != 0 && btn->timer >= btn->repeat_time )
		{
			btn->timer = 0;
			return BMN_EVENT_REPEAT;
		}

	}
	// スクリーンには触ってるけどボタン押してない
	else if(tp_cont){
		ButtonStateChange( btn, STATE_FREE );
		return BMN_EVENT_OUT;
	}
	// スクリーンに触ってない
	else{
		if(btn->doubletap_time){
			ButtonStateChangeNoReset( btn, STATE_DOUBLETAP_CHECK );
		}else{
			ButtonStateChange( btn, STATE_FREE );
			return BMN_EVENT_TAP;
		}
	}

	return BMN_EVENT_NULL;
}
//------------------------------------------------------------------
/**
 * ボタン状態：離されて、ダブルタップがあるかチェック
 *
 * @param   btn			ボタンワーク
 * @param   tp_cont		タッチパネルContフラグ
 * @param   tp_trg		タッチパネルTrgフラグ
 *
 * @retval  u32		発生したイベントタイプ
 */
//------------------------------------------------------------------
static u32 StateDoubleTapCheck( BUTTON *btn, BOOL tp_cont, BOOL tp_trg )
{
	ButtonTimerInc( btn );

	if( btn->timer > btn->doubletap_time ){
		ButtonStateChange( btn, STATE_FREE );
		return BMN_EVENT_TAP;
	}

	if( btn->touch_flag && tp_trg )
	{
		ButtonStateChange( btn, STATE_DOUBLETAP );
		return BMN_EVENT_DOUBLETAP;
	}

	return BMN_EVENT_NULL;
}
//------------------------------------------------------------------
/**
 * ダブルタップ確定後
 *
 * @param   btn			ボタンワーク
 * @param   tp_cont		タッチパネルContフラグ
 * @param   tp_trg		タッチパネルTrgフラグ
 *
 * @retval  u32		発生したイベントタイプ
 */
//------------------------------------------------------------------
static u32 StateDoubleTap( BUTTON *btn, BOOL tp_cont, BOOL tp_trg )
{
	// ボタン押しっぱ
	if( btn->touch_flag ){

		ButtonTimerInc( btn );

	}else{
		ButtonStateChange( btn, STATE_FREE );
	}
	return BMN_EVENT_NULL;
}
//------------------------------------------------------------------
/**
 * 強制リセット後
 *
 * @param   btn			ボタンワーク
 * @param   tp_cont		タッチパネルContフラグ
 * @param   tp_trg		タッチパネルTrgフラグ
 *
 * @retval  u32		発生したイベントタイプ
 */
//------------------------------------------------------------------
static u32 StateReset( BUTTON *btn, BOOL tp_cont,  BOOL tp_trg )
{
	if( btn->touch_flag == FALSE )
	{
		ButtonStateChange( btn, STATE_FREE );
	}
	return BMN_EVENT_NULL;
}

