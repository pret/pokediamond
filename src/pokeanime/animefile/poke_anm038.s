//==============================================================================
/**
 * @file	poke_anm001.s
 * @brief	
 * @author	
 * @date	
 *
 */
//==============================================================================

	.text
	
	.include	"past.h"
	.include	"past_def.h"
	
	.global		PAST_ANIME001
	
// =============================================================================
//
//
//	
//
//
// =============================================================================
PAST_ANIME001:

	SET_DY_CORRECT		CORRECT_ON_MINUS
	//24回のループで、1.5周（0x18000）を処理　
	CALL_MF_CURVE_DIVTIME	APPLY_SET,0,CURVE_SIN_MINUS,TARGET_RY,0x20,0x18000,0,24
	CALL_MF_CURVE_DIVTIME	APPLY_SET,0,CURVE_SIN,TARGET_RX,0x20,0x18000,0,24
	//8回のループで、180°（0x8000）を処理 8ウェイト
	CALL_MF_CURVE_DIVTIME	APPLY_SET,8,CURVE_SIN_MINUS,TARGET_DY,10,0x8000,0,8
	HOLD_CMD

	SET_DY_CORRECT		CORRECT_OFF

	END_ANM
