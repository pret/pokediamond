//============================================================================================
/**
 * @file	poketch_a02_c.c
 * @bfief	ポケッチ（アプリNo02 = 電卓）　コントロール
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#include <nitro/sinit.h>
#include "common.h"
#include "gflib\touchpanel.h"
#include "system\lib_pack.h"
#include "poketool\monsno.h"
#include "savedata\zukanwork.h"

#include "poketch_prv.h"
#include "poketch_a02.h"
#include "poketch_button.h"

//==============================================================
// Work
//==============================================================
typedef struct {
	u8        main_seq;
	u8        seq;
	u8        next_main_seq;
	u8        quit_req_flag;

	u8        dot_on_flag;
	u8        operation;
	u16       action_button_id;

	u32       cmd_req;

	POKETCH_BUTTON_MAN*	button_man;

	CONTACT_WORK*   conwk;
	POKETCH_A02_VIEWWORK*	vwk;
	POKETCH_A02_VIEW_PARAM  vpara;


}APPWORK;

//==============================================================
// シーケンス
//==============================================================
enum {
	SEQ_INIT,
	SEQ_INPUT_NUM1,
	SEQ_INPUT_OP,
	SEQ_INPUT_NUM2,
	SEQ_DISPANS,
	SEQ_OVERFLOW,
	SEQ_QUIT,
};

//==============================================================
// ボタン位置（enum BUTTON_ID に対応）
//==============================================================
#define ORGP(c)		((c)*8)
#define ENDP(c)		((c)*8+7)

static const TP_HIT_TBL ButtonRectData[] = {

	{  ORGP(18), ENDP(21),  ORGP(4), ENDP(11),  },	// 0
	{  ORGP(14), ENDP(17),  ORGP(4),  ENDP(7),  },	// 1
	{  ORGP(14), ENDP(17),  ORGP(8), ENDP(11),  },	// 2
	{  ORGP(14), ENDP(17), ORGP(12), ENDP(15),  },	// 3
	{  ORGP(10), ENDP(13),  ORGP(4),  ENDP(7),  },	// 4
	{  ORGP(10), ENDP(13),  ORGP(8), ENDP(11),  },	// 5
	{  ORGP(10), ENDP(13), ORGP(12), ENDP(15),  },	// 6
	{   ORGP(6),  ENDP(9),  ORGP(4),  ENDP(7),  },	// 7
	{   ORGP(6),  ENDP(9),  ORGP(8), ENDP(11),  },	// 8
	{   ORGP(6),  ENDP(9), ORGP(12), ENDP(15),  },	// 9

	{  ORGP(18), ENDP(21), ORGP(12), ENDP(15),  },	// . 
	{  ORGP(10), ENDP(13), ORGP(20), ENDP(23),  },	// -
	{  ORGP(10), ENDP(13), ORGP(16), ENDP(19),  },	// +
	{  ORGP(14), ENDP(17), ORGP(16), ENDP(19),  },	// *
	{  ORGP(14), ENDP(17), ORGP(20), ENDP(23),  },	// /
	{  ORGP(18), ENDP(21), ORGP(16), ENDP(23),  },	// =
	{   ORGP(6),  ENDP(9), ORGP(16), ENDP(23),  },	// Clear

};

#undef ORGP
#undef ENDP


//==============================================================
// Prototype
//==============================================================
static void NitroStaticInit(void);
static BOOL Poketch_A02_Init(void **wk_ptr, CONTACT_WORK* contact_wk, GF_BGL_INI* bgl, u32 param);
static BOOL WorkSetup(APPWORK *wk, u32 param, GF_BGL_INI* bgl );
static void WorkCleanup(APPWORK *wk);
static void Poketch_A02_Main(TCB_PTR tcb, void *wk_adrs);
static void Poketch_A02_Quit(void *wk_adrs);
static void ChangeSeq(APPWORK *wk, u32 seq);
static void BmnCallback( u32 btn_idx, u32 event, u32 touch_event, void *wk_adrs );
static BOOL SeqInit(APPWORK *wk);
static BOOL SeqInputNum1(APPWORK *wk);
static BOOL SeqInputOp( APPWORK *wk );
static BOOL SeqInputNum2(APPWORK *wk);
static BOOL SeqDispAns(APPWORK *wk);
static BOOL SeqOverFlow(APPWORK *wk);
static void ClearButtonProc( APPWORK *wk );
static BOOL CalcProc( APPWORK *wk, u32 op );
static BOOL SeqQuit(APPWORK *wk);
static void PlayVoice( APPWORK* wk, const REAL_NUMBER* rn );



//------------------------------------------------------------------
/**
 * アプリの制御関数アドレスをメインコントロールに渡す
 */
//------------------------------------------------------------------
static void NitroStaticInit(void)
{
	PoketchSetAppProc(Poketch_A02_Init, Poketch_A02_Quit);
}

//------------------------------------------------------------------
/**
 * アプリ初期化関数
 *
 * @param   wk_ptr		ワークアドレスを保存するポインタのアドレス
 *
 */
//------------------------------------------------------------------
static BOOL Poketch_A02_Init(void **wk_ptr, CONTACT_WORK* contact_wk, GF_BGL_INI* bgl, u32 param)
{
	APPWORK *wk = (APPWORK*)sys_AllocMemory( POKETCH_APP_CTRL_HEAPID, sizeof(APPWORK));

	if(wk != NULL)
	{
		if(WorkSetup( wk, param, bgl ))
		{
			wk->conwk = contact_wk;
			TCB_Add(Poketch_A02_Main, wk, POKETCH_APP_TASKPRI);
			*wk_ptr = wk;

			return TRUE;
		}
	}

	return FALSE;
}
//------------------------------------------------------------------
/**
 * アプリワークセットアップ
 *
 * @param   wk		ワークポインタ
 *
 * @retval  BOOL	TRUEで成功
 */
//------------------------------------------------------------------
static BOOL WorkSetup(APPWORK *wk, u32 param, GF_BGL_INI* bgl )
{
	if(Poketch_A02_SetViewWork( &(wk->vwk), &(wk->vpara), bgl ))
	{
		wk->main_seq = SEQ_INIT;
		wk->seq = 0;
		wk->quit_req_flag = FALSE;

		wk->next_main_seq = SEQ_INIT;
		wk->dot_on_flag = FALSE;

		wk->action_button_id = BUTTON_ID_MAX;
		wk->cmd_req = CMD_NULL;

		RNUM_Create( &wk->vpara.num1, DISP_COLUMN_MAX );
		RNUM_Create( &wk->vpara.num2, DISP_COLUMN_MAX );
		RNUM_Create( &wk->vpara.ans, DISP_COLUMN_MAX );

		if(wk->vpara.num1 == NULL || wk->vpara.num2 == NULL || wk->vpara.ans == NULL)
		{
			return FALSE;
		}

		wk->button_man = PBTN_Create( ButtonRectData, NELEMS(ButtonRectData), BmnCallback, wk, POKETCH_APP_CTRL_HEAPID );
		if(wk->button_man == NULL)
		{
			return FALSE;
		}
	}
	return TRUE;
}
//------------------------------------------------------------------
/**
 * アプリワーククリーンアップ
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
static void WorkCleanup(APPWORK *wk)
{
	if( wk->vpara.num1 ){ RNUM_Delete( wk->vpara.num1 ); }
	if( wk->vpara.num2 ){ RNUM_Delete( wk->vpara.num2 ); }
	if( wk->vpara.ans ){ RNUM_Delete( wk->vpara.ans ); }
	if( wk->button_man ){ PBTN_Delete( wk->button_man ); }

	Poketch_AOO_DeleteViewWork( wk->vwk );

}

//------------------------------------------------------------------
/**
 * アプリメイン関数
 *
 * @param   wk_adrs		ワークアドレス
 *
 */
//------------------------------------------------------------------
static void Poketch_A02_Main(TCB_PTR tcb, void *wk_adrs)
{
	static BOOL (* const seqtbl[])(APPWORK*) = {
		SeqInit,
		SeqInputNum1,
		SeqInputOp,
		SeqInputNum2,
		SeqDispAns,
		SeqOverFlow,
		SeqQuit,
	};

	APPWORK *wk = (APPWORK*)wk_adrs;

	if(wk->quit_req_flag)
	{
		ChangeSeq( wk, SEQ_QUIT );
		wk->quit_req_flag = FALSE;
	}


	if( wk->main_seq < NELEMS(seqtbl) )
	{
		wk->action_button_id = BUTTON_ID_MAX;
		PoketchButtonMainCall( wk->conwk, wk->button_man );

		if( seqtbl[wk->main_seq](wk) )
		{
			WorkCleanup( wk );
			sys_FreeMemoryEz(wk);
			TCB_Delete(tcb);
			PoketchNoticeAppEnd( wk->conwk );
		}
	}
	else
	{
		SDK_ASSERT(0);
	}
}
//------------------------------------------------------------------
/**
 * アプリ終了関数
 *
 * @param   wk_adrs		ワークアドレス
 *
 */
//------------------------------------------------------------------
static void Poketch_A02_Quit(void *wk_adrs)
{
	((APPWORK*)wk_adrs)->quit_req_flag = TRUE;
}
//------------------------------------------------------------------
/**
 * シーケンス変更
 *
 * @param   wk		ワークポインタ
 * @param   seq		変更後のシーケンスナンバー
 *
 */
//------------------------------------------------------------------
static void ChangeSeq(APPWORK *wk, u32 seq)
{
	if(wk->quit_req_flag == FALSE)
	{
		wk->main_seq = seq;
	}
	else
	{
		wk->main_seq = SEQ_QUIT;
	}
	wk->next_main_seq = wk->main_seq;
	wk->seq = 0;
}

//------------------------------------------------------------------
/**
 * ボタン管理マネージャからのコールバック
 *
 * @param   btn_idx		
 * @param   event		
 * @param   touch_event		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void BmnCallback( u32 btn_idx, u32 event, u32 touch_event, void *wk_adrs )
{
	APPWORK *wk = (APPWORK*)wk_adrs;

	switch(touch_event){
	case BMN_TOUCH_OFF:
		wk->vpara.btn_id = btn_idx;
		Poketch_A02_SetViewCommand( wk->vwk, CMD_BUTTON_FREE );
		break;
	case BMN_TOUCH_ON:
		wk->vpara.btn_id = btn_idx;
		Poketch_A02_SetViewCommand( wk->vwk, CMD_BUTTON_PUSH );
		break;
	}

	if( event == BMN_EVENT_TAP )
	{
		wk->action_button_id = btn_idx;
	}
}

//------------------------------------------------------------------
/**
 * シーケンス：画面構築
 *
 * @param   wk			ワークポインタ
 *
 * @retval  BOOL		TRUEでアプリ終了
 */
//------------------------------------------------------------------
static BOOL SeqInit(APPWORK *wk)
{
	switch(wk->seq){
	case 0:
		Poketch_A02_SetViewCommand( wk->vwk, CMD_INIT );
		wk->seq++;
		break;

	case 1:
		if(Poketch_A02_WaitViewCommand( wk->vwk, CMD_INIT ))
		{
			PoketchNoticeAppStart( wk->conwk );
			ChangeSeq( wk, SEQ_INPUT_NUM1 );
		}
		break;
	}
	return FALSE;
}
//------------------------------------------------------------------
/**
 * シーケンス：最初の数値入力
 *
 * @param   wk		ワークポインタ
 *
 * @retval  BOOL		TRUEでアプリ終了
 */
//------------------------------------------------------------------
static BOOL SeqInputNum1(APPWORK *wk)
{
	switch(wk->seq){
	case 0:
		wk->cmd_req = CMD_NULL;

		switch( wk->action_button_id ){
		case BUTTON_ID_MAX:
			break;

		case BUTTON_CLEAR:
			ClearButtonProc( wk );
			wk->cmd_req = CMD_DISPNUM_1_OPCLEAR;
			break;

		case BUTTON_DOT:
			wk->dot_on_flag = TRUE;
			break;

		case BUTTON_PLUS:
		case BUTTON_MINUS:
		case BUTTON_DIV:
		case BUTTON_MUL:
			wk->vpara.operation = wk->action_button_id;
			wk->dot_on_flag = FALSE;
			wk->cmd_req = CMD_OPERATION;
			wk->next_main_seq = SEQ_INPUT_OP;
			break;

		case BUTTON_EQ:
			PlayVoice( wk, wk->vpara.num1 );
			RNUM_SetZero( wk->vpara.num1 );
			break;

		default:
			if(wk->dot_on_flag){
				if(RNUM_ShiftDechimal( wk->vpara.num1, wk->action_button_id )){
					wk->cmd_req = CMD_DISPNUM_1;
				}
			}
			else{
				if(RNUM_ShiftInteger( wk->vpara.num1, wk->action_button_id )){
					wk->cmd_req = CMD_DISPNUM_1;
				}
			}
		}

		if( wk->cmd_req != CMD_NULL )
		{
			Poketch_A02_SetViewCommand( wk->vwk, wk->cmd_req );
			wk->seq++;
		}
		else if( wk->next_main_seq != wk->main_seq )
		{
			ChangeSeq( wk, wk->next_main_seq );
		}
		break;

	case 1:
		if( Poketch_A02_WaitViewCommand( wk->vwk, wk->cmd_req ) )
		{
			if( wk->next_main_seq != wk->main_seq )
			{
				ChangeSeq( wk, wk->next_main_seq );
			}
			else
			{
				wk->seq = 0;
			}
		}
		break;
	}

	return FALSE;
}
//------------------------------------------------------------------
/**
 * シーケンス：計算記号（＋－×÷）入力
 *
 * @param   wk		ワークポインタ
 *
 * @retval  BOOL		TRUEでアプリ終了
 *
 */
//------------------------------------------------------------------
static BOOL SeqInputOp( APPWORK *wk )
{
	switch(wk->seq){
	case 0:
		wk->cmd_req = CMD_NULL;

		switch(wk->action_button_id){
		case BUTTON_ID_MAX:
			break;

		case BUTTON_CLEAR:
			ClearButtonProc( wk );
			wk->cmd_req = CMD_DISPNUM_1_OPCLEAR;
			wk->next_main_seq = SEQ_INPUT_NUM1;
			break;

		case BUTTON_DOT:
			RNUM_SetZero( wk->vpara.num2 );
			wk->cmd_req = CMD_DISPNUM_2;
			wk->dot_on_flag = TRUE;
			wk->next_main_seq = SEQ_INPUT_NUM2;
			break;

		case BUTTON_PLUS:
		case BUTTON_MINUS:
		case BUTTON_DIV:
		case BUTTON_MUL:
			wk->vpara.operation = wk->action_button_id;
			wk->cmd_req = CMD_OPERATION;
			break;

		case BUTTON_EQ:
			RNUM_Set( wk->vpara.num2, wk->vpara.num1 );
			if(CalcProc( wk, wk->vpara.operation ))
			{
				PlayVoice( wk, wk->vpara.ans );
				wk->cmd_req = CMD_DISPNUM_ANS;
				wk->next_main_seq = SEQ_DISPANS;
			}
			else
			{
				wk->cmd_req = CMD_OVERFLOW;
				wk->next_main_seq = SEQ_OVERFLOW;
			}
			break;

		default:
			RNUM_SetZero( wk->vpara.num2 );
			if(RNUM_ShiftInteger( wk->vpara.num2, wk->action_button_id )){
				wk->cmd_req = CMD_DISPNUM_2;
				wk->next_main_seq = SEQ_INPUT_NUM2;
			}
			break;
		}

		if( wk->cmd_req != CMD_NULL )
		{
			Poketch_A02_SetViewCommand( wk->vwk, wk->cmd_req );
			wk->seq++;
		}
		else if( wk->next_main_seq != wk->main_seq )
		{
			ChangeSeq( wk, wk->next_main_seq );
		}
		break;

	case 1:
		if( Poketch_A02_WaitViewCommand( wk->vwk, wk->cmd_req ) )
		{
			if( wk->next_main_seq != wk->main_seq )
			{
				ChangeSeq( wk, wk->next_main_seq );
			}
			else
			{
				wk->seq = 0;
			}
		}
		break;
	}

	return FALSE;
}
//------------------------------------------------------------------
/**
 * シーケンス：２番目の数値入力
 *
 * @param   wk		ワークポインタ
 *
 * @retval  BOOL		TRUEでアプリ終了
 */
//------------------------------------------------------------------
static BOOL SeqInputNum2(APPWORK *wk)
{
	switch(wk->seq){
	case 0:
		wk->cmd_req = CMD_NULL;

		switch(wk->action_button_id){
		case BUTTON_ID_MAX:
			break;

		case BUTTON_CLEAR:
			ClearButtonProc( wk );
			wk->cmd_req = CMD_DISPNUM_1_OPCLEAR;
			wk->next_main_seq = SEQ_INPUT_NUM1;
			break;

		case BUTTON_DOT:
			wk->dot_on_flag = TRUE;
			break;

		case BUTTON_PLUS:
		case BUTTON_MINUS:
		case BUTTON_DIV:
		case BUTTON_MUL:
			if(CalcProc( wk , wk->vpara.operation )){
				wk->vpara.operation = wk->action_button_id;
				wk->dot_on_flag = FALSE;
				RNUM_Set( wk->vpara.num1, wk->vpara.ans );
				wk->cmd_req = CMD_DISPNUM_ANS_OP;
				wk->next_main_seq = SEQ_INPUT_OP;
			}else{
				wk->cmd_req = CMD_OVERFLOW;
				wk->next_main_seq = SEQ_OVERFLOW;
			}
			break;

		case BUTTON_EQ:
			if( CalcProc( wk, wk->vpara.operation ) )
			{
				PlayVoice( wk, wk->vpara.ans );
				wk->cmd_req = CMD_DISPNUM_ANS;
				wk->dot_on_flag = FALSE;
				wk->next_main_seq = SEQ_DISPANS;
			}
			else
			{
				wk->cmd_req = CMD_OVERFLOW;
				wk->next_main_seq = SEQ_OVERFLOW;
			}
			break;

		default:
			if(wk->dot_on_flag){
				if(RNUM_ShiftDechimal( wk->vpara.num2, wk->action_button_id )){
					wk->cmd_req = CMD_DISPNUM_2;
				}
			}
			else{
				if(RNUM_ShiftInteger( wk->vpara.num2, wk->action_button_id )){
					wk->cmd_req = CMD_DISPNUM_2;
				}
			}
			break;
		}

		if( wk->cmd_req != CMD_NULL )
		{
			Poketch_A02_SetViewCommand( wk->vwk, wk->cmd_req );
			wk->seq++;
		}
		else if( wk->next_main_seq != wk->main_seq )
		{
			ChangeSeq( wk, wk->next_main_seq );
		}
		break;

	case 1:
		if( Poketch_A02_WaitViewCommand( wk->vwk, wk->cmd_req ) )
		{
			if( wk->next_main_seq != wk->main_seq )
			{
				ChangeSeq( wk, wk->next_main_seq );
			}
			else
			{
				wk->seq = 0;
			}
		}
		break;
	}

	return FALSE;
}
//------------------------------------------------------------------
/**
 * シーケンス：計算結果表示後の入力
 *
 * @param   wk		ワークポインタ
 *
 * @retval  BOOL		TRUEでアプリ終了
 */
//------------------------------------------------------------------
static BOOL SeqDispAns(APPWORK *wk)
{
	switch(wk->seq){
	case 0:
		wk->cmd_req = CMD_NULL;

		switch(wk->action_button_id){
		case BUTTON_ID_MAX:
			break;

		case BUTTON_CLEAR:
			ClearButtonProc( wk );
			wk->cmd_req = CMD_DISPNUM_1_OPCLEAR;
			wk->next_main_seq = SEQ_INPUT_NUM1;
			break;
		case BUTTON_DOT:
			ClearButtonProc( wk );
			wk->cmd_req = CMD_DISPNUM_1;
			wk->dot_on_flag = TRUE;
			wk->next_main_seq = SEQ_INPUT_NUM1;
			break;
		case BUTTON_PLUS:
		case BUTTON_MINUS:
		case BUTTON_DIV:
		case BUTTON_MUL:
			wk->vpara.operation = wk->action_button_id;
			wk->cmd_req = CMD_OPERATION;
			wk->dot_on_flag = FALSE;
			RNUM_Set( wk->vpara.num1, wk->vpara.ans );
			wk->next_main_seq = SEQ_INPUT_OP;
			break;
		case BUTTON_EQ:
			RNUM_Set( wk->vpara.num1, wk->vpara.ans );
			if( CalcProc( wk, wk->vpara.operation ) )
			{
				PlayVoice( wk, wk->vpara.ans );
				wk->cmd_req = CMD_DISPNUM_ANS;
				wk->dot_on_flag = FALSE;
			}
			else
			{
				wk->cmd_req = CMD_OVERFLOW;
				wk->next_main_seq = SEQ_OVERFLOW;
			}
			break;
		default:
			RNUM_SetZero( wk->vpara.num1 );
			if(RNUM_ShiftInteger( wk->vpara.num1, wk->action_button_id )){
				wk->cmd_req = CMD_DISPNUM_1;
			}
			wk->next_main_seq = SEQ_INPUT_NUM1;
			break;
		}

		if( wk->cmd_req != CMD_NULL )
		{
			Poketch_A02_SetViewCommand( wk->vwk, wk->cmd_req );
			wk->seq++;
		}
		else if( wk->next_main_seq != wk->main_seq )
		{
			ChangeSeq( wk, wk->next_main_seq );
		}
		break;

	case 1:
		if( Poketch_A02_WaitViewCommand( wk->vwk, wk->cmd_req ) )
		{
			if( wk->next_main_seq != wk->main_seq )
			{
				ChangeSeq( wk, wk->next_main_seq );
			}
			else
			{
				wk->seq = 0;
			}
		}
		break;
	}

	return FALSE;
}
//------------------------------------------------------------------
/**
 * シーケンス：桁数オーバー、ゼロ除算などのエラー表示
 *
 * @param   wk		ワークポインタ
 *
 * @retval  BOOL		TRUEでアプリ終了
 */
//------------------------------------------------------------------
static BOOL SeqOverFlow(APPWORK *wk)
{
	switch(wk->seq){
	case 0:
		wk->cmd_req = CMD_NULL;

		switch(wk->action_button_id){
		case BUTTON_ID_MAX:
			break;

		case BUTTON_CLEAR:
			ClearButtonProc( wk );
			wk->cmd_req = CMD_DISPNUM_1;
			wk->next_main_seq = SEQ_INPUT_NUM1;
			break;

		case BUTTON_DOT:
			ClearButtonProc( wk );
			wk->cmd_req = CMD_DISPNUM_1;
			wk->dot_on_flag = TRUE;
			wk->next_main_seq = SEQ_INPUT_NUM1;
			break;

		case BUTTON_PLUS:
		case BUTTON_MINUS:
		case BUTTON_DIV:
		case BUTTON_MUL:
		case BUTTON_EQ:
			break;
		default:
			ClearButtonProc( wk );
			if(RNUM_ShiftInteger( wk->vpara.num1, wk->action_button_id )){
				wk->cmd_req = CMD_DISPNUM_1;
			}
			wk->next_main_seq = SEQ_INPUT_NUM1;
			break;
		}

		if( wk->cmd_req != CMD_NULL )
		{
			Poketch_A02_SetViewCommand( wk->vwk, wk->cmd_req );
			wk->seq++;
		}
		else if( wk->next_main_seq != wk->main_seq )
		{
			ChangeSeq( wk, wk->next_main_seq );
		}
		break;

	case 1:
		if( Poketch_A02_WaitViewCommand( wk->vwk, wk->cmd_req ) )
		{
			if( wk->next_main_seq != wk->main_seq )
			{
				ChangeSeq( wk, wk->next_main_seq );
			}
			else
			{
				wk->seq = 0;
			}
		}
		break;
	}

	return FALSE;
}
//------------------------------------------------------------------
/**
 * クリアボタンが押された時のデータクリア処理
 *
 * @param   wk		ワークポインタ
 *
 */
//------------------------------------------------------------------
static void ClearButtonProc( APPWORK *wk )
{
	RNUM_SetZero(wk->vpara.num1);
	RNUM_SetZero(wk->vpara.num2);
	RNUM_SetZero(wk->vpara.ans);
	wk->vpara.operation = OP_NULL;
	wk->dot_on_flag = FALSE;
}
//------------------------------------------------------------------
/**
 * 現在のデータで計算を行う
 *
 * @param   wk		ワークポインタ
 * @param   op		計算方法
 *
 * @retval	TRUEで正常、FALSEで表示不可（ゼロ除算含む）
 *
 */
//------------------------------------------------------------------
static BOOL CalcProc( APPWORK *wk, u32 op )
{
	BOOL ret = FALSE;

	switch( op ){
	case BUTTON_PLUS:
		RNUM_Add( wk->vpara.num1, wk->vpara.num2, wk->vpara.ans );
		break;
	case BUTTON_MINUS:
		RNUM_Sub( wk->vpara.num1, wk->vpara.num2, wk->vpara.ans );
		break;
	case BUTTON_MUL:
		RNUM_Mul( wk->vpara.num1, wk->vpara.num2, wk->vpara.ans );
		break;
	case BUTTON_DIV:
		RNUM_Div( wk->vpara.num1, wk->vpara.num2, wk->vpara.ans );
		break;
	}

	return RNUM_CheckDisable( wk->vpara.ans, DISP_COLUMN_MAX );
}
//------------------------------------------------------------------
/**
 * シーケンス：終了処理
 *
 * @param   wk		ワークポインタ
 *
 * @retval  BOOL		TRUEでアプリ終了
 */
//------------------------------------------------------------------
static BOOL SeqQuit(APPWORK *wk)
{
	switch(wk->seq){
	case 0:
		Poketch_A02_SetViewCommand( wk->vwk, CMD_QUIT );
		wk->seq++;
		break;

	case 1:
		if(Poketch_A02_WaitViewCommandAll( wk->vwk ))
		{
			return TRUE;
		}
		break;
	}

	return FALSE;
}
//------------------------------------------------------------------
/**
 * 入力されたナンバーのポケモン鳴き声を鳴らす
 *
 * @param   wk		
 * @param   rn		
 *
 */
//------------------------------------------------------------------
static void PlayVoice( APPWORK* wk, const REAL_NUMBER* rn )
{
	s64  n = RNUM_GetInt( rn );
	if( n > 0 && n <= MONSNO_END )
	{
		ZUKAN_WORK* zw;
		u16 monsno;

		zw = SaveData_GetZukanWork( PoketchGetSystemSaveData(wk->conwk) );
		if( ZukanWork_GetZenkokuZukanFlag( zw ) )
		{
			monsno = n;
		}
		else
		{
			monsno = PokeShinouNo2ZenkokuNo( (u16)n );
			OS_TPrintf("%ld -> %d\n", (u32)n, monsno );
		}

		if( (monsno > 0 && monsno <= MONSNO_END)
		&&	ZukanWork_GetPokeSeeFlag(zw, monsno)
		){
			OS_TPrintf("monsno = %d\n", monsno);
			PoketchVoicePlay( monsno );
		}

	}
}
