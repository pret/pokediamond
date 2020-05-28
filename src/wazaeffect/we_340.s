//==============================================================================
/**
 * @file	we_340.s
 * @brief	Ç∆Ç—ÇÕÇÀÇÈ			340
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_TOBIHANERU
	
// =============================================================================
//
//
//	Å°Ç∆Ç—ÇÕÇÀÇÈ			340
//
//
// =============================================================================
WEST_TOBIHANERU:
	
	LOAD_PARTICLE_DROP	0,W_340_SPA
	
	TURN_CHK	WEST_340_TURN_1, WEST_340_TURN_2
	
	SEQEND


WEST_340_TURN_1:

	ADD_PARTICLE 	0,W_340_340_BALL_BIG1, EMTFUNC_ATTACK_POS
	ADD_PARTICLE 	0,W_340_340_BALL_UP, EMTFUNC_ATTACK_POS	

	WAIT			8
	SE_L			SEQ_SE_DP_W100

	FUNC_CALL		WEST_SP_WE_SSP_POKE_VANISH, 2, WE_TOOL_M1, 1

	WAIT_FLAG

	WAIT_PARTICLE
	EXIT_PARTICLE	0,	

	SEQEND


WEST_340_TURN_2:

	ADD_PARTICLE 	0,W_340_340_BALL_DOWN, EMTFUNC_DEFENCE_POS
	
	WAIT			10
	SE_R			SEQ_SE_DP_W029
	WAIT			10
	SE_R			SEQ_SE_DP_143

	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_M_X, 0, SHAKE_M_WAIT, SHAKE_M_NUM,  WE_TOOL_E1 | WE_TOOL_SSP,

	FUNC_CALL		WEST_SP_WE_SSP_POKE_VANISH, 2, WE_TOOL_M1, 0

	WAIT_FLAG
	WAIT_PARTICLE
	EXIT_PARTICLE	0,

	SEQEND
