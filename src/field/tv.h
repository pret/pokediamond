//============================================================================================
/**
 * @file	tv.h
 * @brief	
 * @date	2006.05.18
 * @author	tamada GAME FREAK inc.
 */
//============================================================================================

#ifndef	__TV_H__
#define	__TV_H__

#include "field_common.h"

#include "savedata/tv_work.h"

//============================================================================================
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	放送用データ
 */
//----------------------------------------------------------
typedef struct TVBCD TVBCD;

//extern void TVBCD_Init(TVBCD * bcd);

extern TVBCD * TVBCD_Create(FIELDSYS_WORK * fsys, TVTOPICTYPE topic_type, int index);
extern void TVBCD_Delete(TVBCD * bcd);

//extern void TVBCD_SetTopicData(TVBCD * bcd, TVTOPIC * topic);
//extern void TVBCD_SetSex(TVBCD * bcd, int sex);
//extern void TVBCD_SetRegionCode(TVBCD * bcd, int region_code);
//extern void TVBCD_SetRomVersion(TVBCD * bcd, int rom_ver);
//extern void TVBCD_SetName(TVBCD * bcd, const STRCODE * name);

extern void * TVBCD_GetTopicData(TVBCD * bcd);
extern int TVBCD_GetSex(const TVBCD * bcd);
extern int TVBCD_GetRegionCode(const TVBCD * bcd);
extern int TVBCD_GetRomVersion(const TVBCD * bcd);
extern const STRCODE * TVBCD_GetName(const TVBCD * bcd);
extern int TVBCD_GetTopicID(const TVBCD * bcd);

extern void TVBCD_CountUpBroadCast(TVBCD * bcd);
//============================================================================================
//
//
//		放送用コマンド
//
//
//============================================================================================
//--------------------------------------------------------------------
//tv_cm.c
//--------------------------------------------------------------------
//CMメッセージを取得する
extern int TVCM_ChooseID(FIELDSYS_WORK * fsys);

//--------------------------------------------------------------------
//tv_broadcast.c
//--------------------------------------------------------------------
//放送トピックをセットする
extern BOOL TV_GetProgramID(FIELDSYS_WORK * fsys, WORDSET * ws, int idx, u16 * arc_id, u16 * msg_id);

//放送状態を取得する
extern int TV_GetBroadcastStatus(FIELDSYS_WORK * fsys);

//番組ごとに決まっているメッセージIDを取得（7種類、前フリや終了など）
extern int TV_GetProgramMsg(FIELDSYS_WORK * fsys, int prog_msg_id);

//トピックを選択
extern int TV_ChooseBroadcastTopic(FIELDSYS_WORK * fsys, BOOL mine, BOOL see);
extern int TV_ChooseBroadcastTopicTotal(FIELDSYS_WORK * fsys);

//終了フラグを立てる
extern void TV_SetEndFlag(FIELDSYS_WORK * fsys);


//--------------------------------------------------------------------
//tv_topic.c
//--------------------------------------------------------------------
extern int TVTOPIC_Make(TVTOPICTYPE topic_type,
		FIELDSYS_WORK * fsys, WORDSET * ws, TVBCD * bcd, u16 * arc_id);

extern BOOL TVTOPIC_CheckLimit(TVTOPICTYPE topic_type, FIELDSYS_WORK * fsys, TVBCD * bcd);

#endif	//	__TV_H__
