//============================================================================================
/**
 * @file	tvwork_record.c
 * @brief	テレビデータのレコード処理
 * @author	tamada GAME FREAK inc.
 * @date	2006.05.31
 *
 * レコード処理から呼ばれるために常駐領域に配置されていない。
 * そのためどこからでも呼べるわけではないことに注意
 */
//============================================================================================

#include "common.h"
#include "savedata/savedata_def.h"
#include "system/gamedata.h"

#include "gflib/gf_date.h"

#include "savedata/tv_work.h"
#include "tvwork_local.h"

#include "field/tv_topic.h"

#include "system/pm_rtc.h"
#include "system/pm_str.h"


#ifdef	DEBUG_ONLY_FOR_tamada
#define	DEBUG_PRT_TAMADA(...)	OS_TPrintf( __VA_ARGS__ )
#else
#define	DEBUG_PRT_TAMADA(...)	((void)0)
#endif

//============================================================================================
//
//			定義など
//
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	送受信するテレビトピックの数
 */
//----------------------------------------------------------
#define	TV_RECV_MAX			(4)			

//----------------------------------------------------------
/**
 * @brief	通信する人数
 *
 * 想定できないのでとりあえず。実際は5人確定か？
 */
//----------------------------------------------------------
#define	TV_COMM_MEMBER_MAX	(16)

//============================================================================================
//
//			送信データサイズ取得
//
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	テレビ用送信データサイズ
 * @param	sv		セーブデータへのアドレス
 * @return	u32		送信データのサイズ
 */
//----------------------------------------------------------
u32 TVWORK_GetSendQandADataSize(const SAVEDATA * sv)
{
	return sizeof(SEND_TOPIC) * MY_QANDA_MAX;
}
//----------------------------------------------------------
/**
 * @brief	テレビ用送信データサイズ
 * @param	sv		セーブデータへのアドレス
 * @return	u32		送信データのサイズ
 */
//----------------------------------------------------------
u32 TVWORK_GetSendWatchDataSize(const SAVEDATA * sv)
{
	return sizeof(SEND_TOPIC) * MY_WATCH_MAX;
}

//----------------------------------------------------------
/**
 * @brief	テレビ用送信データサイズ
 * @param	sv		セーブデータへのアドレス
 * @return	u32		送信データのサイズ
 */
//----------------------------------------------------------
u32 TVWORK_GetSendRecordDataSize(const SAVEDATA * sv)
{
	return sizeof(SEND_TOPIC) * MY_RECORD_MAX;
}


//============================================================================================
//
//
//			送信データ生成
//
//
//============================================================================================
//----------------------------------------------------------
/**
 * @brief		自分データから送信データを作成する
 * @param		sv		セーブデータへのアドレス
 * @param		send	送信データを格納するバッファ
 * @param		mt		自分データへのポインタ
 * @param		max		自分データの数
 */
//----------------------------------------------------------
static void MakeSendTopicByMyTopic(SAVEDATA * sv, SEND_TOPIC * send,
		MY_TOPIC * mt, int max)
{
	int i;
	MYSTATUS * my = SaveData_GetMyStatus(sv);

	for (i = 0; i < max; i++, send++) {
		MI_CpuClearFast(send, sizeof(SEND_TOPIC));

		//送信者情報を埋め込む
		send->owner_id = MyStatus_GetID(my);
		send->sex = MyStatus_GetMySex(my);
		send->rom_ver = PM_VERSION;
		send->region_code = PM_LANG;
		PM_strncpy(send->owner_name, MyStatus_GetMyName(my), PERSON_NAME_SIZE + EOM_SIZE);

		send->topic = mt[i].topic;
		send->topic.see_count = 0;	//送信データの視聴カウントはクリア
	}
	//送信データを生成したら自分データは削除する
	//MI_CpuClearFast(mt, sizeof(MY_TOPIC) * max);
}
//----------------------------------------------------------
/**
 * @brief	質問型トピック生成データをAlloc
 * @param	sv
 * @param	headID
 * @param	size
 */
//----------------------------------------------------------
SEND_TOPIC * TVWORK_AllocSendQandAData(SAVEDATA * sv, int headID, u32 size)
{
	SEND_TOPIC * buf;
	TV_WORK * tvwk;
	buf = sys_AllocMemoryLo(headID, size);
	tvwk = SaveData_GetTvWork(sv);
	GF_ASSERT(size == TVWORK_GetSendQandADataSize(sv));
	MakeSendTopicByMyTopic(sv, buf, tvwk->MyQandATopic, MY_QANDA_MAX);
	return buf;
}
//----------------------------------------------------------
/**
 * @brief	監視型トピック生成データをAlloc
 * @param	sv
 * @param	headID
 * @param	size
 */
//----------------------------------------------------------
SEND_TOPIC * TVWORK_AllocSendWatchData(SAVEDATA * sv, int headID, u32 size)
{
	SEND_TOPIC * buf;
	TV_WORK * tvwk;
	buf = sys_AllocMemoryLo(headID, size);
	tvwk = SaveData_GetTvWork(sv);
	GF_ASSERT(size == TVWORK_GetSendWatchDataSize(sv));
	MakeSendTopicByMyTopic(sv, buf, tvwk->MyWatchTopic, MY_WATCH_MAX);
	return buf;
}
//----------------------------------------------------------
/**
 * @brief	ギネス型トピック生成データをAlloc
 * @param	sv
 * @param	headID
 * @param	size
 */
//----------------------------------------------------------
SEND_TOPIC * TVWORK_AllocSendRecordData(SAVEDATA * sv, int headID, u32 size)
{
	SEND_TOPIC * buf;
	TV_WORK * tvwk;
	buf = sys_AllocMemoryLo(headID, size);
	tvwk = SaveData_GetTvWork(sv);
	GF_ASSERT(size == TVWORK_GetSendRecordDataSize(sv));
	MakeSendTopicByMyTopic(sv, buf, tvwk->MyRecordTopic, MY_RECORD_MAX);
	return buf;
}


//============================================================================================
//
//
//			受信データ処理
//
//
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	受信トピックを他人トピック領域にセットする
 * @param	ot			他人トピック領域へのポインタ
 * @param	max			他人トピック領域のサイズ
 * @param	st			受信トピックデータ
 * @retval	TRUE		新たにセットした
 * @retval	FALSE		セットしなかった
 */
//----------------------------------------------------------
static BOOL AddOtherTopic(OTHER_TOPIC * ot, int max, const SEND_TOPIC * st)
{
	int i;
	if (st->topic.topic_id == 0) {
		DEBUG_PRT_TAMADA("NULL topic tr_id=%d\n",st->owner_id & 0xffff);
		//空のトピックデータが来た場合
		return FALSE;
	}
	for (i = 0; i < max; i++) {
		if (ot[i].topic.topic_id == 0) {
			DEBUG_PRT_TAMADA("SET! pos=%d topic=%d tr_id=%d\n",i, st->topic.topic_id, st->owner_id & 0xffff);
			ot[i] = *st;
			return TRUE;
		}
	}
	for (i = 0; i < max; i++) {
		if (ot[i].topic.see_count >= BROADCAST_MAX) {
			DEBUG_PRT_TAMADA("SET! pos=%d topic=%d tr_id=%d\n",i, st->topic.topic_id, st->owner_id & 0xffff);
			ot[i] = *st;
			return TRUE;
		}
	}
	return FALSE;
}
//----------------------------------------------------------
/**
 * @brief	テレビ受信データまぜる処理本体
 * @param	ot			他人トピック領域へのポインタ
 * @param	max			他人トピック領域のサイズ
 * @param	member		通信人数
 * @param	my_id		自分の通信ID
 * @param	darray		受信データへのポインタの配列へのポインタ
 */
//----------------------------------------------------------
static void MixRecvData(OTHER_TOPIC * ot, int max, int member, int my_id, const void ** darray)
{
	u8 count[TV_COMM_MEMBER_MAX];
	int pos, i, j;
	DEBUG_PRT_TAMADA("OT=%08x max=%2d my_id=%5d\n", ot, max, my_id);
	for (i = 0; i < member; i++) {
		DEBUG_PRT_TAMADA("ID[%d]%08x\n", i, darray[i]);
	}

	MI_CpuClear8(count, TV_COMM_MEMBER_MAX);

	pos = 0;
	for (i = 0; i < member; i++) {
		if (darray[i] == NULL) { continue; }//いない場合は次の人へ
		for (j = 0; j < TV_RECV_MAX; j ++) {
			while (darray[pos] == NULL || pos == i || count[pos] == TV_RECV_MAX) {
				//いない人と自分とすでにもらいすぎの人はパス
				pos ++;
				pos %= member;
			}
			count[pos] ++;
			DEBUG_PRT_TAMADA(" %d[%d]->%d[%d]",i,j, pos, count[pos]);
			if (pos != my_id) {
				//人のデータの場合、追加する
				AddOtherTopic(ot, max, &((SEND_TOPIC *)darray[pos])[j]);
			}
		}
		DEBUG_PRT_TAMADA("\n");
	}
}

//----------------------------------------------------------
/**
 * @brief	テレビ用データ混ぜる処理（監視型）
 * @param	tvwk			テレビデータへのポインタ
 * @param	member		通信人数
 * @param	my_id		自分の通信ID
 * @param	darray		受信データへのポインタの配列へのポインタ
 *
 */
//----------------------------------------------------------
void TVWORK_MixWatchData(TV_WORK * tv, int member, int my_id, const void ** darray)
{
	MixRecvData(tv->OtherWatchTopic, OTHER_WATCH_MAX, member, my_id, darray);
}

//----------------------------------------------------------
/**
 * @brief	テレビ用データ混ぜる処理（質問型）
 * @param	tvwk			テレビデータへのポインタ
 * @param	member		通信人数
 * @param	my_id		自分の通信ID
 * @param	darray		受信データへのポインタの配列へのポインタ
 *
 */
//----------------------------------------------------------
void TVWORK_MixRecordData(TV_WORK * tv, int member, int my_id, const void ** darray)
{
	MixRecvData(tv->OtherRecordTopic, OTHER_RECORD_MAX, member, my_id, darray);
}

//----------------------------------------------------------
/**
 * @brief	テレビ用データまぜる処理（質問型）
 * @param	tvwk			テレビデータへのポインタ
 * @param	member		通信人数
 * @param	my_id		自分の通信ID
 * @param	darray		受信データへのポインタの配列へのポインタ
 *
 */
//----------------------------------------------------------
void TVWORK_MixQandAData(TV_WORK * tv, int member, int my_id, const void ** darray)
{
	MixRecvData(tv->OtherQandATopic, OTHER_QANDA_MAX, member, my_id, darray);
}

