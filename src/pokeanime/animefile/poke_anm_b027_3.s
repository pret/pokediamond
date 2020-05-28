//==============================================================================
/**
 * @file	poke_anm_b027_3.s
 * @brief	
 * @author	
 * @date	
 *
 */
//==============================================================================

	.text
	
	.include	"past.h"
	.include	"past_def.h"
	
	.global		PAST_ANIME_B027_3
	
// =============================================================================
//
//
//	�w��		�h��Ȃ���㉺
//
//
// =============================================================================
#define CALC_NUM	(60)
#define TILT	(0x800) 
#define HEIGHT	(4)
PAST_ANIME_B027_3:
	SET_ADD_PARAM	PARAM_DY,USE_VAL,HEIGHT,PARAM_SET
	APPLY_TRANS

	//CALC_NUM��̏����ō��ETILT�̊p�x�X����@���E�Q�񂸂s���̂�2����(0x20000)
	CALL_MF_CURVE_DIVTIME APPLY_SET,0,CURVE_SIN,TARGET_ROT,TILT,0x20000,0,CALC_NUM
	//�X���ɂ��킹�ďc�ړ�
	CALL_MF_CURVE_DIVTIME APPLY_ADD,0,CURVE_COS_MINUS,TARGET_DY,HEIGHT,0x10000,0,CALC_NUM	
	HOLD_CMD

	END_ANM
