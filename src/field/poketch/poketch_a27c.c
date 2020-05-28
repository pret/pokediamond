//============================================================================================
/**
 * @file	poketch_a27c.c
 * @bfief	ポケッチ（アプリNoa27：つうしんサーチャー）　コントロール
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#include <nitro/sinit.h>
#include "common.h"
#include "gflib\touchpanel.h"
#include "system\lib_pack.h"
#include "communication\communication.h"
#include "communication\comm_state.h"
#include "savedata\mystatus.h"


#include "..\fieldsys.h"
#include "..\zonedata.h"
#include "field\location.h"

#include "poketch_a27.h"
#include "poketch_prv.h"
#include "poketch_sound.h"

//==============================================================
// Work
//==============================================================
typedef struct {
	u8        main_seq;
	u8        seq;
	u8        quit_req_flag;

	VIEWPARAM  vpara;
	VIEWWORK*  vwk;
	CONTACT_WORK*  conwk;

	u32        timer;

	u8         comm_seq;
	u8         comm_end_req;

}APPWORK;

//==============================================================
// シーケンス
//==============================================================
enum {
	SEQ_INIT,
	SEQ_TOP,
	SEQ_CONNECT,
	SEQ_ERR_CANT_CONNECT,
	SEQ_ERR_DONT_MOVE,
	SEQ_QUIT,
};

enum {
	COMM_SEQ_FREE,
	COMM_SEQ_INIT_WAIT,
	COMM_SEQ_CONNECTING,
	COMM_SEQ_QUIT_WAIT,
};

//==============================================================
// Prototype
//==============================================================
static void NitroStaticInit(void);
static BOOL Poketch_A27_Init(void **wk_ptr, CONTACT_WORK* conwk, GF_BGL_INI* bgl, u32 param);
static BOOL SetupWork( APPWORK *wk, CONTACT_WORK* conwk, GF_BGL_INI* bgl, u32 param );
static void CleanupWork( APPWORK *wk );
static void Poketch_A27_Main(TCB_PTR tcb, void *wk_adrs);
static void Poketch_A27_Quit(void *wk_adrs);
static void ChangeSeq(APPWORK *wk, u32 seq);
static BOOL SeqInit(APPWORK *wk);
static BOOL SeqTop(APPWORK *wk);
static BOOL SeqConnect( APPWORK* wk );
static BOOL check_player_move( APPWORK* wk );
static BOOL SeqErrCantConnect( APPWORK* wk );
static BOOL SeqErrDontMove( APPWORK* wk );
static BOOL SeqQuit(APPWORK *wk);
static BOOL touch_screen( APPWORK* wk );
static void init_connect_players_count( APPWORK* wk );
static BOOL countup_connect_players( APPWORK* wk );
static void comm_main( APPWORK* wk );
static void comm_start( APPWORK* wk );
static BOOL wait_comm_start( APPWORK* wk );
static void comm_end( APPWORK* wk );
static BOOL comm_end_wait( APPWORK* wk );



//------------------------------------------------------------------
/**
 * アプリの制御関数アドレスをメインコントロールに渡す
 */
//------------------------------------------------------------------
static void NitroStaticInit(void)
{
	PoketchSetAppProc(Poketch_A27_Init, Poketch_A27_Quit);
}

//------------------------------------------------------------------
/**
 * アプリ初期化関数
 *
 * @param   wk_ptr		ワークアドレスを保存するポインタのアドレス
 * @param   conwk		アプリが本体から情報を取得する際に必要となるワーク（アプリへは非公開）
 * @param   bgl			BGLモジュールヘッダ
 * @param   param		カラー・モノクロなど動作タイプ（アプリ依存）
 */
//------------------------------------------------------------------
static BOOL Poketch_A27_Init(void **wk_ptr, CONTACT_WORK* conwk, GF_BGL_INI* bgl, u32 param)
{
	APPWORK* wk = (APPWORK*)sys_AllocMemory( POKETCH_APP_CTRL_HEAPID, sizeof(APPWORK));

	if(wk != NULL)
	{
		if(SetupWork( wk, conwk, bgl, param ))
		{
			if( TCB_Add(Poketch_A27_Main, wk, POKETCH_APP_TASKPRI) != NULL )
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
static BOOL SetupWork( APPWORK *wk, CONTACT_WORK* conwk, GF_BGL_INI* bgl, u32 param )
{
	if( Poketch_A27_SetViewWork( &(wk->vwk), &(wk->vpara), bgl ) )
	{
		wk->main_seq = SEQ_INIT;
		wk->seq = 0;
		wk->quit_req_flag = FALSE;
		wk->comm_seq = COMM_SEQ_FREE;
		wk->comm_end_req = FALSE;

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
	Poketch_A27_DeleteViewWork( wk->vwk );
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
static void Poketch_A27_Main(TCB_PTR tcb, void *wk_adrs)
{
	static BOOL (* const seqtbl[])(APPWORK*) = {
		SeqInit,
		SeqTop,
		SeqConnect,
		SeqErrCantConnect,
		SeqErrDontMove,
		SeqQuit,
	};

	APPWORK *wk = (APPWORK*)wk_adrs;

	if( wk->main_seq < NELEMS(seqtbl) )
	{
		comm_main(wk);

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
static void Poketch_A27_Quit(void *wk_adrs)
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
		Poketch_A27_SetViewCommand( wk->vwk, CMD_INIT );
		wk->seq++;
		break;

	case 1:
		if(Poketch_A27_WaitViewCommand( wk->vwk, CMD_INIT ))
		{
			PoketchNoticeAppStart( wk->conwk );
			ChangeSeq( wk, SEQ_TOP );
		}
		break;
	}
	return FALSE;
}
//------------------------------------------------------------------
/**
 * シーケンス：トップ画面
 *
 * @param   wk		ワークポインタ
 *
 * @retval  BOOL		TRUEでアプリ終了
 */
//------------------------------------------------------------------
static BOOL SeqTop(APPWORK *wk)
{
	if(wk->quit_req_flag)
	{
		ChangeSeq( wk, SEQ_QUIT );
		return FALSE;
	}

	switch( wk->seq ){
	case 0:
		if( touch_screen( wk ) )
		{
			if( comm_end_wait(wk) )
			{
				FIELDSYS_WORK* fsys = PoketchGetFieldSysWork( wk->conwk );

				Poketch_A27_SetViewCommand(wk->vwk, CMD_IMG_SEARCHING);
				if( ZoneData_IsCommPlayableZone( fsys->location->zone_id ) )
				{
					ChangeSeq( wk, SEQ_ERR_CANT_CONNECT );
				}
				else
				{
					ChangeSeq( wk, SEQ_CONNECT );
				}
			}
			else
			{
				PoketchSePlay( POKETCH_SE_TUSHIN_WARNING );
			}
		}
		break;
	}

	return FALSE;
}
//------------------------------------------------------------------
/**
 * シーケンス：接続画面へ
 *
 * @param   wk		ワークポインタ
 *
 * @retval  BOOL		TRUEでアプリ終了
 */
//------------------------------------------------------------------
static BOOL SeqConnect( APPWORK* wk )
{
	enum {
		UPDATE_INTERVAL = 30,
		IMG_DISP_FRAMES = 60,		///< 「サーチ中です…」画面を表示しておく時間
	};

	if(wk->quit_req_flag)
	{
		ChangeSeq( wk, SEQ_QUIT );
		return FALSE;
	}



	switch( wk->seq ){
	case 0:
		comm_start(wk);
		wk->timer = 0;
		wk->seq++;
		break;

	case 1:
		if( check_player_move(wk) )
		{
			ChangeSeq( wk, SEQ_ERR_DONT_MOVE );
			return FALSE;
		}
		if( wk->timer < IMG_DISP_FRAMES )
		{
			wk->timer++;
		}
		if( wait_comm_start(wk) && wk->timer >= IMG_DISP_FRAMES )
		{
			countup_connect_players( wk );
			Poketch_A27_SetViewCommand(wk->vwk, CMD_IMG_STATUS);
			wk->timer = 0;
			wk->seq++;
		}
		break;

	case 2:
		if( check_player_move(wk) || touch_screen(wk) )
		{
			comm_end( wk );
			Poketch_A27_SetViewCommand(wk->vwk, CMD_IMG_TOP);
			ChangeSeq( wk, SEQ_TOP );
			return FALSE;
		}
		if( ++(wk->timer) >= UPDATE_INTERVAL )
		{
			wk->timer = 0;
			if( countup_connect_players( wk ) )
			{
				Poketch_A27_SetViewCommand(wk->vwk, CMD_IMG_STATUS);
			}
		}
		break;
	}


	return FALSE;


}
//------------------------------------------------------------------
/**
 * プレイヤーが移動しようとしたﾁｪｯｸ
 *
 * @param   wk		
 *
 * @retval  BOOL		
 */
//------------------------------------------------------------------
static BOOL check_player_move( APPWORK* wk )
{
	if( PoketchIsSleepMode(wk->conwk) ){ return TRUE; }
	if( PoketchGetPlayerMoveTrg(wk->conwk) ){ return TRUE; }

	return FALSE;
}



//------------------------------------------------------------------
/**
 * シーケンス：エラー画面（サーチできないエリア）
 *
 * @param   wk		ワークポインタ
 *
 * @retval  BOOL		TRUEでアプリ終了
 */
//------------------------------------------------------------------
static BOOL SeqErrCantConnect( APPWORK* wk )
{
	enum {
		IMG_DISP_FRAMES = 60,		///< 「サーチ中です…」画面を表示しておく時間
	};

	if(wk->quit_req_flag)
	{
		ChangeSeq( wk, SEQ_QUIT );
		return FALSE;
	}

	switch( wk->seq ){
	case 0:
		wk->timer = 0;
		wk->seq++;
		/* fallthru */
	case 1:
		if(++(wk->timer) >= IMG_DISP_FRAMES)
		{
			Poketch_A27_SetViewCommand(wk->vwk, CMD_IMG_ERROR_CANT_CONNECT);
			wk->seq++;
		}
		break;
	case 2:
		if( touch_screen( wk ) )
		{
			Poketch_A27_SetViewCommand(wk->vwk, CMD_IMG_TOP);
			ChangeSeq( wk, SEQ_TOP );
		}
		break;
	}
	return FALSE;
}
//------------------------------------------------------------------
/**
 * シーケンス：エラー画面（サーチ中にプレイヤーが動いた）
 *
 * @param   wk		ワークポインタ
 *
 * @retval  BOOL		TRUEでアプリ終了
 */
//------------------------------------------------------------------
static BOOL SeqErrDontMove( APPWORK* wk )
{
	if(wk->quit_req_flag)
	{
		ChangeSeq( wk, SEQ_QUIT );
		return FALSE;
	}

	switch( wk->seq ){
	case 0:
		comm_end( wk );
		Poketch_A27_SetViewCommand(wk->vwk, CMD_IMG_ERROR_DONT_MOVE);
		wk->seq++;
		break;

	case 1:
		if( touch_screen( wk ) )
		{
			Poketch_A27_SetViewCommand(wk->vwk, CMD_IMG_TOP);
			ChangeSeq( wk, SEQ_TOP );
		}
		break;
	}
	return FALSE;


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
		comm_end(wk);
		wk->seq++;
		/* fallthru */
	case 1:
		if( comm_end_wait(wk) )
		{
			Poketch_A27_SetViewCommand( wk->vwk, CMD_QUIT );
			wk->seq++;
		}
		break;
	case 2:
		if(Poketch_A27_WaitViewCommandAll( wk->vwk ))
		{
			return TRUE;
		}
		break;
	}

	return FALSE;
}






//------------------------------------------------------------------
/**
 * モニターにタッチされたかチェック
 *
 * @param   wk		
 *
 * @retval  BOOL		
 */
//------------------------------------------------------------------
static BOOL touch_screen( APPWORK* wk )
{
	if( PoketchIsSleepMode(wk->conwk) == FALSE)
	{
		u32 x, y;
		if( GF_TP_GetPointTrg(&x,&y) )
		{
			if( ((u32)( x - POKETCH_MONITOR_DOT_XORG) < (u32)(POKETCH_MONITOR_DOT_XEND - POKETCH_MONITOR_DOT_XORG))
			&	((u32)( y - POKETCH_MONITOR_DOT_YORG) < (u32)(POKETCH_MONITOR_DOT_YEND - POKETCH_MONITOR_DOT_YORG))
			){
				return TRUE;
			}
		}
	}

	return FALSE;
}



//======================================================================================
// 接続プレイヤー数カウント関連
//======================================================================================

//------------------------------------------------------------------
/**
 * カウント変数領域の初期化
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
static void init_connect_players_count( APPWORK* wk )
{
	int i;
	for(i=0; i<POKETCH_COMM_CATEGORY_MAX; i++)
	{
		wk->vpara.players_count[i] = -1;
	}
}
//------------------------------------------------------------------
/**
 * 接続プレイヤー数カウント
 *
 * @param   wk		
 *
 * @retval  BOOL	TRUEで前回のカウントから更新された
 */
//------------------------------------------------------------------
static BOOL countup_connect_players( APPWORK* wk )
{
	static const u8 union_mode[] = {
		COMM_MODE_UNION,
		COMM_MODE_PICTURE,
		COMM_MODE_RECORD,
		COMM_MODE_UNION_APP,
	};
	static const u8 ug_mode[] = {
		COMM_MODE_UNDERGROUND,
	};
	static const u8 colosseum_mode[] = {
		COMM_MODE_BATTLE_SINGLE,
		COMM_MODE_BATTLE_DOUBLE,
		COMM_MODE_BATTLE_MIX_1ON1,
		COMM_MODE_BATTLE_MULTI,
		COMM_MODE_BATTLE_MIX_2ON2,
	};
	static const u8 other_mode[] = {
		COMM_MODE_TRADE,
		COMM_MODE_NUT_CRASH,
		COMM_MODE_CONTEST,
		COMM_MODE_POLLOCK4,
		COMM_MODE_POLLOCK16,
		COMM_MODE_POKETCH,
	};

	// このテーブルの要素数はPOKETCH_COMM_CATEGORY_MAXと一致しなければならない
	static const struct {
		const u8* table;
		u32       table_size;
	}check_tbl[] = {
		{ union_mode,		NELEMS(union_mode)		},
		{ ug_mode,			NELEMS(ug_mode)			},
		{ colosseum_mode,	NELEMS(colosseum_mode)	},
		{ other_mode,		NELEMS(other_mode)		},
	};


	int i, m, count;
	BOOL update = FALSE;

	for(i=0; i<NELEMS(check_tbl); i++)
	{
		for(m=0, count=0;  m<check_tbl[i].table_size;  m++)
		{
			count += CommMPGetServiceNumber(check_tbl[i].table[m]);
		}
		if( count != wk->vpara.players_count[i] )
		{
			wk->vpara.players_count[i] = count;
			update = TRUE;
		}
	}

	return update;
}



//======================================================================================
// 通信処理関連
//======================================================================================


//------------------------------------------------------------------
/**
 * 通信処理メイン（アプリメインループから毎回呼ぶ）
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
static void comm_main( APPWORK* wk )
{
	switch( wk->comm_seq ){
	case COMM_SEQ_FREE:
		break;

	case COMM_SEQ_INIT_WAIT:
		if( CommIsPoketchSearchingState() )
		{
			wk->comm_seq = COMM_SEQ_CONNECTING;
		}
		break;

	case COMM_SEQ_CONNECTING:
		if( wk->comm_end_req )
		{
			CommStateExitPoketch();
			wk->comm_end_req = FALSE;
			wk->comm_seq = COMM_SEQ_QUIT_WAIT;
		}
		break;

	case COMM_SEQ_QUIT_WAIT:
		if( CommIsInitialize() == FALSE )
		{
			wk->comm_seq = COMM_SEQ_FREE;
		}
		break;
	}
}


//------------------------------------------------------------------
/**
 * 通信開始リクエスト
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
static void comm_start( APPWORK* wk )
{
	if( wk->comm_seq == COMM_SEQ_FREE )
	{
		CommStateEnterPockchChild( PoketchGetSystemSaveData(wk->conwk) );
		wk->comm_seq = COMM_SEQ_INIT_WAIT;
	}
}
//------------------------------------------------------------------
/**
 * 通信開始待ち
 *
 * @param   wk		
 *
 * @retval  BOOL	TRUEで開始された
 */
//------------------------------------------------------------------
static BOOL wait_comm_start( APPWORK* wk )
{
	return wk->comm_seq == COMM_SEQ_CONNECTING;
}
//------------------------------------------------------------------
/**
 * 通信終了リクエスト
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
static void comm_end( APPWORK* wk )
{
	wk->comm_end_req = TRUE;
}
//------------------------------------------------------------------
/**
 * 通信終了待ち
 *
 * @param   wk		
 *
 * @retval  BOOL	TRUEで終了した
 */
//------------------------------------------------------------------
static BOOL comm_end_wait( APPWORK* wk )
{
	return wk->comm_seq == COMM_SEQ_FREE;
}
