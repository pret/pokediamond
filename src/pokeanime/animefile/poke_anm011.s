//==============================================================================
/**
 * @file	poke_anm011.s
 * @brief	���Ƃт͂ˁ@�X���[
 * @author	saito
 * @date	
 *
 */
//==============================================================================

	.text
	
	.include	"past.h"
	.include	"past_def.h"
	
	.global		PAST_ANIME011
	
// =============================================================================
//
//
//	���Ƃт͂ˁ@�X���[
//
//
// =============================================================================
PAST_ANIME011:
	//>��ђ���1���
	//8��̏�����0x8000�i180���j������
	CALL_MF_CURVE_DIVTIME	APPLY_SET,0,CURVE_SIN_MINUS,TARGET_DY,10,0x8000,0,8
	//8��̏�����8�ړ�
	CALL_MF_LINE_DIVTIME	APPLY_SET,0,TARGET_DX,8,8
	//8��̏�����0x1000(22.5��)�X��
	CALL_MF_LINE_DIVTIME	APPLY_SET,0,TARGET_ROT,0x1000,8
	HOLD_CMD
	
	//>��ђ���2�`4���
	START_LOOP	2

		//�X�v���C�g�ʒu��x=8�ɐݒ� dx��0�ɐݒ�
		SET_ADD_PARAM		PARAM_X,USE_VAL,8,PARAM_SET
		SET_ADD_PARAM		PARAM_DX,USE_VAL,0,PARAM_SET
		APPLY_TRANS
		//�X�v���C�g��]��0x1000�ɃZ�b�g
		SET_ADD_PARAM		PARAM_ROT,USE_VAL,0x1000,PARAM_SET
		APPLY_AFFINE
	
		//12��̏�����0x8000�i180���j������
		CALL_MF_CURVE_DIVTIME	APPLY_SET,0,CURVE_SIN_MINUS,TARGET_DY,10,0x8000,0,12
		//12��̏�����-16�ړ�
		CALL_MF_LINE_DIVTIME	APPLY_SET,0,TARGET_DX,-16,12
		//12��̏�����0x1000�`-0x1000��-0x2000(45��)���X��
		CALL_MF_LINE_DIVTIME	APPLY_ADD,0,TARGET_ROT,-0x2000,12
		HOLD_CMD

		//�X�v���C�g�ʒu��x=-8�ɐݒ� dx��0�ɐݒ�
		SET_ADD_PARAM		PARAM_X,USE_VAL,-8,PARAM_SET
		SET_ADD_PARAM		PARAM_DX,USE_VAL,0,PARAM_SET
		APPLY_TRANS
		//�X�v���C�g��]��-0x1000�ɃZ�b�g
		SET_ADD_PARAM		PARAM_ROT,USE_VAL,-0x1000,PARAM_SET
		APPLY_AFFINE

		//12��̏�����0x8000�i180���j������
		CALL_MF_CURVE_DIVTIME	APPLY_SET,0,CURVE_SIN_MINUS,TARGET_DY,10,0x8000,0,12
		//12��̏�����16�ړ�
		CALL_MF_LINE_DIVTIME	APPLY_SET,0,TARGET_DX,16,12
		//12��̏�����-0x1000�`0x1000��0x2000(45��)���X��
		CALL_MF_LINE_DIVTIME	APPLY_ADD,0,TARGET_ROT,0x2000,12
		HOLD_CMD

	END_LOOP

	//�X�v���C�g�ʒu��x=8�ɐݒ� dx��0�ɐݒ�
	SET_ADD_PARAM		PARAM_X,USE_VAL,8,PARAM_SET
	SET_ADD_PARAM		PARAM_DX,USE_VAL,0,PARAM_SET
	APPLY_TRANS
	//�X�v���C�g��]��0x1000�ɃZ�b�g
	SET_ADD_PARAM		PARAM_ROT,USE_VAL,0x1000,PARAM_SET
	APPLY_AFFINE

	//>��ђ���5���
	//12��̏�����0x8000�i180���j������
	CALL_MF_CURVE_DIVTIME	APPLY_SET,0,CURVE_SIN_MINUS,TARGET_DY,10,0x8000,0,12
	//12��̏�����-16�ړ�
	CALL_MF_LINE_DIVTIME	APPLY_SET,0,TARGET_DX,-16,12
	//12��̏�����0x1000�`-0x1000��-0x2000(45��)���X��
	CALL_MF_LINE_DIVTIME	APPLY_ADD,0,TARGET_ROT,-0x2000,12
	HOLD_CMD

	//�X�v���C�g�ʒu��x=-8�ɐݒ� dx��0�ɐݒ�
	SET_ADD_PARAM		PARAM_X,USE_VAL,-8,PARAM_SET
	SET_ADD_PARAM		PARAM_DX,USE_VAL,0,PARAM_SET
	APPLY_TRANS
	//�X�v���C�g��]��-0x1000�ɃZ�b�g
	SET_ADD_PARAM		PARAM_ROT,USE_VAL,-0x1000,PARAM_SET
	APPLY_AFFINE
	
	//>��ђ���6���
	//12��̏�����0x8000�i180���j������
	CALL_MF_CURVE_DIVTIME	APPLY_SET,0,CURVE_SIN_MINUS,TARGET_DY,10,0x8000,0,12
	//12��̏�����8�ړ�
	CALL_MF_LINE_DIVTIME	APPLY_SET,0,TARGET_DX,8,12
	//12��̏�����0x1000(22.5��)�X��
	CALL_MF_LINE_DIVTIME	APPLY_ADD,0,TARGET_ROT,0x1000,12
	HOLD_CMD
	
	
	END_ANM
