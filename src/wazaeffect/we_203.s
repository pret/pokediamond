//==============================================================================
/**
 * @file	we_203.s
 * @brief	���炦��			203
 * @author	goto
 * @date	2005.07.13(��)
 *
 * �����ɐF�X�ȉ�����������Ă��悢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_KORAERU
	
// =============================================================================
//
//
//	�����炦��			203
//
//
// =============================================================================
WEST_KORAERU:
	
	LOAD_PARTICLE_DROP	0,W_203_SPA
	ADD_PARTICLE 	0,W_203_203_KORAERU_LINE, EMTFUNC_ATTACK_POS

	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 6,  WE_TOOL_M1, 0, 2, WE_PAL_RED, 10,0

	SE_REPEAT		SEQ_SE_DP_W082,WAZA_SE_PAN_AT,3,4
	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	WAIT_FLAG
	SEQEND
