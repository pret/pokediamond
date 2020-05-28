//============================================================================================
/**
 * @file	poketch_a18c.c
 * @bfief	ポケッチ（アプリNoa18：わざ相性チェッカー）　コントロール
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#include <nitro/sinit.h>
#include "common.h"
#include "system\lib_pack.h"

#include "poketch_button.h"
#include "poketch_a18.h"
#include "poketch_prv.h"

enum {
	TYPE_MAX = AISYOU_TYPE_NULL,
};
	

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

	POKETCH_BUTTON_MAN*   button;
	u32                   button_event;

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
static BOOL Poketch_A18_Init(void **wk_ptr, CONTACT_WORK* conwk, GF_BGL_INI* bgl, u32 param);
static BOOL SetupWork( APPWORK *wk, CONTACT_WORK* conwk, GF_BGL_INI* bgl, u32 param );
static void init_vparam( VIEWPARAM* vpara );
static void CleanupWork( APPWORK *wk );
static void Poketch_A18_Main(TCB_PTR tcb, void *wk_adrs);
static void ButtonCallBack( u32 idx, u32 event, u32 touch_event, void* wk_adrs );
static void Poketch_A18_Quit(void *wk_adrs);
static void ChangeSeq(APPWORK *wk, u32 seq);
static BOOL SeqInit(APPWORK *wk);
static BOOL SeqIdle(APPWORK *wk);
static BOOL SeqQuit(APPWORK *wk);
static u32 calc_effect_lv( u32 attack_type, u32 defence_type0, u32 defence_type1 );
static u32 get_next_type( s32 type, s32 direction, BOOL null_in_flag );



//------------------------------------------------------------------
/**
 * アプリの制御関数アドレスをメインコントロールに渡す
 */
//------------------------------------------------------------------
static void NitroStaticInit(void)
{
	PoketchSetAppProc(Poketch_A18_Init, Poketch_A18_Quit);
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
static BOOL Poketch_A18_Init(void **wk_ptr, CONTACT_WORK* conwk, GF_BGL_INI* bgl, u32 appNumber)
{
	APPWORK* wk = (APPWORK*)sys_AllocMemory( POKETCH_APP_CTRL_HEAPID, sizeof(APPWORK));

	if(wk != NULL)
	{
		if(SetupWork( wk, conwk, bgl, appNumber ))
		{
			if( TCB_Add(Poketch_A18_Main, wk, POKETCH_APP_TASKPRI) != NULL )
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
	static const TP_HIT_TBL hit_tbl[] = {
		{ BUTTON_ATTACK_L_TOP, BUTTON_ATTACK_L_BOTTOM, BUTTON_ATTACK_L_LEFT, BUTTON_ATTACK_L_RIGHT },
		{ BUTTON_ATTACK_R_TOP, BUTTON_ATTACK_R_BOTTOM, BUTTON_ATTACK_R_LEFT, BUTTON_ATTACK_R_RIGHT },
		{ BUTTON_DEFENCE0_L_TOP, BUTTON_DEFENCE0_L_BOTTOM, BUTTON_DEFENCE0_L_LEFT, BUTTON_DEFENCE0_L_RIGHT },
		{ BUTTON_DEFENCE0_R_TOP, BUTTON_DEFENCE0_R_BOTTOM, BUTTON_DEFENCE0_R_LEFT, BUTTON_DEFENCE0_R_RIGHT },
		{ BUTTON_DEFENCE1_L_TOP, BUTTON_DEFENCE1_L_BOTTOM, BUTTON_DEFENCE1_L_LEFT, BUTTON_DEFENCE1_L_RIGHT },
		{ BUTTON_DEFENCE1_R_TOP, BUTTON_DEFENCE1_R_BOTTOM, BUTTON_DEFENCE1_R_LEFT, BUTTON_DEFENCE1_R_RIGHT },
	};

	wk->appNumber = appNumber;
	if( PoketchWork_Load( appNumber, &(wk->vpara), sizeof(wk->vpara) ) == FALSE )
	{
		init_vparam( &(wk->vpara) );
	}

	if( Poketch_A18_SetViewWork( &(wk->vwk), &(wk->vpara), bgl ) )
	{

		wk->main_seq = SEQ_INIT;
		wk->seq = 0;
		wk->quit_req_flag = FALSE;
		wk->button = PBTN_Create( hit_tbl, NELEMS(hit_tbl), ButtonCallBack, wk, POKETCH_APP_CTRL_HEAPID );
		wk->button_event = BMN_EVENT_NULL;

		wk->conwk = conwk;
		return TRUE;
	}

	return FALSE;
}
//------------------------------------------------------------------
/**
 * 描画パラメータの初期化
 *
 * @param   vpara		
 *
 */
//------------------------------------------------------------------
static void init_vparam( VIEWPARAM* vpara )
{
	vpara->button_id = 0;

	vpara->attack_type = NORMAL_TYPE;
	vpara->defence0_type = NORMAL_TYPE;
	vpara->defence1_type = AISYOU_TYPE_NULL;

	vpara->effect_lv = calc_effect_lv( vpara->attack_type, vpara->defence0_type, vpara->defence1_type );
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
	PoketchWork_Save( wk->appNumber, &(wk->vpara), sizeof(wk->vpara) );
	PBTN_Delete( wk->button );
	Poketch_A18_DeleteViewWork( wk->vwk );
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
static void Poketch_A18_Main(TCB_PTR tcb, void *wk_adrs)
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

	wk->vpara.button_id = idx;
	wk->button_event = event;
}

//------------------------------------------------------------------
/**
 * アプリ終了関数
 *
 * @param   wk_adrs		ワークアドレス
 *
 */
//------------------------------------------------------------------
static void Poketch_A18_Quit(void *wk_adrs)
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
		Poketch_A18_SetViewCommand( wk->vwk, CMD_INIT );
		wk->seq++;
		break;

	case 1:
		if(Poketch_A18_WaitViewCommand( wk->vwk, CMD_INIT ))
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
		if( Poketch_A18_WaitViewCommandAll( wk->vwk ) )
		{
			ChangeSeq( wk, SEQ_QUIT );
		}
		return FALSE;
	}

	switch( wk->seq ){
	case 0:
		if( wk->button_event == BMN_EVENT_TOUCH )
		{
			Poketch_A18_SetViewCommand( wk->vwk, CMD_BUTTON_PUSH );
			wk->seq++;
		}
		break;

	case 1:
		if( wk->button_event == BMN_EVENT_OUT )
		{
			Poketch_A18_SetViewCommand( wk->vwk, CMD_BUTTON_RELEASE );
			wk->seq = 0;
			break;
		}
		if( wk->button_event == BMN_EVENT_TAP )
		{
			switch( wk->vpara.button_id ){
			case BUTTON_ID_ATTACK_L:
				wk->vpara.attack_type = get_next_type( wk->vpara.attack_type, -1, FALSE );
				break;
			case BUTTON_ID_ATTACK_R:
				wk->vpara.attack_type = get_next_type( wk->vpara.attack_type, 1, FALSE );
				break;
			case BUTTON_ID_DEFENCE0_L:
				wk->vpara.defence0_type = get_next_type( wk->vpara.defence0_type, -1, FALSE );
				break;
			case BUTTON_ID_DEFENCE0_R:
				wk->vpara.defence0_type = get_next_type( wk->vpara.defence0_type, 1, FALSE );
				break;
			case BUTTON_ID_DEFENCE1_L:
				wk->vpara.defence1_type = get_next_type( wk->vpara.defence1_type, -1, TRUE );
				break;
			case BUTTON_ID_DEFENCE1_R:
				wk->vpara.defence1_type = get_next_type( wk->vpara.defence1_type, 1, TRUE );
				break;
			}
			wk->vpara.effect_lv = calc_effect_lv( wk->vpara.attack_type, wk->vpara.defence0_type, wk->vpara.defence1_type );
			Poketch_A18_SetViewCommand( wk->vwk, CMD_BUTTON_RELEASE );
			Poketch_A18_SetViewCommand( wk->vwk, CMD_UPDATE_EFFECT );
			wk->seq++;
			break;
		}
		break;

	case 2:
		if( Poketch_A18_WaitViewCommandAll(wk->vwk) )
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
		Poketch_A18_SetViewCommand( wk->vwk, CMD_QUIT );
		wk->seq++;
		break;

	case 1:
		if(Poketch_A18_WaitViewCommandAll( wk->vwk ))
		{
			return TRUE;
		}
		break;
	}

	return FALSE;
}










//------------------------------------------------------------------
/**
 * 技効果レベル判定
 *
 * @param   attack_type		
 * @param   defence_type0		
 * @param   defence_type1		
 *
 * @retval  u32		レベル0（効果なし）～レベル5（４倍）
 */
//------------------------------------------------------------------
static u32 calc_effect_lv( u32 attack_type, u32 defence_type0, u32 defence_type1 )
{
	enum {
		E_0 = -10,	// 効果なし
		E_H = -1,	// 効果 1/2
		E_N = 0,	// 効果 そのまま
		E_D = 1,	// 効果 x2

		EF_DEFAULT_LV = 3,

	};

	static const s8 effect_tbl[][AISYOU_TYPE_MAX] = {
/*			  NRML,FIGT,FLY ,POIS,GRND,ROCK,INSC,GOST,STEL,????,FIRE,WATR,GRAS,ELEC,ESPR,ICE ,DRGN,EVIL		*/
/* NRML */	{ E_N, E_N, E_N, E_N, E_N, E_H, E_N, E_0, E_H, E_N, E_N, E_N, E_N, E_N, E_N, E_N, E_N, E_N },
/* FIGT */	{ E_D, E_N, E_H, E_H, E_N, E_D, E_H, E_0, E_D, E_N, E_N, E_N, E_N, E_N, E_H, E_D, E_N, E_D },
/* FLY  */	{ E_N, E_D, E_N, E_N, E_N, E_H, E_D, E_N, E_H, E_N, E_N, E_N, E_D, E_H, E_N, E_N, E_N, E_N },
/* POIS */	{ E_N, E_N, E_N, E_H, E_H, E_H, E_N, E_H, E_0, E_N, E_N, E_N, E_D, E_N, E_N, E_N, E_N, E_N },
/* GRND */	{ E_N, E_N, E_0, E_D, E_N, E_D, E_H, E_N, E_D, E_N, E_D, E_N, E_H, E_D, E_N, E_N, E_N, E_N },
/* ROCK */	{ E_N, E_H, E_D, E_N, E_H, E_N, E_D, E_N, E_H, E_N, E_D, E_N, E_N, E_N, E_N, E_D, E_N, E_N },
/* INSC */	{ E_N, E_H, E_H, E_H, E_N, E_N, E_N, E_H, E_H, E_N, E_H, E_N, E_D, E_N, E_D, E_N, E_N, E_D },
/* GOST */	{ E_0, E_N, E_N, E_N, E_N, E_N, E_N, E_D, E_H, E_N, E_N, E_N, E_N, E_N, E_D, E_N, E_N, E_H },
/* STEL */	{ E_N, E_N, E_N, E_N, E_N, E_D, E_N, E_N, E_H, E_N, E_H, E_H, E_N, E_H, E_N, E_D, E_N, E_N },
/* ???  */	{ E_N, E_N, E_N, E_N, E_N, E_N, E_N, E_N, E_N, E_N, E_N, E_N, E_N, E_N, E_N, E_N, E_N, E_N },
/* FIRE */	{ E_N, E_N, E_N, E_N, E_N, E_H, E_D, E_N, E_D, E_N, E_H, E_H, E_D, E_N, E_N, E_D, E_H, E_N },
/* WATR */	{ E_N, E_N, E_N, E_N, E_D, E_D, E_N, E_N, E_N, E_N, E_D, E_H, E_H, E_N, E_N, E_N, E_H, E_N },
/* GRAS */	{ E_N, E_N, E_H, E_H, E_D, E_D, E_H, E_N, E_H, E_N, E_H, E_D, E_H, E_N, E_N, E_N, E_H, E_N },
/* ELEC */	{ E_N, E_N, E_D, E_N, E_0, E_N, E_N, E_N, E_N, E_N, E_N, E_D, E_H, E_H, E_N, E_N, E_H, E_N },
/* ESPR */	{ E_N, E_D, E_N, E_D, E_N, E_N, E_N, E_N, E_H, E_N, E_N, E_N, E_N, E_N, E_H, E_N, E_N, E_0 },
/* ICE  */	{ E_N, E_N, E_D, E_N, E_D, E_N, E_N, E_N, E_H, E_N, E_H, E_H, E_D, E_N, E_N, E_H, E_D, E_N },
/* DRGN */	{ E_N, E_N, E_N, E_N, E_N, E_N, E_N, E_N, E_H, E_N, E_N, E_N, E_N, E_N, E_N, E_N, E_D, E_N },
/* EVIL */	{ E_N, E_H, E_N, E_N, E_N, E_N, E_N, E_D, E_H, E_N, E_N, E_N, E_N, E_N, E_D, E_N, E_N, E_H },
	};


	if( (effect_tbl[attack_type][defence_type0] == E_0)
	||	( (defence_type1 != AISYOU_TYPE_NULL) && (effect_tbl[attack_type][defence_type1] == E_0) )
	){
		return 0;
	}
	else
	{
		u32  eff_lv = EF_DEFAULT_LV;

		eff_lv += effect_tbl[attack_type][defence_type0];
		if( defence_type1 != AISYOU_TYPE_NULL && defence_type1 != defence_type0 )
		{
			eff_lv += effect_tbl[attack_type][defence_type1];
		}
		return eff_lv;
	}
}

static u32 get_next_type( s32 type, s32 direction, BOOL null_in_flag )
{
	static const u8 type_lotate_tbl[] = {
		NORMAL_TYPE,	FIRE_TYPE,		WATER_TYPE,		ELECTRIC_TYPE,		KUSA_TYPE,		KOORI_TYPE,
		BATTLE_TYPE,	POISON_TYPE,	JIMEN_TYPE,		HIKOU_TYPE,			SP_TYPE,		MUSHI_TYPE,
		IWA_TYPE,		GHOST_TYPE,		DRAGON_TYPE,	AKU_TYPE,			METAL_TYPE,		
	};

	int i;

	for(i=0; i<NELEMS(type_lotate_tbl); i++)
	{
		if( type_lotate_tbl[i] == type ){ break; }
	}

	// 無効値だった場合
	if( i == NELEMS(type_lotate_tbl) )
	{
		return (direction > 0)? type_lotate_tbl[0] : type_lotate_tbl[(NELEMS(type_lotate_tbl)-1)];
	}

	i += direction;

	if( i >= (int)(NELEMS(type_lotate_tbl)) )	// u32 に揃えられて絶対TRUEになってしまうのでキャストしちゃう
	{
		if( null_in_flag )
		{
			return AISYOU_TYPE_NULL;
		}
		i = 0;
	}
	if( i < 0 )
	{
		if( null_in_flag )
		{
			return AISYOU_TYPE_NULL;
		}
		i = NELEMS(type_lotate_tbl) - 1;
	}

	return type_lotate_tbl[i];

}
