//==============================================================================
/**
 * @file	poke_anm003.s
 * @brief	縦に引っ張る
 * @author	
 * @date	
 *
 */
//==============================================================================

	.text
	
	.include	"past.h"
	.include	"past_def.h"
	
	.global		PAST_ANIME003
	
// =============================================================================
//
//
//	縦に引っ張る
//
//
// =============================================================================
PAST_ANIME003:
	SET_DY_CORRECT		CORRECT_ON_NOT_EQ
	
	//20回のループで180°（0x8000）処理
	CALL_MF_CURVE_DIVTIME APPLY_SET,0,CURVE_SIN,TARGET_RY,0x28,0x8000,0,20
	//ウェイト5　10回のループで4周0x40000）分処理
	CALL_MF_CURVE_DIVTIME APPLY_SYNTHE,5,CURVE_SIN,TARGET_RY,0x8,0x40000,0,10
	HOLD_CMD
	
	SET_DY_CORRECT		CORRECT_OFF
	END_ANM
