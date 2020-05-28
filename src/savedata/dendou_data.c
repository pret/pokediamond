//============================================================================================
/**
 * @file	dendou_data.c
 * @brief	殿堂入りセーブデータ
 * @author	taya
 * @date	2006.04.20
 */
//============================================================================================
#include "common.h"
#include "savedata\savedata.h"
#include "system\gamedata.h"
#include "gflib\strbuf_family.h"
#include "poketool\pokeparty.h"

#include "savedata\dendou_data.h"


enum {
	POKENAME_BUFSIZE = MONS_NAME_SIZE+EOM_SIZE,		// 11
	OYANAME_BUFSIZE = PERSON_NAME_SIZE+EOM_SIZE,	// 8
};


//----------------------------------------------------------
/**
 *	殿堂入りポケモン個体データ（60 bytes）
 */
//----------------------------------------------------------
typedef struct {
	u16	monsno;				///< ポケモンナンバー（０ならデータ全体が無効）
	u8	level;				///< レベル
	u8	formNumber;			///< フォルム
	u32	personalRandom;		///< 個体乱数
	u32	idNumber;			///< ID
	STRCODE	nickname[ POKENAME_BUFSIZE ];	///< ニックネーム
	STRCODE	oyaname[ OYANAME_BUFSIZE ];		///< おや名
	u16	waza[ 4 ];			///< 技ナンバー
}DENDOU_POKEMON_DATA_INSIDE;


//----------------------------------------------------------
/**
 *	殿堂入り１件レコードデータ（364 bytes）
 */
//----------------------------------------------------------
typedef struct {
	DENDOU_POKEMON_DATA_INSIDE	pokemon[ TEMOTI_POKEMAX ];	///< ポケモンデータ
	u16			year;				///< 殿堂入り日付（年） 2006 ～
	u8			month;				///< 殿堂入り日付（月） 1～12
	u8			day;				///< 殿堂入り日付（日） 1～31
}DENDOU_RECORD;


//----------------------------------------------------------
/**
 *	殿堂入りセーブデータ本体（10920 bytes）
 */
//----------------------------------------------------------
struct _DENDOU_SAVEDATA {

	DENDOU_RECORD	record[ DENDOU_RECORD_MAX ];

	u32		savePoint;		///< record配列中の、次にセーブするindex
	u32		latestNumber;	///< 最新データの殿堂入り通算回数
};



//==============================================================
// Prototype
//==============================================================
static int inline recIndex_to_datIndex( const DENDOU_SAVEDATA* data, int recIndex );





//------------------------------------------------------------------
/**
 * セーブデータサイズを返す
 *
 * @retval  int		
 */
//------------------------------------------------------------------
int DendouData_GetWorkSize( void )
{
	return sizeof(DENDOU_SAVEDATA);
}
//------------------------------------------------------------------
/**
 * データ初期化
 *
 * @param   data		
 *
 */
//------------------------------------------------------------------
void DendouData_Init( DENDOU_SAVEDATA* data )
{
	MI_CpuClear32( data, sizeof(DENDOU_SAVEDATA) );
}




//------------------------------------------------------------------
/**
 * 殿堂入りレコード１件追加
 *
 * @param   data		殿堂入りセーブデータポインタ
 * @param   party		殿堂入りパーティーのデータ
 * @param   date		殿堂入り日付データ（NITROのデータそのまま）
 *
 */
//------------------------------------------------------------------
void DendouData_AddRecord( DENDOU_SAVEDATA* data, const POKEPARTY* party, const RTCDate* date )
{
	DENDOU_RECORD*  record;
	POKEMON_PARAM*  pp;
	STRBUF*         strbuf;
	int  pokeCount, i, p;
	BOOL fastFlag;

	GF_ASSERT(data != NULL);
	GF_ASSERT(data->savePoint < DENDOU_RECORD_MAX);

	if( data->latestNumber >= DENDOU_NUMBER_MAX )
	{
		return;
	}

	record = &data->record[ data->savePoint ];
	pokeCount = PokeParty_GetPokeCount( party );

	strbuf = STRBUF_Create( POKENAME_BUFSIZE, HEAPID_BASE_SYSTEM );

	MI_CpuClear16( record->pokemon,  sizeof(DENDOU_POKEMON_DATA_INSIDE)*TEMOTI_POKEMAX );

	for(i=0, p=0; i<pokeCount; i++)
	{
		pp = PokeParty_GetMemberPointer( party, i );

		fastFlag = PokeParaFastModeOn( pp );

		if( PokeParaGet(pp, ID_PARA_tamago_flag, NULL) == FALSE )
		{
			record->pokemon[p].monsno = PokeParaGet( pp, ID_PARA_monsno, NULL );
			record->pokemon[p].level = PokeParaGet( pp, ID_PARA_level, NULL );
			record->pokemon[p].formNumber = PokeParaGet( pp, ID_PARA_form_no, NULL );
			record->pokemon[p].personalRandom = PokeParaGet( pp, ID_PARA_personal_rnd, NULL );
			record->pokemon[p].idNumber = PokeParaGet( pp, ID_PARA_id_no, NULL );
			record->pokemon[p].waza[0] = PokeParaGet( pp, ID_PARA_waza1, NULL );
			record->pokemon[p].waza[1] = PokeParaGet( pp, ID_PARA_waza2, NULL );
			record->pokemon[p].waza[2] = PokeParaGet( pp, ID_PARA_waza3, NULL );
			record->pokemon[p].waza[3] = PokeParaGet( pp, ID_PARA_waza4, NULL );

			if(strbuf)
			{
				PokeParaGet( pp, ID_PARA_nickname_buf, strbuf );
				STRBUF_GetStringCode( strbuf, record->pokemon[p].nickname, POKENAME_BUFSIZE );

				PokeParaGet( pp, ID_PARA_oyaname_buf, strbuf );
				STRBUF_GetStringCode( strbuf, record->pokemon[p].oyaname, OYANAME_BUFSIZE );
			}
			else
			{
				record->pokemon[p].nickname[0] = EOM_;
				record->pokemon[p].oyaname[0] = EOM_;
			}

			p++;
		}

		PokeParaFastModeOff( pp, fastFlag );
	}

	record->year = date->year;
	record->month = date->month;
	record->day = date->day;


	if(++(data->savePoint) >= DENDOU_RECORD_MAX)
	{
		data->savePoint = 0;
	}
	data->latestNumber++;


	if(strbuf)
	{
		STRBUF_Delete(strbuf);
	}

}




//------------------------------------------------------------------
/**
 * 殿堂入りレコード件数を返す
 *
 * @param   data	殿堂入りデータポインタ
 *
 * @retval  u32		件数
 */
//------------------------------------------------------------------
u32 DendouData_GetRecordCount( const DENDOU_SAVEDATA* data )
{
	GF_ASSERT(data != NULL);
	GF_ASSERT(data->savePoint < DENDOU_RECORD_MAX);

	if( data->latestNumber >= DENDOU_RECORD_MAX )
	{
		return DENDOU_RECORD_MAX;
	}
	return data->latestNumber;
}
//------------------------------------------------------------------
/**
 * 殿堂入りレコードが、何回目の殿堂入りかを返す
 *
 * @param   data		殿堂入りデータポインタ
 * @param   index		レコードインデックス（0が最新で、順に旧くなっていく）
 *
 * @retval  u32			
 */
//------------------------------------------------------------------
u32 DendouData_GetRecordNumber( const DENDOU_SAVEDATA* data, int index )
{
	GF_ASSERT(data != NULL);
	GF_ASSERT(data->savePoint < DENDOU_RECORD_MAX);
	GF_ASSERT(index < DENDOU_RECORD_MAX);

	return data->latestNumber - index;
}
//------------------------------------------------------------------
/**
 * 殿堂入りレコードから、ポケモン数取得
 *
 * @param   data		殿堂入りデータポインタ
 * @param   index		レコードインデックス（0が最新で、順に旧くなっていく）
 *
 * @retval	u32		殿堂入りパーティーのポケモン数
 */
//------------------------------------------------------------------
u32 DendouData_GetPokemonCount( const DENDOU_SAVEDATA* data, int index )
{
	u32 i;

	GF_ASSERT(data != NULL);
	GF_ASSERT(data->savePoint < DENDOU_RECORD_MAX);
	GF_ASSERT(index < DENDOU_RECORD_MAX);

	index = recIndex_to_datIndex( data, index );
	for(i=0; i<TEMOTI_POKEMAX; i++)
	{
		if(data->record[index].pokemon[i].monsno == 0)
		{
			break;
		}
	}
	return i;
}
//------------------------------------------------------------------
/**
 * 殿堂入りレコードから、ポケモンデータ取得
 *
 * @param   data		殿堂入りデータポインタ
 * @param   index		レコードインデックス（0が最新で、順に旧くなっていく）
 * @param   poke_pos	何体目のポケモンか（0～5）
 * @param   poke_data	ポケモンデータを受け取る構造体のポインタ
 */
//------------------------------------------------------------------
void DendouData_GetPokemonData( const DENDOU_SAVEDATA* data, int index, int poke_pos, DENDOU_POKEMON_DATA* poke_data )
{
	const DENDOU_POKEMON_DATA_INSIDE*  recPoke;
	int i;

	GF_ASSERT(data != NULL);
	GF_ASSERT(data->savePoint < DENDOU_RECORD_MAX);
	GF_ASSERT(index < DENDOU_RECORD_MAX);

	index = recIndex_to_datIndex( data, index );
	recPoke = &(data->record[index].pokemon[poke_pos]);

	poke_data->monsno = recPoke->monsno;
	poke_data->level = recPoke->level;
	poke_data->personalRandom = recPoke->personalRandom;
	poke_data->idNumber = recPoke->idNumber;
	poke_data->formNumber = recPoke->formNumber;

	STRBUF_SetStringCode( poke_data->nickname, recPoke->nickname );
	STRBUF_SetStringCode( poke_data->oyaname, recPoke->oyaname );

	for(i=0; i<4; i++)
	{
		poke_data->waza[i] = recPoke->waza[i];
	}
}
//------------------------------------------------------------------
/**
 * 殿堂入りレコードから、殿堂入り日付取得
 *
 * @param   data		殿堂入りデータポインタ
 * @param   index		レコードインデックス（0が最新で、順に旧くなっていく）
 * @param   date		日付データを受け取る構造体へのポインタ
 */
//------------------------------------------------------------------
void DendouData_GetDate( const DENDOU_SAVEDATA* data, int index, RTCDate* date )
{
	GF_ASSERT(data != NULL);
	GF_ASSERT(data->savePoint < DENDOU_RECORD_MAX);
	GF_ASSERT(index < DENDOU_RECORD_MAX);

	index = recIndex_to_datIndex( data, index );
	date->year = data->record[index].year;
	date->month = data->record[index].month;
	date->day = data->record[index].day;

	// 曜日は保存しないが、一応クリアしておく
	date->week = 0;

}















//------------------------------------------------------------------
/**
 * レコードインデックス（新しい順インデックス）をデータ配列インデックスに変換
 *
 * @param   index		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int inline recIndex_to_datIndex( const DENDOU_SAVEDATA* data, int recIndex )
{
	int datIndex = (data->savePoint - 1 - recIndex);
	if( datIndex < 0 )
	{
		datIndex += DENDOU_RECORD_MAX;
	}
	return datIndex;
}
