//==============================================================================
/**
 * @file	we_179.s
 * @brief	Ç´ÇµÇ©Ç¢ÇπÇ¢			179
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_KISIKAISEI
	
// =============================================================================
//
//
//	Å°Ç´ÇµÇ©Ç¢ÇπÇ¢			179
//
//
// =============================================================================
WEST_KISIKAISEI:

	LOAD_PARTICLE_DROP	0,W_179_SPA
	SE_L			SEQ_SE_DP_W197
	
	LOOP_LABEL		2
		
		FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, -2, 0, 8, WE_PAL_WHITE
		WAIT_FLAG
		FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, -2, 8, 0, WE_PAL_WHITE
		WAIT_FLAG
		
	LOOP

	SE_L			SEQ_SE_DP_W179
	ADD_PARTICLE 	0,W_179_179_KISIKAI_BALL1, EMTFUNC_FIELD_OPERATOR
	EX_DATA			OPERATOR_DEF_DATA_NUM, OPERATOR_PRI_NONE, OPERATOR_TARGET_DF, OPERATOR_POS_SP, OPERATOR_AXIS_NONE, OPERATOR_FLD_NONE, OPERATOR_CAMERA_NONE
	WAIT			40
		
	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, -2, 0, 8, WE_PAL_WHITE
	WAIT_FLAG
	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, -2, 8, 0, WE_PAL_WHITE
	WAIT_FLAG
	FUNC_CALL		WEST_SP_WE_T10,	4, 4, +WE_MOVE_X_VAL_DEF, 0, WE_TOOL_M1 | WE_TOOL_SSP
	WAIT_FLAG
	
	ADD_PARTICLE 	0,W_179_179_KISIKAI_HIT, EMTFUNC_FIELD_OPERATOR
	EX_DATA			OPERATOR_DEF_DATA_NUM, OPERATOR_PRI_NONE, OPERATOR_TARGET_DF, OPERATOR_POS_EP, OPERATOR_AXIS_NONE, OPERATOR_FLD_NONE, OPERATOR_CAMERA_NONE

	SE_R			SEQ_SE_DP_W025B
	
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, 1, 0, 1, 3,  WE_TOOL_E1 | WE_TOOL_SSP,
	FUNC_CALL		WEST_SP_WE_T10,	4, 4, -WE_MOVE_X_VAL_DEF, 0, WE_TOOL_M1 | WE_TOOL_SSP
	WAIT_FLAG

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
