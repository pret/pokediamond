//==============================================================================
/**
 * @file	poke_anm004.s
 * @brief	������Ł@�c���
 * @author	
 * @date	
 *
 */
//==============================================================================

	.text
	
	.include	"past.h"
	.include	"past_def.h"
	
	.global		PAST_ANIME004
	
// =============================================================================
//
//
//	������Ł@�c���
//
//
// =============================================================================
PAST_ANIME004:
	SET_WORK_VAL		WORK0,0		//�J�E���^
	START_LOOP	40
		//�p�x���v�Z����WORK2�ɃZ�b�g
		MUL_WORK_VAL	WORK2,CALC_VAL,WORK0,0x10000
		DIV_WORK_VAL	WORK2,CALC_WORK,CALC_VAL,WORK2,40
		
		//WORK1��WORK0��2�Ŋ������]����Z�b�g
		MOD_WORK_VAL	WORK1,CALC_WORK,CALC_VAL,WORK0,2
		//WORK1��0�̂Ƃ�	WORK3��0x20���Z�b�g
		SET_IFWORKVAL	USE_VAL,WORK1,0,COMP_EQUAL,USE_VAL,WORK3,0x20
		//WORK1��1�̂Ƃ�	WORK3��0x8���Z�b�g
		SET_IFWORKVAL	USE_VAL,WORK1,1,COMP_EQUAL,USE_VAL,WORK3,0x8
		
		//WORK4�ɃT�C���v�Z���ʂ��Z�b�g�@�p�xWORK2,�U��WORK3�A�ʑ�0
		SET_WORK_VAL_SIN	WORK4,WORK2,USE_WORK,WORK3,USE_VAL,0

		//WORK5�Ɋg�k�����Z�b�g
		SUB_WORK_VAL		WORK5,CALC_VAL,CALC_WORK,0,WORK4

		//�A�j���f�[�^�ɃZ�b�g
		SET_ADD_PARAM		PARAM_RX,USE_WORK,WORK5,PARAM_SET
		SET_ADD_PARAM		PARAM_RY,USE_WORK,WORK5,PARAM_SET

		//�X�v���C�g�ɔ��f
		APPLY_AFFINE
		
		//�J�E���g�A�b�v
		ADD_WORK_VAL	WORK0,CALC_VAL,WORK0,1

		//�`�惊�N�G�X�g
		SET_REQUEST
	END_LOOP
	
	END_ANM
