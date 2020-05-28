//==============================================================================
/**
 * @file	we_029.s
 * @brief	Ç∏Ç¬Ç´			29
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_ZUTUKI
	
// =============================================================================
//
//
//	Å°Ç∏Ç¬Ç´			29
//
//
// =============================================================================
#define WE_029_MOVE_X	(14)
#define WE_029_MOVE_Y	(8)

WEST_ZUTUKI:

	LOAD_PARTICLE_DROP	0,W_029_SPA

	SE_L			SEQ_SE_DP_W029
	//SE_R			SEQ_SE_DP_143
	SE_R			SEQ_SE_DP_030

	FUNC_CALL		WEST_SP_WE_T10,	4, 2, +WE_029_MOVE_X, -WE_029_MOVE_Y, WE_TOOL_M1 | WE_TOOL_SSP
	WAIT_FLAG

	ADD_PARTICLE 	0,W_029_029_HIT_MARK,	EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_029_029_BALL_BURN,	EMTFUNC_DEFENCE_POS

	FUNC_CALL		WEST_SP_WT_SHAKE, 5, 1, 0, 1, 2,  WE_TOOL_E1 | WE_TOOL_SSP,	
	FUNC_CALL		WEST_SP_WE_T10,	4, 2, -WE_029_MOVE_X, +WE_029_MOVE_Y, WE_TOOL_M1 | WE_TOOL_SSP
	WAIT_FLAG

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
