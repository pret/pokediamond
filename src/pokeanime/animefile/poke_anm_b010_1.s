//==============================================================================
/**
 * @file	poke_anm_b010_1.s
 * @brief	�o�E���h
 * @author	
 * @date	
 *
 */
//==============================================================================

	.text
	
	.include	"past.h"
	.include	"past_def.h"
	
	.global		PAST_ANIME_B010_1
	
// =============================================================================
//
//
//	�w��	�o�E���h�N�C�b�N
//
//
// =============================================================================
PAST_ANIME_B010_1:
	//���[�v2��A�w�U��0xc�@�x�U��0xc�@������16
	START_LOOP	2
		//0���`90��
		//dy�̒l��0xc�ɃZ�b�g
		SET_ADD_PARAM		PARAM_DY,USE_VAL,0xc,PARAM_SET
		//4��̏�����90��������
		CALL_MF_CURVE_DIVTIME	APPLY_SET,0,CURVE_SIN_MINUS,TARGET_DX,0xc,0x4000,0,4
		CALL_MF_CURVE_DIVTIME	APPLY_ADD,0,CURVE_SIN,TARGET_DY,0xc,0x4000,0xc000,4
		HOLD_CMD
		//dx�̒l��-0xc�ɃZ�b�g
		SET_ADD_PARAM		PARAM_DX,USE_VAL,-0xc,PARAM_SET
		APPLY_TRANS

		//90���`270��
		//dy�̒l��0xc�ɃZ�b�g
		SET_ADD_PARAM		PARAM_DY,USE_VAL,0xc,PARAM_SET
		//8��̏�����180������
		CALL_MF_CURVE_DIVTIME	APPLY_SET,0,CURVE_SIN_MINUS,TARGET_DX,0xc,0x8000,0x4000,8
		CALL_MF_CURVE_DIVTIME	APPLY_ADD,0,CURVE_SIN,TARGET_DY,0xc,0x8000,0x8000,8
		HOLD_CMD
		//dx�̒l��0xc�ɃZ�b�g
		SET_ADD_PARAM		PARAM_DX,USE_VAL,0xc,PARAM_SET
		APPLY_TRANS
		
		//270���`360��
		//dy�̒l��0xc�ɃZ�b�g
		SET_ADD_PARAM		PARAM_DY,USE_VAL,0xc,PARAM_SET
		//4��̏�����90������
		CALL_MF_CURVE_DIVTIME	APPLY_SET,0,CURVE_SIN_MINUS,TARGET_DX,0xc,0x4000,0xc000,4
		CALL_MF_CURVE_DIVTIME	APPLY_ADD,0,CURVE_SIN,TARGET_DY,0xc,0x4000,0x8000,4
		HOLD_CMD
		//X�̒l��0�ɃZ�b�g
		SET_ADD_PARAM		PARAM_X,USE_VAL,0,PARAM_SET
		SET_ADD_PARAM		PARAM_DX,USE_VAL,0,PARAM_SET
		//dy�̒l��0�ɃZ�b�g
		SET_ADD_PARAM		PARAM_DY,USE_VAL,0,PARAM_SET
		APPLY_TRANS

	END_LOOP
	
	END_ANM
