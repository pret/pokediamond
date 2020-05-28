//==============================================================================
/**
 * @file	poke_anm_b025_3.s
 * @brief	
 * @author	
 * @date	
 *
 */
//==============================================================================

	.text
	
	.include	"past.h"
	.include	"past_def.h"
	
	.global		PAST_ANIME_B025_3
	
// =============================================================================
//
//
//	�w��	�Ԃꉡ�h��B�X���[
//
//
// =============================================================================
#define CALC_NUM	(12)
#define WIDTH	(16)
#define SIZE	(0x40)
#define RAD	(0x4000)
PAST_ANIME_B025_3:
	//CALC_NUM��̃��[�v��1/4���i0x4000�j������
	CALL_MF_CURVE_DIVTIME APPLY_SET,0,CURVE_SIN,TARGET_DX,WIDTH,RAD,0,CALC_NUM
	CALL_MF_CURVE_DIVTIME APPLY_ADD,0,CURVE_SIN_MINUS,TARGET_RX,SIZE,0x8000,0,CALC_NUM
	HOLD_CMD
	//CALC_NUM��̃��[�v��1/4���i0x4000�j������
	CALL_MF_CURVE_DIVTIME APPLY_SET,0,CURVE_SIN,TARGET_DX,WIDTH,RAD,0x4000,CALC_NUM
	CALL_MF_CURVE_DIVTIME APPLY_ADD,0,CURVE_SIN_MINUS,TARGET_RX,SIZE,0x8000,0,CALC_NUM
	HOLD_CMD
	//CALC_NUM��̃��[�v��1/4���i0x4000�j������
	CALL_MF_CURVE_DIVTIME APPLY_SET,0,CURVE_SIN,TARGET_DX,WIDTH,RAD,0x8000,CALC_NUM
	CALL_MF_CURVE_DIVTIME APPLY_ADD,0,CURVE_SIN_MINUS,TARGET_RX,SIZE,0x8000,0,CALC_NUM
	HOLD_CMD
	//CALC_NUM��̃��[�v��1/4���i0x4000�j������
	CALL_MF_CURVE_DIVTIME APPLY_SET,0,CURVE_SIN,TARGET_DX,WIDTH,RAD,0xc000,CALC_NUM
	CALL_MF_CURVE_DIVTIME APPLY_ADD,0,CURVE_SIN_MINUS,TARGET_RX,SIZE,0x8000,0,CALC_NUM
	HOLD_CMD

	END_ANM
