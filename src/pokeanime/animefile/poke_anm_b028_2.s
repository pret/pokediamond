//==============================================================================
/**
 * @file	poke_anm_b028_2.s
 * @brief	
 * @author	
 * @date	
 *
 */
//==============================================================================

	.text
	
	.include	"past.h"
	.include	"past_def.h"
	
	.global		PAST_ANIME_B028_2
	
// =============================================================================
//
//
//	背面		足踏み
//
//
// =============================================================================
#define TILT	(3*0x100)
#define CALC_NUM	(15)
#define SHAKE_NUM	(6)
#define SHAKE_SIZE	(2)
PAST_ANIME_B028_2:
	//回転中心を左にずらす
	SET_ADD_VAL		 PARA_ROT_CX,USE_VAL,-32,PARAM_SET
	//傾かせる
	//CALC_NUM回の処理で90°を処理
	CALL_MF_CURVE_DIVTIME	APPLY_SET,0,CURVE_SIN_MINUS,TARGET_ROT,TILT,0x4000,0,CALC_NUM
	HOLD_CMD
	//少しウェイト
	SET_WAIT	1
	//傾きを戻す(CALC_NUM/2回)
	CALL_MF_CURVE_DIVTIME	APPLY_ADD,0,CURVE_SIN,TARGET_ROT,TILT,0x4000,0,CALC_NUM/2
	HOLD_CMD
	//振動
	CALL_MF_CURVE APPLY_SET,0,CURVE_COS,TARGET_DY,SHAKE_SIZE,0x8000,0,SHAKE_NUM
	HOLD_CMD

	END_ANM
