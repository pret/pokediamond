//==============================================================================
/**
 * @file	we_082.s
 * @brief	ÇËÇ„Ç§ÇÃÇ¢Ç©ÇË			82
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_RYUUNOIKARI
	
// =============================================================================
//
//
//	Å°ÇËÇ„Ç§ÇÃÇ¢Ç©ÇË			82
//
//
// =============================================================================
WEST_RYUUNOIKARI:

	LOAD_PARTICLE_DROP	0,W_082_SPA
	
	//SE_FLOW_LR		SEQ_SE_DP_W082
	SE_FLOW_LR		SEQ_SE_DP_W082C

	ADD_PARTICLE 	0,W_082_082_FIREBEAM01, EMTFUNC_FIELD_OPERATOR
	EX_DATA			OPERATOR_DEF_DATA_NUM, OPERATOR_PRI_NONE, OPERATOR_TARGET_DF, OPERATOR_POS_LSP, OPERATOR_AXIS_AT, OPERATOR_FLD_NONE, OPERATOR_CAMERA_NONE

	ADD_PARTICLE 	0,W_082_082_FIREBEAM02, EMTFUNC_FIELD_OPERATOR
	EX_DATA			OPERATOR_DEF_DATA_NUM, OPERATOR_PRI_NONE, OPERATOR_TARGET_DF, OPERATOR_POS_LSP, OPERATOR_AXIS_AT, OPERATOR_FLD_NONE, OPERATOR_CAMERA_NONE

	ADD_PARTICLE 	0,W_082_082_FIREBEAM03, EMTFUNC_FIELD_OPERATOR
	EX_DATA			OPERATOR_DEF_DATA_NUM, OPERATOR_PRI_NONE, OPERATOR_TARGET_DF, OPERATOR_POS_LSP, OPERATOR_AXIS_AT, OPERATOR_FLD_NONE, OPERATOR_CAMERA_NONE

	WAIT			15

	ADD_PARTICLE 	0,W_082_082_FIREBALL01, EMTFUNC_DEFENCE_POS
	
	LOOP_LABEL		2
	
		FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_B_X, 0, SHAKE_B_WAIT, SHAKE_NUM_LONG2,  WE_TOOL_E1 | WE_TOOL_SSP,
		
		WAIT_FLAG
		
	LOOP

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
