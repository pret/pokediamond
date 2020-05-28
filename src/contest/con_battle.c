//==============================================================================
/**
 * @file	con_battle.c
 * @brief	�R���e�X�g�E�퓬���ʏ���
 * @author	matsuda
 * @date	2006.06.14(��)
 *
 * �I�[�o�[���C�̈��bc_common�ɔz�u����܂�
 */
//==============================================================================
#include "common.h"
#include "contest/contest.h"
#include "poketool/monsno.h"



//--------------------------------------------------------------
/**
 * @brief   �R���e�X�g�Ŕ��]�����Ȃ��|�P�������`�F�b�N
 *
 * @param   monsno		�|�P�����ԍ�
 *
 * @retval  TRUE�F���]����
 * @retval  FALSE�F���]���Ȃ�
 */
//--------------------------------------------------------------
BOOL ContestPokeFlipCheck(u32 monsno)
{
	switch(monsno){
	case MONSNO_HITODEMAN:
	case MONSNO_EREBUU:
	case MONSNO_ARIGEITU:
	case MONSNO_ANNOON:
	case MONSNO_NYUURA:
	case MONSNO_ROZERIA:
	case MONSNO_ZANGUUSU:
	case MONSNO_ABUSORU:
	case MONSNO_SUBOMII:
	case MONSNO_ROZUREIDO:
	case MONSNO_BUUBAAN:
	case MONSNO_MORIGAME:
	case MONSNO_TOGEON:
	case MONSNO_KINGURAA:
		return FALSE;
	}
	return TRUE;
}

