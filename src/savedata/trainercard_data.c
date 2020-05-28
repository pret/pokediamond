//=============================================================================
/**
 * @file	trainercard_data.c
 * @bfief	トレーナーカード用セーブデータアクセス関連
 * @author	Nozomu Saito
 *
 *
 */
//=============================================================================
#include "common.h"
#include "savedata/savedata.h"
#include "savedata/trainercard_data.h"

#define BADGE_MAX	(8)
#define SIGHN_W	(24)
#define SIGHN_H	(8)

#define DEFAULT_BADGE_SCRUCH	(140)

typedef struct TR_BADGE_SV_DATA_tag
{
	int ScruchCount;	//磨き具合
}TR_BADGE_SV_DATA;

typedef struct TR_CARD_SV_DATA_tag
{
	TR_BADGE_SV_DATA BadgeData[BADGE_MAX];
	u8 SighnData[SIGHN_W*SIGHN_H*64/8];	//サイン面データ
}TR_CARD_SV_DATA;

//==============================================================================
/**
 * セーブデータサイズ取得
 *
 * @param	none
 *
 * @return	int		サイズ
 */
//==============================================================================
int TRCSave_GetSaveDataSize(void)
{
	return sizeof(TR_CARD_SV_DATA);
}

//==============================================================================
/**
 * セーブデータ初期化
 *
 * @param	outTrCard	トレーナーカードデータポインタ
 *
 * @return	none
 */
//==============================================================================
void TRCSave_InitSaveData(TR_CARD_SV_PTR outTrCard)
{
	memset( outTrCard, 0, sizeof(TR_CARD_SV_DATA) );
	//バッジの腐食具合をセットする
	{
		int i;
		TR_BADGE_DATA_PTR badge_ptr;
		badge_ptr = TRCSave_GetBadgeDataPtr(outTrCard);
		for(i=0;i<8;i++){
			TRCSave_SetBadgeScruchCount(i, DEFAULT_BADGE_SCRUCH, badge_ptr);
		}
	}
}

//==============================================================================
/**
 * セーブデータ先頭ポインタ取得
 *
 * @param	sv		セーブポインタ
 *
 * @return	TR_CARD_SV_PTR		トレーナーカードデータポインタ
 */
//==============================================================================
TR_CARD_SV_PTR TRCSave_GetSaveDataPtr(SAVEDATA * sv)
{
	return SaveData_Get(sv, GMDATA_ID_TRCARD);
}

//==============================================================================
/**
 * サインデータ先頭ポインタ取得
 *
 * @param	inTrCard		トレーナーカードデータポインタ
 *
 * @return	u8*				サインデータポインタ
 */
//==============================================================================
u8 *TRCSave_GetSighnDataPtr(TR_CARD_SV_PTR inTrCard)
{
	return inTrCard->SighnData;
}

//==============================================================================
/**
 * バッジデータ先頭ポインタ取得
 *
 * @param	inTrCard		トレーナーカードデータポインタ
 *
 * @return	TR_BADGE_DATA_PTR	バッジデータポインタ
 */
//==============================================================================
TR_BADGE_DATA_PTR TRCSave_GetBadgeDataPtr(TR_CARD_SV_PTR inTrCard)
{
	return inTrCard->BadgeData;
}

//==============================================================================
/**
 * バッジ磨き具合を取得
 *
 * @param	inBadgePtr		バッジデータ先頭ポインタ
 * @param	inBadgeNo		バッジナンバー
 *
 * @return	int				磨き具合
 */
//==============================================================================
int TRCSave_GetBadgeScruchCount(const u8 inBadgeNo, TR_BADGE_DATA_PTR inBadgeDataPtr)
{
	return inBadgeDataPtr[inBadgeNo].ScruchCount;
}

//==============================================================================
/**
 * バッジ磨き具合をセット
 *
 * @param	inBadgeNo		バッジナンバー
 * @param	inCount			//磨き回数
 * @param	outBadgePtr		バッジデータ先頭ポインタ
 * 
 *
 * @return	none
 */
//==============================================================================
void TRCSave_SetBadgeScruchCount(const u8 inBadgeNo, const int inCount, TR_BADGE_DATA_PTR outBadgeDataPtr)
{
	outBadgeDataPtr[inBadgeNo].ScruchCount = inCount;
}
