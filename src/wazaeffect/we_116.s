//==============================================================================
/**
 * @file	we_116.s
 * @brief	Ç´Ç†Ç¢ÇæÇﬂ			116
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_KIAIDAME
	
// =============================================================================
//
//
//	Å°Ç´Ç†Ç¢ÇæÇﬂ			116
//
//
// =============================================================================
WEST_KIAIDAME:
	
	LOAD_PARTICLE_DROP	0,W_116_SPA
	ADD_PARTICLE 	0,W_116_RISE_LINE01_YEL, EMTFUNC_ATTACK_POS
	ADD_PARTICLE 	0,W_116_RISE_BALL01_YEL, EMTFUNC_ATTACK_POS
	
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_S_X, 0, SHAKE_S_WAIT, SHAKE_NUM_LONG,  WE_TOOL_M1 | WE_TOOL_SSP,
	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 6,  WE_TOOL_M1, 0, 2, WE_PAL_WHITE, 10,0

	SE_L			SEQ_SE_DP_W082
	
	WAIT_FLAG

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
