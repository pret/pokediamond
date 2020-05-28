//==============================================================================
/**
 * @file	poke_anm_b009_3.s
 * @brief	�O�p�ړ�
 * @author	
 * @date	
 *
 */
//==============================================================================

	.text
	
	.include	"past.h"
	.include	"past_def.h"
	
	.global		PAST_ANIME_B009_3
	
// =============================================================================
//
//
//	�w��	�O�p�ړ�
//
//
// =============================================================================
PAST_ANIME_B009_3:
	//6��̏�����x,y��+12������
	CALL_MF_LINE APPLY_SET,0,TARGET_DX,2,0,6
	CALL_MF_LINE APPLY_SET,0,TARGET_DY,2,0,6
	HOLD_CMD

	//�X�v���C�g�ʒu��x=12,y=12�ɐݒ� dx,dy��0�ɐݒ�
	SET_ADD_PARAM		PARAM_X,USE_VAL,12,PARAM_SET
	SET_ADD_PARAM		PARAM_Y,USE_VAL,12,PARAM_SET
	SET_ADD_PARAM		PARAM_DX,USE_VAL,0,PARAM_SET
	SET_ADD_PARAM		PARAM_DY,USE_VAL,0,PARAM_SET
	APPLY_TRANS

	//6��̏�����x��-24������
	CALL_MF_LINE APPLY_SET,0,TARGET_DX,-4,0,6
	HOLD_CMD

	//�X�v���C�g�ʒu��x=-12,y=12�ɐݒ� dx,dy��0�ɐݒ�
	SET_ADD_PARAM		PARAM_X,USE_VAL,-12,PARAM_SET
	SET_ADD_PARAM		PARAM_Y,USE_VAL,12,PARAM_SET
	SET_ADD_PARAM		PARAM_DX,USE_VAL,0,PARAM_SET
	SET_ADD_PARAM		PARAM_DY,USE_VAL,0,PARAM_SET
	APPLY_TRANS

	//6��̏�����x��+12,y��-12������
	CALL_MF_LINE APPLY_SET,0,TARGET_DX,2,0,6
	CALL_MF_LINE APPLY_SET,0,TARGET_DY,-2,0,6
	HOLD_CMD

	//�X�v���C�g�ʒu��x=0,y=0�ɐݒ� dx,dy��0�ɐݒ�
	SET_ADD_PARAM		PARAM_X,USE_VAL,0,PARAM_SET
	SET_ADD_PARAM		PARAM_Y,USE_VAL,0,PARAM_SET
	SET_ADD_PARAM		PARAM_DX,USE_VAL,0,PARAM_SET
	SET_ADD_PARAM		PARAM_DY,USE_VAL,0,PARAM_SET
	APPLY_TRANS
	
	END_ANM
