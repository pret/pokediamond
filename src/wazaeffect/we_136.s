//==============================================================================
/**
 * @file	we_136.s
 * @brief	Ç∆Ç—Ç–Ç¥Ç∞ÇË			136
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_TOBIHIZAGERI
	
// =============================================================================
//
//
//	Å°Ç∆Ç—Ç–Ç¥Ç∞ÇË			136
//
//
// =============================================================================
WEST_TOBIHIZAGERI:

	LOAD_PARTICLE_DROP	0,W_136_SPA
	
	SE_L			SEQ_SE_DP_W026
	
	FUNC_CALL		WEST_SP_WE_T05, 3, 3, +WE_MOVE_X_VAL_DEF, WE_TOOL_M1 | WE_TOOL_SSP
	WAIT_FLAG
	
//	ADD_PARTICLE 	0,W_136_136_TOBIHIZA_FOOT, EMTFUNC_FIELD_OPERATOR
//	EX_DATA			OPERATOR_DEF_DATA_NUM, OPERATOR_PRI_NONE, OPERATOR_TARGET_DF, OPERATOR_POS_LSP, OPERATOR_AXIS_AT, OPERATOR_FLD_NONE, OPERATOR_CAMERA_NONE
	FUNC_CALL		WEST_SP_WE_T05, 3, 3, -WE_MOVE_X_VAL_DEF, WE_TOOL_M1 | WE_TOOL_SSP

	SE_R			SEQ_SE_DP_W233B

	FUNC_CALL		WEST_SP_WE_T05, 3, 3, -WE_MOVE_X_VAL_DEF, WE_TOOL_E1 | WE_TOOL_SSP
	ADD_PARTICLE 	0,W_136_136_TOBIHIZA_HIT, EMTFUNC_DEFENCE_POS
	WAIT_FLAG
	FUNC_CALL		WEST_SP_WE_T05, 3, 3, +WE_MOVE_X_VAL_DEF, WE_TOOL_E1 | WE_TOOL_SSP
	WAIT_FLAG

	SE_R			SEQ_SE_DP_BASI

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
