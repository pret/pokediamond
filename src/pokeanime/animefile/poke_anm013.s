//==============================================================================
/**
 * @file	poke_anm013.s
 * @brief	���Ƃт͂ˁ@�X���[��
 * @author	saito
 * @date	
 *
 */
//==============================================================================

	.text
	
	.include	"past.h"
	.include	"past_def.h"
	
	.global		PAST_ANIME013
	
// =============================================================================
//
//
//	���Ƃт͂ˁ@�X���[��
//
//
// =============================================================================
PAST_ANIME013:
	//>��ђ���1���
	//4��̏�����0x8000�i180���j������
	CALL_MF_CURVE_DIVTIME	APPLY_SET,0,CURVE_SIN_MINUS,TARGET_DY,10,0x8000,0,4
	//4��̏�����8�ړ�
	CALL_MF_LINE_DIVTIME	APPLY_SET,0,TARGET_DX,8,4
	//4��̏�����0x800(11.25��)�X��
	CALL_MF_LINE_DIVTIME	APPLY_SET,0,TARGET_ROT,0x800,4
	HOLD_CMD
	
	//>��ђ���2�`4���
	START_LOOP	2
		
		//�X�v���C�g�ʒu��x=8�ɐݒ� dx��0�ɐݒ�
		SET_ADD_PARAM		PARAM_X,USE_VAL,8,PARAM_SET
		SET_ADD_PARAM		PARAM_DX,USE_VAL,0,PARAM_SET
		APPLY_TRANS
		//�X�v���C�g��]��0x800�ɃZ�b�g
		SET_ADD_PARAM		PARAM_ROT,USE_VAL,0x800,PARAM_SET
		APPLY_AFFINE
		
		//6��̏�����0x8000�i180���j������
		CALL_MF_CURVE_DIVTIME	APPLY_SET,0,CURVE_SIN_MINUS,TARGET_DY,10,0x8000,0,6
		//6��̏�����-16�ړ�
		CALL_MF_LINE_DIVTIME	APPLY_SET,0,TARGET_DX,-16,6
		//6��̏�����0x800�`-0x800��-0x1000(22.5��)���X��
		CALL_MF_LINE_DIVTIME	APPLY_ADD,0,TARGET_ROT,-0x1000,6
		HOLD_CMD

		//�X�v���C�g�ʒu��x=-8�ɐݒ� dx��0�ɐݒ�
		SET_ADD_PARAM		PARAM_X,USE_VAL,-8,PARAM_SET
		SET_ADD_PARAM		PARAM_DX,USE_VAL,0,PARAM_SET
		APPLY_TRANS
		//�X�v���C�g��]��-0x800�ɃZ�b�g
		SET_ADD_PARAM		PARAM_ROT,USE_VAL,-0x800,PARAM_SET
		APPLY_AFFINE

		//6��̏�����0x8000�i180���j������
		CALL_MF_CURVE_DIVTIME	APPLY_SET,0,CURVE_SIN_MINUS,TARGET_DY,10,0x8000,0,6
		//6��̏�����16�ړ�
		CALL_MF_LINE_DIVTIME	APPLY_SET,0,TARGET_DX,16,6
		//6��̏�����-0x800�`0x800��0x1000(22.5��)���X��
		CALL_MF_LINE_DIVTIME	APPLY_ADD,0,TARGET_ROT,0x1000,6
		HOLD_CMD

	END_LOOP

	//�X�v���C�g�ʒu��x=8�ɐݒ� dx��0�ɐݒ�
	SET_ADD_PARAM		PARAM_X,USE_VAL,8,PARAM_SET
	SET_ADD_PARAM		PARAM_DX,USE_VAL,0,PARAM_SET
	APPLY_TRANS
	//�X�v���C�g��]��0x800�ɃZ�b�g
	SET_ADD_PARAM		PARAM_ROT,USE_VAL,0x800,PARAM_SET
	APPLY_AFFINE

	//>��ђ���5���
	//6��̏�����0x8000�i180���j������
	CALL_MF_CURVE_DIVTIME	APPLY_SET,0,CURVE_SIN_MINUS,TARGET_DY,10,0x8000,0,6
	//6��̏�����-16�ړ�
	CALL_MF_LINE_DIVTIME	APPLY_SET,0,TARGET_DX,-16,6
	//6��̏�����0x800�`-0x800��-0x1000(22.5��)���X��
	CALL_MF_LINE_DIVTIME	APPLY_ADD,0,TARGET_ROT,-0x1000,6
	HOLD_CMD

	//�X�v���C�g�ʒu��x=-8�ɐݒ� dx��0�ɐݒ�
	SET_ADD_PARAM		PARAM_X,USE_VAL,-8,PARAM_SET
	SET_ADD_PARAM		PARAM_DX,USE_VAL,0,PARAM_SET
	APPLY_TRANS
	//�X�v���C�g��]��-0x800�ɃZ�b�g
	SET_ADD_PARAM		PARAM_ROT,USE_VAL,-0x800,PARAM_SET
	APPLY_AFFINE
	
	//>��ђ���6���
	//6��̏�����0x8000�i180���j������
	CALL_MF_CURVE_DIVTIME	APPLY_SET,0,CURVE_SIN_MINUS,TARGET_DY,10,0x8000,0,6
	//6��̏�����8�ړ�
	CALL_MF_LINE_DIVTIME	APPLY_SET,0,TARGET_DX,8,6
	//6��̏�����0x800(11.25��)�X��
	CALL_MF_LINE_DIVTIME	APPLY_ADD,0,TARGET_ROT,0x800,6
	HOLD_CMD
	
	
	END_ANM
