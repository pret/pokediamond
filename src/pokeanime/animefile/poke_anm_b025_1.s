//==============================================================================
/**
 * @file	poke_anm_b025_1.s
 * @brief	
 * @author	
 * @date	
 *
 */
//==============================================================================

	.text
	
	.include	"past.h"
	.include	"past_def.h"
	
	.global		PAST_ANIME_B025_1
	
// =============================================================================
//
//
//	�w��	�Ԃꉡ�h��B�N�C�b�N��2
//
//
// =============================================================================
#define CALC_NUM	(6)
#define WIDTH	(16)
#define SIZE	(0x40)
#define RAD	(0x4000)
PAST_ANIME_B025_1:
	START_LOOP	2
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
	END_LOOP

	END_ANM
