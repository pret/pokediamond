//============================================================================================
/**
 * @file	agb_slot_enc.c
 * @brief	�`�f�a�X���b�g�o�[�W�����ʃG���J�E���g�֘A
 * @author	saitou
 *
 */
//============================================================================================

#include "common.h"
#include "encount_dat.h"

#include "agb_slot_enc.h"

//-----------------------------------------------------------------------------
/**
 * AGB�X���b�g�G���J�E���g�e�[�u�������ւ�
 *
 * @param	*inEncData			�G���J�E���g�f�[�^
 * @param	inBookGet			�S���}�ӓ���t���O
 * @param	*outAgbEncMonsNo1	�G���J�E���g�|�P����1�̖�
 * @param	*outAgbEncMonsNo2	�G���J�E���g�|�P����2�̖�
 *
 * @return	none
 */
//-----------------------------------------------------------------------------
void AgbSlotEnc_SetAgbSlotEnc(	const ENCOUNT_DATA *inEncData,
								const BOOL inBookGet,
								int *outAgbEncMonsNo1, int *outAgbEncMonsNo2)
{
	//�S���}�ӓ��肵�Ă��Ȃ���΁A�������Ȃ�
	if (!inBookGet){
		return;
	}
	
	//AGB�X���b�g�̃o�[�W�����ʂɃG���J�E���g�f�[�^���Z�b�g
	switch(sys.AgbCasetteVersion){		
	case VERSION_SAPPHIRE:
		(*outAgbEncMonsNo1) = inEncData->SapphireEnc[0];
		(*outAgbEncMonsNo2) = inEncData->SapphireEnc[1];
		break;
	case VERSION_RUBY:
		(*outAgbEncMonsNo1) = inEncData->RubyEnc[0];
		(*outAgbEncMonsNo2) = inEncData->RubyEnc[1];
		break;
	case VERSION_EMERALD:
		(*outAgbEncMonsNo1) = inEncData->EmeraldEnc[0];
		(*outAgbEncMonsNo2) = inEncData->EmeraldEnc[1];
		break;
	case VERSION_RED:
		(*outAgbEncMonsNo1) = inEncData->FireEnc[0];
		(*outAgbEncMonsNo2) = inEncData->FireEnc[1];
		break;
	case VERSION_GREEN:
		(*outAgbEncMonsNo1) = inEncData->LeafEnc[0];
		(*outAgbEncMonsNo2) = inEncData->LeafEnc[1];
		break;
	}
}
