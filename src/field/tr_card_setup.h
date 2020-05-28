//============================================================================================
/**
 * @file	tr_card_setup.h
 * @bfief	トレーナーカード情報セットアップ
 * @author	Nozomu Saito
 */
//============================================================================================
#ifndef __TR_CARD_SETUP_H__
#define __TR_CARD_SETUP_H__

#include "common.h"
#include "field_common.h"
#include "application/trainer_card.h"

#define BADGE_BRUSH_ON	(1)
#define BADGE_BRUSH_OFF	(0)

#define TIME_UPDATE_ON	(1)
#define TIME_UPDATE_OFF	(0)

#define GYM_READER_MASK_NONE	(0)

extern TR_CARD_DATA *TRCSET_AllocTrainerCardData( const u16 inHeapID );
extern void TRCSET_FreeTrainerCardData( TR_CARD_DATA *outData );
extern void TRCSET_MakeTrainerInfo(	const u8 inBadgeBrushFlg,
									const u8 inTimeUpdate,
									const u8 inGymReaderMask,
									const u8 inUnionTrNo,
									FIELDSYS_WORK *fsys, 
									TR_CARD_DATA *outTrCardData);
extern void TRCSET_UpdateBadgeScruchCount(FIELDSYS_WORK *fsys, const TR_CARD_DATA *inTrCardData);
extern void TRCSET_SetupTrCardEvent(FIELDSYS_WORK * fsys);
extern u8 TRCSET_GetCardRank(FIELDSYS_WORK *fsys);

#endif //__TR_CARD_SETUP_H__

