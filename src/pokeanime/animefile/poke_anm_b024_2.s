//==============================================================================
/**
 * @file	poke_anm_b024_2.s
 * @brief	
 * @author	
 * @date	
 *
 */
//==============================================================================

	.text
	
	.include	"past.h"
	.include	"past_def.h"
	
	.global		PAST_ANIME_B024_2
	
// =============================================================================
//
//
//	�w��	�Ԃꉡ�h��A�N�C�b�N
//
//
// =============================================================================
#define CALC_NUM	(12)
#define WIDTH	(16)
#define SIZE	(0x40)
PAST_ANIME_B024_2:
	//CALC_NUM��̃��[�v��0.5���i0x8000�j������
	CALL_MF_CURVE_DIVTIME APPLY_SET,0,CURVE_SIN,TARGET_DX,WIDTH,0x8000,0,CALC_NUM
	CALL_MF_CURVE_DIVTIME APPLY_ADD,0,CURVE_SIN_MINUS,TARGET_RX,SIZE,0x8000,0,CALC_NUM
	HOLD_CMD
	//CALC_NUM��̃��[�v��0.5���i0x8000�j������
	CALL_MF_CURVE_DIVTIME APPLY_SET,0,CURVE_SIN,TARGET_DX,WIDTH,0x8000,0x8000,CALC_NUM
	CALL_MF_CURVE_DIVTIME APPLY_ADD,0,CURVE_SIN_MINUS,TARGET_RX,SIZE,0x8000,0,CALC_NUM
	HOLD_CMD

	END_ANM
