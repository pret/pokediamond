//============================================================================================
/**
 * @file	poketch_a23c.c
 * @bfief	ポケッチ（アプリNoa23：きのみマップ）　コントロール
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#include <nitro/sinit.h>
#include "common.h"
#include "system\lib_pack.h"
#include "savedata\seedbed.h"
#include "field\eventflag.h"
#include "..\syswork.h"
#include "..\field_townmap.h"

#include "poketch_a23.h"
#include "poketch_prv.h"

#define __SEED_DATA_INCLUDE__
#include "seed_data.dat"

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
static BOOL Poketch_A23_Init(void **wk_ptr, CONTACT_WORK* conwk, GF_BGL_INI* bgl, u32 param);
static BOOL SetupWork( APPWORK *wk, CONTACT_WORK* conwk, GF_BGL_INI* bgl, u32 param );
static void CleanupWork( APPWORK *wk );
static void Poketch_A23_Main(TCB_PTR tcb, void *wk_adrs);
static void Poketch_A23_Quit(void *wk_adrs);
static void ChangeSeq(APPWORK *wk, u32 seq);
static BOOL SeqInit(APPWORK *wk);
static BOOL SeqIdle(APPWORK *wk);
static BOOL SeqQuit(APPWORK *wk);
static int check_beared_tree_pos( APPWORK* wk );
static BOOL check_update_player_location( APPWORK* wk );
static void update_hidemap_flag( APPWORK* wk, CONTACT_WORK* conwk );



//------------------------------------------------------------------
/**
 * アプリの制御関数アドレスをメインコントロールに渡す
 */
//------------------------------------------------------------------
static void NitroStaticInit(void)
{
	PoketchSetAppProc(Poketch_A23_Init, Poketch_A23_Quit);
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
static BOOL Poketch_A23_Init(void **wk_ptr, CONTACT_WORK* conwk, GF_BGL_INI* bgl, u32 param)
{
	APPWORK* wk = (APPWORK*)sys_AllocMemory( POKETCH_APP_CTRL_HEAPID, sizeof(APPWORK));

	if(wk != NULL)
	{
		if(SetupWork( wk, conwk, bgl, param ))
		{
			if( TCB_Add(Poketch_A23_Main, wk, POKETCH_APP_TASKPRI) != NULL )
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
	wk->conwk = conwk;

	wk->vpara.seed_count = check_beared_tree_pos( wk );

	FLDTOWNMAP_GetBlockXZ( PoketchGetFieldSysWork(wk->conwk),
		 &(wk->vpara.player_x), &(wk->vpara.player_y) );

	update_hidemap_flag( wk, conwk );

	if( Poketch_A23_SetViewWork( &(wk->vwk), &(wk->vpara), bgl ) )
	{
		wk->main_seq = SEQ_INIT;
		wk->seq = 0;
		wk->quit_req_flag = FALSE;
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
	Poketch_A23_DeleteViewWork( wk->vwk );
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
static void Poketch_A23_Main(TCB_PTR tcb, void *wk_adrs)
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
static void Poketch_A23_Quit(void *wk_adrs)
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
		Poketch_A23_SetViewCommand( wk->vwk, CMD_INIT );
		wk->seq++;
		break;

	case 1:
		if(Poketch_A23_WaitViewCommand( wk->vwk, CMD_INIT ))
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
		return FALSE;
	}

	wk->vpara.player_update_flag = check_update_player_location( wk );

	if( Poketch_A23_WaitViewCommand( wk->vwk, CMD_SEED_UPDATE ) )
	{
		u32 x, y;

		if( PoketchGetTPTrg( &x, &y ) )
		{
			// 描画有効範囲である
			if( ((u32)( x - POKETCH_MONITOR_DOT_XORG) < (u32)(POKETCH_MONITOR_DOT_WIDTH))
			&	((u32)( y - POKETCH_MONITOR_DOT_YORG) < (u32)(POKETCH_MONITOR_DOT_WIDTH))
			){
				wk->vpara.seed_count = check_beared_tree_pos( wk );
				Poketch_A23_SetViewCommand( wk->vwk, CMD_SEED_UPDATE );
			}
		}
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
		Poketch_A23_SetViewCommand( wk->vwk, CMD_QUIT );
		wk->seq++;
		break;

	case 1:
		if(Poketch_A23_WaitViewCommandAll( wk->vwk ))
		{
			return TRUE;
		}
		break;
	}

	return FALSE;
}



//------------------------------------------------------------------
/**
 * 木の実がなっている木の位置をvparaにセットする
 *
 * @param   wk		ワークポインタ
 *
 * @retval  int		木の実がなっている木の数
 */
//------------------------------------------------------------------
static int check_beared_tree_pos( APPWORK* wk )
{
	SEEDBED* seedBed = SaveData_GetSeedBed( PoketchGetSystemSaveData(wk->conwk) );
	int i, cnt;

	for(i=0, cnt=0; i<SEED_POS_MAX; i++)
	{
		if( (SEEDBED_GetGrowthFlag(seedBed, i) == TRUE)
		&&	(SEEDBED_GetSeedStatus(seedBed, i) == SEEDSTAT_FRUIT )
		){
			wk->vpara.seed_pos[cnt].x = SeedDataTbl[i].mapX;
			wk->vpara.seed_pos[cnt].y = SeedDataTbl[i].mapY;
			// マップ座標上で同グリッドのものはスキップ
			while(	((i+1)<SEED_POS_MAX)
			&&		(wk->vpara.seed_pos[cnt].x == SeedDataTbl[i+1].mapX)
			&&		(wk->vpara.seed_pos[cnt].y == SeedDataTbl[i+1].mapY)
			){
				i++;
			}

			if( ++cnt >= SEED_GRID_MAX )
			{
				break;
			}
		}
	}
	return cnt;
}


static BOOL check_update_player_location( APPWORK* wk )
{
	BOOL ret = FALSE;
	if(PoketchGetPlayerMoveTrg(wk->conwk))
	{
		// 自機のグリッド（マップ上）が変わったら更新
		int x, y;
		FLDTOWNMAP_GetBlockXZ( PoketchGetFieldSysWork(wk->conwk), &x, &y );
		if( (x != wk->vpara.player_x) || (y != wk->vpara.player_y) )
		{
			wk->vpara.player_x = x;
			wk->vpara.player_y = y;
			ret = TRUE;
		}
	}
	return ret;
}


static void update_hidemap_flag( APPWORK* wk, CONTACT_WORK* conwk )
{
	EVENTWORK* ev = SaveData_GetEventWork( PoketchGetSystemSaveData(conwk) );
	int i;
	for(i=0; i<POKETCH_HIDEMAP_MAX; i++)
	{
		wk->vpara.hidemap_flag[i] = SysWork_HideMapWorkCheck( ev, i );
	}
}
