//============================================================================================
/**
 * @file	situation.c
 * @brief	状況データアクセス
 * @author	tamada GAME FREAK inc.
 * @date	2005.12.03
 */
//============================================================================================

#include "common.h"
#include "system/savedata_def.h"	//SAVEDATA参照のため
#include "fieldsys.h"
#include "field/situation.h"
#include "townmap_footmark.h"

#include "system/savedata.h"

#include "situation_local.h"


#include "fieldobj_header.h"

#include "mapdata_warp.h"

//============================================================================================
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	状況データ型定義
 */
//----------------------------------------------------------
struct _SITUATION {
	LOCATION_WORK now;
	LOCATION_WORK entrance;
	LOCATION_WORK before;
	LOCATION_WORK special;
	LOCATION_WORK escape;
	//LOCATION_WORK teleport;
	u16 bgm;
	u16 weather_id;
	u16 warp_id;
	u8 camera_id;
	TOWN_MAP_FOOTMARK TownMapFootMark;
	PLAYER_SAVE_DATA	player_sv;

	u16 poison_step_count;
	u16 safari_step_count;
	u16 safari_ball_count;
	u16 friendly_step_count;
	u16 revenge_step_count;
};

//----------------------------------------------------------
//----------------------------------------------------------
struct _FIELDOBJ_SAVE{
	FIELD_OBJ_SAVE_DATA fldobj_sv[FLDOBJ_ENTRY_MAX];
};

//============================================================================================
//
//	セーブデータシステムが依存する関数
//
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	状況ワークのサイズ取得
 * @return	int		サイズ（バイト単位）
 */
//----------------------------------------------------------
int Situation_GetWorkSize(void)
{
	return sizeof(SITUATION);
}

//----------------------------------------------------------
//----------------------------------------------------------
int FieldObjSv_GetWorkSize(void)
{
	return sizeof(FIELDOBJ_SAVE);
}

//----------------------------------------------------------
//----------------------------------------------------------
void FieldObjSv_Init(FIELDOBJ_SAVE * sv)
{
	MI_CpuClear32(sv, sizeof(FIELDOBJ_SAVE));
}

//============================================================================================
//
//	状況データ操作のための関数
//
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	状況データの初期化
 * @param	st	状況ワークへのポインタ
 */
//----------------------------------------------------------
void Situation_Init(SITUATION * st)
{
	memset(st, 0, sizeof(SITUATION));
	TMFootMark_Init(&st->TownMapFootMark);
	Player_SaveDataInit(&st->player_sv);
	st->warp_id = WARPDATA_GetInitializeID();
}

//----------------------------------------------------------
/**
 * @brief	現在のLOCATION_WORKを返す
 * @param	st	状況ワークへのポインタ
 * @return	LOCATION_WORKへのポインタ
 */
//----------------------------------------------------------
LOCATION_WORK * Situation_GetNowLocation(SITUATION * st)
{
	return &st->now;
}

//----------------------------------------------------------
/**
 * @brief	直前に入った出入口を示すLOCATION_WORKへのポインタ
 * @param	st	状況ワークへのポインタ
 * @return	LOCATION_WORKへのポインタ
 */
//----------------------------------------------------------
LOCATION_WORK * Situation_GetEntranceLocation(SITUATION * st)
{
	return &st->entrance;
}

//----------------------------------------------------------
/**
 * @param	st	状況ワークへのポインタ
 */
//----------------------------------------------------------
LOCATION_WORK * Situation_GetBeforeLocation(SITUATION * st)
{
	return &st->before;
}

//----------------------------------------------------------
/**
 * @param	st	状況ワークへのポインタ
 */
//----------------------------------------------------------
LOCATION_WORK * Situation_GetEscapeLocation(SITUATION * st)
{
	return &st->escape;
}
//----------------------------------------------------------
/**
 * @brief	特殊接続情報の取得
 * @param	st	状況ワークへのポインタ
 * @return	LOCATION_WORK	特殊接続情報へのポインタ
 */
//----------------------------------------------------------
LOCATION_WORK * Situation_GetSpecialLocation(SITUATION * st)
{
	return &st->special;
}

//----------------------------------------------------------
/**
 * @brief	特殊接続情報のセット
 * @param	st	状況ワークへのポインタ
 * @param	sp	LOCATION_WORKデータのポインタ
 * @return	none
 */
//----------------------------------------------------------
void Situation_SetSpecialLocation(SITUATION * st, LOCATION_WORK* lw)
{
	st->special = *lw;
	return;
}

//----------------------------------------------------------
/**
 * @brief	BGMIDアクセス
 * @param	st	状況ワークへのポインタ
 * @param	u16	BGMIDへのポインタ
 */
//----------------------------------------------------------
u16 * Situation_GetBGMWork(SITUATION * st)
{
	return &st->bgm;
}

//----------------------------------------------------------
/**
 * @brief	天候ID取得
 * @param	st	状況ワークへのポインタ
 * @return	u16	天候IDへのポインタ
 */
//----------------------------------------------------------
u16 Situation_GetWeatherID(const SITUATION * st)
{
	return st->weather_id;
}

//----------------------------------------------------------
/**
 * @brief	天候IDセット
 * @param	st	状況ワークへのポインタ
 * @param	weather_id	天候ID
 */
//----------------------------------------------------------
void Situation_SetWeatherID(SITUATION * st, u16 weather_id)
{
	st->weather_id = weather_id;
}

//----------------------------------------------------------
/**
 * @brief	ワープIDの取得
 * @param	st	状況ワークへのポインタ
 * @return	u16	ワープID
 */
//----------------------------------------------------------
u16 Situation_GetWarpID(const SITUATION * st)
{
	return st->warp_id;
}
//----------------------------------------------------------
/**
 * @brief	ワープIDの設定
 * @param	st		状況ワークへのポインタ
 * @param	warp_id	ワープID
 */
//----------------------------------------------------------
void Situation_SetWarpID(SITUATION * st, u16 warp_id)
{
	st->warp_id = warp_id;
}

//----------------------------------------------------------
/**
 * @param	st	状況ワークへのポインタ
 */
//----------------------------------------------------------
TOWN_MAP_FOOTMARK * Situation_GetTMFootMark(SITUATION * st)
{
	return &st->TownMapFootMark;
}

//----------------------------------------------------------
/**
 * @brief	カメラ指定IDの取得
 * @param	st	状況ワークへのポインタ
 * @return	int カメラ指定のID
 */
//----------------------------------------------------------
int Situation_GetCameraID(const SITUATION * st)
{
	return st->camera_id;
}

//----------------------------------------------------------
/**
 * @brief	カメラ指定IDのセット
 * @param	st	状況ワークへのポインタ
 * @param	camera_id	カメラ指定のID
 */
//----------------------------------------------------------
void Situation_SetCameraID(SITUATION * st, int camera_id)
{
	st->camera_id = camera_id;
}

//----------------------------------------------------------
/**
 * @brief	自機セーブ情報取得
 * @param	st	状況ワークへのポインタ
 * @return	PLAYER_SAVE_DATAへのポインタ
 */
//----------------------------------------------------------
PLAYER_SAVE_DATA * Situation_GetPlayerSaveData(SITUATION * st)
{
	return &st->player_sv;
}


//----------------------------------------------------------
/**
 * @brief	サファリボールワーク取得
 * @param	st	状況ワークへのポインタ
 * @return	u16	ワークへのポインタ
 */
//----------------------------------------------------------
u16 * Situation_GetSafariBallCount(SITUATION * st)
{
	return &st->safari_ball_count;
}

//----------------------------------------------------------
/**
 * @brief	サファリ歩数ワーク取得
 * @param	st	状況ワークへのポインタ
 * @return	u16	ワークへのポインタ
 */
//----------------------------------------------------------
u16 * Situation_GetSafariStepCount(SITUATION * st)
{
	return &st->safari_step_count;
}

//----------------------------------------------------------
/**
 * @brief	毒ダメージ用歩数ワーク取得
 * @param	st	状況ワークへのポインタ
 * @return	u16	ワークへのポインタ
 */
//----------------------------------------------------------
u16 * Situation_GetPoisonStepCount(SITUATION * st)
{
	return &st->poison_step_count;
}

//----------------------------------------------------------
/**
 * @brief	再戦用歩数ワーク取得
 * @param	st	状況ワークへのポインタ
 * @return	u16	ワークへのポインタ
 */
//----------------------------------------------------------
u16 * Situation_GetRevengeStepCount(SITUATION * st)
{
	return &st->poison_step_count;
}

//----------------------------------------------------------
/**
 * @brief	再戦用歩数ワーク取得
 * @param	st	状況ワークへのポインタ
 * @return	u16	ワークへのポインタ
 */
//----------------------------------------------------------
u16 * Situation_GetFriendlyStepCount(SITUATION * st)
{
	return &st->friendly_step_count;
}

//============================================================================================
//
//	セーブデータ取得のための関数
//
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	状況データへのポインタ取得
 * @param	sv			セーブデータ保持ワークへのポインタ
 * @return	SITUATION	状況保持ワークへのポインタ
 */
//----------------------------------------------------------
SITUATION * SaveData_GetSituation(SAVEDATA * sv)
{
		SITUATION * st;
		st = SaveData_Get(sv, GMDATA_ID_SITUATION);
		return st;
}

FIELDOBJ_SAVE * SaveData_GetFieldObjSv(SAVEDATA * sv)
{
	FIELDOBJ_SAVE * fld;
	fld = SaveData_Get(sv, GMDATA_ID_FIELDOBJSV);
	return fld;
}

#if 0
FIELDOBJ_SAVE * SaveData_GetFieldObjSv2(SAVEDATA * sv)
{
	FIELDOBJ_SAVE * fld;
	fld = SaveData_Get(sv, GMDATA_ID_FIELDOBJSV2);
	return fld;
}
#endif

//----------------------------------------------------------
/**
 * @brief	フィールドOBJのセーブ
 * @param	fsys			ゲーム制御ワークへのポインタ
 */
//----------------------------------------------------------
void Field_SaveFieldObj(FIELDSYS_WORK * fsys)
{
	FIELD_OBJ_SAVE_DATA * fldobjsv;
	fldobjsv = ((FIELDOBJ_SAVE *)SaveData_GetFieldObjSv(fsys->savedata))->fldobj_sv;
	FieldOBJSys_DataSaveAll(fsys, fsys->fldobjsys, fldobjsv, FLDOBJ_ENTRY_MAX);
}

//----------------------------------------------------------
/**
 * @brief	フィールドOBJのロード
 * @param	fsys			ゲーム制御ワークへのポインタ
 */
//----------------------------------------------------------
void Field_LoadFieldObj(FIELDSYS_WORK * fsys)
{
	FIELD_OBJ_SAVE_DATA * fldobjsv;
	fldobjsv = ((FIELDOBJ_SAVE *)SaveData_GetFieldObjSv(fsys->savedata))->fldobj_sv;
	FieldOBJSys_DataLoadAll(fsys->fldobjsys, fldobjsv, FLDOBJ_ENTRY_MAX);
}

//============================================================================================
//
//	デバッグ用
//
//============================================================================================
