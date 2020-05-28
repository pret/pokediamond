//============================================================================================
/**
 * @file	pokepark_sys.h
 * @brief
 * @author	tamada GAME FREAK inc.
 * @date	2006.06.08
 */
//============================================================================================

#ifndef	__POKEPARK_SYS_H__
#define	__POKEPARK_SYS_H__

#include "battle/battle_common.h"
typedef struct POKEPARK_CONTROL POKEPARK_CONTROL;

extern void PokeParkSys_Init(FIELDSYS_WORK * fsys);
extern void PokeParkSys_Finish(FIELDSYS_WORK * fsys);

extern BOOL PokeParkSys_CheckEncount(FIELDSYS_WORK * fsys, int x, int z);
BATTLE_PARAM * PokeParkSys_SetBattleParam(FIELDSYS_WORK * fsys);
extern void PokeParkSys_ReflectBattleResult(FIELDSYS_WORK * fsys, BATTLE_PARAM * bp);
extern int PokeParkSys_GetBallCount(FIELDSYS_WORK * fsys);

extern int PokeParkSys_GetCaptureScore(FIELDSYS_WORK * fsys);
extern int PokeParkSys_GetTimeScore(FIELDSYS_WORK * fsys);
extern int PokeParkSys_GetTypeScore(FIELDSYS_WORK * fsys);

#endif	//__POKEPARK_SYS_H__
