//==============================================================================
/**
 * @file	we_133.s
 * @brief	�h�킷��			133
 * @author	goto
 * @date	2005.07.13(��)
 *
 * �����ɐF�X�ȉ�����������Ă��悢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_DOWASURE
	
// =============================================================================
//
//
//	���h�킷��			133
//
//
// =============================================================================
WEST_DOWASURE:
	
	LOAD_PARTICLE_DROP	0,W_133_SPA
	
	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 0, 12, WE_PAL_BLACK,
	WAIT_FLAG
	
	ADD_PARTICLE 	0,W_133_133_DOWASURE_KEMU,  EMTFUNC_ATTACK_POS
	ADD_PARTICLE 	0,W_133_133_DOWASURE_KEMU2, EMTFUNC_ATTACK_POS

	SE_L			SEQ_SE_DP_W118
	SE_WAITPLAY_L	SEQ_SE_DP_W145B,18

	WAIT_PARTICLE
	EXIT_PARTICLE	0,


	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 12, 0, WE_PAL_BLACK,
	WAIT_FLAG
	
	SEQEND
