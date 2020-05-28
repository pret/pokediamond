//============================================================================================
/**
 * @file	sway_grass_hist.c
 * @brief	揺れ草エンカウント履歴
 * @author	saito GAME FREAK inc.
 * @date	2006.02.14
 */
//============================================================================================
#include "common.h"
#include "fieldsys.h"
#include "sway_grass_hist.h"
#include "savedata/encount.h"
static void SortHistData(SWAY_GRASS_HIST *inHist, SWAY_GRASS_REC **outRec);

//-----------------------------------------------------------------------------
/**
 * @brief	現在の履歴数を返す
 * 
 * @param	fsys		フィールドシステムポインタ
 *
 * @retval	int			履歴数（最大3）
 *
 */
//-----------------------------------------------------------------------------
int SwayGrassHist_GetHistNum(FIELDSYS_WORK * fsys)
{
	int i;
	int cnt;
	SWAY_GRASS_HIST * hist;
	hist = EncDataSave_GetSwayGrassHist( EncDataSave_GetSaveDataPtr(fsys->savedata) );
	cnt = 0;
	for(i=0;i<3;i++){
		if (hist->SwayGrassRec[0].Chain){
			cnt++;
		}
	}
	return cnt;
}

//-----------------------------------------------------------------------------
/**
 * @brief	指定順位のモンスターナンバーを返す
 * 
 * @param	fsys		フィールドシステムポインタ
 * @param	inNo		順位（0オリジン）
 *
 * @retval	int			モンスターナンバー
 *
 */
//-----------------------------------------------------------------------------
int SwayGrassHist_GetMonsNo(FIELDSYS_WORK * fsys, const u8 inNo)
{
	SWAY_GRASS_HIST * hist;
	SWAY_GRASS_REC *rec[3];
	GF_ASSERT(inNo<3);
	hist = EncDataSave_GetSwayGrassHist( EncDataSave_GetSaveDataPtr(fsys->savedata) );
	SortHistData(hist, rec);
	return rec[inNo]->MonsNo;
}

//-----------------------------------------------------------------------------
/**
 * @brief	指定順位の連鎖数を返す
 * 
 * @param	fsys		フィールドシステムポインタ
 * @param	inNo		順位（0オリジン）
 *
 * @retval	int			連鎖数
 *
 */
//-----------------------------------------------------------------------------
int SwayGrassHist_GetChain(FIELDSYS_WORK * fsys, const u8 inNo)
{
	SWAY_GRASS_HIST * hist;
	SWAY_GRASS_REC *rec[3];
	GF_ASSERT(inNo<3);
	hist = EncDataSave_GetSwayGrassHist( EncDataSave_GetSaveDataPtr(fsys->savedata) );
	SortHistData(hist, rec);
	return rec[inNo]->Chain;
}

//-----------------------------------------------------------------------------
/**
 * @brief	現在の連鎖数を返す
 * 
 * @param	fsys		フィールドシステムポインタ
 *
 * @retval	int			連鎖数
 *
 */
//-----------------------------------------------------------------------------
int SwayGrassHist_GetNowChain(FIELDSYS_WORK * fsys)
{
	return SwayGrass_GetChain(fsys);
}
//-----------------------------------------------------------------------------
/**
 * @brief	現在のモンスターナンバーを返す
 * 
 * @param	fsys		フィールドシステムポインタ
 *
 * @retval	int			モンスターナンバー
 *
 */
//-----------------------------------------------------------------------------
int SwayGrassHist_GetNowMonsNo(FIELDSYS_WORK * fsys)
{
	int monsno,lv;
	SwayGrass_GetEncMonsNoLv(fsys->SwayGrass,  &monsno, &lv);
	return monsno;
}

//-----------------------------------------------------------------------------
/**
 * @brief	3つの履歴を連鎖数の多い順にソートする
 * 
 * @param	inHist	履歴データポインタ
 *
 * @retval	
 *
 */
//-----------------------------------------------------------------------------
void SwayGrassHist_SortHistData(SWAY_GRASS_HIST *ioHist)
{
	int i;
	SWAY_GRASS_REC rec[3];
	SWAY_GRASS_REC *p_rec[3];
	SortHistData(ioHist, p_rec);

	for(i=0;i<3;i++){
		rec[i] = *(p_rec[i]);
	}
	for(i=0;i<3;i++){
		ioHist->SwayGrassRec[i] = rec[i];
	}
}

//-----------------------------------------------------------------------------
/**
 * @brief	3つの履歴を連鎖数の多い順にソートする
 * 
 * @param	inHist	履歴データポインタ
 * @param	outRec	格納バッファポインタ
 *
 * @retval	
 *
 */
//-----------------------------------------------------------------------------
static void SortHistData(SWAY_GRASS_HIST *inHist, SWAY_GRASS_REC **outRec)
{

	if (inHist->SwayGrassRec[0].Chain<inHist->SwayGrassRec[1].Chain){
		if (inHist->SwayGrassRec[1].Chain<inHist->SwayGrassRec[2].Chain){
			outRec[0] = &inHist->SwayGrassRec[2];
			outRec[1] = &inHist->SwayGrassRec[1];
			outRec[2] = &inHist->SwayGrassRec[0];
		}else if (inHist->SwayGrassRec[0].Chain<inHist->SwayGrassRec[2].Chain){
			outRec[0] = &inHist->SwayGrassRec[1];
			outRec[1] = &inHist->SwayGrassRec[2];
			outRec[2] = &inHist->SwayGrassRec[0];
		}else{
			outRec[0] = &inHist->SwayGrassRec[1];
			outRec[1] = &inHist->SwayGrassRec[0];
			outRec[2] = &inHist->SwayGrassRec[2];
		}
	}else{
		if (inHist->SwayGrassRec[0].Chain<inHist->SwayGrassRec[2].Chain){
			outRec[0] = &inHist->SwayGrassRec[2];
			outRec[1] = &inHist->SwayGrassRec[0];
			outRec[2] = &inHist->SwayGrassRec[1];
		}else if(inHist->SwayGrassRec[1].Chain<inHist->SwayGrassRec[2].Chain){
			outRec[0] = &inHist->SwayGrassRec[0];
			outRec[1] = &inHist->SwayGrassRec[2];
			outRec[2] = &inHist->SwayGrassRec[1];
		}else{
			outRec[0] = &inHist->SwayGrassRec[0];
			outRec[1] = &inHist->SwayGrassRec[1];
			outRec[2] = &inHist->SwayGrassRec[2];
		}
	}
}

