//============================================================================================
/**
 * @file	fld_menu.c
 * @brief	フィールドメニュー処理
 * @author	Hiroyuki Nakamura
 * @date	2004.11.05
 */
//============================================================================================
#include "common.h"
#include "system/procsys.h"
#include "system/bmp_menu.h"
#include "system/fontproc.h"
#include "system/window.h"
#include "system/snd_tool.h"
#include "system/clact_tool.h"
#include "system/menu_gra.naix"
#include "system/wipe.h"
#include "poketool/pokeparty.h"
#include "poketool/poke_number.h"
#include "itemtool/item.h"
#include "application/bag.h"
#include "application/pokelist.h"
#include "application/p_status.h"
#include "application/trainer_card.h"
#include "application/nuts_tag.h"
#include "application/config_tool.h"
#include "application/mailtool.h"
#include "application/zukanlist/zkn_sys.h"
#include "application/townmap.h"
#include "application/nuts_tag.h"
#include "msgdata/msg.naix"
#include "msgdata/msg_fieldmenu.h"
#include "savedata/mystatus.h"
#include "savedata/config.h"
#include "savedata/sp_ribbon.h"
#include "savedata/trainercard_data.h"
#include "battle/shinka.h"
#include "field/field.h"
#include "fld_bgm.h"
#include "fld_bmp.h"
#include "fieldmap.h"
#include "fieldsys.h"
#include "field/field_skill.h"
#include "field_skill_local.h"
#include "field_clact.h"
#include "field_flysky.h"
#include "ev_mapchange.h"
#include "ev_time.h"
#include "syswork.h"
#include "sysflag.h"
#include "tr_card_setup.h"
#include "report.h"
#include "situation_local.h"
#include "pokepark_sys.h"
#include "b_tower_ev.h"
#include "zonedata.h"

#include "communication/communication.h"	// 簡易会話書き換えのために必要
#include "communication/comm_state.h"
#include "comm_union_beacon.h"				// 簡易会話書き換えのために必要
#include "field/comm_union_view_common.h"

#include "script.h"
#include "../fielddata/script/common_scr_def.h"		//SCRID_REPORT
#include "../fielddata/script/safari_def.h"
#include "../fielddata/script/d10r0101_def.h"

#include "field/itemuse.h"

#define FLD_MENU_H_GLOBAL
#include "fld_menu.h"


//============================================================================================
//	定数定義
//============================================================================================
enum {
	MENU_POS_ZUKAN = 0,
	MENU_POS_POKEMON,
	MENU_POS_BAG,
	MENU_POS_HERO,
	MENU_POS_REPORT,
	MENU_POS_CONFIG,
	MENU_POS_EXIT,
	MENU_POS_CHAT,
	MENU_POS_RETIRE,
};

// 技使用
typedef struct {
	u16	poke;	// ポケモン位置
	u16	waza;	// 技
}SKILL_USE;

// メール作成
typedef struct {
	u16	item;
	u8	pos;
	u8	mode;
}FM_MAIL_WORK;


#define	FLDMENU_CLA_CHR_RES_MAX		( 8 )	// セルアクターのキャラ数
#define	FLDMENU_CLA_PAL_RES_MAX		( 1 )	// セルアクターのパレット数
#define	FLDMENU_CLA_CEL_RES_MAX		( 2 )	// セルアクターのセル数
#define	FLDMENU_CLA_ANM_RES_MAX		( 2 )	// セルアクターのセルアニメ数

// セルアクターのキャラID
enum {
	FLDMENU_CLA_CHR_H_ID_CURSOR	= 13528,	// 選択カーソル
	FLDMENU_CLA_CHR_H_ID_ICON,				// アイコン
};
// セルアクターのパレットID
enum {
	FLDMENU_CLA_PAL_H_ID = 13528,			// 選択カーソル＆アイコン
};
// セルアクターのセルID
enum {
	FLDMENU_CLA_CEL_H_ID_CURSOR	= 13528,	// 選択カーソル
	FLDMENU_CLA_CEL_H_ID_ICON,				// アイコン
};
// セルアクターのセルアニメID
enum {
	FLDMENU_CLA_ANM_H_ID_CURSOR	= 13528,	// 選択カーソル
	FLDMENU_CLA_ANM_H_ID_ICON,				// アイコン
};

// アイコンID
enum {
	ICON_ZUKAN,		// 図鑑アイコン
	ICON_POKEMON,	// ポケモンリストアイコン
	ICON_BAG,		// バッグアイコン
	ICON_HERO,		// トレーナーカードアイコン
	ICON_REPORT,	// レポートアイコン
	ICON_CONFIG,	// 設定アイコン
	ICON_CLOSE,		// 閉じるアイコン
	ICON_CHAT,		// チャット
	ICON_RETIRE,	// リタイア
	ICON_BAG_F,		// バッグ（女）　← 一番下に置くこと
};

// セルアクター登録場所
#define	CLA_SET_CURSOR	( 0 )	// 選択カーソル
#define	CLA_SET_ICON	( 1 )	// アイコン

#define	CLA_CURSOR_PX	( 204 )		// 選択カーソル表示X座標
#define	CLA_CURSOR_PY	( 20 )		// 選択カーソル表示Y座標
#define	CLA_ICON_PX		( 174 )		// アイコン表示X座標
#define	CLA_ICON_PY		( 20 )		// アイコン表示Y座標
#define	CLA_ICON_SPC_Y	( 24 )		// アイコンのYスペース

// アイコンアニメID
enum {
	ICON_ANM_STOP = 0,	// 停止
	ICON_ANM_CHANGE,	// 選択された瞬間
	ICON_ANM_SELECT,	// 選択中
};

// 残りボールウィンドウ
#define	BALL_NAME_PX		( 0 )		// ボール名表示X
#define	BALL_NAME_PY		( 0 )		// ボール名表示Y
#define	BALL_VAL_PX			( 0 )		// ボール個数表示X
#define	BALL_VAL_PY			( 16 )		// ボール個数表示Y
#define	BALL_VAL_MSG_SIZ	( 32 )		// ボール個数展開文字数（適当）


//============================================================================================
//	プロトタイプ宣言
//============================================================================================
static FLD_MENU * MenuWorkAllocSet(void);
static u32 FieldMenuParamSet( FIELDSYS_WORK * repw );
static u32 FieldMenuParamSetSafari( FIELDSYS_WORK * repw );
static u32 FieldMenuParamSetPokePark( FIELDSYS_WORK * repw );
static u32 FieldMenuParamSetBtlTowerSalon( FIELDSYS_WORK * repw );
static u32 FieldMenuParamSetUnion( FIELDSYS_WORK * repw );
static u32 FieldMenuParamSetVS( FIELDSYS_WORK * repw );

static void CellActSet( FLD_MENU * wk, u8 * list, u32 max, u8 sex );
static void CellActDelete( FLD_MENU * wk );
static void CellActAnm( FLD_MENU * wk );
static void CursorMove( CLACT_WORK_PTR cwp, u32 cur_pos );
static void IconAnmChange( CLACT_WORK_PTR cwp, u16 anm, u16 pal );
static void MoveIconAnmChg( FLD_MENU * wk, u16 old_pos, u16 new_pos );
static void SelectIconAnmCheck( CLACT_WORK_PTR cwp );

static BOOL GMEVENT_FieldMenu(GMEVENT_CONTROL * event);
static void FieldMenuSet( GMEVENT_CONTROL * event );
static BOOL FieldMenuSelect( GMEVENT_CONTROL * event );
static u32 FieldMenuListMake( FLD_MENU * wk, u8 * list );
static void FieldMenuListExit( FLD_MENU * wk );
static void FldMenu_UnionBeaconChg( FLD_MENU * wk, FIELDSYS_WORK *fsys );
static void FieldBallWinSet( GMEVENT_CONTROL * event );
static void FieldBallWinExit( GMEVENT_CONTROL * event );

static void FldMenu_AppCall( GMEVENT_CONTROL * event );
static void FldMenu_AppWait( GMEVENT_CONTROL * event );

static BOOL FldMenu_ZukanInit( GMEVENT_CONTROL * event );
static BOOL FldMenu_ZukanCall( GMEVENT_CONTROL * event );
static BOOL FldMenu_ZukanEnd( GMEVENT_CONTROL * event );

static BOOL FldMenu_TrCardInit( GMEVENT_CONTROL * event );
static BOOL FldMenu_TrCardCall( GMEVENT_CONTROL * event );
static BOOL FldMenu_TrCardEnd( GMEVENT_CONTROL * event );

static BOOL FldMenu_ConfigInit( GMEVENT_CONTROL * event );
static BOOL FldMenu_ConfigCall( GMEVENT_CONTROL * event );
static BOOL FldMenu_ConfigEnd( GMEVENT_CONTROL * event );

static BOOL FldMenu_ChatInit( GMEVENT_CONTROL * event );
static BOOL FldMenu_ChatCall( GMEVENT_CONTROL * event );
static BOOL FldMenu_ChatEnd( GMEVENT_CONTROL * event );

static BOOL FldMenu_PokeListInit( GMEVENT_CONTROL * event );
static BOOL FldMenu_PokeListCall( GMEVENT_CONTROL * event );

static BOOL FldMenu_BagInit( GMEVENT_CONTROL * event );
static BOOL FldMenu_BagCall( GMEVENT_CONTROL * event );
static BOOL FldMenu_BagEnd( GMEVENT_CONTROL * event );

static BOOL FldMenu_ReportInit( GMEVENT_CONTROL * event );
static void FldMenu_ReportWait( GMEVENT_CONTROL * event );
static void FldMenu_ReportCall( GMEVENT_CONTROL * event );

static BOOL FldMenu_PokeStatusEnd( GMEVENT_CONTROL * event );

static void FldMenu_NutsTagCall( GMEVENT_CONTROL * event, u16 item );
static BOOL FldMenu_NutsTagEnd( GMEVENT_CONTROL * event );

BOOL FldMenu_SorawotobuEnd( GMEVENT_CONTROL * event );

static void FldMenu_ShinkaInit( GMEVENT_CONTROL * event );
static void FldMenu_ShinkaMain( GMEVENT_CONTROL * event );

static BOOL FldMenu_RetireInit( GMEVENT_CONTROL * event );


//============================================================================================
//	グローバル変数
//============================================================================================
static const u32 FldMenuData[][2] =
{
	{ msg_menu_00, (u32)FldMenu_ZukanInit },		// ずかん
	{ msg_menu_01, (u32)FldMenu_PokeListInit },		// ポケモン
	{ msg_menu_02, (u32)FldMenu_BagInit },			// バッグ
	{ msg_menu_03, (u32)FldMenu_TrCardInit },		// 主人公
	{ msg_menu_04, (u32)FldMenu_ReportInit },		// レポート
	{ msg_menu_05, (u32)FldMenu_ConfigInit },		// せってい
	{ msg_menu_06, (u32)BMPMENU_CANCEL },			// とじる
	{ msg_menu_07, (u32)FldMenu_ChatInit },			// チャット
	{ msg_menu_08, (u32)FldMenu_RetireInit },		// リタイア
};

// セルアクターデータ
static const TCATS_OBJECT_ADD_PARAM_S ActAddParam_S[] =
{
	{	// カーソル
		CLA_CURSOR_PX, CLA_CURSOR_PY, 0,
		0, 1, 1, NNS_G2D_VRAM_TYPE_2DMAIN,
		{
			FLDMENU_CLA_CHR_H_ID_CURSOR, FLDMENU_CLA_PAL_H_ID,
			FLDMENU_CLA_CEL_H_ID_CURSOR, FLDMENU_CLA_ANM_H_ID_CURSOR, 0, 0,
		},
		0, 0
	},
	{	// アイコン１
		CLA_ICON_PX, CLA_ICON_PY, 0,
		0, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN,
		{
			FLDMENU_CLA_CHR_H_ID_ICON, FLDMENU_CLA_PAL_H_ID,
			FLDMENU_CLA_CEL_H_ID_ICON, FLDMENU_CLA_ANM_H_ID_ICON, 0, 0,
		},
		0, 0
	},
};

// ポケモンリスト「もたせる」から呼ばれるバッグのデータ
static const u8 PokeList_ItemSetBagList[] = {
	BAG_POKE_NORMAL, BAG_POKE_DRUG, BAG_POKE_BALL, BAG_POKE_WAZA,
	BAG_POKE_NUTS, BAG_POKE_SEAL, BAG_POKE_BATTLE, BAG_POKE_EVENT, 0xff
};

// 通常のステータス画面ページ
const u8 PST_PageTbl_Normal[] = {
	PST_PAGE_INFO,			// 「ポケモンじょうほう」
	PST_PAGE_MEMO,			// 「トレーナーメモ」
	PST_PAGE_PARAM,			// 「ポケモンのうりょく」
	PST_PAGE_CONDITION,		// 「コンディション」
	PST_PAGE_B_SKILL,		// 「たたかうわざ」
	PST_PAGE_C_SKILL,		// 「コンテストわざ」
	PST_PAGE_RIBBON,		// 「きねんリボン」
	PST_PAGE_RET,			// 「もどる」
	PST_PAGE_MAX
};

// 技覚え用ステータス画面ページ
static const u8 PST_PageTbl_WazaSet[] = {
	PST_PAGE_B_SKILL,		// 「たたかうわざ」
	PST_PAGE_C_SKILL,		// 「コンテストわざ」
	PST_PAGE_MAX
};


//============================================================================================
//	呼び出し
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * フィールドメニュー起動処理（通常）
 *
 * @param	repw	フィールドワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void FieldMenuInit( FIELDSYS_WORK * repw )
{
	FLD_MENU * wk = MenuWorkAllocSet();

	if( SysFlag_SafariCheck( SaveData_GetEventWork(repw->savedata) ) == TRUE ){
		wk->ev_flg = FieldMenuParamSetSafari( repw );	// サファリ
	}else if( SysFlag_PokeParkCheck( SaveData_GetEventWork(repw->savedata) ) == TRUE ){
		wk->ev_flg = FieldMenuParamSetPokePark( repw );	// ポケパーク
	}else if( BtlTower_IsSalon(repw) == TRUE ){
		wk->ev_flg = FieldMenuParamSetBtlTowerSalon( repw );	// バトルタワーサロン
	}else{
		wk->ev_flg = FieldMenuParamSet( repw );			// 通常メニュー
	}
	wk->union_flg = FALSE;

	if( Player_MoveForceStopCheck( repw->player ) == TRUE ){
		Player_MoveForceStop( repw->player, Player_DirGet(repw->player) );
	}

	FieldEvent_Set(repw, GMEVENT_FieldMenu, wk);
}

//--------------------------------------------------------------------------------------------
/**
 * フィールドメニュー起動処理（ユニオンルーム用）
 *
 * @param	repw	フィールドワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void FieldMenuInitUnion( FIELDSYS_WORK * repw )
{
	FLD_MENU * wk = MenuWorkAllocSet();

	wk->ev_flg    = FieldMenuParamSetUnion( repw );
	wk->union_flg = TRUE;

	if( Player_MoveForceStopCheck( repw->player ) == TRUE ){
		Player_MoveForceStop( repw->player, Player_DirGet(repw->player) );
	}

	FieldEvent_Set(repw, GMEVENT_FieldMenu, wk);
}

//--------------------------------------------------------------------------------------------
/**
 * フィールドメニュー起動処理（対戦部屋用）
 *
 * @param	repw	フィールドワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void FieldMenuInitVS( FIELDSYS_WORK * repw )
{
	FLD_MENU * wk = MenuWorkAllocSet();

	wk->ev_flg    = FieldMenuParamSetVS( repw );
	wk->union_flg = FALSE;

	if( Player_MoveForceStopCheck( repw->player ) == TRUE ){
		Player_MoveForceStop( repw->player, Player_DirGet(repw->player) );
	}

	FieldEvent_Set(repw, GMEVENT_FieldMenu, wk);
}

//--------------------------------------------------------------------------------------------
/**
 * フィールドメニュー起動割り込み処理（通常）
 *
 * @param	repw	フィールドワーク
 *
 * @return	none
 *
 *	看板などの処理を中断して呼び出す処理
 */
//--------------------------------------------------------------------------------------------
void FieldMenuEvChg( FIELDSYS_WORK * repw )
{
	FLD_MENU * wk;
	
	// 元のワークを解放
	//sys_FreeMemoryEz( FieldEvent_GetSpecialWork(repw->event) );
	
	// メニューワーク作成
	Snd_SePlay( SE_WIN_OPEN );
	wk = MenuWorkAllocSet();

	wk->union_flg = FALSE;

	if( SysFlag_SafariCheck( SaveData_GetEventWork(repw->savedata) ) == TRUE ){
		wk->ev_flg = FieldMenuParamSetSafari( repw );	// サファリ
	}else if( SysFlag_PokeParkCheck( SaveData_GetEventWork(repw->savedata) ) == TRUE ){
		wk->ev_flg = FieldMenuParamSetPokePark( repw );	// ポケパーク
	}else if( BtlTower_IsSalon(repw) == TRUE ){
		wk->ev_flg = FieldMenuParamSetBtlTowerSalon( repw );	// バトルタワーサロン
	}else if( repw->MapMode == MAP_MODE_COLOSSEUM) {
		wk->ev_flg = FieldMenuParamSetVS( repw );		// 対戦部屋
	}else if( repw->MapMode == MAP_MODE_UNION ) {
		wk->ev_flg = FieldMenuParamSetUnion( repw );	// ユニオン
		wk->union_flg = TRUE;
	}else{
		wk->ev_flg = FieldMenuParamSet( repw );			// 通常メニュー
	}

	FieldEvent_Change( repw->event, GMEVENT_FieldMenu, wk );
}

//--------------------------------------------------------------------------------------------
/**
 * フィールドメニュー起動割り込み処理（ユニオンルーム用）
 *
 * @param	repw	フィールドワーク
 *
 * @return	none
 *
 *	看板などの処理を中断して呼び出す処理
 */
//--------------------------------------------------------------------------------------------
void FieldMenuEvChgUnion( FIELDSYS_WORK * repw )
{
	FLD_MENU * wk;
	
	// 元のワークを解放
	//sys_FreeMemoryEz( FieldEvent_GetSpecialWork(repw->event) );
	
	// メニューワーク作成
	Snd_SePlay( SE_WIN_OPEN );
	wk = MenuWorkAllocSet();
	wk->ev_flg    = FieldMenuParamSetUnion( repw );
	wk->union_flg = TRUE;
	FieldEvent_Change( repw->event, GMEVENT_FieldMenu, wk );
}

//--------------------------------------------------------------------------------------------
/**
 * フィールドメニューワーク確保
 *
 * @param	none
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static FLD_MENU * MenuWorkAllocSet(void)
{
	FLD_MENU * wk;

	wk = sys_AllocMemory( HEAPID_WORLD, sizeof(FLD_MENU) );
	wk->seq = FLD_MENU_SEQ_INIT;
	wk->pos = 0;
	wk->app_wk = NULL;

	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * 表示項目制御パラメータ作成（通常）
 *
 * @param	repw	フィールドワーク
 *
 * @return	表示項目制御パラメータ
 */
//--------------------------------------------------------------------------------------------
static u32 FieldMenuParamSet( FIELDSYS_WORK * repw )
{
	u32	prm = 0;

	if( ZukanWork_GetZukanGetFlag(SaveData_GetZukanWork(repw->savedata)) == FALSE ){
		prm |= FLD_MENU_VANISH_ZUKAN;
	}
	if( SysWork_FirstPokeNoGet(SaveData_GetEventWork(repw->savedata)) == 0 ){
		prm |= FLD_MENU_VANISH_PLIST;
	}
	if( SysFlag_BagCheck(SaveData_GetEventWork(repw->savedata)) == 0 ){
		prm |= FLD_MENU_VANISH_BAG;
	}
	// 自然公園かどうかのチェック
	if( ZoneData_IsNaturalPark( repw->location->zone_id ) == TRUE ){
		prm |= FLD_MENU_VANISH_PLIST;
		prm |= FLD_MENU_VANISH_BAG;
	}
	prm |= FLD_MENU_VANISH_CHAT;
	prm |= FLD_MENU_VANISH_RETIRE;

	return prm;
}

//--------------------------------------------------------------------------------------------
/**
 * 表示項目制御パラメータ作成（サファリ）
 *
 * @param	repw	フィールドワーク
 *
 * @return	表示項目制御パラメータ
 */
//--------------------------------------------------------------------------------------------
static u32 FieldMenuParamSetSafari( FIELDSYS_WORK * repw )
{
	return (FLD_MENU_VANISH_REPORT|FLD_MENU_VANISH_CHAT);
}

//--------------------------------------------------------------------------------------------
/**
 * 表示項目制御パラメータ作成（ポケパーク）
 *
 * @param	repw	フィールドワーク
 *
 * @return	表示項目制御パラメータ
 */
//--------------------------------------------------------------------------------------------
static u32 FieldMenuParamSetPokePark( FIELDSYS_WORK * repw )
{
	return (FLD_MENU_VANISH_REPORT|FLD_MENU_VANISH_CHAT|FLD_MENU_VANISH_BAG);
}

//--------------------------------------------------------------------------------------------
/**
 * 表示項目制御パラメータ作成（バトルタワーサロン）
 *
 * @param	repw	フィールドワーク
 *
 * @return	表示項目制御パラメータ
 */
//--------------------------------------------------------------------------------------------
static u32 FieldMenuParamSetBtlTowerSalon( FIELDSYS_WORK * repw )
{
	return (FLD_MENU_VANISH_ZUKAN|FLD_MENU_VANISH_BAG|FLD_MENU_VANISH_REPORT|FLD_MENU_VANISH_CHAT|FLD_MENU_VANISH_RETIRE);
}

//--------------------------------------------------------------------------------------------
/**
 * 表示項目制御パラメータ作成（ユニオン）
 *
 * @param	repw	フィールドワーク
 *
 * @return	表示項目制御パラメータ
 */
//--------------------------------------------------------------------------------------------
static u32 FieldMenuParamSetUnion( FIELDSYS_WORK * repw )
{
	return (FLD_MENU_VANISH_REPORT|FLD_MENU_VANISH_RETIRE);
}

//--------------------------------------------------------------------------------------------
/**
 * 表示項目制御パラメータ作成（対戦部屋）
 *
 * @param	repw	フィールドワーク
 *
 * @return	表示項目制御パラメータ
 */
//--------------------------------------------------------------------------------------------
static u32 FieldMenuParamSetVS( FIELDSYS_WORK * repw )
{
	return (FLD_MENU_VANISH_REPORT|FLD_MENU_VANISH_ZUKAN|FLD_MENU_VANISH_CHAT|FLD_MENU_VANISH_RETIRE);
}


//============================================================================================
//	制御
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * @brief	フィールドイベント：メニュー制御
 * @param	event	フィールドイベント用パラメータ
 * @retval	TRUE	イベント終了
 * @retval	FALSE	イベント継続
 */
//--------------------------------------------------------------------------------------------
static BOOL GMEVENT_FieldMenu(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * wk;

	fsys = FieldEvent_GetFieldSysWork(event);
	wk = FieldEvent_GetSpecialWork(event);

	switch( wk->seq ){
	case FLD_MENU_SEQ_INIT:		// 初期化
		FieldOBJSys_MovePauseAll( fsys->fldobjsys );
		ItemUse_CheckWorkMake( fsys, &wk->item_check );
		FieldSkill_CheckWorkMake( fsys, &wk->skill_check );
		FieldMenuSet( event );
		FieldBallWinSet( event );
		wk->seq = FLD_MENU_SEQ_SELECT;
		break;

	case FLD_MENU_SEQ_SELECT:	// メニュー選択
		if( FieldMenuSelect( event ) == FALSE ){
			return FALSE;
		}
		break;

	case FLD_MENU_SEQ_APP_CALL:	// アプリ呼び出し
		FldMenu_AppCall( event );
		break;

	case FLD_MENU_SEQ_APP_WAIT:	// アプリ終了待ち
		FldMenu_AppWait( event );
		break;

	case FLD_MENU_SEQ_REPORT_CALL:
		FldMenu_ReportCall( event );
		break;
	case FLD_MENU_SEQ_REPORT_WAIT:
		FldMenu_ReportWait( event );
		break;

	case FLD_MENU_SEQ_SHINKA_INIT:	// 進化画面呼び出し
		FldMenu_ShinkaInit( event );
		break;

	case FLD_MENU_SEQ_SHINKA_MAIN:	// 進化画面待ち
		FldMenu_ShinkaMain( event );
		break;

	case FLD_MENU_SEQ_AGAIN:	// ●●●●●●●●●
		//フィールドマッププロセス開始待ち
		if (FieldEvent_Cmd_WaitMapProcStart(fsys)) {
			FieldOBJSys_MovePauseAll( fsys->fldobjsys );
			FieldMenuSet( event );
			FieldBallWinSet( event );
			//ブラックインリクエスト
			FieldFadeWipeSet( FLD_DISP_BRIGHT_BLACKIN );
			wk->seq = FLD_MENU_SEQ_WAIT_BLACK_IN;
		}
		break;

	case FLD_MENU_SEQ_BLACK_IN_END:
		//フィールドマッププロセス開始待ち
		if(FieldEvent_Cmd_WaitMapProcStart(fsys)) {
			//ブラックインリクエスト
			FieldFadeWipeSet( FLD_DISP_BRIGHT_BLACKIN );
			wk->seq = FLD_MENU_SEQ_BLACK_IN_END_WAIT;
		}
		break;

	case FLD_MENU_SEQ_BLACK_IN_END_WAIT:
		if( WIPE_SYS_EndCheck() ){
			FldMenu_UnionBeaconChg( wk, fsys );
			sys_FreeMemoryEz( wk );
			FieldOBJSys_MovePauseAllClear( fsys->fldobjsys );
			return TRUE;
		}
		break;

	case FLD_MENU_SEQ_BLACK_IN_EVCHG:
		//フィールドマッププロセス開始待ち
		if(FieldEvent_Cmd_WaitMapProcStart(fsys)) {
			FieldOBJSys_MovePauseAll( fsys->fldobjsys );
			FieldFadeWipeSet( FLD_DISP_BRIGHT_BLACKIN );
			wk->seq = FLD_MENU_SEQ_BLACK_IN_EVCHG_WAIT;
		}
		break;

	case FLD_MENU_SEQ_BLACK_IN_EVCHG_WAIT:
		if( WIPE_SYS_EndCheck() ){
//			wk->app_func(event);
			FieldEvent_Change( event, wk->app_func, wk->app_wk );
			sys_FreeMemoryEz( wk );
//			return TRUE;
		}
		break;

	case FLD_MENU_SEQ_END_NOMENU:
		//メニューがすでに閉じている状態で終了
		sys_FreeMemoryEz( wk );
		FieldOBJSys_MovePauseAllClear( fsys->fldobjsys );
		return TRUE;

	case FLD_MENU_SEQ_END:
		FldMenu_UnionBeaconChg( wk, fsys );
		FieldMenuListExit( wk );
		BmpMenuWinClear( &wk->win, WINDOW_TRANS_OFF );
		GF_BGL_BmpWinDel( &wk->win );
		FieldBallWinExit( event );
		GF_BGL_LoadScreenV_Req( fsys->bgl, FLD_MBGFRM_FONT );
		sys_FreeMemoryEz( wk );
		FieldOBJSys_MovePauseAllClear( fsys->fldobjsys );
		return TRUE;

	case FLD_MENU_SEQ_WAIT_BLACK_IN:
		if ( WIPE_SYS_EndCheck() ){
			wk->seq = FLD_MENU_SEQ_SELECT;
		}
		break;
	}

	if( wk->mw != NULL ){
		CellActAnm( wk );
		CLACT_Draw( wk->fcat.cas );
	}

	return FALSE;
}

//--------------------------------------------------------------------------------------------
/**
 * フィールドメニュー作成
 *
 * @param	event	フィールドイベント用パラメータ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void FieldMenuSet( GMEVENT_CONTROL * event )
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * wk;
	MSGDATA_MANAGER * man;
	BMPMENU_HEADER	hed;
	u32	i, max;

	fsys = FieldEvent_GetFieldSysWork( event );
	wk   = FieldEvent_GetSpecialWork( event );

	max = FieldMenuListMake( wk, wk->list );

	GF_BGL_BmpWinAdd(
		fsys->bgl, &wk->win, FLD_MBGFRM_FONT, FLD_MENU_WIN_PX, FLD_MENU_WIN_PY,
		FLD_MENU_WIN_SX, max*3, FLD_MSG_WIN_PAL, FLD_MENU_WIN_CGX );

	MenuWinGraphicSet(
		fsys->bgl, FLD_MBGFRM_FONT, MENU_WIN_CGX_NUM, MENU_WIN_PAL, MENU_TYPE_FIELD, HEAPID_WORLD );
	BmpMenuWinWrite( &wk->win, WINDOW_TRANS_OFF, MENU_WIN_CGX_NUM, MENU_WIN_PAL );

	man = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_fieldmenu_dat, HEAPID_WORLD );
	wk->ld = BMP_MENULIST_Create( max, HEAPID_WORLD );
	wk->pos = 0;
	for( i=0; i<max; i++ ){
		if( wk->list[i] == MENU_POS_HERO ){
			WORDSET * wset;
			STRBUF * expb;
			STRBUF * strb;
			
			wset = WORDSET_Create( HEAPID_WORLD );
			expb = STRBUF_Create( BUFLEN_PERSON_NAME, HEAPID_WORLD );
			strb = MSGMAN_AllocString( man, FldMenuData[wk->list[i]][0] );

			WORDSET_RegisterPlayerName( wset, 0, SaveData_GetMyStatus(fsys->savedata) );
			WORDSET_ExpandStr( wset, expb, strb );

			BMP_MENULIST_AddString( wk->ld, expb, wk->list[i] );

			STRBUF_Delete( strb );
			STRBUF_Delete( expb );
			WORDSET_Delete( wset );
		}else{
			BMP_MENULIST_AddArchiveString(
				wk->ld, man, FldMenuData[wk->list[i]][0], wk->list[i] );
		}
		if( fsys->startmenu_pos == wk->list[i] ){
			wk->pos = i;
		}
	}
	fsys->startmenu_pos = wk->list[wk->pos];
	MSGMAN_Delete( man );

	hed.menu  = wk->ld;
	hed.win   = &wk->win;
	hed.font  = FONT_TALK;
	hed.x_max = 1;
	hed.y_max = max;
	hed.line_spc = 8;
	hed.c_disp_f = 1;
	if( max >= 4 ){
		hed.loop_f = 1;
	}else{
		hed.loop_f = 0;
	}

	wk->mw = BmpMenuAdd_NoTrans(
				&hed, 28, 4, wk->pos, HEAPID_WORLD, PAD_BUTTON_CANCEL|PAD_BUTTON_X );

	GF_BGL_BmpWinOnVReq( &wk->win );

	CellActSet( wk, wk->list, max, MyStatus_GetMySex(SaveData_GetMyStatus(fsys->savedata)) );
}

//--------------------------------------------------------------------------------------------
/**
 * メニューリスト作成
 *
 * @param	event	フィールドイベント用パラメータ
 * @param	list	リスト作成場所
 *
 * @return	項目数
 */
//--------------------------------------------------------------------------------------------
static u32 FieldMenuListMake( FLD_MENU * wk, u8 * list )
{
	u32	max = 0;

	// リタイア
	if( ( wk->ev_flg & FLD_MENU_VANISH_RETIRE ) == 0 ){
		list[max] = MENU_POS_RETIRE;
		max++;
	}
	// チャット
	if( ( wk->ev_flg & FLD_MENU_VANISH_CHAT ) == 0 ){
		list[max] = MENU_POS_CHAT;
		max++;
	}
	// 図鑑
	if( ( wk->ev_flg & FLD_MENU_VANISH_ZUKAN ) == 0 ){
		list[max] = MENU_POS_ZUKAN;
		max++;
	}
	// ポケモンリスト
	if( ( wk->ev_flg & FLD_MENU_VANISH_PLIST ) == 0 ){
		list[max] = MENU_POS_POKEMON;
		max++;
	}
	// バッグ
	if( ( wk->ev_flg & FLD_MENU_VANISH_BAG ) == 0 ){
		list[max] = MENU_POS_BAG;
		max++;
	}
	// トレーナーカード
	if( ( wk->ev_flg & FLD_MENU_VANISH_TRCARD ) == 0 ){
		list[max] = MENU_POS_HERO;
		max++;
	}
	// レポート
	if( ( wk->ev_flg & FLD_MENU_VANISH_REPORT ) == 0 ){
		list[max] = MENU_POS_REPORT;
		max++;
	}
	// 設定
	if( ( wk->ev_flg & FLD_MENU_VANISH_CONFIG ) == 0 ){
		list[max] = MENU_POS_CONFIG;
		max++;
	}
	// 閉じる
	if( ( wk->ev_flg & FLD_MENU_VANISH_CLOSE ) == 0 ){
		list[max] = MENU_POS_EXIT;
		max++;
	}

	return max;
}

//--------------------------------------------------------------------------------------------
/**
 * メニュー削除
 *
 * @param	wk		メニューワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void FieldMenuListExit( FLD_MENU * wk )
{
	CellActDelete( wk );

	BmpMenuExit( wk->mw, NULL );

	BMP_MENULIST_Delete( wk->ld );

	wk->mw = NULL;
}

//--------------------------------------------------------------------------------------------
/**
 * サファリ（パーク）ボールの個数ウィンドウ作成
 *
 * @param	event	フィールドイベント用パラメータ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void FieldBallWinSet( GMEVENT_CONTROL * event )
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * wk;
	MSGDATA_MANAGER * man;
	WORDSET * wset;
	STRBUF * expb;
	STRBUF * strb;
	u8	flg;

	fsys = FieldEvent_GetFieldSysWork( event );
	wk   = FieldEvent_GetSpecialWork( event );

	if( SysFlag_SafariCheck( SaveData_GetEventWork(fsys->savedata) ) == TRUE ){
		flg = 0;
	}else if( SysFlag_PokeParkCheck( SaveData_GetEventWork(fsys->savedata) ) == TRUE ){
		flg = 1;
	}else{
		return;
	}

	GF_BGL_BmpWinAdd(
		fsys->bgl, &wk->ball_win,
		FLD_MBGFRM_FONT, FLD_BALL_WIN_PX, FLD_BALL_WIN_PY,
		FLD_BALL_WIN_SX, FLD_BALL_WIN_SY, FLD_BALL_WIN_PAL, FLD_BALL_WIN_CGX );

	MenuWinGraphicSet(
		fsys->bgl, FLD_MBGFRM_FONT, MENU_WIN_CGX_NUM,
		MENU_WIN_PAL, MENU_TYPE_FIELD, HEAPID_WORLD );

	BmpMenuWinWrite( &wk->ball_win, WINDOW_TRANS_OFF, MENU_WIN_CGX_NUM, MENU_WIN_PAL );
	GF_BGL_BmpWinDataFill( &wk->ball_win, 15 );

	man  = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_fieldmenu_dat, HEAPID_WORLD );
	if( flg == 0 ){
		strb = MSGMAN_AllocString( man, msg_menu_09 );	// サファリボール
	}else{
		strb = MSGMAN_AllocString( man, msg_menu_10 );	// パークボール
	}
	GF_STR_PrintSimple(
		&wk->ball_win, FONT_SYSTEM, strb, BALL_NAME_PX, BALL_NAME_PY, MSG_NO_PUT, NULL );
	STRBUF_Delete( strb );

	wset = WORDSET_Create( HEAPID_WORLD );
	expb = STRBUF_Create( BALL_VAL_MSG_SIZ, HEAPID_WORLD );
	strb = MSGMAN_AllocString( man, msg_menu_11 );
	if( flg == 0 ){
		u16 * ball = Situation_GetSafariBallCount( SaveData_GetSituation(fsys->savedata) );
		WORDSET_RegisterNumber( wset, 0, *ball, 2, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
	}else{
		int	ball = PokeParkSys_GetBallCount( fsys );
		WORDSET_RegisterNumber( wset, 0, ball, 2, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
	}
	WORDSET_ExpandStr( wset, expb, strb );
	GF_STR_PrintSimple(
		&wk->ball_win, FONT_SYSTEM, expb, BALL_VAL_PX, BALL_VAL_PY, MSG_NO_PUT, NULL );

	STRBUF_Delete( expb );
	STRBUF_Delete( strb );
	WORDSET_Delete( wset );
	MSGMAN_Delete( man );

	GF_BGL_BmpWinOnVReq( &wk->ball_win );
}

//--------------------------------------------------------------------------------------------
/**
 * サファリ（パーク）ボールの個数ウィンドウ削除
 *
 * @param	event	フィールドイベント用パラメータ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void FieldBallWinExit( GMEVENT_CONTROL * event )
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * wk;

	fsys = FieldEvent_GetFieldSysWork( event );
	wk   = FieldEvent_GetSpecialWork( event );

	if( SysFlag_SafariCheck( SaveData_GetEventWork(fsys->savedata) ) == FALSE &&
		SysFlag_PokeParkCheck( SaveData_GetEventWork(fsys->savedata) ) == FALSE ){
		return;
	}

	BmpMenuWinClear( &wk->ball_win, WINDOW_TRANS_OFF );
	GF_BGL_BmpWinDel( &wk->ball_win );
}


//--------------------------------------------------------------------------------------------
/**
 * 選択処理
 *
 * @param	event	フィールドイベント用パラメータ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static BOOL FieldMenuSelect( GMEVENT_CONTROL * event )
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * wk;
	u16	cur;

	fsys = FieldEvent_GetFieldSysWork( event );
	wk   = FieldEvent_GetSpecialWork( event );

	cur = BmpMenuCursorPosGet( wk->mw );
	wk->ret = BmpMenuMain_SE( wk->mw, SE_FLD_MENU_SELECT );
	wk->pos = BmpMenuCursorPosGet( wk->mw );

	if( cur != wk->pos ){
		CursorMove( wk->cap[CLA_SET_CURSOR]->act, wk->pos );
		MoveIconAnmChg( wk, cur, wk->pos );
		fsys->startmenu_pos = wk->list[wk->pos];
	}

	SelectIconAnmCheck( wk->cap[CLA_SET_ICON+wk->pos]->act );

	switch( wk->ret ){
	case BMPMENU_NULL:
		break;
	case BMPMENU_CANCEL:
		wk->seq = FLD_MENU_SEQ_END;
		break;
	default:
		if( FldMenuData[wk->ret][1] == BMPMENU_CANCEL ){
			wk->seq = FLD_MENU_SEQ_END;
		}else if( FldMenuData[wk->ret][1] != BMPMENU_NULL ){
			GMEVENT_FUNC func = (GMEVENT_FUNC)FldMenuData[wk->ret][1];
			return func( event );
		}
	}

	return TRUE;
}

//--------------------------------------------------------------------------------------------
/**
 * ユニオンルームで話しかけ可能の状態にする
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void FldMenu_UnionBeaconChg( FLD_MENU * wk, FIELDSYS_WORK *fsys )
{
	// 通信ワークが存在しているなら
	if( CommMPIsInitialize() ){
		// ユニオンルームなら
	    if( wk->union_flg ){
			UnionRoomView_ObjAllRise( fsys->union_view );
//			UnionRoomView_ObjInit( fsys->union_view );
			CommStateUnionBconCollectionRestart();
	        Union_BeaconChange( UNION_PARENT_MODE_FREE );
		}
    }
}


//============================================================================================
//	セルアクター
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * セルアクターセット
 *
 * @param	wk		ワーク
 * @param	list	メニューリスト
 * @param	max		メニュー数
 * @param	sex		主人公の性別
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void CellActSet( FLD_MENU * wk, u8 * list, u32 max, u8 sex )
{
	TCATS_RESOURCE_NUM_LIST	crnl = {
		FLDMENU_CLA_CHR_RES_MAX, FLDMENU_CLA_PAL_RES_MAX,
		FLDMENU_CLA_CEL_RES_MAX, FLDMENU_CLA_ANM_RES_MAX, 0, 0
	};
	u32	i;

	FieldCellActSet_S( &wk->fcat, &crnl, FLDMENU_CLACT_MAX, HEAPID_WORLD );

	// 共通パレット読み込み
	FldClact_LoadResPlttArc(
		&wk->fcat, ARC_MENU_GRA,
		NARC_menu_gra_fmenu_obj_NCLR, 0, 2, NNS_G2D_VRAM_TYPE_2DMAIN, FLDMENU_CLA_PAL_H_ID );

	// 選択カーソル
	FldClact_LoadResCellArc(
		&wk->fcat, ARC_MENU_GRA, NARC_menu_gra_fmenu_cur_NCER, 0, FLDMENU_CLA_CEL_H_ID_CURSOR );

	FldClact_LoadResCellAnmArc(
		&wk->fcat, ARC_MENU_GRA, NARC_menu_gra_fmenu_cur_NANR, 0, FLDMENU_CLA_ANM_H_ID_CURSOR );

	FldClact_LoadResourceCharArc(
		&wk->fcat, ARC_MENU_GRA, NARC_menu_gra_fmenu_cur_NCGR,
		0, NNS_G2D_VRAM_TYPE_2DMAIN, FLDMENU_CLA_CHR_H_ID_CURSOR );

	wk->cap[CLA_SET_CURSOR] = FieldCellActAdd_S( &wk->fcat, &ActAddParam_S[CLA_SET_CURSOR] );

	CursorMove( wk->cap[CLA_SET_CURSOR]->act, wk->pos );

	// アイコン
	FldClact_LoadResCellArc(
		&wk->fcat, ARC_MENU_GRA, NARC_menu_gra_fmenu_obj_NCER, 0, FLDMENU_CLA_CEL_H_ID_ICON );

	FldClact_LoadResCellAnmArc(
		&wk->fcat, ARC_MENU_GRA, NARC_menu_gra_fmenu_obj_NANR, 0, FLDMENU_CLA_ANM_H_ID_ICON );

	FldClact_LoadResourceCharArc(
		&wk->fcat, ARC_MENU_GRA, NARC_menu_gra_fmenu_obj_NCGR,
		0, NNS_G2D_VRAM_TYPE_2DMAIN, FLDMENU_CLA_CHR_H_ID_ICON );

	for( i=0; i<max; i++ ){
		TCATS_OBJECT_ADD_PARAM_S	prm;

		prm = ActAddParam_S[CLA_SET_ICON];
		prm.y += CLA_ICON_SPC_Y * i;

		if( list[i] == MENU_POS_BAG && sex == 1 ){
			prm.anm = ICON_BAG_F * 3;
		}else{
			prm.anm = list[i] * 3;
		}

		wk->cap[CLA_SET_ICON+i] = FieldCellActAdd_S( &wk->fcat, &prm );

		{
			VecFx32 sca = { FX32_ONE, FX32_ONE, FX32_ONE };
			CLACT_SetScaleAffine( wk->cap[CLA_SET_ICON+i]->act, &sca, CLACT_AFFINE_NORMAL );
		}
	}
	IconAnmChange( wk->cap[CLA_SET_ICON+wk->pos]->act, ICON_ANM_SELECT, 1 );

	wk->clact_max = max + 1;	// セルアクター数（項目数＋選択カーソル）

	GF_Disp_GX_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );
}

//--------------------------------------------------------------------------------------------
/**
 * セルアクター削除
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void CellActDelete( FLD_MENU * wk )
{
	u16	i;

	for( i=0; i<wk->clact_max; i++ ){
		CATS_ActorPointerDelete_S( wk->cap[i] );
	}
	FieldCellActDelete_S( &wk->fcat );
}

//--------------------------------------------------------------------------------------------
/**
 * セルアクターアニメ
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void CellActAnm( FLD_MENU * wk )
{
	u16	i;

	for( i=0; i<wk->clact_max; i++ ){
		CLACT_AnmFrameChg( wk->cap[i]->act, FX32_ONE );
	}
}

//--------------------------------------------------------------------------------------------
/**
 * カーソル移動
 *
 * @param	cwp			セルアクターワーク
 * @param	cur_pos		カーソル位置
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void CursorMove( CLACT_WORK_PTR cwp, u32 cur_pos )
{
	VecFx32	act_pos;

	act_pos = *(CLACT_GetMatrix( cwp ));
	act_pos.y = ( CLA_CURSOR_PY + CLA_ICON_SPC_Y * cur_pos ) * FX32_ONE;
	CLACT_SetMatrix( cwp, &act_pos );
}

//--------------------------------------------------------------------------------------------
/**
 * アイコンアニメ変更
 *
 * @param	cwp		セルアクターワーク
 * @param	anm		アニメ番号
 * @param	pal		パレット番号
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void IconAnmChange( CLACT_WORK_PTR cwp, u16 anm, u16 pal )
{
	u32	now_anm = CLACT_AnmGet( cwp );

	CLACT_AnmChg( cwp, (now_anm/3)*3+anm );
	CLACT_PaletteNoChgAddTransPlttNo( cwp, pal );
}

//--------------------------------------------------------------------------------------------
/**
 * カーソル移動時のアイコンアニメ変更
 *
 * @param	wk			ワーク
 * @param	old_pos		前回選択されていたアイコン位置
 * @param	new_pos		新しく選択されていたアイコン位置
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void MoveIconAnmChg( FLD_MENU * wk, u16 old_pos, u16 new_pos )
{
	IconAnmChange( wk->cap[CLA_SET_ICON+old_pos]->act, ICON_ANM_STOP, 0 );
	IconAnmChange( wk->cap[CLA_SET_ICON+new_pos]->act, ICON_ANM_CHANGE, 1 );
}

//--------------------------------------------------------------------------------------------
/**
 * 選択されたアイコンのアニメ監視
 *
 * @param	cwp			セルアクターワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void SelectIconAnmCheck( CLACT_WORK_PTR cwp )
{
	if( ( CLACT_AnmGet( cwp ) % 3 ) != ICON_ANM_CHANGE ){
		return;
	}
	if( CLACT_AnmActiveCheck( cwp ) == FALSE ){
		IconAnmChange( cwp, ICON_ANM_SELECT, 1 );
	}
}


//============================================================================================
//	項目ごとの処理
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * アプリ呼び出し
 *
 * @param	event	フィールドイベント用パラメータ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void FldMenu_AppCall( GMEVENT_CONTROL * event )
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * wk;

	if( WIPE_SYS_EndCheck() == FALSE ){ return; }

	fsys = FieldEvent_GetFieldSysWork( event );
	wk   = FieldEvent_GetSpecialWork( event );

	FieldMenuListExit( wk );
	GF_BGL_BmpWinDel( &wk->win );
	FieldBallWinExit( event );

	wk->app_func( event );
	wk->seq = FLD_MENU_SEQ_APP_WAIT;
}

//--------------------------------------------------------------------------------------------
/**
 * アプリ終了待ち
 *
 * @param	event	フィールドイベント用パラメータ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void FldMenu_AppWait( GMEVENT_CONTROL * event )
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * wk;

	fsys = FieldEvent_GetFieldSysWork( event );
	wk   = FieldEvent_GetSpecialWork( event );

	// サブプロセス終了待ち
	if( FieldEvent_Cmd_WaitSubProcEnd( fsys ) ) {
		return;
	}

	wk->app_func( event );
}

//--------------------------------------------------------------------------------------------
/**
 * アプリ終了待ち処理セット
 *
 * @param	wk		ワーク
 * @param	func	終了待ち処理
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void FldMenu_AppWaitFuncSet( FLD_MENU * wk, void * func )
{
	wk->app_func = func;
	wk->seq      = FLD_MENU_SEQ_APP_WAIT;
}


//============================================================================================
//	メニュー：ずかん
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * 図鑑呼び出し設定
 *
 * @param	event	フィールドイベント用パラメータ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static BOOL FldMenu_ZukanInit( GMEVENT_CONTROL * event )
{
	FLD_MENU * wk;

	wk = FieldEvent_GetSpecialWork( event );

	FieldFadeWipeSet( FLD_DISP_BRIGHT_BLACKOUT );

	wk->app_func = FldMenu_ZukanCall;
	wk->seq = FLD_MENU_SEQ_APP_CALL;

	return TRUE;
}

//--------------------------------------------------------------------------------------------
/**
 * 図鑑呼び出し
 *
 * @param	event	フィールドイベント用パラメータ
 *
 * @return	0
 */
//--------------------------------------------------------------------------------------------
static BOOL FldMenu_ZukanCall( GMEVENT_CONTROL * event )
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * wk;
	ZKN_PEARENT_DATA * p_pearent;
	ZUKAN_WORK * p_zukan;
	MYSTATUS * p_mystatus;
	EVENTWORK * p_eventwork;

	fsys = FieldEvent_GetFieldSysWork( event );
	wk   = FieldEvent_GetSpecialWork( event );

	p_pearent = sys_AllocMemory( HEAPID_WORLD, sizeof(ZKN_PEARENT_DATA) );
	p_zukan   = SaveData_GetZukanWork( fsys->savedata );
	p_mystatus = SaveData_GetMyStatus( fsys->savedata );
	p_eventwork = SaveData_GetEventWork( fsys->savedata );
	p_pearent->cp_zukansave_data = p_zukan;
	p_pearent->cp_hero_data = p_mystatus;
	p_pearent->time_zone = EVTIME_GetTimeZone( fsys );
	p_pearent->hidemap_id_D15 = SysWork_HideMapWorkCheck( p_eventwork, HIDEMAP_ID_D15 );
	p_pearent->hidemap_id_D30 = SysWork_HideMapWorkCheck( p_eventwork, HIDEMAP_ID_D30 );
	p_pearent->hidemap_id_L04 = SysWork_HideMapWorkCheck( p_eventwork, HIDEMAP_ID_L04 );
	p_pearent->hidemap_id_D18 = SysWork_HideMapWorkCheck( p_eventwork, HIDEMAP_ID_D18 );
	p_pearent->p_zkn_work = fsys->p_zukandata;
	FieldZukan_SetProc( fsys, p_pearent );

	wk->app_wk   = p_pearent;
	wk->app_func = FldMenu_ZukanEnd;

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 図鑑終了処理
 *
 * @param	event	フィールドイベント用パラメータ
 *
 * @return	0
 */
//--------------------------------------------------------------------------------------------
static BOOL FldMenu_ZukanEnd( GMEVENT_CONTROL * event )
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * wk;

	fsys = FieldEvent_GetFieldSysWork( event );
	wk   = FieldEvent_GetSpecialWork( event );

	//フィールドマッププロセス復帰
	FieldEvent_Cmd_SetMapProc( fsys );

	if( wk->app_wk != NULL ){
		sys_FreeMemory( HEAPID_WORLD, wk->app_wk );
	}

	wk->seq = FLD_MENU_SEQ_AGAIN;

	return 0;
}


//=============================================================================================
//	メニュー：ポケモン
//=============================================================================================
typedef struct {
	u8	pos;
	u8	mode;
	u16	item;
	u16	after_mons;
	int shinka_cond;
}FLDMENU_SHINKA_WORK;

typedef struct {
	u16	item;
	u16	cnt;
}FLDMENU_WAZADEL_WORK;

static BOOL FldMenu_PokeListInit( GMEVENT_CONTROL * event )
{
	FLD_MENU * wk;

	wk = FieldEvent_GetSpecialWork( event );

	FieldFadeWipeSet( FLD_DISP_BRIGHT_BLACKOUT );

	wk->app_func = FldMenu_PokeListCall;
	wk->seq = FLD_MENU_SEQ_APP_CALL;

	return TRUE;
}

static BOOL FldMenu_PokeListCall( GMEVENT_CONTROL * event )
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * wk;

	fsys = FieldEvent_GetFieldSysWork( event );
	wk   = FieldEvent_GetSpecialWork( event );

	wk->app_wk   = FieldPokeList_SetProc( fsys, &wk->skill_check, 0 );
	wk->app_func = FldMenu_PokeListEnd;

	return 0;
}

BOOL FldMenu_PokeListEnd( GMEVENT_CONTROL * event )
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * wk;
	PLIST_DATA * dat;

	fsys = FieldEvent_GetFieldSysWork( event );
	wk   = FieldEvent_GetSpecialWork( event );
	dat	 = (PLIST_DATA *)sys_AllocMemory( HEAPID_WORLD, sizeof(PLIST_DATA) );

	memcpy( dat, wk->app_wk, sizeof(PLIST_DATA) );
	sys_FreeMemoryEz( wk->app_wk );

	switch( dat->ret_mode ){
	case PL_RET_STATUS:
		{
			PSTATUS_DATA * psd = sys_AllocMemory( HEAPID_WORLD, sizeof(PSTATUS_DATA) );

			psd->ppd  = SaveData_GetTemotiPokemon(fsys->savedata);
			psd->cfg  = SaveData_GetConfig( fsys->savedata );
			psd->ppt  = PST_PP_TYPE_POKEPARTY;
			psd->pos  = dat->ret_sel;
			psd->max  = (u8)PokeParty_GetPokeCount( psd->ppd );
			psd->waza = 0;
			psd->mode = PST_MODE_NORMAL;
			psd->ribbon = SaveData_GetSpRibbon( fsys->savedata );
			psd->zukan_mode = PMNumber_GetMode( fsys->savedata );
			psd->ev_contest = PokeStatus_ContestFlagGet( fsys->savedata );
			psd->perap = NULL;
			PokeStatus_PageSet( psd, PST_PageTbl_Normal );
			PokeStatus_PlayerSet( psd, SaveData_GetMyStatus(fsys->savedata) );
			FieldPokeStatus_SetProc( fsys, psd );

			wk->app_wk   = psd;
			FldMenu_AppWaitFuncSet( wk, FldMenu_PokeStatusEnd );
		}
		break;

	case PL_RET_WAZASET:		// 技忘れ（技マシン）
		{
			PSTATUS_DATA * psd = sys_AllocMemory( HEAPID_WORLD, sizeof(PSTATUS_DATA) );

			psd->ppd  = SaveData_GetTemotiPokemon(fsys->savedata);
			psd->cfg  = SaveData_GetConfig( fsys->savedata );
			psd->ppt  = PST_PP_TYPE_POKEPARTY;
			psd->pos  = dat->ret_sel;
			psd->max  = 1;
			psd->waza = dat->waza;
			psd->mode = PST_MODE_WAZAADD;
			psd->zukan_mode = PMNumber_GetMode( fsys->savedata );
			psd->ev_contest = PokeStatus_ContestFlagGet( fsys->savedata );
			psd->perap = NULL;
			PokeStatus_PageSet( psd, PST_PageTbl_WazaSet );
			PokeStatus_PlayerSet( psd, SaveData_GetMyStatus(fsys->savedata) );
			FieldPokeStatus_SetProc( fsys, psd );

			{
				FLDMENU_WAZADEL_WORK * del = sys_AllocMemory( HEAPID_WORLD, sizeof(FLDMENU_WAZADEL_WORK) );
				del->item  = dat->item;
				del->cnt   = 0;
				wk->tmp_wk = del;
			}
			wk->app_wk   = psd;
			FldMenu_AppWaitFuncSet( wk, FldMenu_PokeStatusEnd );
		}
		break;

	case PL_RET_LVUP_WAZASET:	// 技忘れ（不思議なアメ）
		{
			PSTATUS_DATA * psd = sys_AllocMemory( HEAPID_WORLD, sizeof(PSTATUS_DATA) );

			psd->ppd  = SaveData_GetTemotiPokemon(fsys->savedata);
			psd->cfg  = SaveData_GetConfig( fsys->savedata );
			psd->ppt  = PST_PP_TYPE_POKEPARTY;
			psd->pos  = dat->ret_sel;
			psd->max  = 1;
			psd->waza = dat->waza;
			psd->mode = PST_MODE_WAZAADD;
			psd->zukan_mode = PMNumber_GetMode( fsys->savedata );
			psd->ev_contest = PokeStatus_ContestFlagGet( fsys->savedata );
			psd->perap = NULL;
			PokeStatus_PageSet( psd, PST_PageTbl_WazaSet );
			PokeStatus_PlayerSet( psd, SaveData_GetMyStatus(fsys->savedata) );
			FieldPokeStatus_SetProc( fsys, psd );

			{
				FLDMENU_WAZADEL_WORK * del = sys_AllocMemory( HEAPID_WORLD, sizeof(FLDMENU_WAZADEL_WORK) );
				del->item  = ITEM_DUMMY_DATA;
				del->cnt   = (u16)dat->lv_cnt;
				wk->tmp_wk = del;
			}
			wk->app_wk   = psd;
			FldMenu_AppWaitFuncSet( wk, FldMenu_PokeStatusEnd );
		}
		break;

	case PL_RET_MAILSET:
		{
			MAIL_PARAM * mail;

			mail = FieldMailCreate_InitCall(
					fsys, MAILBLOCK_TEMOTI, dat->ret_sel,
					ItemMailDesignGet(dat->item), HEAPID_WORLD );
			wk->app_wk = mail;
			if( dat->mode == PL_MODE_ITEMSET_RET ){
				wk->tmp_wk = FieldMenu_MailWorkMake( 
								dat->item, FM_MAIL_MODE_MAKE_LIST, dat->ret_sel );
			}else{
				wk->tmp_wk = FieldMenu_MailWorkMake(
								dat->item, FM_MAIL_MODE_MAKE_BAG, dat->ret_sel );
			}
			FldMenu_AppWaitFuncSet( wk, FldMenu_MailEnd );
		}
		break;

	case PL_RET_MAILREAD:
		{
			MAIL_PARAM * mail;
			POKEMON_PARAM * pp;

			pp = PokeParty_GetMemberPointer(
					SaveData_GetTemotiPokemon(fsys->savedata), dat->ret_sel );
			mail = FieldMailViewPoke_InitCall( fsys, pp, HEAPID_WORLD );
			wk->app_wk   = mail;
			wk->tmp_wk   = FieldMenu_MailWorkMake( dat->item, FM_MAIL_MODE_READ, dat->ret_sel );
			FldMenu_AppWaitFuncSet( wk, FldMenu_MailEnd );
		}
		break;

	case PL_RET_ITEMSET:	// バッグの持たせるアイテム選択へ
		{
			MYITEM * myitem;
			void * myst;
			u32 * sel_pos;

			// 選択したポケモン位置を退避
			sel_pos = (u32 *)sys_AllocMemory( HEAPID_WORLD, 4 );
			*sel_pos = dat->ret_sel;
			wk->tmp_wk = (void *)sel_pos;

			myitem = SaveData_GetMyItem( fsys->savedata );
			myst   = SaveData_GetMyStatus( fsys->savedata );
			wk->app_wk = MyItem_MakeBagData( myitem, PokeList_ItemSetBagList, HEAPID_WORLD );
			BAG_SysDataSet( wk->app_wk, fsys->savedata, BAG_MODE_ITEMSET, fsys->bag_cursor );
		}

		FieldBag_SubProcSet( fsys, wk->app_wk );
		FldMenu_AppWaitFuncSet( wk, FldMenu_BagEnd );
		break;

	case PL_RET_ITEMSHINKA:		// 進化画面へ（アイテム進化）
		{
			FLDMENU_SHINKA_WORK * swk = sys_AllocMemory(HEAPID_WORLD,sizeof(FLDMENU_SHINKA_WORK));

			swk->item  = dat->item;
			swk->mode  = ITEM_SHINKA_CHECK;
			swk->pos   = dat->ret_sel;
			swk->after_mons = dat->after_mons;
			swk->shinka_cond = dat->shinka_cond;
			wk->app_wk = swk;
			wk->seq = FLD_MENU_SEQ_SHINKA_INIT;
		}
		break;

	case PL_RET_LVUPSHINKA:		// 進化画面へ（レベル進化）
		{
			FLDMENU_SHINKA_WORK * swk = sys_AllocMemory(HEAPID_WORLD,sizeof(FLDMENU_SHINKA_WORK));

			swk->item  = ZoneData_GetShinkaPlaceID( fsys->location->zone_id );
			swk->mode  = LEVELUP_SHINKA;
			swk->pos   = dat->ret_sel;
			swk->after_mons = dat->after_mons;
			swk->shinka_cond = dat->shinka_cond;
			wk->app_wk = swk;
			wk->seq = FLD_MENU_SEQ_SHINKA_INIT;
		}
		break;

	case PL_RET_IWAKUDAKI:		// メニュー 技：いわくだき
	case PL_RET_IAIGIRI:		// メニュー 技：いあいぎり
	case PL_RET_SORAWOTOBU:		// メニュー 技：そらをとぶ
	case PL_RET_KIRIBARAI:		// メニュー 技：きりばらい
	case PL_RET_KAIRIKI:		// メニュー 技：かいりき
	case PL_RET_NAMINORI:		// メニュー 技：なみのり
	case PL_RET_ROCKCLIMB:		// メニュー 技：ロッククライム
	case PL_RET_TAKINOBORI:		// メニュー 技：たきのぼり
	case PL_RET_FLASH:			// メニュー 技：フラッシュ
	case PL_RET_TELEPORT:		// メニュー 技：テレポート
	case PL_RET_ANAWOHORU:		// メニュー 技：あなをほる
	case PL_RET_AMAIKAORI:		// メニュー 技：あまいかおり
	case PL_RET_OSYABERI:		// メニュー 技：おしゃべり
		{
			SKILLUSE_FUNC func;
			SKILLUSE_WORK suwk;

			suwk.skill    = dat->ret_mode - PL_RET_IAIGIRI;
			suwk.poke_pos = dat->ret_sel;
			suwk.event    = event;

			func = (SKILLUSE_FUNC)FieldSkill_FuncGet( FIELDSKILL_PRM_USEFUNC, suwk.skill );
			func( &suwk, &wk->skill_check);
		}
		break;

	case PL_RET_BAG:			// バッグへ戻る
		wk->app_wk = FieldBag_SetProc( fsys, &wk->item_check );
		FldMenu_AppWaitFuncSet( wk, FldMenu_BagEnd );
		break;

	default:
/*
		if( dat->mode == PL_MODE_ITEMUSE || dat->mode == PL_MODE_ITEMSET ||
			dat->mode == PL_MODE_WAZASET || dat->mode == PL_MODE_WAZASET_RET ||
			dat->mode == PL_MODE_SHINKA || dat->mode == PL_MODE_LVUPWAZASET_RET ){
*/
		if( dat->mode == PL_MODE_ITEMUSE || dat->mode == PL_MODE_WAZASET ||
			dat->mode == PL_MODE_WAZASET_RET || dat->mode == PL_MODE_SHINKA ||
			dat->mode == PL_MODE_LVUPWAZASET_RET ){

			wk->app_wk = FieldBag_SetProc( fsys, &wk->item_check );
			if( dat->ret_sel >= 6 ){
				Bag_UsePokeSet( wk->app_wk, 0 );
			}else{
				Bag_UsePokeSet( wk->app_wk, dat->ret_sel );
			}
			FldMenu_AppWaitFuncSet( wk, FldMenu_BagEnd );

		}else if( dat->mode == PL_MODE_ITEMSET ){
			wk->app_wk = FieldBag_SetProc( fsys, &wk->item_check );
			FldMenu_AppWaitFuncSet( wk, FldMenu_BagEnd );

		}else{
			//フィールドマッププロセス復帰
			FieldEvent_Cmd_SetMapProc( fsys );
			wk->seq = FLD_MENU_SEQ_AGAIN;
		}
	}
	sys_FreeMemoryEz( dat );

	return 0;
}





//=============================================================================================
//=============================================================================================
//	メニュー：バッグ
//=============================================================================================
//=============================================================================================

static BOOL FldMenu_BagInit( GMEVENT_CONTROL * event )
{
	FLD_MENU * wk;

	wk   = FieldEvent_GetSpecialWork( event );

	FieldFadeWipeSet( FLD_DISP_BRIGHT_BLACKOUT );

	wk->app_func = FldMenu_BagCall;
	wk->seq = FLD_MENU_SEQ_APP_CALL;

	return TRUE;
}

static BOOL FldMenu_BagCall( GMEVENT_CONTROL * event )
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * wk;

	fsys = FieldEvent_GetFieldSysWork( event );
	wk   = FieldEvent_GetSpecialWork( event );

	wk->app_wk = FieldBag_SetProc( fsys, &wk->item_check );
	Bag_UsePokeSet( wk->app_wk, 0 );
	wk->app_func = FldMenu_BagEnd;

	return 0;
}

static BOOL FldMenu_BagEnd( GMEVENT_CONTROL * event )
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * wk;
	BAG_DATA * dat;

	fsys = FieldEvent_GetFieldSysWork( event );
	wk   = FieldEvent_GetSpecialWork( event );
	dat  = BagSystemDataAlloc( HEAPID_WORLD );

	memcpy( dat, wk->app_wk, BagSystemDataSizeGet() );
	sys_FreeMemoryEz( wk->app_wk );

	switch( BagSysReturnModeGet( dat ) ){
	case BAG_RET_USE:		// つかう
		{
			ITEMUSE_FUNC func;
			ITEMUSE_WORK iuwk;
			s32	use_id;

			iuwk.item     = BagSysReturnItemGet( dat );
			iuwk.use_poke = Bag_UsePokeGet( dat );
			iuwk.event    = event;
			use_id = ItemParamGet( iuwk.item, ITEM_PRM_FIELD, HEAPID_WORLD );
			func   = (ITEMUSE_FUNC)ItemUse_FuncGet( ITEMUSE_PRM_USEFUNC, use_id );
			func( &iuwk, &wk->item_check);
		}
		break;

	case BAG_RET_TAG:		// タグをみる
		FldMenu_NutsTagCall( event, BagSysReturnItemGet(dat) );
		break;

	case BAG_RET_ITEMSET:	// もたせる
		{
			PLIST_DATA * pld;

			pld  = sys_AllocMemory( HEAPID_WORLD, sizeof(PLIST_DATA) );
			memset( pld, 0, sizeof(PLIST_DATA) );
			pld->pp     = SaveData_GetTemotiPokemon(fsys->savedata);
			pld->myitem = SaveData_GetMyItem( fsys->savedata );
			pld->mailblock = SaveData_GetMailBlock( fsys->savedata );
			pld->cfg = SaveData_GetConfig( fsys->savedata );
			pld->scwk = &wk->skill_check;
			pld->type = PL_TYPE_SINGLE;
			pld->mode = PL_MODE_ITEMSET;
			pld->item = BagSysReturnItemGet( dat );
			GameSystem_StartSubProc( fsys, &PokeListProcData, pld );

			wk->app_wk   = pld;
			FldMenu_AppWaitFuncSet( wk, FldMenu_PokeListEnd );
		}
		break;

	case BAG_RET_POKEITEMSET:	// ポケモンリスト「もたせる」
		{
			POKEPARTY * party;
			POKEMON_PARAM * pp;
			u32 pos;
			u16	item;

			party = SaveData_GetTemotiPokemon( fsys->savedata );
			pos   = *(u32 *)wk->tmp_wk;
			item  = BagSysReturnItemGet( dat );
			pp    = PokeParty_GetMemberPointer( party, pos );

			sys_FreeMemoryEz( wk->tmp_wk );

			if( ItemMailCheck( item ) == TRUE && PokeParaGet( pp, ID_PARA_item, NULL ) == 0 ){
				MAIL_PARAM * mail;
				FM_MAIL_WORK * make;

				mail = FieldMailCreate_InitCall(
						fsys, MAILBLOCK_TEMOTI, pos,
						ItemMailDesignGet(item), HEAPID_WORLD );
				wk->app_wk   = mail;
				wk->tmp_wk   = FieldMenu_MailWorkMake( item, FM_MAIL_MODE_MAKE_LIST, (u8)pos );
				FldMenu_AppWaitFuncSet( wk, FldMenu_MailEnd );
			}else{
				PLIST_DATA * pld;

				pld  = sys_AllocMemory( HEAPID_WORLD, sizeof(PLIST_DATA) );
				memset( pld, 0, sizeof(PLIST_DATA) );
				pld->pp     = party;
				pld->myitem = SaveData_GetMyItem( fsys->savedata );
				pld->mailblock = SaveData_GetMailBlock( fsys->savedata );
				pld->cfg = SaveData_GetConfig( fsys->savedata );
				pld->scwk = &wk->skill_check;
				pld->type = PL_TYPE_SINGLE;
				pld->item = BagSysReturnItemGet( dat );
				pld->ret_sel = (u8)pos;
				pld->fsys = fsys;
				if( pld->item == 0 ){
					pld->mode = PL_MODE_FIELD;
				}else{
					pld->mode = PL_MODE_ITEMSET_RET;
				}
				GameSystem_StartSubProc( fsys, &PokeListProcData, pld );
				wk->app_wk   = pld;
				FldMenu_AppWaitFuncSet( wk, FldMenu_PokeListEnd );
			}
		}
		break;

	case BAG_RET_CANCEL:
	default:
		//フィールドマッププロセス復帰
		FieldEvent_Cmd_SetMapProc( fsys );
		wk->seq = FLD_MENU_SEQ_AGAIN;
	}
	sys_FreeMemoryEz( dat );

	return 0;
}




//=============================================================================================
//	メニュー：（主人公）
//=============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * トレーナーカード呼び出し設定
 *
 * @param	event	フィールドイベント用パラメータ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static BOOL FldMenu_TrCardInit( GMEVENT_CONTROL * event )
{
	FLD_MENU * wk;

	wk = FieldEvent_GetSpecialWork( event );

	FieldFadeWipeSet( FLD_DISP_BRIGHT_BLACKOUT );

	wk->app_func = FldMenu_TrCardCall;
	wk->seq = FLD_MENU_SEQ_APP_CALL;

	return TRUE;
}

//--------------------------------------------------------------------------------------------
/**
 * トレーナーカード呼び出し
 *
 * @param	event	フィールドイベント用パラメータ
 *
 * @return	0
 */
//--------------------------------------------------------------------------------------------
static BOOL FldMenu_TrCardCall( GMEVENT_CONTROL * event )
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * wk;

	fsys = FieldEvent_GetFieldSysWork( event );
	wk   = FieldEvent_GetSpecialWork( event );

	wk->app_wk = TRCSET_AllocTrainerCardData( HEAPID_WORLD );
	TRCSET_MakeTrainerInfo( BADGE_BRUSH_ON, TIME_UPDATE_ON, GYM_READER_MASK_NONE,
							UNION_TR_NONE,
							fsys, (TR_CARD_DATA *)wk->app_wk );

	FieldTrCard_SetProc( fsys, (TR_CARD_DATA *)wk->app_wk );

	wk->app_func = FldMenu_TrCardEnd;
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * トレーナーカード終了処理
 *
 * @param	event	フィールドイベント用パラメータ
 *
 * @return	0
 */
//--------------------------------------------------------------------------------------------
static BOOL FldMenu_TrCardEnd( GMEVENT_CONTROL * event )
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * wk;

	fsys = FieldEvent_GetFieldSysWork( event );
	wk   = FieldEvent_GetSpecialWork( event );

	//バッジ磨き回数更新
	TRCSET_UpdateBadgeScruchCount(fsys, (TR_CARD_DATA *)wk->app_wk);
	TRCSET_FreeTrainerCardData( (TR_CARD_DATA *)wk->app_wk );
	//フィールドマッププロセス復帰
	FieldEvent_Cmd_SetMapProc( fsys );
	wk->seq = FLD_MENU_SEQ_AGAIN;

	return 0;
}


//=============================================================================================
//=============================================================================================
//	メニュー：レポート
//=============================================================================================
//=============================================================================================
typedef struct {
	void * infowin;		///<セーブ情報ウィンドウ用ポインタ
//	int result;			///<セーブ結果受け取り用ワーク
	u16 result;			///<セーブ結果受け取り用ワーク
}FLDMENU_REPORT_WORK;

///メニュー項目：レポート：初期化
static BOOL FldMenu_ReportInit( GMEVENT_CONTROL * event )
{
	FLD_MENU * wk   = FieldEvent_GetSpecialWork( event );

	//フィールドメニュー消去
	FieldMenuListExit( wk );
	BmpMenuWinClear( &wk->win, WINDOW_TRANS_OFF );
	GF_BGL_LoadScreenV_Req( wk->win.ini, wk->win.frmnum );
	GF_BGL_BmpWinDel( &wk->win );
	FieldBallWinExit( event );

	wk->seq = FLD_MENU_SEQ_REPORT_CALL;

	return TRUE;
}

///メニュー項目：レポート：呼び出し
static void FldMenu_ReportCall( GMEVENT_CONTROL * event )
{
	FLD_MENU * wk   = FieldEvent_GetSpecialWork( event );
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork( event );
	FLDMENU_REPORT_WORK * repwk;

	if (SaveData_IsOverwritingOtherData(fsys->savedata)) {
		EventCall_Script( event, SCRID_REPORT_NG, NULL, NULL );
	} else {
		//レポート情報生成
		wk->app_wk = sys_AllocMemory(HEAPID_EVENT, sizeof(FLDMENU_REPORT_WORK));
		repwk = wk->app_wk;
		//結果受け取り用ワーク初期化
		repwk->result = FALSE;
		
		EventCall_Script( event, SCRID_REPORT, NULL, &repwk->result );
	}

	wk->seq = FLD_MENU_SEQ_REPORT_WAIT;
}

///メニュー項目：レポート：結果処理
static void FldMenu_ReportWait( GMEVENT_CONTROL * event )
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork( event );
	FLD_MENU * wk   = FieldEvent_GetSpecialWork( event );
	FLDMENU_REPORT_WORK * repwk = wk->app_wk;

	if (SaveData_IsOverwritingOtherData(fsys->savedata)) {
		wk->seq = FLD_MENU_SEQ_INIT;
	} else {
		if( repwk->result == FALSE ){		//セーブしていない
			wk->seq = FLD_MENU_SEQ_INIT;
		}else{								//セーブした
			wk->seq = FLD_MENU_SEQ_END_NOMENU;
		}
		sys_FreeMemoryEz(repwk);
	}
}


//=============================================================================================
//	メニュー：せってい
//=============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * コンフィグ画面呼び出し設定
 *
 * @param	event	フィールドイベント用パラメータ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static BOOL FldMenu_ConfigInit( GMEVENT_CONTROL * event )
{
	FLD_MENU * wk;

	wk   = FieldEvent_GetSpecialWork( event );

	FieldFadeWipeSet( FLD_DISP_BRIGHT_BLACKOUT );

	wk->app_func = FldMenu_ConfigCall;
	wk->seq = FLD_MENU_SEQ_APP_CALL;

	return TRUE;
}

//--------------------------------------------------------------------------------------------
/**
 * コンフィグ画面呼び出し
 *
 * @param	event	フィールドイベント用パラメータ
 *
 * @return	0
 */
//--------------------------------------------------------------------------------------------
static BOOL FldMenu_ConfigCall( GMEVENT_CONTROL * event )
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * wk;

	fsys = FieldEvent_GetFieldSysWork( event );
	wk   = FieldEvent_GetSpecialWork( event );

	wk->app_wk   = FieldConfig_SetProc( fsys );
	wk->app_func = FldMenu_ConfigEnd;

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * コンフィグ画面終了処理
 *
 * @param	event	フィールドイベント用パラメータ
 *
 * @return	0
 */
//--------------------------------------------------------------------------------------------
static BOOL FldMenu_ConfigEnd( GMEVENT_CONTROL * event )
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * wk;

	fsys = FieldEvent_GetFieldSysWork( event );
	wk   = FieldEvent_GetSpecialWork( event );

	//メモリ解放
	sys_FreeMemoryEz( wk->app_wk );
	//フィールドマッププロセス復帰
	FieldEvent_Cmd_SetMapProc( fsys );
	wk->seq = FLD_MENU_SEQ_AGAIN;

	return	0;
}


//=============================================================================================
//=============================================================================================
//	メニュー：チャット
//=============================================================================================
//=============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * チャット画面呼び出し設定
 *
 * @param	event	フィールドイベント用パラメータ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static BOOL FldMenu_ChatInit( GMEVENT_CONTROL * event )
{
	FLD_MENU * wk;

	wk   = FieldEvent_GetSpecialWork( event );

	FieldFadeWipeSet( FLD_DISP_BRIGHT_BLACKOUT );

	wk->app_func = FldMenu_ChatCall;
	wk->seq = FLD_MENU_SEQ_APP_CALL;

	return TRUE;
}

//--------------------------------------------------------------------------------------------
/**
 * チャット画面呼び出し
 *
 * @param	event	フィールドイベント用パラメータ
 *
 * @return	0
 */
//--------------------------------------------------------------------------------------------
static BOOL FldMenu_ChatCall( GMEVENT_CONTROL * event )
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * wk;
	PMS_DATA  pmsDat;

	fsys = FieldEvent_GetFieldSysWork( event );
	wk   = FieldEvent_GetSpecialWork( event );

	wk->app_wk = PMSI_PARAM_Create(
					PMSI_MODE_SENTENCE, PMSI_GUIDANCE_DEFAULT, fsys->savedata, HEAPID_WORLD );
	PMSDAT_Init( &pmsDat, PMS_TYPE_UNION);
	PMSI_PARAM_SetInitializeDataSentence( wk->app_wk, &pmsDat );
	FieldProc_SetPmsInput( fsys, (PMSI_PARAM*)wk->app_wk );

	wk->app_func = FldMenu_ChatEnd;

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * チャット画面終了処理
 *
 * @param	event	フィールドイベント用パラメータ
 *
 * @return	0
 */
//--------------------------------------------------------------------------------------------
static BOOL FldMenu_ChatEnd( GMEVENT_CONTROL * event )
{
	PMS_DATA pmsdata;

	FIELDSYS_WORK * fsys;
	FLD_MENU * wk;

	fsys = FieldEvent_GetFieldSysWork( event );
	wk   = FieldEvent_GetSpecialWork( event );

	// 簡易会話を更新したか？
	if ( PMSI_PARAM_CheckCanceled( wk->app_wk )==0 ){

		// 簡易会話取得
		PMSI_PARAM_GetInputDataSentence( wk->app_wk,  &pmsdata);

		// 通信ワークが存在しているなら
		if(CommMPIsInitialize()){
			// ビーコンデータの簡易会話を書き換える & 通信データに反映
//			CommMPSetMyPMS( &pmsdata );
//			CommMPFlashMyBss();
			Union_PMSReWrite( &pmsdata );							// ビーコンデータに反映させる
			Union_SetMyPmsData( fsys->union_work, &pmsdata );		// ユニオンワークで保存しておき下画面に表示させる
		}
		wk->seq = FLD_MENU_SEQ_BLACK_IN_END;
	}else{
		wk->seq = FLD_MENU_SEQ_AGAIN;
	}
	
	//メモリ解放
	PMSI_PARAM_Delete( (PMSI_PARAM*)wk->app_wk );

	//フィールドマッププロセス復帰
	FieldEvent_Cmd_SetMapProc( fsys );
//	UnionRoomView_ObjInit( fsys->union_view );
	UnionRoomView_ObjAllRise( fsys->union_view );

	return 0;
}


//=============================================================================================
//=============================================================================================
//	メニュー：リタイア
//=============================================================================================
//=============================================================================================
static BOOL FldMenu_RetireInit( GMEVENT_CONTROL * event )
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * wk;

	fsys = FieldEvent_GetFieldSysWork( event );
	wk   = FieldEvent_GetSpecialWork( event );

	//フィールドメニュー消去
	FieldMenuListExit( wk );
	BmpMenuWinClear( &wk->win, WINDOW_TRANS_OFF );
	GF_BGL_LoadScreenV_Req( wk->win.ini, wk->win.frmnum );
	GF_BGL_BmpWinDel( &wk->win );
	FieldBallWinExit( event );

	if( SysFlag_SafariCheck( SaveData_GetEventWork(fsys->savedata) ) == TRUE ){
		EventChange_Script( event, SCRID_SAFARI_RETIRE, NULL );
	}else{
		EventChange_Script( event, SCRID_D10R0101_ASK_RETIRE, NULL );
	}

	sys_FreeMemoryEz( wk );
	return FALSE;
}


//=============================================================================================
//=============================================================================================
//	サブアプリ：ステータス画面
//=============================================================================================
//=============================================================================================
static BOOL FldMenu_PokeStatusEnd( GMEVENT_CONTROL * event )
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * wk;
	PSTATUS_DATA * dat;

	fsys = FieldEvent_GetFieldSysWork( event );
	wk   = FieldEvent_GetSpecialWork( event );

	dat = sys_AllocMemory( HEAPID_WORLD, sizeof(PSTATUS_DATA) );

	memcpy( dat, wk->app_wk, sizeof(PSTATUS_DATA) );
	sys_FreeMemoryEz( wk->app_wk );

	switch( dat->mode ){
	case PST_MODE_WAZAADD:	// 技覚え/技忘れ
		{
			PLIST_DATA * pld;
			FLDMENU_WAZADEL_WORK * del;

			pld  = sys_AllocMemory( HEAPID_WORLD, sizeof(PLIST_DATA) );
			del = (FLDMENU_WAZADEL_WORK *)wk->tmp_wk;
			memset( pld, 0, sizeof(PLIST_DATA) );
			pld->pp     = SaveData_GetTemotiPokemon(fsys->savedata);
			pld->myitem = SaveData_GetMyItem( fsys->savedata );
			pld->mailblock = SaveData_GetMailBlock( fsys->savedata );
			pld->cfg = SaveData_GetConfig( fsys->savedata );
			pld->scwk = &wk->skill_check;
			pld->type = PL_TYPE_SINGLE;
			pld->fsys = fsys;
			if( del->item != ITEM_DUMMY_DATA ){
				pld->mode   = PL_MODE_WAZASET_RET;
				pld->lv_cnt = 0;
			}else{
				pld->mode   = PL_MODE_LVUPWAZASET_RET;
				pld->lv_cnt = del->cnt;
			}
			pld->item = del->item;
			pld->ret_sel = dat->pos;
			pld->waza = dat->waza;
			pld->waza_pos = dat->ret_sel;
			GameSystem_StartSubProc( fsys, &PokeListProcData, pld );
			sys_FreeMemoryEz( wk->tmp_wk );

			wk->app_wk   = pld;
			FldMenu_AppWaitFuncSet( wk, FldMenu_PokeListEnd );
		}
		break;

	default:
		wk->app_wk = FieldPokeList_SetProc( fsys, &wk->skill_check, dat->pos );
		FldMenu_AppWaitFuncSet( wk, FldMenu_PokeListEnd );
	}
	sys_FreeMemoryEz( dat );

	return 0;
}


//=============================================================================================
//=============================================================================================
//	サブアプリ：木の実タグ
//=============================================================================================
//=============================================================================================
static void FldMenu_NutsTagCall( GMEVENT_CONTROL * event, u16 item )
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * wk;
	MYITEM * myitem;
	u8	i;
	u8	scr, cur, max;

	fsys = FieldEvent_GetFieldSysWork( event );
	wk   = FieldEvent_GetSpecialWork( event );

	wk->app_wk = NutsTagSystemDataAlloc( HEAPID_WORLD );
	myitem = SaveData_GetMyItem( fsys->savedata );
	NutsTagPutDataSet( wk->app_wk, item, TAG_ON );
	max = 0;
	for( i=0; i<ITEM_NUTS_MAX; i++ ){
		item = NutsIDItemGet( i );
		if( MyItem_CheckItem( myitem, item, 1, HEAPID_WORLD ) == TRUE ){
			NutsTagPutDataSet( wk->app_wk, item, TAG_OFF );
			max++;
		}
	}
	MyItem_FieldBagCursorGet( fsys->bag_cursor, BAG_POKE_NUTS, &cur, &scr );
	NutsTagBagCursorSet( wk->app_wk, scr, cur, max+3 );

	FieldNutsTag_SetProc( fsys, wk->app_wk );
	FldMenu_AppWaitFuncSet( wk, FldMenu_NutsTagEnd );
}

static BOOL FldMenu_NutsTagEnd( GMEVENT_CONTROL * event )
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * wk;
	u8	scr, cur;

	fsys = FieldEvent_GetFieldSysWork( event );
	wk   = FieldEvent_GetSpecialWork( event );

	TagPosGet( wk->app_wk, &scr, &cur );
	MyItem_FieldBagCursorSet( fsys->bag_cursor, BAG_POKE_NUTS, cur, scr );

	sys_FreeMemory( HEAPID_WORLD, wk->app_wk );

	wk->app_wk = FieldBag_SetProc( fsys, &wk->item_check );
	FldMenu_AppWaitFuncSet( wk, FldMenu_BagEnd );

	return 0;
}


//=============================================================================================
//=============================================================================================
//	サブアプリ：タウンマップ
//=============================================================================================
//=============================================================================================
BOOL FldMenu_TownMapEnd( GMEVENT_CONTROL * event )
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * wk;

	fsys = FieldEvent_GetFieldSysWork( event );
	wk   = FieldEvent_GetSpecialWork( event );

	sys_FreeMemory( HEAPID_WORLD, wk->app_wk );
	wk->app_wk = FieldBag_SetProc( fsys, &wk->item_check );
	FldMenu_AppWaitFuncSet( wk, FldMenu_BagEnd );

	return 0;
}

// 空を飛ぶ
BOOL FldMenu_SorawotobuEnd( GMEVENT_CONTROL * event )
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * wk;
	TOWNMAP_PARAM * tmwk;
	u32	sel_pos;

	fsys = FieldEvent_GetFieldSysWork( event );
	wk   = FieldEvent_GetSpecialWork( event );

	sel_pos = *((u32 *)wk->tmp_wk);
	sys_FreeMemory( HEAPID_WORLD, wk->tmp_wk );

	tmwk = (TOWNMAP_PARAM *)wk->app_wk;
	if( !(tmwk->retval) ){
		sys_FreeMemory( HEAPID_WORLD, wk->app_wk );
		wk->app_wk = FieldPokeList_SetProc( fsys, &wk->skill_check, sel_pos );
		FldMenu_AppWaitFuncSet( wk, FldMenu_PokeListEnd );
	}else{
		POKEMON_PARAM * pp;
		void * ciwk;
		void * buf;

		pp = PokeParty_GetMemberPointer(
				SaveData_GetTemotiPokemon(fsys->savedata), sel_pos );
		ciwk = EventWorkSet_FlySkyMapChange( HEAPID_WORLD,
				fsys, pp, tmwk->ret_zone, tmwk->ret_x*32+16, tmwk->ret_z*32+16 );

		buf = FNOTE_ActionSkillDataMake( FNOTE_SORAWOTOBU, tmwk->ret_zone, HEAPID_WORLD );
		FNOTE_DataSave( fsys->fnote, buf, FNOTE_TYPE_ACTION );

		sys_FreeMemory( HEAPID_WORLD, wk->app_wk );

		FieldEvent_Cmd_SetMapProc( fsys );

		wk->app_func = GMEVENT_FlySkyMapChange;
		wk->app_wk   = ciwk;
		wk->seq      = FLD_MENU_SEQ_BLACK_IN_EVCHG;
	}

	return 0;
}


//=============================================================================================
//=============================================================================================
//	サブアプリ：冒険ノート
//=============================================================================================
//=============================================================================================
BOOL FldMenu_FantasyNoteEnd( GMEVENT_CONTROL * event )
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * wk;

	fsys = FieldEvent_GetFieldSysWork( event );
	wk   = FieldEvent_GetSpecialWork( event );

	wk->app_wk = FieldBag_SetProc( fsys, &wk->item_check );
	FldMenu_AppWaitFuncSet( wk, FldMenu_BagEnd );

	return 0;
}


//=============================================================================================
//=============================================================================================
//	サブアプリ：メール
//=============================================================================================
//=============================================================================================
static void FM_MailMakeTrue( FIELDSYS_WORK * fsys, FLD_MENU * wk, u8 list_mode );

void * FieldMenu_MailWorkMake( u16 item, u8 mode, u8 poke_pos )
{
	FM_MAIL_WORK * mw = sys_AllocMemory( HEAPID_WORLD, sizeof(FM_MAIL_WORK) );

	mw->item = item;
	mw->pos  = poke_pos;
	mw->mode = mode;
	return (void *)mw;
}



BOOL FldMenu_MailEnd( GMEVENT_CONTROL * event )
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * wk;
	FM_MAIL_WORK * mw;

	fsys = FieldEvent_GetFieldSysWork( event );
	wk   = FieldEvent_GetSpecialWork( event );
	mw   = wk->tmp_wk;

	switch( mw->mode ){
	case FM_MAIL_MODE_VIEW:		// メールを見る
		MailSys_ReleaseCallWork( wk->app_wk );
		wk->app_wk = FieldBag_SetProc( fsys, &wk->item_check );
		FldMenu_AppWaitFuncSet( wk, FldMenu_BagEnd );
		break;

	case FM_MAIL_MODE_READ:		// メールを読む
		MailSys_ReleaseCallWork( wk->app_wk );
		wk->app_wk = FieldPokeList_SetProc( fsys, &wk->skill_check, mw->pos );
		FldMenu_AppWaitFuncSet( wk, FldMenu_PokeListEnd );
		break;

	case FM_MAIL_MODE_MAKE_LIST:	// メールを持たせる（ポケモンリストから）
		if( MailSys_IsDataCreate( wk->app_wk ) == TRUE ){
			FM_MailMakeTrue( fsys, wk, PL_MODE_MAILSET_BAG );
		}else{
			MailSys_ReleaseCallWork( wk->app_wk );
			wk->app_wk = FieldPokeList_SetProc( fsys, &wk->skill_check, mw->pos );
			FldMenu_AppWaitFuncSet( wk, FldMenu_PokeListEnd );
		}
		break;

	case FM_MAIL_MODE_MAKE_BAG:		// メールを持たせる（バッグから）
		if( MailSys_IsDataCreate( wk->app_wk ) == TRUE ){
			FM_MailMakeTrue( fsys, wk, PL_MODE_MAILSET );
		}else{
			MailSys_ReleaseCallWork( wk->app_wk );
			wk->app_wk = FieldBag_SetProc( fsys, &wk->item_check );
			FldMenu_AppWaitFuncSet( wk, FldMenu_BagEnd );
		}
		break;
	}
	sys_FreeMemoryEz( wk->tmp_wk );
	return 0;
}

static void FM_MailMakeTrue( FIELDSYS_WORK * fsys, FLD_MENU * wk, u8 list_mode )
{
	FM_MAIL_WORK * mw;
	PLIST_DATA * pld;

	mw  = wk->tmp_wk;
	pld = sys_AllocMemory( HEAPID_WORLD, sizeof(PLIST_DATA) );
	memset( pld, 0, sizeof(PLIST_DATA) );
	pld->pp      = SaveData_GetTemotiPokemon(fsys->savedata);
	pld->myitem  = SaveData_GetMyItem( fsys->savedata );
	pld->mailblock = SaveData_GetMailBlock( fsys->savedata );
	pld->cfg = SaveData_GetConfig( fsys->savedata );
	pld->scwk    = &wk->skill_check;
	pld->type    = PL_TYPE_SINGLE;
	pld->item    = mw->item;
	pld->ret_sel = mw->pos;
	pld->mode    = list_mode;
	pld->fsys = fsys;
	MailSys_PushDataToSavePoke( wk->app_wk, PokeParty_GetMemberPointer(pld->pp,mw->pos) );
	MailSys_ReleaseCallWork( wk->app_wk );

	GameSystem_StartSubProc( fsys, &PokeListProcData, pld );
	wk->app_wk   = pld;
	FldMenu_AppWaitFuncSet( wk, FldMenu_PokeListEnd );
}



//=============================================================================================
//=============================================================================================
//	サブアプリ：ポルトケース
//=============================================================================================
//=============================================================================================
BOOL FldMenu_PorutoCaseEnd( GMEVENT_CONTROL * event )
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * wk;

	fsys = FieldEvent_GetFieldSysWork( event );
	wk   = FieldEvent_GetSpecialWork( event );

	PorutoSys_ReleaseCallWork( wk->app_wk );

	wk->app_wk = FieldBag_SetProc( fsys, &wk->item_check );
	FldMenu_AppWaitFuncSet( wk, FldMenu_BagEnd );

	return 0;
}


//=============================================================================================
//=============================================================================================
//	サブアプリ：友達手帳
//=============================================================================================
//=============================================================================================
BOOL FldMenu_FriendBookEnd( GMEVENT_CONTROL * event )
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * wk;

	fsys = FieldEvent_GetFieldSysWork( event );
	wk   = FieldEvent_GetSpecialWork( event );

	wk->app_wk = FieldBag_SetProc( fsys, &wk->item_check );
	FldMenu_AppWaitFuncSet( wk, FldMenu_BagEnd );

	return 0;
}



//=============================================================================================
//=============================================================================================
//	サブアプリ：進化画面（特殊）
//=============================================================================================
//=============================================================================================

static void FldMenu_ShinkaInit( GMEVENT_CONTROL * event )
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * wk;
	FLDMENU_SHINKA_WORK * swk;
	POKEPARTY * party;
	POKEMON_PARAM * pp;
	SHINKA_WORK * demo;

	fsys = FieldEvent_GetFieldSysWork( event );
	wk   = FieldEvent_GetSpecialWork( event );
	swk  = wk->app_wk;

	Snd_Stop();	//サウンド全停止

	sys_CreateHeap( HEAPID_BASE_APP, HEAPID_ITEMSHINKA, 0x30000 );

	party = SaveData_GetTemotiPokemon(fsys->savedata);
	pp   = PokeParty_GetMemberPointer( party, swk->pos );

	if( swk->mode == LEVELUP_SHINKA ){
		demo = ShinkaInit(
					party,//ppt
					pp, swk->after_mons,
					SaveData_GetConfig(fsys->savedata),
					PokeStatus_ContestFlagGet(fsys->savedata), 
					SaveData_GetZukanWork(fsys->savedata),
					SaveData_GetMyItem(fsys->savedata),//my_item
					SaveData_GetRecord(fsys->savedata),//record
					SaveData_GetPoketchData(fsys->savedata),//poketch_data
					swk->shinka_cond,//shinka_cond
					SHINKA_STATUS_FLAG_CANCEL_ON, HEAPID_ITEMSHINKA );
	}else{
		demo = ShinkaInit(
					party,//ppt
					pp, swk->after_mons,
					SaveData_GetConfig(fsys->savedata),
					PokeStatus_ContestFlagGet(fsys->savedata), 
					SaveData_GetZukanWork(fsys->savedata),
					SaveData_GetMyItem(fsys->savedata),//my_item
					SaveData_GetRecord(fsys->savedata),//record
					SaveData_GetPoketchData(fsys->savedata),//poketch_data
					swk->shinka_cond,//shinka_cond
					NULL, HEAPID_ITEMSHINKA );
	}


	{
		u32 * ret_sel = sys_AllocMemory( HEAPID_WORLD, 4 );
		*ret_sel = swk->pos;
		wk->tmp_wk = ret_sel;
	}

	sys_FreeMemoryEz( wk->app_wk );
	wk->app_wk = demo;
	wk->seq    = FLD_MENU_SEQ_SHINKA_MAIN;
}

static void FldMenu_ShinkaMain( GMEVENT_CONTROL * event )
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * wk;

	fsys = FieldEvent_GetFieldSysWork( event );
	wk   = FieldEvent_GetSpecialWork( event );

	if( ShinkaEndCheck( wk->app_wk ) == TRUE ){
		ShinkaEnd( wk->app_wk );
		sys_DeleteHeap( HEAPID_ITEMSHINKA );

		Snd_BgmStop( SEQ_SHINKA, 0 );				//進化曲を止める
		Snd_SceneSet( SND_SCENE_DUMMY );			//必ずフィールドデータを再ロードさせる！
		Snd_FieldMapInitBgmPlay( fsys, fsys->location->zone_id );

		wk->app_wk = FieldBag_SetProc( fsys, &wk->item_check );
		{
			u32	ret_sel = *((u32 *)wk->tmp_wk);
			Bag_UsePokeSet( wk->app_wk, (u8)ret_sel );
			sys_FreeMemoryEz( wk->tmp_wk );
		}
		FldMenu_AppWaitFuncSet( wk, FldMenu_BagEnd );
	}
}
