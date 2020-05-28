//=============================================================================
/**
 * @file	honeytree_data.h
 * @bfief	蜜塗りエンカウント用セーブデータアクセス関連
 * @author	Nozomu Saito
 *
 *
 */
//=============================================================================
#ifndef __HONEYTREE_DATA_H__
#define __HONEYTREE_DATA_H__
#include "savedata/savedata_def.h"

#define HONEY_TREE_MAX	(21)

typedef struct HONEY_TREE_tag * HT_PTR;

typedef struct HONEY_DATA_tag
{
	int Time;			//蜜を塗った時間
///	u16 State;			//木の状況
	u8 TblMonsNo;		//テーブル内モンスター番号
	u8 TblNo;			//エンカウントテーブル番号
	u8 RareLv;			//レア度	ハズレ、通常、レア、超レア
	u8 SwayLv;			//揺れモーションの度合い
///	u8 AnimeNo;
///	BOOL AnimeFlg;
}HONEY_DATA;

//extern int HTSave_GetSaveDataSize(void);
//extern void HTSave_InitSaveData( HT_PTR outHoneyTree);
//extern HT_PTR HTSave_GetHoneyTree(SAVEDATA * sv);
extern const int HTSave_GetBeforeTreeNo(HT_PTR inPtr);
extern void HTSave_SetBeforeTreeNo(const u8 inTreeNo, HT_PTR outPtr);
extern HONEY_DATA *HTSave_GetHoneyDataPtr(const u8 inTreeNo, HT_PTR outPtr);
extern void HTSave_UpdateHoneyTreeTime(SAVEDATA * sv,  const int inDiffMinute);

#endif //__HONEYTREE_DATA_H__
