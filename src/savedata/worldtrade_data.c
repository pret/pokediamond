//============================================================================================
/**
 * @file	worldtrade_data.c
 * @brief	世界交換セーブデータ
 * @author	mori GAME FREAK inc.
 * @date	2006.04.30
 */
//============================================================================================

#include "savedata/savedata_def.h"	//SAVEDATA参照のため

#include "common.h"

#include "system/gamedata.h"
#include "savedata/savedata.h"

#include "savedata/worldtrade_data.h"

#define POKEMON_DATA_SIZE		(236)

//============================================================================================
//============================================================================================

struct WORLDTRADE_DATA{
	u8 PokemonData[POKEMON_DATA_SIZE];	// 預けたポケモンのデータ
	u16 		flag;					// 預けているかフラグ
	u16 		toBox;					// ボックスＮＯ（手持ちの場合はRETURN_POSITION_TEMOTI）
	GF_DATE		lastExchangeDate;		// 最終交換日付
};



//============================================================================================
//
//	セーブデータシステムが依存する関数
//
//============================================================================================
WORLDTRADE_DATA * SaveData_GetWorldTradeData(SAVEDATA * sv)
{
	return SaveData_Get(sv, GMDATA_ID_WORLDTRADEDATA);
}


//----------------------------------------------------------
/**
 * @brief	自分状態保持ワークのサイズ取得
 * @return	int		サイズ（バイト単位）
 */
//----------------------------------------------------------
int WorldTradeData_GetWorkSize(void)
{
	return sizeof(WORLDTRADE_DATA);
}

//==============================================================================
/**
 * $brief   世界交換状態保存データの確保
 *
 * @param   heapID		
 *
 * @retval  WORLDTRADE_DATA *		
 */
//==============================================================================
WORLDTRADE_DATA * WorldTradeData_AllocWork(u32 heapID)
{
	WORLDTRADE_DATA * WorldTradeData;
	WorldTradeData = sys_AllocMemory(heapID, sizeof(WORLDTRADE_DATA));
	
	WorldTradeData_Init( WorldTradeData );

	return WorldTradeData;
	
}

//==============================================================================
/**
 * $brief   データ初期化
 *
 * @param   randomgroup		
 *
 * @retval  none		
 */
//==============================================================================
void WorldTradeData_Init(WORLDTRADE_DATA * WorldTradeData )
{
	
	MI_CpuClearFast(WorldTradeData, sizeof(WORLDTRADE_DATA));
	
}


//==============================================================================
/**
 * $brief   預けているか？
 *
 * @param   WorldTradeData		
 *
 * @retval  int		0:預けていない	1:預けている
 */
//==============================================================================
int  WorldTradeData_GetFlag( WORLDTRADE_DATA* WorldTradeData )
{
	return WorldTradeData->flag;
}
//==============================================================================
/**
 * $brief   預けているフラグの操作
 *
 * @param   WorldTradeData		
 *
 * @retval  int		
 */
//==============================================================================
void  WorldTradeData_SetFlag( WORLDTRADE_DATA* WorldTradeData, int flag )
{
	WorldTradeData->flag = flag;
}


//==============================================================================
/**
 * $brief   ポケモンデータを取り出す
 *
 * @param   WorldTradeData		
 * @param   poke		
 *
 * @retval  none		
 */
//==============================================================================
void  WorldTradeData_GetPokemonData( WORLDTRADE_DATA* WorldTradeData, POKEMON_PARAM *poke )
{
	MI_CpuCopyFast( WorldTradeData->PokemonData, (void*)poke, POKEMON_DATA_SIZE );
}

//==============================================================================
/**
 * $brief   ポケモンを預けたので、コピーを保存しておく
 *
 * @param   WorldTradeData		
 * @param   poke		
 *
 * @retval  none		
 */
//==============================================================================
void  WorldTradeData_SetPokemonData( WORLDTRADE_DATA* WorldTradeData, POKEMON_PARAM *poke, int boxno )
{
	MI_CpuCopyFast( (void*)poke, WorldTradeData->PokemonData, POKEMON_DATA_SIZE );
}


//==============================================================================
/**
 * $brief   交換が成立した最後の日を得る
 *
 * @param   WorldTradeData		
 *
 * @retval  int		0:預けていない	1:預けている
 */
//==============================================================================
GF_DATE  WorldTradeData_GetLastDate( WORLDTRADE_DATA* WorldTradeData )
{
	return WorldTradeData->lastExchangeDate;
}
//==============================================================================
/**
 * $brief   交換が成立した最後の日を記録する
 *
 * @param   WorldTradeData		
 *
 * @retval  int		
 */
//==============================================================================
void  WorldTradeData_SetLastDate( WORLDTRADE_DATA* WorldTradeData, GF_DATE date )
{
	WorldTradeData->lastExchangeDate = date;
}

//==============================================================================
/**
 * @brief   ポケモンが預けられているBOXNO（てもちはRETURN_POSITION_TEMOTI）取得
 *
 * @param   WorldTradeData		
 *
 * @retval  int		
 */
//==============================================================================
int WorldTradeData_GetBoxNo( WORLDTRADE_DATA* WorldTradeData )
{
	return WorldTradeData->toBox;
}

