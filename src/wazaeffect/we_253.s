//==============================================================================
/**
 * @file	we_253.s
 * @brief	���킮			253
 * @author	goto
 * @date	2005.07.13(��)
 *
 * �����ɐF�X�ȉ�����������Ă��悢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_SAWAGU
	
// =============================================================================
//
//
//	�����킮			253
//
//
// =============================================================================
WEST_SAWAGU:
	
	LOAD_PARTICLE_DROP	0,W_253_SPA

	SE_REPEAT_L		SEQ_SE_DP_W253,29,3
	FUNC_CALL	WEST_SP_WE_SSP_POKE_SCALE_UPDOWN, 8, (WE_TOOL_M1 | WE_TOOL_SSP), 100, 120, 100, 80, 100, 1, (5 << 16) | 5
	WAIT_FLAG
	
	ADD_PARTICLE 	0,W_253_253_VOICE_RING, EMTFUNC_ATTACK_POS
	ADD_PARTICLE 	0,W_253_253_VOICE_BURN, EMTFUNC_ATTACK_POS
	FUNC_CALL	WEST_SP_WE_SSP_POKE_SCALE_UPDOWN, 8, (WE_TOOL_M1 | WE_TOOL_SSP), 100, 80, 100, 140, 100, 1, (5 << 16) | 5
	WAIT_FLAG
	
	LOOP_LABEL		2
		FUNC_CALL	WEST_SP_WE_SSP_POKE_SCALE_UPDOWN, 8, (WE_TOOL_M1 | WE_TOOL_SSP), 100, 120, 100, 80, 100, 1, (5 << 16) | 5
		WAIT_FLAG
		FUNC_CALL	WEST_SP_WE_SSP_POKE_SCALE_UPDOWN, 8, (WE_TOOL_M1 | WE_TOOL_SSP), 100, 80, 100, 140, 100, 1, (5 << 16) | 5
		WAIT_FLAG
	
	LOOP

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
