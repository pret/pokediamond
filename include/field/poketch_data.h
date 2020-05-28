//============================================================================================
/**
 * @file	poketch_data.h
 * @bfief	�|�P�b�`�f�[�^�A�N�Z�X�p�w�b�_
 * @author	taya GAME FREAK inc.
 * @date	2005.10.27
 */
//============================================================================================
#ifndef _POKETCH_DATA_H_
#define _POKETCH_DATA_H_

#include "system/savedata_def.h"	//SAVEDATA�Q�Ƃ̂���
#include "poketool/poke_tool.h"

#include "poketch_app_no.h"


//============================================================================================
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	�|�P�b�`�f�[�^�^��`
 */
//----------------------------------------------------------
typedef struct _POKETCH_DATA POKETCH_DATA;


//----------------------------------------------------------
/**
 * @brief	�|�P�b�`��ʃJ���[�^�C�v
 */
//----------------------------------------------------------
enum {
	POKETCH_COLOR_TYPE0,
	POKETCH_COLOR_TYPE1,
	POKETCH_COLOR_TYPE2,
	POKETCH_COLOR_TYPE3,
	POKETCH_COLOR_TYPE4,
	POKETCH_COLOR_TYPE5,
	POKETCH_COLOR_TYPE6,
	POKETCH_COLOR_TYPE7,

	POKETCH_COLOR_TYPE_MAX,
};

//----------------------------------------------------------
/**
 * @brief	�֘A�萔
 */
//----------------------------------------------------------
enum {
	POKETCH_MAP_MARK_MAX = 6,		///< �}�[�L���O�}�b�v�ň����}�[�N�̎��
	POKETCH_DOTART_DATA_BYTESIZE = 120,		// �h�b�g�A�[�g�f�[�^�T�C�Y�i24*20*2bit�j

	POKETCH_POKE_HISTORY_COUNT_MAX = 12,	// �|�P�����q�X�g���[�̋L�^����
};


//============================================================================================
//============================================================================================
//----------------------------------------------------------
//	�Z�[�u�f�[�^�V�X�e�����ˑ�����֐�
//----------------------------------------------------------
extern int PoketchData_GetWorkSize(void);
extern POKETCH_DATA * PoketchData_AllocWork(u32 heapID);

//----------------------------------------------------------
//	POKETCH_DATA����̂��߂̊֐�
//----------------------------------------------------------
extern void PoketchData_Init(POKETCH_DATA* poketch_data);
extern void PoketchData_SetPoketchGetFlag( POKETCH_DATA* poketch_data );
extern BOOL PoketchData_GetPoketchGetFlag( POKETCH_DATA* poketch_data );
extern int PoketchData_GetApplicationCount(const POKETCH_DATA * poketch_data);
extern int PoketchData_GetRestApplicationSpace( POKETCH_DATA* poketch_data );
extern BOOL PoketchData_AddApplication(POKETCH_DATA * poketch_data, int app_id);
extern int PoketchData_GetNowApplicationPos(const POKETCH_DATA* poketch_data);
extern int PoketchData_GetNowApplication(const POKETCH_DATA* poketch_data);
extern int PoketchData_SetApplicationPosNext( POKETCH_DATA* poketch_data );
extern int PoketchData_SetApplicationPosPrev( POKETCH_DATA* poketch_data );
extern void PoketchData_SetApplicationPos( POKETCH_DATA* poketch_data, int pos );
extern BOOL PoketchData_CheckApplicationRegisterd( POKETCH_DATA* poketch_data, int app_id );
extern u32  PoketchData_GetColorType( const POKETCH_DATA* poketch_data );
extern void PoketchData_SetColorType( POKETCH_DATA* poketch_data, u32 color_type );
extern u32  PoketchData_GetPedometer( const POKETCH_DATA* poketch_data );
extern void PoketchData_SetPedometer( POKETCH_DATA* poketch_data, u32 count );


extern BOOL PoketchData_GetAlarmSwitchFlag( const POKETCH_DATA* poketch_data );
extern void PoketchData_GetAlarmTime( const POKETCH_DATA* poketch_data, u32* hour, u32* min );
extern void PoketchData_SetAlarm( POKETCH_DATA* poketch_data, BOOL switch_flag, u32 hour, u32 min );


extern void PoketchData_Calendar_SetMark( POKETCH_DATA* poketch_data, u32 month, u32 day );
extern void PoketchData_Calendar_ClearMark( POKETCH_DATA* poketch_data, u32 month, u32 day );
extern BOOL PoketchData_Calendar_GetMark( const POKETCH_DATA* poketch_data, u32 month, u32 day );

extern void PoketchData_MarkMap_SetMarkPos( POKETCH_DATA* poketch_data, int id, u8 x, u8 y );
extern void PoketchData_MarkMap_GetMarkPos( const POKETCH_DATA* poketch_data, int id, u8* x, u8* y );

// �h�b�g�A�[�g
extern BOOL PoketchData_DotArt_GetModifiedFlag( const POKETCH_DATA* poketch_data );
extern void PoketchData_DotArt_GetBitData( const POKETCH_DATA* poketch_data, u8* dst );
extern void PoketchData_DotArt_SetBitData( POKETCH_DATA* poketch_data, const u8* src );

// �|�P�����q�X�g���[
extern void PoketchData_PokeHistory_Add( POKETCH_DATA* poketch_data, const POKEMON_PASO_PARAM* ppp );
extern int PoketchData_PokeHistory_GetRecordCount( const POKETCH_DATA* poketch_data );
extern void PoketchData_PokeHistory_GetRecord( const POKETCH_DATA* poketch_data, int index, int* monsno, int* iconPattern );


//----------------------------------------------------------
//	�Z�[�u�f�[�^�擾�̂��߂̊֐�
//----------------------------------------------------------
extern POKETCH_DATA * SaveData_GetPoketchData(SAVEDATA * sv);

//----------------------------------------------------------
//	�f�o�b�O�p
//----------------------------------------------------------
#ifdef PM_DEBUG
extern void PoketchData_AddAllApplication( POKETCH_DATA* poketch_data );
#endif


#endif //_POKETCH_DATA_H_
