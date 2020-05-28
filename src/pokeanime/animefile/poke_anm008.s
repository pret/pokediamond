//==============================================================================
/**
 * @file	poke_anm008.s
 * @brief	
 * @author	
 * @date	
 *
 */
//==============================================================================

	.text
	
	.include	"past.h"
	.include	"past_def.h"
	
	.global		PAST_ANIME008
	
// =============================================================================
//
//
//	
//
//
// =============================================================================
PAST_ANIME008:
	CALL_MF_LINE_DIVTIME	APPLY_SET,0,TARGET_DX,-8,5
	CALL_MF_CURVE_DIVTIME	APPLY_SET,0,CURVE_SIN_MINUS,TARGET_DY,8,0x8000,0,5
	HOLD_CMD
	
	SET_ADD_PARAM		PARAM_X,USE_VAL,-8,PARAM_SET
	SET_ADD_PARAM		PARAM_DX,USE_VAL,0,PARAM_SET
	APPLY_TRANS

	SET_DY_CORRECT		CORRECT_ON_MINUS

	CALL_MF_CURVE		APPLY_SET,8,CURVE_SIN_MINUS,TARGET_DY,20,0x1000,0,8
	CALL_MF_LINE		APPLY_SET,8,TARGET_DX,2,0,8
	CALL_MF_CURVE		APPLY_SET,0,CURVE_SIN_MINUS,TARGET_RY,0x40,0x1000,0,24
	CALL_MF_CURVE		APPLY_SET,0,CURVE_SIN,TARGET_RX,0x20,0x1000,0,24
	HOLD_CMD

	SET_DY_CORRECT		CORRECT_OFF
	
	SET_ADD_PARAM		PARAM_X,USE_VAL,8,PARAM_SET
	SET_ADD_PARAM		PARAM_DX,USE_VAL,0,PARAM_SET
	APPLY_TRANS
	
	CALL_MF_LINE_DIVTIME	APPLY_SET,0,TARGET_DX,-8,5
	CALL_MF_CURVE_DIVTIME	APPLY_SET,0,CURVE_SIN_MINUS,TARGET_DY,8,0x8000,0,5
	HOLD_CMD
	
	END_ANM
