//==============================================================================
/**
 * @file	poke_anm_b011_1.s
 * @brief	�o�E���h�X���[��
 * @author	
 * @date	
 *
 */
//==============================================================================

	.text
	
	.include	"past.h"
	.include	"past_def.h"
	
	.global		PAST_ANIME_B011_1
	
// =============================================================================
//
//
//	�w��	�o�E���h�X���[���N�C�b�N
//
//
// =============================================================================
PAST_ANIME_B010_1:
	//���[�v2��A�w�U��0x4�@�x�U��0x6�@������16
	START_LOOP	2
		//0���`90��
		//dy�̒l��0x6�ɃZ�b�g
		SET_ADD_PARAM		PARAM_DY,USE_VAL,0x6,PARAM_SET
		//4��̏�����90��������
		CALL_MF_CURVE_DIVTIME	APPLY_SET,0,CURVE_SIN_MINUS,TARGET_DX,0x4,0x4000,0,4
		CALL_MF_CURVE_DIVTIME	APPLY_ADD,0,CURVE_SIN,TARGET_DY,0x6,0x4000,0xc000,4
		HOLD_CMD
		//dx�̒l��-0x4�ɃZ�b�g
		SET_ADD_PARAM		PARAM_DX,USE_VAL,-0x4,PARAM_SET
		APPLY_TRANS

		//90���`270��
		//dy�̒l��0x6�ɃZ�b�g
		SET_ADD_PARAM		PARAM_DY,USE_VAL,0x6,PARAM_SET
		//8��̏�����180������
		CALL_MF_CURVE_DIVTIME	APPLY_SET,0,CURVE_SIN_MINUS,TARGET_DX,0x4,0x8000,0x4000,8
		CALL_MF_CURVE_DIVTIME	APPLY_ADD,0,CURVE_SIN,TARGET_DY,0x6,0x8000,0x8000,8
		HOLD_CMD
		//dx�̒l��0x4�ɃZ�b�g
		SET_ADD_PARAM		PARAM_DX,USE_VAL,0x4,PARAM_SET
		APPLY_TRANS
		
		//270���`360��
		//dy�̒l��0x6�ɃZ�b�g
		SET_ADD_PARAM		PARAM_DY,USE_VAL,0x6,PARAM_SET
		//4��̏�����90������
		CALL_MF_CURVE_DIVTIME	APPLY_SET,0,CURVE_SIN_MINUS,TARGET_DX,0x4,0x4000,0xc000,4
		CALL_MF_CURVE_DIVTIME	APPLY_ADD,0,CURVE_SIN,TARGET_DY,0x6,0x4000,0x8000,4
		HOLD_CMD
		//X�̒l��0�ɃZ�b�g
		SET_ADD_PARAM		PARAM_X,USE_VAL,0,PARAM_SET
		SET_ADD_PARAM		PARAM_DX,USE_VAL,0,PARAM_SET
		//dy�̒l��0�ɃZ�b�g
		SET_ADD_PARAM		PARAM_DY,USE_VAL,0,PARAM_SET
		APPLY_TRANS

	END_LOOP
	
	END_ANM
