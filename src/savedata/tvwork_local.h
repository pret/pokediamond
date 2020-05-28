//============================================================================================
/**
 * @file	tvwork_local.h
 * @brief	テレビデータのレコードコーナー混ぜる処理
 * @author	tamada GAME FREAK inc.
 * @date	2006.05.31
 */
//============================================================================================

#ifndef	__TVWORK_LOCAL_H__
#define	__TVWORK_LOCAL_H__

#include "savedata/tv_work.h"

//----------------------------------------------------------
//----------------------------------------------------------
enum {
	MY_TOPIC_COMMON_MAX = 4,
	MY_WATCH_MAX = MY_TOPIC_COMMON_MAX,
	MY_RECORD_MAX = MY_TOPIC_COMMON_MAX,
	MY_QANDA_MAX = MY_TOPIC_COMMON_MAX,

	OTHER_WATCH_MAX = 16,
	OTHER_RECORD_MAX = 8,
	OTHER_QANDA_MAX = 8,

	USED_TOPIC_MAX = 4,
};

#define	BROADCAST_MAX		3

//----------------------------------------------------------
/**
 * @brief	トピックデータ本体
 */
//----------------------------------------------------------
struct TVTOPIC{
	u8 topic_id;			///<トピックID
	u8 see_count;			///<視聴回数カウンタ
	GF_DATE date;			///<製作日付
	u8 data[TOPIC_DATA_SIZE];
};

//----------------------------------------------------------
/**
 * @brief	自分トピックデータ
 *
 * トピックデータ以外に付属するものはない
 */
//----------------------------------------------------------
struct MY_TOPIC{
	TVTOPIC topic;		///<トピックデータ本体
};

//----------------------------------------------------------
/**
 * @brief	他人トピックデータ
 *
 * トピックデータ＋製作者情報などが付加される
 */
//----------------------------------------------------------
struct OTHER_TOPIC{
	u32 owner_id;			///<製作者ID
	u8 sex;					///<製作者性別
	u8 rom_ver;				///<製作ROMバージョン
	u8 region_code;			///<製作ROM国コード
	STRCODE owner_name[PERSON_NAME_SIZE + EOM_SIZE];	///<製作者名
	TVTOPIC topic;		///<トピックデータ本体
};

//----------------------------------------------------------
/**
 * @brief	テレビ放送セーブデータ
 */
//----------------------------------------------------------
struct TV_WORK {
	u8 used_index[USED_TOPIC_MAX];				///<放送済みデータインデックス
	int minute_count;							///<放送時間用カウンタ
	u8 end_flag;								///<放映終了フラグ

	MY_TOPIC MyWatchTopic[MY_WATCH_MAX];		///<自分トピックデータ：監視型番組
	MY_TOPIC MyRecordTopic[MY_RECORD_MAX];		///<自分トピックデータ：ギネス型番組
	MY_TOPIC MyQandATopic[MY_QANDA_MAX];		///<自分トピックデータ：質問型番組

	OTHER_TOPIC OtherWatchTopic[OTHER_WATCH_MAX];	///<他人トピックデータ：監視型番組
	OTHER_TOPIC OtherRecordTopic[OTHER_RECORD_MAX];	///<他人トピックデータ：ギネス型番組
	OTHER_TOPIC OtherQandATopic[OTHER_QANDA_MAX];	///<他人トピックデータ：質問型番組

	TOPICTEMP_CONTEST ContestTemp;			///<質問型：コンテスト用状況保持ワーク
	TOPICTEMP_PARK ParkTemp;				///<質問型：連れ歩き公園用状況保持ワーク
	TOPICTEMP_PORUTO PorutoTemp;			///<質問型：ポルト用状況保持ワーク
	TOPICTEMP_BTOWER BTowerTemp;			///<質問型：バトルタワー用状況保持ワーク
	TOPICTEMP_SAFARI SafariTemp;			///<監視型：サファリ用状況保持ワーク
};

#endif	//__TVWORK_LOCAL_H__

