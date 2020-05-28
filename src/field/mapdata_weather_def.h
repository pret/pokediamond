//============================================================================================
/**
 * @file	mapdata_weather_def.h
 * @brief
 * @date	2006.03.11
 * @author	tamada GAME FREAK inc.
 */
//============================================================================================
#ifndef	__MAPDATA_WEATHER_DEF_H__
#define	__MAPDATA_WEATHER_DEF_H__

//------------------------------------------------------------------
//------------------------------------------------------------------
#include "weather_sys.h"

enum {
	WEATHER_SYS_CAL_START = WEATHER_SYS_NUM + 1,
	WEATHER_SYS_CAL_R212B = WEATHER_SYS_CAL_START,
	WEATHER_SYS_CAL_R213,
	WEATHER_SYS_CAL_R216,
	WEATHER_SYS_CAL_L03,
	WEATHER_SYS_CAL_C09,

	WEATHER_SYS_CAL_END,
};

#endif	/*	__MAPDATA_WEATHER_DEF_H__ */
