//============================================================================================
/**
 * @file	poketch_a17c.c
 * @bfief	ポケッチ（アプリNoa17：コイントス）　コントロール
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#include <nitro/sinit.h>
#include "common.h"
#include "gflib\touchpanel.h"
#include "system\lib_pack.h"


#include "poketch_a17.h"
#include "poketch_prv.h"

//==============================================================
// Work
//==============================================================
typedef struct {
	u8        main_seq;
	u8        seq;
	u8        quit_req_flag;

	u32       appNumber;

	VIEWPARAM  vpara;
	VIEWWORK*  vwk;
	CONTACT_WORK*  conwk;

}APPWORK;

//==============================================================
// シーケンス
//==============================================================
enum {
	SEQ_INIT,
	SEQ_IDLE,
	SEQ_QUIT,
};

//==============================================================
// Prototype
//==============================================================
static void NitroStaticInit(void);
static BOOL Poketch_A17_Init(void **wk_ptr, CONTACT_WORK* conwk, GF_BGL_INI* bgl, u32 param);
static BOOL SetupWork( APPWORK *wk, CONTACT_WORK* conwk, GF_BGL_INI* bgl, u32 param );
static void CleanupWork( APPWORK *wk );
static void Poketch_A17_Main(TCB_PTR tcb, void *wk_adrs);
static void Poketch_A17_Quit(void *wk_adrs);
static void ChangeSeq(APPWORK *wk, u32 seq);
static BOOL SeqInit(APPWORK *wk);
static BOOL SeqIdle(APPWORK *wk);
static BOOL SeqQuit(APPWORK *wk);
static BOOL check_touch_coin( void );



//------------------------------------------------------------------
/**
 * アプリの制御関数アドレスをメインコントロールに渡す
 */
//------------------------------------------------------------------
static void NitroStaticInit(void)
{
	PoketchSetAppProc(Poketch_A17_Init, Poketch_A17_Quit);
}

//------------------------------------------------------------------
/**
 * アプリ初期化関数
 *
 * @param   wk_ptr		ワークアドレスを保存するポインタのアドレス
 * @param   conwk		アプリが本体から情報を取得する際に必要となるワーク（アプリへは非公開）
 * @param   bgl			BGLモジュールヘッダ
 * @param   appNumber	アプリナンバー
 */
//------------------------------------------------------------------
static BOOL Poketch_A17_Init(void **wk_ptr, CONTACT_WORK* conwk, GF_BGL_INI* bgl, u32 appNumber)
{
	APPWORK* wk = (APPWORK*)sys_AllocMemory( POKETCH_APP_CTRL_HEAPID, sizeof(APPWORK));

	if(wk != NULL)
	{
		if(SetupWork( wk, conwk, bgl, appNumber ))
		{
			if( TCB_Add(Poketch_A17_Main, wk, POKETCH_APP_TASKPRI) != NULL )
			{
				*wk_ptr = wk;
				return TRUE;
			}
		}
		sys_FreeMemoryEz( wk );
	}

	return FALSE;
}
//------------------------------------------------------------------
/**
 * ワークのセットアップ
 *
 * @param   wk		ワークポインタ
 *
 */
//------------------------------------------------------------------
static BOOL SetupWork( APPWORK *wk, CONTACT_WORK* conwk, GF_BGL_INI* bgl, u32 appNumber )
{
	wk->appNumber = appNumber;

	if( PoketchWork_Load( appNumber, &(wk->vpara), sizeof(wk->vpara) ) == FALSE )
	{
		wk->vpara.result = 1;
	}

	if( Poketch_A17_SetViewWork( &(wk->vwk), &(wk->vpara), bgl ) )
	{
		wk->main_seq = SEQ_INIT;
		wk->seq = 0;
		wk->quit_req_flag = FALSE;
		wk->conwk = conwk;
		return TRUE;
	}

	return FALSE;
}
//------------------------------------------------------------------
/**
 * ワークのクリーンアップ
 *
 * @param   wk		ワークポインタ
 *
 */
//------------------------------------------------------------------
static void CleanupWork( APPWORK *wk )
{
	PoketchWork_Save(wk->appNumber, &(wk->vpara), sizeof(wk->vpara));

	Poketch_A17_DeleteViewWork( wk->vwk );
	sys_FreeMemoryEz( wk );
}
//------------------------------------------------------------------
/**
 * アプリメイン関数
 *
 * @param   wk_adrs		ワークアドレス
 *
 */
//------------------------------------------------------------------
static void Poketch_A17_Main(TCB_PTR tcb, void *wk_adrs)
{
	static BOOL (* const seqtbl[])(APPWORK*) = {
		SeqInit,
		SeqIdle,
		SeqQuit,
	};

	APPWORK *wk = (APPWORK*)wk_adrs;

	if( wk->main_seq < NELEMS(seqtbl) )
	{
		if( seqtbl[wk->main_seq](wk) )
		{
			CleanupWork( wk );
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
static void Poketch_A17_Quit(void *wk_adrs)
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
	wk->seq = 0;
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
		Poketch_A17_SetViewCommand( wk->vwk, CMD_INIT );
		wk->seq++;
		break;

	case 1:
		if(Poketch_A17_WaitViewCommand( wk->vwk, CMD_INIT ))
		{
			PoketchNoticeAppStart( wk->conwk );
			ChangeSeq( wk, SEQ_IDLE );
		}
		break;
	}
	return FALSE;
}
//------------------------------------------------------------------
/**
 * シーケンス：入力待ち
 *
 * @param   wk		ワークポインタ
 *
 * @retval  BOOL		TRUEでアプリ終了
 */
//------------------------------------------------------------------
static BOOL SeqIdle(APPWORK *wk)
{
	if(wk->quit_req_flag)
	{
		ChangeSeq( wk, SEQ_QUIT );
	}

	switch( wk->seq ){
	case 0:
		// コイン速度調整用
		#if 0

		if(sys.cont & PAD_BUTTON_X)
		{
			if( sys.repeat & PAD_KEY_UP )
			{
				PA17DEBUG_AddCoinSpeed( -( FX32_ONE / 4 ) );
			}
			if( sys.repeat & PAD_KEY_DOWN )
			{
				PA17DEBUG_AddCoinSpeed( ( FX32_ONE / 4 ) );
			}
		}

		if(sys.cont & PAD_BUTTON_Y)
		{
			if( sys.repeat & PAD_KEY_UP )
			{
				PA17DEBUG_AddGravity( ( FX32_ONE / 16 ) );
			}
			if( sys.repeat & PAD_KEY_DOWN )
			{
				PA17DEBUG_AddGravity( -( FX32_ONE / 16 ) );
			}
		}

		#endif

		if( check_touch_coin() )
		{
			wk->vpara.result = gf_mtRand() & 1;
			Poketch_A17_SetViewCommand( wk->vwk, CMD_TOSS );
			wk->seq++;
		}
		break;

	case 1:
		if( Poketch_A17_WaitViewCommand( wk->vwk, CMD_TOSS ) )
		{
			wk->seq = 0;
		}
		break;
	}


	return FALSE;
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
		Poketch_A17_SetViewCommand( wk->vwk, CMD_QUIT );
		wk->seq++;
		break;

	case 1:
		if(Poketch_A17_WaitViewCommandAll( wk->vwk ))
		{
			return TRUE;
		}
		break;
	}

	return FALSE;
}


static BOOL check_touch_coin( void )
{
	u32 x, y;

	if( PoketchGetTPTrg(&x, &y) )
	{
		x = (COIN_DEFAULT_X - x) * (COIN_DEFAULT_X - x);
		y = (COIN_DEFAULT_Y - y) * (COIN_DEFAULT_Y - y);

		if( (x+y) < (24*24) )	// とりあえず半径24dotとして判定
		{
			return TRUE;
		}
	}

	return FALSE;

}
