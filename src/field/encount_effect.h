//=============================================================================
/**
 * @file	encount.h	
 * @brief	�G���J�E���g�G�t�F�N�g
 * @author	GAME FREAK inc.
 */
//=============================================================================

#ifndef	__ENCOUNT_EFFECT_H__
#define	__ENCOUNT_EFFECT_H__

#include "battle/battle_common.h"

#undef GLOBAL
#ifdef __ENCOUNT_EFFECT_H_GLOBAL__
#define GLOBAL /*	*/
#else
#define GLOBAL extern
#endif

//-------------------------------------
//	
//	�G���J�E���g�G�t�F�N�gNo
//
//	�v�Z���Ŗ쐶��ƃg���[�i�[��́A
//	�G���J�E���g�����߂Ă��邽�߁A
//	�쐶�ƁA�g���[�i�[�̃G�t�F�N�g���Ԃ�ς��邱�Ƃ͋֎~
//=====================================
enum{
	// �t�B�[���h
	ENCOUNT_FIELD_GRASS_LEVEL_LOW,	// ���@���x���Ⴂ
	ENCOUNT_FIELD_GRASS_LEVEL_HIGH,	// ���@���x������
	ENCOUNT_FIELD_WATER_LEVEL_LOW,	// ���@���x���Ⴂ
	ENCOUNT_FIELD_WATER_LEVEL_HIGH,	// ���@���x������
	ENCOUNT_FIELD_DAN_LEVEL_LOW,	// �_���W�����@���x���Ⴂ
	ENCOUNT_FIELD_DAN_LEVEL_HIGH,	// �_���W�����@���x������

	// �g���[�i�[
	ENCOUNT_TRAINER_GRASS_LEVEL_LOW,	// ���@���x���Ⴂ
	ENCOUNT_TRAINER_GRASS_LEVEL_HIGH,	// ���@���x������
	ENCOUNT_TRAINER_WATER_LEVEL_LOW,	// ���@���x����
	ENCOUNT_TRAINER_WATER_LEVEL_HIGH,	// ���@���x������
	ENCOUNT_TRAINER_DAN_LEVEL_LOW,		// �_���@���x����
	ENCOUNT_TRAINER_DAN_LEVEL_HIGH,		// �_���@���x������

	// �W���@
	ENCOUNT_SPTR_KUROGANE_GYM,		// �N���K�l�W��
	ENCOUNT_SPTR_HAKUTAI_GYM,		// �n�N�^�C�W��
	ENCOUNT_SPTR_NOMOSE_GYM,		// �m���Z�W��
	ENCOUNT_SPTR_TOBARI_GYM,		// �g�o���W��
	ENCOUNT_SPTR_YOSUGA_GYM,		// ���X�K�g�W��
	ENCOUNT_SPTR_KISSAKI_GYM,		// �L�b�T�L�W��
	ENCOUNT_SPTR_MIO_GYM,			// �~�I�W��
	ENCOUNT_SPTR_NAGISA_GYM,		// �i�M�T�W��
	
	// �l�V��
	ENCOUNT_SPTR_SITEN_00,
	ENCOUNT_SPTR_SITEN_01,
	ENCOUNT_SPTR_SITEN_02,
	ENCOUNT_SPTR_SITEN_03,
	
	// �`�����s�I��
	ENCOUNT_SPTR_CHANPION,
	
	// �`���@�p�b�P�[�W
	ENCOUNT_LEGEND_NORMAL,		// �`���|�P����
	ENCOUNT_LEGEND_PACKAGE,		// PACKAGE�|�P����
	
	// ��͒c
	ENCOUNT_GINGA_NORMAL,		// ��͒c�ʏ�
	ENCOUNT_GINGA_SPECIAL,		// ��͒c����

	// ����
	ENCOUNT_SPECIAL_TOWER,		// �o�g���^���[�@�t�����g
	ENCOUNT_SPECIAL_DOUBLE,		// �_�u���o�g��

/*	ENCOUNT_MOTIONBL00,		// ���[�V�����u���[�G�t�F�N�g��]
	ENCOUNT_MOTIONBL01,		// ���[�V�����u���[�G�t�F�N�g���h��//*/
	ENCOUNT_NUM

};
#define ENCOUNT_MAIN_NONE	(ENCOUNT_NUM)	// �����p���G���J�E���g���Ȃ��Ƃ��Ɏw��


//----------------------------------------------------------------------------
/**
 *
 *@brief	�G���J�E���g�G�t�F�N�g�J�n
 *
 *@param	No		�G���J�E���g�G�t�F�N�gNO
 *@param	*fsw	�t�B�[���h�V�X�e�����[�N�̃|�C���^
 *@param	end		�I���`�F�b�N�p�@TRUE�F�I������ 
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void EncountEffectStart(int No, FIELDSYS_WORK *fsw, BOOL* end );


//-----------------------------------------------------------------------------
/**
 *		�o�g���p�����[�^����
 *		�Ή�����G���J�E���g�G�t�F�N�g�i���o�[��Ԃ�
 */
//-----------------------------------------------------------------------------
GLOBAL u32 ENCEFF_GetEffectNo( const BATTLE_PARAM * p_battleparam );

#undef GLOBAL

#endif	/* __ENCOUNT_H__ */
