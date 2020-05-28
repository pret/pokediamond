//==============================================================================
/**
 * @file	poke_anm001.s
 * @brief	
 * @author	
 * @date	
 *
 */
//==============================================================================

	.text
	
	.include	"past.h"
	.include	"past_def.h"
	
	.global		PAST_ANIME001
	
// =============================================================================
//
//
//	
//
//
// =============================================================================
PAST_ANIME001:

	SET_DY_CORRECT		CORRECT_ON_MINUS
	//24��̃��[�v�ŁA1.5���i0x18000�j�������@
	CALL_MF_CURVE_DIVTIME	APPLY_SET,0,CURVE_SIN_MINUS,TARGET_RY,0x20,0x18000,0,24
	CALL_MF_CURVE_DIVTIME	APPLY_SET,0,CURVE_SIN,TARGET_RX,0x20,0x18000,0,24
	//8��̃��[�v�ŁA180���i0x8000�j������ 8�E�F�C�g
	CALL_MF_CURVE_DIVTIME	APPLY_SET,8,CURVE_SIN_MINUS,TARGET_DY,10,0x8000,0,8
	HOLD_CMD

	SET_DY_CORRECT		CORRECT_OFF

	END_ANM
