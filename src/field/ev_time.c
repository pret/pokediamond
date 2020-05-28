//============================================================================================
/**
 * @file	ev_time.c
 * @brief	ゲーム内時間制御関連
 * @author	tamada
 * @date	2006.02.03
 */
//============================================================================================

#include "common.h"

#include "system/pm_rtc.h"

#include "fieldsys.h"

#include "savedata/savedata.h"
#include "savedata/seedbed.h"
#include "savedata/undergrounddata.h"  // UnderGroundDataDayUpdate
#include "savedata/randomgroup.h"
#include "savedata/honeytree_data.h"
#include "savedata/encount.h"
#include "savedata/tv_work.h"
#include "savedata/b_tower.h"
#include "savedata/wifihistory.h"

#include "situation_local.h"


#include "ev_time.h"

#include "savedata/gametime.h"

#include "system/timezone.h"

#include "seedsys.h"

#include "script.h"

#include "tr_card_time.h"

#include "poketool/poke_tool.h"

#include "syswork.h"

#include "b_tower_ev.h"

//============================================================================================
//============================================================================================

//============================================================================================
//============================================================================================
static void UpdateDayEvent(FIELDSYS_WORK * fsys, s32 diff_days);
static void UpdateMinuteEvent(FIELDSYS_WORK * fsys, s32 diff_minute, const RTCTime * now);

static void UpdateDateCheck(FIELDSYS_WORK * fsys, GMTIME * tm, const RTCDate * now_date);
static void UpdateMinuteCheck(FIELDSYS_WORK * fsys, GMTIME * tm,
		const RTCDate * now_date, const RTCTime * now_time);

//============================================================================================
//============================================================================================
//------------------------------------------------------------------
/**
 */
//------------------------------------------------------------------
void EVTIME_Update(FIELDSYS_WORK * fsys)
{
	RTCDate now_date;
	RTCTime now_time;
	GMTIME * tm = SaveData_GetGameTime(fsys->savedata);

	if (tm->use_flag == FALSE) {
		return;
	}

	GF_RTC_GetDateTime(&now_date, &now_time);

	UpdateDateCheck(fsys, tm, &now_date);
	UpdateMinuteCheck(fsys, tm, &now_date, &now_time);
}

//------------------------------------------------------------------
///日数経過を見る
//------------------------------------------------------------------
static void UpdateDateCheck(FIELDSYS_WORK * fsys, GMTIME * tm, const RTCDate * now_date)
{
	s32 now_day;
	now_day = RTC_ConvertDateToDay(now_date);

	if (now_day < tm->sv_day) {
		//現在　＜　過去　…ありえないはず
		//現在時間をセットするだけで戻る
		tm->sv_day = now_day;
		return;
	}
	if (now_day > tm->sv_day) {
		UpdateDayEvent(fsys, now_day - tm->sv_day);
		tm->sv_day = now_day;
	}
}

//------------------------------------------------------------------
///秒数経過を見る
//------------------------------------------------------------------
static void UpdateMinuteCheck(FIELDSYS_WORK * fsys, GMTIME * tm,
		const RTCDate * now_date, const RTCTime * now_time)
{
	s64 now, sv;
	s32 diff_minute;
	now = RTC_ConvertDateTimeToSecond(now_date, now_time);
	sv = RTC_ConvertDateTimeToSecond(&tm->sv_date, &tm->sv_time);
	if (now < sv) {
		//現在　＜　過去　…ありえないはず
		//現在時間をセットするだけで戻る
		tm->sv_date = *now_date;
		tm->sv_time = *now_time;
		return;
	}
	diff_minute = (now - sv) / 60;
	if (diff_minute > 0) {
		GMTIME_CountDownPenaltyTime(tm, diff_minute);
		UpdateMinuteEvent(fsys, diff_minute, now_time);

		tm->sv_date = *now_date;
		tm->sv_time = *now_time;
	}
}

//============================================================================================
//============================================================================================
//------------------------------------------------------------------
/**
 * @brief	時間によるデータ更新：日数単位
 * @param	fsys			フィールド制御ワークへのポインタ
 * @param	diff_days		経過した時間（日数）
 *
 * 引数にFIELDSYS_WORKをとっているが、基本的にはSAVEDATAのみで
 * 更新できるような仕組みの関数を呼ぶべき。
 */
//------------------------------------------------------------------
static void UpdateDayEvent(FIELDSYS_WORK * fsys, s32 diff_days)
{
	
	//下記のような感じで時間関連イベント更新処理を追加する
	//
	//TVData_Update(fsys, diff_days);
	//ZukanHyouka_Update
	//…

    // 地下の日数経過に関連した処理
    UnderGroundDataDayUpdate(GameSystem_GetSaveData(fsys), diff_days);

	//1日毎にクリアするフラグ
	TimeEventFlagClear(fsys);

	//トレーナーケースのバッジを腐らせる
	TRCTIME_CorrodeBadge(fsys->savedata, diff_days);	

	// 乱数の種グループ更新
	RandomGroup_Update(SaveData_GetRandomGroup(fsys->savedata), diff_days);

	//エンカウント関連ランダムの種更新
	EncDataSave_UpdateRandSeed(EncDataSave_GetSaveDataPtr( fsys->savedata ),
			RandomGroup_GetDefaultRandom( SaveData_GetRandomGroup(fsys->savedata) ) );

	//ポケルス感染の経過を見る by soga 2006.05.16
	{
		POKEPARTY *ppt;

		ppt=SaveData_GetTemotiPokemon(fsys->savedata);
		PokerusCounterDec(ppt,diff_days);
	}

	//新聞社イベント用。しめきり日数を更新 by tomo 2006.5.17
	{
		EVENTWORK * ev = SaveData_GetEventWork(fsys->savedata);
		u16 onedaywork = SysWork_NewsDaysCountGet( ev );
		if (onedaywork > diff_days) {
			onedaywork -= diff_days;
		} else {
			onedaywork = 0;
		}
		SysWork_NewsDaysCountSet( ev , onedaywork );
	}

	//ポケモンクジ
	{
		SysWorkUpdatePokeLot(fsys->savedata, diff_days);
	}

	//アイテムおじさん
	{
		SysWorkUpdatePokeLevelNo(fsys->savedata);
	}


	//バトルタワーDayランダムシード一日一回の更新処理
	BtlTower_UpdateDayRndSeed(fsys->savedata);

	//WIFI通信履歴データの更新処理
	WIFIHISTORY_Update(SaveData_GetWifiHistory(fsys->savedata));
}

//------------------------------------------------------------------
/**
 * @brief	時間によるデータ更新：分単位
 * @param	fsys			フィールド制御ワークへのポインタ
 * @param	diff_minute		経過した時間（分単位）
 *
 * 引数にFIELDSYS_WORKをとっているが、基本的にはSAVEDATAのみで
 * 更新できるような仕組みの関数を呼ぶべき。
 */
//------------------------------------------------------------------
static void UpdateMinuteEvent(FIELDSYS_WORK * fsys, s32 diff_minute, const RTCTime * now)
{
	SeedSys_Growth(fsys, diff_minute);
///	HTE_UpdateHoneyTreeTime(fsys, diff_minute);
	HTSave_UpdateHoneyTreeTime(fsys->savedata, diff_minute);
    UnderGroundDataMinUpdate(fsys->savedata, diff_minute, EVTIME_IsPenaltyMode(fsys));

	{
		TV_WORK * tvwk = SaveData_GetTvWork(fsys->savedata);
		TVWORK_UpdateMinuteCount(tvwk, diff_minute, now->minute);
	}
}




//============================================================================================
//============================================================================================
//------------------------------------------------------------------
/**
 * @brief	時間帯の取得
 * @param	fsys	フィールド制御ワークへのポインタ
 * @return	int		時間帯（field/timezone.hを参照）
 */
//------------------------------------------------------------------
int EVTIME_GetTimeZone(const FIELDSYS_WORK * fsys)
{
	GMTIME * tm = SaveData_GetGameTime(fsys->savedata);
	return GF_RTC_ConvertHourToTimeZone(tm->sv_time.hour);

}
//------------------------------------------------------------------
/**
 * @brief	イベント時間（月）の取得
 * @param	fsys	フィールド制御ワークへのポインタ
 * @return	int		月
 */
//------------------------------------------------------------------
int EVTIME_GetMonth(const FIELDSYS_WORK * fsys)
{
	GMTIME * tm = SaveData_GetGameTime(fsys->savedata);
	return tm->sv_date.month;
}
//------------------------------------------------------------------
/**
 * @brief	イベント時間（日）の取得
 * @param	fsys	フィールド制御ワークへのポインタ
 * @return	int		日
 */
//------------------------------------------------------------------
int EVTIME_GetDay(const FIELDSYS_WORK * fsys)
{
	GMTIME * tm = SaveData_GetGameTime(fsys->savedata);
	return tm->sv_date.day;
}
//------------------------------------------------------------------
/**
 * @brief	イベント時間（曜日）の取得
 * @param	fsys	フィールド制御ワークへのポインタ
 * @return	int		曜日
 */
//------------------------------------------------------------------
int EVTIME_GetWeek(const FIELDSYS_WORK * fsys)
{
	GMTIME * tm = SaveData_GetGameTime(fsys->savedata);
	return tm->sv_date.week;
}
//------------------------------------------------------------------
/**
 * @brief	イベント時間（時）の取得
 * @param	fsys	フィールド制御ワークへのポインタ
 * @return	int		時間
 */
//------------------------------------------------------------------
int EVTIME_GetHour(const FIELDSYS_WORK * fsys)
{
	GMTIME * tm = SaveData_GetGameTime(fsys->savedata);
	return tm->sv_time.hour;
}
//------------------------------------------------------------------
/**
 * @brief	イベント時間（分）の取得
 * @param	fsys	フィールド制御ワークへのポインタ
 * @return	int		分
 */
//------------------------------------------------------------------
int EVTIME_GetMinute(const FIELDSYS_WORK * fsys)
{
	GMTIME * tm = SaveData_GetGameTime(fsys->savedata);
	return tm->sv_time.minute;
}


//------------------------------------------------------------------
/**
 * @brief	ゲーム開始の日付＆時間取得
 * @param	fsys	フィールド制御ワークへのポインタ
 * @param	date	ゲーム開始の日付を受け取るためのRTCDate型へのポインタ
 * @param	time	ゲーム開始の時間を受け取るためのRTCTime型へのポインタ
 */
//------------------------------------------------------------------
void EVTIME_GetGameStartDateTime(const FIELDSYS_WORK * fsys, RTCDate * date, RTCTime * time)
{
	GMTIME * tm = SaveData_GetGameTime(fsys->savedata);
	RTC_ConvertSecondToDateTime(date, time, tm->start_sec);
}

//------------------------------------------------------------------
/**
 * @brief	ゲームクリアの日付＆時間取得
 * @param	fsys	フィールド制御ワークへのポインタ
 * @param	date	ゲーム開始の日付を受け取るためのRTCDate型へのポインタ
 * @param	time	ゲーム開始の時間を受け取るためのRTCTime型へのポインタ
 */
//------------------------------------------------------------------
void EVTIME_GetGameClearDateTime(const FIELDSYS_WORK * fsys, RTCDate * date, RTCTime * time)
{
	GMTIME * tm = SaveData_GetGameTime(fsys->savedata);
	RTC_ConvertSecondToDateTime(date, time, tm->clear_sec);
}

//------------------------------------------------------------------
/**
 * @brief	ゲームクリアの日付＆時間セット
 * @param	fsys	フィールド制御ワークへのポインタ
 */
//------------------------------------------------------------------
void EVTIME_SetGameClearDateTime(const FIELDSYS_WORK * fsys)
{
	GMTIME * tm = SaveData_GetGameTime(fsys->savedata);
	tm->clear_sec = GF_RTC_GetDateTimeBySecond();

}

//------------------------------------------------------------------
/**
 * @brief	DS設定変更のペナルティモードかどうかの判定
 * @param	fsys	フィールド制御ワークへのポインタ
 * @return	BOOL	TRUEのとき、ペナルティ中
 */
//------------------------------------------------------------------
BOOL EVTIME_IsPenaltyMode(FIELDSYS_WORK * fsys)
{
	GMTIME * gt = SaveData_GetGameTime(fsys->savedata);
	return GMTIME_IsPenaltyMode(gt);
}


