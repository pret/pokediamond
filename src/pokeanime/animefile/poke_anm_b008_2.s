//==============================================================================
/**
 * @file	poke_anm_b008_2.s
 * @brief	
 * @author	
 * @date	
 *
 */
//==============================================================================

	.text
	
	.include	"past.h"
	.include	"past_def.h"
	
	.global		PAST_ANIME_B008_2
	
// =============================================================================
//
//
//	�w��	�K�N���K�N���m�[�}��
//
//
// =============================================================================
PAST_ANIME_B008_2:
	SET_WORK_VAL	 WORK0,0		//�J�E���^�Ƃ��Ďg�p
	SET_WORK_VAL	 WORK2,0		//�p�x�Ƃ��Ďg�p

	START_LOOP 15
		ADD_WORK_VAL	WORK0,CALC_VAL,WORK0,1
		ADD_WORK_VAL	WORK2,CALC_VAL,WORK2,0x5000
	
		//�h�ꕝ���v�Z����WORK1�ɃZ�b�g
		SUB_WORK_VAL	WORK1,CALC_VAL,CALC_WORK,15,WORK0
		MUL_WORK_VAL	WORK1,CALC_VAL,WORK1,6
		DIV_WORK_VAL	WORK1,CALC_WORK,CALC_VAL,WORK1,15

		//WORK3�ɃT�C���v�Z���ʂ��Z�b�g�@�p�xWORK2,�U��WORK1�A�ʑ�0
		SET_WORK_VAL_SIN	WORK3,WORK2,USE_WORK,WORK1,USE_VAL,0

		//�A�j���f�[�^dy��WORK3���Z�b�g
		SET_ADD_PARAM	PARAM_DY,USE_WORK,WORK3,PARAM_SET

		APPLY_TRANS
		SET_REQUEST
	END_LOOP

	SET_WAIT	7

	SET_WORK_VAL	 WORK0,0		//�J�E���^�Ƃ��Ďg�p
	SET_WORK_VAL	 WORK2,0		//�p�x�Ƃ��Ďg�p

	START_LOOP 15
		ADD_WORK_VAL	WORK0,CALC_VAL,WORK0,1
		ADD_WORK_VAL	WORK2,CALC_VAL,WORK2,0x5000
	
		//�h�ꕝ���v�Z����WORK1�ɃZ�b�g
		SUB_WORK_VAL	WORK1,CALC_VAL,CALC_WORK,15,WORK0
		MUL_WORK_VAL	WORK1,CALC_VAL,WORK1,6
		DIV_WORK_VAL	WORK1,CALC_WORK,CALC_VAL,WORK1,15

		//WORK3�ɃT�C���v�Z���ʂ��Z�b�g�@�p�xWORK2,�U��WORK1�A�ʑ�0
		SET_WORK_VAL_SIN	WORK3,WORK2,USE_WORK,WORK1,USE_VAL,0

		//�A�j���f�[�^dy��WORK3���Z�b�g
		SET_ADD_PARAM	PARAM_DY,USE_WORK,WORK3,PARAM_SET

		APPLY_TRANS
		SET_REQUEST
	END_LOOP
	
	END_ANM
