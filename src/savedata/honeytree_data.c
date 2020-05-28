//=============================================================================
/**
 * @file	honeytree_data.c
 * @bfief	蜜塗りエンカウント用セーブデータアクセス関連
 * @author	Nozomu Saito
 *
 *
 */
//=============================================================================
#if 0

#include "common.h"
#include "savedata/savedata.h"
#include "savedata/honeytree_data.h"

typedef struct HONEY_TREE_tag
{
	u8 TreeNo;			//前回エンカウントした木のナンバー
	HONEY_DATA HoneyData[HONEY_TREE_MAX];
}HONEY_TREE;

//==============================================================================
/**
 * セーブデータサイズ取得
 *
 * @param	none
 *
 * @return	int			サイズ
 */
//==============================================================================
int HTSave_GetSaveDataSize(void)
{
	return sizeof(HONEY_TREE);
}

//==============================================================================
/**
 * セーブデータ初期化
 *
 * @param	outHoneyTree		蜜塗りセーブデータポインタ
 *
 * @return	none
 */
//==============================================================================
void HTSave_InitSaveData(HT_PTR outHoneyTree)
{
	int i;
	memset( outHoneyTree, 0, sizeof(HONEY_TREE) );
	outHoneyTree->TreeNo = HONEY_TREE_MAX;
	for(i=0;i<HONEY_TREE_MAX;i++){
		outHoneyTree->HoneyData[i].Time = 0;
		//outHoneyTree->HoneyData[i].State = HONEY_SPREAD_OK;
		outHoneyTree->HoneyData[i].TblMonsNo = 0;
		outHoneyTree->HoneyData[i].TblNo = 0;
		outHoneyTree->HoneyData[i].RareLv = 0;
		outHoneyTree->HoneyData[i].SwayLv = 0;
	}
}

//==============================================================================
/**
 * セーブデータ先頭ポインタ取得
 *
 * @param	sv		セーブポインタ
 *
 * @return	HT_PTR	蜜塗りデータポインタ
 */
//==============================================================================
HT_PTR HTSave_GetHoneyTree(SAVEDATA * sv)
{
	return SaveData_Get(sv, GMDATA_ID_HONEYTREE);
}

//==============================================================================
/**
 * 蜜木の時間取得
 *
 * @param	inPtr		蜜塗りエンカウントデータポインタ
 * @param	inTreeNo	木ナンバー
 *
 * @return	int			時間
 */
//==============================================================================
const int HTSave_GetTime(HT_PTR inPtr,  const u8 inTreeNo)
{
	return inPtr->HoneyData[inTreeNo].Time;
}

//==============================================================================
/**
 * テーブル内モンスター番号取得
 *
 * @param	inPtr		蜜塗りエンカウントデータポインタ
 * @param	inTreeNo	木ナンバー
 *
 * @return	u8			テーブルモンスターナンバー
 */
//==============================================================================
const u8 HTSave_GetTblMonsNo(HT_PTR inPtr, const u8 inTreeNo)
{
	return inPtr->HoneyData[inTreeNo].TblMonsNo;
}

//==============================================================================
/**
 * テーブル番号取得
 *
 * @param	inPtr		蜜塗りエンカウントデータポインタ
 * @param	inTreeNo	木ナンバー
 *
 * @return	u8			テーブル番号
 */
//==============================================================================
const u8 HTSave_GetTblNo(HT_PTR inPtr, const u8 inTreeNo)
{
	return inPtr->HoneyData[inTreeNo].TblNo;
}

//==============================================================================
/**
 * テーブルレア度の取得
 *
 * @param	inPtr		蜜塗りエンカウントデータポインタ
 * @param	inTreeNo	木ナンバー
 *
 * @return	u8			レア度
 */
//==============================================================================
const u8 HTSave_GetRareLv(HT_PTR inPtr, const u8 inTreeNo)
{
	return inPtr->HoneyData[inTreeNo].RareLv;
}

//==============================================================================
/**
 * 揺れ度合いを取得
 *
 * @param	inPtr		蜜塗りエンカウントデータポインタ
 * @param	inTreeNo	木ナンバー
 *
 * @return	u8			揺れ具合
 */
//==============================================================================
const u8 HTSave_GetSwayLv(HT_PTR inPtr, const u8 inTreeNo)
{
	return inPtr->HoneyData[inTreeNo].SwayLv;
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
 * 蜜木の時間セット
 *
 * @param	inTime	時間
 * @param	inTreeNo	木ナンバー
 * @param	outPtr		蜜塗りエンカウントデータポインタ
 *
 * @return	none
 */
//==============================================================================
void HTSave_SetTime(const u8 inTime, const u8 inTreeNo, HT_PTR outPtr)
{
	outPtr->HoneyData[inTreeNo].Time = inTime;
}

//==============================================================================
/**
 * テーブル内モンスター番号セット
 *
 * @param	inTblMonsNo	テーブルモンスターナンバー
 * @param	inTreeNo	木ナンバー
 * @param	outPtr		蜜塗りエンカウントデータポインタ
 *
 * @return	none
 */
//==============================================================================
void HTSave_SetTblMonsNo(const u8 inTblMonsNo, const u8 inTreeNo, HT_PTR outPtr)
{
	outPtr->HoneyData[inTreeNo].TblMonsNo = inTblMonsNo;
}

//==============================================================================
/**
 * テーブル番号セット
 *@param	inTblNo		テーブルナンバー
 * @param	inTreeNo	木ナンバー
 * @param	outPtr		蜜塗りエンカウントデータポインタ
 *
 * @return	none
 */
//==============================================================================
void HTSave_SetTblNo(const u8 inTblNo, const u8 inTreeNo, HT_PTR outPtr)
{
	outPtr->HoneyData[inTreeNo].TblNo = inTblNo;
}

//==============================================================================
/**
 * テーブルレア度のセット
 *
 * @param	inRareLv	レアレベル
 * @param	inTreeNo	木ナンバー
 * @param	outPtr		蜜塗りエンカウントデータポインタ
 *
 * @return	none
 */
//==============================================================================
void HTSave_SetRareLv(const u8 inRareLv, const u8 inTreeNo, HT_PTR outPtr)
{
	outPtr->HoneyData[inTreeNo].RareLv = inRareLv;
}

//==============================================================================
/**
 * 揺れ度合いを取得
 *
 * @param	inTreeNo	木ナンバー
 * @param	outPtr		蜜塗りエンカウントデータポインタ
 *
 * @return	none
 */
//==============================================================================
void  HTSave_SetSwayLv(const u8 inSwayLv, const u8 inTreeNo, HT_PTR outPtr)
{
	outPtr->HoneyData[inTreeNo].SwayLv = inSwayLv;
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
	HONEY_DATA *data;

	ptr = HTSave_GetHoneyTree(sv);
	
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

#endif
