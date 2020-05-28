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

	.global		WEST_355
	
// =============================================================================
//
//
//	Å°ÇÕÇÀÇ‚Ç∑Çﬂ
//
//
// =============================================================================
WEST_355:
	
	LOAD_PARTICLE_DROP	0,W_355_SPA

	SE_L			SEQ_SE_DP_210

	ADD_PARTICLE 	0,W_355_355_HANEYASU_KIRA, EMTFUNC_FIELD_OPERATOR
	EX_DATA			OPERATOR_DEF_DATA_NUM, OPERATOR_PRI_NONE, OPERATOR_TARGET_AT, OPERATOR_POS_EP, OPERATOR_AXIS_NONE, OPERATOR_FLD_NONE, OPERATOR_CAMERA_NONE

	ADD_PARTICLE 	0,W_355_355_HANEYASU_HANE, EMTFUNC_FIELD_OPERATOR
	EX_DATA			OPERATOR_DEF_DATA_NUM, OPERATOR_PRI_NONE, OPERATOR_TARGET_AT, OPERATOR_POS_EP, OPERATOR_AXIS_NONE, OPERATOR_FLD_NONE, OPERATOR_CAMERA_NONE
	
	WAIT			50
	SE_L			SEQ_SE_DP_W234
	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 6,  WE_TOOL_M1, 0, 1, WE_PAL_WHITE, WEDEF_FADE_PARAM, 0

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
