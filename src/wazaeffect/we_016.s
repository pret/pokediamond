//==============================================================================
/**
 * @file	we_016.s
 * @brief	Ç©Ç∫Ç®Ç±Çµ			16
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_KAZEOKOSI
	
// =============================================================================
//
//
//	Å°Ç©Ç∫Ç®Ç±Çµ			16
//
//
// =============================================================================
WEST_KAZEOKOSI:
	
	LOAD_PARTICLE_DROP	0,W_016_SPA
	CAMERA_CHG		0,WE_CAMERA_TYPE_PERSPECTIV
	ADD_PARTICLE 	0,W_016_016_WIND_UP1, EMTFUNC_FIELD_OPERATOR
	EX_DATA			OPERATOR_DEF_DATA_NUM, OPERATOR_PRI_NONE, OPERATOR_TARGET_NONE, OPERATOR_POS_NONE, OPERATOR_AXIS_NONE, OPERATOR_FLD_NONE, OPERATOR_CAMERA_DF

	ADD_PARTICLE 	0,W_016_016_WIND_UP2, EMTFUNC_FIELD_OPERATOR
	EX_DATA			OPERATOR_DEF_DATA_NUM, OPERATOR_PRI_NONE, OPERATOR_TARGET_NONE, OPERATOR_POS_NONE, OPERATOR_AXIS_NONE, OPERATOR_FLD_NONE, OPERATOR_CAMERA_DF

	WAIT			5
	SE_R			SEQ_SE_DP_W239
	WAIT			15
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, 3, 0, 1, 15,  WE_TOOL_E1 | WE_TOOL_SSP

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	WAIT_FLAG
	
	SEQEND
