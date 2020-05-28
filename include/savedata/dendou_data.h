//============================================================================================
/**
 * @file	dendou_data.h
 * @brief	�a������Z�[�u�f�[�^
 * @author	taya
 * @date	2006.04.20
 */
//============================================================================================
#ifndef __DENDOU_DATA_H__
#define __DENDOU_DATA_H__

#include "savedata\savedata_def.h"
#include "poketool\pokeparty.h"
#include "gflib\strbuf.h"


//--------------------------------------------------------------
/**
 *	�֘A�萔
 */
//--------------------------------------------------------------
enum {
	DENDOU_RECORD_MAX = 30,		// �Z�[�u�̈�ɕۑ������a������f�[�^�̍ő匏��
	DENDOU_NUMBER_MAX = 9999,	// �f�[�^�ǉ������ʎZ�񐔂̍ő�i����ȏ�͓a�����肵�Ă��ǉ�����Ȃ��j
};

//--------------------------------------------------------------
/**
 *	�a������Z�[�u�f�[�^�̕s���S�^�\���̐錾
 */
//--------------------------------------------------------------
typedef struct _DENDOU_SAVEDATA		DENDOU_SAVEDATA;


//--------------------------------------------------------------
/**
 *	�a������Z�[�u�f�[�^����|�P�����f�[�^���擾���邽�߂̍\����
 *�i������󂯎��p�� STRBUF �͍쐬���Ă������ƁI�j
 */
//--------------------------------------------------------------
typedef struct {
	STRBUF*		nickname;
	STRBUF*		oyaname;

	u32			personalRandom;
	u32			idNumber;
	u16			monsno;
	u8			level;
	u8			formNumber;

	u16			waza[4];

}DENDOU_POKEMON_DATA;







extern int DendouData_GetWorkSize( void );
extern void DendouData_Init( DENDOU_SAVEDATA* data );

//extern DENDOU_SAVEDATA* SaveData_GetDendouData( SAVEDATA* sv );
//�a������f�[�^�͒ʏ�Z�[�u�f�[�^�łȂ����߁A�A�N�Z�X���ɂ͉��L�֐����g�p���ăt���b�V������ǂݏ�������
extern DENDOU_SAVEDATA * SaveData_Extra_LoadDendouData(SAVEDATA * sv,
		int heap_id, LOAD_RESULT * result);
extern SAVE_RESULT SaveData_Extra_SaveDendouData(SAVEDATA * sv, DENDOU_SAVEDATA * data);


//------------------------------------------------------------------
/**
 * �a������f�[�^�P���ǉ�
 *
 * @param   data		�a������Z�[�u�f�[�^�|�C���^
 * @param   party		�a������p�[�e�B�[�̃f�[�^
 * @param   date		�a��������t�f�[�^
 *
 */
//------------------------------------------------------------------
extern void DendouData_AddRecord( DENDOU_SAVEDATA* data, const POKEPARTY* party, const RTCDate* date );




extern u32 DendouData_GetRecordCount( const DENDOU_SAVEDATA* data );
extern u32 DendouData_GetRecordNumber( const DENDOU_SAVEDATA* data, int index );
extern u32 DendouData_GetPokemonCount( const DENDOU_SAVEDATA* data, int index );
extern void DendouData_GetPokemonData( const DENDOU_SAVEDATA* data, int index, int poke_pos, DENDOU_POKEMON_DATA* poke_data );
extern void DendouData_GetDate( const DENDOU_SAVEDATA* data, int index, RTCDate* date );




#endif
