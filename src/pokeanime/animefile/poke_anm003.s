//==============================================================================
/**
 * @file	poke_anm003.s
 * @brief	�c�Ɉ�������
 * @author	
 * @date	
 *
 */
//==============================================================================

	.text
	
	.include	"past.h"
	.include	"past_def.h"
	
	.global		PAST_ANIME003
	
// =============================================================================
//
//
//	�c�Ɉ�������
//
//
// =============================================================================
PAST_ANIME003:
	SET_DY_CORRECT		CORRECT_ON_NOT_EQ
	
	//20��̃��[�v��180���i0x8000�j����
	CALL_MF_CURVE_DIVTIME APPLY_SET,0,CURVE_SIN,TARGET_RY,0x28,0x8000,0,20
	//�E�F�C�g5�@10��̃��[�v��4��0x40000�j������
	CALL_MF_CURVE_DIVTIME APPLY_SYNTHE,5,CURVE_SIN,TARGET_RY,0x8,0x40000,0,10
	HOLD_CMD
	
	SET_DY_CORRECT		CORRECT_OFF
	END_ANM
