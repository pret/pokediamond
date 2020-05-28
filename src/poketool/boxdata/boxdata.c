//============================================================================================
/**
 * @file	boxdata.c
 * @brief	ポケモンボックスデータ取り扱い
 * @author	taya
 * @date	2005.09.05
 */
//============================================================================================
#include "common.h"
#include "gflib\strbuf_family.h"
#include "poketool\poke_tool.h"
#include "system\pm_str.h"
#include "system\msgdata.h"
#include "savedata\savedata.h"

#include "system\arc_tool.h"
#include "msgdata\msg.naix"
#include "msgdata\msg_boxmenu.h"
#include "poketool\boxdata.h"
#include "..\poke_tool_def.h"


struct _BOX_DATA{
	u32					currentTrayNumber;
	POKEMON_PASO_PARAM  ppp[BOX_MAX_TRAY][BOX_MAX_POS];
	STRCODE				trayName[BOX_MAX_TRAY][BOX_TRAYNAME_BUFSIZE];
	u8					wallPaper[BOX_MAX_TRAY];
	u8					daisukiBitFlag;
};


//==============================================================
// Prototype
//==============================================================
static void boxdata_init( BOX_DATA* boxdat );


//------------------------------------------------------------------
/**
 * ボックスデータ初期化
 */
//------------------------------------------------------------------
void BOXDAT_Init( BOX_DATA* boxdat )
{
	boxdata_init(boxdat);
	SaveData_RequestTotalSave();
}
//------------------------------------------------------------------
/**
 * ボックスデータの総サイズを返す
 *
 * @retval  u32		ボックスデータサイズ
 */
//------------------------------------------------------------------
u32 BOXDAT_GetTotalSize( void )
{
	return sizeof( BOX_DATA );
}


//------------------------------------------------------------------
/**
 * ボックスデータ領域初期化
 *
 * @param   boxdat		
 *
 */
//------------------------------------------------------------------
static void boxdata_init( BOX_DATA* boxdat )
{
	u32 i, p;
	MSGDATA_MANAGER*  msgman;

	for(i = 0; i < BOX_MAX_TRAY; i++)
	{
		for(p = 0; p < BOX_MAX_POS; p++)
		{
			PokePasoParaInit( &(boxdat->ppp[i][p]) );
		}
	}

	// 壁紙ナンバー，だいすきクラブ壁紙の取得フラグ
	for(i = 0, p = 0; i < BOX_MAX_TRAY; i++)
	{
		boxdat->wallPaper[i] = p++;
		if(p >= BOX_NORMAL_WALLPAPER_MAX)
		{
			p = 0;
		}
	}
	boxdat->daisukiBitFlag = 0;


	// デフォルトボックス名セット
	msgman = MSGMAN_Create( MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_boxmenu_dat, HEAPID_BASE_SYSTEM );
	if( msgman )
	{
		for(i = 0 ; i < BOX_MAX_TRAY; i++)
		{
			MSGMAN_GetStr( msgman, mes_boxmenu_02_02+i, boxdat->trayName[i] );
		}
		MSGMAN_Delete( msgman );
	}

	boxdat->currentTrayNumber = 0;

}
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
BOOL BOXDAT_PutPokemon( BOX_DATA* box, POKEMON_PASO_PARAM* poke )
{
	u32 b;

	b = box->currentTrayNumber;
	do
	{
		PokePasoPara_RecoverPP(poke);

		if( BOXDAT_PutPokemonBox( box, b, poke ) )
		{
			SaveData_RequestTotalSave();
			return TRUE;
		}

		if( ++b >= BOX_MAX_TRAY )
		{
			b = 0;
		}

	}while( b != box->currentTrayNumber );

	return FALSE;
}

//------------------------------------------------------------------
/**
 * ボックスを指定してポケモンデータ格納
 *
 * @param   box			ボックスデータポインタ
 * @param   trayNum		何番目のボックスに格納するか
 * @param   poke		ポケモンデータ
 *
 * @retval  BOOL		TRUE=格納された／FALSE=空きが無い
 */
//------------------------------------------------------------------
BOOL BOXDAT_PutPokemonBox( BOX_DATA* box, u32 trayNum, POKEMON_PASO_PARAM* poke )
{
	u32 i;

	PokePasoPara_RecoverPP(poke);

	if( trayNum == BOXDAT_TRAYNUM_CURRENT )
	{
		trayNum = box->currentTrayNumber;
	}

	for(i = 0; i < BOX_MAX_POS; i++)
	{
		if( PokePasoParaGet( &(box->ppp[trayNum][i]), ID_PARA_monsno, NULL  ) == 0 )
		{
			box->ppp[trayNum][i] = *poke;
			SaveData_RequestTotalSave();
			return TRUE;
		}
	}

	return FALSE;
}
//------------------------------------------------------------------
/**
 * ボックス、位置を指定してポケモンデータ格納
 *
 * @param   box			ボックスデータポインタ
 * @param   trayNum		何番目のボックスに格納するか
 * @param   pos			ボックス内の位置
 * @param   poke		ポケモンデータ
 *
 * @retval  BOOL		TRUE=格納された／FALSE=空きが無い
 */
//------------------------------------------------------------------
BOOL BOXDAT_PutPokemonPos( BOX_DATA* box, u32 trayNum, u32 pos, POKEMON_PASO_PARAM* poke )
{
	PokePasoPara_RecoverPP(poke);

	if( trayNum == BOXDAT_TRAYNUM_CURRENT )
	{
		trayNum = box->currentTrayNumber;
	}

	if(	(trayNum < BOX_MAX_TRAY)
	&&	(pos < BOX_MAX_POS)
	){
		box->ppp[trayNum][pos] = *poke;
		SaveData_RequestTotalSave();
		return TRUE;
	}
	else
	{
		GF_ASSERT(0);
	}
	return FALSE;
}





//------------------------------------------------------------------
/**
 * 位置を指定してボックスのポケモンデータクリア
 *
 * @param   box			ボックスデータポインタ
 * @param   trayNum		何番目のボックスか
 * @param   pos			ボックス内の位置
 *
 */
//------------------------------------------------------------------
void BOXDAT_ClearPokemon( BOX_DATA* box, u32 trayNum, u32 pos )
{
	if( trayNum == BOXDAT_TRAYNUM_CURRENT )
	{
		trayNum = box->currentTrayNumber;
	}

	if( (pos < BOX_MAX_POS) && (trayNum < BOX_MAX_TRAY) )
	{
		PokePasoParaInit( &(box->ppp[trayNum][pos]) );
		SaveData_RequestTotalSave();
	}
	else
	{
		GF_ASSERT(0);
	}
}

//------------------------------------------------------------------
/**
 * カレントのトレイナンバーを返す
 *
 * @param   box		ボックスデータポインタ
 *
 * @retval  u32		カレントトレイナンバー
 */
//------------------------------------------------------------------
u32 BOXDAT_GetCureentTrayNumber( const BOX_DATA* box )
{
	return box->currentTrayNumber;
}
//------------------------------------------------------------------
/**
 * １つでも空きのあるトレイナンバーを返す（カレントから検索開始する）
 *
 * @param   box		ボックスデータポインタ
 *
 * @retval  u32		空きのあるトレイナンバー／見つからなければ BOXDAT_TRAYNUM_ERROR
 */
//------------------------------------------------------------------
u32 BOXDAT_GetEmptyTrayNumber( const BOX_DATA* box )
{
	int tray, pos;

	tray = box->currentTrayNumber;

	while(1)
	{
		for(pos=0; pos<BOX_MAX_POS; pos++)
		{
			if( PokePasoParaGet( (POKEMON_PASO_PARAM*)(&(box->ppp[tray][pos])), ID_PARA_poke_exist, NULL  ) == 0 )
			{
				return tray;
			}
		}
		if( ++tray >= BOX_MAX_TRAY )
		{
			tray = 0;
		}
		if( tray == box->currentTrayNumber )
		{
			break;
		}
	}

	return BOXDAT_TRAYNUM_ERROR;
}
//------------------------------------------------------------------
/**
 * 空きのあるトレイナンバーとトレイ内の位置を検出
 *
 * @param   box			[in] ボックスデータポインタ
 * @param   trayNum		[in|out] 検出開始トレイナンバーを指定→最初に空きが見つかったトレイナンバーが入る
 * @param   pos			[in|out] 検出開始位置を指定→最初に空きが見つかったトレイ内の位置が入る
 *
 * @retval	空きが見つかったらTRUE, 見つからなかったらFALSE
 *
 */
//------------------------------------------------------------------
BOOL BOXDAT_GetEmptyTrayNumberAndPos( const BOX_DATA* box, int* trayNum, int* pos )
{
	int t, p;

	if( *trayNum == BOXDAT_TRAYNUM_CURRENT )
	{
		*trayNum = box->currentTrayNumber;
	}

	t = *trayNum;
	p = *pos;

	while(1)
	{
		for( ; p<BOX_MAX_POS; p++)
		{
			if( PokePasoParaGet( (POKEMON_PASO_PARAM*)(&(box->ppp[t][p])), ID_PARA_poke_exist, NULL  ) == 0 )
			{
				*trayNum = t;
				*pos = p;
				return TRUE;
			}
		}
		if( ++t >= BOX_MAX_TRAY )
		{
			t = 0;
		}
		if( t == (*trayNum) )
		{
			break;
		}
		p = 0;
	}

	return BOXDAT_TRAYNUM_ERROR;
}

//------------------------------------------------------------------
/**
 * 全体から空きの数をカウントして返す
 *
 * @param   box		ボックスデータポインタ
 *
 * @retval  u32		空きの数
 */
//------------------------------------------------------------------
u32 BOXDAT_GetEmptySpaceTotal( const BOX_DATA* box )
{
	int t, pos;
	u32 cnt;

	cnt = 0;

	for(t=0; t<BOX_MAX_TRAY; t++)
	{
		for(pos=0; pos<BOX_MAX_POS; pos++)
		{
			if( PokePasoParaGet( (POKEMON_PASO_PARAM*)(&(box->ppp[t][pos])), ID_PARA_poke_exist, NULL  ) != 0 )
			{
				cnt++;
			}
		}
	}

	return cnt;
}
//------------------------------------------------------------------
/**
 * 指定トレイから空きの数をカウントして返す
 *
 * @param   box		ボックスデータポインタ
 * @param   trayNum	トレイナンバー
 *
 * @retval  u32		空きの数
 */
//------------------------------------------------------------------
u32 BOXDAT_GetEmptySpaceTray( const BOX_DATA* box, u32 trayNum )
{
	int pos;
	u32 cnt;

	if( trayNum == BOXDAT_TRAYNUM_CURRENT )
	{
		trayNum = box->currentTrayNumber;
	}
	GF_ASSERT( trayNum < BOX_MAX_TRAY );


	cnt = 0;

	for(pos=0; pos<BOX_MAX_POS; pos++)
	{
		if( PokePasoParaGet( (POKEMON_PASO_PARAM*)(&(box->ppp[trayNum][pos])), ID_PARA_poke_exist, NULL  ) != 0 )
		{
			cnt++;
		}
	}

	return cnt;
}
//------------------------------------------------------------------
/**
 * カレントのトレイナンバーをセット
 *
 * @param   box		ボックスデータポインタ
 * @param   num		カレントトレイナンバー
 */
//------------------------------------------------------------------
void BOXDAT_SetCureentTrayNumber( BOX_DATA* box, u32 num )
{
	if( num < BOX_MAX_TRAY )
	{
		box->currentTrayNumber = num;
		SaveData_RequestTotalSave();
	}
	else
	{
		GF_ASSERT(0);
	}
}
//------------------------------------------------------------------
/**
 * 指定トレイの壁紙ナンバーを返す
 *
 * @param   box				ボックスデータポインタ
 * @param   trayNumber		トレイナンバー
 *
 * @retval  u32		壁紙ナンバー
 */
//------------------------------------------------------------------
u32 BOXDAT_GetWallPaperNumber( const BOX_DATA* box, u32 trayNum )
{
	if( trayNum < BOX_MAX_TRAY )
	{
		return box->wallPaper[trayNum];
	}
	else
	{
		GF_ASSERT(0);
		return 0;
	}
}
//------------------------------------------------------------------
/**
 * 指定トレイの壁紙ナンバーをセット
 *
 * @param   box				ボックスデータポインタ
 * @param   trayNum			トレイナンバー
 * @param   wallPaperNumber	壁紙ナンバー
 *
 */
//------------------------------------------------------------------
void BOXDAT_SetWallPaperNumber( BOX_DATA* box, u32 trayNum, u32 wallPaperNumber )
{
	if( trayNum == BOXDAT_TRAYNUM_CURRENT )
	{
		trayNum = box->currentTrayNumber;
	}

	if(	(trayNum < BOX_MAX_TRAY )
	&&	(wallPaperNumber < BOX_TOTAL_WALLPAPER_MAX )
	)
	{
		box->wallPaper[trayNum] = wallPaperNumber;
		SaveData_RequestTotalSave();
	}
	else
	{
		GF_ASSERT(0);
	}
}

//------------------------------------------------------------------
/**
 * 指定トレイの名前取得
 *
 * @param   box				ボックスデータポインタ
 * @param   trayNumber		トレイナンバー
 * @param   buf				文字列コピー先バッファ
 *
 */
//------------------------------------------------------------------
void BOXDAT_GetBoxName( const BOX_DATA* box, u32 trayNumber, STRBUF* buf )
{
	if( trayNumber == BOXDAT_TRAYNUM_CURRENT )
	{
		trayNumber = box->currentTrayNumber;
	}

	if( trayNumber < BOX_MAX_TRAY )
	{
		STRBUF_SetStringCode( buf, box->trayName[trayNumber] );
	}
	else
	{
		GF_ASSERT(0);
	}
}

//------------------------------------------------------------------
/**
 * 指定トレイの名前設定
 *
 * @param   box				ボックスデータポインタ
 * @param   trayNumber		トレイナンバー
 * @param   src				名前
 *
 */
//------------------------------------------------------------------
void BOXDAT_SetBoxName( BOX_DATA* box, u32 trayNumber, const STRBUF* src )
{
	if( trayNumber == BOXDAT_TRAYNUM_CURRENT )
	{
		trayNumber = box->currentTrayNumber;
	}

	if( trayNumber < BOX_MAX_TRAY )
	{
		STRBUF_GetStringCode( src, box->trayName[trayNumber], BOX_TRAYNAME_BUFSIZE );
		SaveData_RequestTotalSave();
	}
}
//------------------------------------------------------------------
/**
 * 指定トレイに格納されているポケモン数を返す
 *
 * @param   box				ボックスデータポインタ
 * @param   trayNumber		トレイナンバー
 *
 * @retval  u32		トレイに格納されているポケモン数
 */
//------------------------------------------------------------------
u32 BOXDAT_GetPokeExistCount( const BOX_DATA* box, u32 trayNum )
{
	if( trayNum == BOXDAT_TRAYNUM_CURRENT )
	{
		trayNum = box->currentTrayNumber;
	}

	if( trayNum < BOX_MAX_TRAY )
	{
		int i;
		u32 cnt = 0;
		for(i=0; i<BOX_MAX_POS; i++)
		{
			if(PokePasoParaGet( (POKEMON_PASO_PARAM*)(&(box->ppp[trayNum][i])), ID_PARA_poke_exist, NULL ))
			{
				cnt++;
			}
		}
		return cnt;
	}
	else
	{
		GF_ASSERT(0);
	}
	return 0;
}

//------------------------------------------------------------------
/**
 * 指定トレイに格納されているポケモン数を返す(タマゴ除外)
 *
 * @param   box				ボックスデータポインタ
 * @param   trayNumber		トレイナンバー
 *
 * @retval  u32		トレイに格納されているポケモン数
 */
//------------------------------------------------------------------
u32 BOXDAT_GetPokeExistCount2( const BOX_DATA* box, u32 trayNum )
{
	if( trayNum == BOXDAT_TRAYNUM_CURRENT )
	{
		trayNum = box->currentTrayNumber;
	}

	if( trayNum < BOX_MAX_TRAY )
	{
		int i;
		u32 cnt = 0;
		for(i=0; i<BOX_MAX_POS; i++)
		{
			if(PokePasoParaGet( (POKEMON_PASO_PARAM*)(&(box->ppp[trayNum][i])), ID_PARA_poke_exist, NULL ))
			{
				if(PokePasoParaGet( (POKEMON_PASO_PARAM*)(&(box->ppp[trayNum][i])), ID_PARA_tamago_flag, NULL ) == 0)	//タマゴ除外
				{
					cnt++;
				}
			}
		}
		return cnt;
	}
	else
	{
		GF_ASSERT(0);
	}
	return 0;
}

//------------------------------------------------------------------
/**
 * ボックス全体に含まれるポケモン数を返す
 *
 * @param   box		ボックスデータポインタ
 *
 * @retval  u32		
 */
//------------------------------------------------------------------
u32 BOXDAT_GetPokeExistCountTotal( const BOX_DATA* box )
{
	u32 cnt, i;

	for(i=0, cnt=0; i<BOX_MAX_TRAY; i++)
	{
		cnt += BOXDAT_GetPokeExistCount( box, i );
	}
	return cnt;
}

//------------------------------------------------------------------
/**
 * ボックス全体に含まれるポケモン数を返す(タマゴ除外版）
 *
 * @param   box		ボックスデータポインタ
 *
 * @retval  u32		
 */
//------------------------------------------------------------------
u32 BOXDAT_GetPokeExistCount2Total( const BOX_DATA* box )
{
	u32 cnt, i;

	for(i=0, cnt=0; i<BOX_MAX_TRAY; i++)
	{
		cnt += BOXDAT_GetPokeExistCount2( box, i );
	}
	return cnt;
}

//------------------------------------------------------------------
/**
 * ボックス格納ポケモンに対するPokePasoParaGet
 *
 * @param   box			ボックスデータポインタ
 * @param   trayNum		トレイナンバー
 * @param   pos			格納位置
 * @param   param		PokePasoParaGet パラメータ
 * @param   buf			PokePasoParaGet バッファ
 *
 * @retval  u32			PokePasoParaGet 戻り値
 */
//------------------------------------------------------------------
u32 BOXDAT_PokeParaGet( const BOX_DATA* box, u32 trayNum, u32 pos, int param, void* buf )
{
	GF_ASSERT((trayNum<BOX_MAX_TRAY)||(trayNum == BOXDAT_TRAYNUM_CURRENT));
	GF_ASSERT(pos<BOX_MAX_POS);

	if( trayNum == BOXDAT_TRAYNUM_CURRENT )
	{
		trayNum = box->currentTrayNumber;
	}

	return PokePasoParaGet( (POKEMON_PASO_PARAM*)(&box->ppp[trayNum][pos]), param, buf );
}


//------------------------------------------------------------------
/**
 * ボックス格納ポケモンに対するPokePasoParaPut
 *
 * @param   box			ボックスデータポインタ
 * @param   trayNum		トレイナンバー
 * @param   pos			格納位置
 * @param   param		PokePasoParaGet パラメータ
 * @param   buf			PokePasoParaGet バッファ
 *
 */
//------------------------------------------------------------------
void BOXDAT_PokeParaPut( BOX_DATA* box, u32 trayNum, u32 pos, int param, void* buf )
{
	GF_ASSERT((trayNum<BOX_MAX_TRAY)||(trayNum == BOXDAT_TRAYNUM_CURRENT));
	GF_ASSERT(pos<BOX_MAX_POS);

	if( trayNum == BOXDAT_TRAYNUM_CURRENT )
	{
		trayNum = box->currentTrayNumber;
	}

	PokePasoParaPut( (POKEMON_PASO_PARAM*)(&box->ppp[trayNum][pos]), param, buf );
	SaveData_RequestTotalSave();
}










//------------------------------------------------------------------
/**
 * 指定位置のポケモンデータへのポインタを返す
 *（あまり使ってほしくはない）
 *
 * @param   box			ボックスデータポインタ
 * @param   boxNum		ボックスナンバー
 * @param   pos			
 *
 * @retval  POKEMON_PASO_PARAM*		
 */
//------------------------------------------------------------------
POKEMON_PASO_PARAM* BOXDAT_GetPokeDataAddress( const BOX_DATA* box, u32 trayNum, u32 pos )
{
	GF_ASSERT_RETURN( ((trayNum<BOX_MAX_TRAY)||(trayNum == BOXDAT_TRAYNUM_CURRENT)), NULL );
	GF_ASSERT_RETURN( (pos<BOX_MAX_POS), NULL );

	if( trayNum == BOXDAT_TRAYNUM_CURRENT )
	{
		trayNum = box->currentTrayNumber;
	}

	return (POKEMON_PASO_PARAM*) &(box->ppp[trayNum][pos]);
}









//==============================================================================================
// だいすきクラブ壁紙
//==============================================================================================

//------------------------------------------------------------------
/**
 * だいすきクラブ壁紙を１枚、有効にする
 *
 * @param   box			ボックスデータポインタ
 * @param   number		有効にする壁紙ナンバー
 *
 */
//------------------------------------------------------------------
void BOXDAT_SetDaisukiKabegamiFlag( BOX_DATA* box, u32 number )
{
	GF_ASSERT( number < BOX_EX_WALLPAPER_MAX );

	box->daisukiBitFlag |= (1 << number);
	SaveData_RequestTotalSave();
}

//------------------------------------------------------------------
/**
 * だいすきクラブ壁紙を取得しているかチェック
 *
 * @param   box			ボックスデータポインタ
 * @param   number		チェックする壁紙ナンバー
 *
 * @retval  BOOL		TRUEで取得している
 */
//------------------------------------------------------------------
BOOL BOXDAT_GetDaisukiKabegamiFlag( const BOX_DATA* box, u32 number )
{
	GF_ASSERT( number < BOX_EX_WALLPAPER_MAX );

	return (box->daisukiBitFlag & (1<<number)) != 0;
}

//------------------------------------------------------------------
/**
 * 取得しただいすきクラブ壁紙の総数を取得
 *
 * @param   box		ボックスデータポインタ
 *
 * @retval  u32		
 */
//------------------------------------------------------------------
u32 BOXDAT_GetDaiukiKabegamiCount( const BOX_DATA* box )
{
	u32 i, cnt;

	for(i=0, cnt=0; i<BOX_EX_WALLPAPER_MAX; i++)
	{
		if( BOXDAT_GetDaisukiKabegamiFlag(box, i) )
		{
			cnt++;
		}
	}
	return cnt;
}
