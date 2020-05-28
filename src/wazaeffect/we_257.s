//==============================================================================
/**
 * @file	we_257.s
 * @brief	ÇÀÇ¡Ç’Ç§			257
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_NEPPUU
	
// =============================================================================
//
//
//	Å°ÇÀÇ¡Ç’Ç§			257
//
//
// =============================================================================
WEST_NEPPUU:
	
	LOAD_PARTICLE_DROP	0,W_257_SPA
	
	CONTEST_JP	CONTEST
	
	SIDE_JP		0, WEST_257_SIDE_MINE, WEST_257_SIDE_ENEMY
	
	SEQEND

CONTEST:

	ADD_PARTICLE 	0,W_257_257_HOT_WIND, EMTFUNC_DUMMY
	SE_FLOW_LR		SEQ_SE_DP_W257
	
	WAIT_FLAG
	
	WAIT			35
	
	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
	
WEST_257_SIDE_MINE:
	ADD_PARTICLE 	0,W_257_257_HOT_WIND, EMTFUNC_DUMMY
	SE_FLOW_LR		SEQ_SE_DP_W257
	
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, 3, 0, 1, 3,  WE_TOOL_E1 | WE_TOOL_SSP
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, 3, 0, 1, 3,  WE_TOOL_E2 | WE_TOOL_SSP
	
	WAIT_FLAG
		
	FUNC_CALL		WEST_SP_WE_T05, 3, 4, -20, WE_TOOL_E1 | WE_TOOL_SSP
	FUNC_CALL		WEST_SP_WE_T05, 3, 4, -20, WE_TOOL_E2 | WE_TOOL_SSP
	WAIT_FLAG
	
	WAIT			35
	
	FUNC_CALL		WEST_SP_WE_T05, 3, 5, +20, WE_TOOL_E1 | WE_TOOL_SSP
	FUNC_CALL		WEST_SP_WE_T05, 3, 5, +20, WE_TOOL_E2 | WE_TOOL_SSP
	WAIT_FLAG

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
	
WEST_257_SIDE_ENEMY:
	ADD_PARTICLE 	0,W_257_257_HOT_WIND02, EMTFUNC_DUMMY
	SE_FLOW_LR		SEQ_SE_DP_W257
	
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, 3, 0, 1, 3,  WE_TOOL_E1 | WE_TOOL_SSP
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, 3, 0, 1, 3,  WE_TOOL_E2 | WE_TOOL_SSP
	
	WAIT_FLAG
		
	FUNC_CALL		WEST_SP_WE_T05, 3, 4, -20, WE_TOOL_E1 | WE_TOOL_SSP
	FUNC_CALL		WEST_SP_WE_T05, 3, 4, -20, WE_TOOL_E2 | WE_TOOL_SSP
	WAIT_FLAG
	
	WAIT			35
	
	FUNC_CALL		WEST_SP_WE_T05, 3, 5, +20, WE_TOOL_E1 | WE_TOOL_SSP
	FUNC_CALL		WEST_SP_WE_T05, 3, 5, +20, WE_TOOL_E2 | WE_TOOL_SSP
	WAIT_FLAG

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
