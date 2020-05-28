//============================================================================================
/**
 * @file	poketch_a06c.c
 * @bfief	ポケッチ（アプリNoa06：簡易ポケモンリスト）　コントロール
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#include <nitro/sinit.h>
#include "common.h"
#include "gflib\touchpanel.h"
#include "system\lib_pack.h"
#include "system\savedata.h"
#include "poketool\pokeicon.h"
#include "poketool\pokeparty.h"

#include "poketch_a06.h"
#include "poketch_prv.h"

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
static BOOL Poketch_A06_Init(void **wk_ptr, CONTACT_WORK* conwk, GF_BGL_INI* bgl, u32 param);
static BOOL SetupWork( APPWORK *wk, CONTACT_WORK* conwk, GF_BGL_INI* bgl, u32 param );
static void CleanupWork( APPWORK *wk );
static void Poketch_A06_Main(TCB_PTR tcb, void *wk_adrs);
static void Poketch_A06_Quit(void *wk_adrs);
static void ChangeSeq(APPWORK *wk, u32 seq);
static BOOL SeqInit(APPWORK *wk);
static BOOL SeqIdle(APPWORK *wk);
static BOOL SeqQuit(APPWORK *wk);
static void update_vpara_pokeparams( VIEWPARAM* vpara, POKEPARTY* party );



//------------------------------------------------------------------
/**
 * アプリの制御関数アドレスをメインコントロールに渡す
 */
//------------------------------------------------------------------
static void NitroStaticInit(void)
{
	PoketchSetAppProc(Poketch_A06_Init, Poketch_A06_Quit);
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
static BOOL Poketch_A06_Init(void **wk_ptr, CONTACT_WORK* conwk, GF_BGL_INI* bgl, u32 param)
{
	APPWORK* wk = (APPWORK*)sys_AllocMemory( POKETCH_APP_CTRL_HEAPID, sizeof(APPWORK));

	if(wk != NULL)
	{
		if(SetupWork( wk, conwk, bgl, param ))
		{
			if( TCB_Add(Poketch_A06_Main, wk, POKETCH_APP_TASKPRI) != NULL )
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
	if( Poketch_A06_SetViewWork( &(wk->vwk), &(wk->vpara), bgl ) )
	{
		wk->main_seq = SEQ_INIT;
		wk->seq = 0;
		wk->quit_req_flag = FALSE;

		update_vpara_pokeparams( &wk->vpara, SaveData_GetTemotiPokemon(PoketchGetSystemSaveData(conwk)) );

		wk->vpara.tp_cont = FALSE;
		wk->vpara.tp_trg = FALSE;
		wk->vpara.tp_x = 0;
		wk->vpara.tp_y = 0;

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
	Poketch_A06_DeleteViewWork( wk->vwk );
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
static void Poketch_A06_Main(TCB_PTR tcb, void *wk_adrs)
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
static void Poketch_A06_Quit(void *wk_adrs)
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
		Poketch_A06_SetViewCommand( wk->vwk, CMD_INIT );
		wk->seq++;
		break;

	case 1:
		if(Poketch_A06_WaitViewCommand( wk->vwk, CMD_INIT ))
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

	if( Poketch_A06_WaitViewCommand( wk->vwk, CMD_UPDATE ) )
	{
		wk->vpara.tp_cont = PoketchGetTPCont( &(wk->vpara.tp_x), &(wk->vpara.tp_y));
		if( wk->vpara.tp_cont )
		{
			wk->vpara.tp_trg = GF_TP_GetTrg();
			if( wk->vpara.tp_trg )
			{
				u32 iconNum = Poketch_A06_CheckTouchIconNum( wk->vpara.tp_x, wk->vpara.tp_y, wk->vpara.poke_count );
				if( iconNum >= wk->vpara.poke_count )
				{
					update_vpara_pokeparams( &wk->vpara,
							SaveData_GetTemotiPokemon( PoketchGetSystemSaveData(wk->conwk) ) );

					Poketch_A06_SetViewCommand( wk->vwk, CMD_UPDATE );
				}
			}
			return FALSE;
		}
	}

	wk->vpara.tp_x = 0;
	wk->vpara.tp_y = 0;
	wk->vpara.tp_trg = FALSE;

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
		Poketch_A06_SetViewCommand( wk->vwk, CMD_QUIT );
		wk->seq++;
		break;

	case 1:
		if(Poketch_A06_WaitViewCommandAll( wk->vwk ))
		{
			return TRUE;
		}
		break;
	}

	return FALSE;
}








//------------------------------------------------------------------
/**
 * ポケモンパラメータ更新
 *
 * @param   vpara		
 *
 */
//------------------------------------------------------------------
static void update_vpara_pokeparams( VIEWPARAM* vpara, POKEPARTY* party )
{
	POKEMON_PARAM* pp;
	int i;
	BOOL fastFlag;

	vpara->poke_count = PokeParty_GetPokeCount(party);
	for(i=0; i<vpara->poke_count; i++)
	{
		pp = PokeParty_GetMemberPointer(party, i);

		fastFlag = PokeParaFastModeOn( pp );

		vpara->poke_param[i].imgArcIdx = PokeIconCgxArcIndexGet((const POKEMON_PASO_PARAM*)pp);
		vpara->poke_param[i].monsno = PokeParaGet(pp, ID_PARA_monsno, NULL);
		vpara->poke_param[i].hp = PokeParaGet(pp, ID_PARA_hp, NULL);
		vpara->poke_param[i].hp_max = PokeParaGet(pp, ID_PARA_hpmax, NULL);
		vpara->poke_param[i].item = PokeParaGet(pp, ID_PARA_item, NULL);
		vpara->poke_param[i].sick_flag = ( PokeParaGet(pp, ID_PARA_condition, NULL) != 0 );
		vpara->poke_param[i].egg_flag = PokeParaGet(pp, ID_PARA_tamago_flag, NULL);
		vpara->poke_param[i].form = PokeParaGet(pp, ID_PARA_form_no, NULL);

		PokeParaFastModeOff( pp, fastFlag );
	}
}

