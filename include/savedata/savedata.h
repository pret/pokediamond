//=============================================================================
/**
 * @file	savedata.h
 * @brief	�Z�[�u�f�[�^�p�w�b�_
 * @author	tamada	GAME FREAK Inc.
 * @date	2005.10.12
 *
 * ���̃w�b�_�̓Z�[�u�f�[�^�̐��������ȂǁA���ڃZ�[�u�f�[�^�ɂ�����镔���ɂ̂ݕK�v�B
 * ����ȊO�̉ӏ��ł�savedata_def.h��SAVEDATA�^�o�R�ŃA�N�Z�X�ł���΂悢�B
 * ���̂��߁A���̃w�b�_���C���N���[�h����ӏ��͌��肳���͂�
 */
//=============================================================================
#ifndef	__SAVEDATA_H__
#define	__SAVEDATA_H__

#include "savedata/savedata_def.h"

//---------------------------------------------------------------------------
///	�Z�[�u�Ɏg�p���Ă���Z�N�^��
//---------------------------------------------------------------------------
#define	SAVE_PAGE_MAX		(32)

#define	SAVE_SECTOR_SIZE	(0x1000)

//�ȉ��̓f�o�b�O�c�[���p�̃Z�[�u�̈�ł� by soga
#define	POKE_ANM_SAVE		(60*SAVE_SECTOR_SIZE)		//�|�P�����A�j���c�[���p�Z�[�u�̈�
#define	DEBUG_FIGHT_SAVE	(63*SAVE_SECTOR_SIZE)		//�f�o�b�O�t�@�C�g�p�Z�[�u�̈�

//---------------------------------------------------------------------------
///	�Z�[�u�u���b�N�̒�`
//---------------------------------------------------------------------------
typedef enum {
	SVBLK_ID_NORMAL = 0,	///<�ʏ�Q�[���i�s�f�[�^
	SVBLK_ID_BOX,			///<�|�P�����{�b�N�X

	SVBLK_ID_MAX,
}SVBLK_ID;

//---------------------------------------------------------------------------
///	�Z�[�u���ڂ̒�`
//---------------------------------------------------------------------------
typedef enum {
	//�m�[�}���f�[�^�O���[�v
	GMDATA_ID_SYSTEM_DATA,
	GMDATA_ID_PLAYER_DATA,
	GMDATA_ID_TEMOTI_POKE,
	GMDATA_ID_TEMOTI_ITEM,
	GMDATA_ID_EVENT_WORK,
	GMDATA_ID_POKETCH_DATA,
	GMDATA_ID_SITUATION,
	GMDATA_ID_ZUKANWORK,
	GMDATA_ID_SODATEYA,
	GMDATA_ID_FRIEND,
	GMDATA_ID_MISC,
	GMDATA_ID_FIELDOBJSV,
	GMDATA_ID_UNDERGROUNDDATA,
    GMDATA_ID_REGULATION,
	GMDATA_ID_IMAGECLIPDATA,
	GMDATA_ID_MAILDATA,
	GMDATA_ID_PORUTODATA,
	GMDATA_ID_RANDOMGROUP,
	GMDATA_ID_FNOTE,
	GMDATA_ID_TRCARD,
	GMDATA_ID_RECORD,
	GMDATA_ID_CUSTOM_BALL,
	GMDATA_ID_PERAPVOICE,
	GMDATA_ID_BTLTOWER,
	GMDATA_ID_SP_RIBBON,
	GMDATA_ID_ENCOUNT,
	GMDATA_ID_WORLDTRADEDATA,
	GMDATA_ID_TVWORK,
	GMDATA_ID_GUINNESS,
	GMDATA_ID_WIFILIST,
	GMDATA_ID_WIFIHISTORY,
	GMDATA_ID_FUSHIGIDATA,
	GMDATA_ID_POKEPARKDATA,
	GMDATA_ID_CONTEST,
	GMDATA_ID_PMS,

	//�{�b�N�X�f�[�^�O���[�v
	GMDATA_ID_BOXDATA,

	GMDATA_ID_MAX,
}GMDATA_ID;

//---------------------------------------------------------------------------
/**
 * @brief	�O���Z�[�u�f�[�^��ID��`
 */
//---------------------------------------------------------------------------
typedef enum {
	EXDATA_ID_DENDOU,			///<�a������f�[�^
	EXDATA_ID_FUSHIGIDATA,		///<�ӂ����Ȃ�������̃f�[�^
	EXDATA_ID_MAX,
}EXDATA_ID;


//============================================================================================
//============================================================================================
//---------------------------------------------------------------------------
//	�t���b�V���A�N�Z�X�p�֐�
//	���f�o�b�O�p�r�ȊO�ł�SaveData_�`���ĂԂ͂��Ȃ̂ŁA�ʏ�͒��ڎg��Ȃ��B
//---------------------------------------------------------------------------
extern BOOL PMSVLD_Init(void);
extern BOOL PMSVLD_Save(u32 src, void * dst, u32 len);
extern BOOL PMSVLD_Load(u32 src, void * dst, u32 len);


//---------------------------------------------------------------------------
//	�Z�[�u�f�[�^����֐�
//---------------------------------------------------------------------------
//�Z�[�u���[�h�V�X�e��������
extern SAVEDATA * SaveData_System_Init(void);

//�t���b�V�����݃`�F�b�N
extern BOOL SaveData_GetFlashExistsFlag(const SAVEDATA * sv);

//���[�h����
extern BOOL SaveData_Load(SAVEDATA * sv);
//�Z�[�u����
extern SAVE_RESULT SaveData_Save(SAVEDATA * sv);
//��������
extern BOOL SaveData_Erase(SAVEDATA * sv);
//�����Z�[�u����
extern SAVE_RESULT SaveData_SaveParts(SAVEDATA * sv, SVBLK_ID id);
//�Z�[�u�f�[�^�������i�������܂Ȃ��j
extern void SaveData_ClearData(SAVEDATA * sv);

//�ŏ��̓ǂݍ��ݎ��̃Z�[�u�f�[�^��Ԏ擾
extern LOAD_RESULT SaveData_GetLoadResult(const SAVEDATA * sv);

//�����f�[�^�ւ̐V�K�f�[�^�㏑���`�F�b�N
extern BOOL SaveData_IsOverwritingOtherData(const SAVEDATA * sv);
//�V�K�f�[�^���ǂ����̔��ʃt���O�擾
extern BOOL SaveData_GetNewDataFlag(const SAVEDATA * sv);
//�f�[�^�����݂��邩�ǂ����̔��ʃt���O�擾
extern BOOL SaveData_GetExistFlag(const SAVEDATA * sv);

//�S�̃Z�[�u���K�v���ǂ����̔��ʃt���O�擾
extern BOOL SaveData_GetTotalSaveFlag(const SAVEDATA * sv);

//�S�̃Z�[�u���N�G�X�g�t���O�Z�b�g
extern void SaveData_RequestTotalSave(void);

//�����Z�[�u�F������
extern void SaveData_DivSave_Init(SAVEDATA * sv, int BlockID);
//�����Z�[�u�F���C��
extern SAVE_RESULT SaveData_DivSave_Main(SAVEDATA * sv);
//�����Z�[�u�F�L�����Z��
extern void SaveData_DivSave_Cancel(SAVEDATA * sv);


//---------------------------------------------------------------------------
//	�Z�[�u�f�[�^�A�N�Z�X�p�֐�
//---------------------------------------------------------------------------
extern void * SaveData_Get(SAVEDATA * sv, GMDATA_ID gmdataID);
extern const void * SaveData_GetReadOnlyData(const SAVEDATA * sv, GMDATA_ID gmdataID);


//---------------------------------------------------------------------------
//	�f�o�b�O�p�֐�
//	���Ȃ��g���Ă͂����܂���B
//---------------------------------------------------------------------------
extern SAVEDATA * SaveData_GetPointer(void);

// �C���f�b�N�X����鎞�̂ݗL��
// �ʏ��OFF�Ȃ̂�ON�ɂȂ��Ă�̂��������疳������OFF�ŗǂ�
//#define CREATE_INDEX

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------


#endif	/* __SAVEDATA_H__ */
