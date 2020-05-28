//============================================================================================
/**
 * @file	itemuse.c
 * @brief	フィールドアイテム使用処理
 * @author	Hiroyuki Nakamura
 * @date	05.12.12
 */
//============================================================================================
#include "common.h"

#include "system/procsys.h"
#include "system/bmp_menu.h"
#include "system/bmp_list.h"
#include "system/clact_tool.h"
#include "system/snd_tool.h"
#include "system/wipe.h"
#include "system/window.h"
#include "poketool/pokeparty.h"
#include "itemtool/item.h"
#include "itemtool/myitem.h"
#include "application/pokelist.h"
#include "application/poru_tool.h"
#include "application/bag.h"
#include "savedata/tv_work.h"

#include "field_common.h"
#include "fieldsys.h"
#include "field_event.h"
#include "field_clact.h"
#include "field_subproc.h"
#include "fld_menu.h"
#include "fld_bgm.h"
#include "fieldmap.h"
#include "talk_msg.h"
#include "ev_mapchange.h"
#include "zonedata.h"
#include "map_attr.h"
#include "sway_grass_enc.h"	//for SwayGrass_InitSwayGrass
#include "sysflag.h"
#include "syswork.h"
#include "savedata/zukanwork.h"
#include "field_fishing.h"
#include "field_ananuke.h"
#include "eventdata.h"
#include "b_tower_ev.h"

#define	ITEMUSE_H_GLOBAL
#include "field/itemuse.h"

#include "seedsys.h"
#include "script.h"
#include "sxy.h"
#include "../fielddata/script/kinomi_def.h"
#include "../fielddata/script/saisen_def.h"
#include "amaikaori_eff.h"

#include "../fielddata/script/common_scr_def.h"	//SCRID_TENKAINOFUE
//#include "mapdefine.h"

//============================================================================================
//	定数定義
//============================================================================================
typedef void * (*CNVFUNC_CALL)(void*);

// 便利ボタンワーク
typedef struct {
	FIELDSYS_WORK * fsys;
	ITEMCHECK_WORK	icwk;
	CNVFUNC_CALL	call;
	void * app_wk;
	u16	item;
	u8	seq;
}CONV_WORK;

typedef BOOL (*ITEMCNV_FUNC)(CONV_WORK*);	// 便利ボタン使用関数

typedef struct {
	ITEMUSE_FUNC	use_func;		// バッグから使用
	ITEMCNV_FUNC	cnv_func;		// 便利ボタンから使用
	ITEMCHECK_FUNC	check_func;		// 使用チェック
}ITEMUSE_FUNC_DATA;


//============================================================================================
//	プロトタイプ宣言
//============================================================================================
extern void * FieldMenuTMap_SetProc( FIELDSYS_WORK * fsys );

static void ItemUse_Recover( ITEMUSE_WORK * iuwk, const ITEMCHECK_WORK * icwk);
static void ItemUse_Townmap( ITEMUSE_WORK * iuwk, const ITEMCHECK_WORK * icwk);
static void ItemUse_Tankenset( ITEMUSE_WORK * iuwk, const ITEMCHECK_WORK * icwk);
static void ItemUse_Cycle( ITEMUSE_WORK * iuwk, const ITEMCHECK_WORK * icwk);
static void ItemUse_FantasyNote( ITEMUSE_WORK * iuwk, const ITEMCHECK_WORK * icwk);
static void ItemUse_WazaMachine( ITEMUSE_WORK * iuwk, const ITEMCHECK_WORK * icwk);
static void ItemUse_Mail( ITEMUSE_WORK * iuwk, const ITEMCHECK_WORK * icwk);
static void ItemUse_Kinomi( ITEMUSE_WORK * iuwk, const ITEMCHECK_WORK * icwk);
static void ItemUse_PrtCase( ITEMUSE_WORK * iuwk, const ITEMCHECK_WORK * icwk);
static void ItemUse_FriendBook( ITEMUSE_WORK * iuwk, const ITEMCHECK_WORK * icwk);
static void ItemUse_PokeSearcher( ITEMUSE_WORK * iuwk , const ITEMCHECK_WORK * icwk);
static void ItemUse_Zyouro( ITEMUSE_WORK * iuwk, const ITEMCHECK_WORK * icwk);
static void ItemUse_Compost( ITEMUSE_WORK * iuwk, const ITEMCHECK_WORK * icwk);
static void ItemUse_SweetHoney( ITEMUSE_WORK * iuwk, const ITEMCHECK_WORK * icwk);
static void ItemUse_BtlSearcher( ITEMUSE_WORK * iuwk, const ITEMCHECK_WORK * icwk);
static void ItemUse_FishingRodBad( ITEMUSE_WORK * iuwk, const ITEMCHECK_WORK * icwk);
static void ItemUse_FishingRodGood( ITEMUSE_WORK * iuwk, const ITEMCHECK_WORK * icwk);
static void ItemUse_FishingRodGreat( ITEMUSE_WORK * iuwk, const ITEMCHECK_WORK * icwk);
static void ItemUse_Evolution( ITEMUSE_WORK * iuwk, const ITEMCHECK_WORK * icwk);
static void ItemUse_Ananuke( ITEMUSE_WORK * iuwk, const ITEMCHECK_WORK * icwk);
static void ItemUse_Tenkainofue( ITEMUSE_WORK * iuwk, const ITEMCHECK_WORK * icwk);

static BOOL ItemCnv_Cycle( CONV_WORK * wk );
static BOOL ItemCnv_FantasyNote( CONV_WORK * wk );
static BOOL ItemCnv_FishingRodBad( CONV_WORK * wk );
static BOOL ItemCnv_FishingRodGood( CONV_WORK * wk );
static BOOL ItemCnv_FishingRodGreat( CONV_WORK * wk );
static BOOL ItemCnv_BagMsgItem( CONV_WORK * wk );
static BOOL ItemCnv_Townmap( CONV_WORK * wk );
static BOOL ItemCnv_PrtCase( CONV_WORK * wk );
static BOOL ItemCnv_FriendBook( CONV_WORK * wk );
static BOOL ItemCnv_Tankenset( CONV_WORK * wk );
static BOOL ItemCnv_PokeSearcher( CONV_WORK * wk );
static BOOL ItemCnv_Zyouro( CONV_WORK * wk );
static BOOL ItemCnv_BtlSearcher( CONV_WORK * wk );
static BOOL ItemCnv_Tenkainofue( CONV_WORK * wk );
static void * ConvCall_FriendBook( void * fsys );
static void * ConvCall_PrtCase( void * fsys );
static void * ConvCall_Townmap( void * fsys );
static void * ConvCall_FantasyNote( void * fsys );

static u32 ItemUseCheck_Cycle( const ITEMCHECK_WORK * icwk );
static u32 ItemUseCheck_Tankenset( const ITEMCHECK_WORK * icwk );
static u32 ItemUseCheck_Kinomi( const ITEMCHECK_WORK * icwk );
static u32 ItemUseCheck_PokeSearcher( const ITEMCHECK_WORK * icwk );
static u32 ItemUseCheck_Zyouro( const ITEMCHECK_WORK * icwk );
static u32 ItemUseCheck_Compost( const ITEMCHECK_WORK * icwk );
static u32 ItemUseCheck_BtlSearcher( const ITEMCHECK_WORK * icwk );
static u32 ItemUseCheck_FishingRod( const ITEMCHECK_WORK * icwk );
static u32 ItemUseCheck_Ananuke( const ITEMCHECK_WORK * icwk );
static u32 ItemUseCheck_Tenkainofue( const ITEMCHECK_WORK * icwk );

static BOOL GMEVENT_ItemUseCycle( GMEVENT_CONTROL * event );
static BOOL GMEVENT_BagMsgItem( GMEVENT_CONTROL * event );

static void ConvFuncCallSet( CONV_WORK * wk, CNVFUNC_CALL call );
static BOOL GMEVENT_ConvButtonCommon( GMEVENT_CONTROL * event );

static BOOL GMEVENT_AnanukeMapChangeInit( GMEVENT_CONTROL *event );

//============================================================================================
//	グローバル変数
//============================================================================================
// 使用関数テーブル
static const ITEMUSE_FUNC_DATA ItemFuncTable[] =
{
	{	// 000:ダミー
		NULL,				// バッグからの使用処理
		ItemCnv_BagMsgItem,	// 便利ボタンからの使用処理
		NULL				// 使用チェック
	},
	{	// 001:回復
		ItemUse_Recover,
		NULL,
		NULL
	},
	{	// 002:タウンマップ
		ItemUse_Townmap,
		ItemCnv_Townmap,
		NULL,
	},
	{	// 003:探検セット
		ItemUse_Tankenset,
		ItemCnv_Tankenset,
		ItemUseCheck_Tankenset
	},
	{	// 004:自転車
		ItemUse_Cycle,
		ItemCnv_Cycle,
		ItemUseCheck_Cycle,
	},
	{	// 005:冒険ノート
		ItemUse_FantasyNote,
		ItemCnv_FantasyNote,
		NULL,
	},
	{	// 006:技マシン
		ItemUse_WazaMachine,
		NULL,
		NULL
	},
	{	// 007:メール
		ItemUse_Mail,
		NULL,
		NULL
	},
	{	// 008:きのみ
		ItemUse_Kinomi,
		NULL,
		ItemUseCheck_Kinomi
	},
	{	// 009:ポルトケース
		ItemUse_PrtCase,
		ItemCnv_PrtCase,
		NULL
	},
	{	// 010:友達手帳
		ItemUse_FriendBook,
		ItemCnv_FriendBook,
		NULL
	},
	{	// 011:ポケサーチャー
		ItemUse_PokeSearcher,
		ItemCnv_PokeSearcher,
		ItemUseCheck_PokeSearcher
	},
	{	// 012:じょうろ
		ItemUse_Zyouro,
		ItemCnv_Zyouro,
		ItemUseCheck_Zyouro
	},
	{	// 013:コヤシ
		ItemUse_Compost,
		NULL,
		ItemUseCheck_Compost
	},
	{	// 014:甘い蜜
		ItemUse_SweetHoney,
		NULL,
		NULL
	},
	{	// 015:バトルサーチャー
		ItemUse_BtlSearcher,
		ItemCnv_BtlSearcher,
		ItemUseCheck_BtlSearcher
	},
	{	// 016:ボロの釣竿
		ItemUse_FishingRodBad,
		ItemCnv_FishingRodBad,
		ItemUseCheck_FishingRod
	},
	{	// 017:良い釣竿
		ItemUse_FishingRodGood,
		ItemCnv_FishingRodGood,
		ItemUseCheck_FishingRod
	},
	{	// 018:凄い釣竿
		ItemUse_FishingRodGreat,
		ItemCnv_FishingRodGreat,
		ItemUseCheck_FishingRod
	},
	{	// 019:バッグ内で使用する道具
		NULL,
		ItemCnv_BagMsgItem,
		NULL
	},
	{	// 020:進化
		ItemUse_Evolution,
		NULL,
		NULL
	},
	{	// 021:穴抜けの紐
		ItemUse_Ananuke,
		NULL,
		ItemUseCheck_Ananuke
	},
	{	// 022:天界の笛
		ItemUse_Tenkainofue,
		ItemCnv_Tenkainofue,
		ItemUseCheck_Tenkainofue
	},
};



//--------------------------------------------------------------------------------------------
/**
 * 使用関数取得
 *
 * @param	prm		取得パラメータ
 * @param	id		関数ID
 *
 * @return	使用関数
 */
//--------------------------------------------------------------------------------------------
u32 ItemUse_FuncGet( u16 prm, u16 id )
{
	if( prm == ITEMUSE_PRM_USEFUNC ){
		return (u32)ItemFuncTable[id].use_func;
	}else if( prm == ITEMUSE_PRM_CNVFUNC ){
		return (u32)ItemFuncTable[id].cnv_func;
	}
	return (u32)ItemFuncTable[id].check_func;
}

//--------------------------------------------------------------------------------------------
/**
 * 使用チェックワーク作成
 *
 * @param	fsys	フィールドワーク
 * @param	id		チェックワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void ItemUse_CheckWorkMake( FIELDSYS_WORK * fsys, ITEMCHECK_WORK * icwk )
{
	int x, z, dir;
	FIELD_OBJ_PTR obj;

	icwk->fsys = fsys;

	//ゾーンＩＤ
	icwk->zone_id = fsys->location->zone_id;

	//連れ歩き
	icwk->Companion = SysFlag_PairCheck(SaveData_GetEventWork(fsys->savedata));

	//自機形状
	icwk->PlayerForm = Player_FormGet( fsys->player );
	x = Player_NowGPosXGet( fsys->player );
	z = Player_NowGPosZGet( fsys->player );
	//現在アトリビュート
	icwk->NowAttr = GetAttributeLSB(fsys, x, z);

	dir = Player_DirGet( fsys->player );
	switch(dir){
	case DIR_UP:
		z--;
		break;
	case DIR_DOWN:
		z++;
		break;
	case DIR_RIGHT:
		x++;
		break;
	case DIR_LEFT:
		x--;
		break;
	}
	//前方アトリビュート
	icwk->FrontAttr = GetAttributeLSB(fsys, x, z);
	SXY_HeroFrontObjGet(fsys, &obj);
	//きのみ関連どうぐの使用チェック
	icwk->SeedInfo = SeedSys_ItemUseCheck(fsys, obj);

	//自機情報参照ポインタ
	icwk->player = fsys->player;
}

//============================================================================================
//
//	スクリプト呼び出し
//
//============================================================================================
static BOOL GMEVENT_ItemScript(GMEVENT_CONTROL * event);
//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
typedef struct {
	u32 scr_id;		///<呼び出すスクリプトのID
	u16 param0;		///<引き渡すパラメータその１
	u16 param1;		///<引き渡すパラメータその２
	u16 param2;		///<引き渡すパラメータその３
	u16 param3;		///<引き渡すパラメータその４
}CALL_SCR_WORK;

//--------------------------------------------------------------------------------------------
/**
 * @brief 
 * @param scr_id;		///<呼び出すスクリプトのID
 * @param param0;		///<引き渡すパラメータその１
 * @param param1;		///<引き渡すパラメータその２
 * @param param2;		///<引き渡すパラメータその３
 * @param param3;		///<引き渡すパラメータその４
 * @return	CALL_SCR_WORK	スクリプト呼び出し用ワーク
 */
//--------------------------------------------------------------------------------------------
static CALL_SCR_WORK * CSW_Create(u32 scr_id, u16 param0, u16 param1, u16 param2, u16 param3)
{
	CALL_SCR_WORK * csw;
	csw = sys_AllocMemory(HEAPID_EVENT, sizeof(CALL_SCR_WORK));
	csw->scr_id = scr_id;
	csw->param0 = param0;
	csw->param1 = param1;
	csw->param2 = param2;
	csw->param3 = param3;
	return csw;
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	アイテム用スクリプト起動の設定
 * @param	iuwk	アイテム使用ワーク
 * @param	icwk	アイテム使用チェックワーク
 * @param	scr_id	スクリプトID
 */
//--------------------------------------------------------------------------------------------
static void SetUpItemScript(ITEMUSE_WORK * iuwk, const ITEMCHECK_WORK * icwk, u32 scr_id)
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * mwk;

	fsys = FieldEvent_GetFieldSysWork( iuwk->event );
	mwk  = FieldEvent_GetSpecialWork( iuwk->event );

	FieldEvent_Cmd_SetMapProc( fsys );

	mwk->app_func = GMEVENT_ItemScript;
	mwk->app_wk   = CSW_Create(scr_id, iuwk->item, 0, 0, 0);
	mwk->seq      = FLD_MENU_SEQ_BLACK_IN_EVCHG;
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	アイテム用スクリプト起動の設定（便利ボタン）
 * @param	iuwk	アイテム使用ワーク
 * @param	icwk	アイテム使用チェックワーク
 * @param	scr_id	スクリプトID
 */
//--------------------------------------------------------------------------------------------
static void SetUpItemScriptCnv( CONV_WORK * wk, u32 scr_id )
{
	void * work = CSW_Create(scr_id, wk->item, 0, 0, 0);
	FieldEvent_Set( wk->fsys, GMEVENT_ItemScript, work );
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	アイテム用スクリプトの呼び出しイベント
 * @param	event	イベント制御ワークへのポインタ
 * @return	BOOL	TRUEでイベント終了、FALSEでイベント続行
 */
//--------------------------------------------------------------------------------------------
static BOOL GMEVENT_ItemScript(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	CALL_SCR_WORK * csw = FieldEvent_GetSpecialWork(event);
	int * seq = FieldEvent_GetSeqWork(event);
	FIELD_OBJ_PTR obj;
	switch (*seq) {
	case 0:
		SXY_HeroFrontObjGet(fsys, &obj);
		EventCall_Script(event, csw->scr_id, obj, NULL);
		*(u16*)(GetEvScriptWorkMemberAdrs(fsys,ID_EVSCR_WK_PARAM0)) = csw->param0;
		*(u16*)(GetEvScriptWorkMemberAdrs(fsys,ID_EVSCR_WK_PARAM1)) = csw->param1;
		*(u16*)(GetEvScriptWorkMemberAdrs(fsys,ID_EVSCR_WK_PARAM2)) = csw->param2;
		*(u16*)(GetEvScriptWorkMemberAdrs(fsys,ID_EVSCR_WK_PARAM3)) = csw->param3;

		(*seq) ++;
		break;
	case 1:
		sys_FreeMemoryEz(csw);
		return TRUE;
	}
	return FALSE;
}

//============================================================================================
//	001:回復
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * アイテム使用関数：回復
 *
 * @param	iuwk	アイテム使用ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void ItemUse_Recover( ITEMUSE_WORK * iuwk, const ITEMCHECK_WORK * icwk)
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * mwk;
	PLIST_DATA * pld;

	fsys = FieldEvent_GetFieldSysWork( iuwk->event );
	mwk  = FieldEvent_GetSpecialWork( iuwk->event );
	pld  = sys_AllocMemory( HEAPID_WORLD, sizeof(PLIST_DATA) );

	memset( pld, 0, sizeof(PLIST_DATA) );
	pld->pp     = SaveData_GetTemotiPokemon( fsys->savedata );
	pld->myitem = SaveData_GetMyItem( fsys->savedata );
	pld->mailblock = SaveData_GetMailBlock( fsys->savedata );
	pld->cfg = SaveData_GetConfig( fsys->savedata );
	pld->tvwk = SaveData_GetTvWork( fsys->savedata );
	pld->scwk = &mwk->skill_check;
	pld->type = PL_TYPE_SINGLE;
	pld->mode = PL_MODE_ITEMUSE;
	pld->fsys = fsys;
	pld->item = iuwk->item;
	pld->ret_sel = iuwk->use_poke;
	GameSystem_StartSubProc( fsys, &PokeListProcData, pld );

	mwk->app_wk = pld;
	FldMenu_AppWaitFuncSet( mwk, FldMenu_PokeListEnd );
}


//============================================================================================
//	002:タウンマップ
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * アイテム使用関数：タウンマップ
 *
 * @param	iuwk	アイテム使用ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void ItemUse_Townmap( ITEMUSE_WORK * iuwk, const ITEMCHECK_WORK * icwk)
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * mwk;

	fsys = FieldEvent_GetFieldSysWork( iuwk->event );
	mwk  = FieldEvent_GetSpecialWork( iuwk->event );

	mwk->app_wk = FieldMenuTMap_SetProc( fsys );
	FldMenu_AppWaitFuncSet( mwk, FldMenu_TownMapEnd );
}


//--------------------------------------------------------------------------------------------
/**
 * 便利ボタン使用関数：タウンマップ
 *
 * @param	wk	便利ボタンワーク
 *
 * @return	TRUE（便利ボタンワークを解放しない）
 */
//--------------------------------------------------------------------------------------------
static BOOL ItemCnv_Townmap( CONV_WORK * wk )
{
	ConvFuncCallSet( wk, ConvCall_Townmap );
	return TRUE;
}

static void * ConvCall_Townmap( void * fsys )
{
	return FieldMenuTMap_SetProc( fsys );
}



//============================================================================================
//	003:探検セット
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * アイテム使用関数：探検セット
 *
 * @param	iuwk	アイテム使用ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void ItemUse_Tankenset( ITEMUSE_WORK * iuwk, const ITEMCHECK_WORK * icwk)
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * mwk;

	fsys = FieldEvent_GetFieldSysWork( iuwk->event );
	mwk  = FieldEvent_GetSpecialWork( iuwk->event );

	FieldEvent_Cmd_SetMapProc( fsys );

	//mwk->app_func = GMEVENT_UgChange;
	mwk->app_func = GMEVENT_GroundToUnderGround;
	mwk->app_wk   = MakeUGChangeWork( fsys );
	mwk->seq      = FLD_MENU_SEQ_BLACK_IN_EVCHG;

	fsys->startmenu_pos = 0;		// メニュー位置クリア
}

//--------------------------------------------------------------------------------------------
/**
 * 便利ボタン使用関数：探検セット
 *
 * @param	wk	便利ボタンワーク
 *
 * @return	FALSE（便利ボタンワーク解放）
 */
//--------------------------------------------------------------------------------------------
static BOOL ItemCnv_Tankenset( CONV_WORK * wk )
{
	void * work = MakeUGChangeWork( wk->fsys );
	FieldOBJSys_MovePauseAll( wk->fsys->fldobjsys );
	FieldEvent_Set( wk->fsys, GMEVENT_GroundToUnderGround, work );
	wk->fsys->startmenu_pos = 0;		// メニュー位置クリア
	return FALSE;
}

//--------------------------------------------------------------------------------------------
/**
 * アイテム使用チェック関数：探検セット
 *
 * @param	icwk	アイテム使用チェックワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static u32 ItemUseCheck_Tankenset( const ITEMCHECK_WORK * icwk )
{
	// フィールドか
	if( !(ZoneData_IsSinouField(icwk->zone_id)) ){
		return ITEMCHECK_FALSE;
	}

	// サイクリングロードチェック
	if( Player_MoveBitCheck_CyclingRoad( icwk->player ) == TRUE ){
		return ITEMCHECK_FALSE;
	}

	// ポケパーク・サファリチェック
	if( SysFlag_SafariCheck( SaveData_GetEventWork(icwk->fsys->savedata) ) == TRUE ||
		SysFlag_PokeParkCheck( SaveData_GetEventWork(icwk->fsys->savedata) ) == TRUE ){
		return ITEMCHECK_FALSE;
	}

	// なみのり中チェック
	if( Player_FormGet( icwk->player ) == HERO_FORM_SWIM ){
		return ITEMCHECK_FALSE;
	}

	// 橋の上
	if( MATR_IsBridge( icwk->NowAttr ) == TRUE ){
		return ITEMCHECK_FALSE;
	}

	{	// OBJと被らないか
		u16	x, z;
		
		x = Player_NowGPosXGet( icwk->fsys->player );
		z = Player_NowGPosZGet( icwk->fsys->player );

		if( EventData_CheckIntoUGPos( icwk->fsys, x, z ) == FALSE ){
			return ITEMCHECK_FALSE;
		}
	}

	return ITEMCHECK_TRUE;
}


//============================================================================================
//	004:自転車
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * アイテム使用関数：自転車
 *
 * @param	iuwk	アイテム使用ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void ItemUse_Cycle( ITEMUSE_WORK * iuwk, const ITEMCHECK_WORK * icwk)
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * mwk;

	fsys = FieldEvent_GetFieldSysWork( iuwk->event );
	mwk  = FieldEvent_GetSpecialWork( iuwk->event );

	FieldEvent_Cmd_SetMapProc( fsys );
	mwk->app_func = GMEVENT_ItemUseCycle;
	mwk->app_wk   = NULL;
	mwk->seq      = FLD_MENU_SEQ_BLACK_IN_EVCHG;
}

//--------------------------------------------------------------------------------------------
/**
 * 便利ボタン使用関数：自転車
 *
 * @param	wk	便利ボタンワーク
 *
 * @return	FALSE（便利ボタンワーク解放）
 */
//--------------------------------------------------------------------------------------------
static BOOL ItemCnv_Cycle( CONV_WORK * wk )
{
	FieldEvent_Set( wk->fsys, GMEVENT_ItemUseCycle, NULL );
	return FALSE;
}

//--------------------------------------------------------------------------------------------
/**
 * アイテム使用イベント：自転車
 *
 * @param	event	フィールドイベント用パラメータ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static BOOL GMEVENT_ItemUseCycle( GMEVENT_CONTROL * event )
{
	FIELDSYS_WORK * fsys;
	int * seq;

	fsys = FieldEvent_GetFieldSysWork( event );
	seq = FieldEvent_GetSeqWork( event );

	switch (*seq) {
	case 0:
		(*seq) ++;
		break;
	case 1:
		if( Player_FormGet( fsys->player ) == HERO_FORM_CYCLE ){

			FieldOBJ_MovePauseClear( Player_FieldOBJGet( fsys->player ) );
			Player_RequestSet( fsys->player, HERO_REQBIT_NORMAL );
			Player_Request( fsys->player );

			//先に形状を戻してから、BGM処理を呼ぶ！(060803)
			Snd_FieldBgmSetSpecial( fsys, 0 );					//クリア
			Snd_FadeOutNextPlayCall(
				fsys, Snd_FieldBgmNoGet(fsys,fsys->location->zone_id), BGM_FADE_FIELD_MODE );
		}else{

			//先にBGM処理を呼んでから、形状を自転車にする！(060803)
			Snd_FieldBgmSetSpecial( fsys, SEQ_BICYCLE );		//セット
			Snd_FadeOutNextPlayCall( fsys, SEQ_BICYCLE, BGM_FADE_FIELD_MODE );

			FieldOBJ_MovePauseClear( Player_FieldOBJGet( fsys->player ) );
			Player_RequestSet( fsys->player, HERO_REQBIT_CYCLE );
			Player_Request( fsys->player );

			//自転車乗ったら揺れ草クリア
			SwayGrass_InitSwayGrass(fsys->SwayGrass);
		}
		(*seq) ++;
		break;
	case 2:
		//FieldOBJ_MovePauseClear( Player_FieldOBJGet( fsys->player ) );
		//Player_Request( fsys->player );
		(*seq) ++;
		break;
	case 3:
		FieldOBJSys_MovePauseAllClear( fsys->fldobjsys );
		return TRUE;
	}

	return FALSE;
}

//--------------------------------------------------------------------------------------------
/**
 * アイテム使用チェック関数：自転車
 *
 * @param	icwk	アイテム使用チェックワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static u32 ItemUseCheck_Cycle( const ITEMCHECK_WORK * icwk )
{
	// 連れ歩き時は使用不可
	if( icwk->Companion == TRUE ){
		return ITEMCHECK_ERR_COMPANION;
	}

	// サイクリングロードチェック
	if( Player_MoveBitCheck_CyclingRoad( icwk->player ) == TRUE ){
		return ITEMCHECK_ERR_CYCLE_OFF;
	}

	{	// 一本橋
		FIELD_OBJ_PTR	fldobj = Player_FieldOBJGet( icwk->player );
		if( FieldOBJ_MapAttrKindCheck_BridgeV( fldobj, icwk->NowAttr ) == TRUE ||
			FieldOBJ_MapAttrKindCheck_BridgeH( fldobj, icwk->NowAttr ) == TRUE ){
			return ITEMCHECK_ERR_CYCLE_OFF;
		}
	}

	// 長い草 / 沼 / 沼草
	if( MATR_IsLongGrass( icwk->NowAttr ) == TRUE ||
		MATR_IsSwamp( icwk->NowAttr ) == TRUE ||
		MATR_IsSwampGrass( icwk->NowAttr ) == TRUE ){
		return ITEMCHECK_FALSE;
	}

	// ゾーンチェック
	if( ZoneData_GetEnableBicycleFlag(icwk->zone_id) == FALSE ){
		return ITEMCHECK_FALSE;
	}

	//なみのり状態かどうか
	if( icwk->PlayerForm == HERO_FORM_SWIM ){
		return ITEMCHECK_FALSE;
	}

	return ITEMCHECK_TRUE;
}


//============================================================================================
//	005:冒険ノート
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * アイテム使用関数：冒険ノート
 *
 * @param	iuwk	アイテム使用ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void ItemUse_FantasyNote( ITEMUSE_WORK * iuwk, const ITEMCHECK_WORK * icwk)
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * mwk;

	fsys = FieldEvent_GetFieldSysWork( iuwk->event );
	mwk  = FieldEvent_GetSpecialWork( iuwk->event );

	FieldFantasyNote_SetProc( fsys, NULL );
	FldMenu_AppWaitFuncSet( mwk, FldMenu_FantasyNoteEnd );
}

//--------------------------------------------------------------------------------------------
/**
 * 便利ボタン使用関数：冒険ノート
 *
 * @param	wk	便利ボタンワーク
 *
 * @return	TRUE（便利ボタンワークを解放しない）
 */
//--------------------------------------------------------------------------------------------
static BOOL ItemCnv_FantasyNote( CONV_WORK * wk )
{
	ConvFuncCallSet( wk, ConvCall_FantasyNote );
	return TRUE;
}

static void * ConvCall_FantasyNote( void * fsys )
{
	FieldFantasyNote_SetProc( fsys, NULL );
	return NULL;
}


//============================================================================================
//	006:技マシン
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * アイテム使用関数：技マシン
 *
 * @param	iuwk	アイテム使用ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void ItemUse_WazaMachine( ITEMUSE_WORK * iuwk, const ITEMCHECK_WORK * icwk)
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * mwk;
	PLIST_DATA * pld;

	fsys = FieldEvent_GetFieldSysWork( iuwk->event );
	mwk  = FieldEvent_GetSpecialWork( iuwk->event );
	pld  = sys_AllocMemory( HEAPID_WORLD, sizeof(PLIST_DATA) );

	memset( pld, 0, sizeof(PLIST_DATA) );
	pld->pp     = SaveData_GetTemotiPokemon( fsys->savedata );
	pld->myitem = SaveData_GetMyItem( fsys->savedata );
	pld->mailblock = SaveData_GetMailBlock( fsys->savedata );
	pld->cfg = SaveData_GetConfig( fsys->savedata );
	pld->scwk = &mwk->skill_check;
	pld->type = PL_TYPE_SINGLE;
	pld->mode = PL_MODE_WAZASET;
	pld->fsys = fsys;
	pld->item = iuwk->item;
	pld->ret_sel = iuwk->use_poke;
	pld->waza = GetWazaNoItem( iuwk->item );
	GameSystem_StartSubProc( fsys, &PokeListProcData, pld );

	mwk->app_wk = pld;
	FldMenu_AppWaitFuncSet( mwk, FldMenu_PokeListEnd );
}


//============================================================================================
//	007:メール
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * アイテム使用関数：メール
 *
 * @param	iuwk	アイテム使用ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void ItemUse_Mail( ITEMUSE_WORK * iuwk, const ITEMCHECK_WORK * icwk)
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * mwk;
	MAIL_PARAM * mail;

	fsys = FieldEvent_GetFieldSysWork( iuwk->event );
	mwk  = FieldEvent_GetSpecialWork( iuwk->event );
	mail = FieldMailView_InitCall(
				fsys, MAILBLOCK_NULL, ItemMailDesignGet(iuwk->item), HEAPID_WORLD );

	mwk->tmp_wk = FieldMenu_MailWorkMake( iuwk->item, FM_MAIL_MODE_VIEW, 0 );
	mwk->app_wk = mail;
	FldMenu_AppWaitFuncSet( mwk, FldMenu_MailEnd );
}


//============================================================================================
//	008:きのみ
//============================================================================================
//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
static u32 ItemUseCheck_Kinomi(const ITEMCHECK_WORK * icwk)
{
	return ITEMCHECK_TRUE;
}

//--------------------------------------------------------------------------------------------
/**
 * アイテム使用関数：きのみ
 *
 * @param	iuwk	アイテム使用ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void ItemUse_Kinomi( ITEMUSE_WORK * iuwk, const ITEMCHECK_WORK * icwk)
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * mwk;
	FIELD_OBJ_PTR	obj;

	fsys = FieldEvent_GetFieldSysWork( iuwk->event );
	mwk  = FieldEvent_GetSpecialWork( iuwk->event );
	if (icwk->SeedInfo & SEEDITEMCHK_USE_SEED) {
		SetUpItemScript(iuwk, icwk, SCRID_KINOMI_BAG_KINOMI);
	} else {
		ItemUse_Recover( iuwk, icwk );
	}
}

//--------------------------------------------------------------------------------------------
/**
 * きのみ使用タイプ取得
 *
 * @param	iuwk	アイテム使用ワーク
 *
 * @retval	"TRUE = 埋める"
 * @retval	"FALSE = それ以外"
 */
//--------------------------------------------------------------------------------------------
BOOL ItemUse_KinomiTypeCheck( const ITEMCHECK_WORK * icwk )
{
	if (icwk->SeedInfo & SEEDITEMCHK_USE_SEED) {
		return TRUE;
	}
	return FALSE;
}


//============================================================================================
//	009:ポルトケース
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * アイテム使用関数：ポルトケース
 *
 * @param	iuwk	アイテム使用ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void ItemUse_PrtCase( ITEMUSE_WORK * iuwk, const ITEMCHECK_WORK * icwk)
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * mwk;
	PORUTO_PARAM * prt;

	fsys = FieldEvent_GetFieldSysWork( iuwk->event );
	mwk  = FieldEvent_GetSpecialWork( iuwk->event );
	prt  = FieldPorutoCase_InitCall( fsys, HEAPID_WORLD );

	mwk->app_wk = prt;
	FldMenu_AppWaitFuncSet( mwk, FldMenu_PorutoCaseEnd );
}

//--------------------------------------------------------------------------------------------
/**
 * 便利ボタン使用関数：ポルトケース
 *
 * @param	wk	便利ボタンワーク
 *
 * @return	TRUE（便利ボタンワークを解放しない）
 */
//--------------------------------------------------------------------------------------------
static BOOL ItemCnv_PrtCase( CONV_WORK * wk )
{
	ConvFuncCallSet( wk, ConvCall_PrtCase );
	return TRUE;
}

static void * ConvCall_PrtCase( void * fsys )
{
	return FieldPorutoCase_InitCall( fsys, HEAPID_WORLD );
}

//============================================================================================
//	010:友達手帳
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * アイテム使用関数：友達手帳
 *
 * @param	iuwk	アイテム使用ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void ItemUse_FriendBook( ITEMUSE_WORK * iuwk, const ITEMCHECK_WORK * icwk)
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * mwk;

	fsys = FieldEvent_GetFieldSysWork( iuwk->event );
	mwk  = FieldEvent_GetSpecialWork( iuwk->event );

	WifiNote_SetProc( fsys, fsys->savedata );

	mwk->app_wk = NULL;
	FldMenu_AppWaitFuncSet( mwk, FldMenu_FriendBookEnd );
}

//--------------------------------------------------------------------------------------------
/**
 * 便利ボタン使用関数：友達手帳
 *
 * @param	wk	便利ボタンワーク
 *
 * @return	TRUE（便利ボタンワークを解放しない）
 */
//--------------------------------------------------------------------------------------------
static BOOL ItemCnv_FriendBook( CONV_WORK * wk )
{
	ConvFuncCallSet( wk, ConvCall_FriendBook );
	return TRUE;
}

static void * ConvCall_FriendBook( void * fsys )
{
	WifiNote_SetProc( fsys, ((FIELDSYS_WORK *)fsys)->savedata );
	return NULL;
}


//============================================================================================
//	011:ポケサーチャー
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * アイテム使用関数：ポケサーチャー
 *
 * @param	iuwk	アイテム使用ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void ItemUse_PokeSearcher( ITEMUSE_WORK * iuwk, const ITEMCHECK_WORK * icwk)
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * mwk;
	int *seq;

	fsys = FieldEvent_GetFieldSysWork( iuwk->event );
	mwk  = FieldEvent_GetSpecialWork( iuwk->event );

	seq = sys_AllocMemoryLo(HEAPID_WORLD,sizeof(int));
	(*seq) = 0;	
	FieldEvent_Cmd_SetMapProc( fsys );
	mwk->app_func = SwayGrass_SetupEvent;
	mwk->app_wk   = seq;
	mwk->seq      = FLD_MENU_SEQ_BLACK_IN_EVCHG;
}

//--------------------------------------------------------------------------------------------
/**
 * 便利ボタン使用関数：ポケサーチャー
 *
 * @param	wk		便利ボタンワーク
 *
 * @return	FALSE（便利ボタンワーク解放）
 */
//--------------------------------------------------------------------------------------------
static BOOL ItemCnv_PokeSearcher( CONV_WORK * wk )
{
	int * seq = sys_AllocMemoryLo(HEAPID_WORLD,sizeof(int));
	*seq = 0;
	FieldEvent_Set( wk->fsys, SwayGrass_SetupEvent, seq );
	return FALSE;
}

//--------------------------------------------------------------------------------------------
/**
 * アイテム使用チェック関数：ポケサーチャー
 *
 * @param	icwk	アイテム使用チェックワーク
 *
 * @return	BOOL	TRUE:使える　FALSE:使えない
 */
//--------------------------------------------------------------------------------------------
static u32 ItemUseCheck_PokeSearcher( const ITEMCHECK_WORK * icwk )
{
	//連れ歩き時は使用不可
	if( icwk->Companion == TRUE ){
		return ITEMCHECK_ERR_COMPANION;
	}
	//自転車乗ってるときは使用不可
	if ( Player_FormGet( icwk->fsys->player ) == HERO_FORM_CYCLE ){
		return ITEMCHECK_FALSE;
	}
	//草アトリビュート以外は使用不可
	if (!MATR_IsGrass(icwk->NowAttr)){
		return ITEMCHECK_FALSE;
	}
	return ITEMCHECK_TRUE;
}


//============================================================================================
//	012:じょうろ
//============================================================================================
//--------------------------------------------------------------------------------------------
/**
 * @brief	アイテム使用関数：じょうろ
 */
//--------------------------------------------------------------------------------------------
static void ItemUse_Zyouro( ITEMUSE_WORK * iuwk, const ITEMCHECK_WORK * icwk)
{
	SetUpItemScript(iuwk, icwk, SCRID_KINOMI_BAG_ZYOURO);
}

//--------------------------------------------------------------------------------------------
/**
 * 便利ボタン使用関数：じょうろ
 *
 * @param	wk		便利ボタンワーク
 *
 * @return	FALSE（便利ボタンワーク解放）
 */
//--------------------------------------------------------------------------------------------
static BOOL ItemCnv_Zyouro( CONV_WORK * wk )
{
	SetUpItemScriptCnv( wk, SCRID_KINOMI_BAG_ZYOURO );
	return FALSE;
}


//--------------------------------------------------------------------------------------------
/**
 * @brief	アイテム使用チェック関数：じょうろ
 */
//--------------------------------------------------------------------------------------------
static u32 ItemUseCheck_Zyouro( const ITEMCHECK_WORK * icwk )
{
	// 連れ歩き時は使用不可
	if( icwk->Companion == TRUE ){
		return ITEMCHECK_ERR_COMPANION;
	}

	if (icwk->SeedInfo & SEEDITEMCHK_USE_ZYOURO) {
		return ITEMCHECK_TRUE;
	} else {
		return ITEMCHECK_FALSE;
	}
}

//============================================================================================
//	013:コヤシ
//============================================================================================
//--------------------------------------------------------------------------------------------
/**
 * @brief	アイテム使用関数：コヤシ
 */
//--------------------------------------------------------------------------------------------
static void ItemUse_Compost( ITEMUSE_WORK * iuwk, const ITEMCHECK_WORK * icwk)
{
	SetUpItemScript(iuwk, icwk, SCRID_KINOMI_BAG_COMPOST);
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	アイテム使用チェック関数：コヤシ
 */
//--------------------------------------------------------------------------------------------
static u32 ItemUseCheck_Compost( const ITEMCHECK_WORK * icwk )
{
	if (icwk->SeedInfo & SEEDITEMCHK_USE_COMPOST) {
		return ITEMCHECK_TRUE;
	} else {
		return ITEMCHECK_FALSE;
	}
}

//============================================================================================
//	014:甘い蜜
//============================================================================================
//--------------------------------------------------------------------------------------------
/**
 * @brief	アイテム使用関数：甘い蜜
 */
//--------------------------------------------------------------------------------------------
static void ItemUse_SweetHoney( ITEMUSE_WORK * iuwk, const ITEMCHECK_WORK * icwk)
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * mwk;
	EVENT_AMAIKAORI_EFF_WORK	*work;
	int size;

	fsys = FieldEvent_GetFieldSysWork( iuwk->event );
	mwk  = FieldEvent_GetSpecialWork( iuwk->event );

	FieldEvent_Cmd_SetMapProc( fsys );
	
	size = FLDMAP_Amaikaori_WorkSize();
	work = sys_AllocMemoryLo( HEAPID_WORLD, size );
	memset(work, 0, size);
	
	mwk->app_func = FLDMAP_AmaikaoriEvent;
	mwk->app_wk   = work;
	mwk->seq      = FLD_MENU_SEQ_BLACK_IN_EVCHG;
	//アイテム減らす
	MyItem_SubItem( SaveData_GetMyItem(fsys->savedata), iuwk->item, 1, HEAPID_WORLD );	
}


//============================================================================================
//	015:バトルサーチャー
//============================================================================================
//--------------------------------------------------------------------------------------------
/**
 * @brief	アイテム使用関数：バトルサーチャー
 */
//--------------------------------------------------------------------------------------------
static void ItemUse_BtlSearcher( ITEMUSE_WORK * iuwk, const ITEMCHECK_WORK * icwk)
{
	SetUpItemScript(iuwk, icwk, SCRID_BTL_SEARCHER);
}

//--------------------------------------------------------------------------------------------
/**
 * 便利ボタン使用関数：バトルサーチャー
 *
 * @param	wk		便利ボタンワーク
 *
 * @return	FALSE（便利ボタンワーク解放）
 */
//--------------------------------------------------------------------------------------------
static BOOL ItemCnv_BtlSearcher( CONV_WORK * wk )
{
	SetUpItemScriptCnv( wk, SCRID_BTL_SEARCHER );
	return FALSE;
}

//--------------------------------------------------------------------------------------------
/**
 * アイテム使用チェック関数：バトルサーチャー
 *
 * @param	icwk	アイテム使用チェックワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static u32 ItemUseCheck_BtlSearcher( const ITEMCHECK_WORK * icwk )
{
	if( ZoneData_IsSinouField(icwk->zone_id) ){
		return ITEMCHECK_TRUE;
	}
	return ITEMCHECK_FALSE;
}


//============================================================================================
//	016:ボロい釣竿
//============================================================================================
//--------------------------------------------------------------------------------------------
/**
 * @brief	アイテム使用関数：ボロい釣竿
 */
//--------------------------------------------------------------------------------------------
static void ItemUse_FishingRodBad( ITEMUSE_WORK * iuwk, const ITEMCHECK_WORK * icwk)
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * mwk;
	
	fsys = FieldEvent_GetFieldSysWork( iuwk->event );
	mwk  = FieldEvent_GetSpecialWork( iuwk->event );
	
	FieldEvent_Cmd_SetMapProc( fsys );
	mwk->app_func = GMEVENT_Fishing;
	mwk->app_wk   = EventWorkSet_Fishing( fsys, HEAPID_WORLD, FISHINGROD_BAD );
	mwk->seq      = FLD_MENU_SEQ_BLACK_IN_EVCHG;
}

//--------------------------------------------------------------------------------------------
/**
 * 便利ボタン使用関数：ボロい釣竿
 * @param	wk	便利ボタンワーク
 * @return	FALSE（便利ボタンワーク解放）
 */
//--------------------------------------------------------------------------------------------
static BOOL ItemCnv_FishingRodBad( CONV_WORK * wk )
{
	void *work = EventWorkSet_Fishing( wk->fsys, HEAPID_FIELD, FISHINGROD_BAD );
	FieldEvent_Set( wk->fsys, GMEVENT_Fishing, work );
	return FALSE;
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	アイテム使用関数：良い釣竿
 */
//--------------------------------------------------------------------------------------------
static void ItemUse_FishingRodGood( ITEMUSE_WORK * iuwk, const ITEMCHECK_WORK * icwk)
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * mwk;
	
	fsys = FieldEvent_GetFieldSysWork( iuwk->event );
	mwk  = FieldEvent_GetSpecialWork( iuwk->event );
	
	FieldEvent_Cmd_SetMapProc( fsys );
	mwk->app_func = GMEVENT_Fishing;
	mwk->app_wk   = EventWorkSet_Fishing( fsys, HEAPID_WORLD, FISHINGROD_GOOD );
	mwk->seq      = FLD_MENU_SEQ_BLACK_IN_EVCHG;
}

//--------------------------------------------------------------------------------------------
/**
 * 便利ボタン使用関数：良い釣竿
 * @param	wk	便利ボタンワーク
 * @return	FALSE（便利ボタンワーク解放）
 */
//--------------------------------------------------------------------------------------------
static BOOL ItemCnv_FishingRodGood( CONV_WORK * wk )
{
	void *work = EventWorkSet_Fishing( wk->fsys, HEAPID_FIELD, FISHINGROD_GOOD );
	FieldEvent_Set( wk->fsys, GMEVENT_Fishing, work );
	return FALSE;
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	アイテム使用関数：凄い釣竿
 */
//--------------------------------------------------------------------------------------------
static void ItemUse_FishingRodGreat( ITEMUSE_WORK * iuwk, const ITEMCHECK_WORK * icwk)
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * mwk;
	
	fsys = FieldEvent_GetFieldSysWork( iuwk->event );
	mwk  = FieldEvent_GetSpecialWork( iuwk->event );
	
	FieldEvent_Cmd_SetMapProc( fsys );
	mwk->app_func = GMEVENT_Fishing;
	mwk->app_wk   = EventWorkSet_Fishing( fsys, HEAPID_WORLD, FISHINGROD_GREAT );
	mwk->seq      = FLD_MENU_SEQ_BLACK_IN_EVCHG;
}

//--------------------------------------------------------------------------------------------
/**
 * 便利ボタン使用関数：凄い釣竿
 * @param	wk	便利ボタンワーク
 * @return	FALSE（便利ボタンワーク解放）
 */
//--------------------------------------------------------------------------------------------
static BOOL ItemCnv_FishingRodGreat( CONV_WORK * wk )
{
	void *work = EventWorkSet_Fishing( wk->fsys, HEAPID_FIELD, FISHINGROD_GREAT );
	FieldEvent_Set( wk->fsys, GMEVENT_Fishing, work );
	return FALSE;
}

//--------------------------------------------------------------------------------------------
/**
 * アイテム使用チェック関数：釣竿
 *
 * @param	icwk	アイテム使用チェックワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static u32 ItemUseCheck_FishingRod( const ITEMCHECK_WORK * icwk )
{
	// 連れ歩き時は使用不可
	if( icwk->Companion == TRUE ){
		return ITEMCHECK_ERR_COMPANION;
	}

	// 目の前が水
	if( MATR_IsWater(icwk->FrontAttr) == TRUE ){
		// 橋の上にいなければOK
		if( MATR_IsBridge( icwk->NowAttr ) == TRUE ||
			MATR_IsBridgeFlag( icwk->NowAttr ) == TRUE ){
			FIELD_OBJ_PTR	fldobj = Player_FieldOBJGet( icwk->player );
			if( FieldOBJ_StatusBitCheck_Bridge(fldobj) == TRUE ){
				return ITEMCHECK_FALSE;
			}
		}
		return ITEMCHECK_TRUE;
	}

	return ITEMCHECK_FALSE;
}


//============================================================================================
//	019:バッグ内で使用する道具
//		コインケース、アクセサリー入れ、シール入れ、ポイントカード
//============================================================================================
typedef struct {
	GF_BGL_BMPWIN win;	// ウィンドウデータ
	STRBUF * msg;		// メッセージ
	u16	midx;			// メッセージインデックス
	u16	seq;			// シーケンス
}BAGMSG_WORK;

#define	BAGMSG_TMP_SIZ		( 128 )


//--------------------------------------------------------------------------------------------
/**
 * 便利ボタン使用関数：バッグ内で使用する道具
 *
 * @param	wk	便利ボタンワーク
 *
 * @return	FALSE（便利ボタンワークを解放）
 */
//--------------------------------------------------------------------------------------------
static BOOL ItemCnv_BagMsgItem( CONV_WORK * wk )
{
	BAGMSG_WORK * bmwk = sys_AllocMemory( HEAPID_WORLD, sizeof(BAGMSG_WORK) );
	bmwk->seq = 0;

	bmwk->msg = STRBUF_Create( BAGMSG_TMP_SIZ, HEAPID_WORLD );
	BAG_ItemUseMsgSet(
		wk->fsys->savedata, bmwk->msg,
		MyItem_CnvButtonItemGet( SaveData_GetMyItem(wk->fsys->savedata) ), HEAPID_WORLD );

	FieldEvent_Set( wk->fsys, GMEVENT_BagMsgItem, bmwk );
	return FALSE;
}

static BOOL GMEVENT_BagMsgItem( GMEVENT_CONTROL * event )
{
	FIELDSYS_WORK * fsys;
	BAGMSG_WORK * wk;

	fsys = FieldEvent_GetFieldSysWork( event );
	wk   = FieldEvent_GetSpecialWork( event );

	switch( wk->seq ){
	case 0:
		FieldOBJSys_MovePauseAll( fsys->fldobjsys );

/*
		wk->msg = STRBUF_Create( BAGMSG_TMP_SIZ, HEAPID_WORLD );

		BAG_ItemUseMsgSet(
			fsys->savedata, wk->msg,
			MyItem_CnvButtonItemGet( SaveData_GetMyItem(fsys->savedata) ), HEAPID_WORLD );
*/

		FldTalkBmpAdd( fsys->bgl, &wk->win, FLD_MBGFRM_FONT );
		{
			const CONFIG * cfg = SaveData_GetConfig( fsys->savedata );
			FieldTalkWinPut( &wk->win, cfg );
			wk->midx = FieldTalkMsgStart( &wk->win, wk->msg, cfg, 1 );
		}
		wk->seq++;
		break;

	case 1:
		if( FldTalkMsgEndCheck( wk->midx ) == 1 ){
			if(sys.trg & (PAD_KEY_UP|PAD_KEY_DOWN|PAD_KEY_LEFT|PAD_KEY_RIGHT|PAD_BUTTON_A|PAD_BUTTON_B)){
				BmpTalkWinClear( &wk->win, WINDOW_TRANS_ON );
				wk->seq++;
			}
		}
		break;

	case 2:
		FieldOBJSys_MovePauseAllClear( fsys->fldobjsys );
		GF_BGL_BmpWinDel( &wk->win );
		STRBUF_Delete( wk->msg );
		sys_FreeMemoryEz( wk );
		return TRUE;
	}

	return FALSE;
}


//============================================================================================
//	020:進化
//============================================================================================

static void ItemUse_Evolution( ITEMUSE_WORK * iuwk, const ITEMCHECK_WORK * icwk )
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * mwk;
	PLIST_DATA * pld;

	fsys = FieldEvent_GetFieldSysWork( iuwk->event );
	mwk  = FieldEvent_GetSpecialWork( iuwk->event );
	pld  = sys_AllocMemory( HEAPID_WORLD, sizeof(PLIST_DATA) );

	memset( pld, 0, sizeof(PLIST_DATA) );
	pld->pp     = SaveData_GetTemotiPokemon( fsys->savedata );
	pld->myitem = SaveData_GetMyItem( fsys->savedata );
	pld->mailblock = SaveData_GetMailBlock( fsys->savedata );
	pld->cfg = SaveData_GetConfig( fsys->savedata );
	pld->tvwk = SaveData_GetTvWork( fsys->savedata );
	pld->scwk = &mwk->skill_check;
	pld->type = PL_TYPE_SINGLE;
	pld->mode = PL_MODE_SHINKA;
	pld->item = iuwk->item;
	pld->ret_sel = iuwk->use_poke;
	GameSystem_StartSubProc( fsys, &PokeListProcData, pld );

	mwk->app_wk = pld;
	FldMenu_AppWaitFuncSet( mwk, FldMenu_PokeListEnd );
}


//============================================================================================
//	021	:穴抜けの紐
//============================================================================================
//--------------------------------------------------------------------------------------------
/**
 * @brief	アイテム使用関数：穴抜けの紐
 */
//--------------------------------------------------------------------------------------------
static void ItemUse_Ananuke( ITEMUSE_WORK * iuwk, const ITEMCHECK_WORK * icwk)
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * mwk;
	
	fsys = FieldEvent_GetFieldSysWork( iuwk->event );
	mwk  = FieldEvent_GetSpecialWork( iuwk->event );
	
	FieldEvent_Cmd_SetMapProc( fsys );
	mwk->app_func = GMEVENT_AnanukeMapChangeInit;
	mwk->app_wk   = NULL;
	mwk->seq      = FLD_MENU_SEQ_BLACK_IN_EVCHG;
	//アイテム減らす
	MyItem_SubItem( SaveData_GetMyItem(fsys->savedata), iuwk->item, 1, HEAPID_WORLD );
}

//--------------------------------------------------------------------------------------------
/**
 * アイテム使用チェック関数：穴抜けの紐
 *
 * @param	icwk	アイテム使用チェックワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static u32 ItemUseCheck_Ananuke( const ITEMCHECK_WORK * icwk )
{
	// 連れ歩き時は使用不可
	if( icwk->Companion == TRUE ){
		return ITEMCHECK_ERR_COMPANION;
	}

	if( ZoneData_IsDungeon(icwk->zone_id) == TRUE &&
		ZoneData_GetEnableEscapeFlag(icwk->zone_id) == TRUE ){
		return ITEMCHECK_TRUE;
	}

	return ITEMCHECK_FALSE;
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	穴抜けの紐ワーク初期化→穴抜けイベントへ
 */
//--------------------------------------------------------------------------------------------
static BOOL GMEVENT_AnanukeMapChangeInit( GMEVENT_CONTROL *event )
{
	FIELDSYS_WORK *fsys = FieldEvent_GetFieldSysWork( event );
	void *work = EventWorkSet_AnanukeMapChange( fsys, HEAPID_WORLD );
	FieldEvent_Change( event, GMEVENT_AnanukeMapChange, work );
	return( FALSE );
}


//============================================================================================
//	022:てんかいのふえ
//============================================================================================
//--------------------------------------------------------------------------------------------
/**
 * アイテム使用関数：てんかいのふえ
 *
 * @param	iuwk	アイテム使用ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void ItemUse_Tenkainofue( ITEMUSE_WORK * iuwk, const ITEMCHECK_WORK * icwk)
{
	SetUpItemScript(iuwk, icwk, SCRID_TENKAINOFUE);

}

//--------------------------------------------------------------------------------------------
/**
 * 便利ボタン使用関数：てんかいのふえ
 *
 * @param	wk		便利ボタンワーク
 *
 * @return	FALSE（便利ボタンワーク解放）
 */
//--------------------------------------------------------------------------------------------
static BOOL ItemCnv_Tenkainofue( CONV_WORK * wk )
{
	SetUpItemScriptCnv( wk, SCRID_TENKAINOFUE );
	return FALSE;
}

//--------------------------------------------------------------------------------------------
/**
 * アイテム使用チェック関数：てんかいのふえ
 *
 * @param	icwk	アイテム使用チェックワーク
 *
 * @return	BOOL	TRUE:使える　FALSE:使えない
 */
//--------------------------------------------------------------------------------------------
static u32 ItemUseCheck_Tenkainofue( const ITEMCHECK_WORK * icwk )
{
	EVENTWORK * ev = SaveData_GetEventWork(icwk->fsys->savedata);
	//ゲームクリア後か？
	if (SysFlag_GameClearCheck(ev) == FALSE) {
		return ITEMCHECK_FALSE;
	}
	//配布イベントフラグは正常に設定されているか？
	if (SysWork_HaihuEventWorkCheck(ev, HAIHUEVENT_ID_D05) == FALSE) {
		return ITEMCHECK_FALSE;
	}
	//全国図鑑入手後か?
	if (ZukanWork_GetZenkokuZukanFlag(SaveData_GetZukanWork(icwk->fsys->savedata)) == FALSE) {
		return ITEMCHECK_FALSE;
	}

	if ( !ZoneData_IsUseTenkainofueZone(icwk->zone_id) ){
		return ITEMCHECK_FALSE;
	}
	
	return ITEMCHECK_TRUE;
}












//============================================================================================
//	便利ボタン
//============================================================================================
// 画面切り替えイベントシーケンス
enum {
	SEQ_FADEOUT_SET = 0,	// フェードアウトセット
	SEQ_FADEOUT_WAIT,		// フェードアウト待ち
	SEQ_END_WAIT,			// サブプロセス終了待ち
	SEQ_RCV_WAIT,			// フィールドマッププロセス開始待ち
	SEQ_FADEIN_WAIT,		// フェードイン待ち
};

static void ItemCnv_ErrorMsgSet( CONV_WORK * wk, u32 err );


//--------------------------------------------------------------------------------------------
/**
 * 便利ボタン起動処理
 *
 * @param	repw	フィールドワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
BOOL FieldConvButtonEventInit( FIELDSYS_WORK * repw )
{
	CONV_WORK * wk;
	ITEMCNV_FUNC	cnv;
	ITEMCHECK_FUNC	check;
	u16	item;
	u16	id;
	BOOL	ret;

	// バトルタワーのサロンでは使用できない
	if( BtlTower_IsSalon(repw) == TRUE ){ return FALSE; }

	// ポケパークでは使用できない
	if( SysFlag_PokeParkCheck(SaveData_GetEventWork(repw->savedata)) == TRUE ){
		return FALSE;
	}

	item  = (u16)MyItem_CnvButtonItemGet( SaveData_GetMyItem(repw->savedata) );
//	if( item == 0 ){ return FALSE; }

	id    = (u16)ItemParamGet( item, ITEM_PRM_FIELD, HEAPID_WORLD );
	check = (ITEMCHECK_FUNC)ItemUse_FuncGet( ITEMUSE_PRM_CHECKFUNC, id );
	cnv   = (ITEMCNV_FUNC)ItemUse_FuncGet( ITEMUSE_PRM_CNVFUNC, id );

	if( cnv == NULL ){ return FALSE; }	// 便利ボタンから使用できない

	wk = sys_AllocMemory( HEAPID_WORLD, sizeof(CONV_WORK) );
	memset( wk, 0, sizeof(CONV_WORK) );
	wk->fsys = repw;
	wk->item = item;
	ItemUse_CheckWorkMake( repw, &wk->icwk );

	ret = FALSE;
	if( check == NULL ){
		ret = cnv( wk );
	}else{
		u32 err = check( &wk->icwk );
		if( err == ITEMCHECK_TRUE ){
			ret = cnv( wk );
		}else{
			ItemCnv_ErrorMsgSet( wk, err );
		}
	}

	if( ret == FALSE ){
		sys_FreeMemoryEz( wk );
	}

	return TRUE;
}


static void ItemCnv_ErrorMsgSet( CONV_WORK * wk, u32 err )
{
	BAGMSG_WORK * bmwk = sys_AllocMemory( HEAPID_WORLD, sizeof(BAGMSG_WORK) );
	bmwk->seq = 0;

	bmwk->msg = STRBUF_Create( BAGMSG_TMP_SIZ, HEAPID_WORLD );

	BAG_ItemUseErrorMsgSet(
		SaveData_GetMyStatus( wk->fsys->savedata ), bmwk->msg, wk->item, err, HEAPID_WORLD );

	FieldEvent_Set( wk->fsys, GMEVENT_BagMsgItem, bmwk );
}


//--------------------------------------------------------------------------------------------
/**
 * 画面切り替えアイテム用共通イベント
 *
 * @param	event
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static BOOL GMEVENT_ConvButtonCommon( GMEVENT_CONTROL * event )
{
	FIELDSYS_WORK * fsys;
	CONV_WORK * wk;

	fsys = FieldEvent_GetFieldSysWork( event );
	wk   = FieldEvent_GetSpecialWork( event );

	switch( wk->seq ){
	case SEQ_FADEOUT_SET:	// フェードアウトセット
		FieldOBJSys_MovePauseAll( fsys->fldobjsys );
		FieldFadeWipeSet( FLD_DISP_BRIGHT_BLACKOUT );
		wk->seq = SEQ_FADEOUT_WAIT;
		break;

	case SEQ_FADEOUT_WAIT:	// フェードアウト待ち
		if( WIPE_SYS_EndCheck() ){
			wk->app_wk = wk->call( fsys );
			wk->seq = SEQ_END_WAIT;
		}
		break;

	case SEQ_END_WAIT:		// サブプロセス終了待ち
		if( FieldEvent_Cmd_WaitSubProcEnd( fsys ) ) {
			break;
		}
		if( wk->app_wk != NULL ){
			if(wk->call == ConvCall_PrtCase){
				//ポルトケースの時は専用メモリ解放関数を呼ぶ 06.07.05 iwasawa
				PorutoSys_ReleaseCallWork(wk->app_wk);
			}else{
				sys_FreeMemoryEz( wk->app_wk );
			}
		}
		FieldEvent_Cmd_SetMapProc( fsys );
		wk->seq = SEQ_RCV_WAIT;
		break;

	case SEQ_RCV_WAIT:		// フィールドマッププロセス開始待ち
		if( FieldEvent_Cmd_WaitMapProcStart(fsys) ) {
			FieldOBJSys_MovePauseAll( fsys->fldobjsys );
			FieldFadeWipeSet( FLD_DISP_BRIGHT_BLACKIN );
			wk->seq = SEQ_FADEIN_WAIT;
		}
		break;

	case SEQ_FADEIN_WAIT:	// フェードイン待ち
		if( WIPE_SYS_EndCheck() ){
			FieldOBJSys_MovePauseAllClear( fsys->fldobjsys );
			sys_FreeMemoryEz( wk );
			return TRUE;
		}
	}

	return FALSE;
}

//--------------------------------------------------------------------------------------------
/**
 * 画面切り替えアイテム用共通イベントセット
 *
 * @param	wk		便利ボタンワーク
 * @param	call	フェードアウト後に呼ばれる処理
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void ConvFuncCallSet( CONV_WORK * wk, CNVFUNC_CALL call )
{
	wk->call = call;
	FieldEvent_Set( wk->fsys, GMEVENT_ConvButtonCommon, wk );
}
