//==============================================================================
/**
 * @file	we_181.s
 * @brief	Ç±Ç»Ç‰Ç´			181
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_KONAYUKI
	
// =============================================================================
//
//
//	Å°Ç±Ç»Ç‰Ç´			181
//
//
// =============================================================================
WEST_KONAYUKI:
	
	LOAD_PARTICLE_DROP	0,W_181_SPA

	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 0, 12, WE_PAL_BLACK
	WAIT_FLAG

	ADD_PARTICLE 	0,W_181_181_KONAYUKI_BALL, EMTFUNC_FIELD_OPERATOR
	EX_DATA			OPERATOR_DEF_DATA_NUM, OPERATOR_PRI_NONE, OPERATOR_TARGET_DF, OPERATOR_POS_LSP, OPERATOR_AXIS_DF_SIDE, OPERATOR_FLD_NONE, OPERATOR_CAMERA_NONE
	
	WAIT			5
	
	ADD_PARTICLE 	0,W_181_181_KONAYUKI_ICE, EMTFUNC_DF_SIDE
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_M_X, 0, SHAKE_M_WAIT, SHAKE_M_NUM*5,  WE_TOOL_E1 | WE_TOOL_SSP,
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_M_X, 0, SHAKE_M_WAIT, SHAKE_M_NUM*5,  WE_TOOL_E2 | WE_TOOL_SSP,

	//SE_FLOW_LR	SEQ_SE_DP_W016B
	SE_REPEAT_R		SEQ_SE_DP_150,3,8
	
	WAIT			50
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_M_X, 0, SHAKE_M_WAIT, SHAKE_M_NUM*5,  WE_TOOL_E1 | WE_TOOL_SSP,
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_M_X, 0, SHAKE_M_WAIT, SHAKE_M_NUM*5,  WE_TOOL_E2 | WE_TOOL_SSP,

	SE_REPEAT_R		SEQ_SE_DP_W258,6,2

	WAIT_PARTICLE
	EXIT_PARTICLE	0,

	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 12, 0, WE_PAL_BLACK
	WAIT_FLAG

	//SE_STOP			SEQ_SE_DP_W016B
	
	SEQEND
