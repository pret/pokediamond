//==============================================================================
/**
 * @file	poke_anm_b027_3.s
 * @brief	
 * @author	
 * @date	
 *
 */
//==============================================================================

	.text
	
	.include	"past.h"
	.include	"past_def.h"
	
	.global		PAST_ANIME_B027_3
	
// =============================================================================
//
//
//	背面		揺れながら上下
//
//
// =============================================================================
#define CALC_NUM	(60)
#define TILT	(0x800) 
#define HEIGHT	(4)
PAST_ANIME_B027_3:
	SET_ADD_PARAM	PARAM_DY,USE_VAL,HEIGHT,PARAM_SET
	APPLY_TRANS

	//CALC_NUM回の処理で左右TILTの角度傾ける　左右２回ずつ行うので2周分(0x20000)
	CALL_MF_CURVE_DIVTIME APPLY_SET,0,CURVE_SIN,TARGET_ROT,TILT,0x20000,0,CALC_NUM
	//傾きにあわせて縦移動
	CALL_MF_CURVE_DIVTIME APPLY_ADD,0,CURVE_COS_MINUS,TARGET_DY,HEIGHT,0x10000,0,CALC_NUM	
	HOLD_CMD

	END_ANM
