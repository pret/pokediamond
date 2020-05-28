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

	.global		WEST_Hataku
	
// =============================================================================
//
//
//	Å°ÇÕÇΩÇ≠
//
//
// =============================================================================
WEST_Hataku:

	LOAD_PARTICLE_DROP	0,W_394_SPA

//FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 0, 12, WE_PAL_RED_BROWN,
//WAIT_FLAG

	ADD_PARTICLE 	0,W_394_394_ATK_BALL, EMTFUNC_FIELD_OPERATOR
	EX_DATA			OPERATOR_DEF_DATA_NUM, OPERATOR_PRI_NONE, OPERATOR_TARGET_AT, OPERATOR_POS_EP, OPERATOR_AXIS_NONE, OPERATOR_FLD_NONE, OPERATOR_CAMERA_NONE

	ADD_PARTICLE 	0,W_394_394_ATK_HIT,	EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_394_394_ATK_BLAST,	EMTFUNC_DEFENCE_POS

	SE_REPEAT_L		SEQ_SE_DP_W052,3,6

	WAIT			25

	FUNC_CALL		WEST_SP_WE_T10,	4, 2, +16, -8, WE_TOOL_M1 | WE_TOOL_SSP
	WAIT_FLAG

	FUNC_CALL		WEST_SP_WE_T10,	4, 2, -16, +8, WE_TOOL_M1 | WE_TOOL_SSP
	
	WORK_CLEAR
	WORK_SET		WEDEF_GP_INDEX_SCREEN_R, 	1
	HAIKEI_CHG		BG_ID_394, WEDEF_HAIKEI_MODE_FADE | WEDEF_HAIKEI_SBIT_NONE
	WAIT			5
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_S_X, 0, SHAKE_S_WAIT, SHAKE_S_NUM,  WE_TOOL_E1 | WE_TOOL_SSP,
	
	SE_R			SEQ_SE_DP_186
	WAIT_FLAG
	
	WAIT_PARTICLE
	EXIT_PARTICLE	0,

//FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 12, 0, WE_PAL_RED_BROWN,
//WAIT_FLAG

	WORK_CLEAR
	WORK_SET		WEDEF_GP_INDEX_SCREEN_R,	1
	HAIKEI_RECOVER	BG_ID_394, WEDEF_HAIKEI_RC_MODE_FADE | WEDEF_HAIKEI_SBIT_NONE
	HAIKEI_CHG_WAIT	

	SEQEND

