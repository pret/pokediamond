//==============================================================================
/**
 * @file	we_025.s
 * @brief	メガトンキック			25
 * @author	goto
 * @date	2005.07.13(水)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_MEGATONKIKKU
	
// =============================================================================
//
//
//	■メガトンキック			25
//
//
// =============================================================================
WEST_MEGATONKIKKU:
//	FUNC_CALL WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 0, 12, WE_PAL_BLACK,
			
	LOAD_PARTICLE_DROP	0,W_025_SPA

	WORK_CLEAR
	WORK_SET		WEDEF_GP_INDEX_SCREEN_R, 	1
	HAIKEI_CHG		BG_ID_025, WEDEF_HAIKEI_MODE_FADE | WEDEF_HAIKEI_SBIT_NONE
//	HAIKEI_CHG_WAIT
	WAIT			5

	ADD_PARTICLE 	0,W_025_025_MEGA_KICK01, EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_025_025_MEGA_KICK02, EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_025_025_HIT_MARK,	 EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_025_B_BURN_RED2,	 EMTFUNC_DEFENCE_POS

	//SE_R			SEQ_SE_DP_BASI
	//SE_WAITPLAY_R	SEQ_SE_DP_030,5
	SE_WAITPLAY_R	SEQ_SE_DP_140,1

	FUNC_CALL		WEST_SP_WT_SHAKE, 5, 4, 0, 1, 2,  WE_TOOL_E1 | WE_TOOL_SSP
	
	WAIT			1
	FUNC_CALL		WEST_SP_BG_SHAKE, 5, 5, 0, 1, 3, 0
	WAIT_FLAG

	WAIT_PARTICLE
	EXIT_PARTICLE	0,

	WORK_CLEAR
	WORK_SET		WEDEF_GP_INDEX_SCREEN_R,	1
	HAIKEI_RECOVER	BG_ID_025, WEDEF_HAIKEI_RC_MODE_FADE | WEDEF_HAIKEI_SBIT_NONE
	HAIKEI_CHG_WAIT
	
//	FUNC_CALL WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 12, 0, WE_PAL_BLACK,
//	WAIT_FLAG
	SEQEND
