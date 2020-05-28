//==============================================================================
/**
 * @file	poke_anm_b015_3.s
 * @brief	突進
 * @author	
 * @date	
 *
 */
//==============================================================================

	.text
	
	.include	"past.h"
	.include	"past_def.h"
	
	.global		PAST_ANIME_B015_3
	
// =============================================================================
//
//
//	背面	突進3
//
//
// =============================================================================
#define MOVE_WIDTH	(6)
#define START_SPD	(0)
#define BACK_SPD	(-1)
#define ADD_SPD		(1)
#define SHAKE_WIDTH	(2)
#define SHAKE_NUM	(6)
PAST_ANIME_B015_3:
	//後退
	CALL_MF_LINE_DST		APPLY_SET,0,TARGET_DX,BACK_SPD,0,-MOVE_WIDTH
	HOLD_CMD
	//突進
	CALL_MF_LINE_DST		APPLY_ADD,0,TARGET_DX,START_SPD,ADD_SPD,MOVE_WIDTH
	HOLD_CMD

	SET_ADD_PARAM	PARAM_DX,USE_VAL,MOVE_WIDTH,PARAM_SET
	APPLY_TRANS

	//振動
	SET_WORK_VAL		WORK0,SHAKE_WIDTH		//振動幅
	START_LOOP		SHAKE_NUM
		SET_ADD_PARAM	PARAM_DX,USE_WORK,WORK0,PARAM_ADD
		APPLY_TRANS
		MUL_WORK_VAL	WORK0,CALC_VAL,WORK0,-1
		//描画リクエスト
		SET_REQUEST
	END_LOOP
	
	//後退
	SET_ADD_PARAM	PARAM_DX,USE_VAL,MOVE_WIDTH,PARAM_SET
	APPLY_TRANS
	CALL_MF_LINE_DST		APPLY_ADD,0,TARGET_DX,BACK_SPD,0,0
	HOLD_CMD
	
	END_ANM
