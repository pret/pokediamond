//==============================================================================
/**
 * @file	we_147.s
 * @brief	�L�m�R�̂ق���			147
 * @author	goto
 * @date	2005.07.13(��)
 *
 * �����ɐF�X�ȉ�����������Ă��悢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_KINOKONOHOUSI
	
// =============================================================================
//
//
//	���L�m�R�̂ق���			147
//
//
// =============================================================================
WEST_KINOKONOHOUSI:
	
	LOAD_PARTICLE_DROP	0,W_147_SPA
	ADD_PARTICLE 	0,W_147_147_KINOKOHOU_KONA, EMTFUNC_DEFENCE_POS
	
	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 6,  WE_TOOL_E1, 0, 3, WE_PAL_GREEN, 10,10

	SE_REPEAT_R		SEQ_SE_DP_W077B,3,12

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
