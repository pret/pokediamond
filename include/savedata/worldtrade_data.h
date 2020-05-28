//============================================================================================
/**
 * @file	worldtrade_data.h
 * @brief
 * @date	2006.04.30
 * @author	mori GameFreak inc.
 */
//============================================================================================

#ifndef	__WORLDTRADE_DATA_H__
#define	__WORLDTRADE_DATA_H__

#include "savedata/savedata_def.h"
#include "poketool/poke_tool.h"
#include "gflib/gf_date.h"

#define RETURN_POSITION_TEMOTI	( 18 )

//----------------------------------------------------------
/**
 * @brief	WORLDTRADE_DATA への不完全型定義
 */
//----------------------------------------------------------
typedef struct WORLDTRADE_DATA WORLDTRADE_DATA;

//世界交換データの取得
extern WORLDTRADE_DATA * SaveData_GetWorldTradeData(SAVEDATA * sv);

extern int   WorldTradeData_GetWorkSize(void);
extern WORLDTRADE_DATA * WorldTradeData_AllocWork(u32 heapID);
extern void  WorldTradeData_Init(WORLDTRADE_DATA *WorldTradeData );
extern int   WorldTradeData_GetFlag( WORLDTRADE_DATA* WorldTradeData );
extern void  WorldTradeData_SetFlag( WORLDTRADE_DATA* WorldTradeData, int flag );
extern void  WorldTradeData_GetPokemonData( WORLDTRADE_DATA* WorldTradeData, POKEMON_PARAM *poke );
extern void  WorldTradeData_SetPokemonData( WORLDTRADE_DATA* WorldTradeData, POKEMON_PARAM *poke, int box );
extern void  WorldTradeData_SetLastDate( WORLDTRADE_DATA* WorldTradeData, GF_DATE date );
extern GF_DATE  WorldTradeData_GetLastDate( WORLDTRADE_DATA* WorldTradeData );
extern int   WorldTradeData_GetBoxNo( WORLDTRADE_DATA* WorldTradeData );


#endif	/* __WORLDTRADE_DATA_H__ */

