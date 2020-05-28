//============================================================================================
/**
 * @file	poketch_a15c.c
 * @bfief	ポケッチ（アプリNoa15：そだてやカメラ）　コントロール
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#include <nitro/sinit.h>
#include "common.h"
#include "gflib\touchpanel.h"
#include "system\lib_pack.h"
#include "poketool\poke_tool.h"
#include "poketool\pokeicon.h"
#include "savedata\sodateyadata.h"
#include "..\sodateya.h"

#include "poketch_a15.h"
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

	SODATEYA_WORK*    sodateya_data;
	

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
static BOOL Poketch_A15_Init(void **wk_ptr, CONTACT_WORK* conwk, GF_BGL_INI* bgl, u32 param);
static BOOL SetupWork( APPWORK *wk, CONTACT_WORK* conwk, GF_BGL_INI* bgl, u32 param );
static void CleanupWork( APPWORK *wk );
static void Poketch_A15_Main(TCB_PTR tcb, void *wk_adrs);
static void Poketch_A15_Quit(void *wk_adrs);
static void ChangeSeq(APPWORK *wk, u32 seq);
static BOOL SeqInit(APPWORK *wk);
static BOOL SeqIdle(APPWORK *wk);
static BOOL SeqQuit(APPWORK *wk);
static BOOL check_monitor_touch( APPWORK* wk );
static void update_sodateya_datas( VIEWPARAM* vpara, SODATEYA_WORK* sodateya_work );



//------------------------------------------------------------------
/**
 * アプリの制御関数アドレスをメインコントロールに渡す
 */
//------------------------------------------------------------------
static void NitroStaticInit(void)
{
	PoketchSetAppProc(Poketch_A15_Init, Poketch_A15_Quit);
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
static BOOL Poketch_A15_Init(void **wk_ptr, CONTACT_WORK* conwk, GF_BGL_INI* bgl, u32 param)
{
	APPWORK* wk = (APPWORK*)sys_AllocMemory( POKETCH_APP_CTRL_HEAPID, sizeof(APPWORK));

	if(wk != NULL)
	{
		// 強制的にそだてやに手持ちポケモンを預ける処理（デバッグ用）
		#ifdef PM_DEBUG
		#if 0
		{
			SAVEDATA* sv = PoketchGetSystemSaveData(conwk);
			SODATEYA_WORK* sodateya = SaveData_GetSodateyaWork(sv);
			if( PokeAzukeruCheck(sodateya) == 0 )
			{
				PokeSodateSet( SaveData_GetTemotiPokemon(sv), 0, sodateya, sv );
				PokeSodateSet( SaveData_GetTemotiPokemon(sv), 0, SaveData_GetSodateyaWork(sv), sv );
				SodateyaWork_SetEggFlag( SaveData_GetSodateyaWork(sv), TRUE );
			}
		}
		#endif
		#endif

		if(SetupWork( wk, conwk, bgl, param ))
		{
			if( TCB_Add(Poketch_A15_Main, wk, POKETCH_APP_TASKPRI) != NULL )
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
	wk->sodateya_data = SaveData_GetSodateyaWork( PoketchGetSystemSaveData(conwk) );

	update_sodateya_datas( &wk->vpara, wk->sodateya_data );

	if( Poketch_A15_SetViewWork( &(wk->vwk), &(wk->vpara), bgl ) )
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
	Poketch_A15_DeleteViewWork( wk->vwk );
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
static void Poketch_A15_Main(TCB_PTR tcb, void *wk_adrs)
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
static void Poketch_A15_Quit(void *wk_adrs)
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
		Poketch_A15_SetViewCommand( wk->vwk, CMD_INIT );
		wk->seq++;
		break;

	case 1:
		if(Poketch_A15_WaitViewCommand( wk->vwk, CMD_INIT ))
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
 * シーケンス：タッチされたら更新
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


	switch( wk->seq ){
	case 0:
		if( check_monitor_touch(wk) )
		{
			update_sodateya_datas( &wk->vpara, wk->sodateya_data );
			Poketch_A15_SetViewCommand( wk->vwk, CMD_UPDATE );
			wk->seq++;
		}
		break;

	case 1:
		if( Poketch_A15_WaitViewCommand( wk->vwk, CMD_UPDATE ) )
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
		Poketch_A15_SetViewCommand( wk->vwk, CMD_QUIT );
		wk->seq++;
		break;

	case 1:
		if(Poketch_A15_WaitViewCommandAll( wk->vwk ))
		{
			return TRUE;
		}
		break;
	}

	return FALSE;
}


//------------------------------------------------------------------
/**
 * モニター範囲にタッチされたかチェック
 *
 * @param   wk		
 *
 * @retval  BOOL		
 */
//------------------------------------------------------------------
static BOOL check_monitor_touch( APPWORK* wk )
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






//------------------------------------------------------------------
/**
 * そだてやポケモンデータを読み取り、情報更新
 *
 * @param   vpara		
 * @param   sodateya_work		
 *
 */
//------------------------------------------------------------------
static void update_sodateya_datas( VIEWPARAM* vpara, SODATEYA_WORK* sodateya_work )
{
	SODATEYA_POKE*  sodateya_poke;
	POKEMON_PASO_PARAM* ppp;
	int i;
	BOOL fastMode;

	vpara->poke_count = PokeAzukeruCheck( sodateya_work );
	vpara->tamago_flag = SodateyaWork_GetEggFlag( sodateya_work );

	for(i=0; i<vpara->poke_count; i++)
	{
		sodateya_poke = SodateyaWork_GetSodateyaPokePointer( sodateya_work, i );
		ppp = SodateyaPoke_GetPokePasoPointer(sodateya_poke);
		fastMode = PokePasoParaFastModeOn( ppp );
		vpara->poke_img_arc_idx[i] = PokeIconCgxArcIndexGet( ppp );
		vpara->poke_monsno[i] = PokePasoParaGet( ppp, ID_PARA_monsno, NULL );
		vpara->poke_form[i] = PokePasoParaGet( ppp, ID_PARA_form_no, NULL );
		vpara->poke_level[i] = GetSodatePokeLevelDirect( sodateya_poke );
		vpara->poke_sex[i] = PokePasoSexGet( ppp );
		PokePasoParaFastModeOff( ppp, fastMode );
	}
}
