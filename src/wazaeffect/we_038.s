//==============================================================================
/**
 * @file	we_038.s
 * @brief	すてみタックル			38
 * @author	goto
 * @date	2005.07.13(水)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_SUTEMITAKKURU
	
// =============================================================================
//
//
//	■すてみタックル			38
//
//
// =============================================================================
WEST_SUTEMITAKKURU:

	LOAD_PARTICLE_DROP	0,W_038_SPA
		
//	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 6,  WE_TOOL_M1, 0, 2, WE_PAL_WHITE, 10, 0

	SE_L			SEQ_SE_DP_W025
	SE_WAITPLAY_R	SEQ_SE_DP_131,10
	WAIT_FLAG
	
	
	FUNC_CALL		WEST_SP_WE_KAITEN, 3, WE_TOOL_M1, 1, 10
	WAIT_FLAG
	
	WORK_CLEAR
	WORK_SET		WEDEF_GP_INDEX_SCREEN_R, 1
	HAIKEI_CHG		BG_ID_038, WEDEF_HAIKEI_MODE_FADE | WEDEF_HAIKEI_SBIT_NONE
	
	FUNC_CALL		WEST_SP_WE_KAITEN, 3, WE_TOOL_M1, 1, 10
	WAIT_FLAG
	
	FUNC_CALL		WEST_SP_WE_T10,	4, 2, +14, -8, WE_TOOL_M1 | WE_TOOL_SSP
	
	ADD_PARTICLE 	0,W_038_038_HIT_MARK1,	EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_038_038_HIT_MARK2,	EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_038_038_HIT_MARK3,	EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_038_038_HIT_MARK4,	EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_038_038_HIT_MARK5,	EMTFUNC_DEFENCE_POS
	
	SE_R			SEQ_SE_DP_140
	WAIT			2
	
	FUNC_CALL		WEST_SP_WE_T10,	4, 2, -18, +4, WE_TOOL_E1 | WE_TOOL_SSP
	FUNC_CALL		WEST_SP_WE_T10,	4, 2, -14, +8, WE_TOOL_M1 | WE_TOOL_SSP
	FUNC_CALL		WEST_SP_BG_SHAKE, 5, 0, 5, 1, 3, 0
	WAIT			2
	
	FUNC_CALL		WEST_SP_WE_T10,	4, 4, +18, -4, WE_TOOL_E1 | WE_TOOL_SSP
	WAIT_FLAG

	WAIT_PARTICLE
	EXIT_PARTICLE	0,

	WORK_CLEAR
	WORK_SET		WEDEF_GP_INDEX_SCREEN_R, 1
	HAIKEI_RECOVER	BG_ID_038, WEDEF_HAIKEI_RC_MODE_FADE | WEDEF_HAIKEI_SBIT_NONE
	HAIKEI_CHG_WAIT
	
	SEQEND
