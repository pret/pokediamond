//==============================================================================
/**
 * @file	we_180.s
 * @brief	うらみ			180
 * @author	goto
 * @date	2005.07.13(水)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_URAMI
	
// =============================================================================
//
//
//	■うらみ			180
//
//
// =============================================================================
// 光る
#define URAMI_PAL_FADE_AT	(WE_TOOL_M1)
#define URAMI_PAL_FADE_NUM	(3)
#define URAMI_PAL_RGB		(WE_PAL_WHITE)
#define URAMI_PAL_FADE_MAX	(10)

WEST_URAMI:

	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 0, 12, WE_PAL_BLACK,
	WAIT_FLAG

	// ポケモンOAM準備
	POKEBG_DROP		1,	WEDEF_POKE_AUTO_OFF
	WAIT			2
	
	POKEOAM_RES_INIT
	PT_DROP_EX_2		WEDEF_DROP_E1, WEDEF_DROP_E1, WEDEF_POKE_CAP_ID_0, WEDEF_POKE_RES_0,
	
	//攻撃ポケモン光る
	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 5, URAMI_PAL_FADE_AT, 0, URAMI_PAL_FADE_NUM, URAMI_PAL_RGB, URAMI_PAL_FADE_MAX, 0,0,0

	FUNC_CALL		WEST_SP_WE_180, 0,0,0,0,0,0,0,0
	SE_L			SEQ_SE_DP_W060

	WAIT_FLAG
	
	POKEBG_DROP_RESET 0
	// ポケモンOAM破棄
	POKEOAM_RES_FREE
	PT_DROP_RESET_EX_2	WEDEF_POKE_CAP_ID_0

	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 12, 0, WE_PAL_BLACK,
	WAIT_FLAG

	SEQEND
