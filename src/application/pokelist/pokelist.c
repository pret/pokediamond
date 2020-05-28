//============================================================================================
/**
 * @file	pokelist.c
 * @brief	ポケモンリスト画面処理
 * @author	Hiroyuki Nakamura
 * @date	05.09.20
 */
//============================================================================================
#include "common.h"
#include "gflib/touchpanel.h"
#include "system/procsys.h"
#include "system/arc_tool.h"
#include "system/arc_util.h"
#include "system/clact_tool.h"
#include "system/brightness.h"
#include "system/fontproc.h"
#include "system/bmp_menu.h"
#include "system/window.h"
#include "system/msgdata.h"
#include "system/numfont.h"
#include "system/wordset.h"
#include "system/snd_tool.h"
#include "system/wipe.h"
#include "poketool/monsno.h"
#include "poketool/pokeicon.h"
#include "poketool/pokeparty.h"
#include "poketool/status_rcv.h"
#include "poketool/poke_regulation.h"
#include "msgdata/msg.naix"
#include "msgdata/msg_pokelist.h"
#include "battle/battle_common.h"
#include "battle/wazano_def.h"
#include "itemtool/item.h"
#include "itemtool/myitem.h"
#include "contest/contest_def.h"
#include "application/p_status.h"
#include "application/app_tool.h"
#include "communication/wm_icon.h"
#include "field/tvtopic_extern.h"
#include "field/fieldsys.h"
#include "../../field/b_tower_ev.h"

#define	POKELIST_H_GLOBAL
#include "application/pokelist.h"
#include "plist_sys.h"
#include "plist_obj.h"
#include "plist_bmp.h"
#include "plist_menu.h"
#include "plist_item.h"
#include "plist_snd_def.h"
#include "application/plist_gra.naix"


//============================================================================================
//	定数定義
//============================================================================================
// 選択結果
enum {
	SEL_POKE = 0,
	SEL_MOVE,
	SEL_TOUCH,
	SEL_CANCEL,
	SEL_ENTER,
	SEL_NONE,
};


// パネルタイプ
enum {
	PANELTYPE_NORMAL = 0,
	PANELTYPE_MULTI,
	PANELTYPE_DETH,
	PANELTYPE_CHANGE,

	PANELTYPE_SELECT,
};

// メニュー選択
enum {
	MENU_SEL_NONE = 0,
	MENU_SEL_CANCEL
};


// パネルの座標
typedef struct {
	u16	plate_px;	// プレートX座標
	u16	plate_py;	// プレートY座標

	u16	icon_px;	// ポケモンアイコンX座標
	u16	icon_py;	// ポケモンアイコンY座標

	u16	ball_px;	// ボールOBJX座標
	u16	ball_py;	// ボールOBJY座標
}PANEL_POS;

#define	POKESEL_EX_FLAG		( 0x80 )	// 前回のカーソル位置へ


//============================================================================================
//	プロトタイプ宣言
//============================================================================================
static PROC_RESULT PokeListProc_Init( PROC * proc, int * seq );
static PROC_RESULT PokeListProc_Main( PROC * proc, int * seq );
static PROC_RESULT PokeListProc_End( PROC * proc, int * seq );

static int MainSeq_In( PLIST_WORK * wk );
static int MainSeq_Main( PLIST_WORK * wk );
static int MainSeq_ItemUseSel( PLIST_WORK * wk );
static int MainSeq_ItemSetSel( PLIST_WORK * wk );
static int MainSeq_MsgWait( PLIST_WORK * wk );
static int MainSeq_EndTrgWait( PLIST_WORK * wk );
static int MainSeq_YesNoInit( PLIST_WORK * wk );
static int MainSeq_YesNoMain( PLIST_WORK * wk );
static int MainSeq_WazaSetSel( PLIST_WORK * wk );
static int MainSeq_Milknomi( PLIST_WORK * wk );

static void PokeListVBlank( void * work );
//static void PokeListVBlank( TCB_PTR tcb, void * work );

static void PokeListVramBankSet(void);
static void PokeListBgSet( GF_BGL_INI * ini );
static void PokeListBgExit( GF_BGL_INI * ini );
static void PokeListBgGraphicSet( PLIST_WORK * wk );
static PLIST_WORK * PokeListWorkInit( PROC * proc );
static void ListModeSet( PLIST_WORK * wk );
static void PokePanelMake( PLIST_WORK * wk );
static u8 PokeMultiCheck( PLIST_WORK * wk, u8 num );
static u8 PokeSelectMain( PLIST_WORK * wk );
static void PanelSelectChg( PLIST_WORK * wk, u8 pos, u8 flg );
static void InitCursorPosSet( PLIST_WORK * wk );
static void CancelCheck( PLIST_WORK * wk );
static int PL_SelectEnter( PLIST_WORK * wk );

static u8 MenuControl( PLIST_WORK * wk, int * seq );
static void MenuExit( PLIST_WORK * wk );
static u8 PokeSelectRow( PLIST_WORK * wk );
static void SubButtonScrnPut( PLIST_WORK * wk, u8 pos, u8 anm );
static int SubButtonCheck( PLIST_WORK * wk );

static u8 PokeSelectItemUse( PLIST_WORK * wk );
static int ItemUseCheck( PLIST_WORK * wk );

static u8 PokeItemCheck( PLIST_WORK * wk );
static int PokeItemSetInit_Bag( PLIST_WORK * wk );
static void PokeList_ItemSet( PLIST_WORK * wk, POKEMON_PARAM * pp );
static int PokeItemSetWait_Bag( PLIST_WORK * wk );
static int PokeItemSetYesNoInit_Bag( PLIST_WORK * wk );
static int PokeItemSetYesNoMain_Bag( PLIST_WORK * wk );
static int MainSeq_ItemMenuSel( PLIST_WORK * wk );
static int PokeItemEndCheck( PLIST_WORK * wk );
static int PL_MailSetEnd( PLIST_WORK * wk );

static void PL_ContestEntryCheck( PLIST_WORK * wk, POKEMON_PARAM * pp, u8 pos );
static u32 PL_TrialMedalGet( POKEMON_PARAM * pp, u8 type );

static void PL_SubButtonAnm( PLIST_WORK * wk );
static void SubButtonEffPosGet( u8 pos, s16 * x, s16 * y );

static int PokeList_KapselGetCheck( PLIST_WORK * wk );

static u8 PL_BattleTowerEnterCheck( PLIST_WORK * wk );

static BOOL PL_TouchPanelCheck( PLIST_WORK * wk );


//============================================================================================
//	グローバル変数
//============================================================================================
// プロセス定義データ
const PROC_DATA PokeListProcData = {
	PokeListProc_Init,
	PokeListProc_Main,
	PokeListProc_End,
	NO_OVERLAY_ID,
};


// パネルの座標テーブル
static const PANEL_POS PanelPosTable[2][6] =
{
	{	// シングル/ダブル
		{ 0,0,		30,16,		16,14 },
		{ 16,1,		158,24,		144,22 },
		{ 0,6,		30,64,		16,62 },
		{ 16,7,		158,72,		144,70 },
		{ 0,12,		30,112,		16,110 },
		{ 16,13,	158,120,	144,118 }
	},
	{	// マルチ
		{ 0,0,		30,16,		16,14 },
		{ 16,0,		158,24-8,	144,22-8 },
		{ 0,6,		30,64,		16,62 },
		{ 16,6,		158,72-8,	144,70-8 },
		{ 0,12,		30,112,		16,110 },
		{ 16,12,	158,120-8,	144,118-8 }
	}
};

// 通常のカーソル移動テーブル
static const POINTER_WORK NormalMoveTable[] =
{
	{  64, 24+1,0,0,	7,2,7,1 },	// 0
	{ 192, 32+1,0,0,	7,3,0,2 },	// 1
	{  64, 72+1,0,0,	0,4,1,3 },	// 2
	{ 192, 80+1,0,0,	1,5,2,4 },	// 3
	{  64,120+1,0,0,	2,7,3,5 },	// 4
	{ 192,128+1,0,0,	3,7,4,7 },	// 5
	{   0,  0,0,0,	0,0,0,0 },	// 6	ダミー（決定）
	{ 224,168,0,0,	5,1,5,0 }	// 7
/*
	{  64, 24+1,0,0,	7,1,7,1 },	// 0
	{ 192, 32+1,0,0,	0,2,0,2 },	// 1
	{  64, 72+1,0,0,	1,3,1,3 },	// 2
	{ 192, 80+1,0,0,	2,4,2,4 },	// 3
	{  64,120+1,0,0,	3,5,3,5 },	// 4
	{ 192,128+1,0,0,	4,7,4,7 },	// 5
	{   0,  0,0,0,	0,0,0,0 },	// 6	ダミー（決定）
	{ 224,168,0,0,	5,0,5,0 }	// 7
*/
};
// マルチバトルのカーソル移動テーブル
static const POINTER_WORK MultiMoveTable[] =
{
	{  64, 24+1,0,0,	4,2,1,1 },			// 0
	{ 192, 24+1,0,0,	7,3,0,0 },			// 1
	{  64, 72+1,0,0,	0,4,3,3 },			// 2
	{ 192, 72+1,0,0,	1,5,2,2 },			// 3
	{  64,120+1,0,0,	2,0,5,5 },			// 4
	{ 192,120+1,0,0,	3,7,4,4 },			// 5
	{ 224,168,0,0,	0,0,0,0 },			// 6	ダミー（決定）
	{ 224,168,0,0,	5,1,0xff,0xff }		// 7
};
// 「けってい」有りのカーソル移動テーブル
static const POINTER_WORK SelectMoveTable[] =
{
	{  64, 24+1,0,0,	7,2,7,1 },	// 0
	{ 192, 32+1,0,0,	7,3,0,2 },	// 1
	{  64, 72+1,0,0,	0,4,1,3 },	// 2
	{ 192, 80+1,0,0,	1,5,2,4 },	// 3
	{  64,120+1,0,0,	2,6,3,5 },	// 4
	{ 192,128+1,0,0,	3,6,4,6 },	// 5
	{ 224,168,0,0,	5,7,5,7 },	// 6
	{ 224,184,0,0,	6,1,6,0 },	// 7
/*
	{  64, 24+1,0,0,	7,1,7,1 },	// 0
	{ 192, 32+1,0,0,	0,2,0,2 },	// 1
	{  64, 72+1,0,0,	1,3,1,3 },	// 2
	{ 192, 80+1,0,0,	2,4,2,4 },	// 3
	{  64,120+1,0,0,	3,5,3,5 },	// 4
	{ 192,128+1,0,0,	4,6,4,6 },	// 5
	{ 224,168,0,0,	5,7,5,7 },	// 6
	{ 224,184,0,0,	6,0,6,0 },	// 7
*/
};

// メニューの技テーブル
static const u16 WazaTbl[] = {
	WAZANO_IAIGIRI,			// 技：いあいぎり
	WAZANO_SORAWOTOBU,		// 技：そらをとぶ
	WAZANO_NAMINORI,		// 技：なみのり
	WAZANO_KAIRIKI,			// 技：かいりき
	WAZANO_KIRIBARAI,		// 技：きりばらい
	WAZANO_IWAKUDAKI,		// 技：いわくだき
	WAZANO_TAKINOBORI,		// 技：たきのぼり
	WAZANO_ROKKUKURAIMU,	// 技：ロッククラム

	WAZANO_HURASSYU,		// 技：フラッシュ
	WAZANO_TEREPOOTO,		// 技：テレポート
	WAZANO_ANAWOHORU,		// 技：あなをほる
	WAZANO_AMAIKAORI,		// 技：あまいかおり
	WAZANO_OSYABERI,		// 技：おしゃべり
	WAZANO_MIRUKUNOMI,		// 技：ミルクのみ
	WAZANO_TAMAGOUMI		// 技：タマゴうみ
};


//============================================================================================
//	プロセス関数
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * プロセス関数：初期化
 *
 * @param	proc	プロセスデータ
 * @param	seq		シーケンス
 *
 * @return	処理状況
 */
//--------------------------------------------------------------------------------------------
static PROC_RESULT PokeListProc_Init( PROC * proc, int * seq )
{
	PLIST_WORK * wk;

	sys_VBlankFuncChange( NULL, NULL );	// VBlankセット
	sys_HBlankIntrStop();				//HBlank割り込み停止

	GF_Disp_GX_VisibleControlInit();
	GF_Disp_GXS_VisibleControlInit();
	GX_SetVisiblePlane( 0 );
	GXS_SetVisiblePlane( 0 );

	G2_BlendNone();
	G2S_BlendNone();

	sys_KeyRepeatSpeedSet( 4, 8 );
	sys_CreateHeap( HEAPID_BASE_APP, HEAPID_POKELIST, 0x20000 );

	wk = PokeListWorkInit( proc );

	WIPE_SYS_Start(
		WIPE_PATTERN_FMAS, WIPE_TYPE_SHUTTERIN_DOWN, WIPE_TYPE_SHUTTERIN_DOWN,
		WIPE_FADE_BLACK, WIPE_DEF_DIV, WIPE_DEF_SYNC, HEAPID_POKELIST );

	// キャンセル設定
	CancelCheck( wk );

	PokeListVramBankSet();
	PokeListBgSet( wk->bgl );
	PokeListBgGraphicSet( wk );

	InitTPSystem();						// タッチパネルシステム初期化
	InitTPNoBuff(4);

	Snd_DataSetByScene( SND_SCENE_SUB_POKELIST, 0, 0 );

	PokeListBmpAdd( wk );

	PokeListCellActorInit( wk );
	PokeListCellActSet( wk );

	ListModeSet( wk );

	PokePanelMake( wk );

	PanelSelectChg( wk, wk->pos, 1 );

	if( wk->dat->mode == PL_MODE_ITEMUSE || wk->dat->mode == PL_MODE_SHINKA ){
		if( PL_ALLDeathRcvItemCheck( wk->dat->item ) == FALSE ){
			PokeListSmallMsgPut( wk, mes_pokelist_02_04, 1 );
		}
	}else if( wk->dat->mode == PL_MODE_WAZASET ){
		PokeListSmallMsgPut( wk, mes_pokelist_02_05, 1 );
	}else if( wk->dat->mode == PL_MODE_ITEMSET || wk->dat->mode == PL_MODE_MAILBOX ){
		PokeListSmallMsgPut( wk, mes_pokelist_02_03, 1 );
	}else if( wk->dat->mode == PL_MODE_WAZASET_RET || wk->dat->mode == PL_MODE_LVUPWAZASET_RET ||
			  wk->dat->mode == PL_MODE_MAILSET || wk->dat->mode == PL_MODE_MAILSET_BAG ){
		CATS_ObjectPaletteSet( wk->act_work[PLIST_ACT_CURSOR1], 1 );
	}else if( wk->dat->mode == PL_MODE_SELECT || wk->dat->mode == PL_MODE_BATTLE_TOWER ){
		PokeListSmallMsgPut( wk, mes_pokelist_02_06, 1 );
	}else if( wk->dat->mode == PL_MODE_KAPSEL_SET ){
		PokeListSmallMsgPut( wk, mes_pokelist_02_06, 1 );
	}else if( wk->dat->mode != PL_MODE_ITEMSET_RET ){
		PokeListSmallMsgPut( wk, mes_pokelist_02_01, 1 );
	}else{
		CATS_ObjectPaletteSet( wk->act_work[PLIST_ACT_CURSOR1], 1 );
	}

	PokeListMenuStrMake( wk );
	InitCursorPosSet( wk );

	if( PL_TouchPanelCheck( wk ) == FALSE ){
		GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_OFF );
	}

//	sys_HBlankIntrSet( BagInWipeEff );	// HBlankセット
	sys_VBlankFuncChange( PokeListVBlank, wk );	// VBlankセット

//	wk->vtask = VIntrTCB_Add( PokeListVBlank, wk, 0 );
//	wk->vtask = VWaitTCB_Add( PokeListVBlank, wk, 0 );

	WirelessIconEasyUnion();

	return PROC_RES_FINISH;
}

//--------------------------------------------------------------------------------------------
/**
 * プロセス関数：メイン
 *
 * @param	proc	プロセスデータ
 * @param	seq		シーケンス
 *
 * @return	処理状況
 */
//--------------------------------------------------------------------------------------------
static PROC_RESULT PokeListProc_Main( PROC * proc, int * seq )
{
	PLIST_WORK * wk  = PROC_GetWork( proc );

	switch( *seq ){
	case SEQ_IN:
		*seq = MainSeq_In( wk );
		break;

	case SEQ_MAIN:
		*seq = MainSeq_Main( wk );
		break;

	case SEQ_MENU:
		if( MenuControl( wk, seq ) == MENU_SEL_CANCEL ){
			*seq = SEQ_MAIN;
		}
		break;

	case SEQ_MENUWAZA_ERR:
		*seq = PokeList_MenuWazaError( wk );
		break;

	case SEQ_ITEMUSE_SEL:
		*seq = MainSeq_ItemUseSel( wk );
		break;

	case SEQ_ITEMUSE_WAIT:
		*seq = wk->strcv_func( wk );
		break;

	case SEQ_WAZAMENU_SEL:
		*seq = PokeList_WazaMenuMain( wk );
		break;

	case SEQ_ITEMUSE_ALLDEATHRCV:	// 全体瀕死回復
		*seq = PokeList_AllDeathRcvMain( wk );
		break;

	case SEQ_ITEMSET_SEL:
		*seq = MainSeq_ItemSetSel( wk );
		break;
	case SEQ_ITEMSET_YN_INIT:
		*seq = PokeItemSetYesNoInit_Bag( wk );
		break;
	case SEQ_ITEMSET_YN_MAIN:
		*seq = PokeItemSetYesNoMain_Bag( wk );
		break;
	case SEQ_ITEMSET_WAIT:
		*seq = PokeItemSetWait_Bag( wk );
		break;

	case SEQ_MAILSET_END:
		*seq = PL_MailSetEnd( wk );
		break;

	case SEQ_ITEM_MENU:
		*seq = MainSeq_ItemMenuSel( wk );
		break;

	case SEQ_ITEM_MENU_SET_RET:
		*seq = PokeItemSetInit_Bag( wk );
		break;

	case SEQ_ITEM_MENU_GET:
		*seq = PokeList_ItemMenuItemGetEndWait( wk );
		break;

	case SEQ_ITEMGET_END:
		*seq = PokeList_ItemGetEnd( wk );
		break;

	case SEQ_WAZASET_SEL:	// 技覚え
		*seq = MainSeq_WazaSetSel( wk );
		break;

	case SEQ_WAZASET_RET_SET:
		*seq = PokeList_WazaSetRetSet( wk );
		break;

	case SEQ_BTLIN_ERR:		// 戦闘参加エラー
		*seq = PokeList_BattleInWaitError( wk );
		break;

	case SEQ_MSG_WAIT:		// メッセージウェイト
		*seq = MainSeq_MsgWait( wk );
		break;

	case SEQ_ENDTRG_WAIT:	// トリガーウェイト -> 終了
		*seq = MainSeq_EndTrgWait( wk );
		break;

	case SEQ_YESNO_INIT:	// はい・いいえ表示
		*seq = MainSeq_YesNoInit( wk );
		break;

	case SEQ_YESNO_MAIN:	// はい・いいえ選択
		*seq = MainSeq_YesNoMain( wk );
		break;

	case SEQ_ROW_SEL:
		{
			u8	sel = PokeSelectRow( wk );

			if( sel == SEL_POKE ){
				*seq = SEQ_FUNC_WAIT;
			}else if( sel == SEL_CANCEL ){
				*seq = SEQ_MAIN;
			}
		}
		break;

	case SEQ_FUNC_WAIT:
		if( PokeListMenu_NarabikaeMain( wk ) == TRUE ){
			*seq = SEQ_MAIN;
		}
		break;

	case SEQ_MILKNOMI:
		*seq = MainSeq_Milknomi( wk );
		break;

	case SEQ_OUT_SET:
		APP_WipeStart( APP_WIPE_OUT, HEAPID_POKELIST );
		*seq = SEQ_OUT;
		break;

	case SEQ_OUT:
		if( WIPE_SYS_EndCheck() == TRUE ){
			wk->dat->ret_sel = wk->pos;
			return PROC_RES_FINISH;
		}
		break;
	}

/*
	if( wk->vblank_func != NULL ){
		wk->vblank_func( wk );
	}
*/

	PokeIconAnime( wk );
	PokeListObj_SubButtonEffMain( wk );
	PL_SubButtonAnm( wk );

	CATS_Draw( wk->crp );

	return PROC_RES_CONTINUE;
}

static int MainSeq_In( PLIST_WORK * wk )
{
	if( WIPE_SYS_EndCheck() == TRUE ){
		if( wk->dat->mode == PL_MODE_ITEMUSE || wk->dat->mode == PL_MODE_SHINKA ){
			if( PL_ALLDeathRcvItemCheck( wk->dat->item ) == TRUE ){
				wk->next_seq = 0;
				return SEQ_ITEMUSE_ALLDEATHRCV;
			}
			return SEQ_ITEMUSE_SEL;
		}else if( wk->dat->mode == PL_MODE_WAZASET ){
			return SEQ_WAZASET_SEL;
		}else if( wk->dat->mode == PL_MODE_WAZASET_RET ){
			return PokeList_WazaSetRetInit( wk );
		}else if( wk->dat->mode == PL_MODE_LVUPWAZASET_RET ){
			return PokeList_LvUpWazaSetRetInit( wk );
		}else if( wk->dat->mode == PL_MODE_MAILSET || wk->dat->mode == PL_MODE_MAILSET_BAG ){
			return SEQ_MAILSET_END;
		}else if( wk->dat->mode == PL_MODE_ITEMSET ){
			return SEQ_ITEMSET_SEL;
		}else if( wk->dat->mode == PL_MODE_ITEMSET_RET ){
			return SEQ_ITEM_MENU_SET_RET;
		}else{
			return SEQ_MAIN;
		}
	}
	return SEQ_IN;
}

static int MainSeq_Main( PLIST_WORK * wk )
{
	u8	sel = PokeSelectMain( wk );

	if( sel == SEL_POKE ){
		if( wk->dat->mode == PL_MODE_SET || wk->dat->mode == PL_MODE_PORUTO ){
			wk->dat->ret_mode = PL_RET_NORMAL;
			return SEQ_OUT_SET;
		}else if( wk->dat->mode == PL_MODE_MAILBOX ){
			PokeList_MailBoxAdd( wk );
			return SEQ_MSG_WAIT;
		}else if( wk->dat->mode == PL_MODE_NPC_TRADE ){
			return PokeList_KapselGetCheck( wk );
		}else{
			return SEQ_MENU;
		}
	}else if( sel == SEL_ENTER ){
		return PL_SelectEnter( wk );
	}else if( sel == SEL_CANCEL ){
		wk->dat->ret_mode = PL_RET_NORMAL;
		return SEQ_OUT_SET;
	}else if( sel == SEL_TOUCH ){
		if( wk->dat->mode != PL_MODE_KAPSEL_SET ){
			wk->dat->ret_mode = PL_RET_STATUS;
			return SEQ_OUT_SET;
		}else{
			CATS_ObjectPaletteSet( wk->act_work[PLIST_ACT_CURSOR1], 1 );
			return PLIST_MenuKapselSet( wk );
		}
	}
	return SEQ_MAIN;
}

static int MainSeq_ItemUseSel( PLIST_WORK * wk )
{
	u8	sel = PokeSelectItemUse( wk );

	if( sel == SEL_POKE || sel == SEL_TOUCH ){
		CATS_ObjectPaletteSet( wk->act_work[PLIST_ACT_CURSOR1], 1 );
		return ItemUseCheck( wk );
	}else if( sel == SEL_CANCEL ){
		wk->dat->ret_mode = PL_RET_NORMAL;
		return SEQ_OUT_SET;
	}

	return SEQ_ITEMUSE_SEL;
}

// アイテムをもたせる
static int MainSeq_ItemSetSel( PLIST_WORK * wk )
{
	u8	sel = PokeSelectItemUse( wk );

	if( sel == SEL_POKE || sel == SEL_TOUCH ){
		CATS_ObjectPaletteSet( wk->act_work[PLIST_ACT_CURSOR1], 1 );
		return PokeItemSetInit_Bag( wk );
	}else if( sel == SEL_CANCEL ){
		wk->dat->ret_mode = PL_RET_NORMAL;
		return SEQ_OUT_SET;
	}

	return SEQ_ITEMSET_SEL;
}

// 「もちもの」メニュー
static int MainSeq_ItemMenuSel( PLIST_WORK * wk )
{
	u32	ret = BmpMenuMain( wk->mw );

	switch( ret ){
	case BMPMENU_NULL:
		break;

	case BMPMENU_CANCEL:
		BmpTalkWinClear( &wk->win[WIN_M_MSG], WINDOW_TRANS_OFF );
		BmpMenuWinClear( &wk->win[WIN_ITEM_MENU], WINDOW_TRANS_OFF );
		GF_BGL_BmpWinOffVReq( &wk->win[WIN_ITEM_MENU] );
		BmpMenuExit( wk->mw, NULL );
		BMP_MENULIST_Delete( wk->md );
		PokeListSmallMsgPut( wk, mes_pokelist_02_01, 1 );
		CATS_ObjectPaletteSet( wk->act_work[PLIST_ACT_CURSOR1], 0 );
		return SEQ_MAIN;

	default:
		{
			pPLMenuFunc	func;
			int	seq;

			func = (pPLMenuFunc)ret;
			func( wk, &seq );
			return seq;
		}
	}

	return SEQ_ITEM_MENU;
}

static int MainSeq_MsgWait( PLIST_WORK * wk )
{
	if( GF_MSG_PrintEndCheck( wk->msg_index ) == 0 ){
		return wk->next_seq;
	}
	return SEQ_MSG_WAIT;
}

static int MainSeq_EndTrgWait( PLIST_WORK * wk )
{
	if( sys.trg & (PAD_BUTTON_DECIDE|PAD_BUTTON_CANCEL) ){
		Snd_SePlay( PLIST_SE_ENTER );
		return SEQ_OUT_SET;
	}
	return SEQ_ENDTRG_WAIT;
}

static int MainSeq_YesNoInit( PLIST_WORK * wk )
{
	PokeList_YesNoSelectInit( wk );
	return SEQ_YESNO_MAIN;
}

static int MainSeq_YesNoMain( PLIST_WORK * wk )
{
	switch( BmpYesNoSelectMain( wk->mw, HEAPID_POKELIST ) ){
	case 0:
		return wk->yesno.yes( wk );
	case BMPMENU_CANCEL:
		return wk->yesno.no( wk );
	}
	return SEQ_YESNO_MAIN;
}


static int MainSeq_WazaSetSel( PLIST_WORK * wk )
{
	u8	sel = PokeSelectItemUse( wk );

	if( sel == SEL_POKE || sel == SEL_TOUCH ){
		CATS_ObjectPaletteSet( wk->act_work[PLIST_ACT_CURSOR1], 1 );
		if( wk->panel[wk->pos].egg != 1 ){
//			CATS_ObjectPaletteSet( wk->act_work[PLIST_ACT_CURSOR1], 1 );
			return PokeList_WazaOboeInit( wk );
		}else{
			PokeListLargeMsgPut( wk, PL_MSG_COMP_EXPAND, 1 );
			wk->dat->ret_mode = PL_RET_NORMAL;
			wk->next_seq = SEQ_ENDTRG_WAIT;
			MSGMAN_GetString( wk->msg_man, mes_pokelist_04_45, wk->msg_buf );
			return SEQ_MSG_WAIT;
		}
	}else if( sel == SEL_CANCEL ){
		wk->dat->ret_mode = PL_RET_NORMAL;
		return SEQ_OUT_SET;
	}
	return SEQ_WAZASET_SEL;
}



//--------------------------------------------------------------------------------------------
/**
 * プロセス関数：終了
 *
 * @param	proc	プロセスデータ
 * @param	seq		シーケンス
 *
 * @return	処理状況
 */
//--------------------------------------------------------------------------------------------
static PROC_RESULT PokeListProc_End( PROC * proc, int * seq )
{
	PLIST_WORK * wk  = PROC_GetWork( proc );
	u32	i;

//	TCB_Delete( wk->vtask );
	sys_VBlankFuncChange( NULL, NULL );		// VBlankセット

	PokeListCellActRerease( wk );	// セルアクター削除

	PokeListBmpWinExit( wk );			// BMPウィンドウ開放
	PokeListBgExit( wk->bgl );			// BGL削除
	StopTP();							// タッチパネル終了
	DellVramTransferManager();

	// ニックネーム文字列領域解放
	for( i=0; i<6; i++ ){
		STRBUF_Delete( wk->panel[i].name );
	}

	// メッセージ展開領域解放
	STRBUF_Delete( wk->msg_buf );
	STRBUF_Delete( wk->str_buf );

	// メニュー文字列展開領域解放
	for( i=0; i<MENU_STR_MAX; i++ ){
		STRBUF_Delete( wk->menu_str[i] );
	}

	MSGMAN_Delete( wk->msg_man );
	NUMFONT_Delete( wk->num_font );
	WORDSET_Delete( wk->wset );

	// レギュレーション図鑑データ解放
	if( wk->zkn != NULL ){
		PokeRegulationEnd( wk->zkn );
	}

	PROC_FreeWork( proc );				// ワーク開放

	sys_DeleteHeap( HEAPID_POKELIST );

	return PROC_RES_FINISH;
}

//--------------------------------------------------------------------------------------------
/**
 * VBlank関数
 *
 * @param	none
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
/*
static void PokeListVBlank( TCB_PTR tcb, void * work )
{
	PLIST_WORK * wk = work;

	if( wk->vblank_func != NULL ){
		wk->vblank_func( work );
	}

	GF_BGL_VBlankFunc( wk->bgl );

	CATS_Draw( wk->crp );

	// セルアクター
	DoVramTransferManager();	// Vram転送マネージャー実行
	CATS_RenderOamTrans();
	
	OS_SetIrqCheckFlag( OS_IE_V_BLANK );
}
*/

static void PokeListVBlank( void * work )
{
	PLIST_WORK * wk = work;

	GF_BGL_VBlankFunc( wk->bgl );

	// セルアクター
	DoVramTransferManager();	// Vram転送マネージャー実行
	CATS_RenderOamTrans();
	
	OS_SetIrqCheckFlag( OS_IE_V_BLANK );
}



//--------------------------------------------------------------------------------------------
/**
 * VRAM設定
 *
 * @param	none
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void PokeListVramBankSet(void)
{
	GF_BGL_DISPVRAM tbl = {
		GX_VRAM_BG_128_A,				// メイン2DエンジンのBG
		GX_VRAM_BGEXTPLTT_NONE,			// メイン2DエンジンのBG拡張パレット

		GX_VRAM_SUB_BG_128_C,			// サブ2DエンジンのBG
		GX_VRAM_SUB_BGEXTPLTT_NONE,		// サブ2DエンジンのBG拡張パレット

		GX_VRAM_OBJ_128_B,				// メイン2DエンジンのOBJ
		GX_VRAM_OBJEXTPLTT_NONE,		// メイン2DエンジンのOBJ拡張パレット

		GX_VRAM_SUB_OBJ_16_I,			// サブ2DエンジンのOBJ
		GX_VRAM_SUB_OBJEXTPLTT_NONE,	// サブ2DエンジンのOBJ拡張パレット

		GX_VRAM_TEX_NONE,				// テクスチャイメージスロット
		GX_VRAM_TEXPLTT_NONE			// テクスチャパレットスロット
	};
	GF_Disp_SetBank( &tbl );
}

//--------------------------------------------------------------------------------------------
/**
 * BG設定
 *
 * @param	ini		BGLデータ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void PokeListBgSet( GF_BGL_INI * ini )
{
	{	// BG SYSTEM
		GF_BGL_SYS_HEADER BGsys_data = {
			GX_DISPMODE_GRAPHICS, GX_BGMODE_0, GX_BGMODE_0, GX_BG0_AS_2D,
		};
		GF_BGL_InitBG( &BGsys_data );
	}

	{	// WINDOW (BMP)
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf800, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
			0, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME0_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( ini, GF_BGL_FRAME0_M );
	}

	{	// PARAM FONT (BMP)
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf000, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
			1, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME1_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( ini, GF_BGL_FRAME1_M );
	}

	{	// PLATE (CHAR)
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xe800, GX_BG_CHARBASE_0x10000, GX_BG_EXTPLTT_01,
			2, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME2_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( ini, GF_BGL_FRAME2_M );
	}

	{	// BG (CHAR)
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xe000, GX_BG_CHARBASE_0x10000, GX_BG_EXTPLTT_01,
			3, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME3_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
	}

	{	// BUTTON (CHAR)
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf800, GX_BG_CHARBASE_0x10000, GX_BG_EXTPLTT_01,
			0, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME0_S, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( ini, GF_BGL_FRAME0_S );
	}

	{	// BG (CHAR)
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf000, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
			1, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME1_S, &TextBgCntDat, GF_BGL_MODE_TEXT );
	}

	GF_BGL_ClearCharSet( GF_BGL_FRAME0_M, 32, 0, HEAPID_POKELIST );
	GF_BGL_ClearCharSet( GF_BGL_FRAME0_S, 32, 0, HEAPID_POKELIST );
}

//--------------------------------------------------------------------------------------------
/**
 * BG解放
 *
 * @param	ini		BGLデータ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void PokeListBgExit( GF_BGL_INI * ini )
{
	GF_Disp_GX_VisibleControl(
		GX_PLANEMASK_BG0 | GX_PLANEMASK_BG1 | GX_PLANEMASK_BG2 |
		GX_PLANEMASK_BG3 | GX_PLANEMASK_OBJ, VISIBLE_OFF );
	GF_Disp_GXS_VisibleControl(
		GX_PLANEMASK_BG0 | GX_PLANEMASK_BG1 | GX_PLANEMASK_OBJ, VISIBLE_OFF );

	GF_BGL_BGControlExit( ini, GF_BGL_FRAME1_S );
	GF_BGL_BGControlExit( ini, GF_BGL_FRAME0_S );
	GF_BGL_BGControlExit( ini, GF_BGL_FRAME3_M );
	GF_BGL_BGControlExit( ini, GF_BGL_FRAME2_M );
	GF_BGL_BGControlExit( ini, GF_BGL_FRAME1_M );
	GF_BGL_BGControlExit( ini, GF_BGL_FRAME0_M );

	sys_FreeMemory( HEAPID_POKELIST, ini );
}

//--------------------------------------------------------------------------------------------
/**
 * グラフィックデータセット
 *
 * @param	wk		ポケモンリスト画面のワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void PokeListBgGraphicSet( PLIST_WORK * wk )
{
	ArcUtil_BgCharSet(
		ARC_PLIST_GRA, NARC_plist_gra_p_list_NCGR,
		wk->bgl, GF_BGL_FRAME3_M, 0, 0, 0, HEAPID_POKELIST );
	ArcUtil_ScrnSet(
		ARC_PLIST_GRA, NARC_plist_gra_p_list_NSCR,
		wk->bgl, GF_BGL_FRAME3_M, 0, 0, 0, HEAPID_POKELIST );

	{
		NNSG2dPaletteData * pal;
		void * buf;
		u16 * cpy;
		
		buf = ArchiveDataLoadMalloc( ARC_PLIST_GRA, NARC_plist_gra_p_list_NCLR, HEAPID_POKELIST );
		NNS_G2dGetUnpackedPaletteData( buf, &pal );
		GF_BGL_PaletteSet( GF_BGL_FRAME3_M, (void *)pal->pRawData, pal->szByte, 0 );
		cpy = (u16 *)pal->pRawData;
		memcpy( wk->pal, &cpy[PAL_PANEL_0*16], 32*8 );
		sys_FreeMemory( HEAPID_POKELIST, buf );
	}

//	SystemFontPaletteLoad( PALTYPE_MAIN_BG, 0, HEAPID_POKELIST );
	TalkFontPaletteLoad( PALTYPE_MAIN_BG, PAL_TALK_FONT*32, HEAPID_POKELIST );

	// メニューウィンドウセット
	MenuWinGraphicSet(
		wk->bgl, GF_BGL_FRAME0_M, PL_MENU_WIN_CGX, PAL_MENU_WIN, 0, HEAPID_POKELIST );
	// 会話ウィンドウセット
	TalkWinGraphicSet(
		wk->bgl, GF_BGL_FRAME0_M,
		PL_TALK_WIN_CGX, PAL_TALK_WIN, CONFIG_GetWindowType(wk->dat->cfg), HEAPID_POKELIST );

	ArcUtil_BgCharSet(
		ARC_PLIST_GRA, NARC_plist_gra_list_but_NCGR,
		wk->bgl, GF_BGL_FRAME0_S, 0, 0, 0, HEAPID_POKELIST );
	ArcUtil_PalSet(
		ARC_PLIST_GRA, NARC_plist_gra_list_but_NCLR,
		PALTYPE_SUB_BG, 0x20, 0x20, HEAPID_POKELIST );

	ArcUtil_BgCharSet(
		ARC_PLIST_GRA, NARC_plist_gra_list_sub_NCGR,
		wk->bgl, GF_BGL_FRAME1_S, 0, 0, 0, HEAPID_POKELIST );
	ArcUtil_ScrnSet(
		ARC_PLIST_GRA, NARC_plist_gra_list_sub_NSCR,
		wk->bgl, GF_BGL_FRAME1_S, 0, 0, 0, HEAPID_POKELIST );
	ArcUtil_PalSet(
		ARC_PLIST_GRA, NARC_plist_gra_list_sub_NCLR,
		PALTYPE_SUB_BG, 0, 0x20, HEAPID_POKELIST );

	PoleList_PokePlateScreenGet(
		HEAPID_POKELIST, wk->plate_top, wk->plate_normal, wk->plate_none );

	GF_BGL_BackGroundColorSet( GF_BGL_FRAME0_M, 0 );
	GF_BGL_BackGroundColorSet( GF_BGL_FRAME0_S, 0 );
}

//--------------------------------------------------------------------------------------------
/**
 * ワーク初期化
 *
 * @param	wk
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static PLIST_WORK * PokeListWorkInit( PROC * proc )
{
	PLIST_WORK * wk;
	u32	i;

	wk = PROC_AllocWork( proc, sizeof(PLIST_WORK), HEAPID_POKELIST );
	memset( wk, 0, sizeof(PLIST_WORK) );

	wk->dat = PROC_GetParentWork( proc );
	wk->bgl = GF_BGL_BglIniAlloc( HEAPID_POKELIST );

	// レギュレーションで使用する図鑑データ取得
	if( wk->dat->mode == PL_MODE_SELECT && wk->dat->reg != NULL ){
		wk->zkn = PokeRegulationInit( HEAPID_POKELIST );
	}else{
		wk->zkn = NULL;
	}

//	wk->dat->mode = PL_MODE_CONTEST;
//	wk->dat->mode = PL_MODE_SET;
//	wk->dat->mode = PL_MODE_NPC_TRADE;
/*
	wk->dat->mode = PL_MODE_SELECT;
	wk->dat->in_num[0] = 0;
	wk->dat->in_num[1] = 0;
	wk->dat->in_num[2] = 0;
	wk->dat->in_num[3] = 0;
	wk->dat->in_num[4] = 0;
	wk->dat->in_num[5] = 0;
	wk->dat->in_min = 3;		// 参加最小数
	wk->dat->in_max = 3;		// 参加最大数
	wk->dat->in_lv = 100;		// 参加レベル
*/

	// メッセージマネージャ作成
	wk->msg_man = MSGMAN_Create(
					MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_pokelist_dat, HEAPID_POKELIST );
	// 8x8フォント作成
	wk->num_font = NUMFONT_Create( 15, 14, FBMP_COL_NULL, HEAPID_POKELIST );

	wk->wset = WORDSET_Create( HEAPID_POKELIST );

	// ニックネーム文字列領域作成
	for( i=0; i<6; i++ ){
		wk->panel[i].name = STRBUF_Create( MONS_NAME_SIZE+EOM_SIZE, HEAPID_POKELIST );
	}

	// メッセージ展開領域作成
	wk->msg_buf = STRBUF_Create( TMP_MSG_SIZE, HEAPID_POKELIST );
	wk->str_buf = STRBUF_Create( TMP_MSG_SIZE, HEAPID_POKELIST );

	// メニュー文字列展開領域作成
	for( i=0; i<MENU_STR_MAX; i++ ){
		wk->menu_str[i] = STRBUF_Create( MENU_STR_SIZE, HEAPID_POKELIST );
	}

	wk->pos = wk->dat->ret_sel;
	wk->old_pos = wk->pos;

	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * キャンセル設定
 *
 * @param	wk
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void CancelCheck( PLIST_WORK * wk )
{
	if( ( wk->dat->mode & PL_MODE_NO_CANCEL ) != 0 ){
		wk->cancel_flg = 1;
		wk->dat->mode ^= PL_MODE_NO_CANCEL;
	}else{
		wk->cancel_flg = 0;
	}
}

//--------------------------------------------------------------------------------------------
/**
 * モードごとの設定
 *
 * @param	wk
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void ListModeSet( PLIST_WORK * wk )
{
	u8	flg = 3;

	// カーソル移動テーブル設定
	if( wk->dat->type == PL_TYPE_MULTI ){
		wk->mv_tbl = MultiMoveTable;
	}else if( wk->dat->mode == PL_MODE_SELECT || wk->dat->mode == PL_MODE_BATTLE_TOWER ){
		wk->mv_tbl = SelectMoveTable;
	}else{
		wk->mv_tbl = NormalMoveTable;
	}

	// 「けってい」非表示
	if( wk->dat->mode != PL_MODE_SELECT && wk->dat->mode != PL_MODE_BATTLE_TOWER ){
		CLACT_SetDrawFlag( wk->act_work[PLIST_ACT_ENTER], 0 );
		CLACT_AnmChg( wk->act_work[PLIST_ACT_EXIT], 0 );
		{
			s16	x, y;

			CATS_ObjectPosGet( wk->act_work[PLIST_ACT_EXIT], &x, &y );
			CATS_ObjectPosSet( wk->act_work[PLIST_ACT_EXIT], x, y-8 );
		}
		flg ^= 1;
	}

	// 「もどる」非表示
	if( wk->dat->mode == PL_MODE_IN ){
		CLACT_SetDrawFlag( wk->act_work[PLIST_ACT_EXIT], 0 );
		flg ^= 2;
	}

	PokeListSelectMsgPut( wk, flg );
}

//---------------------------------------------------------------------------------------------
/**
 * ポケモンがいるかチェック
 *
 * @param	wk		ポケモンリストワーク
 * @param	pos		位置
 *
 * @retval	"TRUE = いる"
 * @retval	"FALSE = いない"
 */
//---------------------------------------------------------------------------------------------
u8 PokeListDataCheck( PLIST_WORK * wk, u8 pos )
{
	return wk->panel[pos].flg;
}

//---------------------------------------------------------------------------------------------
/**
 * ポケモンパラメータ取得
 *
 * @param	wk		ポケモンリストワーク
 *
 * @retval	"TRUE = いる"
 * @retval	"FALSE = いない"
 */
//---------------------------------------------------------------------------------------------
u8 PokeList_PanelPPDataMake( PLIST_WORK * wk, u8 pos )
{
	POKEMON_PARAM * pp;
	u32	prm;
	u16	mons;

	wk->panel[pos].flg = 0;

	if( PokeParty_GetPokeCount( wk->dat->pp ) <= pos ){
		return FALSE;
	}

	pp = PokeParty_GetMemberPointer( wk->dat->pp, pos );

	mons = (u16)PokeParaGet( pp, ID_PARA_monsno, NULL );
	if( mons == 0 ){ return FALSE; }

	PokeListNameMake( wk, pp, pos );

	wk->panel[pos].mons = mons;
	wk->panel[pos].hp   = (u16)PokeParaGet( pp, ID_PARA_hp, NULL );
	wk->panel[pos].mhp  = (u16)PokeParaGet( pp, ID_PARA_hpmax, NULL );
	wk->panel[pos].lv   = (u16)PokeParaGet( pp, ID_PARA_level, NULL );
	wk->panel[pos].item = (u16)PokeParaGet( pp, ID_PARA_item, NULL );
	wk->panel[pos].cb   = (u16)PokeParaGet( pp, ID_PARA_cb_id, NULL );
	wk->panel[pos].egg  = (u8)PokeParaGet( pp, ID_PARA_tamago_flag, NULL );
	wk->panel[pos].form = (u8)PokeParaGet( pp, ID_PARA_form_no, NULL );

	if( PokeParaGet( pp, ID_PARA_nidoran_nickname, NULL ) == TRUE ){
		wk->panel[pos].sex_put = 0;
	}else{
		wk->panel[pos].sex_put = 1;
	}
	wk->panel[pos].sex = PokeSexGet( pp );
	wk->panel[pos].flg = 1;

	wk->panel[pos].st = (u8)BadStatusIconAnmGet( pp );

	// コンテスト参加チェック
	PL_ContestEntryCheck( wk, pp, pos );

	return TRUE;
}


static void PL_ContestEntryCheck( PLIST_WORK * wk, POKEMON_PARAM * pp, u8 pos )
{
	u32	medal;
	u32	i;

	if( wk->dat->mode != PL_MODE_CONTEST ){ return; }

	if( wk->panel[pos].egg == 1 || wk->panel[pos].hp == 0 ){
		wk->panel[pos].contest = 0;
		return;
	}

	medal = PL_TrialMedalGet( pp, wk->dat->con_type );

	for( i=0; i<4; i++ ){
		if( PokeParaGet( pp, ID_PARA_waza1+i, NULL ) == 0 ){
			break;
		}
	}

	if( wk->dat->con_rank <= medal && i >= 2 ){
		wk->panel[pos].contest = 1;
	}else{
		wk->panel[pos].contest = 0;
	}
}

static u32 PL_TrialMedalGet( POKEMON_PARAM * pp, u8 type )
{
	u32	medal;

	switch( type ){
	case CONTYPE_STYLE:		// 格好よさ
		medal  = PokeParaGet( pp, ID_PARA_trial_stylemedal_normal, NULL );
		medal += PokeParaGet( pp, ID_PARA_trial_stylemedal_super, NULL );
		medal += PokeParaGet( pp, ID_PARA_trial_stylemedal_hyper, NULL );
		medal += PokeParaGet( pp, ID_PARA_trial_stylemedal_master, NULL );
		break;
	case CONTYPE_BEAUTIFUL:	// 美しさ
		medal  = PokeParaGet( pp, ID_PARA_trial_beautifulmedal_normal, NULL );
		medal += PokeParaGet( pp, ID_PARA_trial_beautifulmedal_super, NULL );
		medal += PokeParaGet( pp, ID_PARA_trial_beautifulmedal_hyper, NULL );
		medal += PokeParaGet( pp, ID_PARA_trial_beautifulmedal_master, NULL );
		break;
	case CONTYPE_CUTE:		// 可愛さ
		medal  = PokeParaGet( pp, ID_PARA_trial_cutemedal_normal, NULL );
		medal += PokeParaGet( pp, ID_PARA_trial_cutemedal_super, NULL );
		medal += PokeParaGet( pp, ID_PARA_trial_cutemedal_hyper, NULL );
		medal += PokeParaGet( pp, ID_PARA_trial_cutemedal_master, NULL );
		break;
	case CONTYPE_CLEVER:	// 賢さ
		medal  = PokeParaGet( pp, ID_PARA_trial_clevermedal_normal, NULL );
		medal += PokeParaGet( pp, ID_PARA_trial_clevermedal_super, NULL );
		medal += PokeParaGet( pp, ID_PARA_trial_clevermedal_hyper, NULL );
		medal += PokeParaGet( pp, ID_PARA_trial_clevermedal_master, NULL );
		break;
	case CONTYPE_STRONG:	// 逞しさ
		medal  = PokeParaGet( pp, ID_PARA_trial_strongmedal_normal, NULL );
		medal += PokeParaGet( pp, ID_PARA_trial_strongmedal_super, NULL );
		medal += PokeParaGet( pp, ID_PARA_trial_strongmedal_hyper, NULL );
		medal += PokeParaGet( pp, ID_PARA_trial_strongmedal_master, NULL );
	}
	return medal;
}




const u16 * PokeList_HPGageCharGet( PLIST_WORK * wk )
{
	return &wk->plate_normal[PL_PANEL_HPGAGE_PY*16+PL_PANEL_HPGAGE_PX];
}

static void PlateSet( PLIST_WORK * wk, u8 pos, u8 px, u8 py, u8 gage )
{
	const u16 * plate;

	if( pos == 0 || ( wk->dat->type != PL_TYPE_SINGLE && pos == 1 ) ){
		plate = wk->plate_top;
	}else{
		plate = wk->plate_normal;
	}

	wk->panel[pos].plate_px = (s8)px;
	wk->panel[pos].plate_py = (s8)py;

	GF_BGL_ScrWriteExpand(
		wk->bgl, GF_BGL_FRAME2_M, px, py, 16, 6, (const void *)plate, 0, 0, 16, 6 );

	if( gage == 0 ){
		GF_BGL_ScrFill(
			wk->bgl, GF_BGL_FRAME2_M, PL_PANEL_HPGAGE_CLEAR_CHR,
			px+PL_PANEL_HPGAGE_PX, py+PL_PANEL_HPGAGE_PY,
			PL_PANEL_HPGAGE_SX, PL_PANEL_HPGAGE_SY, GF_BGL_SCRWRT_PALNL );
	}

	GF_BGL_ScrPalChange(
		wk->bgl, GF_BGL_FRAME2_M, px, py, 16, 6, PAL_PANEL_0+pos );
	PokeListPanelPaletteSet( wk, pos );
}


static void PokePanelMakeNormal( PLIST_WORK * wk, const PANEL_POS * tbl );
static void PokePanelMakeShinkaOboe( PLIST_WORK * wk, const PANEL_POS * tbl );
static void PokePanelMakeWazaOboe( PLIST_WORK * wk, const PANEL_POS * tbl );
static void PokePanelMakeContest( PLIST_WORK * wk, const PANEL_POS * tbl );
static void PokePanelMakeBattleIn( PLIST_WORK * wk, const PANEL_POS * tbl );
static void DummyPanelSet( PLIST_WORK * wk, u8 pos, s16 px, s16 py );

static void PokePanelMake( PLIST_WORK * wk )
{
	const PANEL_POS * tbl;

	if( wk->dat->type == PL_TYPE_MULTI ){
		tbl = PanelPosTable[1];
	}else{
		tbl = PanelPosTable[0];
	}

	if( wk->dat->mode == PL_MODE_SHINKA ){
		PokePanelMakeShinkaOboe( wk, tbl );
	}else if( wk->dat->mode == PL_MODE_WAZASET ){
		PokePanelMakeWazaOboe( wk, tbl );
	}else if( wk->dat->mode == PL_MODE_CONTEST ){
		PokePanelMakeContest( wk, tbl );
	}else if( wk->dat->mode == PL_MODE_SELECT || wk->dat->mode == PL_MODE_BATTLE_TOWER ){
		PokePanelMakeBattleIn( wk, tbl );
	}else{
		PokePanelMakeNormal( wk, tbl );
	}

	GF_BGL_LoadScreenV_Req( wk->bgl, GF_BGL_FRAME2_M );
	GF_BGL_LoadScreenV_Req( wk->bgl, GF_BGL_FRAME0_S );
}

static void PokePanelMakeNormal( PLIST_WORK * wk, const PANEL_POS * tbl )
{
	u8	i;

	for( i=0; i<6; i++ ){
		if( PokeList_PanelPPDataMake( wk, i ) == TRUE ){
			if( wk->panel[i].egg == 1 ){
				PlateSet( wk, i, tbl[i].plate_px, tbl[i].plate_py, 0 );		// プレートセット
			}else{
				PlateSet( wk, i, tbl[i].plate_px, tbl[i].plate_py, 1 );		// プレートセット
			}
			PokeListParamPut( wk, i );										// パラメータ表示
			PokeListIconAdd( wk, i, tbl[i].icon_px, tbl[i].icon_py );		// アイコン表示
			PokeListBallActSet( wk, i, tbl[i].ball_px, tbl[i].ball_py );	// ボール
			PokeList_ItemIconChg( wk, i, wk->panel[i].item );				// アイテムアイコン
			PokeList_ItemIconPosSet(wk,i,tbl[i].icon_px,tbl[i].icon_py);	// アイテム移動
			PokeList_CustomIconChg( wk, i );
			PokeList_CustomIconPosSet( wk, i );
			PokeList_StatusIconChg( wk, i, wk->panel[i].st );				// 状態異常アイコン

			SubButtonScrnPut( wk, i, 0 );		// サブ画面のボタン

		}else{
			DummyPanelSet( wk, i, tbl[i].plate_px, tbl[i].plate_py );
		}
	}
}

static void PokePanelMakeShinkaOboe( PLIST_WORK * wk, const PANEL_POS * tbl )
{
	u8	i;

	for( i=0; i<6; i++ ){
		if( PokeList_PanelPPDataMake( wk, i ) == TRUE ){
			PlateSet( wk, i, tbl[i].plate_px, tbl[i].plate_py, 0 );			// プレートセット
			PokeList_PanelShinkaCommPut( wk, i );
			PokeListIconAdd( wk, i, tbl[i].icon_px, tbl[i].icon_py );		// アイコン表示
			PokeListBallActSet( wk, i, tbl[i].ball_px, tbl[i].ball_py );	// ボール
			PokeList_ItemIconChg( wk, i, wk->panel[i].item );				// アイテムアイコン
			PokeList_ItemIconPosSet(wk,i,tbl[i].icon_px,tbl[i].icon_py);	// アイテム移動
			PokeList_CustomIconChg( wk, i );
			PokeList_CustomIconPosSet( wk, i );
			PokeList_StatusIconChg( wk, i, wk->panel[i].st );				// 状態異常アイコン

			SubButtonScrnPut( wk, i, 0 );		// サブ画面のボタン

		}else{
			DummyPanelSet( wk, i, tbl[i].plate_px, tbl[i].plate_py );
		}
	}
}

static void PokePanelMakeWazaOboe( PLIST_WORK * wk, const PANEL_POS * tbl )
{
	u8	i;

	for( i=0; i<6; i++ ){
		if( PokeList_PanelPPDataMake( wk, i ) == TRUE ){
			PlateSet( wk, i, tbl[i].plate_px, tbl[i].plate_py, 0 );			// プレートセット
			PokeList_PanelWazaOboeCommPut( wk, i );
			PokeListIconAdd( wk, i, tbl[i].icon_px, tbl[i].icon_py );		// アイコン表示
			PokeListBallActSet( wk, i, tbl[i].ball_px, tbl[i].ball_py );	// ボール
			PokeList_ItemIconChg( wk, i, wk->panel[i].item );				// アイテムアイコン
			PokeList_ItemIconPosSet(wk,i,tbl[i].icon_px,tbl[i].icon_py);	// アイテム移動
			PokeList_CustomIconChg( wk, i );
			PokeList_CustomIconPosSet( wk, i );
			PokeList_StatusIconChg( wk, i, wk->panel[i].st );				// 状態異常アイコン

			SubButtonScrnPut( wk, i, 0 );		// サブ画面のボタン

		}else{
			DummyPanelSet( wk, i, tbl[i].plate_px, tbl[i].plate_py );
		}
	}
}

static void PokePanelMakeContest( PLIST_WORK * wk, const PANEL_POS * tbl )
{
	u8	i;

	for( i=0; i<6; i++ ){
		if( PokeList_PanelPPDataMake( wk, i ) == TRUE ){
			PlateSet( wk, i, tbl[i].plate_px, tbl[i].plate_py, 0 );			// プレートセット
			PokeList_PanelContestCommPut( wk, i );
			PokeListIconAdd( wk, i, tbl[i].icon_px, tbl[i].icon_py );		// アイコン表示
			PokeListBallActSet( wk, i, tbl[i].ball_px, tbl[i].ball_py );	// ボール
			PokeList_ItemIconChg( wk, i, wk->panel[i].item );				// アイテムアイコン
			PokeList_ItemIconPosSet(wk,i,tbl[i].icon_px,tbl[i].icon_py);	// アイテム移動
			PokeList_CustomIconChg( wk, i );
			PokeList_CustomIconPosSet( wk, i );
			PokeList_StatusIconChg( wk, i, wk->panel[i].st );				// 状態異常アイコン

			SubButtonScrnPut( wk, i, 0 );		// サブ画面のボタン

		}else{
			DummyPanelSet( wk, i, tbl[i].plate_px, tbl[i].plate_py );
		}
	}
}

static void PokePanelMakeBattleIn( PLIST_WORK * wk, const PANEL_POS * tbl )
{
	u8	i;

	for( i=0; i<6; i++ ){
		if( PokeList_PanelPPDataMake( wk, i ) == TRUE ){
			PlateSet( wk, i, tbl[i].plate_px, tbl[i].plate_py, 0 );			// プレートセット
			PokeList_PanelBattleInNamePut( wk, i );
			PokeList_PanelBattleInCommPut( wk, i );
			PokeListIconAdd( wk, i, tbl[i].icon_px, tbl[i].icon_py );		// アイコン表示
			PokeListBallActSet( wk, i, tbl[i].ball_px, tbl[i].ball_py );	// ボール
			PokeList_ItemIconChg( wk, i, wk->panel[i].item );				// アイテムアイコン
			PokeList_ItemIconPosSet(wk,i,tbl[i].icon_px,tbl[i].icon_py);	// アイテム移動
			PokeList_CustomIconChg( wk, i );
			PokeList_CustomIconPosSet( wk, i );
			PokeList_StatusIconChg( wk, i, wk->panel[i].st );				// 状態異常アイコン

			SubButtonScrnPut( wk, i, 0 );		// サブ画面のボタン

		}else{
			DummyPanelSet( wk, i, tbl[i].plate_px, tbl[i].plate_py );
		}
	}
}

static void DummyPanelSet( PLIST_WORK * wk, u8 pos, s16 px, s16 py )
{
	GF_BGL_ScrWriteExpand(
		wk->bgl, GF_BGL_FRAME2_M, px, py, 16, 6, (const void *)wk->plate_none, 0, 0, 16, 6 );
	GF_BGL_ScrPalChange( wk->bgl, GF_BGL_FRAME2_M, px, py, 16, 6, PAL_BG );
	PokeList_StatusIconChg( wk, pos, PL_ST_NONE );
	PokeList_ItemIconChg( wk, pos, 0 );
	PokeList_CustomIconChg( wk, pos );
}



void PokeListPanelPaletteSet( PLIST_WORK * wk, u8 num )
{
	POKEMON_PARAM * pp;
	u8	pal;

	pp = PokeParty_GetMemberPointer( wk->dat->pp, num );

	if( wk->chg_flg == 1 && ( num == wk->pos || num == wk->chg_pos ) ){
		pal = PANELTYPE_CHANGE + PANELTYPE_SELECT;
	}else{
		if( num == wk->pos ){
			pal = PANELTYPE_SELECT;
		}else{
			pal = 0;
		}
		if( PokeParaGet( pp, ID_PARA_hp, 0 ) == 0 ){
			pal += PANELTYPE_DETH;
		}else if( PokeMultiCheck( wk, num ) == TRUE ){
			pal += PANELTYPE_MULTI;
		}else{
			pal += PANELTYPE_NORMAL;
		}
	}

	GF_BGL_PaletteSet( GF_BGL_FRAME2_M, &wk->pal[pal*16], 8*2, (PAL_PANEL_0+num)*32 );
}



static u8 PokeMultiCheck( PLIST_WORK * wk, u8 num )
{
	if( wk->dat->type == PL_TYPE_MULTI && ( num & 1 ) != 0 ){
		return TRUE;
	}
	return FALSE;
}


static void InitCursorPosSet( PLIST_WORK * wk )
{
	u8	px, py;

	PointerWkMoveSel( wk->mv_tbl, &px, &py, NULL, NULL, wk->pos, POINT_MV_NULL );
	CLACT_AnmChg(
		wk->act_work[PLIST_ACT_CURSOR1],
		PokeListSelCursorCheck( wk->dat->type, wk->pos ) );
	CATS_ObjectPosSet( wk->act_work[PLIST_ACT_CURSOR1], px, py );
}

// 「けってい」「もどる」の位置の縦移動テーブル
static const u8 ExMvTbl[][6] =
{
	{ 0, 2, 4, 1, 3, 5 },	// KEY=DOWN, OLD=LEFT
	{ 1, 3, 5, 0, 2, 4 },	// KEY=DOWN, OLD=RIGHT
	{ 4, 2, 0, 5, 3, 1 },	// KEY=UP, OLD=LEFT
	{ 5, 3, 1, 4, 2, 0 }	// KEY=UP, OLD=RIGHT
};

static u8 PokemonSelect_Key( PLIST_WORK * wk );
static u8 PokeSelKey_Normal( PLIST_WORK * wk, u8 * px, u8 * py, u8 mv_type );
static u8 PokeSelKey_Ex( PLIST_WORK * wk, u8 * px, u8 * py, const u8 * tbl );
static u8 PokemonSelect_Touch( PLIST_WORK * wk );


static u8 PokemonSelect( PLIST_WORK * wk )
{
	if( PokemonSelect_Key( wk ) == TRUE ){
		return SEL_MOVE;
	}

	if( PokemonSelect_Touch( wk ) == TRUE ){
		return SEL_TOUCH;
	}

	return SEL_NONE;
}

static u8 PokemonSelect_Key( PLIST_WORK * wk )
{
	u8	mv_pos;
	u8	mv_type;
	u8	px, py;

	mv_type = POINT_MV_NULL;

	if( sys.repeat & PAD_KEY_UP ){
		mv_type = POINT_MV_UP;
	}else if( sys.repeat & PAD_KEY_DOWN ){
		mv_type = POINT_MV_DOWN;
	}else if( sys.repeat & PAD_KEY_LEFT ){
		mv_type = POINT_MV_LEFT;
	}else if( sys.repeat & PAD_KEY_RIGHT ){
		mv_type = POINT_MV_RIGHT;
	}

	if( mv_type == POINT_MV_NULL ){ return FALSE; }

	mv_pos = wk->pos;

	if( mv_pos == PL_SEL_POS_ENTER ){
		if( mv_type == POINT_MV_UP ){
			mv_pos = PokeSelKey_Ex( wk, &px, &py, ExMvTbl[2+(wk->old_pos&1)] );
		}else{
			mv_pos = PokeSelKey_Normal( wk, &px, &py, mv_type );
		}
	}else if( mv_pos == PL_SEL_POS_EXIT ){
		if( wk->dat->mode != PL_MODE_SELECT &&
			wk->dat->mode != PL_MODE_BATTLE_TOWER &&
			mv_type == POINT_MV_UP ){
			mv_pos = PokeSelKey_Ex( wk, &px, &py, ExMvTbl[2+(wk->old_pos&1)] );
		}else if( mv_type == POINT_MV_DOWN ){
			mv_pos = PokeSelKey_Ex( wk, &px, &py, ExMvTbl[(wk->old_pos&1)] );
		}else{
			mv_pos = PokeSelKey_Normal( wk, &px, &py, mv_type );
		}
	}else{
		mv_pos = PokeSelKey_Normal( wk, &px, &py, mv_type );
	}

	if( mv_pos != wk->pos && mv_pos != 0xff ){
		if( mv_pos == PL_SEL_POS_ENTER || mv_pos == PL_SEL_POS_EXIT ){
			CLACT_SetDrawFlag( wk->act_work[PLIST_ACT_CURSOR1], 0 );
		}else{
			CLACT_AnmChg(
				wk->act_work[PLIST_ACT_CURSOR1],
				PokeListSelCursorCheck( wk->dat->type, mv_pos ) );
			CLACT_SetDrawFlag( wk->act_work[PLIST_ACT_CURSOR1], 1 );
			CATS_ObjectPosSet( wk->act_work[PLIST_ACT_CURSOR1], px, py );
		}

		{
			u8	old_pos = wk->pos;

			wk->pos = mv_pos;
			PanelSelectChg( wk, old_pos, 0 );
			PanelSelectChg( wk, wk->pos, 1 );

			Snd_SePlay( PLIST_SE_CURSOR );

			// ボタン変更
			if( old_pos < PL_SEL_POS_ENTER ){
				SubButtonScrnPut( wk, old_pos, 0 );
				GF_BGL_LoadScreenV_Req( wk->bgl, GF_BGL_FRAME0_S );
			}

			if( old_pos != PL_SEL_POS_ENTER && old_pos != PL_SEL_POS_EXIT ){
				wk->old_pos = old_pos;
			}
		}

		return TRUE;
	}

	return FALSE;
}

static u8 PokeSelKey_Normal( PLIST_WORK * wk, u8 * px, u8 * py, u8 mv_type )
{
	u8	mv_pos = wk->pos;

	while(1){
		mv_pos = PointerWkMoveSel( wk->mv_tbl, px, py, NULL, NULL, mv_pos, mv_type );
		if( mv_pos == PL_SEL_POS_ENTER || mv_pos == PL_SEL_POS_EXIT || mv_pos == 0xff ){
			break;
		}
		if( PokeListDataCheck( wk, mv_pos ) != 0 ){
			break;
		}
	}
	return mv_pos;
}

static u8 PokeSelKey_Ex( PLIST_WORK * wk, u8 * px, u8 * py, const u8 * tbl )
{
	u8	cnt = 0;

	while( 1 ){
		if( cnt == 6 ){ break; }
		if( PokeListDataCheck( wk, tbl[cnt] ) != 0 ){
			PointerWkMoveSel( wk->mv_tbl, px, py, NULL, NULL, tbl[cnt], POINT_MV_NULL );
			return tbl[cnt];
		}
		cnt++;
	}

	PointerWkMoveSel( wk->mv_tbl, px, py, NULL, NULL, 0, POINT_MV_NULL );
	return 0;
}

static u8 PokemonSelect_Touch( PLIST_WORK * wk )
{
	int	ret = SubButtonCheck( wk );

	if( ret != RECT_HIT_NONE ){
		u8	px, py;
		u8	old_pos;

		old_pos = wk->pos;
		wk->pos = (u8)ret;

		PanelSelectChg( wk, old_pos, 0 );
		PanelSelectChg( wk, wk->pos, 1 );

		if( old_pos < PL_SEL_POS_ENTER ){
			SubButtonScrnPut( wk, old_pos, 0 );
		}
//		SubButtonScrnPut( wk, wk->pos, 1 );

		PointerWkMoveSel( wk->mv_tbl, &px, &py, NULL, NULL, wk->pos, POINT_MV_NULL );
		CLACT_AnmChg(
			wk->act_work[PLIST_ACT_CURSOR1],
			PokeListSelCursorCheck( wk->dat->type, wk->pos ) );
		CLACT_SetDrawFlag( wk->act_work[PLIST_ACT_CURSOR1], 1 );
		CATS_ObjectPosSet( wk->act_work[PLIST_ACT_CURSOR1], px, py );

//		GF_BGL_LoadScreenV_Req( wk->bgl, GF_BGL_FRAME0_S );

		wk->sub_button_seq = 1;
		wk->sub_button_pos = wk->pos;

		Snd_SePlay( PLIST_SE_TP_BALL );

		if( old_pos != PL_SEL_POS_ENTER && old_pos != PL_SEL_POS_EXIT ){
			wk->old_pos = old_pos;
		}

		return TRUE;
	}

	return FALSE;
}

void PokeList_CursorMoveAuto( PLIST_WORK * wk, u8 mv_pos )
{
	if( mv_pos == PL_SEL_POS_ENTER || mv_pos == PL_SEL_POS_EXIT ){
		CLACT_SetDrawFlag( wk->act_work[PLIST_ACT_CURSOR1], 0 );
	}else{
		u8	px, py;
		PointerWkMoveSel( wk->mv_tbl, &px, &py, NULL, NULL, wk->pos, POINT_MV_NULL );
		CLACT_AnmChg(
			wk->act_work[PLIST_ACT_CURSOR1],
			PokeListSelCursorCheck( wk->dat->type, mv_pos ) );
		CLACT_SetDrawFlag( wk->act_work[PLIST_ACT_CURSOR1], 1 );
		CATS_ObjectPosSet( wk->act_work[PLIST_ACT_CURSOR1], px, py );
	}

	{
		u8	old_pos = wk->pos;

		wk->pos = mv_pos;
		PanelSelectChg( wk, old_pos, 0 );
		PanelSelectChg( wk, wk->pos, 1 );

		// ボタン変更
		if( old_pos < PL_SEL_POS_ENTER ){
			SubButtonScrnPut( wk, old_pos, 0 );
			GF_BGL_LoadScreenV_Req( wk->bgl, GF_BGL_FRAME0_S );
		}
	}
}

static void PL_SubButtonAnm( PLIST_WORK * wk )
{
	switch( wk->sub_button_seq ){
	case 0:
		break;
	case 1:
//		if( wk->old_pos < PL_SEL_POS_ENTER ){
//			SubButtonScrnPut( wk, old_pos, 0 );
//		}
		{
			s16	x, y;
			SubButtonEffPosGet( wk->sub_button_pos, &x, &y );
			PokeListObj_SubButtonEffInit( wk, x, y );
		}
		SubButtonScrnPut( wk, wk->sub_button_pos, 2 );
		GF_BGL_LoadScreenV_Req( wk->bgl, GF_BGL_FRAME0_S );
		wk->sub_button_seq++;
		break;
	case 2:
		SubButtonScrnPut( wk, wk->sub_button_pos, 1 );
		GF_BGL_LoadScreenV_Req( wk->bgl, GF_BGL_FRAME0_S );
		wk->sub_button_seq = 0;
		break;
	}
}





static void PL_MenuPut( PLIST_WORK * wk );
static u8 FieldModeMenuMake( PLIST_WORK * wk, u8 * prm );
static u8 ContestModeMenuMake( PLIST_WORK * wk, u8 * prm );
static u8 BattleInModeMenuMake( PLIST_WORK * wk, u8 * prm );
static u8 KapselSetModeMenuMake( PLIST_WORK * wk, u8 * prm );
static u8 SodateyaModeMenuMake( PLIST_WORK * wk, u8 * prm );

static u8 PokeSelectMain( PLIST_WORK * wk )
{
	u8	ret;

	if( sys.trg & PAD_BUTTON_DECIDE ){
//		Snd_SePlay( PLIST_SE_ENTER );
		if( wk->pos == PL_SEL_POS_ENTER ){
			return SEL_ENTER;
		}else if( wk->pos == PL_SEL_POS_EXIT ){
			Snd_SePlay( PLIST_SE_ENTER );
			if( wk->cancel_flg == 0 ){
				return SEL_CANCEL;
			}
		}else if( wk->dat->mode == PL_MODE_SET || wk->dat->mode == PL_MODE_NPC_TRADE ){
			Snd_SePlay( PLIST_SE_ENTER );
			return SEL_POKE;
		}else if( wk->dat->mode == PL_MODE_PORUTO || wk->dat->mode == PL_MODE_MAILBOX ){
			if( wk->panel[wk->pos].egg == 0 ){
				Snd_SePlay( PLIST_SE_ENTER );
				return SEL_POKE;
			}else{
				Snd_SePlay( PLIST_SE_ERROR );
				return SEL_NONE;
			}
		}else if( wk->dat->mode == PL_MODE_KAPSEL_SET ){
			if( wk->panel[wk->pos].egg == 0 ){
				Snd_SePlay( PLIST_SE_ENTER );
				PL_MenuPut( wk );
				return SEL_POKE;
			}else{
				Snd_SePlay( PLIST_SE_ERROR );
				return SEL_NONE;
			}
		}else{
			Snd_SePlay( PLIST_SE_ENTER );
			PL_MenuPut( wk );
			return SEL_POKE;
		}
	}

	if( sys.trg & PAD_BUTTON_CANCEL ){
		if( wk->cancel_flg == 0 ){
			Snd_SePlay( PLIST_SE_CANCEL );
			wk->pos = PL_SEL_POS_EXIT;
			return SEL_CANCEL;
		}
	}

	ret = PokemonSelect( wk );
	if( ret == SEL_TOUCH ){
		if( wk->dat->mode == PL_MODE_PORUTO || wk->dat->mode == PL_MODE_MAILBOX ||
			wk->dat->mode == PL_MODE_KAPSEL_SET ){
			if( wk->panel[wk->pos].egg != 0 ){
				Snd_SePlay( PLIST_SE_ERROR );
				return SEL_NONE;
			}
		}
	}

	return ret;
}

static void PL_MenuPut( PLIST_WORK * wk )
{
	u8 * prm;
	u8	siz;

	BmpTalkWinClear( &wk->win[WIN_S_MSG], WINDOW_TRANS_OFF );
	prm = sys_AllocMemory( HEAPID_POKELIST, 8 );

	switch( wk->dat->mode ){
	case PL_MODE_FIELD:
		siz = FieldModeMenuMake( wk, prm );
		break;
	case PL_MODE_SELECT:
	case PL_MODE_BATTLE_TOWER:
		siz = BattleInModeMenuMake( wk, prm );
		break;
	case PL_MODE_KAPSEL_SET:
		siz = KapselSetModeMenuMake( wk, prm );
		break;
	case PL_MODE_SODATEYA:
		siz = SodateyaModeMenuMake( wk, prm );
		break;
	default:
		siz = ContestModeMenuMake( wk, prm );
	}

	PokeListMenuDataMake( wk, prm, siz );
	sys_FreeMemory( HEAPID_POKELIST, prm );

	PokeListMenuMsgMake( wk );
	PokeListMiddleMsgPut( wk, PL_MSG_COMP_EXPAND, 1 );

	CATS_ObjectPaletteSet( wk->act_work[PLIST_ACT_CURSOR1], 1 );
}

static u8 FieldModeMenuMake( PLIST_WORK * wk, u8 * prm )
{
	POKEMON_PARAM * pp = PokeParty_GetMemberPointer( wk->dat->pp, wk->pos );
	u16	waza;
	u8	h=0, i, j=0, mid;

	prm[j] = MENU_STATUS;
	j++;
	if( BtlTower_IsSalon(wk->dat->fsys) == FALSE ){
		if( wk->panel[wk->pos].egg == 0 ){
			for( i=0; i<4; i++ ){
				waza = (u16)PokeParaGet( pp, ID_PARA_waza1+i, NULL );
				if( waza == 0 ){ break; }
				mid = PokeList_WazaMenuIDGet( waza );

				if( mid != 0xff ){
					prm[j] = mid;
					j++;
					PokeList_WazaMenuStrGet( wk, waza, h );
					h++;
				}
			}
			prm[j] = MENU_ROW;
			j++;
			if( ItemMailCheck( wk->panel[wk->pos].item ) == TRUE ){
				prm[j] = MENU_MAIL;
			}else{
				prm[j] = MENU_ITEM;
			}
			j++;
		}else{
			prm[j] = MENU_ROW;
			j++;
		}
	}
	prm[j] = MENU_CANCEL;
	j++;

	return (j);
}

static u8 KapselSetModeMenuMake( PLIST_WORK * wk, u8 * prm )
{
	prm[0] = MENU_KAPSEL_SET;
	prm[1] = MENU_CANCEL;
	return 2;
}

static u8 SodateyaModeMenuMake( PLIST_WORK * wk, u8 * prm )
{
	if( wk->panel[wk->pos].egg == 0 ){
		prm[0] = MENU_AZUKERU;
		prm[1] = MENU_STATUS;
		prm[2] = MENU_CANCEL;
		return 3;
	}
	prm[0] = MENU_STATUS;
	prm[1] = MENU_CANCEL;
	return 2;
}

static u8 ContestModeMenuMake( PLIST_WORK * wk, u8 * prm )
{
	if( wk->panel[wk->pos].contest == 1 ){
		prm[0] = MENU_CONTEST_IN;
		prm[1] = MENU_STATUS;
		prm[2] = MENU_CANCEL;
		return 3;
	}

	prm[0] = MENU_STATUS;
	prm[1] = MENU_CANCEL;
	return 2;
}

static u8 BattleInModeMenuMake( PLIST_WORK * wk, u8 * prm )
{
	switch( PokeList_BattleInCheck( wk, wk->pos ) ){
	case 0:		// 参加できない
		prm[0] = MENU_STATUS;
		prm[1] = MENU_CANCEL;
		return 2;

	case 1:		// 参加可能
		prm[0] = MENU_BATTLE_IN;
		prm[1] = MENU_STATUS;
		prm[2] = MENU_CANCEL;
		return 3;

	case 2:		// 参加している
		prm[0] = MENU_OUT;
		prm[1] = MENU_STATUS;
		prm[2] = MENU_CANCEL;
		return 3;
	}
	return 0;
}

u8 PokeList_BattleInCheck( PLIST_WORK * wk, u8 num )
{
	u8	i;

	// レギュレーションチェック
	if( wk->dat->reg != NULL ){
		POKEMON_PARAM * pp = PokeParty_GetMemberPointer( wk->dat->pp, num );
		if( PokeRegulationCheckPokePara( wk->dat->reg, pp, wk->zkn ) == FALSE ){
			return 0;
		}
	}

	// バトルタワーチェック
	if( wk->dat->mode == PL_MODE_BATTLE_TOWER ){
		if( BattleTowerExPokeCheck_MonsNo( wk->panel[num].mons ) == TRUE ){
			return 0;
		}
	}

	// 参加している
	for( i=0; i<wk->dat->in_max; i++ ){
		if( wk->dat->in_num[i] == num+1 ){
			return 2;
		}
	}

	// タマゴ or 参加レベルオーバー
	if( wk->panel[num].egg == 1 || wk->panel[num].lv > wk->dat->in_lv ){
		return 0;
	}

	return 1;
}


static void PanelSelectChg( PLIST_WORK * wk, u8 pos, u8 flg )
{
	if( pos == 6 ){
		u8	anm = CLACT_AnmGet( wk->act_work[PLIST_ACT_ENTER] );
		if( flg == 0 ){
			anm = ( anm & 2 );
		}else{
			anm = ( anm & 2 ) + 1;
		}
		CLACT_AnmChg( wk->act_work[PLIST_ACT_ENTER], anm );
		return;
	}
	if( pos == 7 ){
		u8	anm = CLACT_AnmGet( wk->act_work[PLIST_ACT_EXIT] );
		if( flg == 0 ){
			anm = ( anm & 2 );
		}else{
			anm = ( anm & 2 ) + 1;
		}
		CLACT_AnmChg( wk->act_work[PLIST_ACT_EXIT], anm );
		return;
	}

	// 選択されていない状態にする
	if( flg == 0 ){
		// ポケモン座標変更
		wk->panel[pos].mons_px -= 2;
		wk->panel[pos].mons_py -= 2;
		// ボールアニメ変更
		CLACT_AnmChg( wk->act_work[PLIST_ACT_BALL1+pos], 0 );
	// 選択されている状態にする
	}else{
		// ポケモン座標変更
		wk->panel[pos].mons_px += 2;
		wk->panel[pos].mons_py += 2;
		// ボールアニメ変更
		CLACT_AnmChg( wk->act_work[PLIST_ACT_BALL1+pos], 1 );
	}

	// プレートパレット変更
	PokeListPanelPaletteSet( wk, pos );
}

u8 PokeListSelCursorCheck( u8 type, u8 pos )
{
	if( pos == 0 || ( type != PL_TYPE_SINGLE && pos == 1 ) ){
		return 1;
	}
	return 0;
}



static u8 PokeSelectRow( PLIST_WORK * wk )
{
	u8	ret;

	if( sys.trg & PAD_BUTTON_DECIDE ){
		Snd_SePlay( PLIST_SE_ENTER );
		if( wk->pos >= PL_SEL_POS_ENTER || wk->pos == wk->chg_pos ){
			PokeListRowCancel( wk );
			return SEL_CANCEL;
		}else{
			PokeListMenuRowMoveInit( wk );
			return SEL_POKE;
		}
	}

	if( sys.trg & PAD_BUTTON_CANCEL ){
		Snd_SePlay( PLIST_SE_CANCEL );
		PokeListRowCancel( wk );
		return SEL_CANCEL;
	}

	ret = PokemonSelect( wk );
	if( ret == SEL_TOUCH ){
		if( wk->pos == wk->chg_pos ){
			PokeListRowCancel( wk );
			return SEL_CANCEL;
		}else{
			PokeListMenuRowMoveInit( wk );
			return SEL_POKE;
		}
	}

	return ret;
}


static int PL_SelectEnter( PLIST_WORK * wk )
{
	u8	i;

	for( i=0; i<wk->dat->in_min; i++ ){
		if( wk->dat->in_num[i] == 0 ){
			switch( wk->dat->in_max ){
			case 2:
				PokeListLargeMsgPut( wk, mes_pokelist_04_47, 1 );
				break;
			case 3:
				PokeListLargeMsgPut( wk, mes_pokelist_04_60, 1 );
				break;
			case 4:
				PokeListLargeMsgPut( wk, mes_pokelist_04_61, 1 );
				break;
			case 5:
				PokeListLargeMsgPut( wk, mes_pokelist_04_61_01, 1 );
				break;
			case 6:
				PokeListLargeMsgPut( wk, mes_pokelist_04_61_02, 1 );
				break;
			default:
				PokeListLargeMsgPut( wk, mes_pokelist_02_01, 1 );
				break;
			}
			wk->next_seq = SEQ_BTLIN_ERR;
			Snd_SePlay( PLIST_SE_ERROR );
			return SEQ_MSG_WAIT;
		}
	}

	if( wk->dat->reg != NULL ){
		switch( PokeRegulationMatchFullPokeParty(wk->dat->reg,wk->dat->pp,wk->zkn,wk->dat->in_num) ){
		case POKE_REG_OK:				// 正常
			break;

		case POKE_REG_TOTAL_LV_FAILED:	// トータルのLVがオーバーしている
			{
				STRBUF * str;
				int	lv;

				str = MSGMAN_AllocString( wk->msg_man, mes_pokelist_07_03 );
				lv  = Regulation_GetParam( wk->dat->reg, REGULATION_TOTAL_LEVEL );

				WORDSET_RegisterNumber(
					wk->wset, 0, lv, 3, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
				WORDSET_ExpandStr( wk->wset, wk->msg_buf, str );
				STRBUF_Delete( str );
			}
			PokeListLargeMsgPut( wk, PL_MSG_COMP_EXPAND, 1 );
			wk->next_seq = SEQ_BTLIN_ERR;
			Snd_SePlay( PLIST_SE_ERROR );
			return SEQ_MSG_WAIT;

		case POKE_REG_BOTH_POKE:		// 同じポケモンがいる
			PokeListLargeMsgPut( wk, mes_pokelist_07_01, 1 );
			wk->next_seq = SEQ_BTLIN_ERR;
			Snd_SePlay( PLIST_SE_ERROR );
			return SEQ_MSG_WAIT;

		case POKE_REG_BOTH_ITEM:		// 同じアイテムがある
			PokeListLargeMsgPut( wk, mes_pokelist_07_02, 1 );
			wk->next_seq = SEQ_BTLIN_ERR;
			Snd_SePlay( PLIST_SE_ERROR );
			return SEQ_MSG_WAIT;
		}
	}

	// バトルタワー用処理
	if( wk->dat->mode == PL_MODE_BATTLE_TOWER ){
		switch( PL_BattleTowerEnterCheck(wk) ){
		case 0:		// 正常
			break;

		case 1:		// 同じポケモン
			PokeListLargeMsgPut( wk, mes_pokelist_07_01, 1 );
			wk->next_seq = SEQ_BTLIN_ERR;
			Snd_SePlay( PLIST_SE_ERROR );
			return SEQ_MSG_WAIT;

		case 2:		// 同じアイテム
			PokeListLargeMsgPut( wk, mes_pokelist_07_02, 1 );
			wk->next_seq = SEQ_BTLIN_ERR;
			Snd_SePlay( PLIST_SE_ERROR );
			return SEQ_MSG_WAIT;
		}
	}

	wk->dat->ret_mode = PL_RET_NORMAL;
	Snd_SePlay( PLIST_SE_ENTER );
	return SEQ_OUT_SET;
}

static u8 PL_BattleTowerEnterCheck( PLIST_WORK * wk )
{
	u8	i, j;

	for( i=0; i<5; i++ ){
		if( wk->dat->in_num[i] == 0 ){ break; }
		for( j=i+1; j<6; j++ ){
			if( wk->dat->in_num[j] == 0 ){ break; }
			if( wk->panel[wk->dat->in_num[i]-1].mons == wk->panel[wk->dat->in_num[j]-1].mons ){
				return 1;	// 同じポケモン
			}
			if( wk->panel[wk->dat->in_num[i]-1].item != 0 &&
				wk->panel[wk->dat->in_num[i]-1].item == wk->panel[wk->dat->in_num[j]-1].item ){
				return 2;	// 同じアイテム
			}
		}
	}
	return 0;
}


#define	SUB_BUTTON_CGX	( 5 )
#define	SUB_BUTTON_PAL	( 1 << 12 )
#define	SUB_BUTTON_SX	( 5 )
#define	SUB_BUTTON_SY	( 5 )


static const u8 SubButtonPosTbl[6][2] =
{
	{  1,  3 },
	{ 26,  3 },
	{  1, 10 },
	{ 26, 10 },
	{  1, 17 },
	{ 26, 17 },
};

static const RECT_HIT_TBL SubButtonRect[] =
{
	{  3*8,  8*8-1,  1*8,  6*8-1 },
	{  3*8,  8*8-1, 26*8, 31*8-1 },
	{ 10*8, 15*8-1,  1*8,  6*8-1 },
	{ 10*8, 15*8-1, 26*8, 31*8-1 },
	{ 17*8, 22*8-1,  1*8,  6*8-1 },
	{ 17*8, 22*8-1, 26*8, 31*8-1 },
	{ RECT_HIT_END, 0, 0, 0 }
};

static void SubButtonScrnPut( PLIST_WORK * wk, u8 pos, u8 anm )
{
	u16 * scrn;
	u16	pls;
	u8	px, py;
	u8	i, j;

	scrn = (u16 *)GF_BGL_ScreenAdrsGet( wk->bgl, GF_BGL_FRAME0_S );
	pls  = SUB_BUTTON_CGX + SUB_BUTTON_PAL + SUB_BUTTON_SX * SUB_BUTTON_SY * anm;
	px   = SubButtonPosTbl[pos][0];
	py   = SubButtonPosTbl[pos][1];

	for( i=0; i<SUB_BUTTON_SY; i++ ){
		for( j=0; j<SUB_BUTTON_SX; j++ ){
			scrn[ (py+i)*32 + px+j ] = i*SUB_BUTTON_SX + j + pls;
		}
	}
}

static void SubButtonEffPosGet( u8 pos, s16 * x, s16 * y )
{
	*x = SubButtonPosTbl[pos][0] * 8 + (( SUB_BUTTON_SX * 8 ) >> 1);
	*y = SubButtonPosTbl[pos][1] * 8 + (( SUB_BUTTON_SY * 8 ) >> 1);
}


//--------------------------------------------------------------------------------------------
/**
 * タッチパネルのボタン押し判定
 *
 * @param	wk		ポケモンリスト画面のワーク
 *
 * @retval	"RECT_HIT_NONE = 押されていない"
 * @retval	"RECT_HIT_NONE != 押したボタン番号"
 */
//--------------------------------------------------------------------------------------------
static int SubButtonCheck( PLIST_WORK * wk )
{
	int	ret;

	if( PL_TouchPanelCheck( wk ) == FALSE ){
		return RECT_HIT_NONE;
	}

	ret = GF_TP_RectHitTrg( SubButtonRect );

	if( ret != RECT_HIT_NONE ){
		u16	pat = 0xfffe;

		if( GF_BGL_DotCheck( wk->bgl, GF_BGL_FRAME0_S, sys.tp_x, sys.tp_y, &pat ) == FALSE ){
			return RECT_HIT_NONE;
		}
	}
	return ret;
}



//============================================================================================
//============================================================================================
//	メニュー
//============================================================================================
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * メニューコントロール
 *
 * @param	wk		バッグ画面のワーク
 *
 * @retval	"MENU_SEL_NONE = まだ選択されていない"
 * @retval	"MENU_SEL_CANCEL = キャンセル"
 * @retval	"MENU_SEL_NONE = "
 */
//--------------------------------------------------------------------------------------------
static u8 MenuControl( PLIST_WORK * wk, int * seq )
{
	u32	ret = BmpMenuMain( wk->mw );

	switch( ret ){
	case BMPMENU_NULL:
		break;

	case BMPMENU_CANCEL:
		BmpTalkWinClear( &wk->win[WIN_M_MSG], WINDOW_TRANS_OFF );
		PokeListMenuExit( wk );
		if( wk->dat->mode == PL_MODE_SELECT || wk->dat->mode == PL_MODE_BATTLE_TOWER ){
			PokeListSmallMsgPut( wk, mes_pokelist_02_06, 1 );
		}else{
			PokeListSmallMsgPut( wk, mes_pokelist_02_01, 1 );
		}
		CATS_ObjectPaletteSet( wk->act_work[PLIST_ACT_CURSOR1], 0 );
		return MENU_SEL_CANCEL;

	default:
		{
			pPLMenuFunc	func = (pPLMenuFunc)ret;
			func( wk, seq );
		}
	}

	return MENU_SEL_NONE;
}







u16 PokeList_WazaNumGet( u8 menu_id )
{
	return WazaTbl[menu_id-MENU_W_IAIGIRI];
}

u8	PokeList_WazaMenuIDGet( u16 waza )
{
	u8	i;

	for( i=0; i<NELEMS(WazaTbl); i++ ){
		if( waza == WazaTbl[i] ){
			return ( i+MENU_W_IAIGIRI );
		}
	}
	return 0xff;
}

/*
void PokeList_SkillUseFlagSet( PLIST_DATA * dat, u16 waza )
{
	dat->ex_skill |= (1<<PokeList_WazaMenuIDGet(waza) );
}
*/





static u8 MilknomiUseCheck( PLIST_WORK * wk );
static BOOL Milknomi_HPGageMove( PLIST_WORK * wk, u8 pos, s8 mv );

static int MainSeq_Milknomi( PLIST_WORK * wk )
{
	switch( wk->tmp[1] ){
	case 0:		// ポケモン選択
		if( sys.trg & PAD_BUTTON_DECIDE ){
			if( wk->pos >= PL_SEL_POS_ENTER ){
				Snd_SePlay( PLIST_SE_ENTER );
				PokeListRowCancel( wk );
				return SEQ_MAIN;
			}else{
				switch( MilknomiUseCheck( wk ) ){
				case 0:		// 成功
					Snd_SePlay( SEQ_SE_DP_KAIFUKU );
					CATS_ObjectPaletteSet( wk->act_work[PLIST_ACT_CURSOR1], 1 );
					if( wk->panel[wk->pos].mhp - wk->panel[wk->pos].hp < wk->tmp[0] ){
						wk->tmp[0] = wk->panel[wk->pos].mhp - wk->panel[wk->pos].hp;
					}
					wk->tmp[1] = 2;
					wk->tmp[2] = 0;
					break;

				case 1:		// 失敗
					Snd_SePlay( PLIST_SE_ENTER );
					wk->tmp[1] = 1;
					return SEQ_MSG_WAIT;

				case 2:		// タマゴ
					Snd_SePlay( PLIST_SE_ERROR );
					return SEQ_MILKNOMI;
				}
			}
		}
		if( sys.trg & PAD_BUTTON_CANCEL ){
			Snd_SePlay( PLIST_SE_CANCEL );
			PokeListRowCancel( wk );
			return SEQ_MAIN;
		}

		if( PokemonSelect( wk ) == SEL_TOUCH ){
			if( wk->pos == wk->chg_pos ){
				PokeListRowCancel( wk );
				return SEQ_MAIN;
			}else{
				switch( MilknomiUseCheck( wk ) ){
				case 0:		// 成功
					Snd_SePlay( SEQ_SE_DP_KAIFUKU );
					CATS_ObjectPaletteSet( wk->act_work[PLIST_ACT_CURSOR1], 1 );
					if( wk->panel[wk->pos].mhp - wk->panel[wk->pos].hp < wk->tmp[0] ){
						wk->tmp[0] = wk->panel[wk->pos].mhp - wk->panel[wk->pos].hp;
					}
					wk->tmp[1] = 2;
					wk->tmp[2] = 0;
					break;

				case 1:		// 失敗
					wk->tmp[1] = 1;
					return SEQ_MSG_WAIT;

				case 2:		// タマゴ
					Snd_SePlay( PLIST_SE_ERROR );
					return SEQ_MILKNOMI;
				}
			}
		}
		break;

	case 1:		// 使えない
		if( sys.trg & (PAD_BUTTON_DECIDE|PAD_BUTTON_CANCEL) ){
			Snd_SePlay( PLIST_SE_ENTER );
			BmpTalkWinClear( &wk->win[WIN_L_MSG], WINDOW_TRANS_OFF );
			CATS_ObjectPaletteSet( wk->act_work[PLIST_ACT_CURSOR1], 0 );
			PokeListSmallMsgPut( wk, mes_pokelist_02_08, 1 );
			wk->tmp[1] = 0;
		}
		break;

	case 2:		// HP Down
		if( Milknomi_HPGageMove( wk, wk->chg_pos, -1 ) == TRUE ){
			Snd_SePlay( SEQ_SE_DP_KAIFUKU );
			wk->tmp[1] = 3;
			wk->tmp[2] = 0;
		}
		break;

	case 3:		// HP Up
		if( Milknomi_HPGageMove( wk, wk->pos, 1 ) == TRUE ){
			POKEMON_PARAM * pp;
			STRBUF * str;
			void * buf;
			FIELDSYS_WORK * fsys;

			pp  = PokeParty_GetMemberPointer( wk->dat->pp, wk->pos );
			str = MSGMAN_AllocString( wk->msg_man, mes_pokelist_04_14 );
			WORDSET_RegisterPokeNickName( wk->wset, 0, PPPPointerGet(pp) );
			WORDSET_RegisterNumber(
				wk->wset, 1, wk->tmp[2], 3, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
			WORDSET_ExpandStr( wk->wset, wk->msg_buf, str );
			STRBUF_Delete( str );
			PokeListLargeMsgPut( wk, PL_MSG_COMP_EXPAND, 1 );

			buf  = FNOTE_ActionSkillDataMake( (u8)wk->tmp[3], 0, HEAPID_POKELIST );
			fsys = wk->dat->fsys;
			FNOTE_DataSave( fsys->fnote, buf, FNOTE_TYPE_ACTION );

			wk->tmp[1] = 4;
			wk->next_seq = SEQ_MILKNOMI;
			return SEQ_MSG_WAIT;
		}
		break;

	case 4:		// メッセージ表示
		if( sys.trg & (PAD_BUTTON_DECIDE|PAD_BUTTON_CANCEL) ){
			Snd_SePlay( PLIST_SE_ENTER );
			BmpTalkWinClear( &wk->win[WIN_L_MSG], WINDOW_TRANS_OFF );
			CATS_ObjectPaletteSet( wk->act_work[PLIST_ACT_CURSOR1], 0 );
			PokeListRowCancel( wk );
			return SEQ_MAIN;
		}
		break;
	}

	return SEQ_MILKNOMI;
}

static u8 MilknomiUseCheck( PLIST_WORK * wk )
{
	if( wk->panel[wk->pos].egg != 0 ){
		return 2;
	}
	if( wk->pos == wk->chg_pos ||
		wk->panel[wk->pos].hp == 0 ||
		wk->panel[wk->pos].hp == wk->panel[wk->pos].mhp ){

		CATS_ObjectPaletteSet( wk->act_work[PLIST_ACT_CURSOR1], 1 );
		PokeListLargeMsgPut( wk, mes_pokelist_04_68, 1 );
		wk->tmp[1] = 1;
		wk->next_seq = SEQ_MILKNOMI;
		return 1;
	}
	return 0;
}


static BOOL Milknomi_HPGageMove( PLIST_WORK * wk, u8 pos, s8 mv )
{
	wk->panel[pos].hp += mv;
	wk->tmp[2]++;

	PokeListHPClear( wk, pos );
	GF_BGL_BmpWinDataFill( &wk->win[WIN_POKE1_HPBAR+pos*5], 0 );

	PokeListHPPut( wk, pos );
	PokeListHPBerPut( wk, pos );

	if( wk->tmp[0] == wk->tmp[2] || wk->panel[pos].hp == wk->panel[pos].mhp ){
		POKEMON_PARAM * pp;
		u32	hp;
		pp = PokeParty_GetMemberPointer( wk->dat->pp, pos );
		hp = wk->panel[pos].hp;
		PokeParaPut( pp, ID_PARA_hp, &hp );
		return TRUE;
	}

	return FALSE;
}



//============================================================================================
//============================================================================================
//	アイテム使用
//============================================================================================
//============================================================================================
static u8 PokeSelectItemUse( PLIST_WORK * wk )
{
	u8	ret;

	if( sys.trg & PAD_BUTTON_DECIDE ){
		if( wk->pos == PL_SEL_POS_EXIT ){
			if( wk->cancel_flg == 0 ){
				Snd_SePlay( PLIST_SE_ENTER );
				return SEL_CANCEL;
			}
		}else{
			if( wk->panel[wk->pos].egg == 0 ){
				Snd_SePlay( PLIST_SE_ENTER );
				return SEL_POKE;
			}else{
				Snd_SePlay( PLIST_SE_ERROR );
			}
		}
		return SEL_NONE;
	}

	if( sys.trg & PAD_BUTTON_CANCEL ){
		if( wk->cancel_flg == 0 ){
			Snd_SePlay( PLIST_SE_CANCEL );
			wk->pos = PL_SEL_POS_EXIT;
			return SEL_CANCEL;
		}
		return SEL_NONE;
	}

//	return PokemonSelect( wk );
	ret = PokemonSelect( wk );
	if( ret == SEL_TOUCH ){
		if( wk->panel[wk->pos].egg != 0 ){
			Snd_SePlay( PLIST_SE_ERROR );
			return SEL_NONE;
		}
	}

	return ret;
}

static int ItemUseCheck( PLIST_WORK * wk )
{
	ITEMDATA * dat;

	dat = GetItemArcData( wk->dat->item, ITEM_GET_DATA, HEAPID_POKELIST );
	// PPアップ選択
	if( ItemBufParamGet( dat, ITEM_PRM_PP_UP ) !=0 ||
		ItemBufParamGet( dat, ITEM_PRM_PP_3UP )!=0 ){
		sys_FreeMemoryEz( dat );
		PokeList_WazaMenuInit( wk, 0 );
		return SEQ_WAZAMENU_SEL;
	}
	// PP回復選択
	if( ItemBufParamGet( dat, ITEM_PRM_PP_RCV ) != 0 &&
		ItemBufParamGet( dat, ITEM_PRM_ALL_PP_RCV ) == 0 ){
		sys_FreeMemoryEz( dat );
		PokeList_WazaMenuInit( wk, 1 );
		return SEQ_WAZAMENU_SEL;
	}
	sys_FreeMemoryEz( dat );

	if( PokeParty_StatusRecoverCheck(
			wk->dat->pp, wk->dat->item, wk->pos, 0, HEAPID_POKELIST ) == TRUE ){

		MyItem_SubItem( wk->dat->myitem, wk->dat->item, 1, HEAPID_POKELIST );

		if( ItemBufParamGet( dat, ITEM_PRM_EVOLUTION ) != 0 ){
			POKEMON_PARAM * pp = PokeParty_GetMemberPointer( wk->dat->pp, wk->pos );
			wk->dat->after_mons = PokeShinkaCheck(
				NULL, pp, ITEM_SHINKA_CHECK, wk->dat->item, &wk->dat->shinka_cond );
			wk->dat->ret_mode = PL_RET_ITEMSHINKA;
			return SEQ_OUT_SET;
		}

		if( ItemKanpouyakuCheck( wk->dat->item ) == TRUE && wk->dat->tvwk != NULL ){
			POKEMON_PARAM * pp = PokeParty_GetMemberPointer( wk->dat->pp, wk->pos );
			TVTOPIC_Entry_Watch_UseKanpo( wk->dat->tvwk, pp, wk->dat->item );
		}
		PokeList_ItemUseMain( wk );
	}else{
		PokeListLargeMsgPut( wk, mes_pokelist_04_45, 1 );
		wk->pos = PL_SEL_POS_EXIT;
		wk->strcv_func = PokeList_ItemUseMsgWait;
	}
	return SEQ_ITEMUSE_WAIT;
}


//============================================================================================
//============================================================================================
//	もたせる（バッグから）
//============================================================================================
//============================================================================================

// ポケモンの持ってるアイテム
enum {
	POKEITEM_NONE = 0,	// 何も持っていない
	POKEITEM_NORMAL,	// メール以外のアイテムを持っている
	POKEITEM_MAIL,		// メールを持っている
};

// アイテムを持たせられるかどうか
enum {
	ITEMSET_TRUE = 0,	// 持たせられる
	ITEMSET_FALSE		// バッグがいっぱいなのでムリ
};

//--------------------------------------------------------------------------------------------
/**
 * アイテムを持っているかどうか
 *
 * @param	wk		バッグ画面のワーク
 *
 * @retval	"POKEITEM_NONE = 何も持っていない"
 * @retval	"POKEITEM_NORMAL = メール以外のアイテムを持っている"
 * @retval	"POKEITEM_MAIL = メールを持っている"
 */
//--------------------------------------------------------------------------------------------
static u8 PokeItemCheck( PLIST_WORK * wk )
{
	if( wk->panel[wk->pos].item == 0 ){
		return POKEITEM_NONE;
	}else if( ItemMailCheck( wk->panel[wk->pos].item ) == TRUE ){
		return POKEITEM_MAIL;
	}
	return POKEITEM_NORMAL;
}

// 持たせる初期処理
static int PokeItemSetInit_Bag( PLIST_WORK * wk )
{
	POKEMON_PARAM * pp;
	GF_BGL_BMPWIN * win;
	int	ret;
	
	pp  = PokeParty_GetMemberPointer( wk->dat->pp, wk->pos );
	win = &wk->win[WIN_L_MSG];

	switch( PokeItemCheck( wk ) ){
	case POKEITEM_NONE:		// 何も持っていない
		// メールならメール画面へ飛ばす
		if( ItemMailCheck( wk->dat->item ) == TRUE ){
			wk->dat->ret_mode = PL_RET_MAILSET;
			return SEQ_OUT_SET;
		}
		PokeList_ItemSet( wk, pp );
		MSGMAN_GetString( wk->msg_man, mes_pokelist_04_59, wk->str_buf );
		WORDSET_RegisterPokeNickName( wk->wset, 0, PPPPointerGet(pp) );
		WORDSET_RegisterItemName( wk->wset, 1, wk->dat->item );
		WORDSET_ExpandStr( wk->wset, wk->msg_buf, wk->str_buf );
		ret = SEQ_ITEMSET_WAIT;
		break;

	case POKEITEM_NORMAL:	// メール以外のアイテムを持っている
		MSGMAN_GetString( wk->msg_man, mes_pokelist_04_28, wk->str_buf );
		WORDSET_RegisterPokeNickName( wk->wset, 0, PPPPointerGet(pp) );
		WORDSET_RegisterItemName( wk->wset, 1, wk->panel[wk->pos].item );
		WORDSET_ExpandStr( wk->wset, wk->msg_buf, wk->str_buf );
		ret = SEQ_ITEMSET_YN_INIT;
		break;

	case POKEITEM_MAIL:		// メールを持っている
		MSGMAN_GetString( wk->msg_man, mes_pokelist_04_27, wk->msg_buf );
		ret = SEQ_ITEMSET_WAIT;
		break;
	}

	BmpTalkWinWrite( win, WINDOW_TRANS_OFF, PL_TALK_WIN_CGX, PAL_TALK_WIN );
	GF_BGL_BmpWinDataFill( win, FBMP_COL_WHITE );
	PokeList_TalkMsgStart( wk );
	return ret;
}

static void PokeList_ItemSet( PLIST_WORK * wk, POKEMON_PARAM * pp )
{
	u32	item = wk->dat->item;

	MyItem_SubItem( wk->dat->myitem, wk->dat->item, 1, HEAPID_POKELIST );
	PokeParaPut( pp, ID_PARA_item, &item );
	PokeParaAusuFormChange( pp );

	wk->panel[wk->pos].item = wk->dat->item;
	PokeList_ItemIconChg( wk, wk->pos, wk->panel[wk->pos].item );
}

static void PokeList_ItemSetReturn( PLIST_WORK * wk, POKEMON_PARAM * pp, u32 set, u32 get )
{
	MyItem_AddItem( wk->dat->myitem, (u16)set, 1, HEAPID_POKELIST );
	PokeParaPut( pp, ID_PARA_item, &get );
	PokeParaAusuFormChange( pp );

	wk->panel[wk->pos].item = (u16)get;
	PokeList_ItemIconChg( wk, wk->pos, wk->panel[wk->pos].item );
}


static int PokeItemSetWait_Bag( PLIST_WORK * wk )
{
	if( GF_MSG_PrintEndCheck( wk->msg_index ) == 0 ){
		if( sys.trg & (PAD_BUTTON_DECIDE|PAD_BUTTON_CANCEL) ){
			return PokeItemEndCheck( wk );
		}
	}
	return SEQ_ITEMSET_WAIT;
}

static int PokeItemSetYesNoInit_Bag( PLIST_WORK * wk )
{
	if( GF_MSG_PrintEndCheck( wk->msg_index ) == 0 ){
		PokeList_YesNoSelectInit( wk );
		return SEQ_ITEMSET_YN_MAIN;
	}
	return SEQ_ITEMSET_YN_INIT;
}

static int PokeItemSetYesNoMain_Bag( PLIST_WORK * wk )
{
	switch( BmpYesNoSelectMain( wk->mw, HEAPID_POKELIST ) ){
	case 0:
		{
			POKEMON_PARAM * pp;
			GF_BGL_BMPWIN * win;
			u32	set_item;
			u32	get_item;

			pp  = PokeParty_GetMemberPointer( wk->dat->pp, wk->pos );
			win = &wk->win[WIN_L_MSG];

			set_item = wk->dat->item;			// 持たせるアイテム
			get_item = wk->panel[wk->pos].item;	// 持っているアイテム

			PokeList_ItemSet( wk, pp );
			if( MyItem_AddItem(wk->dat->myitem,(u16)get_item,1,HEAPID_POKELIST) == FALSE ){
//				MyItem_AddItem( wk->dat->myitem, (u16)set_item, 1, HEAPID_POKELIST );
//				PokeParaPut( pp, ID_PARA_item, &get_item );
				PokeList_ItemSetReturn( wk, pp, set_item, get_item );
				MSGMAN_GetString( wk->msg_man, mes_pokelist_04_31, wk->msg_buf );
			}else{
				// メールならメール画面へ飛ばす
				if( ItemMailCheck( wk->dat->item ) == TRUE ){
//					MyItem_AddItem( wk->dat->myitem, (u16)set_item, 1, HEAPID_POKELIST );
//					PokeParaPut( pp, ID_PARA_item, &get_item );
					MyItem_SubItem( wk->dat->myitem, (u16)get_item, 1, HEAPID_POKELIST );
					PokeList_ItemSetReturn( wk, pp, set_item, get_item );
					wk->dat->ret_mode = PL_RET_MAILSET;
					return SEQ_OUT_SET;
				}
				MSGMAN_GetString( wk->msg_man, mes_pokelist_04_32, wk->str_buf );
				WORDSET_RegisterItemName( wk->wset, 1, get_item );
				WORDSET_RegisterItemName( wk->wset, 2, set_item );
				WORDSET_ExpandStr( wk->wset, wk->msg_buf, wk->str_buf );
			}
			GF_BGL_BmpWinDataFill( win, FBMP_COL_WHITE );
			PokeList_TalkMsgStart( wk );
		}
		return SEQ_ITEMSET_WAIT;

	case BMPMENU_CANCEL:
		return PokeItemEndCheck( wk );
	}
	return SEQ_ITEMSET_YN_MAIN;
}

static int PokeItemEndCheck( PLIST_WORK * wk )
{
	if( wk->dat->mode == PL_MODE_ITEMSET_RET ){
		BmpTalkWinClear( &wk->win[WIN_L_MSG], WINDOW_TRANS_OFF );
		PokeListSmallMsgPut( wk, mes_pokelist_02_01, 1 );
		CATS_ObjectPaletteSet( wk->act_work[PLIST_ACT_CURSOR1], 0 );
		wk->dat->mode = PL_MODE_FIELD;
		return SEQ_MAIN;
	}
	wk->dat->ret_mode = PL_RET_BAG;
	return SEQ_OUT_SET;
}




static int PL_MailSetEnd( PLIST_WORK * wk )
{
	POKEMON_PARAM * pp;
	GF_BGL_BMPWIN * win;
	u32	set_item;
	u32	get_item;

	pp  = PokeParty_GetMemberPointer( wk->dat->pp, wk->pos );
	win = &wk->win[WIN_L_MSG];

	set_item = wk->dat->item;
	get_item = wk->panel[wk->pos].item;

	PokeList_ItemSet( wk, pp );
	if( get_item == 0 ){
		MSGMAN_GetString( wk->msg_man, mes_pokelist_04_59, wk->str_buf );
		WORDSET_RegisterPokeNickName( wk->wset, 0, PPPPointerGet(pp) );
		WORDSET_RegisterItemName( wk->wset, 1, wk->dat->item );
		WORDSET_ExpandStr( wk->wset, wk->msg_buf, wk->str_buf );
	}else{
		MyItem_AddItem( wk->dat->myitem, (u16)get_item, 1, HEAPID_POKELIST );
		MSGMAN_GetString( wk->msg_man, mes_pokelist_04_32, wk->str_buf );
		WORDSET_RegisterItemName( wk->wset, 1, get_item );
		WORDSET_RegisterItemName( wk->wset, 2, set_item );
		WORDSET_ExpandStr( wk->wset, wk->msg_buf, wk->str_buf );
	}
	BmpTalkWinWrite( win, WINDOW_TRANS_OFF, PL_TALK_WIN_CGX, PAL_TALK_WIN );
	GF_BGL_BmpWinDataFill( win, FBMP_COL_WHITE );
	PokeList_TalkMsgStart( wk );

	if( wk->dat->mode == PL_MODE_MAILSET_BAG ){
		wk->dat->mode = PL_MODE_ITEMSET_RET;
	}
	return SEQ_ITEMSET_WAIT;
}



//--------------------------------------------------------------------------------------------
/**
 * ゲーム内交換のカプセルチェック
 *
 * @param	none
 *
 * @return	キャラのアーカイブインデックス
 */
//--------------------------------------------------------------------------------------------
static int PokeList_KapselGetCheck( PLIST_WORK * wk )
{
	// カプセルを持っていない
	if( wk->panel[wk->pos].cb == 0 ){
		wk->dat->ret_mode = PL_RET_NORMAL;
		return SEQ_OUT_SET;
	}

	CATS_ObjectPaletteSet( wk->act_work[PLIST_ACT_CURSOR1], 1 );
	PokeListLargeMsgPut( wk, mes_pokelist_08_11, 1 );
	wk->yesno.yes = PL_KapselGetYes;
	wk->yesno.no  = PL_KapselGetNo;
	wk->next_seq = SEQ_YESNO_INIT;
	return SEQ_MSG_WAIT;
}


//--------------------------------------------------------------------------------------------
/**
 * タッチパネル有効モードチェック
 *
 * @param	wk		リストワーク
 *
 * @retval	"TRUE = 有効"
 * @retval	"FALSE = 無効"
 */
//--------------------------------------------------------------------------------------------
static BOOL PL_TouchPanelCheck( PLIST_WORK * wk )
{
	if( wk->dat->mode == PL_MODE_ITEMUSE || wk->dat->mode == PL_MODE_WAZASET ||
		wk->dat->mode == PL_MODE_WAZASET_RET || wk->dat->mode == PL_MODE_LVUPWAZASET_RET ||
		wk->dat->mode == PL_MODE_ITEMSET || wk->dat->mode == PL_MODE_MAILSET ||
		wk->dat->mode == PL_MODE_MAILBOX || wk->dat->mode == PL_MODE_SHINKA ||
		wk->dat->mode == PL_MODE_PORUTO ){
		return FALSE;
	}
	return TRUE;
}


//--------------------------------------------------------------------------------------------
/**
 * アイテムアイコンのキャラのアーカイブインデックス取得
 *
 * @param	none
 *
 * @return	キャラのアーカイブインデックス
 */
//--------------------------------------------------------------------------------------------
u32 Pokelist_ItemIconCgxArcGet(void)
{
	return NARC_plist_gra_item_icon_NCGR;
}

//--------------------------------------------------------------------------------------------
/**
 * アイテムアイコンのパレットのアーカイブインデックス取得
 *
 * @param	none
 *
 * @return	パレットのアーカイブインデックス
 */
//--------------------------------------------------------------------------------------------
u32 Pokelist_ItemIconPalArcGet(void)
{
	return NARC_plist_gra_item_icon_NCLR;
}

//--------------------------------------------------------------------------------------------
/**
 * アイテムアイコンのセルのアーカイブインデックス取得
 *
 * @param	none
 *
 * @return	セルのアーカイブインデックス
 */
//--------------------------------------------------------------------------------------------
u32 Pokelist_ItemIconCellArcGet(void)
{
	return NARC_plist_gra_item_icon_NCER;
}

//--------------------------------------------------------------------------------------------
/**
 * アイテムアイコンのセルアニメのアーカイブインデックス取得
 *
 * @param	none
 *
 * @return	セルアニメのアーカイブインデックス
 */
//--------------------------------------------------------------------------------------------
u32 Pokelist_ItemIconCAnmArcGet(void)
{
	return NARC_plist_gra_item_icon_NANR;
}


#define	PANEL_SCREEN_POS_TOP		( 0 )
#define	PANEL_SCREEN_POS_NORMAL		( PL_PANEL_SY )
#define	PANEL_SCREEN_POS_NONE		( PANEL_SCREEN_POS_NORMAL + PL_PANEL_SY )

void PoleList_PokePlateScreenGet( u32 heap, u16 * top, u16 * normal, u16 * none )
{
	NNSG2dScreenData * dat;
	void * buf;
	u16 * screen;
	u32	i;
		
	buf = ArchiveDataLoadMalloc(
				ARC_PLIST_GRA, NARC_plist_gra_list_plate_NSCR, heap );
	NNS_G2dGetUnpackedScreenData( buf, &dat );
	screen = (u16 *)dat->rawData;

	for( i=0; i<PL_PANEL_SY; i++ ){
		memcpy( &top[i*PL_PANEL_SX], &screen[(PANEL_SCREEN_POS_TOP+i)*32], PL_PANEL_SX*2 );
		memcpy( &normal[i*PL_PANEL_SX], &screen[(PANEL_SCREEN_POS_NORMAL+i)*32], PL_PANEL_SX*2 );
		memcpy( &none[i*PL_PANEL_SX], &screen[(PANEL_SCREEN_POS_NONE+i)*32], PL_PANEL_SX*2 );
	}

	sys_FreeMemoryEz( buf );
}

