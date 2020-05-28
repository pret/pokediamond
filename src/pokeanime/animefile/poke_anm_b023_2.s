//==============================================================================
/**
 * @file	poke_anm_b023_2.s
 * @brief	
 * @author	
 * @date	
 *
 */
//==============================================================================

	.text
	
	.include	"past.h"
	.include	"past_def.h"
	
	.global		PAST_ANIME_B023_2
	
// =============================================================================
//
//
//	背面	2回ちぢんで　膨らむ
//
//
// =============================================================================
PAST_ANIME_B023_2:
	SET_DY_CORRECT		CORRECT_ON_MINUS
	
	//24回のループで1.5周（0x18000）分処理
	CALL_MF_CURVE_DIVTIME APPLY_SET,0,CURVE_SIN_MINUS,TARGET_RY,0x20,0x18000,0,24
	CALL_MF_CURVE_DIVTIME APPLY_SET,0,CURVE_SIN_MINUS,TARGET_RX,0x30,0x18000,0,24
	HOLD_CMD

	SET_DY_CORRECT		CORRECT_OFF

	END_ANM
