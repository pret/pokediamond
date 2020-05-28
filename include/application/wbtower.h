//============================================================================================
/**
 * @file	wbtower.h
 * @bfief	WIFI�o�g���^���[�ڑ����
 * @author	Akito Mori
 * @date	06.05.15
 */
//============================================================================================
#ifndef _WBTOWER_H_
#define _WBTOWER_H_

#include <dwc.h>
#include "savedata/system_data.h"
#include "savedata/b_tower.h"
#include "savedata/config.h"
#include "wbtower_def.h"

//============================================================================================
//	��`
//============================================================================================

// �v���Z�X��`�f�[�^
extern PROC_RESULT WBTowerProc_Init( PROC * proc, int * seq );
extern PROC_RESULT WBTowerProc_Main( PROC * proc, int * seq );
extern PROC_RESULT WBTowerProc_End ( PROC * proc, int * seq );


// �ڑ����[�h
enum{
	WIFI_BTOWER_MODE_DOWNLOAD=0,			// ���[���f�[�^�_�E�����[�h
	WIFI_BTOWER_MODE_UPLOAD,				// ���ʃ_�E�����[�h
	WIFI_BTOWER_MODE_LEADER,				// ���[�_�[�f�[�^�_�E�����[�h
};


// �|�C���^�Q�Ƃ����ł���WIFI�o�g���^���[���[�N�\����
typedef struct WBTOWER_WORK WBTOWER_WORK;	


typedef struct{
	BTLTOWER_SCOREWORK	*btowerscore;		// �o�g���^���[���уf�[�^
	BTLTOWER_WIFI_DATA	*wifitowerdata;		// WIFI�o�g���^���[�f�[�^�|�C���^
	SYSTEMDATA			*systemdata;		// �V�X�e���Z�[�u�f�[�^�iDPW���C�u�����p�Ƃ������R�[�h��ۑ��j
	SAVEDATA			*savedata;			// �Z�[�u�f�[�^�|�C���^
	CONFIG				*config;			// �R���t�B�O�\����
	DWCUserData			*MyUserData;		// �F�؍ς݂�DWCUSER�f�[�^�������Ȃ��͂�
	int					mode;				// WIFI�o�g���^���[�ڑ����[�h
	int					profileId;			// GameSpy�v���t�@�C��ID
	int					result;				// �q�������ʂ����ĕԂ�
	int					connect;			// ����f�r�h�c���擾�����i1:�擾���Ă��� 0:���������Ă�)
}WBTOWER_PARAM;

#endif	/* _WBTOWER_H_ */