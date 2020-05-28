//==============================================================================
/**
 * @file	we_318.s
 * @brief	Ç¨ÇÒÇ¢ÇÎÇÃÇ©Ç∫			318
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_GINIRONOKAZE
	
// =============================================================================
//
//
//	Å°Ç¨ÇÒÇ¢ÇÎÇÃÇ©Ç∫			318
//
//
// =============================================================================
WEST_GINIRONOKAZE:
	LOAD_PARTICLE_DROP	0,W_318_SPA
	
	SE_C			SEQ_SE_DP_W016

	ADD_PARTICLE 	0,W_318_318_BALL_SILVER, EMTFUNC_FIELD_OPERATOR
	EX_DATA			OPERATOR_DEF_DATA_NUM, OPERATOR_PRI_NONE, OPERATOR_TARGET_DF, OPERATOR_POS_NONE, OPERATOR_AXIS_NONE, OPERATOR_FLD_NONE, OPERATOR_CAMERA_NONE

	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 0, 12, WE_PAL_BLACK
	WAIT_FLAG
	
	ADD_PARTICLE 	0,W_318_318_WIND_SILVER, EMTFUNC_FIELD_OPERATOR
	EX_DATA			OPERATOR_DEF_DATA_NUM, OPERATOR_PRI_NONE, OPERATOR_TARGET_DF, OPERATOR_POS_NONE, OPERATOR_AXIS_NONE, OPERATOR_FLD_NONE, OPERATOR_CAMERA_NONE

	SE_C			SEQ_SE_DP_W234
	WAIT_PARTICLE
	EXIT_PARTICLE	0,

	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 12, 0, WE_PAL_BLACK
	WAIT_FLAG
	SE_STOP			SEQ_SE_DP_W016
	SE_STOP			SEQ_SE_DP_W234
	
	SEQEND
