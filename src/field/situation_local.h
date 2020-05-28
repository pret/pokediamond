//============================================================================================
/**
 * @file	situation.h
 * @brief	自分状態データアクセス用ヘッダ（ローカル用）
 * @author	tamada GAME FREAK inc.
 * @date	2005.12.03
 *
 * このヘッダはsrc/field/以下のファイルからしかインクルードしてはいけない。
 */
//============================================================================================

#ifndef	__SITUATION_LOCAL_H__
#define	__SITUATION_LOCAL_H__

#include "field/situation.h"
#include "townmap_footmark.h"

//----------------------------------------------------------
//	SITUATION操作のための関数
//----------------------------------------------------------
extern LOCATION_WORK * Situation_GetNowLocation(SITUATION * st);
extern LOCATION_WORK * Situation_GetEntranceLocation(SITUATION * st);
extern LOCATION_WORK * Situation_GetBeforeLocation(SITUATION * st);
extern LOCATION_WORK * Situation_GetEscapeLocation(SITUATION * st);
extern LOCATION_WORK * Situation_GetSpecialLocation(SITUATION * st);
extern void Situation_SetSpecialLocation(SITUATION * st, LOCATION_WORK* lw);
extern u16 * Situation_GetBGMWork(SITUATION * st);
extern u16 Situation_GetWeatherID(const SITUATION * st);
extern void Situation_SetWeatherID(SITUATION * st, u16 weather_id);
extern u16 Situation_GetWarpID(const SITUATION * st);
extern void Situation_SetWarpID(SITUATION * st, u16 warp_id);
extern TOWN_MAP_FOOTMARK * Situation_GetTMFootMark(SITUATION * st);
extern int Situation_GetCameraID(const SITUATION * st);
extern void Situation_SetCameraID(SITUATION * st, int camera_id);
extern PLAYER_SAVE_DATA * Situation_GetPlayerSaveData(SITUATION * st);
extern u16 * Situation_GetSafariBallCount(SITUATION * st);
extern u16 * Situation_GetPoisonStepCount(SITUATION * st);
extern u16 * Situation_GetSafariStepCount(SITUATION * st);
extern u16 * Situation_GetRevengeStepCount(SITUATION * st);
extern u16 * Situation_GetFriendlyStepCount(SITUATION * st);

//----------------------------------------------------------
//	デバッグ用データ生成のための関数
//----------------------------------------------------------
//extern void Debug_Situation_Make(SITUATION * Situation, const STRCODE * name, int sex);

//----------------------------------------------------------
//	FieldOBJのセーブ、ロード
//----------------------------------------------------------
extern void Field_SaveFieldObj(FIELDSYS_WORK * fsys);
extern void Field_LoadFieldObj(FIELDSYS_WORK * fsys);

#endif	//	__SITUATION_LOCAL_H__

