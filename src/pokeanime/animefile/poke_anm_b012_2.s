//==============================================================================
/**
 * @file	poke_anm_b012_2.s
 * @brief	左右ゆれ
 * @author	
 * @date	
 *
 */
//==============================================================================

	.text
	
	.include	"past.h"
	.include	"past_def.h"
	
	.global		PAST_ANIME_B012_2
	
// =============================================================================
//
//
//	背面	左右ゆれ
//
//
// =============================================================================
#define W_SIZE	(0x10)
#define H_SIZE	(0x8)
#define CALC_NUM	(12)	// 24÷2

PAST_ANIME_B012_2:
	//Ｘ振幅0x10　Ｙ振幅0x8　処理回数24 x 2

	//左
	//12回の処理で90°を処理
	CALL_MF_CURVE_DIVTIME	APPLY_SET,0,CURVE_SIN_MINUS,TARGET_DX,W_SIZE,0x4000,0,CALC_NUM
	//12回の処理で180°処理
	CALL_MF_CURVE_DIVTIME	APPLY_SET,0,CURVE_SIN,TARGET_DY,H_SIZE,0x8000,0,CALC_NUM
	HOLD_CMD

	//12回の処理で90°を処理
	CALL_MF_CURVE_DIVTIME	APPLY_SET,0,CURVE_SIN_MINUS,TARGET_DX,W_SIZE,0x4000,0x4000,CALC_NUM
	//12回の処理で180°処理
	CALL_MF_CURVE_DIVTIME	APPLY_SET,0,CURVE_SIN,TARGET_DY,H_SIZE,0x8000,0,CALC_NUM
	HOLD_CMD

	//右
	//12回の処理で90°を処理
	CALL_MF_CURVE_DIVTIME	APPLY_SET,0,CURVE_SIN,TARGET_DX,W_SIZE,0x4000,0,CALC_NUM
	//12回の処理で180°処理
	CALL_MF_CURVE_DIVTIME	APPLY_SET,0,CURVE_SIN,TARGET_DY,H_SIZE,0x8000,0,CALC_NUM
	HOLD_CMD

	//12回の処理で90°を処理
	CALL_MF_CURVE_DIVTIME	APPLY_SET,0,CURVE_SIN,TARGET_DX,W_SIZE,0x4000,0x4000,CALC_NUM
	//12回の処理で180°処理
	CALL_MF_CURVE_DIVTIME	APPLY_SET,0,CURVE_SIN,TARGET_DY,H_SIZE,0x8000,0,CALC_NUM
	HOLD_CMD

	END_ANM
