//==============================================================================
/**
 * @file	we_031.s
 * @brief	Ç›ÇæÇÍÇ√Ç´			31
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_MIDAREDUKI
	
// =============================================================================
//
//
//	Å°Ç›ÇæÇÍÇ√Ç´			31
//
//
// =============================================================================
#define WE_031_MOVE_X	(14)
#define WE_031_MOVE_Y	(8)
WEST_MIDAREDUKI:

	LOAD_PARTICLE_DROP	0,W_031_SPA

	FUNC_CALL		WEST_SP_WE_T10,	4, 2, +WE_031_MOVE_X, -WE_031_MOVE_Y, WE_TOOL_M1 | WE_TOOL_SSP
	WAIT_FLAG

	ADD_PARTICLE 	0,W_031_031_HIT_MARK,	EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_031_031_BALL_BURN,	EMTFUNC_DEFENCE_POS

	FUNC_CALL		WEST_SP_WT_SHAKE, 5, 1, 0, 1, 2,  WE_TOOL_E1 | WE_TOOL_SSP,	
	FUNC_CALL		WEST_SP_WE_T10,	4, 2, -WE_031_MOVE_X, +WE_031_MOVE_Y, WE_TOOL_M1 | WE_TOOL_SSP
	SE_REPEAT_R		SEQ_SE_DP_W030,2,2
	WAIT_FLAG

	WAIT_PARTICLE
	EXIT_PARTICLE	0,	

	SEQEND
