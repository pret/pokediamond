//=============================================================================
/**
 * @file	trainercard_data.c
 * @bfief	�g���[�i�[�J�[�h�p�Z�[�u�f�[�^�A�N�Z�X�֘A
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
	int ScruchCount;	//�����
}TR_BADGE_SV_DATA;

typedef struct TR_CARD_SV_DATA_tag
{
	TR_BADGE_SV_DATA BadgeData[BADGE_MAX];
	u8 SighnData[SIGHN_W*SIGHN_H*64/8];	//�T�C���ʃf�[�^
}TR_CARD_SV_DATA;

//==============================================================================
/**
 * �Z�[�u�f�[�^�T�C�Y�擾
 *
 * @param	none
 *
 * @return	int		�T�C�Y
 */
//==============================================================================
int TRCSave_GetSaveDataSize(void)
{
	return sizeof(TR_CARD_SV_DATA);
}

//==============================================================================
/**
 * �Z�[�u�f�[�^������
 *
 * @param	outTrCard	�g���[�i�[�J�[�h�f�[�^�|�C���^
 *
 * @return	none
 */
//==============================================================================
void TRCSave_InitSaveData(TR_CARD_SV_PTR outTrCard)
{
	memset( outTrCard, 0, sizeof(TR_CARD_SV_DATA) );
	//�o�b�W�̕��H����Z�b�g����
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
 * �Z�[�u�f�[�^�擪�|�C���^�擾
 *
 * @param	sv		�Z�[�u�|�C���^
 *
 * @return	TR_CARD_SV_PTR		�g���[�i�[�J�[�h�f�[�^�|�C���^
 */
//==============================================================================
TR_CARD_SV_PTR TRCSave_GetSaveDataPtr(SAVEDATA * sv)
{
	return SaveData_Get(sv, GMDATA_ID_TRCARD);
}

//==============================================================================
/**
 * �T�C���f�[�^�擪�|�C���^�擾
 *
 * @param	inTrCard		�g���[�i�[�J�[�h�f�[�^�|�C���^
 *
 * @return	u8*				�T�C���f�[�^�|�C���^
 */
//==============================================================================
u8 *TRCSave_GetSighnDataPtr(TR_CARD_SV_PTR inTrCard)
{
	return inTrCard->SighnData;
}

//==============================================================================
/**
 * �o�b�W�f�[�^�擪�|�C���^�擾
 *
 * @param	inTrCard		�g���[�i�[�J�[�h�f�[�^�|�C���^
 *
 * @return	TR_BADGE_DATA_PTR	�o�b�W�f�[�^�|�C���^
 */
//==============================================================================
TR_BADGE_DATA_PTR TRCSave_GetBadgeDataPtr(TR_CARD_SV_PTR inTrCard)
{
	return inTrCard->BadgeData;
}

//==============================================================================
/**
 * �o�b�W��������擾
 *
 * @param	inBadgePtr		�o�b�W�f�[�^�擪�|�C���^
 * @param	inBadgeNo		�o�b�W�i���o�[
 *
 * @return	int				�����
 */
//==============================================================================
int TRCSave_GetBadgeScruchCount(const u8 inBadgeNo, TR_BADGE_DATA_PTR inBadgeDataPtr)
{
	return inBadgeDataPtr[inBadgeNo].ScruchCount;
}

//==============================================================================
/**
 * �o�b�W��������Z�b�g
 *
 * @param	inBadgeNo		�o�b�W�i���o�[
 * @param	inCount			//������
 * @param	outBadgePtr		�o�b�W�f�[�^�擪�|�C���^
 * 
 *
 * @return	none
 */
//==============================================================================
void TRCSave_SetBadgeScruchCount(const u8 inBadgeNo, const int inCount, TR_BADGE_DATA_PTR outBadgeDataPtr)
{
	outBadgeDataPtr[inBadgeNo].ScruchCount = inCount;
}
