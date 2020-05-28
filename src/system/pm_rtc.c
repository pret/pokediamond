//============================================================================================
/**
 * @file	pm_rtc.c
 * @brief	RTCアクセスラッパー
 * @author	tamada	GAME FREAK inc.
 * @date	2005.11.18
 *
 * 
 * RTCアクセスはARM7で行われ、ARM7とARM9の通信によってユーザープログラムから
 * アクセス可能になる。
 * 資料がないので詳細は不明だが、各アプリケーションが個別にRTCにアクセスすると
 * 処理負荷や割り込みタイミングなどの問題が発生する可能性がある。
 * そのため、メイン処理内で一定間隔でRTCへアクセスし、それを各アプリケーションが
 * 参照する仕組みをとる。
 */
//============================================================================================

#include <nitro.h>
#include <nnsys.h>
#include <standard.h>

#include "gflib/assert.h"

#include "system/pm_rtc.h"

#include "system/timezone.h"

//============================================================================================
//
//				定義など
//
//============================================================================================
//--------------------------------------------------------------
//--------------------------------------------------------------
typedef enum {
	FAKEMODE_DISABLE = 0,
	FAKEMODE_FIX,
	FAKEMODE_FAST,
}FAKEMODE;

//--------------------------------------------------------------
/**
 * @brief	RTC制御用ワーク定義
 */
//--------------------------------------------------------------
typedef struct {
	BOOL access_flag;			///<初回RTC取得したかどうか
	BOOL callback_wait_flag;	///<RTC取得中かどうか
	int count;					///<取得してからのウェイトカウント
	RTCResult result;			///<取得時の状態（デバッグ用）
	RTCDate now_date;			///<現在の日付
	RTCTime now_time;			///<現在の時間
	RTCDate get_date;			///<日付取得用ワーク
	RTCTime get_time;			///<時間取得用ワーク

#ifdef	PM_DEBUG
	FAKEMODE fake_mode;
	s32 rate;
	s64 begin_second;
	s64 rec_second;
	RTCDate dmy_date;
	RTCTime dmy_time;
#endif
}GF_RTC_WORK;

//--------------------------------------------------------------
/**
 * @brief	時間取得の間隔
 * 
 * ポケモンDPでは３０フレームで1秒なので、この値は少なくとも
 * 30以下でなければ秒の更新がおかしくなる
 */
//--------------------------------------------------------------
#define	RTC_CHECK_WAIT	(10)

//--------------------------------------------------------------
/**
 * @brief	RTC制御用ワーク
 */
//--------------------------------------------------------------
static GF_RTC_WORK RtcWork;




#ifdef	PM_DEBUG
static void InitFakeMode(GF_RTC_WORK * wk);
static void StartFakeFastMode(GF_RTC_WORK * wk, int rate);
static void UpdateFakeTime(GF_RTC_WORK * wk);
#endif
//============================================================================================
//
//				関数（初期化・メイン）
//
//============================================================================================
static void CallBackFunc(RTCResult res, void * work);
static void GetAsync(GF_RTC_WORK * wk);
//--------------------------------------------------------------
/**
 * @brief	RTCアクセス初期化
 *
 * 呼び出し直後に、非同期RTCアクセス処理を呼び出している。
 * 割り込み関連の初期化処理が終わってからこの関数を呼ぶ必要がある。
 */
//--------------------------------------------------------------
void GF_RTC_Init(void)
{
	RTC_Init();
	memset(&RtcWork, 0, sizeof(RtcWork));
	RtcWork.access_flag = FALSE;
	RtcWork.callback_wait_flag = FALSE;
	RtcWork.count = 0;
	GetAsync(&RtcWork);

#ifdef	PM_DEBUG
	InitFakeMode(&RtcWork);
#endif
}

//--------------------------------------------------------------
/**
 * @brief	RTCアクセスメイン
 *
 * 一定間隔（RTC_CHECK_WAIT)毎に非同期のRTC取得関数を呼び出すことで
 * 常に時間を保持している。
 */
//--------------------------------------------------------------
void GF_RTC_Main(void)
{
	RTCResult res;

	if (RtcWork.callback_wait_flag) {
		//RTC非同期アクセス中は何もしない
		return;
	}
	RtcWork.count ++;
	if (RtcWork.count > RTC_CHECK_WAIT) {
		//カウンタが一定以上なので非同期アクセスを呼び出し
		RtcWork.count = 0;
		GetAsync(&RtcWork);
	}
}

//--------------------------------------------------------------
/**
 * @brief	RTC非同期アクセス用のコールバック関数
 * @param	res		取得処理の結果
 * @param	work	ユーザー指定ワークへのポインタ（この場合、RtcWork）
 */
//--------------------------------------------------------------
static void CallBackFunc(RTCResult res, void * work)
{
	GF_RTC_WORK * wk = work;

	wk->result = res;
	//正常な場合でもRTC_RESULT_SUCCESS以外を返すことがあるのか未検証。
	//とりあえず、現状はここでASSERTをかけておく
	GF_ASSERT_MSG(res == RTC_RESULT_SUCCESS, "RTC error %d\n", wk->result);

	wk->access_flag = TRUE;			//一度でも取得できたらTRUEにする
	wk->now_date = wk->get_date;	//日付を更新
	wk->now_time = wk->get_time;	//時間を更新
	wk->callback_wait_flag = FALSE;	//コールバック終了

#ifdef	PM_DEBUG
	UpdateFakeTime(&RtcWork);
#endif
}

//--------------------------------------------------------------
/**
 * @brief	RTC非同期アクセスの呼び出し
 */
//--------------------------------------------------------------
static void GetAsync(GF_RTC_WORK * wk)
{
	wk->callback_wait_flag = TRUE;
	wk->result = RTC_GetDateTimeAsync(
			&wk->get_date, &wk->get_time, CallBackFunc, wk);
	GF_ASSERT_MSG(wk->result == RTC_RESULT_SUCCESS, "RTC error %d\n", wk->result);
}


//============================================================================================
//
//			取得用関数
//
//============================================================================================
#ifdef	PM_DEBUG
//--------------------------------------------------------------
/**
 * @brief	偽時間処理の初期化
 * @param	wk		RTC制御ワークへのポインタ
 */
//--------------------------------------------------------------
static void InitFakeMode(GF_RTC_WORK * wk)
{
	wk->fake_mode = FAKEMODE_DISABLE;
	wk->rate = 1;
}
//--------------------------------------------------------------
/**
 * @brief	偽時間処理の開始
 * @param	wk		RTC制御ワークへのポインタ
 * @param	rate	何倍で時間をすすめるかのレート
 */
//--------------------------------------------------------------
static void StartFakeFastMode(GF_RTC_WORK * wk, int rate)
{
	wk->fake_mode = FAKEMODE_FAST;
	wk->rate = rate;
	wk->begin_second = RTC_ConvertDateTimeToSecond(&wk->now_date, &wk->now_time);
	wk->rec_second = wk->begin_second;
	wk->dmy_date = wk->now_date;
	wk->dmy_time = wk->now_time;
}
//--------------------------------------------------------------
//--------------------------------------------------------------
static void StartFakeFixMode(GF_RTC_WORK * wk, int hour, int minute)
{
	wk->fake_mode = FAKEMODE_FIX;
	wk->rate = 1;
	wk->begin_second = RTC_ConvertDateTimeToSecond(&wk->now_date, &wk->now_time);
	wk->rec_second = wk->begin_second;
	wk->dmy_date = wk->now_date;
	wk->dmy_time = wk->now_time;
	wk->dmy_time.hour = hour;
	wk->dmy_time.minute = minute;
}

//--------------------------------------------------------------
/**
 * @brief	偽時間処理の更新処理
 * @param	wk	RTC制御ワークへのポインタ
 */
//--------------------------------------------------------------
static void UpdateFakeTime(GF_RTC_WORK * wk)
{
	s64 now, fake;

	if (wk->fake_mode != FAKEMODE_FAST) {
		return;
	}

	now = RTC_ConvertDateTimeToSecond(&wk->now_date, &wk->now_time);
	if (now == wk->rec_second) {
		return;
	}

	//偽時間　=　偽状態開始時の時間　+　経過時間　×　レート
	fake = wk->begin_second + (now - wk->begin_second) * wk->rate;
	RTC_ConvertSecondToDateTime(&wk->dmy_date, &wk->dmy_time, fake);
	wk->rec_second = now;
}
#endif
//--------------------------------------------------------------
//--------------------------------------------------------------
static inline RTCDate * GetDate(GF_RTC_WORK * wk)
{
#ifdef	PM_DEBUG
	if (wk->fake_mode != FAKEMODE_DISABLE) {
		return &wk->dmy_date;
	} else {
		return &wk->now_date;
	}
#else
	return	&wk->now_date;
#endif
}
//--------------------------------------------------------------
//--------------------------------------------------------------
static inline RTCTime * GetTime(GF_RTC_WORK * wk)
{
#ifdef	PM_DEBUG
	if (wk->fake_mode != FAKEMODE_DISABLE) {
		return &wk->dmy_time;
	} else {
		return &wk->now_time;
	}
#else
	return &wk->now_time;
#endif
}


//============================================================================================
//
//			取得用関数
//
//============================================================================================
//--------------------------------------------------------------
/**
 * @brief	日付＆時間の取得
 * @param	date	日付を受け取るポインタ
 * @param	time	時間を受け取るポインタ
 */
//--------------------------------------------------------------
void GF_RTC_GetDateTime(RTCDate * date, RTCTime * time)
{
	GF_ASSERT(RtcWork.access_flag == TRUE);
	*date = *GetDate(&RtcWork);
	*time = *GetTime(&RtcWork);
}

//--------------------------------------------------------------
/**
 * @brief	時間の取得
 * @param	time	時間を受け取るポインタ
 */
//--------------------------------------------------------------
void GF_RTC_GetTime(RTCTime * time)
{
	GF_ASSERT(RtcWork.access_flag == TRUE);
	*time = *GetTime(&RtcWork);
}

//--------------------------------------------------------------
/**
 * @brief	日付の取得
 * @param	date	日付を受け取るポインタ
 */
//--------------------------------------------------------------
void GF_RTC_GetDate(RTCDate * date)
{
	GF_ASSERT(RtcWork.access_flag == TRUE);
	*date = *GetDate(&RtcWork);
}

//--------------------------------------------------------------
/**
 * @brief	時間の取得（秒数単位）
 * @return	int		秒数に変換した時間（0から86400 - 1の値をとる)
 */
//--------------------------------------------------------------
int GF_RTC_GetTimeBySecond(void)
{
	RTCTime * time;
	time = GetTime(&RtcWork);
	return time->hour * 60 * 60 + time->minute * 60 + time->second;
}

//--------------------------------------------------------------
/**
 * @brief	日付＆時間の取得（秒数単位）
 * @return	s64		秒数に変換した日付＆時間
 */
//--------------------------------------------------------------
s64 GF_RTC_GetDateTimeBySecond(void)
{
	return RTC_ConvertDateTimeToSecond(GetDate(&RtcWork), GetTime(&RtcWork));
}

//--------------------------------------------------------------
//--------------------------------------------------------------
int GF_RTC_GetDaysOffset(const RTCDate * date)
{
	int year, days, count;
	static const u16 d_of_m[12] = {
	0,
	31,
	31+28,
	31+28+31,
	31+28+31+30,
	31+28+31+30+31,
	31+28+31+30+31+30,
	31+28+31+30+31+30+31,
	31+28+31+30+31+30+31+31,
	31+28+31+30+31+30+31+31+30,
	31+28+31+30+31+30+31+31+30+31,
	31+28+31+30+31+30+31+31+30+31+30,
	//31+28+31+30+31+30+31+31+30+31+30+31;
	};

	days = date->day;
	days += d_of_m[date->month - 1];
	if (date->month >= 3) {
		year = date->year;
		if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
			days ++;
		}
	}
#ifdef	DEBUG_ONLY_FOR_tamada
	OS_TPrintf("%04d %2d/%d\n",date->year, date->month, date->day);
	OS_TPrintf("offset %3d", days);
#endif
	{
		int check;
		RTCDate top;
		top = *date;
		top.month = 1;
		top.day = 1;
		check = RTC_ConvertDateToDay(date) - RTC_ConvertDateToDay(&top);
		if (check + 1 != days) {
			OS_Printf("%d(Nitro) != %d(InHouse)\n", check + 1, days);
		}
		//GF_ASSERT(check + 1 == days);
	}
	return days;
}

//============================================================================================
//
//		ツール関数
//
//
//	※純粋にRTCライブラリのラッパーとしての関数ではない。
//	　ポケモンに依存しすぎているため、ライブラリとしては排除するべきかも。
//	　もう少し大きくなってから考慮する。
//============================================================================================
//--------------------------------------------------------------
/**
 * @brief	夜かどうかの判定
 * @retval	TRUE	今は夜
 * @retval	FALSE	今は昼
 */
//--------------------------------------------------------------
BOOL GF_RTC_IsNightTime(void)
{
	switch (GF_RTC_GetTimeZone()) {
	case TIMEZONE_MIDNIGHT:
	case TIMEZONE_NIGHT:
		return TRUE;
	}
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief	時間帯の取得
 * @return	int	時間帯（timezone.hを参照）
 */
//--------------------------------------------------------------
int GF_RTC_GetTimeZone(void)
{
	RTCTime time;
	GF_RTC_GetTime(&time);
	return GF_RTC_ConvertHourToTimeZone(time.hour);
}

//--------------------------------------------------------------
/**
 * @brief	時間から時間帯への変換
 * @param	hour	時間（０－２３）
 * @return	int		時間帯（timezone.hを参照）
 */
//--------------------------------------------------------------
int GF_RTC_ConvertHourToTimeZone(int hour)
{
	static const u8 timezone[24] = {
		//00:00 - 3:59
		TIMEZONE_MIDNIGHT,TIMEZONE_MIDNIGHT,TIMEZONE_MIDNIGHT,TIMEZONE_MIDNIGHT,
		//04:00 - 9:59
		TIMEZONE_MORNING,TIMEZONE_MORNING,TIMEZONE_MORNING,TIMEZONE_MORNING,
		TIMEZONE_MORNING,TIMEZONE_MORNING,
		//10:00 - 16:59
		TIMEZONE_NOON,TIMEZONE_NOON,TIMEZONE_NOON,TIMEZONE_NOON,TIMEZONE_NOON,
		TIMEZONE_NOON,TIMEZONE_NOON,
		//17:00 - 19:59
		TIMEZONE_EVENING,TIMEZONE_EVENING,TIMEZONE_EVENING,
		//20:00 - 23:59
		TIMEZONE_NIGHT,TIMEZONE_NIGHT,TIMEZONE_NIGHT,TIMEZONE_NIGHT
	};
	GF_ASSERT(0 <= hour && hour < 24);
	return timezone[hour];
}

//--------------------------------------------------------------
/**
 * @brief	経過時間の計算
 * @param	start_sec
 * @param	end_sec
 */
//--------------------------------------------------------------
s64 GF_RTC_GetPassTime(s64 start_sec, s64 end_sec)
{
	/** RTCが保持する最大の時間を秒数に変換した値 */
	enum{
		RTC_MAX_SECOND = 3155759999,
	};

	RTCDate date = { 99, 12, 31, 0};
	RTCTime time = { 23, 59, 59 };
	s64 MaxSec = RTC_ConvertDateTimeToSecond(&date, &time);
	GF_ASSERT(MaxSec == RTC_MAX_SECOND);

	if (start_sec < end_sec) {
		return end_sec - start_sec;
	}
	return end_sec + (RTC_MAX_SECOND - start_sec);
}

//============================================================================================
//
//		デバッグ用関数
//
//============================================================================================
#ifdef	PM_DEBUG
//--------------------------------------------------------------
/**
 * @brief	デバッグ用：時間経過促進の開始
 * @param	rate	何倍で時間をすすめるかのレート
 */
//--------------------------------------------------------------
void DEBUG_StartFakeTime(int rate)
{
	StartFakeFastMode(&RtcWork, rate);
}

//--------------------------------------------------------------
/**
 * @brief	デバッグ用：時間経過促進の停止
 */
//--------------------------------------------------------------
void DEBUG_StopFakeTime(void)
{
	InitFakeMode(&RtcWork);
}

//--------------------------------------------------------------
/**
 * @brief	デバッグ用：時間固定
 */
//--------------------------------------------------------------
void DEBUG_StartFakeFixTime(int hour, int minute)
{
	StartFakeFixMode(&RtcWork, hour, minute);
}
#endif

