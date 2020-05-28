//==============================================================================
/**
 * @file	poke_anm012.s
 * @brief	きざみよことび
 * @author	saito
 * @date	
 *
 */
//==============================================================================

	.text
	
	.include	"past.h"
	.include	"past_def.h"
	
	.global		PAST_ANIME012
	
// =============================================================================
//
//
//	きざみよことび
//
//
// =============================================================================
PAST_ANIME011:
	//>飛び跳ね1回目
	//6回の処理で-8移動
	CALL_MF_LINE_DIVTIME	APPLY_SET,0,TARGET_DX,-8,6
	//6回の処理で180°(0x8000)処理
	CALL_MF_CURVE_DIVTIME	APPLY_SET,0,CURVE_SIN_MINUS,TARGET_DY,8,0x8000,0,6
	HOLD_CMD

	//スプライト位置をx=-8に設定 dxを0に設定
	SET_ADD_PARAM		PARAM_X,USE_VAL,-8,PARAM_SET
	SET_ADD_PARAM		PARAM_DX,USE_VAL,0,PARAM_SET
	APPLY_TRANS
	
	//飛び跳ね2回目
	//6回の処理で8移動
	CALL_MF_LINE_DIVTIME	APPLY_SET,0,TARGET_DX,8,6
	//6回の処理で180°(0x8000)処理
	CALL_MF_CURVE_DIVTIME	APPLY_SET,0,CURVE_SIN_MINUS,TARGET_DY,8,0x8000,0,6
	HOLD_CMD
		
	//スプライト位置をx=0に設定 dxを0に設定
	SET_ADD_PARAM		PARAM_X,USE_VAL,0,PARAM_SET
	SET_ADD_PARAM		PARAM_DX,USE_VAL,0,PARAM_SET
	APPLY_TRANS

	//飛び跳ね3回目
	//6回の処理で8移動
	CALL_MF_LINE_DIVTIME	APPLY_SET,0,TARGET_DX,8,6
	//6回の処理で180°(0x8000)処理
	CALL_MF_CURVE_DIVTIME	APPLY_SET,0,CURVE_SIN_MINUS,TARGET_DY,8,0x8000,0,6
	HOLD_CMD
		
	//スプライト位置をx=8に設定 dxを0に設定
	SET_ADD_PARAM		PARAM_X,USE_VAL,8,PARAM_SET
	SET_ADD_PARAM		PARAM_DX,USE_VAL,0,PARAM_SET
	APPLY_TRANS

	//飛び跳ね4回目
	//6回の処理で-8移動
	CALL_MF_LINE_DIVTIME	APPLY_SET,0,TARGET_DX,-8,6
	//6回の処理で180°(0x8000)処理
	CALL_MF_CURVE_DIVTIME	APPLY_SET,0,CURVE_SIN_MINUS,TARGET_DY,8,0x8000,0,6
	HOLD_CMD

	END_ANM
