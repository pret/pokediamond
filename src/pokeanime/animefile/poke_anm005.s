//==============================================================================
/**
 * @file	poke_anm005.s
 * @brief	
 * @author	
 * @date	
 *
 */
//==============================================================================

	.text
	
	.include	"past.h"
	.include	"past_def.h"
	
	.global		PAST_ANIME005
	
// =============================================================================
//
//
//	
//
//
// =============================================================================
PAST_ANIME005:

	SET_DY_CORRECT		CORRECT_ON_MINUS
	//48��̃��[�v�ŁA1.5���i0x18000�j�������@
	CALL_MF_CURVE_DIVTIME	APPLY_SET,0,CURVE_SIN_MINUS,TARGET_RY,0x20,0x18000,0,48
	CALL_MF_CURVE_DIVTIME	APPLY_SET,0,CURVE_SIN,TARGET_RX,0x20,0x18000,0,48
	//16��̃��[�v�ŁA180���i0x8000�j������ 16�E�F�C�g
	CALL_MF_CURVE_DIVTIME	APPLY_SET,16,CURVE_SIN_MINUS,TARGET_DY,10,0x8000,0,16
	HOLD_CMD

	SET_DY_CORRECT		CORRECT_OFF

	END_ANM
