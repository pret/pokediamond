//==============================================================================
/**
 * @file	we_214.s
 * @brief	ÇÀÇ≤Ç∆			214
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_NEGOTO
	
// =============================================================================
//
//
//	Å°ÇÀÇ≤Ç∆			214
//
//
// =============================================================================
WEST_NEGOTO:

	LOAD_PARTICLE_DROP	0,W_214_SPA
	
	ADD_PARTICLE 	0,W_214_214_NEGOTO_ZZZ1, EMTFUNC_FIELD_OPERATOR
	EX_DATA			OPERATOR_DEF_DATA_NUM, OPERATOR_PRI_NONE, OPERATOR_TARGET_DF, OPERATOR_POS_SP, OPERATOR_AXIS_AT, OPERATOR_FLD_NONE, OPERATOR_CAMERA_NONE

	ADD_PARTICLE 	0,W_214_214_NEGOTO_ZZZ2, EMTFUNC_FIELD_OPERATOR
	EX_DATA			OPERATOR_DEF_DATA_NUM, OPERATOR_PRI_NONE, OPERATOR_TARGET_DF, OPERATOR_POS_SP, OPERATOR_AXIS_AT, OPERATOR_FLD_NONE, OPERATOR_CAMERA_NONE

	//SE_REPEAT_L		SEQ_SE_DP_W173,8,3
	//SE_REPEAT_L		SEQ_SE_DP_W173B,8,3
	SE_REPEAT_L		SEQ_SE_DP_W173B,8,2

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
