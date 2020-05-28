//============================================================================================
/**
 * @file	poketch_a19c.c
 * @bfief	ポケッチ（アプリNo19：ラブテスター）　コントロール
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#include <nitro/sinit.h>
#include "common.h"
#include "system\lib_pack.h"
#include "poketool\pokeicon.h"

#include "..\sodateya.h"

#include "poketch_prv.h"
#include "poketch_a19.h"
#include "poketch_button.h"
#include "poketch_sound.h"

//==============================================================
// consts
//==============================================================
enum {
	BUTTON_CHECK,
	BUTTON_POKE_L,
	BUTTON_POKE_R,
};

enum {
	POKE_L_TOP = 130,
	POKE_L_BOTTOM = 164,
	POKE_L_LEFT = 24,
	POKE_L_RIGHT = 72,
	POKE_R_TOP = 130,
	POKE_R_BOTTOM = 164,
	POKE_R_LEFT = 152,
	POKE_R_RIGHT = 200,
};

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

	POKETCH_BUTTON_MAN*  button;
	u16                  button_id;
	u16                  button_event;

	POKEMON_PASO_PARAM*   ppp[TEMOTI_POKEMAX];
	POKEMON_PASO_PARAM*   calc_ppp[2];


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
static BOOL Poketch_A19_Init(void **wk_ptr, CONTACT_WORK* conwk, GF_BGL_INI* bgl, u32 param);
static BOOL SetupWork( APPWORK *wk, CONTACT_WORK* conwk, GF_BGL_INI* bgl, u32 param );
static void CleanupWork( APPWORK *wk );
static void ButtonCallBack( u32 idx, u32 event, u32 touch_event, void* wk_adrs );
static void Poketch_A19_Main(TCB_PTR tcb, void *wk_adrs);
static void Poketch_A19_Quit(void *wk_adrs);
static void ChangeSeq(APPWORK *wk, u32 seq);
static BOOL SeqInit(APPWORK *wk);
static BOOL SeqIdle(APPWORK *wk);
static BOOL change_poke_L( APPWORK* wk );
static BOOL change_poke_R( APPWORK* wk );
static BOOL SeqQuit(APPWORK *wk);



//------------------------------------------------------------------
/**
 * アプリの制御関数アドレスをメインコントロールに渡す
 */
//------------------------------------------------------------------
static void NitroStaticInit(void)
{
	PoketchSetAppProc(Poketch_A19_Init, Poketch_A19_Quit);
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
static BOOL Poketch_A19_Init(void **wk_ptr, CONTACT_WORK* conwk, GF_BGL_INI* bgl, u32 param)
{
	APPWORK* wk = (APPWORK*)sys_AllocMemory( POKETCH_APP_CTRL_HEAPID, sizeof(APPWORK));

	if(wk != NULL)
	{
		if(SetupWork( wk, conwk, bgl, param ))
		{
			if( TCB_Add(Poketch_A19_Main, wk, POKETCH_APP_TASKPRI) != NULL )
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
	POKEPARTY* party = SaveData_GetTemotiPokemon( PoketchGetSystemSaveData(conwk) );
	POKEMON_PARAM* pp;
	int i;

	wk->vpara.poke_count = PokeParty_GetPokeCount(party);
	for(i=0; i<wk->vpara.poke_count; i++)
	{
		pp = PokeParty_GetMemberPointer(party, i);
		wk->vpara.pokeImgArcIndex[i] = PokeIconCgxArcIndexGet((const POKEMON_PASO_PARAM*)pp);
		wk->vpara.pokeMonsNo[i] = PokeParaGet(pp, ID_PARA_monsno, NULL);
		wk->vpara.pokeForm[i] = PokeParaGet(pp, ID_PARA_form_no, NULL);
		wk->ppp[i] = (POKEMON_PASO_PARAM*)pp;
	}

	wk->vpara.poke_id_L = 0;
	wk->vpara.poke_id_R = (wk->vpara.poke_count>1)? 1 : 0;

	if( Poketch_A19_SetViewWork( &(wk->vwk), &(wk->vpara), bgl ) )
	{
		static const TP_HIT_TBL hit_tbl[] = {
			{
				LOVE_BUTTON_TOP,  LOVE_BUTTON_BOTTOM,
				LOVE_BUTTON_LEFT, LOVE_BUTTON_RIGHT,
			},{
				POKE_L_TOP, POKE_L_BOTTOM,
				POKE_L_LEFT, POKE_L_RIGHT,
			},{
				POKE_R_TOP, POKE_R_BOTTOM,
				POKE_R_LEFT, POKE_R_RIGHT,
			},
		};


		wk->main_seq = SEQ_INIT;
		wk->seq = 0;
		wk->quit_req_flag = FALSE;

		wk->button =  PBTN_Create( hit_tbl, NELEMS(hit_tbl), ButtonCallBack, wk, POKETCH_APP_CTRL_HEAPID );
		wk->button_event = BMN_EVENT_NULL;

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
	PBTN_Delete(wk->button);
	Poketch_A19_DeleteViewWork( wk->vwk );
	sys_FreeMemoryEz( wk );
}

//------------------------------------------------------------------
/**
 * ボタン管理マネージャからのコールバック関数
 *
 * @param   idx		
 * @param   event		
 * @param   touch_event		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void ButtonCallBack( u32 idx, u32 event, u32 touch_event, void* wk_adrs )
{
	APPWORK *wk = (APPWORK*)wk_adrs;

	wk->button_id = idx;
	wk->button_event = event;
}


//------------------------------------------------------------------
/**
 * アプリメイン関数
 *
 * @param   wk_adrs		ワークアドレス
 *
 */
//------------------------------------------------------------------
static void Poketch_A19_Main(TCB_PTR tcb, void *wk_adrs)
{
	static BOOL (* const seqtbl[])(APPWORK*) = {
		SeqInit,
		SeqIdle,
		SeqQuit,
	};

	APPWORK *wk = (APPWORK*)wk_adrs;

	if( wk->main_seq < NELEMS(seqtbl) )
	{
		PoketchButtonMainCall( wk->conwk, wk->button );

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
static void Poketch_A19_Quit(void *wk_adrs)
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
		Poketch_A19_SetViewCommand( wk->vwk, CMD_INIT );
		wk->seq++;
		break;

	case 1:
		if(Poketch_A19_WaitViewCommand( wk->vwk, CMD_INIT ))
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
 * シーケンス：メイン
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
		if( wk->button_event == BMN_EVENT_TOUCH )
		{
			switch( wk->button_id ){
			case BUTTON_POKE_L:
				if( change_poke_L( wk ) )
				{
					Poketch_A19_SetViewCommand( wk->vwk, CMD_CHANGE_POKE_L );
					wk->seq = 1;
				}
				break;

			case BUTTON_POKE_R:
				if( change_poke_R( wk ) )
				{
					Poketch_A19_SetViewCommand( wk->vwk, CMD_CHANGE_POKE_R );
					wk->seq = 1;
				}
				break;

			case BUTTON_CHECK:
				if( wk->vpara.poke_count > 1 )
				{
					Poketch_A19_SetViewCommand( wk->vwk, CMD_BUTTON_PUSH );
					wk->seq = 2;
				}
				else
				{
					PoketchSePlay( POKETCH_SE_LOVE_BUTTON_DISABLE );
				}
				break;
			}
			wk->button_event = BMN_EVENT_NULL;
		}
		break;

	case 1:
		if( Poketch_A19_WaitViewCommandAll( wk->vwk ) )
		{
			wk->seq = 0;
		}
		break;

	case 2:
		if( wk->button_event == BMN_EVENT_OUT )
		{
			Poketch_A19_SetViewCommand( wk->vwk, CMD_BUTTON_FREE );
			wk->seq = 0;
			break;
		}
		if( wk->button_event == BMN_EVENT_TAP )
		{
			#if 0
			static int lv = 0;
			wk->vpara.affinity_lv = lv;
			if(++lv > 3){ lv = 0;}
			#else
			wk->calc_ppp[0] = wk->ppp[wk->vpara.poke_id_L];
			wk->calc_ppp[1] = wk->ppp[wk->vpara.poke_id_R];
			wk->vpara.affinity_lv = Sodateya_GetAffinityLevel( wk->calc_ppp );
			#endif;
			Poketch_A19_SetViewCommand( wk->vwk, CMD_BUTTON_FREE );
			Poketch_A19_SetViewCommand( wk->vwk, CMD_ANM_PLAY );
			wk->seq++;
		}
		break;

	case 3:
		if( Poketch_A19_WaitViewCommand( wk->vwk, CMD_ANM_PLAY ) )
		{
			wk->seq = 0;
		}
	}

	return FALSE;
}

static BOOL change_poke_L( APPWORK* wk )
{
	if( wk->vpara.poke_count > 2 )
	{
		do{
			if(++(wk->vpara.poke_id_L) >= wk->vpara.poke_count )
			{
				wk->vpara.poke_id_L = 0;
			}
		}while( wk->vpara.poke_id_L == wk->vpara.poke_id_R );

		return TRUE;
	}
	return FALSE;
}
static BOOL change_poke_R( APPWORK* wk )
{
	if( wk->vpara.poke_count > 2 )
	{
		do{
			if(++(wk->vpara.poke_id_R) >= wk->vpara.poke_count )
			{
				wk->vpara.poke_id_R = 0;
			}
		}while( wk->vpara.poke_id_R == wk->vpara.poke_id_L );

		return TRUE;
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
		Poketch_A19_SetViewCommand( wk->vwk, CMD_QUIT );
		wk->seq++;
		break;

	case 1:
		if(Poketch_A19_WaitViewCommandAll( wk->vwk ))
		{
			return TRUE;
		}
		break;
	}

	return FALSE;
}
