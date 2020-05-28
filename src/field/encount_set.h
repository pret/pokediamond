//============================================================================================
/**
 * @file	encount_set.h
 * @brief
 * @author	saito
 */
//============================================================================================
#ifndef _ENCOUNT_SET_H_
#define _ENCOUNT_SET_H_

#include "common.h"
#include "fieldsys.h"
#include "encount_dat.h"
//#include "battle/battle_common.h"
#include "poketool/poke_tool.h"

#include "field_fishing.h"

//ÉGÉâÅ[âÒîÇÃÇΩÇﬂÇ…Ç®Ç¢ÇƒÇ®Ç≠
#include "field_battle.h"

typedef enum  {
	GROUND_ENCOUNT,
	WATER_ENCOUNT,
	FISHING_ENCOUNT,
}ENCOUNT_LOCATION;

extern BOOL EncSet_CheckEncount( FIELDSYS_WORK * fsys, u8 attr  );

extern void EncSet_SetTimeZoneEnc(	const ENCOUNT_DATA *inEncData,
									int *outTZEncMonsNo1,
									int *outTZEncMonsNo2);
								
extern void SetHoneyTreeEncountData(FIELDSYS_WORK *fsys, BATTLE_PARAM *outBattleParam);
extern void SetWildEncountData(FIELDSYS_WORK *fsys, u16 monsno, u8 level,BATTLE_PARAM *outBattleParam);
extern BOOL SetFishingEncount( FIELDSYS_WORK * fsys, const FISHINGROD_TYPE inRodType, BATTLE_PARAM **outBattleParam );
extern BOOL SetSweetEncount( FIELDSYS_WORK * fsys, GMEVENT_CONTROL * event );
extern BOOL SetKeyRandEncount( FIELDSYS_WORK * fsys, BATTLE_PARAM **outBattleParam );

#ifdef PM_DEBUG
extern BOOL DebugSetEncountData(	const ENCOUNT_DATA * inData,
									const u8 id,
									BATTLE_PARAM *outBattleParam);
extern BOOL DebugSetFishingEncount( FIELDSYS_WORK * fsys, const u8 inRodType );
#endif

#endif //_ENCOUNT_SET_H_

