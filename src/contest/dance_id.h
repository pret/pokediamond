//==============================================================================
/**
 * @file	dance_id.h
 * @brief	�_���X����Ŏg�p����A�N�^�[�̃L����ID���̒�`
 * @author	matsuda
 * @date	2005.12.12(��)
 */
//==============================================================================
#ifndef __DANCE_ID_H__
#define __DANCE_ID_H__


///�t�H���gOBJ��ID��`�ŁA�eID�Ԃŋ󂯂�ID��
#define DCI_FONT_ID_OFFSET		(10)


//==============================================================================
//	�L����ID
//==============================================================================
enum{
	D_CHARID_START = 33000,
	
	D_CHARID_MUSIC_BAR8,		///<�Ȃ̐i�s�������o�[
	D_CHARID_MUSIC_BAR32,
	D_CHARID_ONPU_B,			///<����(��)
	D_CHARID_ONPU_G,			///<����(��)
	D_CHARID_ONPU_R,			///<����(��)
	D_CHARID_ONPU_Y,			///<����(��)
	D_CHARID_REVIEW,			///<�]���p�l��
	D_CHARID_MY_CURSOR,			///<�������w���J�[�\��
	D_CHARID_PRIN,				///<�v����
	D_CHARID_SHADOW,			///<�e
	D_CHARID_SPOTLIGHT,			///<�X�|�b�g���C�g
	D_CHARID_STAR,				///<��
	

	//-- �T�u��� --//
	
	
	//-- �t�H���gOBJ --//
	D_CHARID_DCI_FONT_FORWARD,		///<�܂�
	D_CHARID_DCI_FONT_BACK = D_CHARID_DCI_FONT_FORWARD + DCI_FONT_ID_OFFSET,	///<������
	D_CHARID_DCI_FONT_LEFT = D_CHARID_DCI_FONT_BACK + DCI_FONT_ID_OFFSET,		///<�Ђ���
	D_CHARID_DCI_FONT_RIGHT = D_CHARID_DCI_FONT_LEFT + DCI_FONT_ID_OFFSET,		///<�݂�
	
	//�t�H���gOBJID��`�I��
	D_CHARID_DCI_FONT_ID_END,
	D_CHARID_DCI_FONT_END = D_CHARID_DCI_FONT_ID_END + DCI_FONT_ID_OFFSET,
};

//==============================================================================
//	�p���b�gID
//==============================================================================
enum{
	D_PLTTID_START = 33000,

	D_PLTTID_OBJ_COMMON,	///<�풓OBJ�p���b�g
	
	//-- �T�u��� --//
	D_PLTTID_OBJ_COMMON_SUB,	///<�T�u��ʂ̏풓OBJ�p���b�g
	D_PLTTID_SUB_FONTACT,		///<�T�u��ʂ̃t�H���gOBJ�p�p���b�g
};

//--------------------------------------------------------------
//	�풓OBJ�p���b�g�I�t�Z�b�g
//--------------------------------------------------------------
enum{
	PALOFS_MUSIC_BAR = 0,		///<2006.03.14(��) ���ݖ��g�p
	PALOFS_ONPU_B = 2,
	PALOFS_ONPU_G = 2,
	PALOFS_ONPU_R = 7,
	PALOFS_ONPU_Y = 6,
	PALOFS_REVIEW = 3,
	PALOFS_MY_CURSOR = 1,
	PALOFS_PRIN = 5,
	PALOFS_SHADOW = 1,
	PALOFS_SPOTLIGHT = 4,
	PALOFS_STAR = 3,
	
	DANCE_COMMON_PAL_NUM = 8,	///<�풓OBJ�p���b�g�̖{��
};

//--------------------------------------------------------------
//	�T�u��ʂ̏풓OBJ�p���b�g�I�t�Z�b�g
//--------------------------------------------------------------
enum{
	
	DANCE_SUB_COMMON_PAL_NUM = 2,	///<�T�u��ʂ̏풓OBJ�p���b�g�̖{��
};

//==============================================================================
//	�Z��ID
//==============================================================================
enum{
	D_CELLID_START = 33000,

	D_CELLID_MUSIC_BAR8,		///<�Ȃ̐i�s�������o�[
	D_CELLID_MUSIC_BAR32,
	D_CELLID_ONPU,				///<����
	D_CELLID_REVIEW,			///<�]���p�l��
	D_CELLID_MY_CURSOR,			///<�������w���J�[�\��
	D_CELLID_PRIN,				///<�v����
	D_CELLID_SHADOW,			///<�e
	D_CELLID_SPOTLIGHT,			///<�X�|�b�g���C�g
	D_CELLID_STAR,				///<��


	//-- �T�u��� --//
	
	
	//-- �t�H���gOBJ --//
	D_CELLID_DCI_FONT_FORWARD,		///<�܂�
	D_CELLID_DCI_FONT_BACK = D_CELLID_DCI_FONT_FORWARD + DCI_FONT_ID_OFFSET,	///<������
	D_CELLID_DCI_FONT_LEFT = D_CELLID_DCI_FONT_BACK + DCI_FONT_ID_OFFSET,		///<�Ђ���
	D_CELLID_DCI_FONT_RIGHT = D_CELLID_DCI_FONT_LEFT + DCI_FONT_ID_OFFSET,		///<�݂�
	
	//�t�H���gOBJID��`�I��
	D_CELLID_DCI_FONT_ID_END,
	D_CELLID_DCI_FONT_END = D_CELLID_DCI_FONT_ID_END + DCI_FONT_ID_OFFSET,
};

//==============================================================================
//	�Z���A�j��ID
//==============================================================================
enum{
	D_CELLANMID_START = 33000,

	D_CELLANMID_MUSIC_BAR8,		///<�Ȃ̐i�s�������o�[
	D_CELLANMID_MUSIC_BAR32,
	D_CELLANMID_ONPU,			///<����
	D_CELLANMID_REVIEW,			///<�]���p�l��
	D_CELLANMID_MY_CURSOR,			///<�������w���J�[�\��
	D_CELLANMID_PRIN,				///<�v����
	D_CELLANMID_SHADOW,			///<�e
	D_CELLANMID_SPOTLIGHT,			///<�X�|�b�g���C�g
	D_CELLANMID_STAR,				///<��


	//-- �T�u��� --//
	
	
	//-- �t�H���gOBJ --//
	D_CELLANMID_DCI_FONT_FORWARD,		///<�܂�
	D_CELLANMID_DCI_FONT_BACK = D_CELLANMID_DCI_FONT_FORWARD + DCI_FONT_ID_OFFSET,	///<������
	D_CELLANMID_DCI_FONT_LEFT = D_CELLANMID_DCI_FONT_BACK + DCI_FONT_ID_OFFSET,		///<�Ђ���
	D_CELLANMID_DCI_FONT_RIGHT = D_CELLANMID_DCI_FONT_LEFT + DCI_FONT_ID_OFFSET,		///<�݂�
	
	//�t�H���gOBJID��`�I��
	D_CELLANMID_DCI_FONT_ID_END,
	D_CELLANMID_DCI_FONT_END = D_CELLANMID_DCI_FONT_ID_END + DCI_FONT_ID_OFFSET,
};

//==============================================================================
//	�}���`�Z��ID
//==============================================================================
enum{
	D_MCELLID_START = 33000,
};

//==============================================================================
//	�}���`�Z���A�j��ID
//==============================================================================
enum{
	D_MCELLANMID_START = 33000,
};



#endif	//__DANCE_ID_H__

