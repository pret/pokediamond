//============================================================================================
/**
 * @file	encount.c
 * @brief	エンカウント関連アクセス用ソース
 * @author	tamada GAME FREAK inc.
 * @date	2003.04.28
 */
//============================================================================================

#include "common.h"
#include "savedata/savedata.h"
#include "savedata/encount.h"
#include "system/pm_rtc.h"
#include "field/move_pokemon_def.h"
#include "savedata/vidro_type.h"

#include "field/encount_define.h"
//蜜木データ
typedef struct HONEY_TREE_tag
{
	u8 TreeNo;			//前回エンカウントした木のナンバー
	HONEY_DATA HoneyData[HONEY_TREE_MAX];
}HONEY_TREE;

//裏山データ
typedef struct HILL_BACK_DATA_tag
{
	BOOL TalkFlg;	//話しかけ有効フラグ	<<別にセーブしているところがあったので未使用 20060526
	u16 EncTblIdx1;	//裏山エンカウントテーブルインデックス1つ目
	u16 EncTblIdx2;	//裏山エンカウントテーブルインデックス2つ目
}HILL_BACK_DATA;

//自機のゾーン足跡
typedef struct PLAYER_ZONE_HIST_tag
{
	int BeforeZone;	//前回ゾーン
	int OldZone;	//前々回ゾーン
}PLAYER_ZONE_HIST;

//移動ポケモンデータ
typedef struct MV_POKE_DATA_tag{

	int ZoneID;			//ゾーンＩＤ
	u32	PowRnd;		// パワー乱数
	u32	PersonalRnd;	// 個性乱数

	u16	MonsNo;				// ポケモンナンバー
	u16	Hp;				// HP

	u8	Lv;				// Lv
	u8	Cond;			// 状態異常

	u8	Encount;		// エンカウントフラグ
	u8	Dummy;

}MV_POKE_DATA;

typedef struct ENC_SV_DATA_tag
{
	int SafariRandSeed;			//サファリランダムの種
	int GenerateRandSeed;		//大量発生ランダムの種
	HILL_BACK_DATA HillBackData;			//裏山データ
	HONEY_TREE HoneyTree;		//蜜木データ
	SWAY_GRASS_HIST		SwayGrassHist;	//揺れ草履歴
	PLAYER_ZONE_HIST	PlayerZoneHist;	//ゾーン履歴
	MV_POKE_DATA	MovePokeData[MOVE_POKE_MAX];	//移動ポケモンデータ
	u8 MovePokeZoneIdx[MOVE_POKE_MAX];	//移動ポケモン現在ゾーンインデックス
	u8 GenerateValid;					//大量発生発動フラグ
	u8 SprayCount;						//スプレー有効歩数(最大250歩)
	u8 PokeSearcherCharge;				//ポケサーチャ充電値（最大50らしい）
	u8 VidroType;						//使用しているビードロ（vidro_type.hに定義）
	
}ENC_SV_DATA;

//----------------------------------------------------------
/**
 * @brief	エンカウント関連セーブデータサイズ取得
 * 
 * @return	int		ENC_SV_DATAのサイズ
 */
//----------------------------------------------------------
int EncDataSave_GetWorkSize(void)
{
	return sizeof(ENC_SV_DATA);
}

//----------------------------------------------------------
/**
 * @brief		エンカウント関連セーブデータの初期化
 * 
 * @param	outEncData		エンカウント関連セーブデータへのポインタ
 *
 * @return	none
 */
//----------------------------------------------------------
void EncDataSave_InitSaveData(ENC_SV_PTR outEncData)
{
	memset( outEncData, 0, sizeof(ENC_SV_DATA) );

	//ランダムの種セット
	outEncData->SafariRandSeed = gf_mtRand();
	outEncData->GenerateRandSeed = gf_mtRand();
	
	//裏山はなしかけフラグ落とす
	outEncData->HillBackData.TalkFlg = FALSE;
	//裏山エンカウントテーブルインデックスをセット
	outEncData->HillBackData.EncTblIdx1 = HILL_BACK_POKE_NONE;
	outEncData->HillBackData.EncTblIdx2 = HILL_BACK_POKE_NONE;
	//蜜木初期化
	{
		int i;
		HT_PTR ht_ptr = &(outEncData->HoneyTree);
		ht_ptr->TreeNo = HONEY_TREE_MAX;
		for(i=0;i<HONEY_TREE_MAX;i++){
			ht_ptr->HoneyData[i].Time = 0;
			//outHoneyTree->HoneyData[i].State = HONEY_SPREAD_OK;
			ht_ptr->HoneyData[i].TblMonsNo = 0;
			ht_ptr->HoneyData[i].TblNo = 0;
			ht_ptr->HoneyData[i].RareLv = 0;
			ht_ptr->HoneyData[i].SwayLv = 0;
		}
	}
	//大量発生発動フラグを落とす
	outEncData->GenerateValid = 0;
	//スプレー
	outEncData->SprayCount = 0;
	//ポケサーチャー
	outEncData->PokeSearcherCharge = 0;
	//ビードロ
	outEncData->VidroType = VIDRO_NONE;
}

//----------------------------------------------------------
/**
 * @brief		エンカウント関連ランダムの種更新
 * 
 * @param	outEncData		エンカウント関連セーブデータへのポインタ
 *
 * @return	none
 */
//----------------------------------------------------------
void EncDataSave_UpdateRandSeed(ENC_SV_PTR ioEncData, const u32 inRandSeed)
{
	ioEncData->SafariRandSeed = inRandSeed;
	ioEncData->GenerateRandSeed = inRandSeed;
}

//----------------------------------------------------------
/**
 * @brief	エンカウント関連ランダムの種取得
 * 
 * @param	inEncData		エンカウント関連セーブデータへのポインタ
 * @param	inSeedType		ランダムの種の種類（encount.hに意義）
 *
 * @return	u32				サファリランダムの種
 */
//----------------------------------------------------------
u32 EncDataSave_GetRandSeed(ENC_SV_PTR inEncData, const u8 inSeedType)
{
	switch(inSeedType){
	case ENC_RND_SEED_SAFARI:
		return inEncData->SafariRandSeed;
	case ENC_RND_SEED_GENERATE:
		return inEncData->GenerateRandSeed;
	default:
		GF_ASSERT(0);
		return 0;
	}
}

//----------------------------------------------------------
/**
 * @brief	揺れ草履歴データ取得
 * 
 * @param	outEncData		エンカウント関連セーブデータへのポインタ
 *
 * @return	揺れ草履歴データポインタ
 */
//----------------------------------------------------------
SWAY_GRASS_HIST *  EncDataSave_GetSwayGrassHist(ENC_SV_PTR outEncData)
{
	return &(outEncData->SwayGrassHist);
}

//==============================================================================
/**
 * セーブデータ先頭ポインタ取得
 *
 * @param	sv		セーブポインタ
 *
 * @return	ENC_SV_PTR		トレーナーカードデータポインタ
 */
//==============================================================================
ENC_SV_PTR EncDataSave_GetSaveDataPtr(SAVEDATA * sv)
{
	return SaveData_Get(sv, GMDATA_ID_ENCOUNT);
}

//蜜木関連-------------------------------------------------------------------------------------------------------------

//==============================================================================
/**
 * 蜜木データポインタ取得
 *
 * @param	sv		セーブポインタ
 *
 * @return	HT_PTR	蜜塗りデータポインタ
 */
//==============================================================================
HT_PTR EncDataSave_GetHoneyTree(ENC_SV_PTR inEncData)
{
	return &(inEncData->HoneyTree);
}

//==============================================================================
/**
 * 前回エンカウントした木のナンバーを取得
 *
 * @param	inPtr		蜜塗りエンカウントデータポインタ
 *
 * @return	int			木ナンバー
 */
//==============================================================================
const int HTSave_GetBeforeTreeNo(HT_PTR inPtr)
{
	return inPtr->TreeNo;
}

//==============================================================================
/**
 * 前回エンカウントした木のナンバーをセット
 *
 * @param	inTreeNo	木ナンバー
 * @param	outPtr		蜜塗りエンカウントデータポインタ
 *
 * @return	none
 */
//==============================================================================
void HTSave_SetBeforeTreeNo(const u8 inTreeNo, HT_PTR outPtr)
{
	outPtr->TreeNo = inTreeNo;
}

//==============================================================================
/**
 * 蜜木データポインタの取得
 *
 * @param	inTreeNo	木ナンバー
 * @param	outPtr		蜜塗りエンカウントデータポインタ
 *
 * @return	none
 */
//==============================================================================
HONEY_DATA *HTSave_GetHoneyDataPtr(const u8 inTreeNo, HT_PTR outPtr)
{
	HONEY_DATA *data;
	data = &outPtr->HoneyData[inTreeNo];

	return data;
}

//==============================================================================
/**
 * 時間更新
 *
 * @param	sv				セーブポインタ
 * @param	inDiffminute	時間差分
 *
 * @return	none
 */
//==============================================================================
void HTSave_UpdateHoneyTreeTime(SAVEDATA * sv,  const int inDiffMinute)
{
	int i;
	HT_PTR ptr;
	ENC_SV_PTR enc_data;
	HONEY_DATA *data;
	enc_data = EncDataSave_GetSaveDataPtr(sv);
	ptr = &(enc_data->HoneyTree);

	for(i=0;i<HONEY_TREE_MAX;i++){
		data = HTSave_GetHoneyDataPtr(i, ptr);
		if (data->Time != 0){
			data->Time -= inDiffMinute;
			if (data->Time < 0){
				data->Time = 0;
			}
		}
	}
}

//==============================================================================
/**
 * 大量発生開始
 *
 * @param	sv				セーブポインタ
 *
 * @return	none
 */
//==============================================================================
void EncDataSave_StartGenerate( SAVEDATA * sv )
{
	ENC_SV_PTR enc_data;
	enc_data = EncDataSave_GetSaveDataPtr(sv);
	enc_data->GenerateValid = 1;
}

//==============================================================================
/**
 * 大量発生中かを返す
 *
 * @param	inEncData			エンカウント関連セーブポインタ
 *
 * @return	u8 0以外：大量発生中
 */
//==============================================================================
u8 EncDataSave_IsGenerate( ENC_SV_PTR inEncData )
{
	return inEncData->GenerateValid;
}

//==============================================================================
/**
 * 主人公のゾーン履歴の更新
 *
 * @param	outEncData			エンカウント関連セーブポインタ
 * @param	inZoneID			ゾーンＩＤ
 */
//==============================================================================
void EncDataSave_UpdatePlayerZoneHist(ENC_SV_PTR ioEncData, const int inZoneID)
{
	if (ioEncData->PlayerZoneHist.BeforeZone != inZoneID){
		ioEncData->PlayerZoneHist.OldZone = ioEncData->PlayerZoneHist.BeforeZone;
		ioEncData->PlayerZoneHist.BeforeZone = inZoneID;
	}
}

//==============================================================================
/**
 * 主人公の前々回いたゾーンを取得
 *
 * @param	inEncData		エンカウント関連セーブポインタ
 *
 * @return	int				ゾーンＩＤ
 */
//==============================================================================
int EncDataSave_GetPlayerOldZone(ENC_SV_PTR inEncData)
{
	return inEncData->PlayerZoneHist.OldZone;
}

//==============================================================================
/**
 * 指定移動ポケモンのゾーンインデックスを取得
 *
 * @param	inEncData		エンカウント関連セーブポインタ
 * @param	inTargetPoke	移動ポケモン(0～2)
 *
 * @return	u8				ゾーンインデックス
 */
//==============================================================================
u8 EncDataSave_GetMovePokeZoneIdx(ENC_SV_PTR inEncData, const u8 inTargetPoke)
{
	GF_ASSERT(inTargetPoke<MOVE_POKE_MAX);
	
	return inEncData->MovePokeZoneIdx[inTargetPoke];
}

//==============================================================================
/**
 * 指定移動ポケモンのゾーンインデックスをセット
 *
 * @param	outEncData		エンカウント関連セーブポインタ
 * @param	inTargetPoke	移動ポケモン(0～2)
 * @param	inZoneIndex		ゾーンインデックス
 *
 * @return	none
 */
//==============================================================================
void EncDataSave_SetMovePokeZoneIdx(ENC_SV_PTR outEncData, const u8 inTargetPoke, const u8 inZoneIndex)
{
	GF_ASSERT(inTargetPoke<MOVE_POKE_MAX);
	outEncData->MovePokeZoneIdx[inTargetPoke] = inZoneIndex;
}

//==============================================================================
/**
 * 指定移動ポケモンのエンカウントフラグみて、移動しているかどうかをチェック
 *
 * @param	inEncData		エンカウント関連セーブポインタ
 * @param	inTargetPoke	移動ポケモン(0～2)
 *
 * @return	u8			0以外:移動してる	0:移動してない
 */
//==============================================================================
u8 EncDataSave_IsMovePokeValid(ENC_SV_PTR inEncData, const u8 inTargetPoke)
{
	GF_ASSERT(inTargetPoke<MOVE_POKE_MAX);
	return inEncData->MovePokeData[inTargetPoke].Encount;
}

//==============================================================================
/**
 * 指定移動ポケモンデータのクリア
 *
 * @param	inEncData		エンカウント関連セーブポインタ
 * @param	inTargetPoke	移動ポケモン(0～2)
 *
 * @return	none
 */
//==============================================================================
void EncDataSave_ClearMovePokeData(MPD_PTR *outMPData)
{
	memset((*outMPData), 0, sizeof(MV_POKE_DATA));
}

//==============================================================================
/**
 * 指定移動ポケモンデータポインタの取得
 *
 * @param	inEncData		エンカウント関連セーブポインタ
 * @param	inTargetPoke	移動ポケモン(0～2)
 *
 * @return	MPD_PTR			移動ポケモンデータ
 */
//==============================================================================
MPD_PTR	EncDataSave_GetMovePokeDataPtr(ENC_SV_PTR inEncData, const u8 inTargetPoke)
{
	GF_ASSERT(inTargetPoke<MOVE_POKE_MAX);
	return &(inEncData->MovePokeData[inTargetPoke]);
}

//==============================================================================
/**
 * 移動ポケモンデータパラメータ取得
 *
 * @param	inMPData		移動尾ポケモンデータポインタ
 * @param	inParamID		パラメータＩＤ
 *
 * @return	u32
 */
//==============================================================================
u32 EncDataSave_GetMovePokeDataParam(const MPD_PTR inMPData, const u8 inParamID)
{
	u32 val;
	switch(inParamID){
	case MP_PARAM_ZONE_ID:			//出現ゾーン
		val = inMPData->ZoneID;
		break;
	case MP_PARAM_POW_RND:			//パワー乱数
		val = inMPData->PowRnd;
		break;
	case MP_PARAM_PER_RND:			//個性乱数
		val = inMPData->PersonalRnd;
		break;
	case MP_PARAM_MONSNO:			//モンスターナンバー
		val = inMPData->MonsNo;
		break;
	case MP_PARAM_HP:				//ＨＰ
		val = inMPData->Hp;
		break;
	case MP_PARAM_LV:				//ＬＶ
		val = inMPData->Lv;
		break;
	case MP_PARAM_COND:				//状態異常
		val = inMPData->Cond;
		break;
	case MP_PARAM_ENC:				//エンカウントフラグ
		val = inMPData->Encount;
		break;
	defauld:
		GF_ASSERT(0);
		return 0;
	}
	return val;
}

//==============================================================================
/**
 * 移動ポケモンデータパラメータセット
 *
 * @param	EncData		エンカウント関連セーブポインタ
 * @param	inParamID	パラメータＩＤ
 * @param	inVal		セットする値
 *
 * @return	none
 */
//==============================================================================
void EncDataSave_SetMovePokeDataParam(MPD_PTR outMPData, const u8 inParamID, const u32 inVal)
{
	u32 val;
	switch(inParamID){
	case MP_PARAM_ZONE_ID:			//出現ゾーン
		outMPData->ZoneID = inVal;
		break;
	case MP_PARAM_POW_RND:			//パワー乱数
		outMPData->PowRnd = inVal;
		break;
	case MP_PARAM_PER_RND:			//個性乱数
		outMPData->PersonalRnd = inVal;
		break;
	case MP_PARAM_MONSNO:			//モンスターナンバー
		outMPData->MonsNo = inVal;
		break;
	case MP_PARAM_HP:				//ＨＰ
		outMPData->Hp = inVal;
		break;
	case MP_PARAM_LV:				//ＬＶ
		outMPData->Lv = inVal;
		break;
	case MP_PARAM_COND:				//状態異常
		outMPData->Cond = inVal;
		break;
	case MP_PARAM_ENC:				//エンカウントフラグ
		outMPData->Encount = inVal;
		break;
	defauld:
		GF_ASSERT(0);
	}
}

//==============================================================================
/**
 * ポケサーチャ充電値を格納したメンバのポインタを取得
 *
 * @param	inEncData		エンカウント関連セーブポインタ
 *
 * @return	u8*				ポケサーチャー充電値ポインタ
 */
//==============================================================================
u8 *EncDataSave_GetPokeSearcherCharge(ENC_SV_PTR inEncData)
{
	return &(inEncData->PokeSearcherCharge);
}

//==============================================================================
/**
 * スプレー有効歩数を格納したメンバのポインタを取得
 *
 * @param	inEncData		エンカウント関連セーブポインタ
 *
 * @return	u8*				スプレー有効歩数ポインタ
 */
//==============================================================================
u8 *EncDataSave_GetSprayCnt(ENC_SV_PTR inEncData)
{
	return &(inEncData->SprayCount);
}

//==============================================================================
/**
 * スプレーを使用できるかどうかのチェック
 * 
 * @param	inEncData		エンカウント関連セーブポインタ
 *
 * @return	BOOL	TRUE:使用可		FALSE:使用不可
 */
//==============================================================================
BOOL EncDataSave_CanUseSpray(ENC_SV_PTR inEncData)
{
	if (!inEncData->SprayCount){
		return TRUE;
	}else{
		return FALSE;
	}
}

//==============================================================================
/**
 * ビードロタイプセット
 * 
 * @param	outEncData		エンカウント関連セーブポインタ
 * @param	inType			ビードロタイプ
 *
 * @return	none
 */
//==============================================================================
void EncDataSave_SetVidro(ENC_SV_PTR outEncData, const u8 inType)
{
	GF_ASSERT( (inType == VIDRO_BLACK)||
				(inType == VIDRO_WHITE)||
				(inType == VIDRO_NONE) );
	outEncData->VidroType = inType;
}

//==============================================================================
/**
 * ビードロタイプ取得
 * 
 * @param	inEncData		エンカウント関連セーブポインタ
 *
 * @return	u8			ビードロタイプ
 */
//==============================================================================
u8 EncDataSave_GetVidro(ENC_SV_PTR inEncData)
{
	return inEncData->VidroType;
}

//==============================================================================
/**
 * 裏山エンカウントポケモンインデックスの取得
 *
 * @param	sv				セーブデータポインタ
 * @param	outIndex1		裏山ポケモンインデックス
 * @param	outIndex2		裏山ポケモンインデックス
 *
 * @return	none
 */
//==============================================================================
void EncDataSave_GetHillBackPokeIdx(SAVEDATA *sv, u16 *outIndex1, u16 *outIndex2)
{
	ENC_SV_PTR  enc_data = EncDataSave_GetSaveDataPtr(sv);
	(*outIndex1) = enc_data->HillBackData.EncTblIdx1;
	(*outIndex2) = enc_data->HillBackData.EncTblIdx2;
}

//==============================================================================
/**
 * 裏山エンカウントポケモンインデックスのセット（押し出し式）
 *
 * @param	sv			セーブデータポインタ
 * @param	inIndex		裏山ポケモンインデックス
 *
 * @return	none
 */
//==============================================================================
void EncDataSave_SetHillBackPokeIdx(SAVEDATA *sv, const u16 inIndex)
{
	ENC_SV_PTR  enc_data = EncDataSave_GetSaveDataPtr(sv);
	GF_ASSERT(inIndex<HILL_BACK_ENC_MONS_MAX);
	enc_data->HillBackData.EncTblIdx2 = enc_data->HillBackData.EncTblIdx1;
	enc_data->HillBackData.EncTblIdx1 = inIndex;
}

