//============================================================================================
/**
 * @brief	playtime.c
 * @brief	プレイ時間操作
 * @date	2006.03.09
 * @author	tamada
 */
//============================================================================================

#include "savedata/playtime.h"
#include "playtime_local.h"
#include "gflib/assert.h"

enum {
	PLAYTIME_HOUR_MAX = 999,
	PLAYTIME_MINUTE_MAX = 59,
	PLAYTIME_SECOND_MAX = 59,
};
//============================================================================================
//============================================================================================
//---------------------------------------------------------------------------
/**
 * @brief	プレイ時間の初期化処理
 * @param	ptime	プレイ時間へのポインタ
 */
//---------------------------------------------------------------------------
void PLAYTIME_Init(PLAYTIME * ptime)
{
	ptime->hour = 0;
	ptime->minute = 0;
	ptime->second = 0;
}

//---------------------------------------------------------------------------
/**
 * @brief	プレイ時間のセット
 * @param	ptime	プレイ時間へのポインタ
 * @param	hour	時間
 * @param	min		分
 * @param	sec		秒
 *
 * 指定したプレイ時間にセットする処理。
 * デバッグでしか使用しない？
 */
//---------------------------------------------------------------------------
void PLAYTIME_Set(PLAYTIME * ptime, u32 hour, u32 min, u32 sec)
{
	GF_ASSERT(hour <= PLAYTIME_HOUR_MAX); 
	GF_ASSERT(min <= PLAYTIME_MINUTE_MAX); 
	GF_ASSERT(sec <= PLAYTIME_SECOND_MAX); 
	ptime->hour = hour;
	ptime->minute = min;
	ptime->second = sec;
}

//---------------------------------------------------------------------------
/**
 * @brief
 * @param	ptime	プレイ時間へのポインタ
 * @return
 */
//---------------------------------------------------------------------------
void PLAYTIME_CountUp(PLAYTIME * ptime, u32 passed_sec)
{
	u32 hour, min, sec;

	if( (ptime->hour == PLAYTIME_HOUR_MAX)
	&&	(ptime->minute == PLAYTIME_MINUTE_MAX)
	&&	(ptime->second == PLAYTIME_SECOND_MAX)
	){
		return;
	}

	hour = ptime->hour;
	min = ptime->minute;
	sec = ptime->second + passed_sec;
	if( sec > PLAYTIME_SECOND_MAX )
	{
		min = ptime->minute + (sec / (PLAYTIME_SECOND_MAX+1));
		sec %= (PLAYTIME_SECOND_MAX+1);
		if( min > PLAYTIME_MINUTE_MAX )
		{
			hour = ptime->hour + (min / (PLAYTIME_MINUTE_MAX+1));
			min %= (PLAYTIME_MINUTE_MAX+1);
			if( hour >= PLAYTIME_HOUR_MAX )
			{
				hour = PLAYTIME_HOUR_MAX;
				min = PLAYTIME_MINUTE_MAX;
				sec = PLAYTIME_SECOND_MAX;
			}
		}
	}

	ptime->hour = hour;
	ptime->minute = min;
	ptime->second = sec;
}

//---------------------------------------------------------------------------
/**
 * @brief
 * @param	ptime	プレイ時間へのポインタ
 * @return
 */
//---------------------------------------------------------------------------
u16 PLAYTIME_GetHour(const PLAYTIME * ptime)
{
	return ptime->hour;
}

//---------------------------------------------------------------------------
/**
 * @brief
 * @param	ptime	プレイ時間へのポインタ
 * @return
 */
//---------------------------------------------------------------------------
u8 PLAYTIME_GetMinute(const PLAYTIME * ptime)
{
	return ptime->minute;
}

//---------------------------------------------------------------------------
/**
 * @brief
 * @param	ptime	プレイ時間へのポインタ
 * @return
 */
//---------------------------------------------------------------------------
u8 PLAYTIME_GetSecond(const PLAYTIME * ptime)
{
	return ptime->second;
}

