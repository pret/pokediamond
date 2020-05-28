//==============================================================================
/**
 * @file	we_051.s
 * @brief	ÇÊÇ§Ç©Ç¢Ç¶Ç´			51
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_YOUKAIEKI
	
// =============================================================================
//
//
//	Å°ÇÊÇ§Ç©Ç¢Ç¶Ç´			51
//
//
// =============================================================================
WEST_YOUKAIEKI:
	
	LOAD_PARTICLE_DROP	0,W_051_SPA
	
	SE_FLOW_LR		SEQ_SE_DP_W145C

	ADD_PARTICLE 	0, W_051_051_EKI_BEAM, EMTFUNC_ATTACK_POS
	FUNC_CALL		WEST_SP_EMIT_PARABOLIC, 6, 0, 0, 0, 0, 8, 64,
	WAIT			8
	
	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 6,  WE_TOOL_E1, 0, 1, WE_PAL_POISON, 10,0
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_S_X, 0, SHAKE_S_WAIT, SHAKE_S_NUM,  WE_TOOL_E1 | WE_TOOL_SSP,

	ADD_PARTICLE 	0, W_051_051_EKI_HIT, 	EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0, W_051_051_EKI_HIT2,	EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0, W_051_051_BALL_BURN, EMTFUNC_DEFENCE_POS
	
	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 6,  WE_TOOL_E2, 0, 1, WE_PAL_POISON, 10,0
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_S_X, 0, SHAKE_S_WAIT, SHAKE_S_NUM,  WE_TOOL_E2 | WE_TOOL_SSP,
	
	SE_R			SEQ_SE_DP_W145
	WAIT_FLAG

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
