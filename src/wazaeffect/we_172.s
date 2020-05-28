//==============================================================================
/**
 * @file	we_172.s
 * @brief	Ç©Ç¶ÇÒÇÆÇÈÇ‹			172
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_KAENGURUMA
	
// =============================================================================
//
//
//	Å°Ç©Ç¶ÇÒÇÆÇÈÇ‹			172
//
//
// =============================================================================
#define MOVE_VAL_X1		(WE_MOVE_X_VAL_DEF)
WEST_KAENGURUMA:
	
	LOAD_PARTICLE_DROP	0,W_172_SPA
	ADD_PARTICLE 	0,W_172_172_KAGURUMA_FIRE1, EMTFUNC_ATTACK_POS

	SE_REPEAT_L		SEQ_SE_DP_W172,3,12

	WAIT			20
	
	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 5, WE_TOOL_M1, 0, 1, WE_PAL_RED, 12
	WAIT_FLAG
	FUNC_CALL		WEST_SP_WE_T05, 3, 3, +MOVE_VAL_X1, WE_TOOL_M1 | WE_TOOL_SSP
	ADD_PARTICLE 	0,W_172_172_KAGURUMA_HIT,  EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_172_172_KAGURUMA_FIRE2, EMTFUNC_DEFENCE_POS
	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 5, WE_TOOL_E1, 0, 1, WE_PAL_RED, 12
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_M_X, 0, SHAKE_M_WAIT, SHAKE_M_NUM,  WE_TOOL_E1 | WE_TOOL_SSP,

	SE_R			SEQ_SE_DP_W172B

	WAIT_FLAG
	FUNC_CALL		WEST_SP_WE_T05, 3, 3, -MOVE_VAL_X1, WE_TOOL_M1 | WE_TOOL_SSP

//	ADD_PARTICLE 	0,W_172_172_KAGURUMA_RING, EMTFUNC_DEFENCE_POS
	
	WAIT_FLAG

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
