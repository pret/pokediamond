//============================================================================================
/**
 * @file	tv_broadcast.c
 * @brief
 * @author	tamada GAME FREAK inc.
 * @date	2006.05.17
 */
//============================================================================================

#include "common.h"

#include "fieldsys.h"

#include "savedata/tv_work.h"
#include "tv_define.h"


#include "system/pm_rtc.h"
#include "ev_time.h"

#include "tv.h"
#include "scr_tv.h"

#include "msgdata/msg.naix"

#include "system/pm_rtc.h"

#include "system/arc_tool.h"
#include "../arc/tv.naix"

#include "msgdata/msg_tv_program.h"
#include "msgdata/msg_tvcm.h"
#include "msgdata/msg_tv_interview.h"
#include "msgdata/msg_msg_tv_01.h"
#include "msgdata/msg_msg_tv_02.h"
#include "msgdata/msg_msg_tv_03.h"
#include "msgdata/msg_msg_tv_04.h"

#include "system/debug_flag.h"

#ifdef	PM_DEBUG
#define	TV_BROADCAST_DEBUG
#endif
//============================================================================================
//
//============================================================================================
//--------------------------------------------------------------------
/**
 * @brief	１番組で放送可能なトピック種類の最大値
 */
//--------------------------------------------------------------------
#define	PROG_TOPIC_MAX		8

#define	TOPIC_ARRAY_MAX		16

//--------------------------------------------------------------------
/**
 * @brief	番組内容データの長さ
 *
 * topic_typeが１バイト、topic_id１バイトがPROG_TOPIC_MAX個の合計9バイトで構成されています。
 * 9バイトｘ8番組＝72バイトのバイナリデータから取得しています。
 */
//--------------------------------------------------------------------
#define	CONTENTS_DATA_LEN	(1 + PROG_TOPIC_MAX)

//--------------------------------------------------------------------
/**
 */
//--------------------------------------------------------------------
typedef struct {
	u8 morning_id;
	u8 noon_id;
	u8 night_id;
	u8 first_intro_id;
	u8 next_intro_id;
	u8 end_id;
	u8 make_id;
}TVPROG_MSG;

//============================================================================================
//============================================================================================
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static const TVPROG_MSG TVProgramMsg[] = {
	{	//01	たたかう　トレーナー
		msg_tv_00_01_01,
		msg_tv_00_01_02,
		msg_tv_00_01_03,
		msg_tv_00_01_04,
		msg_tv_00_01_05,
		msg_tv_00_01_06,
		msg_tv_00_01_07,
	},
	{	//02	トレーナーリサーチ
		msg_tv_00_02_01,
		msg_tv_00_02_02,
		msg_tv_00_02_03,
		msg_tv_00_02_04,
		msg_tv_00_02_05,
		msg_tv_00_02_06,
		msg_tv_00_02_07,
	},
	{	//03	バトルウォッチ
		msg_tv_00_03_01,
		msg_tv_00_03_02,
		msg_tv_00_03_03,
		msg_tv_00_03_04,
		msg_tv_00_03_05,
		msg_tv_00_03_06,
		msg_tv_00_03_07,
	},
	{	//04	トレーナーの　にちじょう
		msg_tv_00_04_01,
		msg_tv_00_04_02,
		msg_tv_00_04_03,
		msg_tv_00_04_04,
		msg_tv_00_04_05,
		msg_tv_00_04_06,
		msg_tv_00_04_07,
	},
	{	//05	シンオウ　ニュース　ネット
		msg_tv_00_05_01,
		msg_tv_00_05_02,
		msg_tv_00_05_03,
		msg_tv_00_05_04,
		msg_tv_00_05_05,
		msg_tv_00_05_06,
		msg_tv_00_05_07,
	},
	{	//06	きろくでゴン！
		msg_tv_00_06_01,
		msg_tv_00_06_02,
		msg_tv_00_06_03,
		msg_tv_00_06_04,
		msg_tv_00_06_05,
		msg_tv_00_06_06,
		msg_tv_00_06_07,
	},
	{	//07	シンオウ・ナウ！
		msg_tv_00_07_01,
		msg_tv_00_07_02,
		msg_tv_00_07_03,
		msg_tv_00_07_04,
		msg_tv_00_07_05,
		msg_tv_00_07_06,
		msg_tv_00_07_07,
	},
	{	//08	トレンドばんぐみ
		msg_tv_00_08_01,
		msg_tv_00_08_02,
		msg_tv_00_08_03,
		msg_tv_00_08_04,
		msg_tv_00_08_05,
		msg_tv_00_08_06,
		msg_tv_00_08_07,
	},
};
//============================================================================================
//============================================================================================

//--------------------------------------------------------------------
/**
 * @brief	番組を終了状態にする
 * @param	fsys
 *
 * ※スクリプトから呼ばれる
 */
//--------------------------------------------------------------------
void TV_SetEndFlag(FIELDSYS_WORK * fsys)
{
	TV_WORK * tvwk = SaveData_GetTvWork(fsys->savedata);
	TVWORK_SetProgramEnd(tvwk, TRUE);
}

//--------------------------------------------------------------------
/**
 * @brief	番組の状態を取得する
 * @param	fsys
 * @retval	TV_STATUS_PROGRAM_END
 * @retval	TV_STATUS_TOPIC_END
 * @retval	TV_STATUS_START
 * @retval	TV_STATUS_ONAIR
 * @retval	TV_STATUS_NO_TOPIC
 *
 * ※スクリプトから呼ばれる
 */
//--------------------------------------------------------------------
int TV_GetBroadcastStatus(FIELDSYS_WORK * fsys)
{
	int num;
	TV_WORK * tvwk = SaveData_GetTvWork(fsys->savedata);

#ifdef	TV_BROADCAST_DEBUG
	TVWORK_DEBUG_Info(tvwk);
#endif
	if (TVWORK_IsProgramEnd(tvwk) == TRUE) {
		return	TV_STATUS_PROGRAM_END;	//番組終了状態
	}
	num = TVWORK_GetUsedTopicNumber(tvwk);
	if (num == 0) {
		return TV_STATUS_START;			//番組開始直後
	}
	if (num == 4) {
		return TV_STATUS_TOPIC_END;		//４つトピックを放送した
	}
	return TV_STATUS_ONAIR;			//番組放送中（2つ目以降）
}


//============================================================================================
//============================================================================================
#ifdef	TV_BROADCAST_DEBUG
static void DebugPutList(const char * name, const u8 * list, int max)
{
	int i;
	OS_Printf("%s", name);
	for (i = 0; i < PROG_TOPIC_MAX; i++) {
		OS_TPrintf("%02d ", list[i]);
	}
	OS_PutString("\n");
}
#endif

//--------------------------------------------------------------------
/**
 * @brief	現在の番組IDを取得
 * @param	fsys
 * @return	int		番組ID
 */
//--------------------------------------------------------------------
static TV_PROGRAM_ID GetNowProgramID(FIELDSYS_WORK * fsys)
{
	u8 id;
	u8 plist[7];
	int week, hour, min;
	int ofs;
	week = (EVTIME_GetWeek(fsys) + 6) % 7;
	hour = EVTIME_GetHour(fsys);
	min = EVTIME_GetMinute(fsys);
	ofs = (((19 + hour) % 24) * 4 + (min / 15)) * 7;
	ArchiveDataLoadOfs(plist, ARC_TV, NARC_tv_list_bin, ofs, sizeof(u8) * 7);
	id = plist[week];
#ifdef	TV_BROADCAST_DEBUG
	if (DebugFlagData.tv_program_id != 0) {
		id = DebugFlagData.tv_program_id;
	}
#endif
#ifdef	DEBUG_ONLY_FOR_tamada
	{
		int i;
		OS_TPrintf("TVID:%d week=%d %02d:%02d\n",id, EVTIME_GetWeek(fsys), hour, min);
		for (i = 0; i < 7; i++) {
			OS_TPrintf(" %02d",plist[i]);
		}
		OS_PutString("\n");
	}
#endif
	GF_ASSERT(0 < id && id < TV_PROGRAM_ID_MAX);
	return id;
}

//============================================================================================
//
//
//		番組内容データの取得
//
//
//============================================================================================
//--------------------------------------------------------------------
/**
 * @brief	トピック種別の取得
 * @param	prog_id
 * @return	TVTOPICTYPE
 */
//--------------------------------------------------------------------
static TVTOPICTYPE GetTopicType(TV_PROGRAM_ID prog_id)
{
	u8 type;
	int ofs = CONTENTS_DATA_LEN * (prog_id - 1);
	ArchiveDataLoadOfs(&type, ARC_TV, NARC_tv_contents_bin, ofs, sizeof(u8));
	OS_TPrintf("TV TOPIC TYPE %d\n", type);
	GF_ASSERT(type < TVTOPICTYPE_MAX);
	return type;
}
//--------------------------------------------------------------------
/**
 * @brief	番組内トピックIDの取得
 * @param	prog_id
 * @param	list	トピックIDをコピーするワークへのポインタ
 */
//--------------------------------------------------------------------
static void GetTopicList(TV_PROGRAM_ID prog_id, u8 * list)
{
	u8 type;
	int ofs = CONTENTS_DATA_LEN * (prog_id - 1) + 1;
	ArchiveDataLoadOfs(list, ARC_TV, NARC_tv_contents_bin, ofs, sizeof(u8) * PROG_TOPIC_MAX);
#ifdef TV_BROADCAST_DEBUG
	DebugPutList("TOPIC_ID:", list, PROG_TOPIC_MAX);
#endif
}

//============================================================================================
//============================================================================================

//--------------------------------------------------------------------
/**
 * @brief	トピック放送条件判定
 * @param	fsys
 * @param	prog_id
 * @param	topic_id
 * @retval	TRUE
 * @retval	FALSE
 */
//--------------------------------------------------------------------
static BOOL IsEnableBroadcast(FIELDSYS_WORK * fsys, TV_PROGRAM_ID prog_id, int topic_id)
{
	return TRUE;
}

//--------------------------------------------------------------------
/**
 * @brief	放送制限のないトピックのリストを作成
 */
//--------------------------------------------------------------------
static void MakeTopicTypeList(TV_PROGRAM_ID prog_id, FIELDSYS_WORK * fsys, u8 * type_array)
{
	u8 tlist[PROG_TOPIC_MAX];
	int i, n;
	TV_WORK * tvwk = SaveData_GetTvWork(fsys->savedata);
	GetTopicList(prog_id, tlist);

	MI_CpuClear8(type_array, sizeof(u8) * PROG_TOPIC_MAX);

	//放送制限のかかっていないトピックを抽出
	for (i = 0, n = 0; i < PROG_TOPIC_MAX; i++) {
		if (tlist[i] == 0) {
			break;
		}
		if (IsEnableBroadcast(fsys,prog_id,tlist[i]) == TRUE) {
			type_array[n] = tlist[i];
			n ++;
		}
	}
}

//--------------------------------------------------------------------
/**
 * @brief	ランダムでインデックスを選択する
 */
//--------------------------------------------------------------------
static int SelectRandomTopicData(FIELDSYS_WORK * fsys, const u8 * t_array)
{
	u8 array[PROG_TOPIC_MAX];
	int i,n;
	MI_CpuClear8(array, sizeof(u8) * PROG_TOPIC_MAX);
	for (i = 0, n = 0; i < PROG_TOPIC_MAX; i++) {
		if (t_array[i] != 0) {
			array[n] = t_array[i];
			n ++;
		}
	}
	if (n == 0) {
		return 0;
	} else if (n == 1) {
		return array[0];
	}
	return array[gf_mtRand() % n];
}

//--------------------------------------------------------------------
/**
 * @brief	指定トピックの抽出
 * @param	tvwk	テレビワークへのポインタ
 * @param	topic_type	トピックの種類
 * @param	topic_id	トピックID
 * @param	mine	自分データかどうか
 * @param	see		見たかどうか
 * @param	array	トピックインデックス格納のための配列へのポインタ
 */
//--------------------------------------------------------------------
static int SelectExistTopic(TV_WORK * tvwk, TVTOPICTYPE topic_type,
		int topic_id, BOOL mine, BOOL see, u8 * array)
{
	if (topic_type != TVTOPICTYPE_EVENT) {
		return TVWORK_SearchTopics(tvwk, topic_type, topic_id, mine, see, array);
	}
	if (see) {	//見たかどうかを覚えておけないのでとりあえず
		return 0;
	}
	if (!mine) {
		return 0;
	}
	if (TVWORK_IsUsedTopicIndex(tvwk, topic_id) == FALSE) {
		array[0] = topic_id;
		return 1;
	}
	return 0;
	
}

//--------------------------------------------------------------------
/**
 * @brief	
 * @param	fsys	フィールド制御へのポインタ
 * @param	mine	自分データかどうか
 * @param	see		見たかどうか
 * @param	type_array	トピックIDの配列へのポインタ
 * @param	topic_array	トピックインデックス格納のための配列へのポインタ
 */
//--------------------------------------------------------------------
static int SelectExistTopicData(TVTOPICTYPE topic_type,
		FIELDSYS_WORK * fsys, BOOL mine, BOOL see, const u8 * type_array, u8 * topic_array)
{
	u8 array[TOPIC_ARRAY_MAX];
	TV_WORK * tvwk = SaveData_GetTvWork(fsys->savedata);
	int i,j;
	int n = 0;

	while (*type_array != 0) {
		MI_CpuClear8(array, TOPIC_ARRAY_MAX);
		if (SelectExistTopic(tvwk, topic_type, *type_array, mine, see, array)) {
			for (j = 0; array[j] != 0 && j < TOPIC_ARRAY_MAX; j++) {
				topic_array[n] = array[j];
				n ++;
			}
		}
		type_array ++;
	}
	return n;
}

//--------------------------------------------------------------------
/**
 * @brief	放映できないトピックを削除
 * @param	fsys		フィールド制御へのポインタ
 * @param	topic_type	トピックの種類
 * @param	topic_array	トピックインデックス格納のための配列へのポインタ
 */
//--------------------------------------------------------------------
static void SelectEnableTopicData(FIELDSYS_WORK * fsys, TVTOPICTYPE topic_type, u8 * topic_array)
{
	int i;
	TVBCD * bcd;
	for (i = 0; *topic_array != 0 && i < TOPIC_ARRAY_MAX; topic_array ++, i++) {
		bcd = TVBCD_Create(fsys, topic_type, *topic_array);
		if (!TVTOPIC_CheckLimit(topic_type, fsys, bcd)) {
			*topic_array = 0;
		}
		TVBCD_Delete(bcd);
	}
}

//--------------------------------------------------------------------
/**
 * @brief	番組内で放送したトピックを削除
 * @param	fsys		フィールド制御へのポインタ
 * @param	topic_array	トピックインデックス格納のための配列へのポインタ
 */
//--------------------------------------------------------------------
static void DeleteUsedTopicData(FIELDSYS_WORK * fsys, u8 * topic_array)
{
	TV_WORK * tvwk = SaveData_GetTvWork(fsys->savedata);
	while (*topic_array != 0) {
		if (TVWORK_IsUsedTopicIndex(tvwk, *topic_array)) {
			*topic_array = 0;
		}
		topic_array ++;
	}
}

//--------------------------------------------------------------------
/**
 * @brief	放送するトピックを抽出する
 * @param	fsys
 * @param	mine
 * @param	see
 * @return	int		0のとき、データなし
 */
//--------------------------------------------------------------------
int TV_ChooseBroadcastTopic(FIELDSYS_WORK * fsys, BOOL mine, BOOL see)
{
	u8 type_array[PROG_TOPIC_MAX];
	u8 topic_array[TOPIC_ARRAY_MAX];
	int result;
	TV_PROGRAM_ID prog_id;
	int topic_type;
	
	prog_id = GetNowProgramID(fsys);
	topic_type = GetTopicType(prog_id);

	MI_CpuClear8(type_array, PROG_TOPIC_MAX);
	MI_CpuClear8(topic_array, TOPIC_ARRAY_MAX);

	//放送制限のないトピックのリスト生成
	MakeTopicTypeList(prog_id, fsys, type_array);
#ifdef	TV_BROADCAST_DEBUG
	DebugPutList("TOPIC_ID:", type_array, PROG_TOPIC_MAX);
#endif

	//データ存在チェックで選択
	result = SelectExistTopicData(topic_type, fsys, mine, see, type_array, topic_array);
#ifdef	TV_BROADCAST_DEBUG
	DebugPutList("EXIST  INDEX:",topic_array, TOPIC_ARRAY_MAX);
#endif
	if (result == 0) {
		return 0;			//データがなかった
	}
	// 放送できないトピックを削除
	SelectEnableTopicData(fsys, topic_type, topic_array);
#ifdef	TV_BROADCAST_DEBUG
	DebugPutList("ENABLE INDEX:",topic_array, TOPIC_ARRAY_MAX);
#endif

	//放送済みトピックを排除
	DeleteUsedTopicData(fsys, topic_array);
#ifdef	TV_BROADCAST_DEBUG
	DebugPutList("NOTUSE INDEX:",topic_array, TOPIC_ARRAY_MAX);
#endif

	//残ったものから乱数で選択
	result = SelectRandomTopicData(fsys, topic_array);

	return result;
}

//--------------------------------------------------------------------
/**
 */
//--------------------------------------------------------------------
int TV_ChooseBroadcastTopicTotal(FIELDSYS_WORK * fsys)
{
	int result;
	result = TV_ChooseBroadcastTopic(fsys, TV_OTHER_TOPIC, TV_NEW_TOPIC);
	if (result) {
		return result;
	}
	result = TV_ChooseBroadcastTopic(fsys, TV_MINE_TOPIC, TV_NEW_TOPIC);
	if (result) {
		return result;
	}
	result = TV_ChooseBroadcastTopic(fsys, TV_OTHER_TOPIC, TV_OLD_TOPIC);
	if (result) {
		return result;
	}
	result = TV_ChooseBroadcastTopic(fsys, TV_MINE_TOPIC, TV_OLD_TOPIC);
	return result;
}

//============================================================================================
//============================================================================================

//--------------------------------------------------------------------
/**
 * @brief	番組にあわせてメッセージ構造体を取得
 */
//--------------------------------------------------------------------
static const TVPROG_MSG * GetNowProgramMsgData(FIELDSYS_WORK * fsys)
{
	TV_PROGRAM_ID prog_id = GetNowProgramID(fsys);
	GF_ASSERT(prog_id <= NELEMS(TVProgramMsg));
	return &TVProgramMsg[prog_id - 1];
}

//--------------------------------------------------------------------
/**
 * @brief	番組ごとに決まっているメッセージIDを取得（7種類、前フリや終了など）
 * @param	fsys
 * @param	prog_msg_id		TV_PRO_MSG_～（scr_tv.h参照）
 * @return	int				メッセージID（NARC_msg_tv_program_dat内）
 *
 * ※スクリプトから呼ばれる
 */
//--------------------------------------------------------------------
int TV_GetProgramMsg(FIELDSYS_WORK * fsys, int prog_msg_id)
{
	TV_WORK * tvwk = SaveData_GetTvWork(fsys->savedata);
	const TVPROG_MSG * pmsg = GetNowProgramMsgData(fsys);

	switch (prog_msg_id) {
	default:
		GF_ASSERT(0);
		/* FALL THROUGH */
	case TV_PROG_MSG_OPENING:
		switch (GF_RTC_GetTimeZone()) {
		case TIMEZONE_MORNING:
			return pmsg->morning_id;
		case TIMEZONE_NOON:
			return pmsg->noon_id;
		default:
			return pmsg->night_id;
		}
	case TV_PROG_MSG_INTRO:
		if (TVWORK_GetUsedTopicNumber(tvwk) == 0) {
			return pmsg->first_intro_id;
		} else {
			return pmsg->next_intro_id;
		}
	case TV_PROG_MSG_ENDING:
		return pmsg->end_id;
	case TV_PROG_MSG_PLEASE:
		return pmsg->make_id;
	}
}

//============================================================================================
//============================================================================================
//--------------------------------------------------------------------
/**
 * @brief	番組トピック生成処理
 * @param	fsys		フィールド制御へのポインタ
 * @param	ws			WORDSETへのポインタ
 * @param	idx			トピックインデックス指定
 * @param	arc_id		アーカイブ指定を受け取るためのポインタ
 * @param	msg_id		メッセージ指定を受け取るためのポインタ
 */
//--------------------------------------------------------------------
BOOL TV_GetProgramID(FIELDSYS_WORK * fsys, WORDSET * ws, int idx, u16 * arc_id, u16 * msg_id)
{
	TV_PROGRAM_ID prog_id = GetNowProgramID(fsys);
	int topic_type = GetTopicType(prog_id);
	TV_WORK * tvwk = SaveData_GetTvWork(fsys->savedata);
	TVBCD * bcd;

	TVWORK_SetUsedTopicIndex(tvwk, idx);

	bcd = TVBCD_Create(fsys, topic_type, idx);
	//TVWORK_DEBUG_Info(tvwk);

	TVBCD_CountUpBroadCast(bcd);
	*msg_id = TVTOPIC_Make(topic_type, fsys, ws, bcd, arc_id);

	TVBCD_Delete(bcd);
	return TRUE;
}



