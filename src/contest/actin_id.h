//==============================================================================
/**
 * @file	actin_id.h
 * @brief	���Z�͕���Ŏg�p����A�N�^�[�̃L����ID���̒�`
 * @author	matsuda
 * @date	2005.11.30(��)
 */
//==============================================================================
#ifndef __ACTIN_ID_H__
#define __ACTIN_ID_H__


///�t�H���gOBJ��ID��`�ŁA�eID�Ԃŋ󂯂�ID��
#define ACI_FONT_ID_OFFSET		(10)


//==============================================================================
//	�L����ID
//==============================================================================
enum{
	CHARID_START = 33000,
	
	CHARID_JUDGE_0,		///<�R���O
	CHARID_JUDGE_1,
	CHARID_JUDGE_2,
	
	CHARID_JUDGE_BOX,	///<�R���̓����Ă��锠

	CHARID_SPECIAL_HEART,	///<���ʐR�����ɂ���n�[�g
	CHARID_APPEAL_POINT,	///<�A�s�[���|�C���g�̓_����\���n�[�g
	CHARID_VOLTAGE_EFF,		///<�{���e�[�W���o
	CHARID_VOLTAGE_POINT,	///<�{���e�[�W�|�C���g�̓_����\�������v
	CHARID_NEXT_ICON,		///<���A�C�R��
	
	CHARID_WIN_COVER_0,		///<�E�B���h�E�X�N���[�����̃}�X�N�J�o�[
	CHARID_WIN_COVER_1,		///<�E�B���h�E�X�N���[�����̃}�X�N�J�o�[
	CHARID_WIN_COVER_2,		///<�E�B���h�E�X�N���[�����̃}�X�N�J�o�[
	
	CHARID_JUDGE_REACTION,	///<�R�����A�N�V�����A�C�R��
	
	//-- �T�u��� --//
	CHARID_CONTYPE_ICON_1,
	CHARID_CONTYPE_ICON_2,
	CHARID_CONTYPE_ICON_3,
	CHARID_CONTYPE_ICON_4,
	
	CHARID_SUB_HEART_8,		///<�Z�������̃n�[�g
	CHARID_SUB_HEART_32,	///<�����R�����o����R�����ɂ���n�[�g
	CHARID_SUB_CTYPE_ICON,	///<�R���e�X�g�^�C�v�A�C�R��

	CHARID_ACTIN_CURSOR,	///<���͉�ʃJ�[�\��

	//-- �t�H���gOBJ --//
	CHARID_ACI_FONT_JUDGE_1,		///<�R��1
	CHARID_ACI_FONT_JUDGE_2 = CHARID_ACI_FONT_JUDGE_1 + ACI_FONT_ID_OFFSET,		///<�R��2
	CHARID_ACI_FONT_JUDGE_3 = CHARID_ACI_FONT_JUDGE_2 + ACI_FONT_ID_OFFSET,		///<�R��3
	CHARID_ACI_FONT_JUDGE_4 = CHARID_ACI_FONT_JUDGE_3 + ACI_FONT_ID_OFFSET,		///<�R��4
	CHARID_ACI_FONT_WAZA_1 = CHARID_ACI_FONT_JUDGE_4 + ACI_FONT_ID_OFFSET,		///<�Z1
	CHARID_ACI_FONT_WAZA_2 = CHARID_ACI_FONT_WAZA_1 + ACI_FONT_ID_OFFSET,		///<�Z2
	CHARID_ACI_FONT_WAZA_3 = CHARID_ACI_FONT_WAZA_2 + ACI_FONT_ID_OFFSET,		///<�Z3
	CHARID_ACI_FONT_WAZA_4 = CHARID_ACI_FONT_WAZA_3 + ACI_FONT_ID_OFFSET,		///<�Z4
	CHARID_ACI_FONT_SETUMEI_UP_1 = 
		CHARID_ACI_FONT_WAZA_4 + ACI_FONT_ID_OFFSET,		///<�Z1
	CHARID_ACI_FONT_SETUMEI_UP_2 = 
		CHARID_ACI_FONT_SETUMEI_UP_1 + ACI_FONT_ID_OFFSET,	///<�Z2
	CHARID_ACI_FONT_SETUMEI_UP_3 = 
		CHARID_ACI_FONT_SETUMEI_UP_2 + ACI_FONT_ID_OFFSET,	///<�Z3
	CHARID_ACI_FONT_SETUMEI_UP_4 = 
		CHARID_ACI_FONT_SETUMEI_UP_3 + ACI_FONT_ID_OFFSET,	///<�Z4
	CHARID_ACI_FONT_SETUMEI_DOWN_1 = 
		CHARID_ACI_FONT_SETUMEI_UP_4 + ACI_FONT_ID_OFFSET,		///<�Z1
	CHARID_ACI_FONT_SETUMEI_DOWN_2 = 
		CHARID_ACI_FONT_SETUMEI_DOWN_1 + ACI_FONT_ID_OFFSET,	///<�Z2
	CHARID_ACI_FONT_SETUMEI_DOWN_3 = 
		CHARID_ACI_FONT_SETUMEI_DOWN_2 + ACI_FONT_ID_OFFSET,	///<�Z3
	CHARID_ACI_FONT_SETUMEI_DOWN_4 = 
		CHARID_ACI_FONT_SETUMEI_DOWN_3 + ACI_FONT_ID_OFFSET,	///<�Z4
	
	//�t�H���gOBJID��`�I��
	CHARID_ACI_FONT_ID_END,
	CHARID_ACI_FONT_END = CHARID_ACI_FONT_ID_END + ACI_FONT_ID_OFFSET,
};

//==============================================================================
//	�p���b�gID
//==============================================================================
enum{
	PLTTID_START = 33000,

	PLTTID_OBJ_COMMON,	///<�풓OBJ�p���b�g
	
	PLTTID_JUDGE_0,
	PLTTID_JUDGE_1,
	PLTTID_JUDGE_2,

	PLTTID_FONTACT,			///<�t�H���g�A�N�^�[(�u���[�_�[���Ȃ�)

	PLTTID_WIN_COVER,		///<�E�B���h�E�X�N���[�����̃}�X�N�J�o�[

	//-- �T�u��� --//
	PLTTID_OBJ_COMMON_SUB,	///<�T�u��ʂ̏풓OBJ�p���b�g
	PLTTID_SUB_FONTACT,		///<�T�u��ʂ̃t�H���g�A�N�^�[
	PLTTID_ACTIN_CURSOR,	///<���͉�ʃJ�[�\��
};

//--------------------------------------------------------------
//	�풓OBJ�p���b�g�I�t�Z�b�g
//--------------------------------------------------------------
enum{
	PALOFS_JUDGE_BOX_LEFT = 2,		///<�R���{�b�N�X(��)�̃p���b�g�I�t�Z�b�g
	PALOFS_JUDGE_BOX_CENTER = 4,	///<�R���{�b�N�X(����)�̃p���b�g�I�t�Z�b�g
	PALOFS_JUDGE_BOX_RIGHT = 5,		///<�R���{�b�N�X(�E)�̃p���b�g�I�t�Z�b�g
	PALOFS_SPECIAL_HEART = 0,	///<���ʐR�����ɂ���n�[�g
	PALOFS_APPEAL_POINT = 3,	///<�A�s�[���|�C���g�̓_����\���n�[�g
	PALOFS_VOLTAGE_EFF = 0,		///<�{���e�[�W���o
	PALOFS_VOLTAGE_POINT = 2,	///<�{���e�[�W�|�C���g�̓_����\�������v
	PALOFS_NEXT_ICON = 0,		///<���A�C�R��
	PALOFS_JUDGE_REACTION = 0,	///<�R�����A�N�V�����A�C�R��
	
	ACTIN_COMMON_PAL_NUM = 6,	///<�풓OBJ�p���b�g�̖{��
};

//--------------------------------------------------------------
//	�T�u��ʂ̏풓OBJ�p���b�g�I�t�Z�b�g
//--------------------------------------------------------------
enum{
	PALOFS_SUB_HEART_8 = 0,			///<�Z�������̃n�[�g(AP�l)
	PALOFS_SUB_HEART_BLACK_8 = 1,	///<�Z�������̃n�[�g(�W�Q�l)
	PALOFS_SUB_HEART_32 = 0,		///<�����R�����o����R�����ɂ���n�[�g
	PALOFS_SUB_CTYPE_ICON = 1,		///<�R���e�X�g�^�C�v�A�C�R��
	
	ACTIN_SUB_COMMON_PAL_NUM = 3,	///<�T�u��ʂ̏풓OBJ�p���b�g�̖{��
};

//==============================================================================
//	�Z��ID
//==============================================================================
enum{
	CELLID_START = 33000,

	CELLID_JUDGE_0,
	CELLID_JUDGE_1,
	CELLID_JUDGE_2,

	CELLID_JUDGE_BOX,	///<�R���̓����Ă��锠

	CELLID_SPECIAL_HEART,	///<���ʐR�����ɂ���n�[�g
	CELLID_APPEAL_POINT,	///<�A�s�[���|�C���g�̓_����\���n�[�g
	CELLID_VOLTAGE_EFF,		///<�{���e�[�W���o
	CELLID_VOLTAGE_POINT,	///<�{���e�[�W�|�C���g�̓_����\�������v

	CELLID_NEXT_ICON,		///<���A�C�R��

	CELLID_WIN_COVER,		///<�E�B���h�E�X�N���[�����̃}�X�N�J�o�[

	CELLID_JUDGE_REACTION,	///<�R�����A�N�V�����A�C�R��

	//-- �T�u��� --//
	CELLID_CONTYPE_ICON,

	CELLID_SUB_HEART_8,		///<�Z�������̃n�[�g
	CELLID_SUB_HEART_32,	///<�����R�����o����R�����ɂ���n�[�g
	CELLID_SUB_CTYPE_ICON,	///<�R���e�X�g�^�C�v�A�C�R��
	CELLID_ACTIN_CURSOR,	///<���͉�ʃJ�[�\��

	//-- �t�H���gOBJ --//
	CELLID_ACI_FONT_JUDGE_1,		///<�R��1
	CELLID_ACI_FONT_JUDGE_2 = CELLID_ACI_FONT_JUDGE_1 + ACI_FONT_ID_OFFSET,		///<�R��2
	CELLID_ACI_FONT_JUDGE_3 = CELLID_ACI_FONT_JUDGE_2 + ACI_FONT_ID_OFFSET,		///<�R��3
	CELLID_ACI_FONT_JUDGE_4 = CELLID_ACI_FONT_JUDGE_3 + ACI_FONT_ID_OFFSET,		///<�R��4
	CELLID_ACI_FONT_WAZA_1 = CELLID_ACI_FONT_JUDGE_4 + ACI_FONT_ID_OFFSET,		///<�Z1
	CELLID_ACI_FONT_WAZA_2 = CELLID_ACI_FONT_WAZA_1 + ACI_FONT_ID_OFFSET,		///<�Z2
	CELLID_ACI_FONT_WAZA_3 = CELLID_ACI_FONT_WAZA_2 + ACI_FONT_ID_OFFSET,		///<�Z3
	CELLID_ACI_FONT_WAZA_4 = CELLID_ACI_FONT_WAZA_3 + ACI_FONT_ID_OFFSET,		///<�Z4
	CELLID_ACI_FONT_SETUMEI_UP_1 = 
		CELLID_ACI_FONT_WAZA_4 + ACI_FONT_ID_OFFSET,		///<�Z1
	CELLID_ACI_FONT_SETUMEI_UP_2 = 
		CELLID_ACI_FONT_SETUMEI_UP_1 + ACI_FONT_ID_OFFSET,	///<�Z2
	CELLID_ACI_FONT_SETUMEI_UP_3 = 
		CELLID_ACI_FONT_SETUMEI_UP_2 + ACI_FONT_ID_OFFSET,	///<�Z3
	CELLID_ACI_FONT_SETUMEI_UP_4 = 
		CELLID_ACI_FONT_SETUMEI_UP_3 + ACI_FONT_ID_OFFSET,	///<�Z4
	CELLID_ACI_FONT_SETUMEI_DOWN_1 = 
		CELLID_ACI_FONT_SETUMEI_UP_4 + ACI_FONT_ID_OFFSET,		///<�Z1
	CELLID_ACI_FONT_SETUMEI_DOWN_2 = 
		CELLID_ACI_FONT_SETUMEI_DOWN_1 + ACI_FONT_ID_OFFSET,	///<�Z2
	CELLID_ACI_FONT_SETUMEI_DOWN_3 = 
		CELLID_ACI_FONT_SETUMEI_DOWN_2 + ACI_FONT_ID_OFFSET,	///<�Z3
	CELLID_ACI_FONT_SETUMEI_DOWN_4 = 
		CELLID_ACI_FONT_SETUMEI_DOWN_3 + ACI_FONT_ID_OFFSET,	///<�Z4
	
	//�t�H���gOBJID��`�I��
	CELLID_ACI_FONT_ID_END,
	CELLID_ACI_FONT_END = CELLID_ACI_FONT_ID_END + ACI_FONT_ID_OFFSET,
};

//==============================================================================
//	�Z���A�j��ID
//==============================================================================
enum{
	CELLANMID_START = 33000,

	CELLANMID_JUDGE_0,
	CELLANMID_JUDGE_1,
	CELLANMID_JUDGE_2,

	CELLANMID_JUDGE_BOX,	///<�R���̓����Ă��锠

	CELLANMID_SPECIAL_HEART,	///<���ʐR�����ɂ���n�[�g
	CELLANMID_APPEAL_POINT,	///<�A�s�[���|�C���g�̓_����\���n�[�g
	CELLANMID_VOLTAGE_EFF,		///<�{���e�[�W���o
	CELLANMID_VOLTAGE_POINT,	///<�{���e�[�W�|�C���g�̓_����\�������v

	CELLANMID_NEXT_ICON,		///<���A�C�R��

	CELLANMID_WIN_COVER,		///<�E�B���h�E�X�N���[�����̃}�X�N�J�o�[

	CELLANMID_JUDGE_REACTION,	///<�R�����A�N�V�����A�C�R��

	//-- �T�u��� --//
	CELLANMID_CONTYPE_ICON,

	CELLANMID_SUB_HEART_8,		///<�Z�������̃n�[�g
	CELLANMID_SUB_HEART_32,		///<�����R�����o����R�����ɂ���n�[�g
	CELLANMID_SUB_CTYPE_ICON,	///<�R���e�X�g�^�C�v�A�C�R��
	CELLANMID_ACTIN_CURSOR,	///<���͉�ʃJ�[�\��

	//-- �t�H���gOBJ --//
	CELLANMID_ACI_FONT_JUDGE_1,		///<�R��1
	CELLANMID_ACI_FONT_JUDGE_2 = CELLANMID_ACI_FONT_JUDGE_1 + ACI_FONT_ID_OFFSET,		///<�R��2
	CELLANMID_ACI_FONT_JUDGE_3 = CELLANMID_ACI_FONT_JUDGE_2 + ACI_FONT_ID_OFFSET,		///<�R��3
	CELLANMID_ACI_FONT_JUDGE_4 = CELLANMID_ACI_FONT_JUDGE_3 + ACI_FONT_ID_OFFSET,	///<�R��4
	CELLANMID_ACI_FONT_WAZA_1 = CELLANMID_ACI_FONT_JUDGE_4 + ACI_FONT_ID_OFFSET,		///<�Z1
	CELLANMID_ACI_FONT_WAZA_2 = CELLANMID_ACI_FONT_WAZA_1 + ACI_FONT_ID_OFFSET,		///<�Z2
	CELLANMID_ACI_FONT_WAZA_3 = CELLANMID_ACI_FONT_WAZA_2 + ACI_FONT_ID_OFFSET,		///<�Z3
	CELLANMID_ACI_FONT_WAZA_4 = CELLANMID_ACI_FONT_WAZA_3 + ACI_FONT_ID_OFFSET,	///<�Z4
	CELLANMID_ACI_FONT_SETUMEI_UP_1 = 
		CELLANMID_ACI_FONT_WAZA_4 + ACI_FONT_ID_OFFSET,		///<�Z1
	CELLANMID_ACI_FONT_SETUMEI_UP_2 = 
		CELLANMID_ACI_FONT_SETUMEI_UP_1 + ACI_FONT_ID_OFFSET,	///<�Z2
	CELLANMID_ACI_FONT_SETUMEI_UP_3 = 
		CELLANMID_ACI_FONT_SETUMEI_UP_2 + ACI_FONT_ID_OFFSET,	///<�Z3
	CELLANMID_ACI_FONT_SETUMEI_UP_4 = 
		CELLANMID_ACI_FONT_SETUMEI_UP_3 + ACI_FONT_ID_OFFSET,	///<�Z4
	CELLANMID_ACI_FONT_SETUMEI_DOWN_1 = 
		CELLANMID_ACI_FONT_SETUMEI_UP_4 + ACI_FONT_ID_OFFSET,		///<�Z1
	CELLANMID_ACI_FONT_SETUMEI_DOWN_2 = 
		CELLANMID_ACI_FONT_SETUMEI_DOWN_1 + ACI_FONT_ID_OFFSET,	///<�Z2
	CELLANMID_ACI_FONT_SETUMEI_DOWN_3 = 
		CELLANMID_ACI_FONT_SETUMEI_DOWN_2 + ACI_FONT_ID_OFFSET,	///<�Z3
	CELLANMID_ACI_FONT_SETUMEI_DOWN_4 = 
		CELLANMID_ACI_FONT_SETUMEI_DOWN_3 + ACI_FONT_ID_OFFSET,	///<�Z4
	
	//�t�H���gOBJID��`�I��
	CELLANMID_ACI_FONT_ID_END,
	CELLANMID_ACI_FONT_END = CELLANMID_ACI_FONT_ID_END + ACI_FONT_ID_OFFSET,
};

//==============================================================================
//	�}���`�Z��ID
//==============================================================================
enum{
	MCELLID_START = 33000,
};

//==============================================================================
//	�}���`�Z���A�j��ID
//==============================================================================
enum{
	MCELLANMID_START = 33000,
};



#endif	//__ACTIN_ID_H__

