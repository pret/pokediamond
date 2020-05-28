//==============================================================================
/**
 * @file	we_343.s
 * @brief	ÇŸÇµÇ™ÇÈ			343
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_HOSIGARU
	
// =============================================================================
//
//
//	Å°ÇŸÇµÇ™ÇÈ			343
//
//
// =============================================================================
WEST_HOSIGARU:
	
	TURN_CHK	WEST_TURN_1, WEST_TURN_2
	
	SEQEND

WEST_TURN_1:

	LOAD_PARTICLE_DROP	0,W_343_SPA
	
	
	ADD_PARTICLE 	0,W_343_343_HART_BURN, EMTFUNC_FIELD_OPERATOR
	EX_DATA			OPERATOR_DEF_DATA_NUM, OPERATOR_PRI_NONE, OPERATOR_TARGET_DF, OPERATOR_POS_SP, OPERATOR_AXIS_NONE, OPERATOR_FLD_NONE, OPERATOR_CAMERA_NONE
	FUNC_CALL		WEST_SP_WE_175,	1, 0
	
	SE_REPEAT_L		SEQ_SE_DP_W204,2,4
	WAIT			20
	SE_REPEAT_L		SEQ_SE_DP_W204,2,4
	WAIT			10
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, 1, 0, 1, 6,  WE_TOOL_E1 | WE_TOOL_SSP,	

	SE_WAITPLAY_R	SEQ_SE_DP_350,12

	WAIT_FLAG
	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND


WEST_TURN_2:

	LOAD_PARTICLE_DROP	0,W_168_SPA

	ADD_PARTICLE 	0,W_168_168_DOROBO_PRE,		EMTFUNC_ATTACK_POS
	FUNC_CALL		WEST_SP_EMIT_PARABOLIC, 7, 0, 0, 0, 0, 19, 64, 1,

	SE_FLOW_RL		SEQ_SE_DP_W039

	WAIT			20
	
	WAIT_PARTICLE
	EXIT_PARTICLE	0,
		
	SEQEND
