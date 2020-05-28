//=============================================================================
/**
 * @file	trainerbadge_data.h
 * @bfief	トレーナーカード用セーブデータアクセス関連
 * @author	Nozomu Saito
 *
 *
 */
//=============================================================================
#ifndef __TRAINERCARD_DATA_H__
#define __TRAINERCARD_DATA_H__
#include "savedata/savedata_def.h"

typedef struct TR_BADGE_SV_DATA_tag * TR_BADGE_DATA_PTR;
typedef struct TR_CARD_SV_DATA_tag * TR_CARD_SV_PTR;

extern int TRCSave_GetSaveDataSize(void);
extern void TRCSave_InitSaveData(TR_CARD_SV_PTR outTrCard);
extern TR_CARD_SV_PTR TRCSave_GetSaveDataPtr(SAVEDATA * sv);
extern u8 *TRCSave_GetSighnDataPtr(TR_CARD_SV_PTR inTrCard);

extern TR_BADGE_DATA_PTR TRCSave_GetBadgeDataPtr(TR_CARD_SV_PTR inTrCard);
extern int TRCSave_GetBadgeScruchCount(const u8 inBadgeNo, TR_BADGE_DATA_PTR inBadgeDataPtr);
extern void TRCSave_SetBadgeScruchCount(const u8 inBadgeNo, const int inCount, TR_BADGE_DATA_PTR outBadgeDataPtr);
#endif //__TRAINERCARD_DATA_H__

