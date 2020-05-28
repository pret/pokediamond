//==============================================================================
/**
 * @file	we_093.s
 * @brief	ねんりき			93
 * @author	goto
 * @date	2005.07.13(水)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_NENRIKI
	
// =============================================================================
//
//
//	■ねんりき			93
//
//
// =============================================================================
#define WE093_SHAKE_MOVE	(2)	// 横揺れ幅
#define WE093_SHAKE_SYNC	(1)	
#define WE093_SHAKE_ATNUM	(2)
// 光る
#define WE093_PAL_FADE_AT	(WE_TOOL_M1)
#define WE093_PAL_FADE_NUM	(1)
#define WE093_PAL_RGB		(WE_PAL_WHITE)
#define WE093_PAL_FADE_MAX	(4)

WEST_NENRIKI:
	// BGfade
	HAIKEI_CHG		BG_ID_093, WEDEF_HAIKEI_MODE_FADE | WEDEF_HAIKEI_SBIT_NONE
	HAIKEI_CHG_WAIT
	

	// ポケモンOAM準備
	POKEOAM_RES_INIT

	POKEOAM_RES_LOAD	0,

	// 描画開始
	POKEOAM_DROP		WEDEF_DROP_E1, WEDEF_POKE_AUTO_OFF, WEDEF_POKE_CAP_ID_0, WEDEF_POKE_RES_0,


	FUNC_CALL		WEST_SP_WT_SHAKE, 5, WE093_SHAKE_MOVE, 0,WE093_SHAKE_SYNC, WE093_SHAKE_ATNUM, WE_TOOL_M1 | WE_TOOL_SSP, 0, 0
	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 5, WE093_PAL_FADE_AT, 0, WE093_PAL_FADE_NUM, WE093_PAL_RGB, WE093_PAL_FADE_MAX, 0,0,0

	WAIT	10
	
	//SE_R			SEQ_SE_DP_W109
	SE_R			SEQ_SE_DP_480
	PT_DROP_EX		WEDEF_DROP_E2, WEDEF_DROP_E2,
	FUNC_CALL		WEST_SP_WE_093, 0,0,0,0,0,0,0,0,0

	WAIT_FLAG	///<TCB待ち

	// ポケモンOAM破棄
	POKEOAM_RES_FREE
	POKEOAM_DROP_RESET	WEDEF_POKE_CAP_ID_0
	PT_DROP_RESET_EX

	// BG戻す
	HAIKEI_RECOVER	BG_ID_093, WEDEF_HAIKEI_RC_MODE_FADE | WEDEF_HAIKEI_SBIT_NONE
	HAIKEI_CHG_WAIT

	SEQEND
