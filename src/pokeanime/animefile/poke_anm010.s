//==============================================================================
/**
 * @file	poke_anm010.s
 * @brief	
 * @author	
 * @date	
 *
 */
//==============================================================================

	.text
	
	.include	"past.h"
	.include	"past_def.h"
	
	.global		PAST_ANIME010
	
// =============================================================================
//
//
//	���W���x�[		�X���[
//
//
// =============================================================================
PAST_ANIME010:
	//50��̏����ō��E0xccc�̊p�x�X����
	CALL_MF_CURVE_DIVTIME APPLY_SET,0,CURVE_SIN_MINUS,TARGET_ROT,0xccc,0x10000,0,50
	//�X���ɂ��킹�ď������ړ�
	CALL_MF_CURVE_DIVTIME APPLY_SET,0,CURVE_SIN_MINUS,TARGET_DX,10,0x10000,0,50
	HOLD_CMD

	END_ANM
