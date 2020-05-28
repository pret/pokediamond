//==============================================================================
/**
 * @file	poke_anm_b022_3.s
 * @brief	–c‚ç‚Þ
 * @author	
 * @date	
 *
 */
//==============================================================================

	.text
	
	.include	"past.h"
	.include	"past_def.h"
	
	.global		PAST_ANIME_B022_3
	
// =============================================================================
//
//
//	”w–Ê	–c‚ç‚Þ
//
//
// =============================================================================
#define SIZE	(0x40)
#define CALC_NUM	(30)
PAST_ANIME_B022_3:
	CALL_MF_CURVE_DIVTIME	APPLY_ADD,0,CURVE_SIN,TARGET_RX,SIZE,0x8000,0,CALC_NUM
	CALL_MF_CURVE_DIVTIME	APPLY_ADD,0,CURVE_SIN,TARGET_RY,SIZE,0x8000,0,CALC_NUM
	HOLD_CMD
	
	END_ANM
