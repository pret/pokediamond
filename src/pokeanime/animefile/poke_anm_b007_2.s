//==============================================================================
/**
 * @file	poke_anm_b007_2.s
 * @brief	縦横に引っ張る
 * @author	
 * @date	
 *
 */
//==============================================================================

	.text
	
	.include	"past.h"
	.include	"past_def.h"
	
	.global		PAST_ANIME_B007_2
	
// =============================================================================
//
//
//	背面	縦横に引っ張るノーマル
//
//
// =============================================================================
PAST_ANIME_B007_2:
	//15回のループで180°（0x8000）処理
	CALL_MF_CURVE_DIVTIME APPLY_SET,0,CURVE_SIN,TARGET_RY,0x3c,0x8000,0,15
	CALL_MF_CURVE_DIVTIME APPLY_SET,0,CURVE_SIN,TARGET_RX,0x3c,0x8000,0,15
	//ウェイト4　7回のループで4周0x40000）分処理
	CALL_MF_CURVE_DIVTIME APPLY_SYNTHE,4,CURVE_SIN,TARGET_RY,0xc,0x40000,0,7
	CALL_MF_CURVE_DIVTIME APPLY_SYNTHE,4,CURVE_SIN,TARGET_RX,0xc,0x40000,0,7
	HOLD_CMD
	
	END_ANM
