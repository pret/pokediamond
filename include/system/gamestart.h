//============================================================================================
/**
 * @file	gamestart.h
 * @brief
 * @author	tamada GAME FREAK inc.
 * @date	2006.05.10
 */
//============================================================================================
#ifndef	__GAMESTART_H__
#define	__GAMESTART_H__

#include "system/procsys.h"

FS_EXTERN_OVERLAY(gamestart);

#define	OVERLAY_ID_GAMESTART	FS_OVERLAY_ID(gamestart)

extern const PROC_DATA NewGameStartProcData;
extern const PROC_DATA AfterOpeningProcData;
extern const PROC_DATA DebugNewGameStartProcData;
extern const PROC_DATA ContinueGameStartProcData;

//本来は専用のヘッダに定義するべき？
extern const PROC_DATA OpeningProcData;

#endif	/* __GAMESTART_H__ */
