//============================================================================================
/**
 * @file	fieldmap_pri.h
 * @brief	�t�B�[���h�}�b�v���œ��삷��^�X�N�̃v���C�I���e�B��`
 */
//============================================================================================

#ifndef	__FIELDMAP_PRI_H__
#define	__FIELDMAP_PRI_H__

typedef enum {
	FLDMAP_PRI_POKETCH = 0,				///<�|�P�b�`

	FLDMAP_PRI_PLACENAME = 0,			///<�n���\���E�B���h�E

	FLDMAP_PRI_DIVMAP_MODEL = 1,		///<�n�`���f���f�[�^�ǂݍ���
	FLDMAP_PRI_DIVMAP_HEIGHT = 1,		///<�n�`�������f�[�^�ǂݍ���

	FLDMAP_PRI_MSGICON = 0,				///<�i�s�E�B���h�E�̃A�C�R������
	FLDMAP_PRI_SCRIPT_MENU = 0,			///<�X�N���v�g�Ăяo�����j���[
	FLDMAP_PRI_OBJSYS = 5,				///<���샂�f������̊�v���C�I���e�B

	FLDMAP_PRI_WEATHER_CHG = 0,			///<�V��V�X�e���F�ύX
	FLDMAP_PRI_WEATHER_DIVINIT = 1,		///<�V��V�X�e���F������
	FLDMAP_PRI_WEATHER_MAIN = 4,		///<�V��V�X�e���F���C��

	FLDMAP_PRI_ENCOUNT_EFF = 5,			///<�G���J�E���g�G�t�F�N�g
	FLDMAP_PRI_UG_CHG_EFF = 5,			///<�Y�z�ړ��G�t�F�N�g

	FLDMAP_PRI_UNION_MAIN = 10,			///<���j�I�����[������
	FLDMAP_PRI_UNION_VIEW = 11,			///<���j�I�����[���\��

	FLDMAP_PRI_UG_COMMON = 100,			///<�Y�z�̊�v���C�I���e�B

	FLDMAP_PRI_VOICE_CTRL = 0,			///<��������
	FLDMAP_PRI_QUICK_SAND	= 2,		///<�����A�j���Ď�
	FLDMAP_PRI_BASE_PANEL = 0,			///<�閧��n�p�l���J�[�\��
	FLDMAP_PRI_DEBUGPRINT	= 0x10000,
}FLDMAP_PRI;


#endif	/* __FIELDMAP_PRI_H__ */
