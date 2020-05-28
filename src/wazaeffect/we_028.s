//==============================================================================
/**
 * @file	we_028.s
 * @brief	Ç∑Ç»Ç©ÇØ			28
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_SUNAKAKE
	
// =============================================================================
//
//
//	Å°Ç∑Ç»Ç©ÇØ			28
//
//
// =============================================================================
WEST_SUNAKAKE:
	LOAD_PARTICLE_DROP	0,W_028_SPA
	
	FUNC_CALL		WEST_SP_WE_T05, 3, 3, -WE_MOVE_X_VAL_DEF, WE_TOOL_M1 | WE_TOOL_SSP
	WAIT_FLAG
	FUNC_CALL		WEST_SP_WE_T05, 3, 3, +WE_MOVE_X_VAL_DEF, WE_TOOL_M1 | WE_TOOL_SSP

	SE_FLOW_LR		SEQ_SE_DP_W028

	ADD_PARTICLE 	0,W_028_SUNAKAKE01, EMTFUNC_FIELD_OPERATOR
	EX_DATA			OPERATOR_DEF_DATA_NUM, OPERATOR_PRI_NONE, OPERATOR_TARGET_DF, OPERATOR_POS_LSP, OPERATOR_AXIS_AT, OPERATOR_FLD_NONE, OPERATOR_CAMERA_NONE
	
	ADD_PARTICLE 	0,W_028_SUNAKAKE02, EMTFUNC_FIELD_OPERATOR
	EX_DATA			OPERATOR_DEF_DATA_NUM, OPERATOR_PRI_NONE, OPERATOR_TARGET_DF, OPERATOR_POS_LSP, OPERATOR_AXIS_AT, OPERATOR_FLD_NONE, OPERATOR_CAMERA_NONE
	
	WAIT			9
	
	ADD_PARTICLE 	0,W_028_028_SAND_HIT01, EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_028_028_SAND_HIT02, EMTFUNC_DEFENCE_POS
	WAIT_FLAG

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND

