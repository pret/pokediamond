//==============================================================================
/**
 * @file	poke_anm_b013_1.s
 * @brief	����
 * @author	
 * @date	
 *
 */
//==============================================================================

	.text
	
	.include	"past.h"
	.include	"past_def.h"
	
	.global		PAST_ANIME_B013_1
	
// =============================================================================
//
//
//	�w��	���ރN�C�b�N
//
//
// =============================================================================
#define TILT	(8*0x100)
#define CALC_NUM	(15)	

PAST_ANIME_B013_1:
	//��]���S�����ɂ��炷
	SET_ADD_VAL		 PARA_ROT_CX,USE_VAL,-32,PARAM_SET

	START_LOOP 2
		//CALC_NUM��̏�����180��������
		CALL_MF_CURVE_DIVTIME	APPLY_SET,0,CURVE_SIN,TARGET_ROT,TILT,0x8000,0,CALC_NUM
		HOLD_CMD
	END_LOOP
	
	END_ANM
