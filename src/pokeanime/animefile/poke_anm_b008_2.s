//==============================================================================
/**
 * @file	poke_anm_b008_2.s
 * @brief	
 * @author	
 * @date	
 *
 */
//==============================================================================

	.text
	
	.include	"past.h"
	.include	"past_def.h"
	
	.global		PAST_ANIME_B008_2
	
// =============================================================================
//
//
//	背面	ガクンガクンノーマル
//
//
// =============================================================================
PAST_ANIME_B008_2:
	SET_WORK_VAL	 WORK0,0		//カウンタとして使用
	SET_WORK_VAL	 WORK2,0		//角度として使用

	START_LOOP 15
		ADD_WORK_VAL	WORK0,CALC_VAL,WORK0,1
		ADD_WORK_VAL	WORK2,CALC_VAL,WORK2,0x5000
	
		//揺れ幅を計算してWORK1にセット
		SUB_WORK_VAL	WORK1,CALC_VAL,CALC_WORK,15,WORK0
		MUL_WORK_VAL	WORK1,CALC_VAL,WORK1,6
		DIV_WORK_VAL	WORK1,CALC_WORK,CALC_VAL,WORK1,15

		//WORK3にサイン計算結果をセット　角度WORK2,振幅WORK1、位相0
		SET_WORK_VAL_SIN	WORK3,WORK2,USE_WORK,WORK1,USE_VAL,0

		//アニメデータdyにWORK3をセット
		SET_ADD_PARAM	PARAM_DY,USE_WORK,WORK3,PARAM_SET

		APPLY_TRANS
		SET_REQUEST
	END_LOOP

	SET_WAIT	7

	SET_WORK_VAL	 WORK0,0		//カウンタとして使用
	SET_WORK_VAL	 WORK2,0		//角度として使用

	START_LOOP 15
		ADD_WORK_VAL	WORK0,CALC_VAL,WORK0,1
		ADD_WORK_VAL	WORK2,CALC_VAL,WORK2,0x5000
	
		//揺れ幅を計算してWORK1にセット
		SUB_WORK_VAL	WORK1,CALC_VAL,CALC_WORK,15,WORK0
		MUL_WORK_VAL	WORK1,CALC_VAL,WORK1,6
		DIV_WORK_VAL	WORK1,CALC_WORK,CALC_VAL,WORK1,15

		//WORK3にサイン計算結果をセット　角度WORK2,振幅WORK1、位相0
		SET_WORK_VAL_SIN	WORK3,WORK2,USE_WORK,WORK1,USE_VAL,0

		//アニメデータdyにWORK3をセット
		SET_ADD_PARAM	PARAM_DY,USE_WORK,WORK3,PARAM_SET

		APPLY_TRANS
		SET_REQUEST
	END_LOOP
	
	END_ANM
