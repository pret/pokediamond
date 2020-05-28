
//============================================================================================
/**
 * @brief	coin.h
 * @brief	コイン操作
 * @date	2006.03.09
 * @author	tamada
 */
//============================================================================================

#ifndef	__PLAYTIME_H__
#define	__PLAYTIME_H__

#include "savedata/savedata_def.h"
//============================================================================================
//============================================================================================
//---------------------------------------------------------------------------
/**
 * @brief	プレイ時間の不完全型定義
 */
//---------------------------------------------------------------------------
typedef struct PLAYTIME PLAYTIME;

//---------------------------------------------------------------------------
//		プレイ時間の最大値の定義
//---------------------------------------------------------------------------
#define	PTIME_HOUR_MAX		(999)			///<プレイ時間（時）の最大値
#define	PTIME_MINUTE_MAX	(59)			///<プレイ時間（分）の最大値
#define	PTIME_SECOND_MAX	(59)			///<プレイ時間（秒）の最大値

//============================================================================================
//============================================================================================

extern PLAYTIME * SaveData_GetPlayTime(SAVEDATA * sv);
extern void PLAYTIME_Init(PLAYTIME * coin);
extern void PLAYTIME_CountUp(PLAYTIME * ptime, u32 value);
extern u16 PLAYTIME_GetHour(const PLAYTIME * ptime);
extern u8 PLAYTIME_GetMinute(const PLAYTIME * ptime);
extern u8 PLAYTIME_GetSecond(const PLAYTIME * ptime);

extern void PLAYTIME_Set(PLAYTIME * ptime, u32 hour, u32 min, u32 sec);
#endif	__PLAYTIME_H__
