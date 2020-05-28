//============================================================================================
/**
 * @file	mapdata_weather.c
 * @brief
 * @author	tamada GAME FREAK inc.
 * @date	2006.03.11
 */
//============================================================================================

#include "common.h"

#include "fieldsys.h"

#include "mapdata_weather.h"
#include "mapdata_weather_def.h"

#include "zonedata.h"

#include "system/pm_rtc.h"
#include "savedata/gametime.h"
#include "ev_time.h"

#define	CAL_RAIN		(WEATHER_SYS_RAIN)
#define	CAL_STRAIN		(WEATHER_SYS_STRAIN)
#define CAL_SPARK		(WEATHER_SYS_SPARK)
#define	CAL_RAINBOW		(WEATHER_SYS_RAINBOW)
#define	CAL_CLOUDINESS	(WEATHER_SYS_CLOUDINESS)
#define	CAL_SNOW		(WEATHER_SYS_SNOW)
#define	CAL_SNOWSTORM	(WEATHER_SYS_SNOWSTORM)
#define CAL_SNOWSTORM_H	(WEATHER_SYS_SNOWSTORM_H)
#define	CAL_DIAMONDDUST	(WEATHER_SYS_DIAMONDDUST)
#define	CAL_FOG			(WEATHER_SYS_FOG)
#define	CAL_SUNNY		(WEATHER_SYS_SUNNY)
#define	CAL_SANDSTORM	(WEATHER_SYS_SANDSTORM)
#define	CAL_VOLCANO		(WEATHER_SYS_VOLCANO)


#include "caldata.dat"
//============================================================================================
//============================================================================================
//------------------------------------------------------------------
//------------------------------------------------------------------
int WeatherData_Get(FIELDSYS_WORK * fsys, int now_zone_id)
{
	int weather;

	weather = ZoneData_GetWeatherID(now_zone_id);
#ifdef	DEBUG_ONLY_FOR_tamada
		OS_Printf("WEATHER ID = %d\n",weather);
#endif
	if (weather < WEATHER_SYS_CAL_START) {
		return weather;
	}

	{
		int ofs;
		GMTIME * tm = SaveData_GetGameTime(fsys->savedata);
		ofs = GF_RTC_GetDaysOffset(&tm->sv_date) - 1;
		GF_ASSERT(ofs >= 0 && ofs < 366);
		if (tm->sv_date.month > 2 && !GF_RTC_IsLeapYear(tm->sv_date.year)) {
			//うるう日を含んだテーブルなので、うるう年ではなく3月以降の場合は
			//オフセットに＋１する
			ofs ++;
		}
		if (EVTIME_IsPenaltyMode(fsys)) {
			//DS設定変更後のペナルティ期間はデフォルト天候＝1月1日の天候にする
			ofs = 1;
		}
#ifdef	DEBUG_ONLY_FOR_tamada
		OS_Printf("OFFSET = %d:", ofs);
#endif
		weather = WeatherCalendar[5 * ofs + (weather - WEATHER_SYS_CAL_START)];
#ifdef	DEBUG_ONLY_FOR_tamada
		OS_Printf("NEW WEATHER ID = %d\n",weather);
#endif
	}
	return weather;

}


//============================================================================================
//============================================================================================
//------------------------------------------------------------------
//------------------------------------------------------------------

