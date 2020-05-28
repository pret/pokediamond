//==============================================================================
/**
 * @file	we_140.s
 * @brief	ÇΩÇ‹Ç»Ç∞			140
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_TAMANAGE
	
// =============================================================================
//
//
//	Å°ÇΩÇ‹Ç»Ç∞			140
//
//
// =============================================================================
WEST_TAMANAGE:
	
	LOAD_PARTICLE_DROP	0,W_140_SPA

	ADD_PARTICLE_EMIT_SET 	0,1,W_140_140_TAMANAGE_BALL1, EMTFUNC_ATTACK_POS
	FUNC_CALL		WEST_SP_EMIT_PARABOLIC, 6, 1, 0, 0, 0, 15, 64,
	
	SE_FLOW_LR		SEQ_SE_DP_W207
	
	ADD_PARTICLE 	0,W_140_140_TAMANAGE_BALL2, EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_140_140_TAMANAGE_KEMURI, EMTFUNC_DEFENCE_POS
	
	WAIT			15
	FUNC_CALL		WEST_SP_BG_SHAKE, 5, 0, 5, 1, 3, 0
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_M_X, 0, SHAKE_M_WAIT, SHAKE_M_NUM,  WE_TOOL_E1 | WE_TOOL_SSP,
	SE_R			SEQ_SE_DP_W088
	
	WAIT_FLAG


	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
