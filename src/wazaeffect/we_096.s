//==============================================================================
/**
 * @file	we_096.s
 * @brief	ヨガのポーズ			96
 * @author	goto
 * @date	2005.07.13(水)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_YOGANOPOOZU
	
// =============================================================================
//
//
//	■ヨガのポーズ			96
//
//
// =============================================================================
WEST_YOGANOPOOZU:

	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 0, 12, WE_PAL_BLACK,
	WAIT_FLAG
	
	SE_L			SEQ_SE_DP_W029
	FUNC_CALL		WEST_SP_WE_096, 0,0,0,0,0,0,0,0,0
	
	SE_WAITPLAY_L	SEQ_SE_DP_W036,10
	WAIT_FLAG

	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 12, 0, WE_PAL_BLACK,
	WAIT_FLAG
	
	SEQEND
