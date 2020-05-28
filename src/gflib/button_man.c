//============================================================================================
/**
 * @file	button_man.c
 * @bfief	ボタン状態管理マネージャ
 * @date	2005.11.08
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#include "common.h"
#include "gflib\button_man.h"




//==============================================================================
// 定数
//==============================================================================
//-----------------------------------------------
/**
 * ボタン状態
 */
//-----------------------------------------------
enum {
	STATE_FREE = 0,
	STATE_HOLD,
};

//-----------------------------------------------
/**
 * そのた
 */
//-----------------------------------------------
enum {
	BMN_EVENT_NULL = 0xffffffff,	///< ボタンイベント無効値（何もイベントが発生していない状態を現す）
	HOLD_TIMER_MAX = 0xffff,		///< タイマー最大値
};

//==============================================================================
// 構造体定義
//==============================================================================

//----------------------------------------------
/**
 * 個別のボタン状態
 */
//----------------------------------------------
typedef struct {
	u8  state;				///< 状態
	u8  touch_flag;			///< 触られているフラグ
	u16 timer;
}BUTTON;

//----------------------------------------------
/**
 * マネージャ全体のワーク
 */
//----------------------------------------------
struct _BUTTON_MAN {
	const TP_HIT_TBL*	hit_tbl;
	u32					btn_cnt;
	pBmnCallBackFunc	callback_func;
	void*				callback_arg;

	BUTTON *btn;
};



//==============================================================================
// Prototype
//==============================================================================
static void button_state_init( BUTTON* btn );
static u32 button_proc_free( BUTTON *btn, BOOL tp_cont, BOOL tp_trg );
static u32 button_proc_hold( BUTTON *btn, BOOL tp_cont, BOOL tp_trg );
static void button_state_change( BUTTON *btn, u32 state );


//======================================================================================================
/**
 * ボタン管理マネージャ作成
 *
 * @param   hit_tbl			[in]  当たり判定テーブル
 * @param   btn_cnt			[in]  hit_tbl の要素数（=これが登録するボタンの数ということ）
 * @param   callback		[in]  ボタンイベント発生時に呼び出されるコールバック関数
 * @param   callback_arg	[in]  callback 呼び出し時に引数として渡される任意のポインタ
 * @param   heapID			[in]  マネージャ領域作成用ヒープID
 *
 * @retval  BUTTON_MAN*		マネージャポインタ
 */
//======================================================================================================
BUTTON_MAN* BMN_Create( const TP_HIT_TBL *hit_tbl, u32 btn_cnt, pBmnCallBackFunc callback, void *callback_arg, u32 heapID )
{
	BUTTON_MAN *bmn;

	GF_ASSERT( btn_cnt > 0 );

	bmn = sys_AllocMemory( heapID, sizeof(BUTTON_MAN) );
	if(bmn)
	{
		bmn->hit_tbl = hit_tbl;
		bmn->btn_cnt = btn_cnt;
		bmn->callback_func = callback;
		bmn->callback_arg = callback_arg;

		bmn->btn = sys_AllocMemory( heapID, sizeof(BUTTON) * btn_cnt );
		if(bmn->btn)
		{
			u32 i;

			for(i=0; i<btn_cnt; i++)
			{
				button_state_init( &bmn->btn[i] );
			}
		}
		else
		{
			sys_FreeMemoryEz( bmn );
			bmn = NULL;
		}
	}
	return bmn;
}
//------------------------------------------------------------------
/**
 * ボタンワーク初期化
 *
 * @param   btn		ボタンワーク
 *
 */
//------------------------------------------------------------------
static void button_state_init( BUTTON* btn )
{
	btn->state = STATE_FREE;
	btn->touch_flag = FALSE;
	btn->timer = 0;
}


//======================================================================================================
/**
 * ボタン管理マネージャ消去
 *
 * @param   bmn		マネージャポインタ
 */
//======================================================================================================
void BMN_Delete( BUTTON_MAN *bmn )
{
	GF_ASSERT( bmn );
	sys_FreeMemoryEz( bmn->btn );
	sys_FreeMemoryEz( bmn );
}

//======================================================================================================
/**
 * ボタン管理マネージャメイン
 *
 * 各ボタン状態のチェック＆更新、イベントが発生すればコールバック呼び出しを行う。
 *
 * @param   bmn		マネージャポインタ
 *
 */
//======================================================================================================
void BMN_Main( BUTTON_MAN *bmn )
{
	static u32 (* const ButtonProc[])(BUTTON*, BOOL, BOOL ) = {
		button_proc_free,
		button_proc_hold,
	};

	BOOL tp_cont, tp_trg;
	u32 i, ev;

	tp_cont = GF_TP_GetCont();
	if( tp_cont )
	{
		tp_trg = GF_TP_GetTrg();

		for(i = 0; i < bmn->btn_cnt; i++)
		{
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
			bmn->btn[i].touch_flag = FALSE;
		}
	}


	for(i=0; i<bmn->btn_cnt; i++)
	{
		ev = ButtonProc[bmn->btn[i].state]( &bmn->btn[i], tp_cont, tp_trg );
		if(ev != BMN_EVENT_NULL)
		{
			bmn->callback_func( i, ev, bmn->callback_arg );
		}
	}
/*
	for(i++ ; i < bmn->btn_cnt; i++)
	{
		ButtonProc[bmn->btn[i].state]( &bmn->btn[i], tp_cont, tp_trg );
	}
*/

}
//------------------------------------------------------------------
/**
 * ボタン状態：触られていない
 *
 * @param   btn			ボタンワーク
 * @param   tp_cont		タッチパネルContフラグ
 * @param   tp_trg		タッチパネルTrgフラグ
 *
 * @retval  u32		発生したイベントタイプ
 */
//------------------------------------------------------------------
static u32 button_proc_free( BUTTON *btn, BOOL tp_cont, BOOL tp_trg )
{
	if(btn->touch_flag){
		if(tp_trg){
			button_state_change( btn, STATE_HOLD );
			return BMN_EVENT_TOUCH;
		}
	}
	return BMN_EVENT_NULL;
}
//------------------------------------------------------------------
/**
 * ボタン状態：触られている
 *
 * @param   btn			ボタンワーク
 * @param   tp_cont		タッチパネルContフラグ
 * @param   tp_trg		タッチパネルTrgフラグ
 *
 * @retval  u32		発生したイベントタイプ
 */
//------------------------------------------------------------------
static u32 button_proc_hold( BUTTON *btn, BOOL tp_cont, BOOL tp_trg )
{
	// ボタン押しっぱ
	if( btn->touch_flag )
	{
		if( btn->timer < HOLD_TIMER_MAX )
		{
			btn->timer++;
		}
		return BMN_EVENT_HOLD;
	}
	// ボタン押してないけどスクリーンには触っている
	else if(tp_cont)
	{
		button_state_change( btn, STATE_FREE );
		return BMN_EVENT_SLIDEOUT;
	}
	// スクリーンに触ってない
	else
	{
		button_state_change( btn, STATE_FREE );
		return BMN_EVENT_RELEASE;
	}

	return BMN_EVENT_NULL;
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
static void button_state_change( BUTTON *btn, u32 state )
{
	btn->state = state;
	btn->timer = 0;
}



//======================================================================================================
/**
 * ボタンがホールド状態にある時、そのホールド時間（フレーム数）を返す
 *
 * @param   bmn		マネージャワーク
 * @param   idx		ボタンインデックス
 *
 * @retval  u32		ホールド中ならホールド時間、ホールド中以外なら０
 */
//======================================================================================================
u32 BMN_GetHoldFrameCount( BUTTON_MAN* bmn, u32 idx )
{
	BUTTON *btn = &bmn->btn[idx];

	if(btn->state == STATE_HOLD)
	{
		return btn->timer;
	}
	return 0;
}
