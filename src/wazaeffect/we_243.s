//==============================================================================
/**
 * @file	we_243.s
 * @brief	�~���[�R�[�g			243
 * @author	goto
 * @date	2005.07.13(��)
 *
 * �����ɐF�X�ȉ�����������Ă��悢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_MIRAAKOOTO
	
// =============================================================================
//
//
//	���~���[�R�[�g			243
//
//
// =============================================================================
WEST_MIRAAKOOTO:
	
	LOAD_PARTICLE_DROP	0,W_243_SPA
	ADD_PARTICLE 	0,W_243_243_MIRROR_KIRA,  EMTFUNC_ATTACK_POS
	ADD_PARTICLE 	0,W_243_243_MIRROR_BOARD, EMTFUNC_ATTACK_POS

	SE_L			SEQ_SE_DP_W115

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
