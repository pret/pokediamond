//============================================================================================
/**
 * @file	ev_time.h
 * @brief	ÉQÅ[ÉÄì‡éûä‘êßå‰ä÷òA
 * @author	tamada
 * @date	2006.02.03
 */
//============================================================================================

#ifndef	__EV_TIME_H__
#define	__EV_TIME_H__


#include "field_common.h"

#include "system/timezone.h"

//============================================================================================
//============================================================================================

//------------------------------------------------------------------
//------------------------------------------------------------------

//------------------------------------------------------------------
//------------------------------------------------------------------
extern void EVTIME_Update(FIELDSYS_WORK * fsys);


//------------------------------------------------------------------
//------------------------------------------------------------------
extern int EVTIME_GetTimeZone(const FIELDSYS_WORK * fsys);
extern int EVTIME_GetHour(const FIELDSYS_WORK * fsys);
extern int EVTIME_GetMinute(const FIELDSYS_WORK * fsys);
extern int EVTIME_GetMonth(const FIELDSYS_WORK * fsys);
extern int EVTIME_GetDay(const FIELDSYS_WORK * fsys);
extern int EVTIME_GetWeek(const FIELDSYS_WORK * fsys);

extern void EVTIME_GetGameStartDateTime(const FIELDSYS_WORK * fsys, RTCDate * date, RTCTime * time);
extern void EVTIME_GetGameClearDateTime(const FIELDSYS_WORK * fsys, RTCDate * date, RTCTime * time);
extern void EVTIME_SetGameClearDateTime(const FIELDSYS_WORK * fsys);

extern BOOL EVTIME_IsPenaltyMode(FIELDSYS_WORK * fsys);


#endif	/* __EV_TIME_H__ */
