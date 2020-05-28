//==============================================================================
/**
 * @file	we_094.s
 * @brief	サイコキネシス			94
 * @author	goto
 * @date	2005.07.13(水)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_SAIKOKINESISU
	
// =============================================================================
//
//
//	■サイコキネシス			94
//
//
// =============================================================================
WEST_SAIKOKINESISU:
	POKEOAM_RES_INIT
	POKEOAM_RES_LOAD	0,
	POKEOAM_DROP	WEDEF_DROP_E1, WEDEF_POKE_AUTO_OFF, WEDEF_POKE_CAP_ID_0, WEDEF_POKE_RES_0,

	WORK_SET		WEDEF_GP_INDEX_SPEED_Y,  8
	HAIKEI_CHG		BG_ID_094, WEDEF_HAIKEI_MODE_FADE | WEDEF_HAIKEI_SBIT_MOVE
	HAIKEI_CHG_WAIT

	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_S_X, 0, SHAKE_S_WAIT, SHAKE_S_NUM,  WE_TOOL_E1 | WE_TOOL_SSP,
	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 6,  WE_TOOL_M1, 0, 1, WE_PAL_YELLOW, 10,0

	WAIT	10
	PT_DROP_EX		WEDEF_DROP_E2, WEDEF_DROP_E2,
	
	//SE_R			SEQ_SE_DP_W109
	SE_REPEAT_R		SEQ_SE_DP_480,4,2
	FUNC_CALL		WEST_SP_WE_093, 0,0,0,0,0,0,0,0,0
	WAIT_FLAG

	POKEOAM_RES_FREE
	POKEOAM_DROP_RESET	WEDEF_POKE_CAP_ID_0
	PT_DROP_RESET_EX

	WORK_SET		WEDEF_GP_INDEX_SPEED_Y,  8
	HAIKEI_RECOVER	BG_ID_094, WEDEF_HAIKEI_RC_MODE_FADE | WEDEF_HAIKEI_SBIT_STOP	
	HAIKEI_CHG_WAIT


	SEQEND
