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

	.global		WEST_368
	
// =============================================================================
//
//
//	Å°ÇÕÇΩÇ≠
//
//
// =============================================================================
WEST_368:

	LOAD_PARTICLE_DROP	0,W_368_SPA
	
	
	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 0, 12, WE_PAL_BLACK,
	WAIT_FLAG

	SE_REPEAT_C		SEQ_SE_DP_W368,3,8
	
	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 6,  WE_TOOL_M1, 0, 1, WE_PAL_WHITE, WEDEF_FADE_PARAM,0
	ADD_PARTICLE 	0,W_368_368_MATELBST_HIZASHI1,	EMTFUNC_ATTACK_POS
	ADD_PARTICLE 	0,W_368_368_MATELBST_HIZASHI2,	EMTFUNC_ATTACK_POS	
	ADD_PARTICLE 	0,W_368_368_MATELBST_BALL,		EMTFUNC_ATTACK_POS
	
	WAIT			30
	SE_FLOW_LR		SEQ_SE_DP_W209
	
	ADD_PARTICLE 	0,W_368_368_MATELBST_HIT,		EMTFUNC_DEFENCE_POS
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_M_X, 0, SHAKE_M_WAIT, SHAKE_M_NUM*3,  WE_TOOL_E1 | WE_TOOL_SSP,
	
	WAIT_PARTICLE
	EXIT_PARTICLE	0,
		
	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 12, 0, WE_PAL_BLACK,
	WAIT_FLAG
	
	SEQEND

