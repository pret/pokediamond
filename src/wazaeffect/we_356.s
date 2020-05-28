//==============================================================================
/**
 * @file	we_001.s
 * @brief	ÇÕÇΩÇ≠
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_356
	
// =============================================================================
//
//
//	Å°Ç∂Ç„Ç§ÇËÇÂÇ≠
//
//
// =============================================================================
WEST_356:
	
	LOAD_PARTICLE_DROP	0,W_356_SPA
	WAIT			10
	SE_L			SEQ_SE_DP_W356

	ADD_PARTICLE 	0,W_356_356_JURYOKU_KAITEN, EMTFUNC_FIELD_OPERATOR
	EX_DATA			OPERATOR_DEF_DATA_NUM, OPERATOR_PRI_NONE, OPERATOR_TARGET_AT, OPERATOR_POS_EP, OPERATOR_AXIS_NONE, OPERATOR_FLD_NONE, OPERATOR_CAMERA_NONE

	ADD_PARTICLE 	0,W_356_356_JURYOKU_WIND, EMTFUNC_FIELD_OPERATOR
	EX_DATA			OPERATOR_DEF_DATA_NUM, OPERATOR_PRI_NONE, OPERATOR_TARGET_NONE, OPERATOR_POS_NONE, OPERATOR_AXIS_NONE, OPERATOR_FLD_NONE, OPERATOR_CAMERA_NONE
	
	ADD_PARTICLE 	0,W_356_356_JURYOKU_KAITEN2, EMTFUNC_FIELD_OPERATOR
	EX_DATA			OPERATOR_DEF_DATA_NUM, OPERATOR_PRI_NONE, OPERATOR_TARGET_AT, OPERATOR_POS_EP, OPERATOR_AXIS_NONE, OPERATOR_FLD_NONE, OPERATOR_CAMERA_NONE

	WAIT			10
	SE_STOP			SEQ_SE_DP_W356
	SE_C			SEQ_SE_DP_205

	FUNC_CALL		WEST_SP_WE_SSP_POKE_SCALE_UPDOWN, 8, (WE_TOOL_A), 100, 100, 100, 60, 100, (30 << 16) | 1, (10 << 16) | 10
	FUNC_CALL		WEST_SP_WE_SSP_POKE_SCALE_UPDOWN, 8, (WE_TOOL_B), 100, 100, 100, 60, 100, (30 << 16) | 1, (10 << 16) | 10
	FUNC_CALL		WEST_SP_WE_SSP_POKE_SCALE_UPDOWN, 8, (WE_TOOL_C), 100, 100, 100, 60, 100, (30 << 16) | 1, (10 << 16) | 10
	FUNC_CALL		WEST_SP_WE_SSP_POKE_SCALE_UPDOWN, 8, (WE_TOOL_D), 100, 100, 100, 60, 100, (30 << 16) | 1, (10 << 16) | 10
	WAIT_FLAG

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	
	SEQEND
