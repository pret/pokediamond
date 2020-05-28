//==============================================================================
/**
 * @file	we_099.s
 * @brief	Ç¢Ç©ÇË			99
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_IKARI
	
// =============================================================================
//
//
//	Å°Ç¢Ç©ÇË			99
//
//
// =============================================================================
WEST_IKARI:

	LOAD_PARTICLE_DROP	0,W_099_SPA

	SE_L			SEQ_SE_DP_131
	SE_WAITPLAY_R	SEQ_SE_DP_030,50
	
	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 6,  WE_TOOL_M1, 0, 2, WE_PAL_RED, 10, 0
	WAIT_FLAG

	FUNC_CALL		WEST_SP_WE_T05, 3, 3, +WE_MOVE_X_VAL_DEF, WE_TOOL_M1 | WE_TOOL_SSP
	WAIT_FLAG
	
	FUNC_CALL		WEST_SP_WE_T05, 3, 3, -WE_MOVE_X_VAL_DEF, WE_TOOL_M1 | WE_TOOL_SSP
	ADD_PARTICLE 	0,W_099_099_HIT_MARK,	EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_099_099_BALL_BURN,	EMTFUNC_DEFENCE_POS
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_S_X, 0, SHAKE_S_WAIT, SHAKE_S_NUM,  WE_TOOL_E1 | WE_TOOL_SSP,

	WAIT_FLAG
	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
