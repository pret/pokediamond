//==============================================================================
/**
 * @file	we_026.s
 * @brief	Ç∆Ç—Ç∞ÇË			26
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_TOBIGERI
	
// =============================================================================
//
//
//	Å°Ç∆Ç—Ç∞ÇË			26
//
//
// =============================================================================
WEST_TOBIGERI:
	
	LOAD_PARTICLE_DROP	0,W_026_SPA

	FUNC_CALL		WEST_SP_WE_T05, 3, 3, +WE_MOVE_X_VAL_DEF, WE_TOOL_M1 | WE_TOOL_SSP
	ADD_PARTICLE 	0,W_026_FOOT_BEAM01, EMTFUNC_FIELD_OPERATOR
	EX_DATA			OPERATOR_DEF_DATA_NUM, OPERATOR_PRI_NONE, OPERATOR_TARGET_DF,	\
					OPERATOR_POS_LSP, OPERATOR_AXIS_AT, OPERATOR_FLD_CONVERGENCE_POS, OPERATOR_CAMERA_NONE
	EX_DATA			OPERATOR_FLD_EX_DATA_NUM, OPERATOR_FLD_DF, OPERATOR_EX_REVERCE_ON, 0,0,0
	WAIT_FLAG	
	FUNC_CALL		WEST_SP_WE_T05, 3, 3, -WE_MOVE_X_VAL_DEF, WE_TOOL_M1 | WE_TOOL_SSP
	SE_R			SEQ_SE_DP_131
	WAIT_FLAG	
	WAIT			20
	
	ADD_PARTICLE 	0,W_026_001_HIT_MARK,	EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_026_001_BALL_BURN,	EMTFUNC_DEFENCE_POS
	
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, 1, 0, 1, 2,  WE_TOOL_E1 | WE_TOOL_SSP,
	SE_R			SEQ_SE_DP_030

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
