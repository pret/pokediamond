//==============================================================================
/**
 * @file	poke_anm_b012_3.s
 * @brief	���E���
 * @author	
 * @date	
 *
 */
//==============================================================================

	.text
	
	.include	"past.h"
	.include	"past_def.h"
	
	.global		PAST_ANIME_B012_3
	
// =============================================================================
//
//
//	�w��	���E���X���[
//
//
// =============================================================================
#define W_SIZE	(0x10)
#define H_SIZE	(0x8)
#define CALC_NUM	(16)	// 32��2

PAST_ANIME_B012_3:
	//�w�U��0x10�@�x�U��0x8�@������32 x 2

	//��
	//16��̏�����90��������
	CALL_MF_CURVE_DIVTIME	APPLY_SET,0,CURVE_SIN_MINUS,TARGET_DX,W_SIZE,0x4000,0,CALC_NUM
	//16��̏�����180������
	CALL_MF_CURVE_DIVTIME	APPLY_SET,0,CURVE_SIN,TARGET_DY,H_SIZE,0x8000,0,CALC_NUM
	HOLD_CMD

	//16��̏�����90��������
	CALL_MF_CURVE_DIVTIME	APPLY_SET,0,CURVE_SIN_MINUS,TARGET_DX,W_SIZE,0x4000,0x4000,CALC_NUM
	//16��̏�����180������
	CALL_MF_CURVE_DIVTIME	APPLY_SET,0,CURVE_SIN,TARGET_DY,H_SIZE,0x8000,0,CALC_NUM
	HOLD_CMD

	//�E
	//16��̏�����90��������
	CALL_MF_CURVE_DIVTIME	APPLY_SET,0,CURVE_SIN,TARGET_DX,W_SIZE,0x4000,0,CALC_NUM
	//16��̏�����180������
	CALL_MF_CURVE_DIVTIME	APPLY_SET,0,CURVE_SIN,TARGET_DY,H_SIZE,0x8000,0,CALC_NUM
	HOLD_CMD

	//16��̏�����90��������
	CALL_MF_CURVE_DIVTIME	APPLY_SET,0,CURVE_SIN,TARGET_DX,W_SIZE,0x4000,0x4000,CALC_NUM
	//16��̏�����180������
	CALL_MF_CURVE_DIVTIME	APPLY_SET,0,CURVE_SIN,TARGET_DY,H_SIZE,0x8000,0,CALC_NUM
	HOLD_CMD

	END_ANM
