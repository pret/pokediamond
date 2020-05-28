//==============================================================================
/**
 * @file	we_101.s
 * @brief	ナイトヘッド			101
 * @author	goto
 * @date	2005.07.13(水)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_NAITOHEDDO
	
// =============================================================================
//
//
//	■ナイトヘッド			101
//
//
// =============================================================================
WEST_NAITOHEDDO:

	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 0, 12, WE_PAL_BLACK,
	WAIT_FLAG

	// ポケモンOAM準備
	POKEOAM_RES_INIT

	POKEOAM_RES_LOAD	0,

	// 描画開始
	POKEOAM_DROP		WEDEF_DROP_M1, WEDEF_POKE_AUTO_OFF, WEDEF_POKE_CAP_ID_0, WEDEF_POKE_RES_0,

	PT_DROP_EX_2		WEDEF_DROP_M2, WEDEF_DROP_M2, WEDEF_POKE_CAP_ID_1, WEDEF_POKE_RES_1,

	FUNC_CALL		WEST_SP_WE_101AT, 0,0,0,0,0,0,0,0,0
	SE_L			SEQ_SE_DP_W109

	WAIT	16	
	SE_R			SEQ_SE_DP_201
	
	FUNC_CALL		WEST_SP_WE_101DF, 0,0,0,0,0,0,0,0,0

	WAIT_FLAG	///<TCB待ち

	// ポケモンOAM破棄
	POKEOAM_RES_FREE
	POKEOAM_DROP_RESET	WEDEF_POKE_CAP_ID_0
	PT_DROP_RESET_EX_2	WEDEF_POKE_CAP_ID_1

	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 12, 0, WE_PAL_BLACK,
	WAIT_FLAG
	
	SEQEND
