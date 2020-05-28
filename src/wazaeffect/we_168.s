//==============================================================================
/**
 * @file	we_168.s
 * @brief	Ç«ÇÎÇ⁄Ç§			168
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_DOROBOU
	
// =============================================================================
//
//
//	Å°Ç«ÇÎÇ⁄Ç§			168
//
//
// =============================================================================
#define MOVE_VAL_X1		(WE_MOVE_X_VAL_DEF)
WEST_DOROBOU:
	
	LOAD_PARTICLE_DROP	0,W_168_SPA

	TURN_CHK	WEST_TURN_1, WEST_TURN_2

	SEQEND

WEST_TURN_1:

	FUNC_CALL		WEST_SP_WE_T05, 3, 3, +MOVE_VAL_X1, WE_TOOL_M1 | WE_TOOL_SSP
	WAIT_FLAG
	FUNC_CALL		WEST_SP_WE_T05, 3, 3, -MOVE_VAL_X1, WE_TOOL_M1 | WE_TOOL_SSP
	
	ADD_PARTICLE 	0,W_168_168_DOROBO_HIT,		EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_168_168_DOROBO_BALL,	EMTFUNC_DEFENCE_POS

	FUNC_CALL		WEST_SP_WT_SHAKE, 5, 1, 0, 1, 2,  WE_TOOL_E1 | WE_TOOL_SSP,

	SE_R			SEQ_SE_DP_W233


	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	
	SEQEND
	
WEST_TURN_2:

	ADD_PARTICLE 	0,W_168_168_DOROBO_PRE,		EMTFUNC_ATTACK_POS
	FUNC_CALL		WEST_SP_EMIT_PARABOLIC, 7, 0, 0, 0, 0, 19, 64, 1,

	SE_FLOW_RL		SEQ_SE_DP_W039

	WAIT			20
	
	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
