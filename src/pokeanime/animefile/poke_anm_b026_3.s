//==============================================================================
/**
 * @file	poke_anm_b026_3.s
 * @brief	
 * @author	
 * @date	
 *
 */
//==============================================================================

	.text
	
	.include	"past.h"
	.include	"past_def.h"
	
	.global		PAST_ANIME_B026_3
	
// =============================================================================
//
//
//	�w��	�s�����s����	�񐔏��Ȃ�	
//
//
// =============================================================================
PAST_ANIME_B026_3:
	CALL_MF_CURVE	APPLY_SET,0,CURVE_SIN_MINUS,TARGET_DY,6,0x2000,0,4
	HOLD_CMD
	
	CALL_MF_CURVE	APPLY_SET,0,CURVE_SIN_MINUS,TARGET_DY,7,0x2000,0,4
	HOLD_CMD
	END_ANM
