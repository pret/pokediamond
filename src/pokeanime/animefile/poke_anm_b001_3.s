//==============================================================================
/**
 * @file	poke_anm_b001_3.s
 * @brief	ポケモンアニメ分身
 * @author	saito
 * @date	
 *
 */
//==============================================================================

	.text
	
	.include	"past.h"
	.include	"past_def.h"
	
	.global		PAST_ANIME_B001_3
	
// =============================================================================
//
//
//	背面	分身
//
//
// =============================================================================
PAST_ANIME_B001_3:
	SET_WORK_VAL		WORK1,0
	SET_WORK_VAL		WORK2,1

	START_LOOP			32
		ADD_WORK_VAL		WORK1,CALC_VAL,WORK1,1024
		SET_WORK_VAL_SIN	WORK0,WORK1,USE_VAL,6,USE_VAL,0
		MUL_WORK_VAL		WORK0,CALC_WORK,WORK0,WORK2
		SET_D				WORK0,PARAM_DX
		MUL_WORK_VAL		WORK2,CALC_VAL,WORK2,-1
		APPLY_TRANS
		SET_REQUEST
	END_LOOP

	END_ANM
