//============================================================================================
/**
 * @file	tv_work.h
 * @brief
 * @author	tamada GAME FREAK inc.
 * @date	2006.05.11
 */
//============================================================================================
#ifndef	__TV_WORK_H__
#define	__TV_WORK_H__

#include "savedata/savedata_def.h"
#include "gflib/gf_date.h"
//============================================================================================
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	テレビ番組データへの不完全型定義
 */
//----------------------------------------------------------
typedef struct TV_WORK TV_WORK;

typedef struct TVTOPIC TVTOPIC;
typedef struct MY_TOPIC MY_TOPIC;
typedef struct OTHER_TOPIC OTHER_TOPIC;
typedef OTHER_TOPIC SEND_TOPIC;

//============================================================================================
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	テレビトピックの種類
 */
//----------------------------------------------------------
typedef enum {
	TVTOPICTYPE_NOTHING = 0,
	TVTOPICTYPE_INTERVIEW,		///<質問型トピック
	TVTOPICTYPE_WATCH,			///<監視型トピック
	TVTOPICTYPE_RECORD,			///<ギネス型トピック
	TVTOPICTYPE_EVENT,			///<イベント型トピック

	TVTOPICTYPE_MAX,
}TVTOPICTYPE;

//----------------------------------------------------------
/**
 * @brief	汎用トピック内容保持ワークのサイズ
 */
//----------------------------------------------------------
enum {
	TOPIC_DATA_SIZE = 40,
};

//----------------------------------------------------------
/**
 * @brief	コンテスト用状況保持ワーク定義
 */
//----------------------------------------------------------
typedef struct TOPICTEMP_CONTEST{
	u8 exist_flag;
	u16 monsno;
	u8 mons_sex;
	u8 mons_region;
	u8 mons_rom;
	u8 contest_rank;
	u8 contest_type;
	u8 contest_result;
}TOPICTEMP_CONTEST;

//----------------------------------------------------------
/**
 * @brief	連れ歩き公園での拾い物状況
 */
//----------------------------------------------------------
enum {
	PARKPICK_ID_NOTHING = 0,	///<拾っていない
	PARKPICK_ID_ITEM,			///<アイテム拾った
	PARKPICK_ID_ACCESSORIES,	///<アクセサリ拾った
};
//----------------------------------------------------------
/**
 * @brief	自然公園用状況保持ワーク定義
 */
//----------------------------------------------------------
typedef struct TOPICTEMP_PARK {
	u8 exist_flag;
	u16 monsno;
	u8 mons_sex;
	u8 mons_region;
	u8 mons_rom;
	u8 nickname_flag;
	STRCODE nickname[MONS_NAME_SIZE + EOM_SIZE];
	u8 poke_character;			///<ポケモンの性格
	u8 pick_type;				///<最後に拾ったものの種類
	u8 accessories;				///<拾ったアクセサリ
	u16 item_no;				///<拾ったアイテム
}TOPICTEMP_PARK;

//----------------------------------------------------------
/**
 * @brief	ポルトミニゲーム用状況保持ワーク定義
 */
//----------------------------------------------------------
typedef struct TOPICTEMP_PORUTO {
	u8 exist_flag;		///<データ存在チェック
	u8 taste_type;		///<ポルトの種類（味）
}TOPICTEMP_PORUTO;

//----------------------------------------------------------
/**
 * @brief	バトルタワー用状況保持ワーク定義
 */
//----------------------------------------------------------
typedef struct TOPICTEMP_BTOWER {
	u8 exist_flag;		///<データ存在チェック
	u8 continue_flag;	///<連勝中かどうかのチェック
	u16 win_count;		///<その時点での連勝数
} TOPICTEMP_BTOWER;

//----------------------------------------------------------
/**
 * @brief	サファリ用状況保持ワーク定義
 */
//----------------------------------------------------------
typedef struct TOPICTEMP_SAFARI {
	u8 exist_flag;
	u16 monsno;
	u8 mons_sex;
	u8 mons_region;
	u8 mons_rom;
	u8 capture_count;
}TOPICTEMP_SAFARI;

//============================================================================================
//
//			関数外部参照宣言
//
//============================================================================================
//----------------------------------------------------------
//	セーブデータ関連処理
//----------------------------------------------------------
extern int TVWORK_GetWorkSize(void);
extern void TVWORK_Init(TV_WORK * tv);
extern TV_WORK * SaveData_GetTvWork(SAVEDATA * sv);

//----------------------------------------------------------
//	時間による番組更新処理
//----------------------------------------------------------
extern void TVWORK_UpdateMinuteCount(TV_WORK * tvwk, int min_diff, int now_minute);

extern MY_TOPIC * TVWORK_GetMyTopicByIndex(TV_WORK * tvwk, TVTOPICTYPE topic_type, int index);
extern OTHER_TOPIC * TVWORK_GetOtherTopicByIndex(TV_WORK * tvwk, TVTOPICTYPE topic_type, int index);

//----------------------------------------------------------
//トピックの追加処理
//----------------------------------------------------------
extern BOOL TVWORK_MakeTopic(TV_WORK * tvwk, TVTOPICTYPE topic_type, int topic_id, const u8 * data);

//----------------------------------------------------------
//	番組内容制御関連
//----------------------------------------------------------
extern int TVWORK_SearchTopics(const TV_WORK * tvwk, TVTOPICTYPE topic_type,
		int topic_id, BOOL mine, BOOL see, u8 * array);
extern BOOL TVWORK_EnableMakeTopic(TV_WORK * tvwk, TVTOPICTYPE topic_type, int topic_id);
extern BOOL TVWORK_IsUsedTopicIndex(const TV_WORK * tvwk, int index);
extern void TVWORK_SetUsedTopicIndex(TV_WORK * tvwk, int index);
extern BOOL TVWORK_IsProgramEnd(const TV_WORK * tvwk);
extern void TVWORK_SetProgramEnd(TV_WORK * tvwk, BOOL flag);
extern void TVWORK_StartProgram(TV_WORK * tvwk);

extern int TVWORK_GetUsedTopicNumber(const TV_WORK * tvwk);

//----------------------------------------------------------
//	トピックのクリア
//----------------------------------------------------------
extern void TVWORK_ClearMyTopic(TV_WORK * tvwk);
extern void TVWORK_ClearOtherTopic(TV_WORK * tvwk);

//----------------------------------------------------------
//	OTHER_TOPICからの取得処理
//----------------------------------------------------------
extern const STRCODE * OTHERTOPIC_GetName(const OTHER_TOPIC * ot);
extern int OTHERTOPIC_GetSex(const OTHER_TOPIC * ot);
extern int OTHERTOPIC_GetRegionCode(const OTHER_TOPIC * ot);
extern int OTHERTOPIC_GetRomVersion(const OTHER_TOPIC * ot);
extern int OTHERTOPIC_GetSenderID(const OTHER_TOPIC * ot);
extern u32 OTHERTOPIC_GetOwnerID(const OTHER_TOPIC * ot);
extern TVTOPIC * OTHERTOPIC_GetTopicData(OTHER_TOPIC * ot);

//----------------------------------------------------------
//	MY_TOPICからの取得処理
//----------------------------------------------------------
extern TVTOPIC * MYTOPIC_GetTopic(MY_TOPIC * mt);

//----------------------------------------------------------
//	TVTOPIC関連
//----------------------------------------------------------
extern void TVTOPIC_CountUpBroadcast(TVTOPIC * topic);
extern void * TVTOPIC_GetData(TVTOPIC * topic);
extern int TVTOPIC_GetTopicID(const TVTOPIC * topic);

extern GF_DATE TVTOPIC_GetDate(const TVTOPIC * topic);
extern int TVTOPIC_GetSeeCount(const TVTOPIC * topic);

extern BOOL TVWORK_IsMineIndex(int index);
extern int TVWORK_MakeOtherIndex(int index);

//----------------------------------------------------------
//	状況保持ワークの取得
//----------------------------------------------------------
extern TOPICTEMP_CONTEST * TVWORK_GetContestTemp(TV_WORK * tvwk);
extern TOPICTEMP_PARK * TVWORK_GetParkTemp(TV_WORK * tvwk);
extern TOPICTEMP_PORUTO * TVWORK_GetPorutoTemp(TV_WORK * tvwk);
extern TOPICTEMP_BTOWER * TVWORK_GetBTowerTemp(TV_WORK * tvwk);
extern TOPICTEMP_SAFARI * TVWORK_GetSafariTemp(TV_WORK * tvwk);

//----------------------------------------------------------
//	レコード関連
//
//	※常駐領域に配置されていないため、レコードからしか呼ぶことはできない
//----------------------------------------------------------
extern u32 TVWORK_GetSendQandADataSize(const SAVEDATA * sv);
extern u32 TVWORK_GetSendWatchDataSize(const SAVEDATA * sv);
extern u32 TVWORK_GetSendRecordDataSize(const SAVEDATA * sv);

extern SEND_TOPIC * TVWORK_AllocSendQandAData(SAVEDATA * sv, int headID, u32 size);
extern SEND_TOPIC * TVWORK_AllocSendWatchData(SAVEDATA * sv, int headID, u32 size);
extern SEND_TOPIC * TVWORK_AllocSendRecordData(SAVEDATA * sv, int headID, u32 size);

extern void TVWORK_MixWatchData(TV_WORK * tv, int member, int my_id, const void ** darray);
extern void TVWORK_MixRecordData(TV_WORK * tv, int member, int my_id, const void ** darray);
extern void TVWORK_MixQandAData(TV_WORK * tv, int member, int my_id, const void ** darray);

//----------------------------------------------------------
//		デバッグ用
//----------------------------------------------------------
#ifdef	PM_DEBUG
extern void TVWORK_DEBUG_Info(const TV_WORK * tvwk);
#endif

#endif	/* __TV_WORK_H__ */

