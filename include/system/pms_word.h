//============================================================================================
/**
 * @file	pms_word.h
 * @bfief	�ȈՉ�b�p�P��f�[�^��舵��
 * @author	taya
 * @date	06.01.20
 */
//============================================================================================
#ifndef __PMS_WORD_H__
#define __PMS_WORD_H__

#include "system\pms_data.h"

typedef struct _PMSW_MAN	PMSW_MAN;


extern PMSW_MAN* PMSW_MAN_Create(u32 heapID);
extern void PMSW_MAN_Delete( PMSW_MAN* man );
extern void PMSW_MAN_CopyStr( PMSW_MAN* man, PMS_WORD  pms_word, STRBUF* buf );
extern void PMSW_GetStr( PMS_WORD pms_word, STRBUF* dst );
extern PMS_WORD  PMSW_GetWordNumberByGmmID( u32 gmmID, u32 wordID );


extern int PMSW_GetDupWordCount( PMS_WORD word );
extern PMS_WORD PMSW_GetDupWord( PMS_WORD word, int idx );


//===================================================================================
// �Z�[�u�f�[�^����
//===================================================================================
#include "savedata\savedata.h"

typedef struct _PMSW_SAVEDATA	PMSW_SAVEDATA;

//--------------------------------------------------
/**
 *	�e�����������Ƃ΂�ID
 *	�igmm�ƘA�����Ă��邽�ߏ��Ԃ͌Œ�j
 */
//--------------------------------------------------
typedef enum {
	PMSW_AISATSU_JP,	// ���{��
	PMSW_AISATSU_EN,	// �p��
	PMSW_AISATSU_FR,	// �t�����X��
	PMSW_AISATSU_IT,	// �C�^���A��
	PMSW_AISATSU_GE,	// �h�C�c��
	PMSW_AISATSU_SP,	// �X�y�C����

	PMSW_AISATSU_HIDE_MAX,
}PMSW_AISATSU_ID;


//--------------------------------------------------
/**
 *	������Ƃ΂̍ő吔
 */
//--------------------------------------------------
enum {
	PMSW_NANKAI_WORD_MAX = 32,
};


extern PMSW_SAVEDATA* SaveData_GetPMSW( SAVEDATA* sv );

extern BOOL PMSW_GetNankaiFlag( const PMSW_SAVEDATA* saveData, u32 id );
extern u32 PMSW_SetNewNankaiWord( PMSW_SAVEDATA* saveData );
extern PMS_WORD  PMSW_NankaiWord_to_PMSWORD( u32 id );
extern BOOL PMSW_GetAisatsuFlag( const PMSW_SAVEDATA* saveData, PMSW_AISATSU_ID id );
extern BOOL PMSW_CheckNankaiWordComplete( PMSW_SAVEDATA* saveData );
extern void PMSW_SetAisatsuFlag( PMSW_SAVEDATA* saveData, PMSW_AISATSU_ID id );



// �Z�[�u�f�[�^�����V�X�e���p
extern u32 PMSW_GetSaveDataSize(void);
extern void PMSW_InitSaveData( void* work );


#endif

