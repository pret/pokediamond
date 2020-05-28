//==============================================================================
/**
 * @file	we_223.s
 * @brief	ばくれつパンチ			223
 * @author	goto
 * @date	2005.07.13(水)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_BAKURETUPANTI
	
// =============================================================================
//
//
//	■ばくれつパンチ			223
//
//
// =============================================================================
WEST_BAKURETUPANTI:

	LOAD_PARTICLE_DROP	0,W_223_SPA

	WORK_CLEAR
	WORK_SET		WEDEF_GP_INDEX_SCREEN_R, 	1
	HAIKEI_CHG		BG_ID_223, WEDEF_HAIKEI_MODE_FADE | WEDEF_HAIKEI_SBIT_NONE
//	HAIKEI_CHG_WAIT
	WAIT			5
		
	SE_R			SEQ_SE_DP_W233B

	ADD_PARTICLE 	0,W_223_223_BAKUPAN_HAND, EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_223_223_BAKUPAN_BOMB, EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_223_223_BAKUPAN_HIT,  EMTFUNC_DEFENCE_POS

	FUNC_CALL		WEST_SP_WT_SHAKE, 5, 1, 0, 1, 2,  WE_TOOL_E1 | WE_TOOL_SSP,
	
	WAIT			2
	FUNC_CALL		WEST_SP_BG_SHAKE, 5, 5, 0, 1, 6, 0
	SE_REPEAT_R		SEQ_SE_DP_W120,4,6
	WAIT			3
	
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, 4, 0, 1, 10,  WE_TOOL_E1 | WE_TOOL_SSP,

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	WORK_CLEAR
	WORK_SET		WEDEF_GP_INDEX_SCREEN_R,	1
	HAIKEI_RECOVER	BG_ID_223, WEDEF_HAIKEI_RC_MODE_FADE | WEDEF_HAIKEI_SBIT_NONE
	HAIKEI_CHG_WAIT
	
	SEQEND
