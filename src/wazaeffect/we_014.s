//==============================================================================
/**
 * @file	we_014.s
 * @brief	�邬�̂܂�			14
 * @author	goto
 * @date	2005.07.13(��)
 *
 * �����ɐF�X�ȉ�����������Ă��悢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_TURUGINOMAI
	
// =============================================================================
//
//
//	���邬�̂܂�			14
//
//
// =============================================================================
WEST_TURUGINOMAI:
	
	LOAD_PARTICLE_DROP	0,W_014_SPA
	ADD_PARTICLE 	0,W_014_SWORD_ROLL, EMTFUNC_ATTACK_POS
	ADD_PARTICLE 	0,W_014_BALL_ROLL, EMTFUNC_ATTACK_POS

	SE_L			SEQ_SE_DP_SHUSHU

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
