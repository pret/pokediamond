//==============================================================================
/**
 * @file	poke_anm021.s
 * @brief	
 * @author	
 * @date	
 *
 */
//==============================================================================

	.text
	
	.include	"past.h"
	.include	"past_def.h"
	
	.global		PAST_ANIME021
	
// =============================================================================
//
//
//	ボワボワ
//
//
// =============================================================================
PAST_ANIME021:
	//20回のループで2周（0x20000）分処理
	CALL_MF_CURVE_DIVTIME APPLY_SET,0,CURVE_COS_MINUS,TARGET_RY,0x20,0x20000,0,20
	CALL_MF_CURVE_DIVTIME APPLY_SET,0,CURVE_SIN_MINUS,TARGET_RX,0x20,0x20000,0,20
	HOLD_CMD

	END_ANM
