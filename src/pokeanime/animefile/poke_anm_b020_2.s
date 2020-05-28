//==============================================================================
/**
 * @file	poke_anm_b020_2.s
 * @brief	�u���u�����ړ�
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
//	�w��	�u���u�����ړ�
//
//
// =============================================================================
#define	WIDTH	(16)
#define CALC_NUM	(6)
#define HEIGHT	(2)
PAST_ANIME_B020_2:
	//��	CALC_NUM��̏�����-WIDTH�ړ�
	CALL_MF_LINE_DIVTIME	APPLY_SET,0,TARGET_DX,-WIDTH,CALC_NUM
	//�㉺
	CALL_MF_CURVE_DIVTIME	APPLY_SET,0,CURVE_SIN_MINUS,TARGET_DY,HEIGHT,0x4000*CALC_NUM,0,CALC_NUM
	HOLD_CMD
	
	//�E	CALC_NUMx2��̏�����WIDTH��2�ړ�
	CALL_MF_LINE_DIVTIME	APPLY_ADD,0,TARGET_DX,WIDTH*2,CALC_NUM*2
	//�㉺
	CALL_MF_CURVE_DIVTIME	APPLY_SET,0,CURVE_SIN_MINUS,TARGET_DY,HEIGHT,0x4000*CALC_NUM*2,0,CALC_NUM*2
	HOLD_CMD
	
	//��	CALC_NUM��̏�����-WIDTH�ړ�
	CALL_MF_LINE_DIVTIME	APPLY_ADD,0,TARGET_DX,-WIDTH,CALC_NUM
	//�㉺
	CALL_MF_CURVE_DIVTIME	APPLY_SET,0,CURVE_SIN_MINUS,TARGET_DY,HEIGHT,0x4000*CALC_NUM,0,CALC_NUM
	HOLD_CMD
	
	END_ANM
