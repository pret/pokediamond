//==============================================================================
/**
 * @file	we_235.s
 * @brief	������������			235
 * @author	goto
 * @date	2005.07.13(��)
 *
 * �����ɐF�X�ȉ�����������Ă��悢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_KOUGOUSEI
	
// =============================================================================
//
//
//	��������������			235
//
//
// =============================================================================
WEST_KOUGOUSEI:
	
	LOAD_PARTICLE_DROP	0,W_235_SPA
	ADD_PARTICLE 	0,W_235_CENTER_LIGHT01,  EMTFUNC_ATTACK_POS
	ADD_PARTICLE 	0,W_235_LIGHT_RADIATE01, EMTFUNC_ATTACK_POS

	SE_L			SEQ_SE_DP_W025

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
