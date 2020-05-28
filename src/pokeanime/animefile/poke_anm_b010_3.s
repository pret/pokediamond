//==============================================================================
/**
 * @file	poke_anm_b010_3.s
 * @brief	バウンド
 * @author	
 * @date	
 *
 */
//==============================================================================

	.text
	
	.include	"past.h"
	.include	"past_def.h"
	
	.global		PAST_ANIME_B010_3
	
// =============================================================================
//
//
//	背面	バウンドスロー
//
//
// =============================================================================
PAST_ANIME_B010_3:
	//Ｘ振幅0xc　Ｙ振幅0xc　処理回数32
	
	//0°～90°
	//dyの値を0xcにセット
	SET_ADD_PARAM		PARAM_DY,USE_VAL,0xc,PARAM_SET
	//8回の処理で90°を処理
	CALL_MF_CURVE_DIVTIME	APPLY_SET,0,CURVE_SIN_MINUS,TARGET_DX,0xc,0x4000,0,8
	CALL_MF_CURVE_DIVTIME	APPLY_ADD,0,CURVE_SIN,TARGET_DY,0xc,0x4000,0xc000,8
	HOLD_CMD
	//dxの値を-0xcにセット
	SET_ADD_PARAM		PARAM_DX,USE_VAL,-0xc,PARAM_SET
	APPLY_TRANS
	
	//90°～270°
	//dyの値を0xcにセット
	SET_ADD_PARAM		PARAM_DY,USE_VAL,0xc,PARAM_SET
	//16回の処理で180°処理
	CALL_MF_CURVE_DIVTIME	APPLY_SET,0,CURVE_SIN_MINUS,TARGET_DX,0xc,0x8000,0x4000,16
	CALL_MF_CURVE_DIVTIME	APPLY_ADD,0,CURVE_SIN,TARGET_DY,0xc,0x8000,0x8000,16
	HOLD_CMD
	//dxの値を0xcにセット
	SET_ADD_PARAM		PARAM_DX,USE_VAL,0xc,PARAM_SET
	APPLY_TRANS
		
	//270°～360°
	//dyの値を0xcにセット
	SET_ADD_PARAM		PARAM_DY,USE_VAL,0xc,PARAM_SET
	//8回の処理で90°処理
	CALL_MF_CURVE_DIVTIME	APPLY_SET,0,CURVE_SIN_MINUS,TARGET_DX,0xc,0x4000,0xc000,8
	CALL_MF_CURVE_DIVTIME	APPLY_ADD,0,CURVE_SIN,TARGET_DY,0xc,0x4000,0x8000,8
	HOLD_CMD
	//Xの値を0にセット
	SET_ADD_PARAM		PARAM_X,USE_VAL,0,PARAM_SET
	SET_ADD_PARAM		PARAM_DX,USE_VAL,0,PARAM_SET
	//dyの値を0にセット
	SET_ADD_PARAM		PARAM_DY,USE_VAL,0,PARAM_SET
	APPLY_TRANS

	END_ANM
