//==============================================================================
/**
 * @file	poke_anm_b018_1.s
 * @brief	�΃t�F�[�h
 * @author	
 * @date	
 *
 */
//==============================================================================

	.text
	
	.include	"past.h"
	.include	"past_def.h"
	
	.global		PAST_ANIME_B018_1
	
// =============================================================================
//
//
//	�w��	�΃t�F�[�h
//
//
// =============================================================================
#define	CALC_NUM	(10) 
#define COLOR	(0x3e0)
#define FADE_VAL	(12)
PAST_ANIME_B018_1:
	SET_PALETTE_FADE	0,FADE_VAL,0,COLOR
	WAIT_PALETTE_FADE

	//CALC_NUM��̓����2������
	CALL_MF_CURVE_DIVTIME	APPLY_SET,0,CURVE_SIN_MINUS,TARGET_DX,6,0x10000*2,0,CALC_NUM
	HOLD_CMD

	SET_PALETTE_FADE	FADE_VAL,0,0,COLOR
	WAIT_PALETTE_FADE
	END_ANM
