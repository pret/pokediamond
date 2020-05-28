//==============================================================================
/**
 * @file	poke_anm_b028_2.s
 * @brief	
 * @author	
 * @date	
 *
 */
//==============================================================================

	.text
	
	.include	"past.h"
	.include	"past_def.h"
	
	.global		PAST_ANIME_B028_2
	
// =============================================================================
//
//
//	�w��		������
//
//
// =============================================================================
#define TILT	(3*0x100)
#define CALC_NUM	(15)
#define SHAKE_NUM	(6)
#define SHAKE_SIZE	(2)
PAST_ANIME_B028_2:
	//��]���S�����ɂ��炷
	SET_ADD_VAL		 PARA_ROT_CX,USE_VAL,-32,PARAM_SET
	//�X������
	//CALC_NUM��̏�����90��������
	CALL_MF_CURVE_DIVTIME	APPLY_SET,0,CURVE_SIN_MINUS,TARGET_ROT,TILT,0x4000,0,CALC_NUM
	HOLD_CMD
	//�����E�F�C�g
	SET_WAIT	1
	//�X����߂�(CALC_NUM/2��)
	CALL_MF_CURVE_DIVTIME	APPLY_ADD,0,CURVE_SIN,TARGET_ROT,TILT,0x4000,0,CALC_NUM/2
	HOLD_CMD
	//�U��
	CALL_MF_CURVE APPLY_SET,0,CURVE_COS,TARGET_DY,SHAKE_SIZE,0x8000,0,SHAKE_NUM
	HOLD_CMD

	END_ANM
