//==============================================================================
/**
 * @file	poke_anm_b007_1.s
 * @brief	縦横に引っ張る
 * @author	
 * @date	
 *
 */
//==============================================================================

	.text
	
	.include	"past.h"
	.include	"past_def.h"
	
	.global		PAST_ANIME_B007_1
	
// =============================================================================
//
//
//	背面	縦横に引っ張るクイック
//
//
// =============================================================================
PAST_ANIME_B007_1:
	START_LOOP	2
		//10回のループで180°（0x8000）処理
		CALL_MF_CURVE_DIVTIME APPLY_SET,0,CURVE_SIN,TARGET_RY,0x46,0x8000,0,10
		CALL_MF_CURVE_DIVTIME APPLY_SET,0,CURVE_SIN,TARGET_RX,0x46,0x8000,0,10
		//ウェイト2　6回のループで4周0x40000）分処理
		CALL_MF_CURVE_DIVTIME APPLY_SYNTHE,2,CURVE_SIN,TARGET_RY,0xe,0x40000,0,6
		CALL_MF_CURVE_DIVTIME APPLY_SYNTHE,2,CURVE_SIN,TARGET_RX,0xe,0x40000,0,6
		HOLD_CMD
	END_LOOP
	
	END_ANM
