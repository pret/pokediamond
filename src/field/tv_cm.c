//============================================================================================
/**
 * @file	tv_cm.c
 * @brief	放映するCMの決定
 * @author	tamada GAME FREAK inc.
 * @date	2006.05.17
 */
//============================================================================================

#include "common.h"

#include "fieldsys.h"

#include "savedata/tv_work.h"
#include "savedata/zukanwork.h"
#include "savedata/mystatus.h"
#include "field/eventflag.h"

#include "field/tv_topic.h"

#include "system/pm_rtc.h"
#include "ev_time.h"
#include "sysflag.h"

#include "tv.h"

//============================================================================================
//============================================================================================
//--------------------------------------------------------------------
/**
 * @brief	CMチェック用関数型定義
 */
//--------------------------------------------------------------------
typedef BOOL (*CHECK_CM_FUNC)(FIELDSYS_WORK *);

static BOOL AnytimeEnable(FIELDSYS_WORK * fsys);
static BOOL AnytimeDisable(FIELDSYS_WORK * fsys);
static BOOL C01Check(FIELDSYS_WORK * fsys);
static BOOL T03Check(FIELDSYS_WORK * fsys);
static BOOL C03Check(FIELDSYS_WORK * fsys);
static BOOL C04Check(FIELDSYS_WORK * fsys);
static BOOL C05Check(FIELDSYS_WORK * fsys);
static BOOL C11Check(FIELDSYS_WORK * fsys);
static BOOL GTCOpenCheck(FIELDSYS_WORK * fsys);
static BOOL Get5BadgeCheck(FIELDSYS_WORK * fsys);
static BOOL SinouZukanCompleteCheck(FIELDSYS_WORK * fsys);
static BOOL GingaCMCheck(FIELDSYS_WORK * fsys);
static BOOL ZukanGetCheck(FIELDSYS_WORK * fsys);
static BOOL BattleTowerOpenCheck(FIELDSYS_WORK * fsys);
static BOOL WiFiBattleTowerOpenCheck(FIELDSYS_WORK * fsys);
static BOOL ShipEnableCheck(FIELDSYS_WORK * fsys);
static BOOL GameClearCheck(FIELDSYS_WORK * fsys);



//--------------------------------------------------------------------
/**
 * @brief	放送許可チェックID
 *
 * AllConditionFuncTableと並びを一致させておく必要がある
 */
//--------------------------------------------------------------------
enum {
	FLAG_AnytimeEnable,				///<最初から
	FLAG_T03Check,					///<ソノオ到着
	FLAG_C01Check,					///<コトブキ到着
	FLAG_C03Check,					///<クロガネ到着
	FLAG_C04Check,					///<ハクタイ到着
	FLAG_C05Check,					///<ヨスガ到着
	FLAG_C11Check,					///<C11到着
	FLAG_Get5BadgeCheck,			///<ジムバッジ５個
	FLAG_SinouZukanCompleteCheck,	///<シンオウ図鑑コンプ
	FLAG_ZukanGetCheck,				///<図鑑取得後
	FLAG_GameClearCheck,			///<殿堂入り後

	FLAG_CMCHECK_MAX,
};
//--------------------------------------------------------------------
/**
 * @brief	放送許可チェック関数のテーブル
 */
//--------------------------------------------------------------------
static const CHECK_CM_FUNC AllConditionFuncTable[] = {
	AnytimeEnable,				///<最初から
	T03Check,					///<ソノオ到着
	C01Check,					///<コトブキ到着
	C03Check,					///<クロガネ到着
	C04Check,					///<ハクタイ到着
	C05Check,					///<ヨスガ到着
	C11Check,					///<C11到着
	Get5BadgeCheck,				///<ジムバッジ５個
	SinouZukanCompleteCheck,	///<シンオウ図鑑コンプ
	ZukanGetCheck,				///<図鑑取得後
	GameClearCheck,				///<殿堂入り後
};

//============================================================================================
//
//============================================================================================
//--------------------------------------------------------------------
/**
 * @brief	各CMごとの放送許可条件テーブル
 */
//--------------------------------------------------------------------
static u8 CheckCMTable[] = {
	FLAG_AnytimeEnable,				///<ポケモンセンター	最初から
	FLAG_AnytimeEnable,				///<フレンドリィショップ	最初から
	FLAG_AnytimeEnable,				///<ＴＶ局	最初から
	FLAG_AnytimeEnable,				///<トレーナースクール	最初から
	FLAG_AnytimeEnable,				///<ポケッチ	最初から
	FLAG_C01Check,					///<ポケッチソフト	
	FLAG_T03Check,					///<花屋	ソノオ到着
	FLAG_C04Check,					///<自転車屋	ハクタイ到着
	FLAG_C04Check,					///<コンテストＣＭ	ハクタイ到着
	FLAG_C05Check,					///<ゲームコーナー	ヨスガ到着
	FLAG_C05Check,					///<自然公園	ヨスガ到着
	FLAG_C05Check,					///<トバリデパート	ヨスガ到着
	FLAG_C05Check,					///<育て屋	ヨスガ到着
	FLAG_C05Check,					///<ホテル	ヨスガ到着
	FLAG_C05Check,					///<大湿原	ヨスガ到着
	FLAG_Get5BadgeCheck,				///<キッサキシティ	ジムバッジ５個
	FLAG_Get5BadgeCheck,				///<ナギサ市場	ジムバッジ５個
	FLAG_C03Check,					///<ＧＴＣ	クロガネ到着
	FLAG_SinouZukanCompleteCheck,	///<ポケモンパーク	シンオウ図鑑コンプ
	FLAG_GameClearCheck,			///<キッサキシティの船	シンオウ図鑑コンプ
	FLAG_GameClearCheck,			///<バトルゾーン	シンオウ図鑑コンプ
	FLAG_SinouZukanCompleteCheck,	///<会員制の建物	シンオウ図鑑コンプ
	FLAG_C05Check,					///<ギンガ団１	ヨスガ到着
	FLAG_C05Check,					///<ギンガ団２	ヨスガ到着
	FLAG_ZukanGetCheck,				///<ポケモンセンター通信編	図鑑取得後
	FLAG_ZukanGetCheck,				///<ポケモンセンターWi-Fi編	図鑑取得後
	FLAG_C11Check,					///<バトルタワー	C11到着
	FLAG_C11Check,					///< Wi-Fiバトルタワー	C11到着
	FLAG_GameClearCheck,				///<乗り物ＣＭ（船）	殿堂入り後
};

//============================================================================================
//============================================================================================

//--------------------------------------------------------------------
//--------------------------------------------------------------------
static BOOL AnytimeEnable(FIELDSYS_WORK * fsys)
{
	return TRUE;
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static BOOL AnytimeDisable(FIELDSYS_WORK * fsys)
{
	return FALSE;
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static BOOL C01Check(FIELDSYS_WORK * fsys)
{
	EVENTWORK * ev = SaveData_GetEventWork(fsys->savedata);
	return SysFlag_ArriveGet(ev, FLAG_ARRIVE_C01);
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------
static BOOL T03Check(FIELDSYS_WORK * fsys)
{
	EVENTWORK * ev = SaveData_GetEventWork(fsys->savedata);
	return SysFlag_ArriveGet(ev, FLAG_ARRIVE_T03);
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static BOOL C03Check(FIELDSYS_WORK * fsys)
{
	EVENTWORK * ev = SaveData_GetEventWork(fsys->savedata);
	return SysFlag_ArriveGet(ev, FLAG_ARRIVE_C03);
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static BOOL C04Check(FIELDSYS_WORK * fsys)
{
	EVENTWORK * ev = SaveData_GetEventWork(fsys->savedata);
	return SysFlag_ArriveGet(ev, FLAG_ARRIVE_C04);
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static BOOL C05Check(FIELDSYS_WORK * fsys)
{
	EVENTWORK * ev = SaveData_GetEventWork(fsys->savedata);
	return SysFlag_ArriveGet(ev, FLAG_ARRIVE_C05);
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static BOOL C11Check(FIELDSYS_WORK * fsys)
{
	EVENTWORK * ev = SaveData_GetEventWork(fsys->savedata);
	return SysFlag_ArriveGet(ev, FLAG_ARRIVE_C11);
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static BOOL GTCOpenCheck(FIELDSYS_WORK * fsys)
{
	EVENTWORK * ev = SaveData_GetEventWork(fsys->savedata);
	return SysFlag_GTCOpenCheck(ev);
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static BOOL Get5BadgeCheck(FIELDSYS_WORK * fsys)
{
	MYSTATUS * my = SaveData_GetMyStatus(fsys->savedata);
	if (MyStatus_GetBadgeCount(my) >= 5) {
		return TRUE;
	} else {
		return FALSE;
	}
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static BOOL SinouZukanCompleteCheck(FIELDSYS_WORK * fsys)
{
	ZUKAN_WORK * zw = SaveData_GetZukanWork(fsys->savedata);
	return ZukanWork_CheckShinouComp(zw);
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------
static BOOL GingaCMCheck(FIELDSYS_WORK * fsys)
{
	return FALSE;
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static BOOL ZukanGetCheck(FIELDSYS_WORK * fsys)
{
	ZUKAN_WORK * zw = SaveData_GetZukanWork(fsys->savedata);
	return ZukanWork_GetZukanGetFlag(zw);
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static BOOL BattleTowerOpenCheck(FIELDSYS_WORK * fsys)
{
	EVENTWORK * ev = SaveData_GetEventWork(fsys->savedata);
	return SysFlag_BTowerOpenCheck(ev);
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static BOOL WiFiBattleTowerOpenCheck(FIELDSYS_WORK * fsys)
{
	EVENTWORK * ev = SaveData_GetEventWork(fsys->savedata);
	return SysFlag_BTowerOpenCheck(ev);
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static BOOL ShipEnableCheck(FIELDSYS_WORK * fsys)
{
	EVENTWORK * ev = SaveData_GetEventWork(fsys->savedata);
	return SysFlag_ShipCheck(ev);
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static BOOL GameClearCheck(FIELDSYS_WORK * fsys)
{
	EVENTWORK * ev = SaveData_GetEventWork(fsys->savedata);
	return SysFlag_GameClearCheck(ev);
}



//============================================================================================
//============================================================================================
//--------------------------------------------------------------------
/**
 * @brief	放映可能なCMの抽出処理
 */
//--------------------------------------------------------------------
static int ChooseEnableCMID(FIELDSYS_WORK * fsys, u8 * cm_array)
{
	int i,n;
	BOOL check_list[NELEMS(AllConditionFuncTable)];

	GF_ASSERT(NELEMS(AllConditionFuncTable) == FLAG_CMCHECK_MAX);
	//条件を全チェック
	for (i = 0; i < NELEMS(AllConditionFuncTable); i++) {
		check_list[i] = AllConditionFuncTable[i](fsys);
	}
	//CMごとに条件が成立しているかチェック
	for (i = 0, n = 0; i < NELEMS(CheckCMTable); i++) {
		if (check_list[CheckCMTable[i]]) {
			cm_array[n] = i;
			n ++;
		}
	}
	return n;
}

//--------------------------------------------------------------------
/**
 * @brief	CMを抽出、その中からランダムでIDを取得する
 */
//--------------------------------------------------------------------
int TVCM_ChooseID(FIELDSYS_WORK * fsys)
{
	u8 cm_id[32];
	int max;
	MI_CpuClear8(cm_id, 32);
	max = ChooseEnableCMID(fsys, cm_id);
	if (max == 0) {
		return 0;
	}
	return cm_id[gf_mtRand() % max];
}






