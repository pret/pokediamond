//==============================================================================
/**
 * @file	poke_anm007.s
 * @brief	
 * @author	
 * @date	
 *
 */
//==============================================================================

	.text
	
	.include	"past.h"
	.include	"past_def.h"
	
	.global		PAST_ANIME007
	
// =============================================================================
//
//
//	�s�����s����	
//
//
// =============================================================================
PAST_ANIME007:
	START_LOOP	2
		CALL_MF_CURVE	APPLY_SET,0,CURVE_SIN_MINUS,TARGET_DY,6,0x2000,0,4
		HOLD_CMD
	END_LOOP
	
	CALL_MF_CURVE	APPLY_SET,0,CURVE_SIN_MINUS,TARGET_DY,9,0x2000,0,4
	HOLD_CMD
	END_ANM
