//==============================================================================
/**
 * @file	poke_anm_b023_1.s
 * @brief	
 * @author	
 * @date	
 *
 */
//==============================================================================

	.text
	
	.include	"past.h"
	.include	"past_def.h"
	
	.global		PAST_ANIME_B023_1
	
// =============================================================================
//
//
//	�w��	2�񂿂���Ł@�c���x2
//
//
// =============================================================================
PAST_ANIME_B023_1:
	SET_DY_CORRECT		CORRECT_ON_MINUS
	
	//48��̃��[�v��3���i0x30000�j������
	CALL_MF_CURVE_DIVTIME APPLY_SET,0,CURVE_SIN_MINUS,TARGET_RY,0x20,0x30000,0,48
	CALL_MF_CURVE_DIVTIME APPLY_SET,0,CURVE_SIN_MINUS,TARGET_RX,0x30,0x30000,0,48
	HOLD_CMD
	

	SET_DY_CORRECT		CORRECT_OFF

	END_ANM
