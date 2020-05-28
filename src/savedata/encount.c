//============================================================================================
/**
 * @file	encount.c
 * @brief	�G���J�E���g�֘A�A�N�Z�X�p�\�[�X
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
//���؃f�[�^
typedef struct HONEY_TREE_tag
{
	u8 TreeNo;			//�O��G���J�E���g�����؂̃i���o�[
	HONEY_DATA HoneyData[HONEY_TREE_MAX];
}HONEY_TREE;

//���R�f�[�^
typedef struct HILL_BACK_DATA_tag
{
	BOOL TalkFlg;	//�b�������L���t���O	<<�ʂɃZ�[�u���Ă���Ƃ��낪�������̂Ŗ��g�p 20060526
	u16 EncTblIdx1;	//���R�G���J�E���g�e�[�u���C���f�b�N�X1��
	u16 EncTblIdx2;	//���R�G���J�E���g�e�[�u���C���f�b�N�X2��
}HILL_BACK_DATA;

//���@�̃]�[������
typedef struct PLAYER_ZONE_HIST_tag
{
	int BeforeZone;	//�O��]�[��
	int OldZone;	//�O�X��]�[��
}PLAYER_ZONE_HIST;

//�ړ��|�P�����f�[�^
typedef struct MV_POKE_DATA_tag{

	int ZoneID;			//�]�[���h�c
	u32	PowRnd;		// �p���[����
	u32	PersonalRnd;	// ������

	u16	MonsNo;				// �|�P�����i���o�[
	u16	Hp;				// HP

	u8	Lv;				// Lv
	u8	Cond;			// ��Ԉُ�

	u8	Encount;		// �G���J�E���g�t���O
	u8	Dummy;

}MV_POKE_DATA;

typedef struct ENC_SV_DATA_tag
{
	int SafariRandSeed;			//�T�t�@�������_���̎�
	int GenerateRandSeed;		//��ʔ��������_���̎�
	HILL_BACK_DATA HillBackData;			//���R�f�[�^
	HONEY_TREE HoneyTree;		//���؃f�[�^
	SWAY_GRASS_HIST		SwayGrassHist;	//�h�ꑐ����
	PLAYER_ZONE_HIST	PlayerZoneHist;	//�]�[������
	MV_POKE_DATA	MovePokeData[MOVE_POKE_MAX];	//�ړ��|�P�����f�[�^
	u8 MovePokeZoneIdx[MOVE_POKE_MAX];	//�ړ��|�P�������݃]�[���C���f�b�N�X
	u8 GenerateValid;					//��ʔ��������t���O
	u8 SprayCount;						//�X�v���[�L������(�ő�250��)
	u8 PokeSearcherCharge;				//�|�P�T�[�`���[�d�l�i�ő�50�炵���j
	u8 VidroType;						//�g�p���Ă���r�[�h���ividro_type.h�ɒ�`�j
	
}ENC_SV_DATA;

//----------------------------------------------------------
/**
 * @brief	�G���J�E���g�֘A�Z�[�u�f�[�^�T�C�Y�擾
 * 
 * @return	int		ENC_SV_DATA�̃T�C�Y
 */
//----------------------------------------------------------
int EncDataSave_GetWorkSize(void)
{
	return sizeof(ENC_SV_DATA);
}

//----------------------------------------------------------
/**
 * @brief		�G���J�E���g�֘A�Z�[�u�f�[�^�̏�����
 * 
 * @param	outEncData		�G���J�E���g�֘A�Z�[�u�f�[�^�ւ̃|�C���^
 *
 * @return	none
 */
//----------------------------------------------------------
void EncDataSave_InitSaveData(ENC_SV_PTR outEncData)
{
	memset( outEncData, 0, sizeof(ENC_SV_DATA) );

	//�����_���̎�Z�b�g
	outEncData->SafariRandSeed = gf_mtRand();
	outEncData->GenerateRandSeed = gf_mtRand();
	
	//���R�͂Ȃ������t���O���Ƃ�
	outEncData->HillBackData.TalkFlg = FALSE;
	//���R�G���J�E���g�e�[�u���C���f�b�N�X���Z�b�g
	outEncData->HillBackData.EncTblIdx1 = HILL_BACK_POKE_NONE;
	outEncData->HillBackData.EncTblIdx2 = HILL_BACK_POKE_NONE;
	//���؏�����
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
	//��ʔ��������t���O�𗎂Ƃ�
	outEncData->GenerateValid = 0;
	//�X�v���[
	outEncData->SprayCount = 0;
	//�|�P�T�[�`���[
	outEncData->PokeSearcherCharge = 0;
	//�r�[�h��
	outEncData->VidroType = VIDRO_NONE;
}

//----------------------------------------------------------
/**
 * @brief		�G���J�E���g�֘A�����_���̎�X�V
 * 
 * @param	outEncData		�G���J�E���g�֘A�Z�[�u�f�[�^�ւ̃|�C���^
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
 * @brief	�G���J�E���g�֘A�����_���̎�擾
 * 
 * @param	inEncData		�G���J�E���g�֘A�Z�[�u�f�[�^�ւ̃|�C���^
 * @param	inSeedType		�����_���̎�̎�ށiencount.h�ɈӋ`�j
 *
 * @return	u32				�T�t�@�������_���̎�
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
 * @brief	�h�ꑐ�����f�[�^�擾
 * 
 * @param	outEncData		�G���J�E���g�֘A�Z�[�u�f�[�^�ւ̃|�C���^
 *
 * @return	�h�ꑐ�����f�[�^�|�C���^
 */
//----------------------------------------------------------
SWAY_GRASS_HIST *  EncDataSave_GetSwayGrassHist(ENC_SV_PTR outEncData)
{
	return &(outEncData->SwayGrassHist);
}

//==============================================================================
/**
 * �Z�[�u�f�[�^�擪�|�C���^�擾
 *
 * @param	sv		�Z�[�u�|�C���^
 *
 * @return	ENC_SV_PTR		�g���[�i�[�J�[�h�f�[�^�|�C���^
 */
//==============================================================================
ENC_SV_PTR EncDataSave_GetSaveDataPtr(SAVEDATA * sv)
{
	return SaveData_Get(sv, GMDATA_ID_ENCOUNT);
}

//���؊֘A-------------------------------------------------------------------------------------------------------------

//==============================================================================
/**
 * ���؃f�[�^�|�C���^�擾
 *
 * @param	sv		�Z�[�u�|�C���^
 *
 * @return	HT_PTR	���h��f�[�^�|�C���^
 */
//==============================================================================
HT_PTR EncDataSave_GetHoneyTree(ENC_SV_PTR inEncData)
{
	return &(inEncData->HoneyTree);
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
 * ��ʔ����J�n
 *
 * @param	sv				�Z�[�u�|�C���^
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
 * ��ʔ���������Ԃ�
 *
 * @param	inEncData			�G���J�E���g�֘A�Z�[�u�|�C���^
 *
 * @return	u8 0�ȊO�F��ʔ�����
 */
//==============================================================================
u8 EncDataSave_IsGenerate( ENC_SV_PTR inEncData )
{
	return inEncData->GenerateValid;
}

//==============================================================================
/**
 * ��l���̃]�[�������̍X�V
 *
 * @param	outEncData			�G���J�E���g�֘A�Z�[�u�|�C���^
 * @param	inZoneID			�]�[���h�c
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
 * ��l���̑O�X�񂢂��]�[�����擾
 *
 * @param	inEncData		�G���J�E���g�֘A�Z�[�u�|�C���^
 *
 * @return	int				�]�[���h�c
 */
//==============================================================================
int EncDataSave_GetPlayerOldZone(ENC_SV_PTR inEncData)
{
	return inEncData->PlayerZoneHist.OldZone;
}

//==============================================================================
/**
 * �w��ړ��|�P�����̃]�[���C���f�b�N�X���擾
 *
 * @param	inEncData		�G���J�E���g�֘A�Z�[�u�|�C���^
 * @param	inTargetPoke	�ړ��|�P����(0�`2)
 *
 * @return	u8				�]�[���C���f�b�N�X
 */
//==============================================================================
u8 EncDataSave_GetMovePokeZoneIdx(ENC_SV_PTR inEncData, const u8 inTargetPoke)
{
	GF_ASSERT(inTargetPoke<MOVE_POKE_MAX);
	
	return inEncData->MovePokeZoneIdx[inTargetPoke];
}

//==============================================================================
/**
 * �w��ړ��|�P�����̃]�[���C���f�b�N�X���Z�b�g
 *
 * @param	outEncData		�G���J�E���g�֘A�Z�[�u�|�C���^
 * @param	inTargetPoke	�ړ��|�P����(0�`2)
 * @param	inZoneIndex		�]�[���C���f�b�N�X
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
 * �w��ړ��|�P�����̃G���J�E���g�t���O�݂āA�ړ����Ă��邩�ǂ������`�F�b�N
 *
 * @param	inEncData		�G���J�E���g�֘A�Z�[�u�|�C���^
 * @param	inTargetPoke	�ړ��|�P����(0�`2)
 *
 * @return	u8			0�ȊO:�ړ����Ă�	0:�ړ����ĂȂ�
 */
//==============================================================================
u8 EncDataSave_IsMovePokeValid(ENC_SV_PTR inEncData, const u8 inTargetPoke)
{
	GF_ASSERT(inTargetPoke<MOVE_POKE_MAX);
	return inEncData->MovePokeData[inTargetPoke].Encount;
}

//==============================================================================
/**
 * �w��ړ��|�P�����f�[�^�̃N���A
 *
 * @param	inEncData		�G���J�E���g�֘A�Z�[�u�|�C���^
 * @param	inTargetPoke	�ړ��|�P����(0�`2)
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
 * �w��ړ��|�P�����f�[�^�|�C���^�̎擾
 *
 * @param	inEncData		�G���J�E���g�֘A�Z�[�u�|�C���^
 * @param	inTargetPoke	�ړ��|�P����(0�`2)
 *
 * @return	MPD_PTR			�ړ��|�P�����f�[�^
 */
//==============================================================================
MPD_PTR	EncDataSave_GetMovePokeDataPtr(ENC_SV_PTR inEncData, const u8 inTargetPoke)
{
	GF_ASSERT(inTargetPoke<MOVE_POKE_MAX);
	return &(inEncData->MovePokeData[inTargetPoke]);
}

//==============================================================================
/**
 * �ړ��|�P�����f�[�^�p�����[�^�擾
 *
 * @param	inMPData		�ړ����|�P�����f�[�^�|�C���^
 * @param	inParamID		�p�����[�^�h�c
 *
 * @return	u32
 */
//==============================================================================
u32 EncDataSave_GetMovePokeDataParam(const MPD_PTR inMPData, const u8 inParamID)
{
	u32 val;
	switch(inParamID){
	case MP_PARAM_ZONE_ID:			//�o���]�[��
		val = inMPData->ZoneID;
		break;
	case MP_PARAM_POW_RND:			//�p���[����
		val = inMPData->PowRnd;
		break;
	case MP_PARAM_PER_RND:			//������
		val = inMPData->PersonalRnd;
		break;
	case MP_PARAM_MONSNO:			//�����X�^�[�i���o�[
		val = inMPData->MonsNo;
		break;
	case MP_PARAM_HP:				//�g�o
		val = inMPData->Hp;
		break;
	case MP_PARAM_LV:				//�k�u
		val = inMPData->Lv;
		break;
	case MP_PARAM_COND:				//��Ԉُ�
		val = inMPData->Cond;
		break;
	case MP_PARAM_ENC:				//�G���J�E���g�t���O
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
 * �ړ��|�P�����f�[�^�p�����[�^�Z�b�g
 *
 * @param	EncData		�G���J�E���g�֘A�Z�[�u�|�C���^
 * @param	inParamID	�p�����[�^�h�c
 * @param	inVal		�Z�b�g����l
 *
 * @return	none
 */
//==============================================================================
void EncDataSave_SetMovePokeDataParam(MPD_PTR outMPData, const u8 inParamID, const u32 inVal)
{
	u32 val;
	switch(inParamID){
	case MP_PARAM_ZONE_ID:			//�o���]�[��
		outMPData->ZoneID = inVal;
		break;
	case MP_PARAM_POW_RND:			//�p���[����
		outMPData->PowRnd = inVal;
		break;
	case MP_PARAM_PER_RND:			//������
		outMPData->PersonalRnd = inVal;
		break;
	case MP_PARAM_MONSNO:			//�����X�^�[�i���o�[
		outMPData->MonsNo = inVal;
		break;
	case MP_PARAM_HP:				//�g�o
		outMPData->Hp = inVal;
		break;
	case MP_PARAM_LV:				//�k�u
		outMPData->Lv = inVal;
		break;
	case MP_PARAM_COND:				//��Ԉُ�
		outMPData->Cond = inVal;
		break;
	case MP_PARAM_ENC:				//�G���J�E���g�t���O
		outMPData->Encount = inVal;
		break;
	defauld:
		GF_ASSERT(0);
	}
}

//==============================================================================
/**
 * �|�P�T�[�`���[�d�l���i�[���������o�̃|�C���^���擾
 *
 * @param	inEncData		�G���J�E���g�֘A�Z�[�u�|�C���^
 *
 * @return	u8*				�|�P�T�[�`���[�[�d�l�|�C���^
 */
//==============================================================================
u8 *EncDataSave_GetPokeSearcherCharge(ENC_SV_PTR inEncData)
{
	return &(inEncData->PokeSearcherCharge);
}

//==============================================================================
/**
 * �X�v���[�L���������i�[���������o�̃|�C���^���擾
 *
 * @param	inEncData		�G���J�E���g�֘A�Z�[�u�|�C���^
 *
 * @return	u8*				�X�v���[�L�������|�C���^
 */
//==============================================================================
u8 *EncDataSave_GetSprayCnt(ENC_SV_PTR inEncData)
{
	return &(inEncData->SprayCount);
}

//==============================================================================
/**
 * �X�v���[���g�p�ł��邩�ǂ����̃`�F�b�N
 * 
 * @param	inEncData		�G���J�E���g�֘A�Z�[�u�|�C���^
 *
 * @return	BOOL	TRUE:�g�p��		FALSE:�g�p�s��
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
 * �r�[�h���^�C�v�Z�b�g
 * 
 * @param	outEncData		�G���J�E���g�֘A�Z�[�u�|�C���^
 * @param	inType			�r�[�h���^�C�v
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
 * �r�[�h���^�C�v�擾
 * 
 * @param	inEncData		�G���J�E���g�֘A�Z�[�u�|�C���^
 *
 * @return	u8			�r�[�h���^�C�v
 */
//==============================================================================
u8 EncDataSave_GetVidro(ENC_SV_PTR inEncData)
{
	return inEncData->VidroType;
}

//==============================================================================
/**
 * ���R�G���J�E���g�|�P�����C���f�b�N�X�̎擾
 *
 * @param	sv				�Z�[�u�f�[�^�|�C���^
 * @param	outIndex1		���R�|�P�����C���f�b�N�X
 * @param	outIndex2		���R�|�P�����C���f�b�N�X
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
 * ���R�G���J�E���g�|�P�����C���f�b�N�X�̃Z�b�g�i�����o�����j
 *
 * @param	sv			�Z�[�u�f�[�^�|�C���^
 * @param	inIndex		���R�|�P�����C���f�b�N�X
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

