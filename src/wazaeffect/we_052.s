//==============================================================================
/**
 * @file	we_052.s
 * @brief	Ç–ÇÃÇ±			52
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_HINOKO
	
// =============================================================================
//
//
//	Å°Ç–ÇÃÇ±			52
//
//
// =============================================================================
WEST_HINOKO:

	LOAD_PARTICLE_DROP	0,W_052_SPA
	ADD_PARTICLE 	0,W_052_FIRE_HIT01_S, EMTFUNC_FIELD_OPERATOR
	EX_DATA			OPERATOR_DEF_DATA_NUM, OPERATOR_PRI_NONE, OPERATOR_TARGET_DF, OPERATOR_POS_EP, OPERATOR_AXIS_NONE, OPERATOR_FLD_NONE, OPERATOR_CAMERA_NONE
	
	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 6,  WE_TOOL_E1, 0, 1, WE_PAL_RED, 10,0
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_S_X, 0, SHAKE_S_WAIT, SHAKE_S_NUM,  WE_TOOL_E1 | WE_TOOL_SSP,

	SE_REPEAT_R		SEQ_SE_DP_W052,3,4

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND

