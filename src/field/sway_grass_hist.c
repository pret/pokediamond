//============================================================================================
/**
 * @file	sway_grass_hist.c
 * @brief	�h�ꑐ�G���J�E���g����
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
 * @brief	���݂̗��𐔂�Ԃ�
 * 
 * @param	fsys		�t�B�[���h�V�X�e���|�C���^
 *
 * @retval	int			���𐔁i�ő�3�j
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
 * @brief	�w�菇�ʂ̃����X�^�[�i���o�[��Ԃ�
 * 
 * @param	fsys		�t�B�[���h�V�X�e���|�C���^
 * @param	inNo		���ʁi0�I���W���j
 *
 * @retval	int			�����X�^�[�i���o�[
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
 * @brief	�w�菇�ʂ̘A������Ԃ�
 * 
 * @param	fsys		�t�B�[���h�V�X�e���|�C���^
 * @param	inNo		���ʁi0�I���W���j
 *
 * @retval	int			�A����
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
 * @brief	���݂̘A������Ԃ�
 * 
 * @param	fsys		�t�B�[���h�V�X�e���|�C���^
 *
 * @retval	int			�A����
 *
 */
//-----------------------------------------------------------------------------
int SwayGrassHist_GetNowChain(FIELDSYS_WORK * fsys)
{
	return SwayGrass_GetChain(fsys);
}
//-----------------------------------------------------------------------------
/**
 * @brief	���݂̃����X�^�[�i���o�[��Ԃ�
 * 
 * @param	fsys		�t�B�[���h�V�X�e���|�C���^
 *
 * @retval	int			�����X�^�[�i���o�[
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
 * @brief	3�̗�����A�����̑������Ƀ\�[�g����
 * 
 * @param	inHist	�����f�[�^�|�C���^
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
 * @brief	3�̗�����A�����̑������Ƀ\�[�g����
 * 
 * @param	inHist	�����f�[�^�|�C���^
 * @param	outRec	�i�[�o�b�t�@�|�C���^
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

