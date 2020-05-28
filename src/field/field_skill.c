//============================================================================================
/**
 * @file	field_skill.c
 * @brief	フィールド技処理（秘伝技など）
 * @author	Hiroyuki Nakamura
 * @date	2005.12.01
 */
//============================================================================================
#include "common.h"

#include "system/procsys.h"
#include "system/window.h"
#include "system/msgdata.h"
#include "system/bmp_menu.h"
#include "system/clact_tool.h"
#include "msgdata/msg.naix"
#include "msgdata/msg_debug_nakahiro.h"
#include "application/townmap.h"

#include "fieldsys.h"
#include "fieldmap.h"
#include "field_event.h"
#include "field_clact.h"
#include "fld_menu.h"
#include "talk_msg.h"
#include "script.h"
#include "sysflag.h"
#include "zonedata.h"
#include "map_mode.h"

#define	FIELD_SKILL_H_GLOBAL
#include "field/field_skill.h"
#include "field_skill_local.h"
#include "field_skill_prm.h"

#include "field_ananuke.h"
#include "field_amaikaori.h"
#include "../fielddata/script/perap_def.h"
#include "../fielddata/script/hiden_def.h"

#include "sxy.h"
#include "fieldobj.h"
#include "player.h"
#include "situation_local.h"
#include "weather_sys.h"

//============================================================================================
//	定数定義
//============================================================================================
// 使用関数データ
typedef struct {
	SKILLUSE_FUNC	use_func;
	SKILLCHECK_FUNC	check_func;
}SKILLUSE_FUNC_DATA;


//============================================================================================
//	プロトタイプ宣言
//============================================================================================
static int SkillCheck_Sorawotobu( const SKILLCHECK_WORK * scwk );
static void SkillUse_Sorawotobu( SKILLUSE_WORK * suwk, const SKILLCHECK_WORK * scwk );

static int SkillCheck_Teleport( const SKILLCHECK_WORK * scwk );
static void SkillUse_Teleport( SKILLUSE_WORK * suwk, const SKILLCHECK_WORK * scwk );
static BOOL GMEVENT_TeleportMapChangeInit( GMEVENT_CONTROL *event );

static int SkillCheck_Naminori( const SKILLCHECK_WORK * scwk);
static void SkillUse_Naminori( SKILLUSE_WORK * suwk, const SKILLCHECK_WORK * scwk );
static BOOL GMEVENT_Naminori(GMEVENT_CONTROL * event);

static int SkillCheck_Takinobori( const SKILLCHECK_WORK * scwk);
static void SkillUse_Takinobori( SKILLUSE_WORK * suwk, const SKILLCHECK_WORK * scwk );
static BOOL GMEVENT_Takinobori(GMEVENT_CONTROL * event);

static int SkillCheck_RockClimb( const SKILLCHECK_WORK * scwk);
static void SkillUse_RockClimb( SKILLUSE_WORK * suwk, const SKILLCHECK_WORK * scwk );
static BOOL GMEVENT_RockClimb(GMEVENT_CONTROL * event);

static int SkillCheck_Flash( const SKILLCHECK_WORK * scwk);
static void SkillUse_Flash( SKILLUSE_WORK * suwk, const SKILLCHECK_WORK * scwk );
static BOOL GMEVENT_Flash(GMEVENT_CONTROL * event);

static int SkillCheck_Kiribarai( const SKILLCHECK_WORK * scwk);
static void SkillUse_Kiribarai( SKILLUSE_WORK * suwk, const SKILLCHECK_WORK * scwk );
static BOOL GMEVENT_Kiribarai(GMEVENT_CONTROL * event);

static int SkillCheck_Iwakudaki( const SKILLCHECK_WORK * scwk);
static void SkillUse_Iwakudaki( SKILLUSE_WORK * suwk, const SKILLCHECK_WORK * scwk );
static BOOL GMEVENT_Iwakudaki(GMEVENT_CONTROL * event);

static int SkillCheck_Kairiki( const SKILLCHECK_WORK * scwk);
static void SkillUse_Kairiki( SKILLUSE_WORK * suwk, const SKILLCHECK_WORK * scwk );
static BOOL GMEVENT_Kairiki(GMEVENT_CONTROL * event);

static int SkillCheck_Anawohoru( const SKILLCHECK_WORK * scwk );
static void SkillUse_Anawohoru( SKILLUSE_WORK * suwk, const SKILLCHECK_WORK * scwk );
static BOOL GMEVENT_AnawohoruMapChangeInit( GMEVENT_CONTROL *event );

static int SkillCheck_Amaikaori( const SKILLCHECK_WORK * scwk );
static void SkillUse_Amaikaori( SKILLUSE_WORK * suwk, const SKILLCHECK_WORK * scwk );

static int SkillCheck_Osyaberi( const SKILLCHECK_WORK * scwk );
static void SkillUse_Osyaberi( SKILLUSE_WORK * suwk, const SKILLCHECK_WORK * scwk );
static BOOL GMEVENT_OsyaberiCall( GMEVENT_CONTROL * event );

static int SkillCheck_Iaigiri( const SKILLCHECK_WORK * scwk);
static void SkillUse_Iaigiri( SKILLUSE_WORK * suwk, const SKILLCHECK_WORK * scwk );
static BOOL GMEVENT_Iaigiri(GMEVENT_CONTROL * event);


//============================================================================================
//	グローバル変数
//============================================================================================
// 使用関数テーブル
static const SKILLUSE_FUNC_DATA SkillFuncTable[] =
{
	{ SkillUse_Iaigiri,		SkillCheck_Iaigiri },		// 00 : いあいぎり
	{ SkillUse_Sorawotobu,	SkillCheck_Sorawotobu },	// 01 : そらをとぶ
	{ SkillUse_Naminori,	SkillCheck_Naminori },		// 02 : なみのり
	{ SkillUse_Kairiki,		SkillCheck_Kairiki },		// 03 : かいりき
	{ SkillUse_Kiribarai,	SkillCheck_Kiribarai },		// 04 : きりばらい
	{ SkillUse_Iwakudaki,	SkillCheck_Iwakudaki },		// 05 : いわくだき
	{ SkillUse_Takinobori,	SkillCheck_Takinobori },	// 06 : たきのぼり
	{ SkillUse_RockClimb,	SkillCheck_RockClimb },		// 07 : ロッククライム
	{ SkillUse_Flash,		SkillCheck_Flash },			// 08 : フラッシュ
	{ SkillUse_Teleport,	SkillCheck_Teleport },		// 09 : テレポート
	{ SkillUse_Anawohoru,	SkillCheck_Anawohoru },		// 10 : あなをほる
	{ SkillUse_Amaikaori,	SkillCheck_Amaikaori },		// 11 : あまいかおり
	{ SkillUse_Osyaberi,	SkillCheck_Osyaberi },		// 12 : おしゃべり
};


//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
static inline BOOL IsEnableSkill(const SKILLCHECK_WORK * scwk, int skill_id)
{
	if ((scwk->enable_skill & (1 << skill_id)) != 0) {
		return TRUE;
	} else {
		return FALSE;
	}
}

// バッジチェック
static inline BOOL BadgeCheck( const SKILLCHECK_WORK * scwk, int badge )
{
	return MyStatus_GetBadgeFlag( SaveData_GetMyStatus(scwk->fsys->savedata), badge );
}

// 連れ歩きチェック
static inline BOOL CompanionCheck( const SKILLCHECK_WORK * scwk )
{
	return SysFlag_PairCheck( SaveData_GetEventWork(scwk->fsys->savedata) );
}

// サファリ・ポケパークチェック
static inline BOOL ParkCheck( const SKILLCHECK_WORK * scwk )
{
	if( SysFlag_SafariCheck( SaveData_GetEventWork(scwk->fsys->savedata) ) == TRUE ||
		SysFlag_PokeParkCheck(SaveData_GetEventWork(scwk->fsys->savedata)) == TRUE ){
		return TRUE;
	}
	return FALSE;
}

// ポケパークチェック
static inline BOOL PokeParkCheck( const SKILLCHECK_WORK * scwk )
{
	if( SysFlag_PokeParkCheck(SaveData_GetEventWork(scwk->fsys->savedata)) == TRUE ){
		return TRUE;
	}
	return FALSE;
}

// コロシアム・ユニオンルームチェック
static inline BOOL MapModeUseChack( const SKILLCHECK_WORK * scwk )
{
	if( scwk->fsys->MapMode == MAP_MODE_COLOSSEUM || scwk->fsys->MapMode == MAP_MODE_UNION ){
		return FALSE;
	}
	return TRUE;
}


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
u32 FieldSkill_FuncGet( u16 prm, u16 id )
{
	if( prm == FIELDSKILL_PRM_USEFUNC ){
		return (u32)SkillFuncTable[id].use_func;
	}
	return (u32)SkillFuncTable[id].check_func;
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
void FieldSkill_CheckWorkMake( FIELDSYS_WORK * fsys, SKILLCHECK_WORK * scwk )
{
	FIELD_OBJ_PTR obj;
	int gx, gz;
	int fattr;
	int nattr;

	scwk->fsys = fsys;
	scwk->zone_id = fsys->location->zone_id;
	scwk->enable_skill = 0;

	SXY_HeroFrontObjGet(fsys, &obj);
	scwk->obj = obj;
	if (obj != NULL) {
		switch (FieldOBJ_OBJCodeGet(obj)) {
		case ROCK:
			scwk->enable_skill |= (1 << FLD_SKILL_KAIRIKI);
			break;
		case BREAKROCK:
			scwk->enable_skill |= (1 << FLD_SKILL_IWAKUDAKI);
			break;
		case TREE:
			scwk->enable_skill |= (1 << FLD_SKILL_IAIGIRI);
			break;
		}
	}
	// 現在地のアトリビュート
	gx = Player_NowGPosXGet( fsys->player );
	gz = Player_NowGPosZGet( fsys->player );
	nattr = GetAttributeLSB(fsys, gx, gz);
	// 自機前のアトリビュート
	Player_DirFrontGridPosGet(fsys->player, &gx, &gz);
	fattr = GetAttributeLSB(fsys, gx, gz);
//	if (Player_EventAttrCheck_Naminori(fsys->player,mattr)) {
	if (Player_EventAttrCheck_Naminori(fsys->player,nattr,fattr)) {
		scwk->enable_skill |= (1 << FLD_SKILL_NAMINORI);
	}
	if (Player_EventAttrCheck_KabeNobori(fattr, Player_DirGet(fsys->player))) {
		scwk->enable_skill |= (1 << FLD_SKILL_ROCKCLIMB);
	}
	if (MATR_IsWaterFall(fattr)) {
		scwk->enable_skill |= (1 << FLD_SKILL_TAKINOBORI);
	}
	switch (Situation_GetWeatherID(SaveData_GetSituation(fsys->savedata))) {
	case WEATHER_SYS_MIST1:
		scwk->enable_skill |= (1 << FLD_SKILL_KIRIBARAI);
		break;
	case WEATHER_SYS_FLASH:
		scwk->enable_skill |= (1 << FLD_SKILL_FLASH);
		break;
	}
}

//============================================================================================
//============================================================================================
//--------------------------------------------------------------
///秘伝わざスクリプト起動用ワーク
//--------------------------------------------------------------
typedef struct {
	u32 magic;
	FIELD_OBJ_PTR obj;
	SKILLUSE_WORK suwk;
}HIDEN_SCR_WORK;

#define	HSW_MAGIC_NUMBER	0x19740205		//あっきーの誕生日

//--------------------------------------------------------------
/**
 * @brief	秘伝わざスクリプト起動用ワーク生成
 */
//--------------------------------------------------------------
static HIDEN_SCR_WORK * HSW_Create(const SKILLUSE_WORK * suwk, const SKILLCHECK_WORK * scwk)
{
	HIDEN_SCR_WORK * hsw = sys_AllocMemory(HEAPID_EVENT, sizeof(HIDEN_SCR_WORK));
	hsw->magic = HSW_MAGIC_NUMBER;
	hsw->obj = scwk->obj;
	hsw->suwk = *suwk;
	return hsw;
}

//--------------------------------------------------------------
/**
 * @brief	秘伝わざスクリプト起動用ワーク消去
 */
//--------------------------------------------------------------
static void HSW_Delete(HIDEN_SCR_WORK * hsw)
{
	GF_ASSERT(hsw->magic == HSW_MAGIC_NUMBER);
	sys_FreeMemoryEz(hsw);
}


//============================================================================================
//	00 : いあいぎり
//============================================================================================
// 技使用チェック関数
static int SkillCheck_Iaigiri( const SKILLCHECK_WORK * scwk)
{
	// コロシアム・ユニオンルームチェック
	if( MapModeUseChack( scwk ) == FALSE ){
		return FIELDSKILL_USE_FALSE;
	}

	// バッジチェック
	if( BadgeCheck( scwk, BADGE_ID_C04 ) == FALSE ){
		return FIELDSKILL_NO_BADGE;
	}

	if (IsEnableSkill(scwk, FLD_SKILL_IAIGIRI)) {
		return FIELDSKILL_USE_TRUE;
	} else {
		return FIELDSKILL_USE_FALSE;
	}
}

// 技使用関数
static void SkillUse_Iaigiri( SKILLUSE_WORK * suwk, const SKILLCHECK_WORK * scwk )
{
	FLD_MENU * mwk;
	HIDEN_SCR_WORK * hsw;

	mwk  = FieldEvent_GetSpecialWork( suwk->event );
	hsw = HSW_Create(suwk, scwk);
		
	FieldEvent_Cmd_SetMapProc( scwk->fsys );

	mwk->app_func = GMEVENT_Iaigiri;
	mwk->app_wk   = hsw;
	mwk->seq      = FLD_MENU_SEQ_BLACK_IN_EVCHG;
}

static BOOL GMEVENT_Iaigiri(GMEVENT_CONTROL * event)
{
	HIDEN_SCR_WORK * hsw = FieldEvent_GetSpecialWork(event);
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);

	EventChange_Script(event, SCRID_HIDEN_IAIGIRI_MENU, hsw->obj);
	EvScript_SetParam(fsys, hsw->suwk.poke_pos, 0, 0, 0);
	HSW_Delete( hsw );
	return FALSE;
}


//============================================================================================
//	01 : そらをとぶ
//============================================================================================
// 技使用チェック関数
static int SkillCheck_Sorawotobu( const SKILLCHECK_WORK * scwk )
{
	// コロシアム・ユニオンルームチェック
	if( MapModeUseChack( scwk ) == FALSE ){
		return FIELDSKILL_USE_FALSE;
	}

	// バッジチェック
	if( BadgeCheck( scwk, BADGE_ID_C07 ) == FALSE ){
		return FIELDSKILL_NO_BADGE;
	}

	//マップごとの指定チェック
	if( ZoneData_GetEnableFlyFlag( scwk->zone_id ) == FALSE ){
		return FIELDSKILL_USE_FALSE;
	}

	// 連れ歩き
	if( CompanionCheck( scwk ) == TRUE ){
		return FIELDSKILL_COMPANION;
	}

	// サファリ・ポケパーク
	if( ParkCheck( scwk ) == TRUE ){
		return FIELDSKILL_USE_FALSE;
	}

	return FIELDSKILL_USE_TRUE;
}

// 技使用関数
static void SkillUse_Sorawotobu( SKILLUSE_WORK * suwk, const SKILLCHECK_WORK * scwk )
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * mwk;

	fsys = FieldEvent_GetFieldSysWork( suwk->event );
	mwk  = FieldEvent_GetSpecialWork( suwk->event );

	{
		u32 * sel_pos;

		// 選択したポケモン位置を退避
		sel_pos     = (u32 *)sys_AllocMemory( HEAPID_WORLD, 4 );
		*sel_pos    = suwk->poke_pos;
		mwk->tmp_wk = (void *)sel_pos;
	}

	mwk->app_wk = sys_AllocMemory( HEAPID_WORLD, sizeof(TOWNMAP_PARAM) );
	FieldTMap_CallDataSet( fsys, mwk->app_wk, TMAP_MJUMP );
	//このフラグをONにすると、到着フラグ無視で飛べるがPM_DEBUGの中でしか使えない
//	((TOWNMAP_PARAM *)mwk->app_wk)->debug_f = TRUE;	// デバッグモードフラグON
	FieldTMap_SetProc( fsys, mwk->app_wk );
	FldMenu_AppWaitFuncSet( mwk, FldMenu_SorawotobuEnd );
}


//============================================================================================
//	02 : なみのり
//============================================================================================

// 技使用チェック関数
static int SkillCheck_Naminori( const SKILLCHECK_WORK * scwk)
{
	// コロシアム・ユニオンルームチェック
	if( MapModeUseChack( scwk ) == FALSE ){
		return FIELDSKILL_USE_FALSE;
	}

	// バッジチェック
	if( BadgeCheck( scwk, BADGE_ID_C05 ) == FALSE ){
		return FIELDSKILL_NO_BADGE;
	}

	// なみのり中
	if( Player_FormGet( scwk->fsys->player ) == HERO_FORM_SWIM ){
		return FIELDSKILL_PLAYER_SWIM;
	}

	if( !(IsEnableSkill(scwk, FLD_SKILL_NAMINORI)) ){
		return FIELDSKILL_USE_FALSE;
	}

	// 連れ歩き
	if( CompanionCheck( scwk ) == TRUE ){
		return FIELDSKILL_COMPANION;
	}

	return FIELDSKILL_USE_TRUE;

/*
	if (IsEnableSkill(scwk, FLD_SKILL_NAMINORI)) {
		return FIELDSKILL_USE_TRUE;
	} else {
		return FIELDSKILL_USE_FALSE;
	}
*/
}

// 技使用関数
static void SkillUse_Naminori( SKILLUSE_WORK * suwk, const SKILLCHECK_WORK * scwk )
{
	FLD_MENU * mwk;
	HIDEN_SCR_WORK * hsw;

	mwk  = FieldEvent_GetSpecialWork( suwk->event );
	hsw = HSW_Create(suwk, scwk);
		
	FieldEvent_Cmd_SetMapProc( scwk->fsys );

	mwk->app_func = GMEVENT_Naminori;
	mwk->app_wk   = hsw;
	mwk->seq      = FLD_MENU_SEQ_BLACK_IN_EVCHG;
}

static BOOL GMEVENT_Naminori(GMEVENT_CONTROL * event)
{
	HIDEN_SCR_WORK * hsw = FieldEvent_GetSpecialWork(event);
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);

	EventChange_Script(event, SCRID_HIDEN_NAMINORI_MENU, NULL);
	EvScript_SetParam(fsys, hsw->suwk.poke_pos, 0, 0, 0);
	HSW_Delete( hsw );
	return FALSE;
}


//============================================================================================
//	03 : かいりき
//============================================================================================

// 技使用チェック関数
static int SkillCheck_Kairiki( const SKILLCHECK_WORK * scwk)
{
	// コロシアム・ユニオンルームチェック
	if( MapModeUseChack( scwk ) == FALSE ){
		return FIELDSKILL_USE_FALSE;
	}

	// バッジチェック
	if( BadgeCheck( scwk, BADGE_ID_C02 ) == FALSE ){
		return FIELDSKILL_NO_BADGE;
	}

	if (IsEnableSkill(scwk, FLD_SKILL_KAIRIKI)) {
		return FIELDSKILL_USE_TRUE;
	} else {
		return FIELDSKILL_USE_FALSE;
	}
}

// 技使用関数
static void SkillUse_Kairiki( SKILLUSE_WORK * suwk, const SKILLCHECK_WORK * scwk )
{
	FLD_MENU * mwk;
	HIDEN_SCR_WORK * hsw;

	mwk  = FieldEvent_GetSpecialWork( suwk->event );
	hsw = HSW_Create(suwk, scwk);
		
	FieldEvent_Cmd_SetMapProc( scwk->fsys );

	mwk->app_func = GMEVENT_Kairiki;
	mwk->app_wk   = hsw;
	mwk->seq      = FLD_MENU_SEQ_BLACK_IN_EVCHG;
}

static BOOL GMEVENT_Kairiki(GMEVENT_CONTROL * event)
{
	HIDEN_SCR_WORK * hsw = FieldEvent_GetSpecialWork(event);
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);

	EventChange_Script(event, SCRID_HIDEN_KAIRIKI_MENU, hsw->obj);
	EvScript_SetParam(fsys, hsw->suwk.poke_pos, 0, 0, 0);
	HSW_Delete( hsw );
	return FALSE;
}


//============================================================================================
//	04 : きりばらい
//============================================================================================

// 技使用チェック関数
static int SkillCheck_Kiribarai( const SKILLCHECK_WORK * scwk)
{
	// コロシアム・ユニオンルームチェック
	if( MapModeUseChack( scwk ) == FALSE ){
		return FIELDSKILL_USE_FALSE;
	}

	// バッジチェック
	if( BadgeCheck( scwk, BADGE_ID_C06 ) == FALSE ){
		return FIELDSKILL_NO_BADGE;
	}

	if (IsEnableSkill(scwk, FLD_SKILL_KIRIBARAI)) {
		return FIELDSKILL_USE_TRUE;
	} else {
		return FIELDSKILL_USE_FALSE;
	}
}

// 技使用関数
static void SkillUse_Kiribarai( SKILLUSE_WORK * suwk, const SKILLCHECK_WORK * scwk )
{
	FLD_MENU * mwk;
	HIDEN_SCR_WORK * hsw;

	mwk  = FieldEvent_GetSpecialWork( suwk->event );
	hsw = HSW_Create(suwk, scwk);
		
	FieldEvent_Cmd_SetMapProc( scwk->fsys );

	mwk->app_func = GMEVENT_Kiribarai;
	mwk->app_wk   = hsw;
	mwk->seq      = FLD_MENU_SEQ_BLACK_IN_EVCHG;
}

static BOOL GMEVENT_Kiribarai(GMEVENT_CONTROL * event)
{
	HIDEN_SCR_WORK * hsw = FieldEvent_GetSpecialWork(event);
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);

	EventChange_Script(event, SCRID_HIDEN_KIRIBARAI_MENU, NULL);
	EvScript_SetParam(fsys, hsw->suwk.poke_pos, 0, 0, 0);
	HSW_Delete( hsw );
	return FALSE;
}


//============================================================================================
//	05 : いわくだき
//============================================================================================

// 技使用チェック関数
static int SkillCheck_Iwakudaki( const SKILLCHECK_WORK * scwk)
{
	// コロシアム・ユニオンルームチェック
	if( MapModeUseChack( scwk ) == FALSE ){
		return FIELDSKILL_USE_FALSE;
	}

	// バッジチェック
	if( BadgeCheck( scwk, BADGE_ID_C03 ) == FALSE ){
		return FIELDSKILL_NO_BADGE;
	}

	if (IsEnableSkill(scwk, FLD_SKILL_IWAKUDAKI)) {
		return FIELDSKILL_USE_TRUE;
	} else {
		return FIELDSKILL_USE_FALSE;
	}
}

// 技使用関数
static void SkillUse_Iwakudaki( SKILLUSE_WORK * suwk, const SKILLCHECK_WORK * scwk )
{
	FLD_MENU * mwk;
	HIDEN_SCR_WORK * hsw;

	mwk  = FieldEvent_GetSpecialWork( suwk->event );
	hsw = HSW_Create(suwk, scwk);
		
	FieldEvent_Cmd_SetMapProc( scwk->fsys );

	mwk->app_func = GMEVENT_Iwakudaki;
	mwk->app_wk   = hsw;
	mwk->seq      = FLD_MENU_SEQ_BLACK_IN_EVCHG;
}

static BOOL GMEVENT_Iwakudaki(GMEVENT_CONTROL * event)
{
	HIDEN_SCR_WORK * hsw = FieldEvent_GetSpecialWork(event);
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);

	EventChange_Script(event, SCRID_HIDEN_IWAKUDAKI_MENU, hsw->obj);
	EvScript_SetParam(fsys, hsw->suwk.poke_pos, 0, 0, 0);
	HSW_Delete( hsw );
	return FALSE;
}


//============================================================================================
//	06 : たきのぼり
//============================================================================================

// 技使用チェック関数
static int SkillCheck_Takinobori( const SKILLCHECK_WORK * scwk)
{
	// コロシアム・ユニオンルームチェック
	if( MapModeUseChack( scwk ) == FALSE ){
		return FIELDSKILL_USE_FALSE;
	}

	// バッジチェック
	if( BadgeCheck( scwk, BADGE_ID_C08 ) == FALSE ){
		return FIELDSKILL_NO_BADGE;
	}

	if (IsEnableSkill(scwk, FLD_SKILL_TAKINOBORI)) {
		return FIELDSKILL_USE_TRUE;
	} else {
		return FIELDSKILL_USE_FALSE;
	}
}

// 技使用関数
static void SkillUse_Takinobori( SKILLUSE_WORK * suwk, const SKILLCHECK_WORK * scwk )
{
	FLD_MENU * mwk;
	HIDEN_SCR_WORK * hsw;

	mwk  = FieldEvent_GetSpecialWork( suwk->event );
	hsw = HSW_Create(suwk, scwk);
		
	FieldEvent_Cmd_SetMapProc( scwk->fsys );

	mwk->app_func = GMEVENT_Takinobori;
	mwk->app_wk   = hsw;
	mwk->seq      = FLD_MENU_SEQ_BLACK_IN_EVCHG;
}

static BOOL GMEVENT_Takinobori(GMEVENT_CONTROL * event)
{
	HIDEN_SCR_WORK * hsw = FieldEvent_GetSpecialWork(event);
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);

	EventChange_Script(event, SCRID_HIDEN_TAKINOBORI_MENU, NULL);
	EvScript_SetParam(fsys, hsw->suwk.poke_pos, 0, 0, 0);
	HSW_Delete( hsw );
	return FALSE;
}


//============================================================================================
//	07 : ロッククライム
//============================================================================================

// 技使用チェック関数
static int SkillCheck_RockClimb( const SKILLCHECK_WORK * scwk)
{
	// コロシアム・ユニオンルームチェック
	if( MapModeUseChack( scwk ) == FALSE ){
		return FIELDSKILL_USE_FALSE;
	}

	// バッジチェック
	if( BadgeCheck( scwk, BADGE_ID_C09 ) == FALSE ){
		return FIELDSKILL_NO_BADGE;
	}

	if( !(IsEnableSkill(scwk, FLD_SKILL_ROCKCLIMB)) ){
		return FIELDSKILL_USE_FALSE;
	}

	// 連れ歩き
	if( CompanionCheck( scwk ) == TRUE ){
		return FIELDSKILL_COMPANION;
	}

	return FIELDSKILL_USE_TRUE;

/*
	if (IsEnableSkill(scwk, FLD_SKILL_ROCKCLIMB)) {
		return FIELDSKILL_USE_TRUE;
	} else {
		return FIELDSKILL_USE_FALSE;
	}
*/
}

// 技使用関数
static void SkillUse_RockClimb( SKILLUSE_WORK * suwk, const SKILLCHECK_WORK * scwk )
{
	FLD_MENU * mwk;
	HIDEN_SCR_WORK * hsw;

	mwk  = FieldEvent_GetSpecialWork( suwk->event );
	hsw = HSW_Create(suwk, scwk);
		
	FieldEvent_Cmd_SetMapProc( scwk->fsys );

	mwk->app_func = GMEVENT_RockClimb;
	mwk->app_wk   = hsw;
	mwk->seq      = FLD_MENU_SEQ_BLACK_IN_EVCHG;
}

static BOOL GMEVENT_RockClimb(GMEVENT_CONTROL * event)
{
	HIDEN_SCR_WORK * hsw = FieldEvent_GetSpecialWork(event);
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);

	EventChange_Script(event, SCRID_HIDEN_KABENOBORI_MENU, NULL);
	EvScript_SetParam(fsys, hsw->suwk.poke_pos, 0, 0, 0);
	HSW_Delete( hsw );
	return FALSE;
}


//============================================================================================
//	08 : フラッシュ
//============================================================================================

// 技使用チェック関数
static int SkillCheck_Flash( const SKILLCHECK_WORK * scwk)
{
	// コロシアム・ユニオンルームチェック
	if( MapModeUseChack( scwk ) == FALSE ){
		return FIELDSKILL_USE_FALSE;
	}

	if (IsEnableSkill(scwk, FLD_SKILL_FLASH)) {
		return FIELDSKILL_USE_TRUE;
	} else {
		return FIELDSKILL_USE_FALSE;
	}
}

// 技使用関数
static void SkillUse_Flash( SKILLUSE_WORK * suwk, const SKILLCHECK_WORK * scwk )
{
	FLD_MENU * mwk;
	HIDEN_SCR_WORK * hsw;

	mwk  = FieldEvent_GetSpecialWork( suwk->event );
	hsw = HSW_Create(suwk, scwk);
		
	FieldEvent_Cmd_SetMapProc( scwk->fsys );

	mwk->app_func = GMEVENT_Flash;
	mwk->app_wk   = hsw;
	mwk->seq      = FLD_MENU_SEQ_BLACK_IN_EVCHG;
}

static BOOL GMEVENT_Flash(GMEVENT_CONTROL * event)
{
	HIDEN_SCR_WORK * hsw = FieldEvent_GetSpecialWork(event);
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);

	EventChange_Script(event, SCRID_HIDEN_FLASH_MENU, NULL);
	EvScript_SetParam(fsys, hsw->suwk.poke_pos, 0, 0, 0);
	HSW_Delete( hsw );
	return FALSE;
}


//============================================================================================
//	09 : テレポート
//============================================================================================
// 技使用チェック関数
static int SkillCheck_Teleport( const SKILLCHECK_WORK * scwk )
{
	// コロシアム・ユニオンルームチェック
	if( MapModeUseChack( scwk ) == FALSE ){
		return FIELDSKILL_USE_FALSE;
	}

	// マップごとの指定チェック
	if( ZoneData_GetEnableTeleportFlag( scwk->zone_id ) == FALSE ){
		return FIELDSKILL_USE_FALSE;
	}

	// 連れ歩き
	if( CompanionCheck( scwk ) == TRUE ){
		return FIELDSKILL_COMPANION;
	}

	// サファリ・ポケパーク
	if( ParkCheck( scwk ) == TRUE ){
		return FIELDSKILL_USE_FALSE;
	}

	return FIELDSKILL_USE_TRUE;
}

// 技使用関数
static void SkillUse_Teleport( SKILLUSE_WORK * suwk, const SKILLCHECK_WORK * scwk )
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * mwk;
	
	fsys = FieldEvent_GetFieldSysWork( suwk->event );
	mwk  = FieldEvent_GetSpecialWork( suwk->event );

	FieldEvent_Cmd_SetMapProc( fsys );

	{
		FLD_SKILL_PRM *skill;
		skill = F_SkillPrm_AllocMemory( HEAPID_WORLD, suwk->poke_pos, fsys->savedata );
		
		mwk->app_func = GMEVENT_TeleportMapChangeInit;
		mwk->app_wk   = skill;
		mwk->seq      = FLD_MENU_SEQ_BLACK_IN_EVCHG;
	}
}

// テレポート用ワーク初期化→テレポート使用イベントマップ遷移へ
static BOOL GMEVENT_TeleportMapChangeInit( GMEVENT_CONTROL *event )
{
	FIELDSYS_WORK *fsys = FieldEvent_GetFieldSysWork( event );
	FLD_SKILL_PRM *skill = FieldEvent_GetSpecialWork( event );
	void *work = EventWorkSet_TeleportMapChange( fsys, skill->PokeParam, HEAPID_FIELD );
	
	sys_FreeMemoryEz( skill );
	FieldEvent_Change( event, GMEVENT_TeleportMapChange, work );
	return( FALSE );
}


//============================================================================================
//	10 : あなをほる
//============================================================================================
// 技使用チェック関数
static int SkillCheck_Anawohoru( const SKILLCHECK_WORK * scwk )
{
	// コロシアム・ユニオンルームチェック
	if( MapModeUseChack( scwk ) == FALSE ){
		return FIELDSKILL_USE_FALSE;
	}

	if( !(ZoneData_IsDungeon(scwk->zone_id)==TRUE && ZoneData_GetEnableEscapeFlag(scwk->zone_id)==TRUE) ){
		return FIELDSKILL_USE_FALSE;
	}

	// 連れ歩き
	if( CompanionCheck( scwk ) == TRUE ){
		return FIELDSKILL_COMPANION;
	}

	return FIELDSKILL_USE_TRUE;

/*
	if( ZoneData_IsDungeon(scwk->zone_id) == TRUE &&
		ZoneData_GetEnableEscapeFlag(scwk->zone_id) == TRUE ){
		return FIELDSKILL_USE_TRUE;
	}

	return FIELDSKILL_USE_FALSE;
*/

}

// 技使用関数
static void SkillUse_Anawohoru( SKILLUSE_WORK * suwk, const SKILLCHECK_WORK * scwk )
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * mwk;
	
	fsys = FieldEvent_GetFieldSysWork( suwk->event );
	mwk  = FieldEvent_GetSpecialWork( suwk->event );

	FieldEvent_Cmd_SetMapProc( fsys );
	
	{
		FLD_SKILL_PRM *skill;
		skill = F_SkillPrm_AllocMemory( HEAPID_WORLD, suwk->poke_pos, fsys->savedata );
		
		mwk->app_func = GMEVENT_AnawohoruMapChangeInit;
		mwk->app_wk   = skill;
		mwk->seq      = FLD_MENU_SEQ_BLACK_IN_EVCHG;
	}
}

// 穴を掘るワーク初期化→穴を掘る使用イベントマップ遷移へ
static BOOL GMEVENT_AnawohoruMapChangeInit( GMEVENT_CONTROL *event )
{
	FIELDSYS_WORK *fsys = FieldEvent_GetFieldSysWork( event );
	FLD_SKILL_PRM *skill = FieldEvent_GetSpecialWork( event );
	void *work = EventWorkSet_AnawohoruMapChange( fsys, skill->PokeParam, HEAPID_WORLD );

	{
		void * buf = FNOTE_ActionSkillDataMake(
						FNOTE_ANAWOHORU, fsys->location->zone_id, HEAPID_FIELD );
		FNOTE_DataSave( fsys->fnote, buf, FNOTE_TYPE_ACTION );
	}

	sys_FreeMemoryEz( skill );
	FieldEvent_Change( event, GMEVENT_AnawohoruMapChange, work );
	return( FALSE );
}

//============================================================================================
//	11 : あまいかおり
//============================================================================================
// 技使用チェック関数
static int SkillCheck_Amaikaori( const SKILLCHECK_WORK * scwk )
{
	// コロシアム・ユニオンルームチェック
	if( MapModeUseChack( scwk ) == FALSE ){
		return FIELDSKILL_USE_FALSE;
	}

	// ポケパーク
	if( PokeParkCheck( scwk ) == TRUE ){
		return FIELDSKILL_USE_FALSE;
	}
	return  FIELDSKILL_USE_TRUE;
}

// 技使用関数
static void SkillUse_Amaikaori( SKILLUSE_WORK * suwk, const SKILLCHECK_WORK * scwk )
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * mwk;
	FLD_SKILL_PRM * param;
	int size;
	void * buf;
	
	fsys = FieldEvent_GetFieldSysWork( suwk->event );
	mwk  = FieldEvent_GetSpecialWork( suwk->event );
	
	param = F_SkillPrm_AllocMemory( HEAPID_WORLD, suwk->poke_pos, fsys->savedata );
	FieldEvent_Cmd_SetMapProc( fsys );
	mwk->app_func = GMEVENT_Amakikaori;
	mwk->app_wk   = param;
	mwk->seq      = FLD_MENU_SEQ_BLACK_IN_EVCHG;

	buf = FNOTE_ActionSkillDataMake( FNOTE_AMAIKAORI, fsys->location->zone_id, HEAPID_WORLD );
	FNOTE_DataSave( fsys->fnote, buf, FNOTE_TYPE_ACTION );
}


//============================================================================================
//	12 : おしゃべり
//============================================================================================
// 技使用チェック関数
static int SkillCheck_Osyaberi( const SKILLCHECK_WORK * scwk )
{
	// コロシアム・ユニオンルームチェック
	if( MapModeUseChack( scwk ) == FALSE ){
		return FIELDSKILL_USE_FALSE;
	}

	return  FIELDSKILL_USE_TRUE;
}

// 技使用関数
static void SkillUse_Osyaberi( SKILLUSE_WORK * suwk, const SKILLCHECK_WORK * scwk )
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * mwk;
	HIDEN_SCR_WORK * hsw;
	
	fsys = FieldEvent_GetFieldSysWork( suwk->event );
	mwk  = FieldEvent_GetSpecialWork( suwk->event );
	hsw  = HSW_Create(suwk, scwk);
	
	FieldEvent_Cmd_SetMapProc( fsys );

	mwk->app_func = GMEVENT_OsyaberiCall;
	mwk->app_wk   = hsw;
	mwk->seq      = FLD_MENU_SEQ_BLACK_IN_EVCHG;
}

// 「おしゃべり」スクリプト呼び出し
static BOOL GMEVENT_OsyaberiCall( GMEVENT_CONTROL * event )
{
	HIDEN_SCR_WORK * hsw = FieldEvent_GetSpecialWork(event);
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);

	EventChange_Script( event, SCRID_PERAP, NULL );
	EvScript_SetParam(fsys, hsw->suwk.poke_pos, 0, 0, 0);
	HSW_Delete( hsw );
	return FALSE;
}
