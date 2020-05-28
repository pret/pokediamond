//=============================================================================
/**
 * @file	honeytree_data.h
 * @bfief	���h��G���J�E���g�p�Z�[�u�f�[�^�A�N�Z�X�֘A
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
	int Time;			//����h��������
///	u16 State;			//�؂̏�
	u8 TblMonsNo;		//�e�[�u���������X�^�[�ԍ�
	u8 TblNo;			//�G���J�E���g�e�[�u���ԍ�
	u8 RareLv;			//���A�x	�n�Y���A�ʏ�A���A�A�����A
	u8 SwayLv;			//�h�ꃂ�[�V�����̓x����
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
