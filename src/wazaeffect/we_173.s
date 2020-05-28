//==============================================================================
/**
 * @file	we_173.s
 * @brief	Ç¢Ç—Ç´			173
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_IBIKI
	
// =============================================================================
//
//
//	Å°Ç¢Ç—Ç´			173
//
//
// =============================================================================
WEST_IBIKI:
	
	LOAD_PARTICLE_DROP	0,W_173_SPA
	ADD_PARTICLE 	0,W_173_IBIKI, EMTFUNC_ATTACK_POS
	ADD_PARTICLE 	0,W_173_S_ZZZ01, EMTFUNC_ATTACK_POS

	FUNC_CALL		WEST_SP_BG_SHAKE, 5, 5, 0, 0, 8, 0	
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_M_X, 0, SHAKE_M_WAIT, SHAKE_M_NUM*3,  WE_TOOL_E1 | WE_TOOL_SSP,

	//SE_REPEAT_L		SEQ_SE_DP_W173,20,3
	SE_REPEAT_L		SEQ_SE_DP_W173B,20,2

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
