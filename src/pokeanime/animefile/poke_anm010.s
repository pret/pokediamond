//==============================================================================
/**
 * @file	poke_anm010.s
 * @brief	
 * @author	
 * @date	
 *
 */
//==============================================================================

	.text
	
	.include	"past.h"
	.include	"past_def.h"
	
	.global		PAST_ANIME010
	
// =============================================================================
//
//
//	ヤジロベー		スロー
//
//
// =============================================================================
PAST_ANIME010:
	//50回の処理で左右0xcccの角度傾ける
	CALL_MF_CURVE_DIVTIME APPLY_SET,0,CURVE_SIN_MINUS,TARGET_ROT,0xccc,0x10000,0,50
	//傾きにあわせて少し横移動
	CALL_MF_CURVE_DIVTIME APPLY_SET,0,CURVE_SIN_MINUS,TARGET_DX,10,0x10000,0,50
	HOLD_CMD

	END_ANM
