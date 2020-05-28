//============================================================================================
/**
 * @file	tv_work.c
 * @brief
 * @author	tamada GAME FREAK inc.
 * @date	2006.05.11
 */
//============================================================================================

#include "common.h"
#include "savedata/savedata_def.h"
#include "system/gamedata.h"

#include "savedata/tv_work.h"

#include "gflib/gf_date.h"

#include "field/tv_topic.h"

#include "system/pm_rtc.h"
#include "system/pm_str.h"


#include "tvwork_local.h"



#define	OTHER_MASK	0x80

static void TVWORK_ClearUsedTopicIndex(TV_WORK * tvwk);
static MY_TOPIC * GetMyTopicByTopicType(TV_WORK * tvwk, TVTOPICTYPE topic_type);
//============================================================================================
//
//		セーブシステムに必要な関数
//
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	テレビ放送セーブデータサイズの取得
 * @return	int		データサイズ
 */
//----------------------------------------------------------
int TVWORK_GetWorkSize(void)
{
	return sizeof(TV_WORK);
}

//----------------------------------------------------------
/**
 * @brief	テレビ放送セーブデータの初期化
 * @param	tv		テレビ放送セーブデータへのポインタ
 */
//----------------------------------------------------------
void TVWORK_Init(TV_WORK * tv)
{
	MI_CpuClearFast(tv, sizeof(TV_WORK));
}


//============================================================================================
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	自分トピックのクリア
 * @param	tvwk			テレビデータへのポインタ
 */
//----------------------------------------------------------
void TVWORK_ClearMyTopic(TV_WORK * tvwk)
{
	MI_CpuClearFast(tvwk->MyWatchTopic, sizeof(MY_TOPIC) * MY_WATCH_MAX);
	MI_CpuClearFast(tvwk->MyRecordTopic, sizeof(MY_TOPIC) * MY_RECORD_MAX);
	MI_CpuClearFast(tvwk->MyQandATopic, sizeof(MY_TOPIC) * MY_QANDA_MAX);
	TVWORK_StartProgram(tvwk);		//参照されていると問題なので、念のため
}

//----------------------------------------------------------
/**
 * @brief	他人トピックのクリア
 * @param	tvwk			テレビデータへのポインタ
 */
//----------------------------------------------------------
void TVWORK_ClearOtherTopic(TV_WORK * tvwk)
{
	MI_CpuClearFast(tvwk->OtherWatchTopic, sizeof(OTHER_TOPIC) * OTHER_WATCH_MAX);
	MI_CpuClearFast(tvwk->OtherRecordTopic, sizeof(OTHER_TOPIC) * OTHER_RECORD_MAX);
	MI_CpuClearFast(tvwk->OtherQandATopic, sizeof(OTHER_TOPIC) * OTHER_QANDA_MAX);
	TVWORK_StartProgram(tvwk);		//参照されていると問題なので、念のため
}

//----------------------------------------------------------
/**
 * @brief	テレビ用時間経過処理
 * @param	tvwk			テレビデータへのポインタ
 * @param	min_diff		前回の更新からの経過時間（分単位）
 * @param	now_minute		現在の時間（分）
 *
 * 時間経過処理（分単位）から呼び出される。
 */
//----------------------------------------------------------
void TVWORK_UpdateMinuteCount(TV_WORK * tvwk, int min_diff, int now_minute)
{
	int i;
	if (tvwk->minute_count > min_diff) {
		tvwk->minute_count -= min_diff;
	} else {
		tvwk->minute_count = 15 - now_minute % 15;
		if (tvwk->minute_count == 0) {
			tvwk->minute_count = 15;
		}
		tvwk->end_flag = FALSE;
		for (i = 0; i < USED_TOPIC_MAX; i++) {
			tvwk->used_index[i] = 0;
		}
	}
}

//----------------------------------------------------------
/**
 * @brief	番組放送開始
 * @param	tvwk			テレビデータへのポインタ
 */
//----------------------------------------------------------
void TVWORK_StartProgram(TV_WORK * tvwk)
{
	TVWORK_SetProgramEnd(tvwk, FALSE);
	TVWORK_ClearUsedTopicIndex(tvwk);
}

//============================================================================================
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	番組終了状態セット
 * @param	tvwk			テレビデータへのポインタ
 * @retval	TRUE
 * @retval	FALSE
 */
//----------------------------------------------------------
void TVWORK_SetProgramEnd(TV_WORK * tvwk, BOOL flag)
{
	tvwk->end_flag = flag;
}
//----------------------------------------------------------
/**
 * @brief	番組終了状態かどうかのチェック
 * @param	tvwk			テレビデータへのポインタ
 * @retval	TRUE
 * @retval	FALSE
 */
//----------------------------------------------------------
BOOL TVWORK_IsProgramEnd(const TV_WORK * tvwk)
{
	return tvwk->end_flag;
}

//----------------------------------------------------------
/**
 * @brief	放送済みトピック登録
 * @param	tvwk			テレビデータへのポインタ
 */
//----------------------------------------------------------
void TVWORK_SetUsedTopicIndex(TV_WORK * tvwk, int index)
{
	int i;
	for (i = 0; i < USED_TOPIC_MAX; i++) {
#ifdef	DEBUG_ONLY_FOR_tamada
		OS_TPrintf("[%02x]", tvwk->used_index[i]);
#endif
		if (tvwk->used_index[i] == 0) {
			tvwk->used_index[i] = index;
			return;
		}
	}
	GF_ASSERT(0);
}

//----------------------------------------------------------
/**
 * @brief	放送したトピックインデックスをクリアする
 * @param	tvwk			テレビデータへのポインタ
 */
//----------------------------------------------------------
static void TVWORK_ClearUsedTopicIndex(TV_WORK * tvwk)
{
	int i;
	for (i = 0; i < USED_TOPIC_MAX; i++) {
		tvwk->used_index[i] = 0;
	}
}
//----------------------------------------------------------
/**
 * @brief	放送したトピックかどうかをチェック
 * @param	tvwk			テレビデータへのポインタ
 */
//----------------------------------------------------------
BOOL TVWORK_IsUsedTopicIndex(const TV_WORK * tvwk, int index)
{
	int i;
	for (i = 0; i < USED_TOPIC_MAX; i++) {
		if (tvwk->used_index[i] == index) {
			return TRUE;
		}
	}
	return FALSE;
}

//----------------------------------------------------------
/**
 * @brief	放送したトピックの数を返す
 * @param	tvwk	テレビデータへのポインタ
 * @return	int		放送したトピックの数
 */
//----------------------------------------------------------
int TVWORK_GetUsedTopicNumber(const TV_WORK * tvwk)
{
	int i, num;
	for (i = 0, num = 0; i < USED_TOPIC_MAX; i++) {
		if (tvwk->used_index[i] != 0) {
			num ++;
		}
	}
	return num;
}
//============================================================================================
//============================================================================================
//----------------------------------------------------------
//----------------------------------------------------------
static void TVTOPIC_SetTopic(TVTOPIC * topic, int topic_id, const u8 * data)
{
	RTCDate date;
	GF_RTC_GetDate(&date);
	topic->date = RTCDate2GFDate(&date);
	topic->topic_id = topic_id;
	topic->see_count = 0;
	MI_CpuCopyFast(data, topic->data, TOPIC_DATA_SIZE);
}
//----------------------------------------------------------
/**
 * @brief
 * @param	tvwk		テレビデータへのポインタ
 * @param	prog_id		番組ID
 * @param	topic_id	トピックID
 * @param	data		データ
 * @retval	TRUE		登録できた
 * @retval	FALSE		登録できなかった
 */
//----------------------------------------------------------
BOOL TVWORK_MakeTopic(TV_WORK * tvwk, TVTOPICTYPE topic_type, int topic_id, const u8 * data)
{
	int i;
	MY_TOPIC * topic;
	topic = GetMyTopicByTopicType(tvwk, topic_type);

	//同じトピックがある場合の処理
	for (i = 0; i < MY_TOPIC_COMMON_MAX; i++) {
		if (topic[i].topic.topic_id == topic_id) {
			if (topic[i].topic.see_count >= BROADCAST_MAX) {
				TVTOPIC_SetTopic(&topic[i].topic, topic_id, data);
				return TRUE;
			}
			return FALSE;
		}
	}
	//空きを探す
	for (i = 0; i < MY_TOPIC_COMMON_MAX; i++) {
		if (topic[i].topic.topic_id == 0) {
			TVTOPIC_SetTopic(&topic[i].topic, topic_id, data);
			return TRUE;
		}
	}
	//古いトピックを探して上書きできるかチェック
	for (i = 0; i < MY_TOPIC_COMMON_MAX; i++) {
		if (topic[i].topic.see_count >= BROADCAST_MAX) {
			TVTOPIC_SetTopic(&topic[i].topic, topic_id, data);
			return TRUE;
		}
	}
	return FALSE;
}
//============================================================================================
//============================================================================================
//----------------------------------------------------------
//----------------------------------------------------------
const STRCODE * OTHERTOPIC_GetName(const OTHER_TOPIC * ot)
{
	return ot->owner_name;
}
//----------------------------------------------------------
//----------------------------------------------------------
int OTHERTOPIC_GetSex(const OTHER_TOPIC * ot)
{
	return ot->sex;
}
//----------------------------------------------------------
//----------------------------------------------------------
int OTHERTOPIC_GetRegionCode(const OTHER_TOPIC * ot)
{
	return ot->region_code;
}
//----------------------------------------------------------
//----------------------------------------------------------
int OTHERTOPIC_GetRomVersion(const OTHER_TOPIC * ot)
{
	return ot->rom_ver;
}
//----------------------------------------------------------
//----------------------------------------------------------
u32 OTHERTOPIC_GetOwnerID(const OTHER_TOPIC * ot)
{
	return ot->owner_id;
}
//----------------------------------------------------------
//----------------------------------------------------------
TVTOPIC * OTHERTOPIC_GetTopicData(OTHER_TOPIC * ot)
{
	return	&ot->topic;
}
//----------------------------------------------------------
//----------------------------------------------------------
TVTOPIC * MYTOPIC_GetTopic(MY_TOPIC * mt)
{
	return &mt->topic;
}

//----------------------------------------------------------
/**
 */
//----------------------------------------------------------
static MY_TOPIC * GetMyTopicByTopicType(TV_WORK * tvwk, TVTOPICTYPE topic_type)
{
	MY_TOPIC * mt = NULL;
	switch (topic_type) {
	case TVTOPICTYPE_INTERVIEW:
		mt = tvwk->MyQandATopic;
		break;
	case TVTOPICTYPE_WATCH:
		mt = tvwk->MyWatchTopic;
		break;
	case TVTOPICTYPE_RECORD:
		mt = tvwk->MyRecordTopic;
		break;
	case TVTOPICTYPE_EVENT:
		GF_ASSERT(0);
	}
	return mt;
}
//----------------------------------------------------------
/**
 */
//----------------------------------------------------------
static OTHER_TOPIC * GetOtherTopicByTopicType(TV_WORK * tvwk, TVTOPICTYPE topic_type)
{
	OTHER_TOPIC * ot = NULL;

	switch (topic_type) {
	case TVTOPICTYPE_WATCH:
		ot = tvwk->OtherWatchTopic;
		break;
	case TVTOPICTYPE_RECORD:
		ot = tvwk->OtherRecordTopic;
		break;
	case TVTOPICTYPE_INTERVIEW:
		ot = tvwk->OtherQandATopic;
		break;
	case TVTOPICTYPE_EVENT:
		GF_ASSERT(0);
	}
	return ot;
}
//============================================================================================
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	トピックのIDを取得
 * @param	topic
 */
//----------------------------------------------------------
int TVTOPIC_GetTopicID(const TVTOPIC * topic)
{
	return topic->topic_id;
}
//----------------------------------------------------------
/**
 * @brief	視聴回数のカウントアップ
 * @param	topic
 */
//----------------------------------------------------------
void TVTOPIC_CountUpBroadcast(TVTOPIC * topic)
{
	if (topic->see_count < BROADCAST_MAX) {
		topic->see_count ++;
	}
}

//----------------------------------------------------------
/**
 * @brief	トピックの内容データを取得
 * @param	topic
 */
//----------------------------------------------------------
void * TVTOPIC_GetData(TVTOPIC * topic)
{
	return topic->data;
}

//----------------------------------------------------------
//----------------------------------------------------------
GF_DATE TVTOPIC_GetDate(const TVTOPIC * topic)
{
	return topic->date;
}
//----------------------------------------------------------
//----------------------------------------------------------
int TVTOPIC_GetSeeCount(const TVTOPIC * topic)
{
	return topic->see_count;
}

//============================================================================================
//============================================================================================
//----------------------------------------------------------
//----------------------------------------------------------
static int SelectMyTopic(const MY_TOPIC * topic, int max,
		int topic_id, BOOL see_flag, u8 * array)
{
	int i, n;
	for (n = 0, i = 0; i < max; i++) {
		if (topic[i].topic.topic_id == topic_id) {
			int count = topic[i].topic.see_count;
			if (see_flag && count) {
			//視聴データ
				array[n] = i+1;
				n ++;
			} else if (!see_flag && count == 0) {
			//未視聴データ
				array[n] = i+1;
				n ++;
			}
		}
	}
	return n;
}

//----------------------------------------------------------
//----------------------------------------------------------
static int SelectOtherTopic(const OTHER_TOPIC * other, int max,
		int topic_id, BOOL see_flag, u8 * array)
{
	int i, n;
	for (n = 0, i = 0; i < max; i++) {
		int count = other[i].topic.see_count;
		if (other[i].topic.topic_id == topic_id) {
			if (see_flag && count) {
			//視聴データ
				array[n] = TVWORK_MakeOtherIndex(i+1);
				n ++;
			} else if (!see_flag && count == 0) {
			//未視聴データ
				array[n] = TVWORK_MakeOtherIndex(i+1);
				n ++;
			}
		}
	}
	return n;
}


//----------------------------------------------------------
/**
 * @brief	指定条件のトピックデータインデックスを返す
 * @param	tvwk		テレビワークへのポインタ
 * @param	topic_type	データ指定（監視・レコード・質問）
 * @param	topic_id	トピックの種類ID
 * @param	see_flag	見たデータかどうか
 * @param	array		結果を保存する配列
 */
//----------------------------------------------------------
int TVWORK_SearchTopics(const TV_WORK * tvwk, TVTOPICTYPE topic_type,
		int topic_id, BOOL mine, BOOL see, u8 * array)
{
	switch (topic_type) {
	case TVTOPICTYPE_WATCH:
		if (mine) {
			return SelectMyTopic(tvwk->MyWatchTopic, MY_WATCH_MAX, topic_id, see, array);
		} else {
			return SelectOtherTopic(tvwk->OtherWatchTopic, OTHER_WATCH_MAX, topic_id, see, array);
		}
	case TVTOPICTYPE_RECORD:
		if (mine) {
			return SelectMyTopic(tvwk->MyRecordTopic, MY_RECORD_MAX, topic_id, see, array);
		} else {
			return SelectOtherTopic(tvwk->OtherRecordTopic, OTHER_RECORD_MAX, topic_id, see, array);
		}
	case TVTOPICTYPE_INTERVIEW:
		if (mine) {
			return SelectMyTopic(tvwk->MyQandATopic, MY_QANDA_MAX, topic_id, see, array);
		} else {
			return SelectOtherTopic(tvwk->OtherQandATopic, OTHER_QANDA_MAX, topic_id, see, array);
		}
	case TVTOPICTYPE_EVENT:
		//GF_ASSERT(0);
		//万が一イベント型を検索しても０＝＝データなしで返す
		return 0;
	}
	return 0;
}

//----------------------------------------------------------
/**
 * @brief	トピックを生成可能かどうかのチェック
 * @param	tvwk		テレビワークへのポインタ
 * @param	type		データ指定（監視・レコード・質問）
 * @param	topic_id	トピックの種類ID
 *
 * 本来はトピックの放送回数などを含めてチェックするがまずは
 * 簡単に未聴取かどうかのチェックを返している
 */
//----------------------------------------------------------
BOOL TVWORK_EnableMakeTopic(TV_WORK * tvwk, TVTOPICTYPE topic_type, int topic_id)
{
	int n;
	int i;
	u8 array[MY_TOPIC_COMMON_MAX];
	MY_TOPIC * mtopic;
	MI_CpuClear8(array, MY_TOPIC_COMMON_MAX);

	//未視聴データをチェック
	n = TVWORK_SearchTopics(tvwk, topic_type, topic_id, TRUE, FALSE, array);
	if (n != 0) {
		//見たことのないデータがある
		return FALSE;
	}

	//視聴データをチェック
	n = TVWORK_SearchTopics(tvwk, topic_type, topic_id, TRUE, TRUE, array);
	if (n != 0) {
		//視聴済データがあった場合
		for (i = 0; i < MY_TOPIC_COMMON_MAX & array[i] != 0; i++) {
			mtopic = TVWORK_GetMyTopicByIndex(tvwk, topic_type, array[i]);
			if (mtopic->topic.see_count >= BROADCAST_MAX) {
				//視聴データがあるが上書き可能
				return TRUE;
			}
		}
		//視聴データがあり、上書き不可能
		return FALSE;
	}

	//空きか、上書き可能な場所を探す
	for (i = 1; i <= MY_TOPIC_COMMON_MAX; i++) {
		mtopic = TVWORK_GetMyTopicByIndex(tvwk, topic_type, i);
		if (mtopic->topic.topic_id == 0 ||
				mtopic->topic.see_count >= BROADCAST_MAX) {
			return TRUE;
		}
	}

	//空きも上書き可能なトピックもない
	return FALSE;
}

//----------------------------------------------------------
//----------------------------------------------------------
MY_TOPIC * TVWORK_GetMyTopicByIndex(TV_WORK * tvwk, TVTOPICTYPE topic_type, int index)
{
	MY_TOPIC * topic;

	GF_ASSERT(TVWORK_IsMineIndex(index) == TRUE);
	index &= ~OTHER_MASK;
	topic = GetMyTopicByTopicType(tvwk, topic_type);
	return &topic[index - 1];
}
//----------------------------------------------------------
//----------------------------------------------------------
OTHER_TOPIC * TVWORK_GetOtherTopicByIndex(TV_WORK * tvwk, TVTOPICTYPE topic_type, int index)
{
	OTHER_TOPIC * ot;

	GF_ASSERT(TVWORK_IsMineIndex(index) == FALSE);
	index &= ~OTHER_MASK;
	ot = GetOtherTopicByTopicType(tvwk, topic_type);
	return &ot[index - 1];
}

//----------------------------------------------------------
/**
 * @brief	インデックス値が自分データかどうかのチェック
 * @param	index
 * @retval	TRUE
 * @retval	FALSE
 */
//----------------------------------------------------------
BOOL TVWORK_IsMineIndex(int index)
{
	if (index & OTHER_MASK) {
		return FALSE;
	} else {
		return TRUE;
	}
}

//----------------------------------------------------------
/**
 * @brief	他人データのインデックス値に変換する
 * @param	index
 * @param	int		他人データ用インデックス値
 */
//----------------------------------------------------------
int TVWORK_MakeOtherIndex(int index)
{
	return index | OTHER_MASK;
}


//============================================================================================
//
//
//				状況保持ワークの取得
//
//
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	状況保持ワーク取得：コンテスト
 * @param	tvwk
 * @return	TOPICTEMP_CONTESTへのポインタ
 */
//----------------------------------------------------------
TOPICTEMP_CONTEST * TVWORK_GetContestTemp(TV_WORK * tvwk)
{
	return &tvwk->ContestTemp;
}
//----------------------------------------------------------
/**
 * @brief	状況保持ワーク取得：コンテスト
 * @param	tvwk
 * @return	TOPICTEMP_CONTESTへのポインタ
 */
//----------------------------------------------------------
TOPICTEMP_PARK * TVWORK_GetParkTemp(TV_WORK * tvwk)
{
	return &tvwk->ParkTemp;
}
//----------------------------------------------------------
/**
 * @brief	状況保持ワーク取得：コンテスト
 * @param	tvwk
 * @return	TOPICTEMP_CONTESTへのポインタ
 */
//----------------------------------------------------------
TOPICTEMP_PORUTO * TVWORK_GetPorutoTemp(TV_WORK * tvwk)
{
	return &tvwk->PorutoTemp;
}
//----------------------------------------------------------
/**
 * @brief	状況保持ワーク取得：バトルタワー
 * @param	tvwk
 * @return	TOPICTEMP_BTOWERへのポインタ
 */
//----------------------------------------------------------
TOPICTEMP_BTOWER * TVWORK_GetBTowerTemp(TV_WORK * tvwk)
{
	return &tvwk->BTowerTemp;
}
//----------------------------------------------------------
/**
 * @brief	状況保持ワーク取得：コンテスト
 * @param	tvwk
 * @return	TOPICTEMP_CONTESTへのポインタ
 */
//----------------------------------------------------------
TOPICTEMP_SAFARI * TVWORK_GetSafariTemp(TV_WORK * tvwk)
{
	return &tvwk->SafariTemp;
}

#ifdef	PM_DEBUG
//============================================================================================
//
//
//				デバッグ情報表示
//
//
//============================================================================================
//----------------------------------------------------------
//----------------------------------------------------------
static void DebugTopicInfo(const TVTOPIC * topic)
{
	GF_DATE dt = topic->date;
	OS_TPrintf("ID%02x:CT%02d:", topic->topic_id, topic->see_count);
	OS_TPrintf("%02d/%02d/%02d ",
			GFDate_GetYear(dt), GFDate_GetMonth(dt), GFDate_GetDay(dt)
			);
}
//----------------------------------------------------------
//----------------------------------------------------------
static void DebugMyTopicInfo(const char * name, const MY_TOPIC * mytopic, int max)
{
	int i;
	OS_TPrintf("%s\n",name);
	for (i = 0; i < max; i++) {
		OS_TPrintf("[%02d ", i);
		DebugTopicInfo(&mytopic[i].topic);
		OS_TPrintf("]");
		if (i % 4 == 3) OS_PutString("\n");
	}
	OS_TPrintf("\n");
}
//----------------------------------------------------------
//----------------------------------------------------------
static void DebugOtherTopicInfo(const char * name, const OTHER_TOPIC * other, int max)
{
	int i;
	OS_TPrintf("%s\n",name);
	for (i = 0; i < max; i++) {
		OS_TPrintf("[%02d ", i);
		DebugTopicInfo(&other[i].topic);
		OS_TPrintf("]");
		if (i % 4 == 3) OS_PutString("\n");
	}
}
//----------------------------------------------------------
//----------------------------------------------------------
void TVWORK_DEBUG_Info(const TV_WORK * tvwk)
{
	int i;
	OS_TPrintf("END=%s:",(tvwk->end_flag? "TRUE":"FALSE"));
	for (i = 0; i < USED_TOPIC_MAX; i++) {
		OS_TPrintf("[%02x]", tvwk->used_index[i]);
	}
	OS_PutString("\n");
	DebugMyTopicInfo("MY WATCH TYPE", tvwk->MyWatchTopic, MY_WATCH_MAX);
	DebugMyTopicInfo("MY RECORD TYPE", tvwk->MyRecordTopic, MY_RECORD_MAX);
	DebugMyTopicInfo("MY QANDA TYPE", tvwk->MyQandATopic, MY_QANDA_MAX);
	DebugOtherTopicInfo("OTHER WATCH TYPE", tvwk->OtherWatchTopic, OTHER_WATCH_MAX);
	DebugOtherTopicInfo("OTHER RECORD TYPE", tvwk->OtherRecordTopic, OTHER_RECORD_MAX);
	DebugOtherTopicInfo("OTHER QANDA TYPE", tvwk->OtherQandATopic, OTHER_QANDA_MAX);
}

#endif	//PM_DEBUG

