//==============================================================================
/**
 * @file	poke_anm012.s
 * @brief	�����݂悱�Ƃ�
 * @author	saito
 * @date	
 *
 */
//==============================================================================

	.text
	
	.include	"past.h"
	.include	"past_def.h"
	
	.global		PAST_ANIME012
	
// =============================================================================
//
//
//	�����݂悱�Ƃ�
//
//
// =============================================================================
PAST_ANIME011:
	//>��ђ���1���
	//6��̏�����-8�ړ�
	CALL_MF_LINE_DIVTIME	APPLY_SET,0,TARGET_DX,-8,6
	//6��̏�����180��(0x8000)����
	CALL_MF_CURVE_DIVTIME	APPLY_SET,0,CURVE_SIN_MINUS,TARGET_DY,8,0x8000,0,6
	HOLD_CMD

	//�X�v���C�g�ʒu��x=-8�ɐݒ� dx��0�ɐݒ�
	SET_ADD_PARAM		PARAM_X,USE_VAL,-8,PARAM_SET
	SET_ADD_PARAM		PARAM_DX,USE_VAL,0,PARAM_SET
	APPLY_TRANS
	
	//��ђ���2���
	//6��̏�����8�ړ�
	CALL_MF_LINE_DIVTIME	APPLY_SET,0,TARGET_DX,8,6
	//6��̏�����180��(0x8000)����
	CALL_MF_CURVE_DIVTIME	APPLY_SET,0,CURVE_SIN_MINUS,TARGET_DY,8,0x8000,0,6
	HOLD_CMD
		
	//�X�v���C�g�ʒu��x=0�ɐݒ� dx��0�ɐݒ�
	SET_ADD_PARAM		PARAM_X,USE_VAL,0,PARAM_SET
	SET_ADD_PARAM		PARAM_DX,USE_VAL,0,PARAM_SET
	APPLY_TRANS

	//��ђ���3���
	//6��̏�����8�ړ�
	CALL_MF_LINE_DIVTIME	APPLY_SET,0,TARGET_DX,8,6
	//6��̏�����180��(0x8000)����
	CALL_MF_CURVE_DIVTIME	APPLY_SET,0,CURVE_SIN_MINUS,TARGET_DY,8,0x8000,0,6
	HOLD_CMD
		
	//�X�v���C�g�ʒu��x=8�ɐݒ� dx��0�ɐݒ�
	SET_ADD_PARAM		PARAM_X,USE_VAL,8,PARAM_SET
	SET_ADD_PARAM		PARAM_DX,USE_VAL,0,PARAM_SET
	APPLY_TRANS

	//��ђ���4���
	//6��̏�����-8�ړ�
	CALL_MF_LINE_DIVTIME	APPLY_SET,0,TARGET_DX,-8,6
	//6��̏�����180��(0x8000)����
	CALL_MF_CURVE_DIVTIME	APPLY_SET,0,CURVE_SIN_MINUS,TARGET_DY,8,0x8000,0,6
	HOLD_CMD

	END_ANM
