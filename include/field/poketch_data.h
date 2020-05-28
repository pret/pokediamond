//============================================================================================
/**
 * @file	poketch_data.h
 * @bfief	ポケッチデータアクセス用ヘッダ
 * @author	taya GAME FREAK inc.
 * @date	2005.10.27
 */
//============================================================================================
#ifndef _POKETCH_DATA_H_
#define _POKETCH_DATA_H_

#include "system/savedata_def.h"	//SAVEDATA参照のため
#include "poketool/poke_tool.h"

#include "poketch_app_no.h"


//============================================================================================
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	ポケッチデータ型定義
 */
//----------------------------------------------------------
typedef struct _POKETCH_DATA POKETCH_DATA;


//----------------------------------------------------------
/**
 * @brief	ポケッチ画面カラータイプ
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
 * @brief	関連定数
 */
//----------------------------------------------------------
enum {
	POKETCH_MAP_MARK_MAX = 6,		///< マーキングマップで扱うマークの種類
	POKETCH_DOTART_DATA_BYTESIZE = 120,		// ドットアートデータサイズ（24*20*2bit）

	POKETCH_POKE_HISTORY_COUNT_MAX = 12,	// ポケモンヒストリーの記録件数
};


//============================================================================================
//============================================================================================
//----------------------------------------------------------
//	セーブデータシステムが依存する関数
//----------------------------------------------------------
extern int PoketchData_GetWorkSize(void);
extern POKETCH_DATA * PoketchData_AllocWork(u32 heapID);

//----------------------------------------------------------
//	POKETCH_DATA操作のための関数
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

// ドットアート
extern BOOL PoketchData_DotArt_GetModifiedFlag( const POKETCH_DATA* poketch_data );
extern void PoketchData_DotArt_GetBitData( const POKETCH_DATA* poketch_data, u8* dst );
extern void PoketchData_DotArt_SetBitData( POKETCH_DATA* poketch_data, const u8* src );

// ポケモンヒストリー
extern void PoketchData_PokeHistory_Add( POKETCH_DATA* poketch_data, const POKEMON_PASO_PARAM* ppp );
extern int PoketchData_PokeHistory_GetRecordCount( const POKETCH_DATA* poketch_data );
extern void PoketchData_PokeHistory_GetRecord( const POKETCH_DATA* poketch_data, int index, int* monsno, int* iconPattern );


//----------------------------------------------------------
//	セーブデータ取得のための関数
//----------------------------------------------------------
extern POKETCH_DATA * SaveData_GetPoketchData(SAVEDATA * sv);

//----------------------------------------------------------
//	デバッグ用
//----------------------------------------------------------
#ifdef PM_DEBUG
extern void PoketchData_AddAllApplication( POKETCH_DATA* poketch_data );
#endif


#endif //_POKETCH_DATA_H_
