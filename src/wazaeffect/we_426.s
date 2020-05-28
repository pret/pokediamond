//==============================================================================
/**
 * @file	we_001.s
 * @brief	ÇÕÇΩÇ≠
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_Hataku
	
// =============================================================================
//
//
//	Å°ÇÕÇΩÇ≠
//
//
// =============================================================================
WEST_Hataku:
	LOAD_PARTICLE_DROP	0,W_426_SPA

	SE_FLOW_LR		SEQ_SE_DP_W145C
	WAIT			1

	///< BEAM
	ADD_PARTICLE 	0,W_426_426_BALL_BEAM,	EMTFUNC_ATTACK_POS
	FUNC_CALL		WEST_SP_EMIT_PARABOLIC, 6, 0, 0, 0, 0, 24, 64,
	
	ADD_PARTICLE 	0,W_426_426_BALL_BURN,	EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_426_426_HIT_MARK,	EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_426_426_BOMB,		EMTFUNC_DEFENCE_POS	
	
	WAIT			23
	SE_R			SEQ_SE_DP_W426
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_S_X, 0, SHAKE_S_WAIT, SHAKE_S_NUM,  WE_TOOL_E1 | WE_TOOL_SSP,	
	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND

