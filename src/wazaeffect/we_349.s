//==============================================================================
/**
 * @file	we_349.s
 * @brief	��イ�̂܂�			349
 * @author	goto
 * @date	2005.07.13(��)
 *
 * �����ɐF�X�ȉ�����������Ă��悢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_RYUUNOMAI
	
// =============================================================================
//
//
//	����イ�̂܂�			349
//
//
// =============================================================================
WEST_RYUUNOMAI:
	
	LOAD_PARTICLE_DROP	0,W_349_SPA
	ADD_PARTICLE 	0,W_349_349_KEMURI_ROLL, EMTFUNC_ATTACK_POS
	
	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 6,  WE_TOOL_M1, 0, 3, WE_PAL_RED, WEDEF_FADE_PARAM, 10
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_M_X, 0, SHAKE_M_WAIT, SHAKE_M_NUM*8,  WE_TOOL_M1 | WE_TOOL_SSP,

	SE_REPEAT_L		SEQ_SE_DP_W379,4,5

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
