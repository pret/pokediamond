//==============================================================================
/**
 * @file	poke_anm013.s
 * @brief	横とびはね　スモール
 * @author	saito
 * @date	
 *
 */
//==============================================================================

	.text
	
	.include	"past.h"
	.include	"past_def.h"
	
	.global		PAST_ANIME013
	
// =============================================================================
//
//
//	横とびはね　スモール
//
//
// =============================================================================
PAST_ANIME013:
	//>飛び跳ね1回目
	//4回の処理で0x8000（180°）を処理
	CALL_MF_CURVE_DIVTIME	APPLY_SET,0,CURVE_SIN_MINUS,TARGET_DY,10,0x8000,0,4
	//4回の処理で8移動
	CALL_MF_LINE_DIVTIME	APPLY_SET,0,TARGET_DX,8,4
	//4回の処理で0x800(11.25°)傾く
	CALL_MF_LINE_DIVTIME	APPLY_SET,0,TARGET_ROT,0x800,4
	HOLD_CMD
	
	//>飛び跳ね2～4回目
	START_LOOP	2
		
		//スプライト位置をx=8に設定 dxを0に設定
		SET_ADD_PARAM		PARAM_X,USE_VAL,8,PARAM_SET
		SET_ADD_PARAM		PARAM_DX,USE_VAL,0,PARAM_SET
		APPLY_TRANS
		//スプライト回転を0x800にセット
		SET_ADD_PARAM		PARAM_ROT,USE_VAL,0x800,PARAM_SET
		APPLY_AFFINE
		
		//6回の処理で0x8000（180°）を処理
		CALL_MF_CURVE_DIVTIME	APPLY_SET,0,CURVE_SIN_MINUS,TARGET_DY,10,0x8000,0,6
		//6回の処理で-16移動
		CALL_MF_LINE_DIVTIME	APPLY_SET,0,TARGET_DX,-16,6
		//6回の処理で0x800～-0x800の-0x1000(22.5°)分傾く
		CALL_MF_LINE_DIVTIME	APPLY_ADD,0,TARGET_ROT,-0x1000,6
		HOLD_CMD

		//スプライト位置をx=-8に設定 dxを0に設定
		SET_ADD_PARAM		PARAM_X,USE_VAL,-8,PARAM_SET
		SET_ADD_PARAM		PARAM_DX,USE_VAL,0,PARAM_SET
		APPLY_TRANS
		//スプライト回転を-0x800にセット
		SET_ADD_PARAM		PARAM_ROT,USE_VAL,-0x800,PARAM_SET
		APPLY_AFFINE

		//6回の処理で0x8000（180°）を処理
		CALL_MF_CURVE_DIVTIME	APPLY_SET,0,CURVE_SIN_MINUS,TARGET_DY,10,0x8000,0,6
		//6回の処理で16移動
		CALL_MF_LINE_DIVTIME	APPLY_SET,0,TARGET_DX,16,6
		//6回の処理で-0x800～0x800の0x1000(22.5°)分傾く
		CALL_MF_LINE_DIVTIME	APPLY_ADD,0,TARGET_ROT,0x1000,6
		HOLD_CMD

	END_LOOP

	//スプライト位置をx=8に設定 dxを0に設定
	SET_ADD_PARAM		PARAM_X,USE_VAL,8,PARAM_SET
	SET_ADD_PARAM		PARAM_DX,USE_VAL,0,PARAM_SET
	APPLY_TRANS
	//スプライト回転を0x800にセット
	SET_ADD_PARAM		PARAM_ROT,USE_VAL,0x800,PARAM_SET
	APPLY_AFFINE

	//>飛び跳ね5回目
	//6回の処理で0x8000（180°）を処理
	CALL_MF_CURVE_DIVTIME	APPLY_SET,0,CURVE_SIN_MINUS,TARGET_DY,10,0x8000,0,6
	//6回の処理で-16移動
	CALL_MF_LINE_DIVTIME	APPLY_SET,0,TARGET_DX,-16,6
	//6回の処理で0x800～-0x800の-0x1000(22.5°)分傾く
	CALL_MF_LINE_DIVTIME	APPLY_ADD,0,TARGET_ROT,-0x1000,6
	HOLD_CMD

	//スプライト位置をx=-8に設定 dxを0に設定
	SET_ADD_PARAM		PARAM_X,USE_VAL,-8,PARAM_SET
	SET_ADD_PARAM		PARAM_DX,USE_VAL,0,PARAM_SET
	APPLY_TRANS
	//スプライト回転を-0x800にセット
	SET_ADD_PARAM		PARAM_ROT,USE_VAL,-0x800,PARAM_SET
	APPLY_AFFINE
	
	//>飛び跳ね6回目
	//6回の処理で0x8000（180°）を処理
	CALL_MF_CURVE_DIVTIME	APPLY_SET,0,CURVE_SIN_MINUS,TARGET_DY,10,0x8000,0,6
	//6回の処理で8移動
	CALL_MF_LINE_DIVTIME	APPLY_SET,0,TARGET_DX,8,6
	//6回の処理で0x800(11.25°)傾く
	CALL_MF_LINE_DIVTIME	APPLY_ADD,0,TARGET_ROT,0x800,6
	HOLD_CMD
	
	
	END_ANM
