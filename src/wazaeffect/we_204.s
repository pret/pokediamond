//==============================================================================
/**
 * @file	we_204.s
 * @brief	���܂���			204
 * @author	goto
 * @date	2005.07.13(��)
 *
 * �����ɐF�X�ȉ�����������Ă��悢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_AMAERU
	
// =============================================================================
//
//
//	�����܂���			204
//
//
// =============================================================================
WEST_AMAERU:
	
	LOAD_PARTICLE_DROP	0,W_204_SPA
	ADD_PARTICLE 	0,W_204_204_AMAERU_HART, EMTFUNC_ATTACK_POS

	FUNC_CALL		WEST_SP_WE_204, 0,0,0,0,0,0,0,0,0

	LOOP_LABEL	3
		SE_L		SEQ_SE_DP_W204
		WAIT 8
	LOOP

	SE_L			SEQ_SE_DP_W204

	WAIT_PARTICLE
	EXIT_PARTICLE	0,

	WAIT_FLAG
	
	SEQEND
