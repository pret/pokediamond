//============================================================================================
/**
 * @file	savedata_local.h
 * @brief
 * @date	2006.04.17
 * @author	tamada GAME FREAK inc.
 */
//============================================================================================

#ifndef	__SAVEDATA_LOCAL_H__
#define	__SAVEDATA_LOCAL_H__

#include "savedata/savedata.h"

#ifdef	PM_DEBUG
//���̒�`��L���ɂ���ƃt���b�V���̃G���[�`�F�b�N�������ɂȂ�
//�f�o�b�O���ԗp�Ȃ̂Ő��i�łł͔ɉh�����Ȃ����ƁI
//#define	DISABLE_FLASH_CHECK
#endif

//=============================================================================
//=============================================================================

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
typedef int (*FUNC_GET_SIZE)(void);

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
typedef void (*FUNC_INIT_WORK)(void *);

//---------------------------------------------------------------------------
/**
 * @brief	�Z�[�u�f�[�^���e�f�[�^�p�̍\���̒�`
 */
//---------------------------------------------------------------------------
typedef struct {
	GMDATA_ID gmdataID;				///<�Z�[�u�f�[�^����ID
	SVBLK_ID	blockID;
	FUNC_GET_SIZE get_size;			///<�Z�[�u�f�[�^�T�C�Y�擾�֐�
	FUNC_INIT_WORK	init_work;		///<�Z�[�u�f�[�^�������֐�
}SAVEDATA_TABLE;


//---------------------------------------------------------------------------
/**
 * @brief	����Z�[�u�f�[�^��`�f�[�^�̍\���̒�`
 */
//---------------------------------------------------------------------------
typedef struct {
	EXDATA_ID id;					///<����Z�[�u�f�[�^����ID
	u32 sector;						///<�J�n�Z�N�^
	FUNC_GET_SIZE get_size;			///<�f�[�^�T�C�Y�擾�֐�
	FUNC_INIT_WORK init_work;		///<�Z�[�u�f�[�^�������֐�
}EXSAVEDATA_TABLE;

//=============================================================================
//=============================================================================

extern const SAVEDATA_TABLE SaveDataTable[];
extern const int SaveDataTableMax;

extern const EXSAVEDATA_TABLE ExtraSaveDataTable[];
extern const int ExtraSaveDataTableMax;

extern SAVE_RESULT SaveData_Extra_Save(const SAVEDATA * sv, EXDATA_ID id, void * data);
extern void * SaveData_Extra_LoadAlloc(SAVEDATA * sv,
		int heap_id, EXDATA_ID id, LOAD_RESULT * result);




#endif	/* __SAVEDATA_LOCAL_H__ */
