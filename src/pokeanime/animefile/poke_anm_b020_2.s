//==============================================================================
/**
 * @file	poke_anm_b020_2.s
 * @brief	ブルブル横移動
 * @author	
 * @date	
 *
 */
//==============================================================================

	.text
	
	.include	"past.h"
	.include	"past_def.h"
	
	.global		PAST_ANIME_B020_2
	
// =============================================================================
//
//
//	背面	ブルブル横移動
//
//
// =============================================================================
#define	WIDTH	(16)
#define CALC_NUM	(6)
#define HEIGHT	(2)
PAST_ANIME_B020_2:
	//左	CALC_NUM回の処理で-WIDTH移動
	CALL_MF_LINE_DIVTIME	APPLY_SET,0,TARGET_DX,-WIDTH,CALC_NUM
	//上下
	CALL_MF_CURVE_DIVTIME	APPLY_SET,0,CURVE_SIN_MINUS,TARGET_DY,HEIGHT,0x4000*CALC_NUM,0,CALC_NUM
	HOLD_CMD
	
	//右	CALC_NUMx2回の処理でWIDTHｘ2移動
	CALL_MF_LINE_DIVTIME	APPLY_ADD,0,TARGET_DX,WIDTH*2,CALC_NUM*2
	//上下
	CALL_MF_CURVE_DIVTIME	APPLY_SET,0,CURVE_SIN_MINUS,TARGET_DY,HEIGHT,0x4000*CALC_NUM*2,0,CALC_NUM*2
	HOLD_CMD
	
	//左	CALC_NUM回の処理で-WIDTH移動
	CALL_MF_LINE_DIVTIME	APPLY_ADD,0,TARGET_DX,-WIDTH,CALC_NUM
	//上下
	CALL_MF_CURVE_DIVTIME	APPLY_SET,0,CURVE_SIN_MINUS,TARGET_DY,HEIGHT,0x4000*CALC_NUM,0,CALC_NUM
	HOLD_CMD
	
	END_ANM
