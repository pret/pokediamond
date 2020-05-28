//==============================================================================
/**
 * @file	we_192.s
 * @brief	Ç≈ÇÒÇ∂ÇŸÇ§			192
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_DENZIHOU
	
// =============================================================================
//
//
//	Å°Ç≈ÇÒÇ∂ÇŸÇ§			192
//
//
// =============================================================================
WEST_DENZIHOU:

	LOAD_PARTICLE_DROP	0,W_192_SPA

	WORK_CLEAR
	WORK_SET		WEDEF_GP_INDEX_SCREEN_R, 1
	HAIKEI_CHG		BG_ID_192, WEDEF_HAIKEI_MODE_FADE | WEDEF_HAIKEI_SBIT_NONE
	WAIT			5
	
	SE_REPEAT_C		SEQ_SE_DP_W086,2,3	
	FUNC_CALL		WEST_SP_BG_SHAKE, 5, 8, 8, 0, 20, 0

	ADD_PARTICLE 	0,W_192_192_DENJIHOU_BALL,  EMTFUNC_FIELD_OPERATOR
	EX_DATA			OPERATOR_DEF_DATA_NUM, OPERATOR_PRI_NONE, OPERATOR_TARGET_DF, OPERATOR_POS_LSP, OPERATOR_AXIS_AT, OPERATOR_FLD_NONE, OPERATOR_CAMERA_NONE
	
	ADD_PARTICLE 	0,W_192_192_DENJIHOU_HIT1, EMTFUNC_DEFENCE_POS
	
	WAIT			5
	ADD_PARTICLE 	0,W_192_192_DENJIHOU_HIT2, EMTFUNC_DEFENCE_POS
	
	WAIT			10	
	SE_R			SEQ_SE_DP_W085C
	SE_WAITPLAY_R	SEQ_SE_DP_W085B,25
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, 4, 0, 1, 4,  WE_TOOL_E1 | WE_TOOL_SSP,
	
	WAIT_FLAG

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	WORK_SET		WEDEF_GP_INDEX_SCREEN_R, 1
	HAIKEI_RECOVER	BG_ID_192, WEDEF_HAIKEI_RC_MODE_FADE | WEDEF_HAIKEI_SBIT_NONE
	HAIKEI_CHG_WAIT
	SEQEND
