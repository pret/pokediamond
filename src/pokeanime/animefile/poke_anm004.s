//==============================================================================
/**
 * @file	poke_anm004.s
 * @brief	ちぢんで　膨らむ
 * @author	
 * @date	
 *
 */
//==============================================================================

	.text
	
	.include	"past.h"
	.include	"past_def.h"
	
	.global		PAST_ANIME004
	
// =============================================================================
//
//
//	ちぢんで　膨らむ
//
//
// =============================================================================
PAST_ANIME004:
	SET_WORK_VAL		WORK0,0		//カウンタ
	START_LOOP	40
		//角度を計算してWORK2にセット
		MUL_WORK_VAL	WORK2,CALC_VAL,WORK0,0x10000
		DIV_WORK_VAL	WORK2,CALC_WORK,CALC_VAL,WORK2,40
		
		//WORK1にWORK0を2で割った余りをセット
		MOD_WORK_VAL	WORK1,CALC_WORK,CALC_VAL,WORK0,2
		//WORK1が0のとき	WORK3に0x20をセット
		SET_IFWORKVAL	USE_VAL,WORK1,0,COMP_EQUAL,USE_VAL,WORK3,0x20
		//WORK1が1のとき	WORK3に0x8をセット
		SET_IFWORKVAL	USE_VAL,WORK1,1,COMP_EQUAL,USE_VAL,WORK3,0x8
		
		//WORK4にサイン計算結果をセット　角度WORK2,振幅WORK3、位相0
		SET_WORK_VAL_SIN	WORK4,WORK2,USE_WORK,WORK3,USE_VAL,0

		//WORK5に拡縮率をセット
		SUB_WORK_VAL		WORK5,CALC_VAL,CALC_WORK,0,WORK4

		//アニメデータにセット
		SET_ADD_PARAM		PARAM_RX,USE_WORK,WORK5,PARAM_SET
		SET_ADD_PARAM		PARAM_RY,USE_WORK,WORK5,PARAM_SET

		//スプライトに反映
		APPLY_AFFINE
		
		//カウントアップ
		ADD_WORK_VAL	WORK0,CALC_VAL,WORK0,1

		//描画リクエスト
		SET_REQUEST
	END_LOOP
	
	END_ANM
