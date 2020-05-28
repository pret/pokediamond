//==============================================================================
/**
 * @file	we_053.s
 * @brief	Ç©Ç¶ÇÒÇŸÇ§ÇµÇ·			53
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_KAENHOUSYA
	
// =============================================================================
//
//
//	Å°Ç©Ç¶ÇÒÇŸÇ§ÇµÇ·			53
//
//
// =============================================================================
#define WE_053_SHAKE_NUM	(SHAKE_M_NUM * 7)
WEST_KAENHOUSYA:

	LOAD_PARTICLE_DROP	0,W_053_SPA
	
	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 0, 12, WE_PAL_RED_BROWN,
	WAIT_FLAG

	ADD_PARTICLE 	0,W_053_FIRE_BREATH01, EMTFUNC_FIELD_OPERATOR
	EX_DATA			OPERATOR_DEF_DATA_NUM, OPERATOR_PRI_NONE, OPERATOR_TARGET_DF, OPERATOR_POS_LSP, OPERATOR_AXIS_AT, OPERATOR_FLD_NONE, OPERATOR_CAMERA_NONE

//	KEY_WAIT

	SE_R			SEQ_SE_DP_W053

	WAIT			50
	ADD_PARTICLE 	0,W_053_053_FIRE_HIT, EMTFUNC_DEFENCE_POS	
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_M_X, 0, SHAKE_M_WAIT, WE_053_SHAKE_NUM,  WE_TOOL_M1 | WE_TOOL_SSP,
	
	WAIT			3
	
	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 6,  WE_TOOL_E1, 0, 1, WE_PAL_RED, 10, 25
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_M_X, 0, SHAKE_M_WAIT, WE_053_SHAKE_NUM,  WE_TOOL_E1 | WE_TOOL_SSP,
	
	WAIT_PARTICLE
	EXIT_PARTICLE	0,

	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 12, 0, WE_PAL_RED_BROWN,
	WAIT_FLAG
	
	SEQEND

