//==============================================================================
/**
 * @file	we_261.s
 * @brief	Ç®Ç…Ç—			261
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_ONIBI
	
// =============================================================================
//
//
//	Å°Ç®Ç…Ç—			261
//
//
// =============================================================================
WEST_ONIBI:

	LOAD_PARTICLE_DROP	0,W_261_SPA
	
	SE_FLOW_LR		SEQ_SE_DP_W052

	ADD_PARTICLE 	0,W_261_261_ONIBI_BEAM, EMTFUNC_FIELD_OPERATOR
	EX_DATA			OPERATOR_DEF_DATA_NUM, OPERATOR_PRI_NONE, OPERATOR_TARGET_DF,	\
					OPERATOR_POS_LSP, OPERATOR_AXIS_AT, OPERATOR_FLD_MAGNET_POS, OPERATOR_CAMERA_NONE
	EX_DATA			OPERATOR_FLD_EX_DATA_NUM, OPERATOR_FLD_DF, OPERATOR_EX_REVERCE_ON, 0,0,0
	
	WAIT			30

	ADD_PARTICLE 	0,W_261_261_ONIBI_HIT, EMTFUNC_DEFENCE_POS

	SE_R			SEQ_SE_DP_W172B
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_M_X, 0, SHAKE_S_WAIT, SHAKE_S_NUM,  WE_TOOL_E1 | WE_TOOL_SSP,

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
