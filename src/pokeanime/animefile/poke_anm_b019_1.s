//==============================================================================
/**
 * @file	poke_anm_b019_1.s
 * @brief	�X�p�[�N
 * @author	
 * @date	
 *
 */
//==============================================================================

	.text
	
	.include	"past.h"
	.include	"past_def.h"
	
	.global		PAST_ANIME_B019_1
	
// =============================================================================
//
//
//	�w��	�X�p�[�N
//
//
// =============================================================================
PAST_ANIME_B019_1:
	SET_WORK_VAL		WORK0,2		//�h�ꕝ

	//�ړ�
	SET_ADD_PARAM	PARAM_DX,USE_WORK,WORK0,PARAM_SET
	APPLY_TRANS
	MUL_WORK_VAL	WORK0,CALC_VAL,WORK0,-1
	
	SET_PALETTE_FADE	16,16,0,0x3ff
	SET_REQUEST

	SET_PALETTE_FADE	0,0,0,0x3ff
	SET_REQUEST

	START_LOOP	7
		SET_ADD_PARAM	PARAM_DX,USE_WORK,WORK0,PARAM_SET
		APPLY_TRANS
		MUL_WORK_VAL	WORK0,CALC_VAL,WORK0,-1
		SET_REQUEST
	END_LOOP
	
	//�ړ�
	SET_ADD_PARAM	PARAM_DX,USE_WORK,WORK0,PARAM_SET
	APPLY_TRANS
	MUL_WORK_VAL	WORK0,CALC_VAL,WORK0,-1
	
	SET_PALETTE_FADE	16,16,0,0x3ff
	SET_REQUEST

	SET_PALETTE_FADE	0,0,0,0x3ff
	SET_REQUEST

	START_LOOP	7
		SET_ADD_PARAM	PARAM_DX,USE_WORK,WORK0,PARAM_SET
		APPLY_TRANS
		MUL_WORK_VAL	WORK0,CALC_VAL,WORK0,-1
		SET_REQUEST
	END_LOOP

	//�ړ�
	SET_ADD_PARAM	PARAM_DX,USE_WORK,WORK0,PARAM_SET
	APPLY_TRANS
	MUL_WORK_VAL	WORK0,CALC_VAL,WORK0,-1
	
	SET_PALETTE_FADE	16,16,0,0x3ff
	SET_REQUEST

	SET_PALETTE_FADE	0,0,0,0x3ff
	SET_REQUEST
	
	
	START_LOOP		7
		//�ړ�
		SET_ADD_PARAM	PARAM_DX,USE_WORK,WORK0,PARAM_SET
		APPLY_TRANS
		MUL_WORK_VAL	WORK0,CALC_VAL,WORK0,-1
		SET_PALETTE_FADE	16,16,0,0x3ff
		SET_REQUEST
		
		SET_PALETTE_FADE	0,0,0,0x3ff
		SET_REQUEST

	END_LOOP
	
	END_ANM
