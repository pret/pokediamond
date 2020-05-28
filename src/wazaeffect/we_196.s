//==============================================================================
/**
 * @file	we_196.s
 * @brief	Ç±Ç≤Ç¶ÇÈÇ©Ç∫			196
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_KOGOERUKAZE
	
// =============================================================================
//
//
//	Å°Ç±Ç≤Ç¶ÇÈÇ©Ç∫			196
//
//
// =============================================================================
WEST_KOGOERUKAZE:

FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 0, 12, WE_PAL_BLACK,
WAIT_FLAG
	
	LOAD_PARTICLE_DROP	0,W_196_SPA
	ADD_PARTICLE 	0,W_196_196_KOGOERU_ICE1, EMTFUNC_FIELD_OPERATOR
	EX_DATA			OPERATOR_DEF_DATA_NUM, OPERATOR_PRI_NONE, OPERATOR_TARGET_DF, OPERATOR_POS_LSP, OPERATOR_AXIS_DF_SIDE, OPERATOR_FLD_NONE, OPERATOR_CAMERA_NONE	

	SE_REPEAT_C		SEQ_SE_DP_W016B,2,14
	
	ADD_PARTICLE 	0,W_196_196_KOGOERU_ICE2, EMTFUNC_FIELD_OPERATOR
	EX_DATA			OPERATOR_DEF_DATA_NUM, OPERATOR_PRI_NONE, OPERATOR_TARGET_DF, OPERATOR_POS_LSP, OPERATOR_AXIS_DF_SIDE, OPERATOR_FLD_NONE, OPERATOR_CAMERA_NONE	
	
	WAIT			20
	
	ADD_PARTICLE 	0,W_196_196_KOGOERU_ICEHIT, EMTFUNC_DF_SIDE
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_M_X, 0, SHAKE_M_WAIT, SHAKE_M_NUM*5,  WE_TOOL_E1 | WE_TOOL_SSP,
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_M_X, 0, SHAKE_M_WAIT, SHAKE_M_NUM*5,  WE_TOOL_E2 | WE_TOOL_SSP,

	WAIT			10	
	SE_REPEAT_R		SEQ_SE_DP_W258, 4, 4
	WAIT			50	

	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 12, 0, WE_PAL_BLACK,
	WAIT_FLAG	

	WAIT_PARTICLE
	EXIT_PARTICLE	0,

	SE_STOP			SEQ_SE_DP_W016B

	SEQEND
