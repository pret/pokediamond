//==============================================================================
/**
 * @file	poke_anm_b023_3.s
 * @brief	
 * @author	
 * @date	
 *
 */
//==============================================================================

	.text
	
	.include	"past.h"
	.include	"past_def.h"
	
	.global		PAST_ANIME_B023_3
	
// =============================================================================
//
//
//	�w��	2�񂿂���Ł@�c��ރX���[
//
//
// =============================================================================
PAST_ANIME_B023_3:
	SET_DY_CORRECT		CORRECT_ON_MINUS
	
	//32��̃��[�v��1.5���i0x18000�j������
	CALL_MF_CURVE_DIVTIME APPLY_SET,0,CURVE_SIN_MINUS,TARGET_RY,0x20,0x18000,0,32
	CALL_MF_CURVE_DIVTIME APPLY_SET,0,CURVE_SIN_MINUS,TARGET_RX,0x30,0x18000,0,32
	HOLD_CMD

	SET_DY_CORRECT		CORRECT_OFF

	END_ANM
