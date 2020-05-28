
//============================================================================================
/**
 * @file	game_init.h
 * @brief	ƒQ[ƒ€ŠJn‚Ì‰Šú‰»ˆ—
 * @date	2005.08.01
 */
//============================================================================================

#ifndef	__GAME_INIT_H__
#define	__GAME_INIT_H__

#include "system/savedata.h"
#include "system/procsys.h"

extern const PROC_DATA ContinueGameProcData;
extern const PROC_DATA FirstGameProcData;


extern void GameData_SetNewGame(int heapID, SAVEDATA * savedata);
extern void GameData_SetDebugNewGame(int heapID, SAVEDATA * savedata, int usr_id);
extern void GameData_SetContinueData(int heapID, SAVEDATA * savedata);

#ifdef	PM_DEBUG
extern int Debug_GetMyID(void);
#endif

#endif	/* __GAME_INIT_H__ */
