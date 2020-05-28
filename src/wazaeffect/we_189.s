//==============================================================================
/**
 * @file	we_189.s
 * @brief	�ǂ납��			189
 * @author	goto
 * @date	2005.07.13(��)
 *
 * �����ɐF�X�ȉ�����������Ă��悢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_DOROKAKE
	
// =============================================================================
//
//
//	���ǂ납��			189
//
//
// =============================================================================
WEST_DOROKAKE:
	
	LOAD_PARTICLE_DROP	0,W_189_SPA
	ADD_PARTICLE 	0,W_189_189_DOROKAKE_KEMURI, EMTFUNC_FIELD_OPERATOR
	EX_DATA			OPERATOR_DEF_DATA_NUM, OPERATOR_PRI_NONE, OPERATOR_TARGET_DF, OPERATOR_POS_LSP, OPERATOR_AXIS_AT, OPERATOR_FLD_NONE, OPERATOR_CAMERA_NONE
	
	SE_REPEAT_C		SEQ_SE_DP_W028,4,6

	WAIT			20
	
	ADD_PARTICLE 	0,W_189_189_DOROKAKE_HIT, EMTFUNC_DEFENCE_POS
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_M_X, 0, SHAKE_M_WAIT, SHAKE_M_NUM,  WE_TOOL_E1 | WE_TOOL_SSP,
	
	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
