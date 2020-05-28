//==============================================================================
/**
 *
 *@file		boxdata.h
 *@brief	ポケモンボックスデータ管理
 *@author	taya
 *@data		2005.09.8
 *
 */
//==============================================================================
#ifndef __BOXDATA_H__
#define __BOXDATA_H__

#include  "system\savedata_def.h"
#include  "gflib\strbuf.h"
#include  "poketool\poke_tool.h"	// POKEMON_PASO_PARAM 参照のため

//------------------------------------------------------------
/**
 * @brief	ボックスデータ参照用不完全型ポインタ
 *
 *   これのポインタ経由で処理を行う
 */
//------------------------------------------------------------
typedef struct _BOX_DATA	BOX_DATA;

//------------------------------------------------------------
/**
 *   定数
 */
//------------------------------------------------------------
#define BOX_MAX_RAW				(5)
#define BOX_MAX_COLUMN			(6)
#define BOX_MAX_TRAY			(18)
#define BOX_TRAYNAME_MAXLEN		(8)
#define BOX_TRAYNAME_BUFSIZE	(20)	// 日本語８文字＋EOM。海外版用の余裕も見てこの程度。
#define BOX_MAX_POS				(BOX_MAX_RAW*BOX_MAX_COLUMN)


#define BOX_NORMAL_WALLPAPER_MAX	(16)
#define BOX_EX_WALLPAPER_MAX		(8)
#define BOX_TOTAL_WALLPAPER_MAX		(BOX_NORMAL_WALLPAPER_MAX+BOX_EX_WALLPAPER_MAX)

#define BOXDAT_TRAYNUM_CURRENT		(0xffffffff)	///< トレイナンバーを引数に取る関数で指定すると、カレントを指定したことになる。
#define BOXDAT_TRAYNUM_ERROR		(BOX_MAX_TRAY)	///< 空きのあるトレイサーチで、見つからなかった時などの戻り値


extern BOX_DATA * SaveData_GetBoxData(SAVEDATA * sv);

//------------------------------------------------------------------
/**
 * ボックスデータ領域を作成（セーブデータ読み込み時に１回だけ）
 *
 * @param   heapID		作成先ヒープＩＤ
 *
 * @retval  BOX_DATA*	作成されたボックスデータのポインタ
 */
//------------------------------------------------------------------
extern BOX_DATA* BOXDAT_Create( u32 heapID );


//------------------------------------------------------------------
/**
 * ボックスデータの内容を初期化する
 *
 * @param   boxdat		ボックスデータのポインタ
 */
//------------------------------------------------------------------
extern void BOXDAT_Init( BOX_DATA* boxdat );

//------------------------------------------------------------------
/**
 * ボックスデータ領域の総サイズを返す（セーブデータ管理用）
 *
 * @retval  u32		ボックスデータ総サイズ
 */
//------------------------------------------------------------------
extern u32 BOXDAT_GetTotalSize( void );


//------------------------------------------------------------------
/**
 * ボックス全体からから空き領域を探してポケモンデータを格納
 *
 * @param   box			ボックスデータポインタ
 * @param   poke		ポケモンデータ
 *
 * @retval  BOOL		TRUE=格納された／FALSE=空きが無い
 */
//------------------------------------------------------------------
extern BOOL BOXDAT_PutPokemon( BOX_DATA* box, POKEMON_PASO_PARAM* poke );

//------------------------------------------------------------------
/**
 * ボックスを指定してポケモンデータ格納
 *
 * @param   box			ボックスデータポインタ
 * @param   boxNum		何番目のボックスに格納するか
 * @param   poke		ポケモンデータ
 *
 * @retval  BOOL		TRUE=格納された／FALSE=空きが無い
 */
//------------------------------------------------------------------
extern BOOL BOXDAT_PutPokemonBox( BOX_DATA* box, u32 boxNum, POKEMON_PASO_PARAM* poke );

//------------------------------------------------------------------
/**
 * ボックス、位置を指定してポケモンデータ格納
 *
 * @param   box			ボックスデータポインタ
 * @param   boxNum		何番目のボックスに格納するか
 * @param   x			ボックス内の位置Ｘ
 * @param   y			ボックス内の位置Ｙ
 * @param   poke		ポケモンデータ
 *
 * @retval  BOOL		TRUE=格納された／FALSE=空きが無い
 */
//------------------------------------------------------------------
extern BOOL BOXDAT_PutPokemonPos( BOX_DATA* box, u32 boxNum, u32 pos, POKEMON_PASO_PARAM* poke );


//------------------------------------------------------------------
/**
 * １つでも空きのあるトレイナンバーを返す（カレントから検索開始する）
 *
 * @param   box		ボックスデータポインタ
 *
 * @retval  u32		空きのあるトレイナンバー／見つからなければ BOXDAT_TRAYNUM_ERROR が返る
 */
//------------------------------------------------------------------
extern u32 BOXDAT_GetEmptyTrayNumber( const BOX_DATA* box );


//------------------------------------------------------------------
/**
 * 位置を指定してカレントボックスのポケモンデータクリア
 *
 * @param   box			ボックスデータポインタ
 * @param   trayNumber	何番目のボックスか
 * @param   pos			ボックス内の位置
 *
 */
//------------------------------------------------------------------
extern void BOXDAT_ClearPokemon( BOX_DATA* box, u32 trayNum, u32 pos );

//------------------------------------------------------------------
/**
 * ボックス全体に含まれるポケモン数を返す
 *
 * @param   box		ボックスデータポインタ
 *
 * @retval  u32		
 */
//------------------------------------------------------------------
extern u32 BOXDAT_GetPokeExistCountTotal( const BOX_DATA* box );
extern u32 BOXDAT_GetPokeExistCount2Total( const BOX_DATA* box );

extern u32 BOXDAT_GetEmptySpaceTotal( const BOX_DATA* box );
extern u32 BOXDAT_GetEmptySpaceTray( const BOX_DATA* box, u32 trayNum );

extern u32 BOXDAT_GetCureentTrayNumber( const BOX_DATA* box );
extern void BOXDAT_SetCureentTrayNumber( BOX_DATA* box, u32 num );
extern u32 BOXDAT_GetWallPaperNumber( const BOX_DATA* box, u32 trayNumber );
extern void BOXDAT_SetWallPaperNumber( BOX_DATA* box, u32 trayNum, u32 wallPaperNumber );
extern void BOXDAT_GetBoxName( const BOX_DATA* box, u32 trayNumber, STRBUF* buf );
extern void BOXDAT_SetBoxName( BOX_DATA* box, u32 trayNumber, const STRBUF* src );
extern u32 BOXDAT_GetPokeExistCount( const BOX_DATA* box, u32 trayNumber );
extern u32 BOXDAT_GetPokeExistCount2( const BOX_DATA* box, u32 trayNumber );
extern POKEMON_PASO_PARAM* BOXDAT_GetPokeDataAddress( const BOX_DATA* box, u32 boxNum, u32 pos );
extern BOOL BOXDAT_GetEmptyTrayNumberAndPos( const BOX_DATA* box, int* trayNum, int* pos );
extern u32 BOXDAT_PokeParaGet( const BOX_DATA* box, u32 trayNum, u32 pos, int param, void* buf );
extern void BOXDAT_PokeParaPut( BOX_DATA* box, u32 trayNum, u32 pos, int param, void* buf );


//==============================================================================================
// だいすきクラブ壁紙
//==============================================================================================
extern void BOXDAT_SetDaisukiKabegamiFlag( BOX_DATA* box, u32 number );
extern BOOL BOXDAT_GetDaisukiKabegamiFlag( const BOX_DATA* box, u32 number );
extern u32  BOXDAT_GetDaiukiKabegamiCount( const BOX_DATA* box );

#endif
