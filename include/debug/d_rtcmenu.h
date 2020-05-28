//============================================================================================
/**
 * @file	d_rtcmenu.h
 * @brief
 * @date	2006.06.23
 * @author	tamada GAME FREAK inc.
 */
//============================================================================================

#ifndef	__D_RTCMENU_H__
#define	__D_RTCMENU_H__

#include "system/procsys.h"
//============================================================================================
//============================================================================================

//------------------------------------------------------------------
//------------------------------------------------------------------
extern PROC_RESULT DebugRtcMenuProc_Init(PROC * proc, int * seq);
extern PROC_RESULT DebugRtcMenuProc_Main(PROC * proc, int * seq);
extern PROC_RESULT DebugRtcMenuProc_End(PROC * proc, int * seq);

extern const PROC_DATA DebugRtcMenuProcData;

#endif	__D_RTCMENU_H__
