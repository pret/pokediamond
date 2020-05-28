//=============================================================================
/**
 * @file	honeytree_data.c
 * @bfief	���h��G���J�E���g�p�Z�[�u�f�[�^�A�N�Z�X�֘A
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
	u8 TreeNo;			//�O��G���J�E���g�����؂̃i���o�[
	HONEY_DATA HoneyData[HONEY_TREE_MAX];
}HONEY_TREE;

//==============================================================================
/**
 * �Z�[�u�f�[�^�T�C�Y�擾
 *
 * @param	none
 *
 * @return	int			�T�C�Y
 */
//==============================================================================
int HTSave_GetSaveDataSize(void)
{
	return sizeof(HONEY_TREE);
}

//==============================================================================
/**
 * �Z�[�u�f�[�^������
 *
 * @param	outHoneyTree		���h��Z�[�u�f�[�^�|�C���^
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
 * �Z�[�u�f�[�^�擪�|�C���^�擾
 *
 * @param	sv		�Z�[�u�|�C���^
 *
 * @return	HT_PTR	���h��f�[�^�|�C���^
 */
//==============================================================================
HT_PTR HTSave_GetHoneyTree(SAVEDATA * sv)
{
	return SaveData_Get(sv, GMDATA_ID_HONEYTREE);
}

//==============================================================================
/**
 * ���؂̎��Ԏ擾
 *
 * @param	inPtr		���h��G���J�E���g�f�[�^�|�C���^
 * @param	inTreeNo	�؃i���o�[
 *
 * @return	int			����
 */
//==============================================================================
const int HTSave_GetTime(HT_PTR inPtr,  const u8 inTreeNo)
{
	return inPtr->HoneyData[inTreeNo].Time;
}

//==============================================================================
/**
 * �e�[�u���������X�^�[�ԍ��擾
 *
 * @param	inPtr		���h��G���J�E���g�f�[�^�|�C���^
 * @param	inTreeNo	�؃i���o�[
 *
 * @return	u8			�e�[�u�������X�^�[�i���o�[
 */
//==============================================================================
const u8 HTSave_GetTblMonsNo(HT_PTR inPtr, const u8 inTreeNo)
{
	return inPtr->HoneyData[inTreeNo].TblMonsNo;
}

//==============================================================================
/**
 * �e�[�u���ԍ��擾
 *
 * @param	inPtr		���h��G���J�E���g�f�[�^�|�C���^
 * @param	inTreeNo	�؃i���o�[
 *
 * @return	u8			�e�[�u���ԍ�
 */
//==============================================================================
const u8 HTSave_GetTblNo(HT_PTR inPtr, const u8 inTreeNo)
{
	return inPtr->HoneyData[inTreeNo].TblNo;
}

//==============================================================================
/**
 * �e�[�u�����A�x�̎擾
 *
 * @param	inPtr		���h��G���J�E���g�f�[�^�|�C���^
 * @param	inTreeNo	�؃i���o�[
 *
 * @return	u8			���A�x
 */
//==============================================================================
const u8 HTSave_GetRareLv(HT_PTR inPtr, const u8 inTreeNo)
{
	return inPtr->HoneyData[inTreeNo].RareLv;
}

//==============================================================================
/**
 * �h��x�������擾
 *
 * @param	inPtr		���h��G���J�E���g�f�[�^�|�C���^
 * @param	inTreeNo	�؃i���o�[
 *
 * @return	u8			�h��
 */
//==============================================================================
const u8 HTSave_GetSwayLv(HT_PTR inPtr, const u8 inTreeNo)
{
	return inPtr->HoneyData[inTreeNo].SwayLv;
}

//==============================================================================
/**
 * �O��G���J�E���g�����؂̃i���o�[���擾
 *
 * @param	inPtr		���h��G���J�E���g�f�[�^�|�C���^
 *
 * @return	int			�؃i���o�[
 */
//==============================================================================
const int HTSave_GetBeforeTreeNo(HT_PTR inPtr)
{
	return inPtr->TreeNo;
}


//==============================================================================
/**
 * ���؂̎��ԃZ�b�g
 *
 * @param	inTime	����
 * @param	inTreeNo	�؃i���o�[
 * @param	outPtr		���h��G���J�E���g�f�[�^�|�C���^
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
 * �e�[�u���������X�^�[�ԍ��Z�b�g
 *
 * @param	inTblMonsNo	�e�[�u�������X�^�[�i���o�[
 * @param	inTreeNo	�؃i���o�[
 * @param	outPtr		���h��G���J�E���g�f�[�^�|�C���^
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
 * �e�[�u���ԍ��Z�b�g
 *@param	inTblNo		�e�[�u���i���o�[
 * @param	inTreeNo	�؃i���o�[
 * @param	outPtr		���h��G���J�E���g�f�[�^�|�C���^
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
 * �e�[�u�����A�x�̃Z�b�g
 *
 * @param	inRareLv	���A���x��
 * @param	inTreeNo	�؃i���o�[
 * @param	outPtr		���h��G���J�E���g�f�[�^�|�C���^
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
 * �h��x�������擾
 *
 * @param	inTreeNo	�؃i���o�[
 * @param	outPtr		���h��G���J�E���g�f�[�^�|�C���^
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
 * �O��G���J�E���g�����؂̃i���o�[���Z�b�g
 *
 * @param	inTreeNo	�؃i���o�[
 * @param	outPtr		���h��G���J�E���g�f�[�^�|�C���^
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
 * ���؃f�[�^�|�C���^�̎擾
 *
 * @param	inTreeNo	�؃i���o�[
 * @param	outPtr		���h��G���J�E���g�f�[�^�|�C���^
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
 * ���ԍX�V
 *
 * @param	sv				�Z�[�u�|�C���^
 * @param	inDiffminute	���ԍ���
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
